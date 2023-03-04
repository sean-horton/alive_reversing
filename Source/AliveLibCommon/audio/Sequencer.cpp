#pragma once

#include "Sequencer.hpp"
#include <array>

namespace sean {

/////////////////////////////////
/// DuckStation
u32 mask(u32 num)
{
    u32 res = 0;
    while (num-- > 0)
    {
        res = (res << 1) | 1;
    }
    return res;
}

ADSR parseADSR(u16 adsr1, u16 adsr2)
{
    ADSR adsr;
    adsr.sustainLevel = (adsr1) &mask(4);
    adsr.decayRate = (adsr1 >> 4) & mask(4);
    adsr.attackRate = (adsr1 >> 8) & mask(7);
    adsr.attackExponential = (adsr1 >> 15) & mask(1);

    adsr.releaseRate = adsr2 & mask(5);
    adsr.releaseExponential = (adsr2 >> 5) & mask(1);
    adsr.sustainRate = (adsr2 >> 6) & mask(7);
    adsr.sustainDirection = (adsr2 >> 14) & mask(1);
    adsr.sustainExponential = (adsr2 >> 15) & mask(1);
    return adsr;
}

struct ADSRTableEntry
{
    s32 ticks;
    s32 step;
};
enum : u32
{
    NUM_ADSR_TABLE_ENTRIES = 128,
    NUM_ADSR_DIRECTIONS = 2 // increasing, decreasing
};
using ADSRTableEntries = std::array<std::array<ADSRTableEntry, NUM_ADSR_TABLE_ENTRIES>, NUM_ADSR_DIRECTIONS>;

static constexpr ADSRTableEntries ComputeADSRTableEntries()
{
    ADSRTableEntries entries = {};
    for (u32 decreasing = 0; decreasing < 2; decreasing++)
    {
        for (u32 rate = 0; rate < NUM_ADSR_TABLE_ENTRIES; rate++)
        {
            if (rate < 48)
            {
                entries[decreasing][rate].ticks = 1;
                if (decreasing != 0)
                    entries[decreasing][rate].step = static_cast<s32>(static_cast<u32>(-8 + static_cast<s32>(rate & 3)) << (11 - (rate >> 2)));
                else
                    entries[decreasing][rate].step = (7 - static_cast<s32>(rate & 3)) << (11 - (rate >> 2));
            }
            else
            {
                entries[decreasing][rate].ticks = 1 << (static_cast<s32>(rate >> 2) - 11);
                if (decreasing != 0)
                    entries[decreasing][rate].step = (-8 + static_cast<s32>(rate & 3));
                else
                    entries[decreasing][rate].step = (7 - static_cast<s32>(rate & 3));
            }
        }
    }

    return entries;
}

static constexpr ADSRTableEntries s_adsr_table = ComputeADSRTableEntries();

//struct Voice
//{
//    u16 current_address;
//    VoiceRegisters regs;
//    VoiceCounter counter;
//    ADPCMFlags current_block_flags;
//    bool is_first_block;
//    std::array<s16, NUM_SAMPLES_FROM_LAST_ADPCM_BLOCK + NUM_SAMPLES_PER_ADPCM_BLOCK> current_block_samples;
//    std::array<s16, 2> adpcm_last_samples;
//    s32 last_volume;
//
//    VolumeSweep left_volume;
//    VolumeSweep right_volume;
//
//    VolumeEnvelope adsr_envelope;
//    ADSRPhase adsr_phase;
//    s16 adsr_target;
//    bool has_samples;
//    bool ignore_loop_address;
//
//    bool IsOn() const
//    {
//        return adsr_phase != ADSRPhase::Off;
//    }
//
//    void KeyOn();
//    void KeyOff();
//    void ForceOff();
//
//    void DecodeBlock(const ADPCMBlock& block);
//    s32 Interpolate() const;
//
//    // Switches to the specified phase, filling in target.
//    void UpdateADSREnvelope();
//
//    // Updates the ADSR volume/phase.
//    void TickADSR();
//};
/// DuckStation END
/////////////////////////////////

Sequencer::Sequencer()
{
    for (int i = 0; i < sourceCount; i++)
    {
        voices[i] = NULL;
        patches[i] = NULL;
        sourceLock[i] = false;
    }

    // Open the AL device
    ALenum error;
    alGetError(); // clear out error state
    device = alcOpenDevice(NULL);
    ctx = alcCreateContext(device, NULL);
    alcMakeContextCurrent(ctx);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        return;
    }

