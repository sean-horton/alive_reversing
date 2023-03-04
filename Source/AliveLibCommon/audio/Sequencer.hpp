#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/efx.h"
#include "AL/efx-presets.h"
#include "BitField.hpp"

namespace sean {

struct ASDR
{
    // adsr1
    u32 sustainLevel;
    u32 decayRate;
    u32 attackRate;
    u32 attackExponential;

    // adsr2
    u32 releaseRate;
    u32 releaseExponential;
    u32 sustainRate;
    u32 sustainDirection;
    u32 sustainExponential;
} typedef ADSR;
ADSR parseADSR(u16 adsr1, u16 adsr2);


/*
* Defines an audio sample. This contains raw audio data and its information
*/
class Sample
{
public:
    Sample(ALvoid* buffer, ALsizei size)
    {
        buf = buffer;
        bufSize = size;
        alGenBuffers(1, &alBuffer);
        alBufferData(alBuffer, AL_FORMAT_MONO16, buffer, size, 22050); // TODO - are sample rates different?
    }
    ~Sample()
    {
        alDeleteBuffers(1, &alBuffer);
    }

    float volume;
    float pan;

    // reverb style - 0 is none
    s8 reverb;

    // Root Key
    u8 rootNote;
    u8 rootNotePitchShift;

    // Key range
    u8 minNote;
    u8 maxNote;

    ADSR adsr;

    // ADSR time in seconds
    double attack;
    double release;
    double decay;
    double sustain; // is this actually level?

    bool releaseExponential = false;
    double sustainLevel;

    ALvoid* buf;
    ALsizei bufSize;
    ALuint alBuffer;
};


/*
* A patch is an instrument, think of a piano/keyboard. A piano may be configured
* to play drums on lower keys and guitar on upper keys. The instrument
* defines which sample(s) to play when a note is pressed.
*/
class Patch
{
public:
    Patch()
    {
        for (int i = 0; i < 128; i++)
        {
            samples[i] = NULL;
        }
    }
    ~Patch()
    {
        for (Sample* sample : samples)
        {
            delete sample;
        }
    }

    Sample* samples[128];

    u64 getAdsrReleaseTime(u8 note);
};


enum MIDIMessageType
{
    NOTE_ON,
    NOTE_OFF,
    PATCH_CHANGE,
    END_TRACK
};


/*
* Defines what to do in a MIDI sequence (play note, stop note, etc)
*/
class MIDIMessage
{
public:
    MIDIMessageType type;
    u32 tick;
    u8 channelId = 0;
    u8 patchId = 0;
    u8 note = 0;
    u8 velocity = 0;
};


struct Channel
{   
    // channels may have volums and pans too
    Patch* patch;
};

/*
* A MIDI sequence (a song). Contains information on the tones (Notes/percussion)
* in the song.
*/
class Sequence
{
public:
    Sequence()
    {
        for (int i = 0; i < 16; i++)
        {
            channels[i] = new Channel();
        }
    }
    ~Sequence()
    {
        for (int i = 0; i < 16; i++)
        {
            delete channels[i];
        }
        for (auto msg : messages)
        {
            delete msg;
        }
    }

    s32 id;
    s32 repeatLimit = 1;
    bool play = false;

    float volume = 1;
    float pan = 0;
    float tempoUs; // BPM - defined in in microseconds (us)
    float ticksPerBeat;

    s32 repeats = 0;

    MIDIMessage* createMIDIMessage();
    MIDIMessage* next(u64 now);
    Channel* channels[16];

private:
    std::vector<MIDIMessage*> messages;


private:
    u32 actionPos = 0;
    u64 trackStartTime = 0;
};

enum AttackPhase
{
    NONE,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
};

class Voice
{
public:
    s32 uuid;
    Sequence* sequence = NULL;
    Patch* patch;
    u8 note;
    u8 pitch;
    s32 pitchMin = 0;
    s32 pitchMax = 127;
    float velocity = 1.0f;
    float pan = 0.0f;
    float noteVolume = 1.0f;

    bool loop = false;
    u64 onTime = 0;   // when the note was pressed
    u64 offTime = 0;  // when the note was released
    bool forceStopNow = false;
    u64 lastProcessedTick = 0;
    u64 lastProcessedMs = 0;

    AttackPhase phase = NONE;
    s32 counter = 0; // decremented each midi tick
    u8 rate;
    bool decreasing;
    bool exponential;

    std::vector<s16> sources;
    std::vector<Sample*> samples;
};

/*
* Can play MIDI
*/
class Sequencer
{
public:
    Sequencer();
    ~Sequencer();

    void reset();

    Patch* createPatch(s16 id);

    Sequence* createSequence();
    Sequence* getSequence(s32 id);

    s32 playNote(s32 patchId, u8 note, float velocity, float pan, u8 pitch, s32 pitchMin, s32 pitchMax);

    void playSeq(s32 seqId);
    void stopSeq(s32 seqId);

    void tick();

private:

    s32 uuid = 1;
    s32 nextUuid();
    
    Voice* obtainVoice();
    void releaseVoice(Voice* v);

    s16 obtainSource();
    void releaseSource(s16 id);

    ALCdevice* device;
    ALCcontext* ctx;

    std::vector<Sequence*> sequences;

    static const int sourceCount = 128;
    //int activeSource = 0;
    //int activeVoice = 0;
    Voice* voices[sourceCount];
    bool sourceLock[sourceCount];
    ALuint source[sourceCount];
    Patch* patches[sourceCount];

    ALuint efxReverb0;
    ALuint efxSlot0;
};


/*
* BELOW IS ALL OPENAL EFFECTS LOADING
* Not sure where else to put this...
*/
/* Define a macro to help load the function pointers. 
    https://github.com/kcat/openal-soft/blob/master/examples/alreverb.c */
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

ALuint PREPARE_REVERB(const EFXEAXREVERBPROPERTIES* reverb);
void LOAD_EFFECT_FUNCTIONS();

} // namespace