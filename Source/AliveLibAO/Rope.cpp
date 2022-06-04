#include "stdafx_ao.h"
#include "Function.hpp"
#include "Rope.hpp"
#include "stdlib.hpp"
#include "PathData.hpp"
#include "PsxDisplay.hpp"
#include "ScreenManager.hpp"
#include "ShadowZone.hpp"
#include "Map.hpp"
#include "ResourceManager.hpp"

namespace AO {

void ClipPoly_Vertically_4584B0(Poly_FT4* pPoly, s32 minY, s32 maxY)
{
    const s32 d1 = minY - Y0(pPoly);
    const s16 polyHeight = Y3(pPoly) - Y0(pPoly);
    if (d1 > 0 && d1 <= polyHeight)
    {
        SetXY0(pPoly, X0(pPoly), Y0(pPoly) + (s16) d1);
        SetXY1(pPoly, X1(pPoly), Y1(pPoly) + (s16) d1);

        SetUV0(pPoly, U0(pPoly), V0(pPoly) + (u8) d1);
        SetUV1(pPoly, U1(pPoly), V1(pPoly) + (u8) d1);
    }

    const s32 d2 = Y3(pPoly) - maxY;
    if (d2 > 0 && d2 <= polyHeight)
    {
        SetXY2(pPoly, X2(pPoly), Y2(pPoly) - (s16) d2);
        SetXY3(pPoly, X3(pPoly), Y3(pPoly) - (s16) d2);

        SetUV2(pPoly, U2(pPoly), V2(pPoly) - (u8) d2);
        SetUV3(pPoly, U3(pPoly), V3(pPoly) - (u8) d2);
    }
}

Rope::~Rope()
{
    ao_delete_free_447540(field_E8_pRopeRes);
}

Rope::Rope(s32 left, s32 top, s32 bottom, FP scale)
{
    mBaseGameObjectTypeId = ReliveTypes::eRope;

    field_C8_yOffset = 0;

    if (scale == FP_FromInteger(1))
    {
        field_E6_rope_length = 15;
    }
    else
    {
        field_E6_rope_length = 7;
    }

    switch (gMap.mCurrentLevel)
    {
        case LevelIds::eRuptureFarms_1:
        case LevelIds::eDesert_8:
        case LevelIds::eDesertTemple_9:
        case LevelIds::eBoardRoom_12:
        case LevelIds::eRuptureFarmsReturn_13:
        case LevelIds::eDesertEscape_15:
        {
            const AnimRecord& ropeRec = AO::AnimRec(AnimId::Rope_R1);
            u8** ppRopeRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, ropeRec.mResourceId, 1, 0);
            Animation_Init_417FD0(ropeRec.mFrameTableOffset, ropeRec.mMaxW, ropeRec.mMaxH, ppRopeRes, 1);
            break;
        }

        default:
        {
            const AnimRecord& ropeRec = AO::AnimRec(AnimId::Rope_Lines);
            u8** ppRopeRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, ropeRec.mResourceId, 1, 0);
            Animation_Init_417FD0(ropeRec.mFrameTableOffset, ropeRec.mMaxW, ropeRec.mMaxH, ppRopeRes, 1);
            break;
        }
    }
    field_10_anim.field_14_scale = scale;
    field_BC_sprite_scale = scale;
    if (scale == FP_FromInteger(1))
    {
        field_10_anim.mRenderLayer = Layer::eLayer_RopeWebMeatSaw_24;
        field_C6_scale = 1;
    }
    else
    {
        field_10_anim.mRenderLayer = Layer::eLayer_RopeWebMeatSaw_Half_5;
        field_C6_scale = 0;
    }

    field_10_anim.mRed = 128;
    field_10_anim.mGreen = 128;
    field_10_anim.mBlue = 128;

    field_F2_bottom = static_cast<s16>(bottom);
    field_E4_rope_segment_count = 240 / field_E6_rope_length + 1;

    field_A8_xpos = FP_FromInteger(left);
    field_AC_ypos = FP_FromInteger(bottom);
    field_EC_left = static_cast<s16>(left);
    field_F0_right = static_cast<s16>(left);
    field_EE_top = static_cast<s16>(top);

    field_E8_pRopeRes = reinterpret_cast<AnimationUnknown*>(ao_new_malloc_447520(sizeof(AnimationUnknown) * field_E4_rope_segment_count));
    if (field_E8_pRopeRes)
    {
        for (s32 i = 0; i < field_E4_rope_segment_count; i++)
        {
            // Placement new the items
            AnimationUnknown* pSegment = &field_E8_pRopeRes[i];
            new (pSegment) AnimationUnknown();

            pSegment->mAnimFlags.Set(AnimFlags::eBit3_Render);
            pSegment->field_68_anim_ptr = &field_10_anim;
            pSegment->mRenderLayer = field_10_anim.mRenderLayer;
            pSegment->field_6C_scale = scale;
            pSegment->mAnimFlags.Clear(AnimFlags::eBit15_bSemiTrans);
            pSegment->mAnimFlags.Clear(AnimFlags::eBit16_bBlending);
        }
    }
}

