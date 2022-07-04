#include "stdafx.h"
#include "Animation.hpp"
#include "Function.hpp"
#include "Map.hpp"
#include "Compression.hpp"
#include "VRam.hpp"
#include "Game.hpp"
#include "PsxDisplay.hpp"
#include "Abe.hpp"    // For anim call back table
#include "Slig.hpp"   // For slig frame call back
#include "Fleech.hpp" // For fleech frame call back
#include "stdlib.hpp"
#include "Particle.hpp"
#include "Events.hpp"
#include "Slurg.hpp"
#include "Slog.hpp"
#include "Sfx.hpp"
#include "Blood.hpp"
#include "ObjectIds.hpp"
#include "Sys_common.hpp"
#include "Renderer/IRenderer.hpp"
#include <gmock/gmock.h>

// Frame call backs ??
s32 Animation_OnFrame_Common_Null_455F40(BaseGameObject*, s16*)
{
    return 1;
}

s32 Animation_OnFrame_Null_455F60(BaseGameObject*, s16*)
{
    return 1;
}

s32 Animation_OnFrame_Common_4561B0(BaseGameObject* pObjPtr, s16* pData)
{
    auto pObj = static_cast<BaseAliveGameObject*>(pObjPtr);
    const AnimRecord& dustRec = AnimRec(AnimId::Dust_Particle);
    u8** ppAnimData = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, dustRec.mResourceId, FALSE, FALSE);

    FP xOff = {};
    if (pObj->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        xOff = -(pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pData[0]));
    }
    else
    {
        xOff = (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pData[0]));
    }

    FP xpos = xOff + pObj->mBaseAnimatedWithPhysicsGameObject_XPos;
    FP ypos = (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pData[1])) + pObj->mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(25);
    if (!pObj->BaseAliveGameObjectCollisionLine)
    {
        return 1;
    }

    const s8 count = sSlurg_Step_Watch_Points_Count_5BD4DC[sSlurg_Step_Watch_Points_Idx_5C1C08];
    if (count < 5)
    {
        Slurg_Step_Watch_Points* pPoints = &sSlurg_Step_Watch_Points_5C1B28[sSlurg_Step_Watch_Points_Idx_5C1C08];
        pPoints->field_0_points[count].field_0_xPos = FP_GetExponent(xpos);
        pPoints->field_0_points[count].field_2_yPos = pObj->BaseAliveGameObjectCollisionLine->mRect.y - 5;
        sSlurg_Step_Watch_Points_Count_5BD4DC[sSlurg_Step_Watch_Points_Idx_5C1C08] = count + 1;
    }

    if (!IsActiveHero(pObj))
    {
        return 1;
    }

    if (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
    {
        ypos -= FP_FromInteger(14);
    }

    if (pObj->mCurrentMotion == eAbeMotions::Motion_71_Knockback_455090 && pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
    {
        ypos += FP_FromInteger(5);
    }

    if (pObj->mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_44FBA0)
    {
        ypos -= FP_FromInteger(5);
    }

    auto pPartical = relive_new Particle(xpos, ypos, AnimId::Dust_Particle, ppAnimData);
    if (pPartical)
    {
        pPartical->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_1;

        if (pObj->mBaseAnimatedWithPhysicsGameObject_Scale == Scale::Fg)
        {
            pPartical->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_36;
        }
        else
        {
            pPartical->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
        }

        pPartical->mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(45, 35, 5);

        switch (pObj->mCurrentMotion)
        {
            case eAbeMotions::Motion_1_WalkLoop_44FBA0:
                pPartical->mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromDouble(0.3) * pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale;
                break;

            case eAbeMotions::Motion_40_SneakLoop_450550:
                pPartical->mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromInteger(0);
                break;

            case eAbeMotions::Motion_71_Knockback_455090:
                pPartical->mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromInteger(1) * pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale;
                break;

            default:
                pPartical->mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromDouble(0.6) * pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale;
                break;
        }
    }
    return 1;
}

s32 Animation_OnFrame_Common_434130(BaseGameObject* pObjPtr, s16* pData)
{
    auto pObj = static_cast<BaseAliveGameObject*>(pObjPtr);

    if (pObj->Type() == ReliveTypes::eAbe || pObj->Type() == ReliveTypes::eMudokon || pObj->Type() == ReliveTypes::eRingOrLiftMud)
    {
        LOG_ERROR("never expected pObj type id to be abe or mudokon in Animation_OnFrame_Common_434130");
        ALIVE_FATAL("got wrong type id");
    }

    if (pObj->mHealth <= FP_FromInteger(0))
    {
        return 1;
    }

    // flying slig: kVaporResID
    u8** ppAnimRes = pObj->field_10_resources_array.ItemAt(7);
    FP xOff = {};
    if (pObj->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        xOff = -(pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pData[0]));
    }
    else
    {
        xOff = (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pData[0]));
    }

    FP xpos = xOff + pObj->mBaseAnimatedWithPhysicsGameObject_XPos;
    FP ypos = (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * (FP_FromInteger(pData[1]) + FP_FromInteger(25))) + pObj->mBaseAnimatedWithPhysicsGameObject_YPos;

    if (EventGet(kEventDeathReset))
    {
        pObj->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    auto pParticle = relive_new Particle(xpos, ypos, AnimId::Vaporize_Particle, ppAnimRes);
    if (pParticle)
    {
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_1;
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_36;
        pParticle->mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(64, 64, 64);
        pParticle->mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromDouble(0.6) * pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale;
    }
    return 1;
}

