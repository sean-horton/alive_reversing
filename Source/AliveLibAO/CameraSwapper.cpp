#include "stdafx_ao.h"
#include "CameraSwapper.hpp"
#include "Function.hpp"
#include "PsxDisplay.hpp"
#include "Movie.hpp"
#include "Map.hpp"
#include "stdlib.hpp"
#include "Psx.hpp"
#include "ScreenClipper.hpp"
#include "MusicController.hpp"
#include "BackgroundMusic.hpp"
#include "ScreenManager.hpp"
#include "PsxDisplay.hpp"
#include "Sfx.hpp"
#include "Sys_common.hpp"

namespace AO {

ALIVE_VAR(1, 0x507668, s16, sNumCamSwappers_507668, 0);

CameraSwapper::CameraSwapper(u8** ppBits, s32 movieId, s32 movieFlag, s8 movieFlags, s16 flags, s16 volume)
    : BaseGameObject(1)
{
    Init(ppBits, CameraSwapEffects::ePlay1FMV_5);

    PSX_ResetCallBack_49AFB0();

    ao_new<Movie>(movieFlag, movieId, movieFlags, flags, volume);

    field_3C_movie_bPutDispEnv = flags;
}

CameraSwapper::CameraSwapper(u8** ppBits, s32 moviePos1, s32 movieId1, s32 moviePos2, s32 movieFlag1, s8 movieFlags1, s16 movieVol1, s16 movieFlag2, s16 movieFlag2_1, s16 movieFlags2_1, s16 movieVol2)
    : BaseGameObject(1)
{
    Init(ppBits, CameraSwapEffects::ePlay2FMVs_9);

    PSX_ResetCallBack_49AFB0();

    ao_new<Movie>(movieId1, moviePos1, movieFlags1, movieVol1, movieFlag2);

    field_14_movie_id_3 = movieFlag1;
    field_10_movie_pos_3 = moviePos2;
    field_34_movie_vol_3 = movieVol2;
    field_32_movie_flags_3 = movieFlags2_1;
    field_30_movie_flag_3 = movieFlag2_1;

    field_3C_movie_bPutDispEnv = movieVol1;
}

CameraSwapper::CameraSwapper(u8** ppBits, s32 moviePos1, s32 movieIds1, s32 moviePos2, s32 movieId2, s32 moviePos3, s32 movieId3, s8 movieFlag1, s16 movieFlags1, s16 movieVol1, s16 movieFlag2, s16 movieFlags2, s16 movieVol2, s16 movieFlag3, s16 movieFlags3, s16 movieVol3)
    : BaseGameObject(1)
{
    Init(ppBits, CameraSwapEffects::ePlay3FMVs_10);

    PSX_ResetCallBack_49AFB0();
    ao_new<Movie>(movieIds1, moviePos1, movieFlag1, movieFlags1, movieVol1);

    field_18_movie_pos_2 = moviePos2;
    field_1C_movie_id_2 = movieId2;
    field_38_movie_flags_2 = movieFlags2;
    field_36_movie_flag_2 = movieFlag2;
    field_3A_movie_vol_2 = movieVol2;

    field_14_movie_id_3 = movieId3;
    field_10_movie_pos_3 = moviePos3;
    field_30_movie_flag_3 = movieFlag3;
    field_34_movie_vol_3 = movieVol3;
    field_32_movie_flags_3 = movieFlags3;

    field_3C_movie_bPutDispEnv = movieFlags1;
}

void CameraSwapper::VScreenChanged()
{
    // Empty
}

CameraSwapper::CameraSwapper(u8** ppBits, CameraSwapEffects changeEffect, s32 xpos, s32 ypos)
    : BaseGameObject(1)
{
    field_40_ypos_converted = static_cast<s16>(ypos);
    field_3E_xpos_converted = static_cast<s16>(PsxToPCX(xpos));
    Init(ppBits, changeEffect);
}

CameraSwapper::~CameraSwapper()
{
    sNumCamSwappers_507668--;

    if (field_24_pSubObject)
    {
        field_24_pSubObject->mBaseGameObjectFlags.Set(Options::eDead);
    }

    if (sMap_bDoPurpleLightEffect_507C9C)
    {
        gMap.RemoveObjectsWithPurpleLight(0);
        sMap_bDoPurpleLightEffect_507C9C = FALSE;
    }

    BackgroundMusic::Play();
    MusicController::EnableMusic(1);
    gMap.Start_Sounds_For_Objects_In_Near_Cameras();
}

void CameraSwapper::Init(u8** ppCamRes, CameraSwapEffects changeEffect)
{
    mBaseGameObjectFlags.Set(Options::eUpdateDuringCamSwap_Bit10);

    mBaseGameObjectTypeId = ReliveTypes::eCameraSwapper;

    field_24_pSubObject = nullptr;

    if (changeEffect == CameraSwapEffects::ePlay1FMV_5 || changeEffect == CameraSwapEffects::ePlay2FMVs_9 || changeEffect == CameraSwapEffects::ePlay3FMVs_10)
    {
        field_20_ppCamRes = ppCamRes;
    }
    else
    {
        pScreenManager_4FF7C8->DecompressCameraToVRam(reinterpret_cast<u16**>(ppCamRes));
    }

    sNumCamSwappers_507668++;

    if (sNumCamSwappers_507668 != 1)
    {
        mBaseGameObjectFlags.Clear(BaseGameObject::eUpdatable_Bit2);
        mBaseGameObjectFlags.Set(BaseGameObject::eListAddFailed_Bit1);
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);

        // There can only be 1 active at a time
        return;
    }

