#include "stdafx.h"
#include "SoundSDL.hpp"
#include "SDLSoundBuffer.hpp"
#include "SDLSoundSystem.hpp"

#if USE_SDL2_SOUND

bool gReverbEnabled = false;
bool gAudioStereo = true;

void SND_InitVolumeTable_SDL()
{
    for (int i = 0; i < 127; i++)
    {
        sVolumeTable_BBBD38[i] = i;
    }
    sVolumeTable_BBBD38[0] = 0;
}

int SND_Clear_SDL(SoundEntry* pSoundEntry, u32 sampleOffset, u32 size)
{
    const DWORD alignedOffset = sampleOffset * pSoundEntry->field_1D_blockAlign;
    const DWORD alignedSize = size * pSoundEntry->field_1D_blockAlign;

    // TODO: Should only clear from offset to size ??
    memset(pSoundEntry->field_4_pDSoundBuffer->GetBuffer()->data(), 0, pSoundEntry->field_14_buffer_size_bytes);

    return 0;
}

s32 SND_LoadSamples_SDL(const SoundEntry* pSnd, DWORD sampleOffset, u8* pSoundBuffer, u32 sampleCount)
{
    const int offsetBytes = sampleOffset * pSnd->field_1D_blockAlign;
    const u32 bufferSizeBytes = sampleCount * pSnd->field_1D_blockAlign;
    memcpy(reinterpret_cast<Uint8*>(pSnd->field_4_pDSoundBuffer->GetBuffer()->data()) + offsetBytes, pSoundBuffer, bufferSizeBytes);
    return 0;
}

s32 SND_CreateDS_SDL(u32 sampleRate, int bitsPerSample, int isStereo)
{
    sDSound_BBC344 = new SDLSoundSystem();
    sDSound_BBC344->Init(sampleRate, bitsPerSample, isStereo);
    return 0;
}

const char* SND_HR_Err_To_String_SDL(long)
{
    return "unknown error";
}

#endif