s32 Animation_OnFrame_Slog_4C3030(BaseGameObject* pObjPtr, s16* pPoints)
{
    auto pSlog = static_cast<Slog*>(pObjPtr);
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(pSlog->field_118_target_id));
    if (!pTarget)
    {
        return 1;
    }

    if ((pTarget->Type() == ReliveTypes::eAbe && pTarget->mCurrentMotion == eAbeMotions::Motion_68_ToOffScreenHoist_454B80) || pSlog->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted))
    {
        return 1;
    }

    const PSX_RECT bTargetRect = pTarget->VGetBoundingRect();
    const PSX_RECT bSlogRect = pSlog->VGetBoundingRect();

    if (bSlogRect.x > bTargetRect.w || bSlogRect.w < bTargetRect.x || bSlogRect.h < bTargetRect.y || bSlogRect.y > bTargetRect.h || pTarget->mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromInteger(1) || pSlog->field_11C_biting_target)
    {
        return 1;
    }

    if (!pTarget->VTakeDamage(pSlog))
    {
        return 1;
    }

    FP bloodX = {};
    if (pSlog->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        bloodX = pSlog->mBaseAnimatedWithPhysicsGameObject_XPos - (pSlog->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pPoints[0]));
    }
    else
    {
        bloodX = (pSlog->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pPoints[0])) + pSlog->mBaseAnimatedWithPhysicsGameObject_XPos;
    }

    const FP bloodY = (pSlog->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(pPoints[1])) + pSlog->mBaseAnimatedWithPhysicsGameObject_YPos;

    relive_new Blood(
        bloodX,
        bloodY - FP_FromInteger(8),
        pSlog->mBaseAnimatedWithPhysicsGameObject_VelX * FP_FromInteger(2),
        FP_FromInteger(0),
        pSlog->mBaseAnimatedWithPhysicsGameObject_SpriteScale,
        50);

    pSlog->field_11C_biting_target = 1;
    SfxPlayMono(SoundEffect::SlogBite_34, 0);

    return 1;
}

// TODO: Array is possibly bigger, called by AnimationEx::Invoke_CallBacks
TFrameCallBackType kAbe_Anim_Frame_Fns_55EF98[5] = {
    Animation_OnFrame_Common_Null_455F40,
    Animation_OnFrame_Null_455F60,
    Animation_OnFrame_Abe_455F80,
    Animation_OnFrame_Common_4561B0,
    Animation_OnFrame_Common_434130};

TFrameCallBackType kSlig_Anim_Frame_Fns_55EFAC[4] = {
    Animation_OnFrame_Common_Null_455F40,
    Animation_OnFrame_Null_455F60,
    Animation_OnFrame_Slig_4C0600,
    Animation_OnFrame_Common_4561B0};

TFrameCallBackType kSlog_Anim_Frame_Fns_55EFBC[2] = {
    Animation_OnFrame_Slog_4C3030,
    Animation_OnFrame_Null_455F60};

TFrameCallBackType kFlyingSlig_Anim_Frames_Fns_55EFC4[3] = {
    Animation_OnFrame_Common_Null_455F40,
    Animation_OnFrame_Null_455F60,
    Animation_OnFrame_Common_434130};

TFrameCallBackType kFleech_Anim_Frame_Fns_55EFD0[3] = {
    Animation_OnFrame_Common_Null_455F40,
    Animation_OnFrame_Null_455F60,
    Animation_OnFrame_Fleech_449A60};

// ================================================================
static IRenderer::BitDepth AnimFlagsToBitDepth(const BitField32<AnimFlags>& flags)
{
    if (flags.Get(AnimFlags::eBit14_Is16Bit))
    {
        return IRenderer::BitDepth::e16Bit;
    }
    else if (flags.Get(AnimFlags::eBit13_Is8Bit))
    {
        return IRenderer::BitDepth::e8Bit;
    }
    return IRenderer::BitDepth::e4Bit;
}

