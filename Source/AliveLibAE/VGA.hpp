#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/bmp.hpp"

void VGA_Shutdown_4F3170();
void VGA_CopyToFront(RECT* pRect);
bool VGA_IsWindowMode_4F31E0();
s32 VGA_FullScreenSet_4F31F0(bool bFullScreen);
s32 VGA_DisplaySet_4F32C0(u16 width, u16 height, u8 bpp, u8 backbufferCount, TSurfaceType** ppSurface);

extern Bitmap sVGA_bmp_primary_BD2A20;