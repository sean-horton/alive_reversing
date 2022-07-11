#include "stdafx_ao.h"
#include "Function.hpp"
#include "MotionDetector.hpp"
#include "stdlib.hpp"
#include "ResourceManager.hpp"
#include "SwitchStates.hpp"
#include "Sfx.hpp"
#include "../relive_lib/Events.hpp"
#include "CameraSwapper.hpp"
#include "Abe.hpp"
#include "DDCheat.hpp"
#include "Game.hpp"
#include "Alarm.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "Sys_common.hpp"

namespace AO {

#undef min
#undef max

MotionDetector::MotionDetector(Path_MotionDetector* pTlv, s32 tlvInfo)
{
    mBaseGameObjectTypeId = ReliveTypes::eMotionDetector;
    const AnimRecord rec = AO::AnimRec(AnimId::MotionDetector_Flare);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
    Animation_Init(AnimId::MotionDetector_Flare, ppRes);
    mAnim.mFlags.Set(AnimFlags::eBit7_SwapXY);
    mAnim.mRenderMode = TPageAbr::eBlend_1;
    mAnim.mRenderLayer = Layer::eLayer_Foreground_36;
    mYOffset = 0;
    mRGB.SetRGB(64, 0, 0);
    field_160_bObjectInLaser = 0;
    field_F6_bDontComeBack = 1;
    field_E4_tlvInfo = tlvInfo;

    if (pTlv->field_18_scale == Scale_short::eHalf_1)
    {
        mSpriteScale = FP_FromDouble(0.5);
    }
    else
    {
        mSpriteScale = FP_FromInteger(1);
    }

    field_F8_top_left_x = FP_FromInteger(pTlv->mTopLeft.x);
    field_100_bottom_right_x = FP_FromInteger(pTlv->mBottomRight.x);

    field_FC_top_left_y = FP_FromInteger(pTlv->mTopLeft.y);
    field_104_bottom_right_y = FP_FromInteger(pTlv->mBottomRight.y);

    mXPos = FP_FromInteger(pTlv->field_1A_device_x);
    mYPos = FP_FromInteger(pTlv->field_1C_device_y);

    field_15C_speed = FP_FromRaw(pTlv->field_1E_speed_x256 << 8);

    const AnimRecord& laserRec = AO::AnimRec(AnimId::MotionDetector_Laser);
    u8** ppResLaser = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, laserRec.mResourceId, 1, 0);
    if (pTlv->field_20_initial_move_direction == Path_MotionDetector::InitialMoveDirection::eRight_0)
    {
        
        field_E8_state = States::eMoveRight_0;
        auto pMotionDetectors = relive_new MotionDetectorLaser();
        if (pMotionDetectors)
        {
            pMotionDetectors->mBaseGameObjectTypeId = ReliveTypes::eRedLaser;
            
            pMotionDetectors->Animation_Init(AnimId::MotionDetector_Laser, ppResLaser);
            
            pMotionDetectors->mAnim.mRenderMode = TPageAbr::eBlend_1;
            pMotionDetectors->mAnim.mRenderLayer = Layer::eLayer_Foreground_36;

            pMotionDetectors->mXPos = field_F8_top_left_x;
            pMotionDetectors->mYPos = field_104_bottom_right_y;

            pMotionDetectors->mSpriteScale = mSpriteScale;
            pMotionDetectors->mYOffset = 0;
            field_108_pLaser = pMotionDetectors;
        }
    }
    else if (pTlv->field_20_initial_move_direction == Path_MotionDetector::InitialMoveDirection::eLeft_1)
    {
        field_E8_state = States::eMoveLeft_2;
        auto pMotionDetectors = relive_new MotionDetectorLaser();
        if (pMotionDetectors)
        {
            pMotionDetectors->mBaseGameObjectTypeId = ReliveTypes::eRedLaser;
            
            pMotionDetectors->Animation_Init(AnimId::MotionDetector_Laser, ppResLaser);
            
            pMotionDetectors->mAnim.mRenderMode = TPageAbr::eBlend_1;
            pMotionDetectors->mAnim.mRenderLayer = Layer::eLayer_Foreground_36;
            pMotionDetectors->mXPos = field_100_bottom_right_x;
            pMotionDetectors->mYPos = field_104_bottom_right_y;
            pMotionDetectors->mSpriteScale = mSpriteScale;
            pMotionDetectors->mYOffset = 0;
            field_108_pLaser = pMotionDetectors;
        }
    }
    else
    {
        ALIVE_FATAL("couldn't find start move direction for motion detector");
    }