void Animation::UploadTexture(const FrameHeader* pFrameHeader, const PSX_RECT& vram_rect, s16 width_bpp_adjusted)
{
    IRenderer& renderer = *IRenderer::GetRenderer();
    switch (pFrameHeader->field_7_compression_type)
    {
        case CompressionType::eType_0_NoCompression:
            // No compression, load the data directly into frame buffer
            mAnimFlags.Set(AnimFlags::eBit25_bDecompressDone);
            renderer.Upload(AnimFlagsToBitDepth(mAnimFlags), vram_rect, reinterpret_cast<const u8*>(&pFrameHeader->field_8_width2)); // TODO: Refactor structure to get pixel data
            break;

        case CompressionType::eType_1_NotUsed:
            // This isn't in any of the animation data files on disk, therefore can't ever be used.
            ALIVE_FATAL("Compression type 1 never expected to be used.");
            break;

        case CompressionType::eType_2_ThreeToFourBytes:
            mAnimFlags.Set(AnimFlags::eBit25_bDecompressDone);
            if (EnsureDecompressionBuffer())
            {
                // TODO: Refactor structure to get pixel data.
                CompressionType2_Decompress_40AA50(
                    reinterpret_cast<const u8*>(&pFrameHeader[1]),
                    *mDbuf,
                    width_bpp_adjusted * pFrameHeader->field_5_height * 2);

                renderer.Upload(AnimFlagsToBitDepth(mAnimFlags), vram_rect, *mDbuf);
            }
            break;

        case CompressionType::eType_3_RLE_Blocks:
            if (mAnimFlags.Get(AnimFlags::eBit25_bDecompressDone))
            {
                if (EnsureDecompressionBuffer())
                {
                    // TODO: Refactor structure to get pixel data.
                    CompressionType_3Ae_Decompress_40A6A0(reinterpret_cast<const u8*>(&pFrameHeader->field_8_width2), *mDbuf);

                    renderer.Upload(AnimFlagsToBitDepth(mAnimFlags), vram_rect, *mDbuf);
                }
            }
            break;

        case CompressionType::eType_4_RLE:
        case CompressionType::eType_5_RLE:
            if (EnsureDecompressionBuffer())
            {
                // TODO: Refactor structure to get pixel data.
                CompressionType_4Or5_Decompress_4ABAB0(reinterpret_cast<const u8*>(&pFrameHeader->field_8_width2), *mDbuf);
                renderer.Upload(AnimFlagsToBitDepth(mAnimFlags), vram_rect, *mDbuf);
            }
            break;

        case CompressionType::eType_6_RLE:
            if (mAnimFlags.Get(AnimFlags::eBit25_bDecompressDone))
            {
                if (EnsureDecompressionBuffer())
                {
                    // TODO: Refactor structure to get pixel data.
                    CompressionType6Ae_Decompress_40A8A0(reinterpret_cast<const u8*>(&pFrameHeader->field_8_width2), *mDbuf);
                    renderer.Upload(AnimFlagsToBitDepth(mAnimFlags), vram_rect, *mDbuf);
                }
            }
            break;

        case CompressionType::eType_7_NotUsed:
        case CompressionType::eType_8_NotUsed:
            ALIVE_FATAL("Decompression 7 and 8 never expected to be used");
            break;
    }
}

bool Animation::EnsureDecompressionBuffer()
{
    if (!mDbuf)
    {
        mDbuf = ResourceManager::Alloc_New_Resource_49BED0(ResourceManager::Resource_DecompressionBuffer, 0, mDbufSize);
    }
    return mDbuf != nullptr;
}

void Animation::DecompressFrame()
{
    if (mAnimFlags.Get(AnimFlags::eBit11_bToggle_Bit10))
    {
        mAnimFlags.Toggle(AnimFlags::eBit10_alternating_flag);
    }

    const FrameInfoHeader* pFrameInfoHeader = Get_FrameHeader(-1); // -1 = use current frame
    if (pFrameInfoHeader->field_6_count > 0)
    {
        Invoke_CallBacks();
    }

    const FrameHeader* pFrameHeader = reinterpret_cast<const FrameHeader*>(&(*field_20_ppBlock)[pFrameInfoHeader->field_0_frame_header_offset]);

    // No VRAM allocation
    if (mVramRect.w <= 0)
    {
        return;
    }

    s16 width_bpp_adjusted = 0;
    if (mAnimFlags.Get(AnimFlags::eBit13_Is8Bit))
    {
        // 8 bit, divided by half
        width_bpp_adjusted = ((pFrameHeader->field_4_width + 3) / 2) & ~1;
    }
    else if (mAnimFlags.Get(AnimFlags::eBit14_Is16Bit))
    {
        // 16 bit, only multiple of 2 rounding
        width_bpp_adjusted = (pFrameHeader->field_4_width + 1) & ~1;
    }
    else
    {
        // 4 bit divide by quarter
        width_bpp_adjusted = ((pFrameHeader->field_4_width + 7) / 4) & ~1;
    }

    PSX_RECT vram_rect = {
        mVramRect.x,
        mVramRect.y,
        width_bpp_adjusted,
        pFrameHeader->field_5_height,
    };

    // Clamp width
    if (vram_rect.w > mVramRect.w)
    {
        vram_rect.w = mVramRect.w;
    }

    // Clamp height
    if (pFrameHeader->field_5_height > mVramRect.h)
    {
        vram_rect.h = mVramRect.h;
    }

    UploadTexture(pFrameHeader, vram_rect, width_bpp_adjusted);
}