    // Prepare some known effects we will use
    LOAD_EFFECT_FUNCTIONS();
    EFXEAXREVERBPROPERTIES reverb = EFX_REVERB_PRESET_AUDITORIUM;
    efxReverb0 = PREPARE_REVERB(&reverb);
    alGenAuxiliaryEffectSlots(1, &efxSlot0);
    alAuxiliaryEffectSloti(efxSlot0, AL_EFFECTSLOT_EFFECT, (ALint) efxReverb0);

    // Prepare sources (these are streams buffers can be played in)
    alGenSources(sourceCount, source);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        return;
    }
}

Sequencer::~Sequencer()
{
    // Delete sources
    alDeleteSources(sourceCount, source);

    // Delete effects
    alDeleteAuxiliaryEffectSlots(1, &efxSlot0);
    alDeleteEffects(1, &efxReverb0);

    // Close AL device
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(device);

    // Delete buffers (by killing the instrument)
    for (Patch* patch : patches)
    {
        delete patch;
    }
}

u64 timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


//////////////////////////
// PRIVATE
void Sequencer::reset()
{
    alcSuspendContext(ctx);

    for (s16 i = 0; i < sourceCount; i++)
    {
        releaseSource(i);
        releaseVoice(voices[i]);
    }

    for (s16 i = 0; i < sourceCount; i++)
    {
        // must be deleted separately from sources
        // since deleting a patch may delete a buffer
        // attached to a source
        delete patches[i];
        patches[i] = NULL;
    }

    for (Sequence* seq : sequences)
    {
        delete seq;
    }
    sequences.clear();

    alcProcessContext(ctx);
}

void Sequencer::playSeq(s32 seqId)
{
    for (Sequence* seq : sequences)
    {
        if (seq->id == seqId)
        {
            seq->play = true;
        }
    }
}

void Sequencer::stopSeq(s32 seqId)
{
    for (Sequence* seq : sequences)
    {
        if (seq->id == seqId)
        {
            seq->play = false;
            for (Voice* v : voices)
            {
                if (v && v->sequence == seq)
                {
                    //v->forceStopNow = true;
                }
            }
        }
    }
}