    field_28_changeEffect = changeEffect;

    PSX_Point xy = {};
    PSX_Point wh = {};

    switch (field_28_changeEffect)
    {
        case CameraSwapEffects::eInstantChange_0:
            pScreenManager_4FF7C8->InvalidateRect_Idx3(0, 0, 640, 240);
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            field_24_pSubObject = nullptr;
            break;

        case CameraSwapEffects::eLeftToRight_1:
            field_46_slice_width = 48; // 384 / 8 ?
            field_2C_slices_per_tick = -1;
            field_2E_total_slices = gPsxDisplay_504C78.field_0_width / field_46_slice_width;
            field_2A_current_slice = field_2E_total_slices;

            xy.field_2_y = 0;
            xy.field_0_x = gPsxDisplay_504C78.field_0_width;

            wh.field_0_x = gPsxDisplay_504C78.field_0_width;
            wh.field_2_y = gPsxDisplay_504C78.field_2_height;

            pScreenManager_4FF7C8->field_38 = 1;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, wh, Layer::eLayer_0);
            break;

        case CameraSwapEffects::eRightToLeft_2:
            field_46_slice_width = 48;
            field_2C_slices_per_tick = 1;
            field_2E_total_slices = gPsxDisplay_504C78.field_0_width / field_46_slice_width + 1;
            field_2A_current_slice = -1;

            xy.field_2_y = 0;
            xy.field_0_x = 0;

            wh.field_0_x = 0;
            wh.field_2_y = gPsxDisplay_504C78.field_2_height;