void Animation::VRender(s32 xpos, s32 ypos, PrimHeader** ppOt, s16 width, s32 height)
{
    if ((mVramRect.x || mVramRect.y) && !(mAnimFlags.Get(AnimFlags::eBit25_bDecompressDone)))
    {
        Vram_free({mVramRect.x, mVramRect.y}, {mVramRect.w, mVramRect.h});
        mVramRect.x = 0;
        mVramRect.y = 0;
    }

    const s16 xpos_pc = static_cast<s16>(PsxToPCX(xpos));
    const s16 width_pc = static_cast<s16>(PsxToPCX(width));

    if (!mAnimFlags.Get(AnimFlags::eBit3_Render))
    {
        return;
    }

    if (!field_20_ppBlock)
    {
        return;
    }


    const FrameInfoHeader* pFrameInfoHeader = Get_FrameHeader(-1);
    const FrameHeader* pFrameHeader = (const FrameHeader*) &(*field_20_ppBlock)[pFrameInfoHeader->field_0_frame_header_offset];

    FP scaled_width = {};
    FP scaled_height = {};
    if (width_pc)
    {
        scaled_width = FP_FromInteger(width_pc);
        scaled_height = FP_FromInteger(height);
    }
    else
    {
        scaled_width = FP_FromInteger(pFrameHeader->field_4_width);
        scaled_height = FP_FromInteger(pFrameHeader->field_5_height);
    }

    FP xOffSet_scaled = {};
    FP yOffset_scaled = {};
    if (mAnimFlags.Get(AnimFlags::eBit20_use_xy_offset))
    {
        xOffSet_scaled = FP_FromInteger(0);
        yOffset_scaled = FP_FromInteger(0);
    }
    else
    {
        xOffSet_scaled = FP_FromInteger(pFrameInfoHeader->field_8_data.offsetAndRect.mOffset.x);
        yOffset_scaled = FP_FromInteger(pFrameInfoHeader->field_8_data.offsetAndRect.mOffset.y);
    }

    TPageMode textureMode = {};
    if (mAnimFlags.Get(AnimFlags::eBit13_Is8Bit))
    {
        textureMode = TPageMode::e8Bit_1;
    }
    else if (mAnimFlags.Get(AnimFlags::eBit14_Is16Bit))
    {
        textureMode = TPageMode::e16Bit_2;
    }
    else
    {
        textureMode = TPageMode::e4Bit_0;
    }

    Poly_FT4* pPoly = &mOtData[gPsxDisplay.mBufferIndex];
    PolyFT4_Init(pPoly);
    Poly_Set_SemiTrans(&pPoly->mBase.header, mAnimFlags.Get(AnimFlags::eBit15_bSemiTrans));
    Poly_Set_Blending(&pPoly->mBase.header, mAnimFlags.Get(AnimFlags::eBit16_bBlending));

    SetRGB0(pPoly, mRed, mGreen, mBlue);
    SetTPage(pPoly, static_cast<u16>(PSX_getTPage(textureMode, mRenderMode, mVramRect.x, mVramRect.y)));
    SetClut(pPoly, static_cast<u16>(PSX_getClut(mPalVramXY.x, mPalVramXY.y)));

    u8 u1 = mVramRect.x & 63;
    if (textureMode == TPageMode::e8Bit_1)
    {
        // 8 bit
        u1 *= 2;
    }
    else if (textureMode == TPageMode::e4Bit_0)
    {
        // 4 bit
        u1 *= 4;
    }
    else
    {
        // 16 bit
    }

    const u8 v0 = static_cast<u8>(mVramRect.y);
    const u8 u0 = pFrameHeader->field_4_width + u1 - 1;
    const u8 v1 = pFrameHeader->field_5_height + v0 - 1;

    if (field_14_scale != FP_FromInteger(1))
    {
        // Apply scale to x/y pos
        scaled_height *= field_14_scale;
        scaled_width *= field_14_scale;

        if (field_14_scale == FP_FromDouble(0.5))
        {
            // Add 1 if half scale
            scaled_height += FP_FromDouble(1.0);
            scaled_width += FP_FromDouble(1.0);
        }

        // Apply scale to x/y offset
        xOffSet_scaled *= field_14_scale;
        yOffset_scaled = (yOffset_scaled * field_14_scale) - FP_FromInteger(1);
    }

    s16 polyXPos = 0;
    s16 polyYPos = 0;

    const bool kFlipY = mAnimFlags.Get(AnimFlags::eBit6_FlipY);
    const bool kFlipX = mAnimFlags.Get(AnimFlags::eBit5_FlipX);


    if (kFlipX)
    {
        polyXPos = xpos_pc - FP_GetExponent(xOffSet_scaled + FP_FromDouble(0.499)) - FP_GetExponent(scaled_width + FP_FromDouble(0.499));
    }
    else
    {
        polyXPos = xpos_pc + FP_GetExponent(xOffSet_scaled + FP_FromDouble(0.499));
    }

    if (kFlipY)
    {
        // TODO: Might be wrong because this was doing something with the sign bit abs() ??
        polyYPos = static_cast<s16>(ypos) - FP_GetExponent(yOffset_scaled + FP_FromDouble(0.499)) - FP_GetExponent(scaled_height + FP_FromDouble(0.499));
    }
    else
    {
        polyYPos = static_cast<s16>(ypos) + FP_GetExponent(yOffset_scaled + FP_FromDouble(0.499));
    }

    SetUV0(pPoly, kFlipX ? u0 : u1, kFlipY ? v1 : v0);
    SetUV1(pPoly, kFlipX ? u1 : u0, kFlipY ? v1 : v0);
    SetUV2(pPoly, kFlipX ? u0 : u1, kFlipY ? v0 : v1);
    SetUV3(pPoly, kFlipX ? u1 : u0, kFlipY ? v0 : v1);


    SetXY0(pPoly, polyXPos, polyYPos);
    SetXY1(pPoly, polyXPos + FP_GetExponent(scaled_width - FP_FromDouble(0.501)), polyYPos);
    SetXY2(pPoly, polyXPos, polyYPos + FP_GetExponent(scaled_height - FP_FromDouble(0.501)));
    SetXY3(pPoly, polyXPos + FP_GetExponent(scaled_width - FP_FromDouble(0.501)), polyYPos + FP_GetExponent(scaled_height - FP_FromDouble(0.501)));

    if (pFrameHeader->field_7_compression_type == CompressionType::eType_3_RLE_Blocks || pFrameHeader->field_7_compression_type == CompressionType::eType_6_RLE)
    {
        SetPrimExtraPointerHack(pPoly, &pFrameHeader->field_8_width2);
    }
    else
    {
        SetPrimExtraPointerHack(pPoly, nullptr);
    }

    OrderingTable_Add(OtLayer(ppOt, mRenderLayer), &pPoly->mBase.header);
}