void Sequencer::tick()
{
    // pause openal changes to perform bulk update - more performant.
    // unpause is called at the end.
    alcSuspendContext(ctx);
    
    ADSRTableEntry e = s_adsr_table[0][0];
    ADSRTableEntries table = s_adsr_table;

    u64 now = timeSinceEpochMillisec();

    // Tick sequences
    for (Sequence* seq : sequences)
    {
        if (!seq || !seq->play)
        {
            continue;
        }
        
        //if (seq->repeats >= seq->repeatLimit)
        //{
        //    stopSeq(seq->id);
        //    continue;
        //}

        MIDIMessage* message;
        while ((message = seq->next(now)) != NULL)
        {
            switch (message->type)
            {
                case NOTE_ON:
                {
                    if (!seq->channels[message->channelId]->patch)
                    {
                        break;
                    }

                    Voice* v = obtainVoice();
                    if (v)
                    {
                        v->sequence = seq;
                        v->note = message->note;
                        v->noteVolume = message->velocity;
                        v->patch = seq->channels[message->channelId]->patch;
                    }
                    break;
                }
                case NOTE_OFF:
                {
                    for (Voice* v : voices)
                    {
                        if (v && v->sequence == seq && v->note == message->note)
                        {
                            v->offTime = now;
                        }
                    }
                    break;
                }
                case PATCH_CHANGE:
                    seq->channels[message->channelId]->patch = patches[message->patchId];
                    break;

                case END_TRACK:
                    // repeats are handled in the sequence when messages starts at position 1 again
                    break;
            }
        }
    }

    // Tick voices
    ALenum error;
    int vCount = 0;
    for (int c = 0; c < sourceCount; c++)
    {

        Voice* voice = voices[c];
        if (!voice)
        {
            continue;
        }
        vCount++;
        // we are just starting to play this note
        if (voice->onTime == 0 && !voice->forceStopNow)
        {
            if (!voice->patch)
            {
                continue;
            }

            voice->onTime = now;
            for (Sample* sample : voice->patch->samples)
            {
                if (!sample)
                {
                    continue;
                }

                if (voice->note > sample->maxNote || voice->note < sample->minNote)
                {
                    continue;
                }

                s16 id = obtainSource();
                if (id < 0)
                {
                    continue;
                }

                alSourcei(source[id], AL_BUFFER, sample->alBuffer);
                if ((error = alGetError()) != AL_NO_ERROR)
                {
                    continue;
                }

                alSourcePlay(source[id]);
                if ((error = alGetError()) != AL_NO_ERROR)
                {
                    continue;
                }

                voice->sources.push_back(id);
                voice->samples.push_back(sample);
                voice->loop = sample->attack / 1000 > 1;
            }
        }

        // Update the play source paramters
        int playCount = 0;
        ALenum state;
        for (int i = 0; i < (int) voice->sources.size(); i++)
        {
            Sample* sample = voice->samples.at(i);
            s16 id = voice->sources.at(i);

            if (id < 0)
            {
                continue;
            }

            // If we are past the duration of the notes playback 
            alGetSourcei(source[id], AL_SOURCE_STATE, &state);
            if (state != AL_PLAYING 
                || voice->forceStopNow 
                //|| (voice->offTime != 0 && now > voice->offTime + sample->release) 
                //|| (voice->offTime != 0 && sample->release > 60000 && voice->loop)
                )
            {
                releaseSource(id);
                voice->samples.at(i) = NULL;
                voice->sources.at(i) = -1;
                continue;
            }

            u8 note = voice->note;
            s32 notePitch = voice->pitch < voice->pitchMin ? voice->pitchMin : voice->pitch; // or sample?
            u8 rootNote = sample->rootNote;
            u8 rootPitch = sample->rootNotePitchShift;
            // This figures out the frequency of midi notes (ex. 60 is middle C and 261.63 hz)
            // noteFreq is the note we want to play
            // rootFreq is the samples root note 
            // We then divide the two to figure out how to pitch shift the sample to match the 
            // the desired note. For some reason we have to multiply it by 2. don't know why. 
            float noteFreq = float(pow(2.0, float(note + (notePitch / 127.0f)) / 12.0f));
            float rootFreq = float(pow(2.0, float(rootNote + (rootPitch / 127.0f)) / 12.0f));
            float freq = noteFreq / rootFreq * 2.0f;
            float pan = voice->pan;

            if (sample->pan)
            {
                pan = sample->pan;
            }

            float volume = voice->velocity;
            Sequence* seq = voice->sequence;
            //if (seq)
            //{
            //    volume = seq->volume * volume;
            //}


            float attackMulti = 1;
            if (sample->attack > 1000 && now < voice->onTime + sample->attack)
            {
                float offset = float(voice->onTime + sample->attack - now);
                attackMulti = offset / float(sample->attack);
                attackMulti = 1 - std::min(1.0f, std::max(0.0f, attackMulti));
            }

            float decayMulti = 1;
            if (sample->decay != 0 && now < voice->onTime + sample->attack + sample->decay)
            {
                decayMulti;
            }

            float releaseMulti = 1;
            if (voice->offTime != 0 && now >= voice->offTime)
            {
                releaseMulti = 1 - (float(now - voice->offTime) / float(sample->release));
                //releaseMulti = exp(-5 * releaseMulti);
                //std::cout << releaseMulti <<std::endl;
            }

            //volume = volume * releaseMulti * attackMulti * decayMulti;


            //counter--;
            //if (counter > 0)
            //    return current_level;
            //
            //const ADSRTableEntry& table_entry = s_adsr_table[BoolToUInt8(decreasing)][rate];
            //s32 this_step = table_entry.step;
            //counter = table_entry.ticks;
            //
            //if (exponential)
            //{
            //    if (decreasing)
            //    {
            //        this_step = (this_step * current_level) >> 15;
            //    }
            //    else
            //    {
            //        if (current_level >= 0x6000)
            //        {
            //            if (rate < 40)
            //            {
            //                this_step >>= 2;
            //            }
            //            else if (rate >= 44)
            //            {
            //                counter >>= 2;
            //            }
            //            else
            //            {
            //                this_step >>= 1;
            //                counter >>= 1;
            //            }
            //        }
            //    }
            //}
            //
            //return static_cast<s16>(
            //    std::clamp<s32>(static_cast<s32>(current_level) + this_step, ENVELOPE_MIN_VOLUME, ENVELOPE_MAX_VOLUME));
            // ENVELOPE_MIN_VOLUME = 0         and       ENVELOPE_MAX_VOLUME = 0x7FFF (32767)
            



            //void SPU::VolumeEnvelope::Reset(u8 rate_, bool decreasing_, bool exponential_)
            //{
            //    rate = rate_;
            //    decreasing = decreasing_;
            //    exponential = exponential_;
            //
            //    const ADSRTableEntry& table_entry = s_adsr_table[BoolToUInt8(decreasing)][rate];
            //    counter = table_entry.ticks;
            //}



            //if (exponential)
            //{
            //    if (decreasing)
            //    {
            //        this_step = (this_step * current_level) >> 15;
            //    }
            //    else
            //    {
            //        if (current_level >= 0x6000)
            //        {
            //            if (rate < 40)
            //            {
            //                this_step >>= 2;
            //            }
            //            else if (rate >= 44)
            //            {
            //                counter >>= 2;
            //            }
            //            else
            //            {
            //                this_step >>= 1;
            //                counter >>= 1;
            //            }
            //        }
            //    }
            //}

            // According to duckstation
            // MASTER_CLOCK = 44100 * 0x300 // 33868800Hz or 33.8688MHz, also used as CPU clock
            // SYSCLK_TICKS_PER_SPU_TICK = System::MASTER_CLOCK / SAMPLE_RATE, // 0x300
            
            // 768 sys clock ticks per spu tick - sys clock tick is 
            // ----- so 768 spu ticks per second -----


            alSource3f(source[id], AL_POSITION, pan, 0, -sqrtf(1.0f - pan * pan));
            alSourcef(source[id], AL_PITCH, (ALfloat) freq);
            alSourcef(source[id], AL_GAIN, (ALfloat) volume);
            alSourcei(source[id], AL_LOOPING, voice->loop);

            // 0 Off
            // 1 Vibrate 
            // 2 Portamento 
            // 3 1 & 2(Portamento and Vibrate on) 
            // 4 Reverb
            if (sample->reverb != 0)
            {
                alSource3i(source[id], AL_AUXILIARY_SEND_FILTER, (ALint) efxSlot0, 0, AL_FILTER_NULL);
            }
            else
            {
                alSource3i(source[id], AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, NULL);
            }
            
            playCount++;
            if (!seq)
            {
                continue;
            }

            
            u64 runtimeUs = std::max((u64) 0, now - voice->onTime) * 1000; // x1000 to conver to microseconds
            float midiTickUs = seq->tempoUs / seq->ticksPerBeat;
            u64 voiceTick = u64(runtimeUs / midiTickUs);
            ADSRTableEntry entryAttack = s_adsr_table[false][sample->adsr.attackRate];
            ADSRTableEntry entryDecay = s_adsr_table[true][sample->adsr.decayRate << 2];
            ADSRTableEntry entrySustain = s_adsr_table[sample->adsr.sustainDirection][sample->adsr.sustainRate];
            ADSRTableEntry entryRelease = s_adsr_table[true][sample->adsr.releaseRate << 2];
            entryAttack;
            entryDecay;
            entrySustain;
            entryRelease;
            voiceTick;

            // sample voice seq

            float currentLevel = volume * 32767;
            if (voice->lastProcessedTick == 0)
            {
                voice->lastProcessedTick = voiceTick;
                voice->lastProcessedMs = voice->onTime;
                voice->velocity = 0.0f;
                currentLevel = 0.0f;
                volume = 0.0f;
            }


            //    std::clamp<s32>(static_cast<s32>(current_level) + this_step, ENVELOPE_MIN_VOLUME, ENVELOPE_MAX_VOLUME));
            // ENVELOPE_MIN_VOLUME = 0         and       ENVELOPE_MAX_VOLUME = 0x7FFF (32767)
            //if (voiceTick <= entryAttack.ticks)
            //if (now <= voice->onTime + sample->attack) 
            //{

                //if (sample->attack > 1000 && now < voice->onTime + sample->attack)
                //{
                //    float offset = float(voice->onTime + sample->attack - now);
                //    attackMulti = offset / float(sample->attack);
                //    attackMulti = 1 - std::min(1.0f, std::max(0.0f, attackMulti));
                //    currentLevel = currentLevel * attackMulti + currentLevel;
                //}

                //currentLevel = volume * 32767 + 1000;


                //volume = volume * 0.5f;
                // in attack
            /*    volume = volume * 32767.0f + float(entryAttack.step) / 32767.0f;
                volume = volume + 0.01f;*/


            // NOTE: Default is 60 ticks per second?
            //float ttt = 44100.0f / 4096.0f;
            while (voice->offTime == 0 && voice->lastProcessedTick++ <= voiceTick + u64(entryAttack.ticks))
            //while (voice->lastProcessedMs++ <= (voice->onTime) + (entryAttack.ticks * 0.2441f))
            //while (voice->lastProcessedMs <= voice->onTime + (entryAttack.ticks * ttt))
            //float tmp = float(now - voice->lastProcessedMs) / 60;
            //float cccccc = 0.0f;
            //while (voice->offTime == 0 && cccccc++ <= tmp)
            //if (voice->offTime == 0 )
            //s64 start = voice->lastProcessedMs * 1000;
            //s64 end = s64(voice->onTime * 1000) + s64(s64(entryAttack.ticks) * s64(768));
            //while (voice->offTime == 0 && start <= end)
            {
                //start = start + 24;
                //voice->lastProcessedMs = voice->lastProcessedMs + u64(midiTickUs / 1000.0f);
                if (sample->adsr.attackExponential)
                {
                    voice->counter--;
                    if (voice->counter <= 0)
                    {
                        s32 this_step = entryAttack.step;
                        voice->counter = entryAttack.ticks;

                        if (currentLevel >= 0x6000)
                        {
                            if (sample->adsr.attackRate < 40)
                            {
                                this_step >>= 2;
                            }
                            else if (sample->adsr.attackRate >= 44)
                            {
                                voice->counter >>= 2;
                            }
                            else
                            {
                                this_step >>= 1;
                                voice->counter >>= 1;
                            }
                        }

                        currentLevel = currentLevel + this_step;
                    }
                }
                else
                {
                    currentLevel = currentLevel + entryAttack.step;
                }
            }
            //voice->lastProcessedMs = start / 1000;
            volume = currentLevel / 32767;
            volume = std::min(volume, sample->volume * seq->volume * voice->noteVolume);

            if (voice->offTime == 0 && voiceTick <= u64(entryAttack.ticks) + u64(entryDecay.ticks))
            {
                // in decay
                //volume = volume * 0.75f;
                //volume = volume * 32767.0f + float(entryDecay.step) / 32767.0f;
                //volume = volume - 0.01f;
                //volume = float(sample->adsr.sustainLevel / 127.0f * sample->volume * seq->volume);
            }
            else if (voice->offTime == 0 && voice->lastProcessedTick > voiceTick + u64(entryAttack.ticks) + u64(entryDecay.ticks))
            {
                // in sustain
                //volume = volume * 0.5f;
                //volume = 1.0f;
                volume = float((sample->adsr.sustainLevel / 127.0f) * sample->volume * seq->volume * voice->noteVolume);
            }
            else if (voice->offTime != 0)
            {
                // in release
                //volume = volume * 0.1f;
                //this_step = (this_step * current_level) >> 15;
                if (sample->adsr.releaseExponential)
                {
                    //while (voice->lastProcessedMs++ * 1000 < now * 1000)
                    //while (dur-- > 0)
                    //while (voice->lastProcessedMs <= now)
                    while (voice->lastProcessedTick++ <= voiceTick)
                    {
                        //voice->lastProcessedMs = voice->lastProcessedMs + u64(ttt);
                        s32 this_step = entryRelease.step;
                        this_step = s32(float(this_step) * currentLevel) >> 15;
                        currentLevel = currentLevel + this_step;
                    }
                }
                else
                {
                    currentLevel = currentLevel + entryRelease.step;
                }
                
                volume = currentLevel / 32767;

                //volume = volume * 32767 + this_step / 32767;


                //volume = volume * 32767.0f + float(entryRelease.step) / 32767.0f;
                //volume = volume - 0.01f;
            }
            volume = std::max(0.0f, std::min(1.0f, volume)); // clamp
            volume = std::min(volume, sample->volume * seq->volume);
            voice->velocity = volume;
            voice->lastProcessedTick = voiceTick;
            voice->lastProcessedMs = now;
            if (volume < 0.00001f)
            {
                playCount--;
            }
            alSourcef(source[id], AL_GAIN, (ALfloat) volume);

            
            //case ADSRPhase::Attack:
            //    adsr_target = 32767; // 0 -> max
            //    adsr_envelope.Reset(regs.adsr.attack_rate, false, regs.adsr.attack_exponential);
            //    break;
            //
            //case ADSRPhase::Decay:
            //    adsr_target = static_cast<s16>(std::min<s32>((u32(regs.adsr.sustain_level.GetValue()) + 1) * 0x800,
            //                                                 ENVELOPE_MAX_VOLUME)); // max -> sustain level
            //    adsr_envelope.Reset(regs.adsr.decay_rate_shr2 << 2, true, true);
            //    break;
            //
            //case ADSRPhase::Sustain:
            //    adsr_target = 0;
            //    adsr_envelope.Reset(regs.adsr.sustain_rate, regs.adsr.sustain_direction_decrease, regs.adsr.sustain_exponential);
            //    break;
            //
            //case ADSRPhase::Release:
            //    adsr_target = 0;
            //    adsr_envelope.Reset(regs.adsr.release_rate_shr2 << 2, true, regs.adsr.release_exponential);
        }

        if (playCount == 0)
        {
            releaseVoice(voice);
        }
    }
    //std::cout << vCount << std::endl;

    alcProcessContext(ctx);
}