void Rope::VUpdate()
{
    // Empty
}

void Rope::VRender(PrimHeader** ppOt)
{
    PSX_Point camPos = {};
    gMap.GetCurrentCamCoords(&camPos);
    if (field_B2_lvl_number == gMap.mCurrentLevel)
    {
        if (field_B0_path_number == gMap.mCurrentPath)
        {
            if (field_A8_xpos >= FP_FromInteger(camPos.field_0_x) && field_A8_xpos <= FP_FromInteger(camPos.field_0_x + 1024))
            {
                const FP camYPos = pScreenManager_4FF7C8->field_10_pCamPos->field_4_y;

                s32 minY = FP_GetExponent((FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos + field_EE_top))
                                          - camYPos);
                s32 maxY = FP_GetExponent((FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos + field_F2_bottom))
                                          - camYPos);

                s16 ypos = FP_GetExponent(field_AC_ypos);
                if (ypos > field_F2_bottom)
                {
                    ypos = field_F2_bottom + ((ypos - field_F2_bottom) % field_E6_rope_length);
                }

                s16 screenX = PsxToPCX(
                    FP_GetExponent(field_A8_xpos + FP_FromInteger(pScreenManager_4FF7C8->field_14_xpos) - pScreenManager_4FF7C8->field_10_pCamPos->field_0_x),
                    11);
                s16 screenY = FP_GetExponent(
                    (FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos + ypos))
                    - camYPos);

                if (field_C8_yOffset + screenY > 240)
                {
                    screenY = screenY % field_E6_rope_length + 240;
                    ypos = FP_GetExponent(pScreenManager_4FF7C8->field_10_pCamPos->field_4_y
                                          + FP_FromInteger(screenY - pScreenManager_4FF7C8->field_16_ypos));
                }
                if (minY < 0)
                {
                    minY = 0;
                }
                if (maxY > 240)
                {
                    maxY = 240;
                }

                field_10_anim.VRender(640, 240, ppOt, 0, 0);
                if (screenY >= minY)
                {
                    for (s32 idx = 0; idx < field_E4_rope_segment_count; idx++)
                    {
                        s16 r = 128;
                        s16 g = 128;
                        s16 b = 128;
                        ShadowZone::ShadowZones_Calculate_Colour(
                            FP_GetExponent(field_A8_xpos),
                            ypos - (idx * field_E6_rope_length),
                            field_C6_scale,
                            &r,
                            &g,
                            &b);

                        field_E8_pRopeRes[idx].mRed = static_cast<u8>(r);
                        field_E8_pRopeRes[idx].mGreen = static_cast<u8>(g);
                        field_E8_pRopeRes[idx].mBlue = static_cast<u8>(b);

                        field_E8_pRopeRes[idx].VRender2(
                            screenX,
                            field_C8_yOffset + screenY,
                            ppOt);

                        PSX_RECT rect = {};
                        field_E8_pRopeRes[idx].GetRenderedSize(&rect);
                        pScreenManager_4FF7C8->InvalidateRect(
                            rect.x,
                            rect.y,
                            rect.w,
                            rect.h,
                            pScreenManager_4FF7C8->field_2E_idx);

                        ClipPoly_Vertically_4584B0(
                            &field_E8_pRopeRes[idx].field_10_polys[gPsxDisplay_504C78.field_A_buffer_index],
                            minY + field_C8_yOffset,
                            maxY + field_C8_yOffset);

                        screenY -= field_E6_rope_length;
                        if (screenY < minY)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

} // namespace AO