void Animation::VCleanUp()
{
    gAnimations->Remove_Item(this);

    Animation_Pal_Free();

    ResourceManager::FreeResource_49C330(mDbuf);
}

void Animation::VDecode()
{
    if (DecodeCommon())
    {
        DecompressFrame();
    }
}

bool Animation::DecodeCommon()
{
    if (!field_20_ppBlock || !*field_20_ppBlock)
    {
        return false;
    }

    AnimationHeader* pAnimationHeader = reinterpret_cast<AnimationHeader*>(&(*field_20_ppBlock)[mFrameTableOffset]);
    if (pAnimationHeader->field_2_num_frames == 1 && mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        return false;
    }

    bool isLastFrame = false;
    if (mAnimFlags.Get(AnimFlags::eBit19_LoopBackwards))
    {
        // Loop backwards
        const s16 prevFrameNum = --mCurrentFrame;
        mFrameChangeCounter = mFrameDelay;

        if (prevFrameNum < pAnimationHeader->field_4_loop_start_frame)
        {
            if (mAnimFlags.Get(AnimFlags::eBit8_Loop))
            {
                // Loop to last frame
                mCurrentFrame = pAnimationHeader->field_2_num_frames - 1;
            }
            else
            {
                // Stay on current frame
                mFrameChangeCounter = 0;
                mCurrentFrame = prevFrameNum + 1;
            }

            // For some reason eBit12_ForwardLoopCompleted isn't set when going backwards
        }

        // Is first (last since running backwards) frame?
        if (mCurrentFrame == 0)
        {
            isLastFrame = true;
        }
    }
    else
    {
        // Loop forwards
        const s16 nextFrameNum = ++mCurrentFrame;
        mFrameChangeCounter = mFrameDelay;

        // Animation reached end point
        if (nextFrameNum >= pAnimationHeader->field_2_num_frames)
        {
            if (mAnimFlags.Get(AnimFlags::eBit8_Loop))
            {
                // Loop back to loop start frame
                mCurrentFrame = pAnimationHeader->field_4_loop_start_frame;
            }
            else
            {
                // Stay on current frame
                mCurrentFrame = nextFrameNum - 1;
                mFrameChangeCounter = 0;
            }

            mAnimFlags.Set(AnimFlags::eBit12_ForwardLoopCompleted);
        }

        // Is last frame ?
        if (mCurrentFrame == pAnimationHeader->field_2_num_frames - 1)
        {
            isLastFrame = true;
        }
    }

    if (isLastFrame)
    {
        mAnimFlags.Set(AnimFlags::eBit18_IsLastFrame);
    }
    else
    {
        mAnimFlags.Clear(AnimFlags::eBit18_IsLastFrame);
    }

    return true;
}