    field_108_pLaser->mBaseGameObjectRefCount++;

    field_F0_disable_switch_id = pTlv->field_24_disable_switch_id;

    field_108_pLaser->mAnim.mFlags.Set(AnimFlags::eBit3_Render, SwitchStates_Get(field_F0_disable_switch_id) == 0);

    mAnim.mFlags.Set(AnimFlags::eBit3_Render, pTlv->field_22_draw_flare == Choice_short::eYes_1);

    field_F4_alarm_duration = pTlv->field_28_alarm_duration;

    field_F2_alarm_switch_id = pTlv->field_26_alarm_switch_id;
}

void MotionDetector::SetDontComeBack(s16 bDontComeBack)
{
    field_F6_bDontComeBack = bDontComeBack;
}

MotionDetector::~MotionDetector()
{
    if (field_F6_bDontComeBack)
    {
        Path::TLV_Reset(field_E4_tlvInfo, -1, 0, 0);
    }
    else
    {
        Path::TLV_Reset(field_E4_tlvInfo, -1, 0, 1);
    }

    if (field_108_pLaser)
    {
        field_108_pLaser->mBaseGameObjectRefCount--;
        field_108_pLaser->mBaseGameObjectFlags.Set(Options::eDead);
    }
}

void MotionDetector::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

void MotionDetector::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(Options::eDead);
    }

    if (!sNumCamSwappers_507668)
    {
        if (SwitchStates_Get(field_F0_disable_switch_id))
        {
            field_108_pLaser->mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
        }
        else
        {
            field_108_pLaser->mAnim.mFlags.Set(AnimFlags::eBit3_Render);

            const PSX_RECT laserRect = field_108_pLaser->VGetBoundingRect();

            field_160_bObjectInLaser = FALSE;

            for (s32 i = 0; i < gBaseAliveGameObjects_4FC8A0->Size(); i++)
            {
                BaseAliveGameObject* pObj = gBaseAliveGameObjects_4FC8A0->ItemAt(i);
                if (!pObj)
                {
                    break;
                }

                if (pObj->mBaseGameObjectTypeId != ReliveTypes::eTimedMine)
                {
                    const PSX_RECT objRect = pObj->VGetBoundingRect();

                    if (laserRect.x <= (objRect.w - 8) && laserRect.w >= (objRect.x + 8) && laserRect.h >= objRect.y && laserRect.y <= objRect.h && pObj->mSpriteScale == mSpriteScale)
                    {
                        if (pObj == sActiveHero)
                        {
                            if (sGnFrame % 2)
                            {
                                SfxPlayMono(SoundEffect::Zap2_58, 45, 0);
                            }
                        }

                        bool alarm = false;
                        if (pObj->mBaseGameObjectTypeId == ReliveTypes::eAbe)
                        {
                            if (pObj->mCurrentMotion != eAbeMotions::Motion_0_Idle_423520 && pObj->mCurrentMotion != eAbeMotions::Motion_19_CrouchIdle_4284C0 && pObj->mCurrentMotion != eAbeMotions::Motion_66_LedgeHang_428D90 && pObj->mCurrentMotion != eAbeMotions::Motion_62_LoadedSaveSpawn_45ADD0 && pObj->mCurrentMotion != eAbeMotions::Motion_60_Dead_42C4C0 && !sDDCheat_FlyingEnabled_50771C)
                            {
                                alarm = true;
                            }
                        }
                        else if (FP_GetExponent(pObj->mVelX) || FP_GetExponent(pObj->mVelY))
                        {
                            alarm = true;
                        }

                        if (alarm)
                        {
                            field_160_bObjectInLaser = TRUE;

                            if (alarmInstanceCount_5076A8 == 0)
                            {
                                relive_new Alarm(
                                    field_F4_alarm_duration,
                                    field_F2_alarm_switch_id,
                                    0,
                                    Layer::eLayer_Above_FG1_39);

                                if (pObj == sActiveHero)
                                {
                                    Mudokon_SFX(MudSounds::eOops_16, 0, 0, nullptr);
                                }
                            }
                        }
                    }
                }
            }


            switch (field_E8_state)
            {
                case States::eMoveRight_0:
                    if (field_108_pLaser->mXPos >= field_100_bottom_right_x)
                    {
                        field_E8_state = States::eWaitThenMoveLeft_1;
                        field_EC_timer = sGnFrame + 15;
                        SfxPlayMono(SoundEffect::MenuNavigation_61, 0);
                    }
                    else
                    {
                        field_108_pLaser->mXPos += field_15C_speed;
                    }
                    break;

                case States::eWaitThenMoveLeft_1:
                    if (static_cast<s32>(sGnFrame) > field_EC_timer)
                    {
                        field_E8_state = States::eMoveLeft_2;
                    }
                    break;

                case States::eMoveLeft_2:
                    if (field_108_pLaser->mXPos <= field_F8_top_left_x)
                    {
                        field_E8_state = States::eWaitThenMoveRight_3;
                        field_EC_timer = sGnFrame + 15;
                        SfxPlayMono(SoundEffect::MenuNavigation_61, 0);
                    }
                    else
                    {
                        field_108_pLaser->mXPos -= field_15C_speed;
                    }
                    break;

                case States::eWaitThenMoveRight_3:
                    if (static_cast<s32>(sGnFrame) > field_EC_timer)
                    {
                        field_E8_state = States::eMoveRight_0;
                    }
                    break;

                default:
                    return;
            }
        }
    }
}