Voice* Sequencer::obtainVoice()
{
    //if (activeVoice >= 32)
    //{
    //    return NULL;
    //}
    for (int i = 0; i < sourceCount; i++)
    {
        if (!voices[i])
        {
            //activeVoice++;
            Voice* v = new Voice();
            v->uuid = nextUuid();
            voices[i] = v;
            return v;
        }
    }
    return NULL;
}

void Sequencer::releaseVoice(Voice* v)
{
    if (!v)
    {
        return;
    }

    for (int i = 0; i < sourceCount; i++)
    {
        if (v == voices[i])
        {
            //activeVoice--;
            delete v;
            voices[i] = NULL;
            return;
        }
    }
}

s16 Sequencer::obtainSource()
{
    //if (activeSource >= 32)
    //{
    //    return -1;
    //}
    for (s16 i = 0; i < sourceCount; i++)
    {
        if (!sourceLock[i])
        {
            //activeSource++;
            sourceLock[i] = true;
            return i;
        }
    }
    return -1;
}

void Sequencer::releaseSource(s16 id)
{
    if (!sourceLock[id])
    {
        return;
    }
    //activeSource--;

    sourceLock[id] = false;
    alSourceStop(source[id]);
    alSourcei(source[id], AL_BUFFER, NULL);
}

