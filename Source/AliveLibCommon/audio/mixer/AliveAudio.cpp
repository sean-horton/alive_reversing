#pragma once

#include <chrono>
#include "AliveAudio.hpp"


#include "AL/alc.h"
#include "AL/al.h"
#include "AL/alext.h"
#include "AL/efx.h"
#include "AL/efx-presets.h"

/* Effect object functions */
static LPALGENEFFECTS alGenEffects;
static LPALDELETEEFFECTS alDeleteEffects;
static LPALISEFFECT alIsEffect;
static LPALEFFECTI alEffecti;
static LPALEFFECTIV alEffectiv;
static LPALEFFECTF alEffectf;
static LPALEFFECTFV alEffectfv;
static LPALGETEFFECTI alGetEffecti;
static LPALGETEFFECTIV alGetEffectiv;
static LPALGETEFFECTF alGetEffectf;
static LPALGETEFFECTFV alGetEffectfv;
static LPALFILTERF alFilterf;
static LPALFILTERI alFilteri;

/* Auxiliary Effect Slot object functions */
static LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
static LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
static LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
static LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
static LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
static LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
static LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
static LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
static LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
static LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
static LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;

namespace psx {

Soundbank* AliveAudio::m_CurrentSoundbank = nullptr;
std::mutex AliveAudio::voiceListMutex;
std::vector<Voice*> AliveAudio::m_Voices;
long long AliveAudio::currentSampleIndex = 20;
biquad* AliveAudio::AliveAudioEQBiQuad = nullptr;

ALCdevice* device;
ALCcontext* ctx;
ALuint effectG;
ALuint slot = 0;
unsigned int alSource[64];
ALenum error;
unsigned int alSampleSet[64];
Sample* sampleId[64];

ALuint LoadEffect(const EFXEAXREVERBPROPERTIES* reverb)
{
    ALuint effect = 0;
    ALenum err;

    /* Create the effect object and check if we can do EAX reverb. */
    alGenEffects(1, &effect);
    //alFilteri(effect, AL_FILTER_TYPE, AL_FILTER_LOWPASS);

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

void AliveInitAudio()
{
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec waveSpec;
    waveSpec.callback = AliveAudioSDLCallback;
    waveSpec.userdata = nullptr;
    waveSpec.channels = 2;
    waveSpec.freq = AliveAudioSampleRate;
    waveSpec.samples = 512;
    waveSpec.format = AUDIO_F32;

    /* Open the audio device */
    if (SDL_OpenAudio(&waveSpec, NULL) < 0)
    {
        fprintf(stderr, "Failed to initialize audio: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_PauseAudio(0);

    
    device = alcOpenDevice(NULL);
    ctx = alcCreateContext(device, NULL);
    alcMakeContextCurrent(ctx);

    /* Define a macro to help load the function pointers. 
    https://github.com/kcat/openal-soft/blob/master/examples/alreverb.c */
 
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

    //EFXEAXREVERBPROPERTIES reverb = EFX_REVERB_PRESET_FACTORY_MEDIUMROOM;
    EFXEAXREVERBPROPERTIES reverb = EFX_REVERB_PRESET_AUDITORIUM;

    effectG = LoadEffect(&reverb);
    alGenAuxiliaryEffectSlots(1, &slot);
    alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, (ALint) effectG);


    alGenBuffers(64, alSampleSet);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        return;
    }

    alGenSources(64, alSource);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        return;
    }
}

int getSource()
{
    ALenum state;
    int i;
    for (i = 0; i < 64; i++)
    {
        alGetSourcei(alSource[i], AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING)
        {
            alSourceStop(alSource[i]);
            return i;
        }
    }
    return -1;
}

void AliveAudio::PlayOneShot(s32 playId, int programId, int note, s32 volLeft, s32 volRight, float pitch, s32 pitch_min, s32 pitch_max)
{
    for (auto program : m_CurrentSoundbank->m_Programs)
    {
        if (program->prog_id != programId)
        {
            continue;
        }

        pitch;
        pitch_min;
        pitch_max;
        for (auto tone : program->m_Tones)
        {
            if (note >= tone->Min && note <= tone->Max)
            {
                Voice* voice = new Voice();
                voice->i_TrackID = playId;
                voice->i_Note = note;
                voice->f_Velocity = float(std::min(volLeft, volRight)) / 127;
                voice->m_Tone = tone;
                voice->f_Pan = (float(volRight) / float(volLeft)) - 1;

                // TODO - something more is probably suppose to happen with pitch.
                // From the looks of things pitch_min and pitch_max are always equal.
                // and if pitch is 0, try using pitch_min instead.
                voice->f_Pitch = pitch == 0 ? pitch_min / 127 : pitch / 127;
                //m_Voices.push_back(voice);

                alGetError(); // clear error code
                Sample* s = voice->m_Tone->m_Sample;
                
                int i = 0;
                int pos = -1;
                for (i = 0; i < 64; ++i)
                {
                    if (sampleId[i] == s || !sampleId[i])
                    {
                        pos = i;
                    }
                }

                int a = getSource();
                if (a == -1)
                {
                    return;
                }

                if (!sampleId[pos])
                {
                    alBufferData(alSampleSet[pos], AL_FORMAT_MONO16, s->m_SampleBuffer, s->i_SampleSize * 2, 22050);
                    if ((error = alGetError()) != AL_NO_ERROR)
                    {
                        return;
                    }
                    sampleId[pos] = s;
                }

                //float center = float(tone->c_Center);
                //float pitch1 = float(tone->Pitch);
                //float shift = float(tone->c_Shift);
                //float min = tone->Min;
                //float max = tone->Max;
                float freq = float(pow(1.059463094359, (f64) (note - tone->c_Shift) * 0.00390625));

                freq = (float(note) / float(tone->c_Shift));
                freq = tone->c_Shift == 0 ? 1 : freq;
                freq = (note / float(tone->c_Shift / 256.0));
                freq = tone->c_Shift == 0 ? 1 : freq;


                float noteFreq = float(pow(2.0, float(note) / 12.0));
                float sampleRootFreq = float(pow(2.0, float(tone->c_Center + (tone->c_Shift / 127.0)) / 12.0));
                freq = noteFreq / sampleRootFreq * 2.0f;

                ALfloat pan;
                pan = voice->f_Pan;
                alSource3f(alSource[a], AL_POSITION, pan, 0, -sqrtf(1.0f - pan * pan));
                alSourcef(alSource[a], AL_PITCH, (ALfloat) freq);
                alSourcef(alSource[a], AL_GAIN, (ALfloat) voice->f_Velocity);

                alSourcei(alSource[a], AL_BUFFER, alSampleSet[pos]);
                if (tone->mode != 0)
                    alSource3i(alSource[a], AL_AUXILIARY_SEND_FILTER, (ALint) slot, 0, AL_FILTER_NULL);
                else
                    alSource3i(alSource[a], AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, NULL);

                if ((error = alGetError()) != AL_NO_ERROR)
                {
                    return;
                }

                alSourcePlay(alSource[a]);

                //ALfloat adsr = ALfloat(0.1);
                //while (adsr < 2)
                //{
                //    alSourcef(alSource[pos], AL_PITCH, (ALfloat) adsr);
                //    adsr += ALfloat(0.1);
                //    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                //}

                //ALenum state;
                //do
                //{
                //    // al_nssleep(10000000);
                //    alGetSourcei(alSource, AL_SOURCE_STATE, &state);
                //}
                //while (alGetError() == AL_NO_ERROR && state == AL_PLAYING);

                //alDeleteSources(1, &alSource);
                //alDeleteAuxiliaryEffectSlots(1, &slot);
                //alDeleteEffects(1, &effect);
                //alDeleteBuffers(1, alSampleSet);
            }
        }
    }
}

void AliveAudio::PlayOneShot(s32 playId, int programId, int note, s32 volume, float pitch, s32 pitch_min, s32 pitch_max)
{
    AliveAudio::PlayOneShot(playId, programId, note, volume, volume, pitch, pitch_min, pitch_max);
}


void AliveAudio::NoteOn(int programId, int note, char velocity, float pitch , int trackID , float trackDelay, float masterVolMulti)
{
    for (auto program : m_CurrentSoundbank->m_Programs)
    {
        if (program->prog_id != programId)
        {
            continue;
        }
        for (auto tone : program->m_Tones)
        {
            if (note >= tone->Min && note <= tone->Max) // this is funny `if (tone->f_Volume > 0)`
            {
                Voice* voice = new Voice();
                voice->i_Note = note;
                voice->m_Tone = tone;
                voice->i_Program = programId;
                voice->f_Velocity = velocity == 0 ? tone->f_Volume : velocity / 127.0f;
                voice->i_TrackID = trackID;
                voice->f_Pitch = pitch;
                voice->f_TrackDelay = trackDelay;
                //m_Voices.push_back(voice);

                alGetError(); // clear error code
                Sample* s = voice->m_Tone->m_Sample;

                int i = 0;
                int pos = -1;
                for (i = 0; i < 64; ++i)
                {
                    if (sampleId[i] == s || !sampleId[i])
                    {
                        pos = i;
                    }
                }

                int a = getSource();
                if (a == -1)
                {
                    return;
                }

                if (!sampleId[pos])
                {
                    alBufferData(alSampleSet[pos], AL_FORMAT_MONO16, s->m_SampleBuffer, s->i_SampleSize * 2, 22050);
                    if ((error = alGetError()) != AL_NO_ERROR)
                    {
                        return;
                    }
                    sampleId[pos] = s;
                }

                // Centre: This one is the most important. This is the root note, or, the note that your sample is in.
                // If you got your sample from a Sample CD, often it will have what note it is somewhere.
                // If you don't know what note your sample is in, LoopAuditioneer can find it out for you.

                // Pitch: This is the pitch fine-tuning, it might be needed depending on the sample you are using.

                // Note: The VAB tool can't preview pitch fine-tuning if you are not using a dev board.

                // MinNote: The lowest note in which this tone will be played.

                //float center = float(tone->c_Center);
     /*           float pitch1 = float(tone->Pitch);

                float ii = center + (center * pitch1);
                ii;*/
                
                //float shift_cent = float( (tone->c_Shift + (tone->c_Center << 7)));
                float freq = float(pow(1.059463094359, (f64) ((tone->c_Shift / 256.0)) * 0.00390625));
                //freq = (pow(1.059463094359, (f64) ((note / 256.0) - (tone->c_Shift / 256.0)))) * 40;
                //freq = (note / float(tone->c_Shift / 256.0));
                //freq = tone->c_Shift == 0 ? 1 : freq;

                //freq = (float(note) / float(tone->c_Center));
                //freq = (float(note) / float(tone->c_Shift / 256.0));
                //freq = tone->c_Shift == 0 ? 1 : freq;
                freq = float(note) / (float(pow(tone->c_Center, 2) / (pow(tone->c_Shift, 2))));
                freq = float(note) / float(2 * (tone->c_Shift + (tone->c_Center << 7)));

                float noteFreq = float(pow(2.0, float(note) / 12.0));
                float sampleRootFreq = float(pow(2.0, float(tone->c_Center + (tone->c_Shift / 127.0)) / 12.0));
                freq = noteFreq / sampleRootFreq * 2.0f;
                //freq = note / float(float(tone->c_Center) + float(tone->c_Shift / 127.0));
                //freq = note / float(float(tone->c_Center) + float(tone->c_Shift / 127.0));

                //freq = freq + 0.5;
                //freq = float(note) / float(float(tone->c_Center));

                ALfloat pan;
                pan = voice->f_Pan == 0 ? voice->m_Tone->f_Pan : voice->f_Pan;
                alSource3f(alSource[a], AL_POSITION, pan, 0, -sqrtf(1.0f - pan * pan));
                alSourcef(alSource[a], AL_PITCH, (ALfloat) freq);
                alSourcef(alSource[a], AL_GAIN, (ALfloat) voice->f_Velocity * masterVolMulti);
                alSourcei(alSource[a], AL_BUFFER, alSampleSet[pos]);
                if (tone->mode != 0)
                    alSource3i(alSource[a], AL_AUXILIARY_SEND_FILTER, (ALint) slot, 0, AL_FILTER_NULL);
                else
                    alSource3i(alSource[a], AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, NULL);

                if ((error = alGetError()) != AL_NO_ERROR)
                {
                    return;
                }

                alSourcePlay(alSource[a]);
                AliveAudio::currentSampleIndex++;
            }
        }
    }
}
void AliveAudio::NoteOn(int program, int note, char velocity, int trackID , float trackDelay, float masterValMulti)
{
    NoteOn(program, note, velocity, 0, trackID, trackDelay, masterValMulti);
} 

// sets the volume and pan for all voices on a given track.
// since we are probably updating the volume of a sequence 
// we will set a volume multiplier that will be used on the 
// sequences voices volume. 
void AliveAudio::SetVolume(int trackID, s32 volLeft, s32 volRight)
{
    for (auto voice : m_Voices)
    {
        if (voice->i_TrackID == trackID)
        {
            voice->f_VelocityMulti = double(std::min(volLeft, volRight)) / double(127);
            voice->f_Pan = (float(volRight) / float(volLeft)) - 1;
        }
    }
}

void AliveAudio::NoteOff(int program, int note, int trackID )
{
    for (auto voice : m_Voices)
    {
        if (voice->i_Note == note && voice->i_Program == program && voice->i_TrackID == trackID)
        {
            voice->b_NoteOn = false;
        }
    }
}
void AliveAudio::NoteOffDelay(int program, int note, int trackID , float trackDelay)
{
    for (auto voice : m_Voices)
    {
        if (voice->i_Note == note && voice->i_Program == program && voice->i_TrackID == trackID && voice->f_TrackDelay < trackDelay && voice->f_NoteOffDelay <= 0)
        {
            voice->m_UsesNoteOffDelay = true;
            voice->f_NoteOffDelay = trackDelay;
        }
    }
} 
void AliveAudio::DebugPlayFirstToneSample(int program, int tone)
{
    program;
    tone;
} 
void AliveAudio::LockNotes()
{
    voiceListMutex.lock();
}
void AliveAudio::UnlockNotes()
{
    voiceListMutex.unlock();
}

void AliveAudio::ClearAllVoices(bool forceKill)
{
    std::vector<Voice*> deadVoices;

    for (auto voice : AliveAudio::m_Voices)
    {
        if (forceKill)
        {
            deadVoices.push_back(voice);
        }
        else
        {
            voice->b_NoteOn = false;        // Send a note off to all of the notes though.
            if (voice->f_SampleOffset == 0) // Let the voices that are CURRENTLY playing play.
            {
                deadVoices.push_back(voice);
            }
        }
    }

    for (auto obj : deadVoices)
    {
        delete obj;

        AliveAudio::m_Voices.erase(std::remove(AliveAudio::m_Voices.begin(), AliveAudio::m_Voices.end(), obj), AliveAudio::m_Voices.end());
    }
}

void AliveAudio::ClearAllTrackVoices(int trackID, bool forceKill)
{
    std::vector<Voice*> deadVoices;

    for (auto voice : AliveAudio::m_Voices)
    {
        if (forceKill)
        {
            //voice->b_NoteOn = false;    
            //voice->ActiveReleaseLevel = 1;
            if (voice->i_TrackID == trackID) // Kill the voices no matter what. Cuts of any sounds = Ugly sound
            {
                deadVoices.push_back(voice);
            }
        }
        else if (voice->i_TrackID == trackID)
        {
            voice->b_NoteOn = false;        // Send a note off to all of the notes though.
            if (voice->f_SampleOffset == 0) // Let the voices that are CURRENTLY playing play.
            {
                deadVoices.push_back(voice);
            }
        }
    }

    for (auto obj : deadVoices)
    {
        delete obj;
        AliveAudio::m_Voices.erase(std::remove(AliveAudio::m_Voices.begin(), AliveAudio::m_Voices.end(), obj), AliveAudio::m_Voices.end());
    }
}

void CleanVoices()
{
    std::vector<Voice*> deadVoices;

    for (auto voice : AliveAudio::m_Voices)
    {
        if (voice->b_Dead)
        {
            deadVoices.push_back(voice);
        }
    }

    for (auto obj : deadVoices)
    {
        delete obj;

        AliveAudio::m_Voices.erase(std::remove(AliveAudio::m_Voices.begin(), AliveAudio::m_Voices.end(), obj), AliveAudio::m_Voices.end());
    }
}

void AliveRenderAudio(float* AudioStream, int StreamLength)
{
    AudioStream;
    StreamLength;

    static float tick = 0;
    static int note = 0;

    int voiceCount = AliveAudio::m_Voices.size();
    Voice** rawPointer = AliveAudio::m_Voices.data(); // Real nice speed boost here.

    for (int i = 0; i < StreamLength; i += 2)
    {
        for (int v = 0; v < voiceCount; v++)
        {
            Voice* voice = rawPointer[v]; // Raw pointer skips all that vector bottleneck crap

            voice->f_TrackDelay--;

            if (voice->m_UsesNoteOffDelay)
            {
                voice->f_NoteOffDelay--;
            }

            if (voice->m_UsesNoteOffDelay && voice->f_NoteOffDelay <= 0 && voice->b_NoteOn == true)
            {
                voice->b_NoteOn = false;
            }

            if (voice->b_Dead || voice->f_TrackDelay > 0) {
                continue;
            }
            
            float centerPan = voice->f_Pan == 0 ? voice->m_Tone->f_Pan : voice->f_Pan;
            float leftPan = 1.0f;
            float rightPan = 1.0f;

            if (centerPan > 0)
            {
                leftPan = 1.0f - abs(centerPan);
            }
            if (centerPan < 0)
            {
                rightPan = 1.0f - abs(centerPan);
            }
            float s = voice->GetSample();

            float leftSample = s * leftPan;
            float rightSample = s * rightPan;

            SDL_MixAudioFormat((Uint8*) (AudioStream + i), (const Uint8*) &leftSample, AUDIO_F32, sizeof(float), 37);      // Left Channel
            SDL_MixAudioFormat((Uint8*) (AudioStream + i + 1), (const Uint8*) &rightSample, AUDIO_F32, sizeof(float), 37); // Right Channel
        }

        AliveAudio::currentSampleIndex++;
    }

    CleanVoices();
}


void AliveAudioSetEQ(float cutoff)
{
    if (AliveAudio::AliveAudioEQBiQuad != nullptr)
        delete AliveAudio::AliveAudioEQBiQuad;

    AliveAudio::AliveAudioEQBiQuad = BiQuad_new(PEQ, 8, cutoff, AliveAudioSampleRate, 1);
}

void AliveEQEffect(float* stream, int len)
{
    if (AliveAudio::AliveAudioEQBiQuad == nullptr)
    {
        AliveAudioSetEQ(20500);
    }

    for (int i = 0; i < len; i++)
    {
        stream[i] = BiQuad(stream[i], AliveAudio::AliveAudioEQBiQuad);
    }
}

void AliveAudioSDLCallback(void* udata, Uint8* stream, int len)
{
    udata;
    memset(stream, 0, len);

    AliveAudio::LockNotes();
    AliveRenderAudio((float*) stream, len / sizeof(float));

    //if (AliveAudio::EQEnabled)
    AliveEQEffect((float*) stream, len / sizeof(float));

    AliveAudio::UnlockNotes();
}

} // namespace psx