void Animation::Invoke_CallBacks()
{
    if (!field_20_ppBlock || !mFnPtrArray)
    {
        return;
    }

    FrameInfoHeader* pFrameHeaderCopy = Get_FrameHeader(-1);
    // This data can be an array of u32's + other data up to field_6_count
    // which appears AFTER the usual data.
    const u32* pCallBackData = reinterpret_cast<const u32*>(&pFrameHeaderCopy->field_8_data.points[3]);
    for (s32 i = 0; i < pFrameHeaderCopy->field_6_count; i++)
    {
        const auto pFnCallBack = mFnPtrArray[*pCallBackData];
        if (!pFnCallBack)
        {
            break;
        }
        pCallBackData++; // Skip the array index
        // Pass the data pointer into the call back which will then read and skip any extra data
        pCallBackData += pFnCallBack(mGameObj, (s16*) pCallBackData);
    }
}

s16 Animation::Set_Animation_Data(AnimId animId, u8** pAnimRes)
{
    const AnimRecord& anim = AnimRec(animId);
    return Set_Animation_Data(anim.mFrameTableOffset, pAnimRes);
}

s16 Animation::Set_Animation_Data(s32 frametableoffset, u8** pAnimRes)
{
    
    if (pAnimRes)
    {
        field_20_ppBlock = pAnimRes;
    }

    if (!field_20_ppBlock)
    {
        return 0;
    }

    mFrameTableOffset = frametableoffset;

    AnimationHeader* pAnimationHeader = reinterpret_cast<AnimationHeader*>(&(*field_20_ppBlock)[mFrameTableOffset]);
    mFrameDelay = pAnimationHeader->field_0_fps;

    mAnimFlags.Clear(AnimFlags::eBit12_ForwardLoopCompleted);
    mAnimFlags.Clear(AnimFlags::eBit18_IsLastFrame);
    mAnimFlags.Clear(AnimFlags::eBit19_LoopBackwards);
    mAnimFlags.Clear(AnimFlags::eBit8_Loop);

    if (pAnimationHeader->field_6_flags & AnimationHeader::eLoopFlag)
    {
        mAnimFlags.Set(AnimFlags::eBit8_Loop);
    }

    mFrameChangeCounter = 1;
    mCurrentFrame = -1;

    VDecode();

    // Reset to start frame
    mFrameChangeCounter = 1;
    mCurrentFrame = -1;

    return 1;
}

void Animation::Animation_Pal_Free()
{
    if (mVramRect.w > 0)
    {
        if (mVramRect.x || mVramRect.y)
        {
            Vram_free({mVramRect.x, mVramRect.y}, {mVramRect.w, mVramRect.h});
        }
    }

    if (mPalDepth > 0)
    {
        IRenderer::GetRenderer()->PalFree(IRenderer::PalRecord{mPalVramXY.x, mPalVramXY.y, mPalDepth});
    }
}

void Animation::SetFrame(s16 newFrame)
{
    if (field_20_ppBlock)
    {
        if (newFrame == -1)
        {
            newFrame = 0;
        }

        AnimationHeader* pHead = reinterpret_cast<AnimationHeader*>(*field_20_ppBlock + mFrameTableOffset); // TODO: Make getting offset to animation header cleaner

        if (newFrame > pHead->field_2_num_frames)
        {
            newFrame = pHead->field_2_num_frames;
        }

        mFrameChangeCounter = 1;
        mCurrentFrame = newFrame - 1;
    }
}

ALIVE_VAR(1, 0x5440AC, FrameInfoHeader, sBlankFrameInfoHeader_5440AC, {});