s32 Sequencer::nextUuid()
{
    uuid++;
    if (uuid % 50000)
    {
        uuid = 1;
    }
    return uuid;
}

//////////////////////////
// PUBLIC
Patch* Sequencer::createPatch(s16 id)
{
    if (patches[id])
    {
        return patches[id];
    }

    patches[id] = new Patch();
    return patches[id];
}

Sequence* Sequencer::createSequence()
{
    Sequence* seq = new Sequence();
    sequences.push_back(seq);
    return seq;
}

Sequence* Sequencer::getSequence(s32 id)
{
    for (Sequence* seq : sequences)
    {
        if (seq->id == id)
        {
            return seq;
        }
    }
    return NULL;
}

s32 Sequencer::playNote(s32 patchId, u8 note, float velocity, float pan, u8 pitch, s32 pitchMin, s32 pitchMax)
{    
    Patch* patch = patches[patchId];
    if (!patch)
    {
        return 0;
    }

    Voice* v = obtainVoice();
    if (!v)
    {
        return 0;
    }

    v->patch = patch;
    v->note = note;
    v->velocity = velocity;
    v->pan = pan;
    v->pitch = pitch;
    v->pitchMin = pitchMin;
    v->pitchMax = pitchMax;
    return v->uuid;
}


//////////////////////////
// OTHERS
MIDIMessage* Sequence::createMIDIMessage()
{
    MIDIMessage* msg = new MIDIMessage();
    messages.push_back(msg);
    return msg;
}