void MotionDetector::VRender(PrimHeader** ppOt)
{
    mXPos += FP_FromInteger(11);
    BaseAnimatedWithPhysicsGameObject::VRender(ppOt);
    mXPos -= FP_FromInteger(11);

    if (!SwitchStates_Get(field_F0_disable_switch_id))
    {
        const s16 screen_top = FP_GetExponent(pScreenManager->mCamPos->y - FP_FromInteger(pScreenManager->mCamYOff));

        const s16 screen_left = FP_GetExponent(pScreenManager->mCamPos->x - FP_FromInteger(pScreenManager->mCamXOff));

        const PSX_RECT bLaserRect = field_108_pLaser->VGetBoundingRect();

        const s16 x0 = static_cast<s16>(PsxToPCX(FP_GetExponent(mXPos) - screen_left, 11));
        const s16 y0 = FP_GetExponent(mYPos) - screen_top;
        const s16 y1 = FP_GetExponent(field_108_pLaser->mYPos) - screen_top;
        const s16 y2 = y1 + bLaserRect.y - bLaserRect.h;
        const s16 x1 = static_cast<s16>(PsxToPCX(FP_GetExponent(field_108_pLaser->mXPos) - screen_left, 11));

        Poly_F3* pPrim = &field_10C_prims[gPsxDisplay.mBufferIndex];
        PolyF3_Init(pPrim);

        SetXY0(pPrim, x0, y0);
        SetXY1(pPrim, x1, y1);
        SetXY2(pPrim, x1, y2);

        SetRGB0(pPrim, 64, 0, 0);

        // Add triangle
        Poly_Set_SemiTrans(&pPrim->mBase.header, TRUE);
        OrderingTable_Add(OtLayer(ppOt, mAnim.mRenderLayer), &pPrim->mBase.header);

        // Add tpage
        Init_SetTPage(&field_13C_tPage[gPsxDisplay.mBufferIndex], 0, 0, PSX_getTPage(TPageMode::e16Bit_2, field_160_bObjectInLaser != 0 ? TPageAbr::eBlend_1 : TPageAbr::eBlend_3, 0, 0)); // When detected transparency is off, gives the "solid red" triangle
        OrderingTable_Add(OtLayer(ppOt, mAnim.mRenderLayer), &field_13C_tPage[gPsxDisplay.mBufferIndex].mBase);

        pScreenManager->InvalidateRectCurrentIdx(
            std::min(x0, std::min(x1, x1)),
            std::min(y0, std::min(y1, y2)),
            std::max(x0, std::max(x1, x1)),
            std::max(y0, std::max(y1, y2)));
    }
}

} // namespace AO