FrameInfoHeader* Animation::Get_FrameHeader(s16 frame)
{
    if (!field_20_ppBlock)
    {
        return nullptr;
    }

    if (frame < -1 || frame == -1)
    {
        frame = mCurrentFrame != -1 ? mCurrentFrame : 0;
    }

    AnimationHeader* pHead = reinterpret_cast<AnimationHeader*>(*field_20_ppBlock + mFrameTableOffset); // TODO: Make getting offset to animation header cleaner
    u32 frameOffset = pHead->mFrameOffsets[frame];

    FrameInfoHeader* pFrame = reinterpret_cast<FrameInfoHeader*>(*field_20_ppBlock + frameOffset);

    // Never seen this get hit, perhaps some sort of PSX specific check as addresses have to be aligned there?
    // TODO: Remove it in the future when proven to be not required?
#if defined(_MSC_VER) && !defined(_WIN64)
    if (reinterpret_cast<u32>(pFrame) & 3)
    {
        FrameInfoHeader* Unknown = &sBlankFrameInfoHeader_5440AC;
        return Unknown;
    }
#endif

    return pFrame;
}

void Animation::Get_Frame_Rect(PSX_RECT* pRect)
{
    Poly_FT4* pPoly = &mOtData[gPsxDisplay.mBufferIndex];
    if (!mAnimFlags.Get(AnimFlags::eBit20_use_xy_offset))
    {
        Poly_FT4_Get_Rect_409DA0(pRect, pPoly);
        return;
    }

    const auto min_x0_x1 = std::min(X0(pPoly), X1(pPoly));
    const auto min_x2_x3 = std::min(X2(pPoly), X3(pPoly));
    pRect->x = std::min(min_x0_x1, min_x2_x3);

    const auto max_x0_x1 = std::max(X0(pPoly), X1(pPoly));
    const auto max_x2_x3 = std::max(X2(pPoly), X3(pPoly));
    pRect->w = std::max(max_x0_x1, max_x2_x3);

    const auto min_y0_y1 = std::min(Y0(pPoly), Y1(pPoly));
    const auto min_y2_y3 = std::min(Y2(pPoly), Y3(pPoly));
    pRect->y = std::min(min_y0_y1, min_y2_y3);

    const auto max_y0_y1 = std::max(Y0(pPoly), Y1(pPoly));
    const auto max_y2_y3 = std::max(Y2(pPoly), Y3(pPoly));
    pRect->h = std::max(max_y0_y1, max_y2_y3);
}

u16 Animation::Get_Frame_Count()
{
    AnimationHeader* pHead = reinterpret_cast<AnimationHeader*>(*field_20_ppBlock + mFrameTableOffset); // TODO: Make getting offset to animation header cleaner
    return pHead->field_2_num_frames;
}