            pScreenManager_4FF7C8->field_38 = 1;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, wh, Layer::eLayer_0);
            break;

        case CameraSwapEffects::eTopToBottom_3:
            field_46_slice_width = 30; // 240 / 8 ?
            field_2C_slices_per_tick = -1;
            field_2E_total_slices = gPsxDisplay_504C78.field_2_height / field_46_slice_width;
            field_2A_current_slice = field_2E_total_slices;

            xy.field_0_x = 0;
            xy.field_2_y = gPsxDisplay_504C78.field_2_height;

            wh.field_0_x = gPsxDisplay_504C78.field_0_width;
            wh.field_2_y = gPsxDisplay_504C78.field_2_height;

            pScreenManager_4FF7C8->field_38 = 1;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, wh, Layer::eLayer_0);
            break;

        case CameraSwapEffects::eBottomToTop_4:
            field_46_slice_width = 30; // 240 / 8 ?
            field_2C_slices_per_tick = 1;
            field_2E_total_slices = gPsxDisplay_504C78.field_2_height / field_46_slice_width;
            field_2A_current_slice = -1;

            xy.field_0_x = 0;
            xy.field_2_y = 0;

            wh.field_0_x = gPsxDisplay_504C78.field_0_width;
            wh.field_2_y = 0;

            pScreenManager_4FF7C8->field_38 = 1;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, wh, Layer::eLayer_0);
            break;

        case CameraSwapEffects::eVerticalSplit_6:
            field_46_slice_width = 24; // ??
            field_2E_total_slices = (gPsxDisplay_504C78.field_0_width / 2) / field_46_slice_width;
            field_2C_slices_per_tick = 1;
            field_2A_current_slice = 0;

            pScreenManager_4FF7C8->field_38 = 1;

            xy.field_0_x = gPsxDisplay_504C78.field_0_width / 2;
            xy.field_2_y = 0;

            wh.field_0_x = gPsxDisplay_504C78.field_0_width / 2;
            wh.field_2_y = gPsxDisplay_504C78.field_2_height;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, wh, Layer::eLayer_0);
            break;


        case CameraSwapEffects::eHorizontalSplit_7:
            field_46_slice_width = 15; // ??
            field_2C_slices_per_tick = 1;
            field_2E_total_slices = (gPsxDisplay_504C78.field_2_height / 2) / field_46_slice_width;
            field_2A_current_slice = 0;

            pScreenManager_4FF7C8->field_38 = 1;

            xy.field_0_x = 0;
            xy.field_2_y = gPsxDisplay_504C78.field_2_height / 2;

            wh.field_0_x = gPsxDisplay_504C78.field_0_width;
            wh.field_2_y = gPsxDisplay_504C78.field_2_height / 2;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, wh, Layer::eLayer_0);
            break;

        case CameraSwapEffects::eBoxOut_8:
        {
            field_42_XSlices = 24; // ??
            field_44_YSlices = 15; // ??

            s16 xDiff = gPsxDisplay_504C78.field_0_width - field_3E_xpos_converted;
            if (xDiff <= field_3E_xpos_converted)
            {
                xDiff = field_3E_xpos_converted;
            }

            s16 yDiff = gPsxDisplay_504C78.field_2_height - field_40_ypos_converted;
            if (yDiff <= field_40_ypos_converted)
            {
                yDiff = field_40_ypos_converted;
            }

            s16 startingSlice = 0;
            if ((xDiff / field_42_XSlices) <= (yDiff / field_44_YSlices))
            {
                startingSlice = yDiff / field_44_YSlices;
            }
            else
            {
                startingSlice = xDiff / field_42_XSlices;
            }

            field_2C_slices_per_tick = 1;
            field_2E_total_slices = startingSlice + 1;
            field_2A_current_slice = 0;

            pScreenManager_4FF7C8->field_38 = 1;

            xy.field_0_x = gPsxDisplay_504C78.field_0_width - 1;
            xy.field_2_y = gPsxDisplay_504C78.field_2_height - 1;

            field_24_pSubObject = ao_new<ScreenClipper>(xy, PSX_Point{ 1, 1 }, Layer::eLayer_0);

            // "Whoosh" door sound effect
            SFX_Play_Mono(SoundEffect::IngameTransition_107, 127);
            break;
        }

        case CameraSwapEffects::ePlay1FMV_5:
        case CameraSwapEffects::ePlay2FMVs_9:
        case CameraSwapEffects::ePlay3FMVs_10:
            pScreenManager_4FF7C8->field_38 = 1;
            field_24_pSubObject = ao_new<ScreenClipper>(PSX_Point{ 0, 0 }, PSX_Point{ 1, 1 }, Layer::eLayer_0);
            field_2A_current_slice = 0;
            break;

        default:
            ALIVE_FATAL("Unknown camera swap effect"); // Or one that isn't handled here
    }
}