MIDIMessage* Sequence::next(u64 now)
{
    if (messages.size() <= 0)
    {
        return NULL;
    }

    if (actionPos == 0)
    {
        // the track is just starting if we are at pos 0
        trackStartTime = now;
    }

    u64 runtimeUs = std::max((u64) 0, now - trackStartTime) * 1000; // x1000 to conver to microseconds
    float midiTickUs = tempoUs / ticksPerBeat;
    u64 trackTick = u64(runtimeUs / midiTickUs);

    MIDIMessage* msg = messages.at(actionPos);
    if (msg->tick <= trackTick)
    {
        actionPos++;
        if (actionPos == messages.size())
        {
            actionPos = 0;
            repeats++; // we've looped the sequence
        }
        return msg;
    }
    return NULL;
}

u64 Patch::getAdsrReleaseTime(u8 note)
{
    u64 max = 0;
    for (Sample* sample : samples)
    {
        if (note >= sample->minNote && note <= sample->maxNote)
        {
            max = std::max(max, (u64) sample->attack);
        }
    }
    return max;
}


//////////////////////////
// OPENAL BS
ALuint PREPARE_REVERB(const EFXEAXREVERBPROPERTIES* reverb)
{
    ALuint effect = 0;
    ALenum err;

    /* Create the effect object and check if we can do EAX reverb. */
    alGenEffects(1, &effect);
    if (alGetEnumValue("AL_EFFECT_EAXREVERB") != 0)
    {
        printf("Using EAX Reverb\n");

        /* EAX Reverb is available. Set the EAX effect type then load the
         * reverb properties. */
        alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
        alEffectf(effect, AL_EAXREVERB_DENSITY, reverb->flDensity);
        alEffectf(effect, AL_EAXREVERB_DIFFUSION, reverb->flDiffusion);
        alEffectf(effect, AL_EAXREVERB_GAIN, reverb->flGain);
        alEffectf(effect, AL_EAXREVERB_GAINHF, reverb->flGainHF);
        alEffectf(effect, AL_EAXREVERB_GAINLF, reverb->flGainLF);
        alEffectf(effect, AL_EAXREVERB_DECAY_TIME, reverb->flDecayTime);
        alEffectf(effect, AL_EAXREVERB_DECAY_HFRATIO, reverb->flDecayHFRatio);
        alEffectf(effect, AL_EAXREVERB_DECAY_LFRATIO, reverb->flDecayLFRatio);
        alEffectf(effect, AL_EAXREVERB_REFLECTIONS_GAIN, reverb->flReflectionsGain);
        alEffectf(effect, AL_EAXREVERB_REFLECTIONS_DELAY, reverb->flReflectionsDelay);
        alEffectfv(effect, AL_EAXREVERB_REFLECTIONS_PAN, reverb->flReflectionsPan);
        alEffectf(effect, AL_EAXREVERB_LATE_REVERB_GAIN, reverb->flLateReverbGain);
        alEffectf(effect, AL_EAXREVERB_LATE_REVERB_DELAY, reverb->flLateReverbDelay);
        alEffectfv(effect, AL_EAXREVERB_LATE_REVERB_PAN, reverb->flLateReverbPan);
        alEffectf(effect, AL_EAXREVERB_ECHO_TIME, reverb->flEchoTime);
        alEffectf(effect, AL_EAXREVERB_ECHO_DEPTH, reverb->flEchoDepth);
        alEffectf(effect, AL_EAXREVERB_MODULATION_TIME, reverb->flModulationTime);
        alEffectf(effect, AL_EAXREVERB_MODULATION_DEPTH, reverb->flModulationDepth);
        alEffectf(effect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, reverb->flAirAbsorptionGainHF);
        alEffectf(effect, AL_EAXREVERB_HFREFERENCE, reverb->flHFReference);
        alEffectf(effect, AL_EAXREVERB_LFREFERENCE, reverb->flLFReference);
        alEffectf(effect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, reverb->flRoomRolloffFactor);
        alEffecti(effect, AL_EAXREVERB_DECAY_HFLIMIT, reverb->iDecayHFLimit);
    }
    else
    {
        printf("Using Standard Reverb\n");

        /* No EAX Reverb. Set the standard reverb effect type then load the
         * available reverb properties. */
        alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);

        alEffectf(effect, AL_REVERB_DENSITY, reverb->flDensity);
        alEffectf(effect, AL_REVERB_DIFFUSION, reverb->flDiffusion);
        alEffectf(effect, AL_REVERB_GAIN, reverb->flGain);
        alEffectf(effect, AL_REVERB_GAINHF, reverb->flGainHF);
        alEffectf(effect, AL_REVERB_DECAY_TIME, reverb->flDecayTime);
        alEffectf(effect, AL_REVERB_DECAY_HFRATIO, reverb->flDecayHFRatio);
        alEffectf(effect, AL_REVERB_REFLECTIONS_GAIN, reverb->flReflectionsGain);
        alEffectf(effect, AL_REVERB_REFLECTIONS_DELAY, reverb->flReflectionsDelay);
        alEffectf(effect, AL_REVERB_LATE_REVERB_GAIN, reverb->flLateReverbGain);
        alEffectf(effect, AL_REVERB_LATE_REVERB_DELAY, reverb->flLateReverbDelay);
        alEffectf(effect, AL_REVERB_AIR_ABSORPTION_GAINHF, reverb->flAirAbsorptionGainHF);
        alEffectf(effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, reverb->flRoomRolloffFactor);
        alEffecti(effect, AL_REVERB_DECAY_HFLIMIT, reverb->iDecayHFLimit);
    }

    /* Check if an error occured, and clean up if so. */
    err = alGetError();
    if (err != AL_NO_ERROR)
    {
        fprintf(stderr, "OpenAL error: %s\n", alGetString(err));
        if (alIsEffect(effect))
            alDeleteEffects(1, &effect);
        return 0;
    }

    return effect;
}