s16 Animation::Init(s32 frametableoffset, u16 maxW, u16 maxH, BaseGameObject* pGameObj, u8** ppAnimData)
{
    mAnimFlags.Raw().all = 0; // TODO extra - init to 0's first - this may be wrong if any bits are explicitly set before this is called
    mAnimFlags.Set(AnimFlags::eBit21);

    mFrameTableOffset = frametableoffset;
    field_20_ppBlock = ppAnimData;
    mFnPtrArray = nullptr;
    mDbuf = nullptr;

    if (!ppAnimData)
    {
        return 0;
    }

    mGameObj = pGameObj;
    AnimationHeader* pHeader = reinterpret_cast<AnimationHeader*>(&(*ppAnimData)[frametableoffset]);

    mAnimFlags.Clear(AnimFlags::eBit1);
    mAnimFlags.Clear(AnimFlags::eBit5_FlipX);
    mAnimFlags.Clear(AnimFlags::eBit6_FlipY);
    mAnimFlags.Clear(AnimFlags::eBit7_SwapXY);
    mAnimFlags.Set(AnimFlags::eBit2_Animate);
    mAnimFlags.Set(AnimFlags::eBit3_Render);

    mAnimFlags.Set(AnimFlags::eBit8_Loop, pHeader->field_6_flags & AnimationHeader::eLoopFlag);

    mAnimFlags.Clear(AnimFlags::eBit10_alternating_flag);

    mAnimFlags.Clear(AnimFlags::eBit11_bToggle_Bit10);

    mAnimFlags.Clear(AnimFlags::eBit14_Is16Bit);
    mAnimFlags.Clear(AnimFlags::eBit13_Is8Bit);

    // Clear vram/pal inits to not allocated
    mVramRect.w = 0;
    mPalDepth = 0;

    mAnimFlags.Clear(AnimFlags::eBit24);
    mAnimFlags.Clear(AnimFlags::eBit23);
    mAnimFlags.Clear(AnimFlags::eBit22_DeadMode);

    mAnimFlags.Clear(AnimFlags::eBit15_bSemiTrans);
    mAnimFlags.Set(AnimFlags::eBit16_bBlending);

    mFrameDelay = pHeader->field_0_fps;
    mFrameChangeCounter = 1;
    mCurrentFrame = -1;
    mRenderMode = TPageAbr::eBlend_0;
    mBlue = 0;
    mGreen = 0;
    mRed = 0;
    field_14_scale = FP_FromInteger(1);

    FrameInfoHeader* pFrameInfoHeader = Get_FrameHeader(0);
    u8* pAnimData = *field_20_ppBlock;

    const FrameHeader* pFrameHeader = reinterpret_cast<const FrameHeader*>(&(*field_20_ppBlock)[pFrameInfoHeader->field_0_frame_header_offset]);

    u8* pClut = &pAnimData[pFrameHeader->field_0_clut_offset];

    s8 b256Pal = 0;
    s32 vram_width = 0;
    s16 pal_depth = 0;

    switch (pFrameHeader->field_6_colour_depth)
    {
    case 4:
    {
        vram_width = (maxW % 2) + (maxW / 2);
        pal_depth = 16;
        b256Pal = 0; // is 16 pal
    }
    break;

    case 8:
    {
        vram_width = maxW;
        if (*(u32*)pClut == 64) // CLUT entry count/len
        {
            pal_depth = 64;
        }
        else
        {
            pal_depth = 256;
            b256Pal = 1; // is 256 pal
        }
        mAnimFlags.Set(AnimFlags::eBit13_Is8Bit);

    }
    break;

    case 16:
    {
        vram_width = maxW * 2;
        mAnimFlags.Set(AnimFlags::eBit14_Is16Bit);
    }
    break;

    default:
        return 0;
    }

    if (!Vram_alloc(maxW, maxH, pFrameHeader->field_6_colour_depth, &mVramRect))
    {
        // Seems like this can at least happen with many bomb particles
        // this will be fixed in the future
        LOG_ERROR("Vram alloc failed");
        return 0;
    }

    // This makes no sense
    mAnimFlags.Set(AnimFlags::eBit25_bDecompressDone, b256Pal);


    if (pal_depth > 0)
    {
        IRenderer::PalRecord palRec{ 0, 0, pal_depth };
        if (!IRenderer::GetRenderer()->PalAlloc(palRec))
        {
            ALIVE_FATAL("PalAlloc failed");
        }

        mPalVramXY.x = palRec.x;
        mPalVramXY.y = palRec.y;
        mPalDepth = palRec.depth;

        IRenderer::GetRenderer()->PalSetData(palRec, pClut + 4); // +4 Skip len, load pal
    }

    mDbufSize = maxH * (vram_width + 3);
    mDbufSize += 8; // Add 8 for some reason
    mDbuf = nullptr;

    // NOTE: OG bug or odd compiler code gen? Why isn't it using the passed in list which appears to always be this anyway ??
    if (!gAnimations->Push_Back(this))
    {
        LOG_ERROR("gAnimations->Push_Back(this) returned 0 but shouldn't");
        return 0;
    }

    // Get first frame decompressed/into VRAM
    VDecode();

    mFrameChangeCounter = 1;
    mCurrentFrame = -1;

    return 1;
}

s16 Animation::Init(AnimId animId, BaseGameObject* pGameObj, u8** ppAnimData)
{
    const AnimRecord& anim = AnimRec(animId);
    return Init(anim.mFrameTableOffset, anim.mMaxW, anim.mMaxH, pGameObj, ppAnimData);
}

void Animation::LoadPal(u8** pAnimData, s32 palOffset)
{
    if (pAnimData)
    {
        // +4 = skip CLUT len
        const u8* pPalDataOffset = &(*pAnimData)[palOffset];
        if (mPalDepth != 16 && mPalDepth != 64 && mPalDepth != 256)
        {
            LOG_ERROR("Bad pal depth " << mPalDepth);
            ALIVE_FATAL("Bad pal depth");
        }
        IRenderer::GetRenderer()->PalSetData(IRenderer::PalRecord{mPalVramXY.x, mPalVramXY.y, mPalDepth}, pPalDataOffset + 4); // +4 skip len, load pal
    }
}

void Animation::Get_Frame_Offset(s16* pBoundingX, s16* pBoundingY)
{
    FrameInfoHeader* pFrameHeader = Get_FrameHeader(-1);
    *pBoundingX = pFrameHeader->field_8_data.offsetAndRect.mOffset.x;
    *pBoundingY = pFrameHeader->field_8_data.offsetAndRect.mOffset.y;
}


void Animation::Get_Frame_Width_Height(s16* pWidth, s16* pHeight)
{
    FrameInfoHeader* pFrameHeader = Get_FrameHeader(-1);
    if (mAnimFlags.Get(AnimFlags::eBit22_DeadMode))
    {
        ALIVE_FATAL("Mode should never be used");
    }
    else
    {
        auto pHeader = reinterpret_cast<const FrameHeader*>(&(*field_20_ppBlock)[pFrameHeader->field_0_frame_header_offset]);
        *pWidth = pHeader->field_4_width;
        *pHeight = pHeader->field_5_height;
    }
}