void CameraSwapper::VUpdate()
{
    if (mBaseGameObjectFlags.Get(BaseGameObject::eDead))
    {
        return;
    }

    switch (field_28_changeEffect)
    {
        case CameraSwapEffects::eInstantChange_0:
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            return;

        case CameraSwapEffects::eLeftToRight_1:
        case CameraSwapEffects::eRightToLeft_2:
        {
            field_2A_current_slice += field_2C_slices_per_tick;
            if (field_2A_current_slice < 0 || field_2A_current_slice >= field_2E_total_slices)
            {
                // All slices done
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                return;
            }

            const s16 xpos = field_46_slice_width * field_2A_current_slice;
            s16 width = field_46_slice_width * (field_2A_current_slice + 1);
            if (width > gPsxDisplay_504C78.field_0_width - 1)
            {
                width = gPsxDisplay_504C78.field_0_width - 1;
            }

            pScreenManager_4FF7C8->InvalidateRect_Idx3(xpos, 0, width, gPsxDisplay_504C78.field_2_height);
            field_24_pSubObject->Update_Clip_Rect({xpos, 0}, {static_cast<s16>(width + 1), static_cast<s16>(gPsxDisplay_504C78.field_2_height)});
        }
        break;

        case CameraSwapEffects::eTopToBottom_3:
        case CameraSwapEffects::eBottomToTop_4:
        {
            field_2A_current_slice += field_2C_slices_per_tick;
            if (field_2A_current_slice < 0 || field_2A_current_slice >= field_2E_total_slices)
            {
                // All slices done
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                return;
            }

            const s16 ypos = field_46_slice_width * field_2A_current_slice;
            s16 height = field_46_slice_width * (field_2A_current_slice + 1);

            pScreenManager_4FF7C8->InvalidateRect_Idx3(
                0,
                ypos,
                gPsxDisplay_504C78.field_0_width,
                height);
            field_24_pSubObject->Update_Clip_Rect({0, ypos}, {static_cast<s16>(gPsxDisplay_504C78.field_0_width), height});
        }
        break;

        case CameraSwapEffects::ePlay1FMV_5:
        {
            if (sMovie_ref_count_9F309C)
            {
                // A movie is still playing
                return;
            }

            if (field_3C_movie_bPutDispEnv == 1)
            {
                gPsxDisplay_504C78.PutCurrentDispEnv_40DE40();
            }

            pScreenManager_4FF7C8->field_38 = 1;

            // Now apply the camera we where storing now that the movie is finished
            if (field_20_ppCamRes)
            {
                pScreenManager_4FF7C8->DecompressCameraToVRam(reinterpret_cast<u16**>(field_20_ppCamRes));
                pScreenManager_4FF7C8->InvalidateRect(0, 0, 640, 240, 0);
                pScreenManager_4FF7C8->InvalidateRect(0, 0, 640, 240, 1);
                pScreenManager_4FF7C8->InvalidateRect(0, 0, 640, 240, 2);
                pScreenManager_4FF7C8->field_36_flags |= 1;
            }
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
        break;

        case CameraSwapEffects::eVerticalSplit_6:
        {
            field_2A_current_slice += field_2C_slices_per_tick;
            if (field_2A_current_slice < 0 || field_2A_current_slice > field_2E_total_slices)
            {
                // All slices done
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                return;
            }

            const s16 xpos = field_46_slice_width * field_2A_current_slice;
            const s16 halfDisplayWidth = gPsxDisplay_504C78.field_0_width / 2;

            pScreenManager_4FF7C8->InvalidateRect_Idx3(static_cast<s16>(halfDisplayWidth - xpos), 0, static_cast<s16>(xpos + halfDisplayWidth), gPsxDisplay_504C78.field_2_height);
            field_24_pSubObject->Update_Clip_Rect({static_cast<s16>(halfDisplayWidth - xpos), 0}, {static_cast<s16>(xpos + halfDisplayWidth + 1), static_cast<s16>(gPsxDisplay_504C78.field_2_height)});
        }
        break;

        case CameraSwapEffects::eHorizontalSplit_7:
        {
            field_2A_current_slice += field_2C_slices_per_tick;
            if (field_2A_current_slice < 0 || field_2A_current_slice > field_2E_total_slices)
            {
                // All slices done
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                return;
            }

            const s16 ypos = field_46_slice_width * field_2A_current_slice;
            const s16 halfDisplayHeight = gPsxDisplay_504C78.field_2_height / 2;

            pScreenManager_4FF7C8->InvalidateRect_Idx3(0, static_cast<s16>(halfDisplayHeight - ypos), 640, static_cast<s16>(halfDisplayHeight + ypos));
            field_24_pSubObject->Update_Clip_Rect({0, static_cast<s16>(halfDisplayHeight - ypos)}, {640, static_cast<s16>(halfDisplayHeight + ypos)});
        }
        break;

        case CameraSwapEffects::eBoxOut_8:
        {
            field_2A_current_slice += field_2C_slices_per_tick;
            if (field_2A_current_slice < 0 || field_2A_current_slice > field_2E_total_slices)
            {
                // All slices done
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                return;
            }

            const s16 xSlicePos = field_2A_current_slice * field_42_XSlices;
            const s16 width = (field_3E_xpos_converted + xSlicePos > gPsxDisplay_504C78.field_0_width) ? gPsxDisplay_504C78.field_0_width : field_3E_xpos_converted + xSlicePos;

            const s16 ySlicePos = field_2A_current_slice * field_44_YSlices;
            const s16 height = (ySlicePos + field_40_ypos_converted > gPsxDisplay_504C78.field_2_height) ? gPsxDisplay_504C78.field_2_height : ySlicePos + field_40_ypos_converted;

            PSX_Point rect_xy = {};
            rect_xy.field_0_x = (field_3E_xpos_converted - xSlicePos <= 0) ? 0 : field_3E_xpos_converted - xSlicePos;
            rect_xy.field_2_y = (field_40_ypos_converted - ySlicePos <= 0) ? 0 : field_40_ypos_converted - ySlicePos;

            pScreenManager_4FF7C8->InvalidateRect_Idx3(
                rect_xy.field_0_x,
                rect_xy.field_2_y,
                width,
                height);

            PSX_Point rect_wh = {};
            rect_wh.field_0_x = width + 1;
            rect_wh.field_2_y = height;

            field_24_pSubObject->Update_Clip_Rect(rect_xy, rect_wh);
        }
        break;

        // TODO: 2 and 3 FMV cases can be de-duped
        case CameraSwapEffects::ePlay2FMVs_9:
            if (field_2A_current_slice < 1)
            {
                field_2A_current_slice++;
            }
            else
            {
                pScreenManager_4FF7C8->field_36_flags &= ~1u;
            }

            // When no movie is playing start the next one
            if (sMovie_ref_count_9F309C == 0)
            {
                ao_new<Movie>(
                    field_14_movie_id_3,
                    field_10_movie_pos_3,
                    static_cast<s8>(field_30_movie_flag_3),
                    field_32_movie_flags_3,
                    field_34_movie_vol_3);

                field_28_changeEffect = CameraSwapEffects::ePlay1FMV_5;
                field_3C_movie_bPutDispEnv = field_32_movie_flags_3;
            }
            break;

        case CameraSwapEffects::ePlay3FMVs_10:
            if (field_2A_current_slice < 1)
            {
                field_2A_current_slice++;
            }
            else
            {
                pScreenManager_4FF7C8->field_36_flags &= ~1u;
            }

            // When no movie is playing start the next one
            if (sMovie_ref_count_9F309C == 0)
            {
                ao_new<Movie>(
                    field_1C_movie_id_2,
                    field_18_movie_pos_2,
                    static_cast<s8>(field_36_movie_flag_2),
                    field_38_movie_flags_2,
                    field_3A_movie_vol_2);

                field_28_changeEffect = CameraSwapEffects::ePlay2FMVs_9;
                field_3C_movie_bPutDispEnv = field_38_movie_flags_2;
            }
            break;

        default:
            break;
    }
}

} // namespace AO