void LOAD_EFFECT_FUNCTIONS()
{
#if __STDC_VERSION__ >= 199901L
    #define FUNCTION_CAST(T, ptr) (union        \
                                   {            \
                                       void* p; \
                                       T f;     \
                                   }){ptr}      \
                                      .f
#elif defined(__cplusplus)
    #define FUNCTION_CAST(T, ptr) reinterpret_cast<T>(ptr)
#else
    #define FUNCTION_CAST(T, ptr) (T)(ptr)
#endif

#define LOAD_PROC(T, x) ((x) = FUNCTION_CAST(T, alGetProcAddress(#x)))
    LOAD_PROC(LPALGENEFFECTS, alGenEffects);
    LOAD_PROC(LPALDELETEEFFECTS, alDeleteEffects);
    LOAD_PROC(LPALISEFFECT, alIsEffect);
    LOAD_PROC(LPALEFFECTI, alEffecti);
    LOAD_PROC(LPALEFFECTIV, alEffectiv);
    LOAD_PROC(LPALEFFECTF, alEffectf);
    LOAD_PROC(LPALEFFECTFV, alEffectfv);
    LOAD_PROC(LPALGETEFFECTI, alGetEffecti);
    LOAD_PROC(LPALGETEFFECTIV, alGetEffectiv);
    LOAD_PROC(LPALGETEFFECTF, alGetEffectf);
    LOAD_PROC(LPALGETEFFECTFV, alGetEffectfv);

    LOAD_PROC(LPALFILTERF, alFilterf);
    LOAD_PROC(LPALFILTERI, alFilteri);

    LOAD_PROC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
    LOAD_PROC(LPALDELETEAUXILIARYEFFECTSLOTS, alDeleteAuxiliaryEffectSlots);
    LOAD_PROC(LPALISAUXILIARYEFFECTSLOT, alIsAuxiliaryEffectSlot);
    LOAD_PROC(LPALAUXILIARYEFFECTSLOTI, alAuxiliaryEffectSloti);
    LOAD_PROC(LPALAUXILIARYEFFECTSLOTIV, alAuxiliaryEffectSlotiv);
    LOAD_PROC(LPALAUXILIARYEFFECTSLOTF, alAuxiliaryEffectSlotf);
    LOAD_PROC(LPALAUXILIARYEFFECTSLOTFV, alAuxiliaryEffectSlotfv);
    LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti);
    LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTIV, alGetAuxiliaryEffectSlotiv);
    LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTF, alGetAuxiliaryEffectSlotf);
    LOAD_PROC(LPALGETAUXILIARYEFFECTSLOTFV, alGetAuxiliaryEffectSlotfv);
#undef LOAD_PROC
}

} // namespace