#include "stdafx.h"
#include "GasCountDown.hpp"
#include "../relive_lib/Function.hpp"
#include "../relive_lib/GameObjects/Alarm.hpp"
#include "../relive_lib/SwitchStates.hpp"
#include "../relive_lib/Events.hpp"
#include "Sfx.hpp"
#include "../relive_lib/GameObjects/DeathGas.hpp"
#include "../relive_lib/GameObjects/ScreenManager.hpp"
#include "../relive_lib/GameType.hpp"

s32 gDeathGasTimer = 0;
bool gDeathGasOn = false;

// hardcoded values for the boardroom in AO
constexpr u32 kGasCountDownSwitchIdAO = 70;
constexpr u32 kGasCountdownTimeAO = 3600;

GasCountDown::GasCountDown(relive::Path_GasCountDown* pTlv, const Guid& tlvInfo)
    : BaseGameObject(true, 0)
{
    SetType(ReliveTypes::eGasCountDown);
    mTlvId = tlvInfo;

    mPal = ResourceManagerWrapper::LoadPal(PalId::LedFont_Red);
    mFontContext.LoadFontType(FontType::LcdFont);
    mFont.Load(5, mPal, &mFontContext);
    SetDrawable(true);
    gObjListDrawables->Push_Back(this);

    mGasXPos = FP_GetExponent(FP_FromInteger(pTlv->mTopLeftX) - gScreenManager->CamXPos());
    mGasYPos = FP_GetExponent(FP_FromInteger(pTlv->mTopLeftY) - gScreenManager->CamYPos());

    gDeathGasOn = false;

    mStartTimerSwitchId = pTlv->mStartTimerSwitchId;

    if (GetGameType() == GameType::eAo)
    {
        mGasTimeLeftSecs = kGasCountdownTimeAO / 30;
        mStopTimerSwitchId = kGasCountDownSwitchIdAO;
        mGasCountdownTimer = kGasCountdownTimeAO;
    }
    else
    {
        mGasCountdownTimer = pTlv->mGasCountdownTimer;
        mStopTimerSwitchId = pTlv->mStopTimerSwitchId;
        if (gDeathGasTimer)
        {
            mGasTimeLeftSecs = static_cast<s16>((mGasCountdownTimer - (sGnFrame - gDeathGasTimer)) / 30);
            if (mGasTimeLeftSecs < 0)
            {
                mGasTimeLeftSecs = 0;
            }

            relive_new Alarm(mGasCountdownTimer, 0, 0, Layer::eLayer_Above_FG1_39);
        }
        else
        {
            mGasTimeLeftSecs = mGasCountdownTimer / 30;
        }
    }
}

GasCountDown::~GasCountDown()
{
    gObjListDrawables->Remove_Item(this);
    GetMap().TLV_Reset(mTlvId);
}

void GasCountDown::VScreenChanged()
{
    SetDead(true);
    if (GetMap().LevelChanged() || GetMap().PathChanged())
    {
        gDeathGasTimer = 0;
    }
}

void GasCountDown::VUpdate()
{
    if (EventGet(Event::kEventDeathReset))
    {
        SetDead(true);
    }

    if (EventGet(Event::kEventDeathResetEnd))
    {
        gDeathGasTimer = 0;
        gDeathGasOn = false;
    }

    // Enable
    if (!gDeathGasTimer && SwitchStates_Get(mStartTimerSwitchId) && !SwitchStates_Get(mStopTimerSwitchId))
    {
        gDeathGasTimer = sGnFrame;
        relive_new Alarm(mGasCountdownTimer, 0, 0, Layer::eLayer_Above_FG1_39);
    }

    if (!gDeathGasTimer)
    {
        // Off/idle
        mGasTimeLeftSecs = mGasCountdownTimer / 30;
    }
    else
    {
        // Running
        if (SwitchStates_Get(mStopTimerSwitchId))
        {
            gDeathGasTimer = 0;
            return;
        }

        if (EventGet(Event::kEventResetting))
        {
            gDeathGasTimer++;
        }

        const s32 oldTimer = mGasTimeLeftSecs;
        const s32 newTimer = (mGasCountdownTimer - (static_cast<s32>(sGnFrame) - gDeathGasTimer)) / 30;
        mGasTimeLeftSecs = static_cast<s16>(newTimer);
        if (oldTimer != mGasTimeLeftSecs && mGasTimeLeftSecs > 0)
        {
            SFX_Play_Pitch(relive::SoundEffects::RedTick, 55, -1000);
        }
    }

    DealDamage();
}

void GasCountDown::DealDamage()
{
    // This value will re-calc per frame becoming a larger and larger
    // negative number eventually.
    if (mGasTimeLeftSecs < 0)
    {
        // Ensure a few frames have passed before we gas everyone
        if (mGasTimeLeftSecs <= -3)
        {
            GetAbe()->VTakeDamage(this);
            for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
            {
                BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(i);
                if (!pObj)
                {
                    break;
                }

                if (pObj->Type() == ReliveTypes::eMudokon)
                {
                    pObj->VTakeDamage(this);
                }
            }
        }
        // Clamp to 0 anytime below 0
        mGasTimeLeftSecs = 0;
    }

    if (!gDeathGasOn && mGasTimeLeftSecs <= 0)
    {
        gDeathGasOn = true;
        if (!gDeathGasCount)
        {
            relive_new DeathGas(Layer::eLayer_Above_FG1_39, 2);
        }
    }
}

void GasCountDown::VRender(OrderingTable& ot)
{
    char_type text[128] = {}; // Bigger buffer to handle large numbers or negative numbers causing a buffer overflow/crash.
    sprintf(text, "%02d:%02d", mGasTimeLeftSecs / 60, mGasTimeLeftSecs % 60);
    const auto textWidth = mFont.MeasureTextWidth(text);

    mFont.DrawString(
        ot,
        text,
        mGasXPos,
        mGasYPos,
        relive::TBlendModes::eBlend_1,
        1,
        0,
        Layer::eLayer_BeforeWell_22,
        127,
        127,
        127,
        0,
        FP_FromInteger(1),
        textWidth + mGasXPos,
        gDisableFontFlicker ? 0 : 50);
}