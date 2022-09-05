#include "stdafx_ao.h"
#include "Function.hpp"
#include "DoorFlame.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "SwitchStates.hpp"
#include "ResourceManager.hpp"
#include "Midi.hpp"
#include "Math.hpp"
#include "Map.hpp"
#include "Sfx.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "CameraSwapper.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "../relive_lib/AnimationUnknown.hpp"

namespace AO {

ALIVE_VAR(1, 0x507734, DoorFlame*, pFlameControllingTheSound_507734, nullptr);

class FireBackgroundGlow final : public BaseAnimatedWithPhysicsGameObject
{
public:
    FireBackgroundGlow(FP xpos, FP ypos, FP scale)
        : BaseAnimatedWithPhysicsGameObject(0)
    {
        mBaseGameObjectTypeId = ReliveTypes::eNone;

        const AnimRecord rec = AO::AnimRec(AnimId::Door_FireBackgroundGlow);
        u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
        Animation_Init(AnimId::Door_FireBackgroundGlow, ppRes);

        mVisualFlags.Set(VisualFlags::eApplyShadowZoneColour);

        mAnim.mFlags.Clear(AnimFlags::eBit16_bBlending);
        mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);
        mAnim.mFlags.Set(AnimFlags::eBit20_use_xy_offset);

        mXPos = xpos;
        mYPos = ypos + FP_FromInteger(4);

        mAnim.mRenderLayer = Layer::eLayer_DoorFlameRollingBallFallingItemPortalClip_Half_12;
        mAnim.mRenderMode = TPageAbr::eBlend_3;

        mAnim.mRed = 100;
        mAnim.mGreen = 100;
        mAnim.mBlue = 63;

        mSpriteScale = scale;

        Calc_Rect();
    }

    virtual void VUpdate() override
    {
        // Empty
    }

    virtual void VRender(PrimHeader** ppOt) override
    {
        if (Is_In_Current_Camera() == CameraPos::eCamCurrent_0)
        {
            mAnim.mRed = static_cast<u8>(mRGB.r);
            mAnim.mGreen = static_cast<u8>(mRGB.g);
            mAnim.mBlue = static_cast<u8>(mRGB.b);

            mAnim.VRender(
                FP_GetExponent(field_E4_xPos),
                FP_GetExponent(field_E8_yPos),
                ppOt,
                FP_GetExponent(field_EC_xOff - field_E4_xPos) + 1,
                FP_GetExponent(field_F0_yOff - field_E8_yPos) + 1);

            PSX_RECT rect = {};
            mAnim.Get_Frame_Rect(&rect);
            pScreenManager->InvalidateRectCurrentIdx(
                rect.x,
                rect.y,
                rect.w,
                rect.h);
        }
    }

    void Calc_Rect()
    {
        PSX_Point xy = {};

        s16 frameW = 0;
        s16 frameH = 0;

        mAnim.Get_Frame_Width_Height(&frameW, &frameH);
        mAnim.Get_Frame_Offset(&xy.x, &xy.y);

        const auto& pCamPos = pScreenManager->mCamPos;
        const FP screenX = FP_FromInteger(pScreenManager->mCamXOff) + mXPos - pCamPos->x;
        const FP screenY = FP_FromInteger(pScreenManager->mCamYOff) + mYPos - pCamPos->y;

        const FP frameWScaled = (FP_FromInteger(frameW) * mSpriteScale);
        const FP frameHScaled = (FP_FromInteger(frameH) * mSpriteScale);

        const s32 offXScaled = FP_GetExponent(FP_FromInteger(xy.x) * mSpriteScale);
        const s32 offYScaled = FP_GetExponent(FP_FromInteger(xy.y) * mSpriteScale);

        // TODO: Refactor PSX <> PC width conversion
        const FP frameWScaled_converted = ((frameWScaled * FP_FromInteger(23)) + FP_FromInteger(20)) / FP_FromInteger(40);
        // Why isn't this converted ??
        //const s16 offXScaled_converted = FP_GetExponent(((FP_FromInteger(offXScaled) * FP_FromInteger(23)) + FP_FromInteger(20)) / FP_FromInteger(40));


        field_E4_xPos = screenX + FP_FromInteger(offXScaled) + FP_FromInteger(Math_NextRandom() % 3);
        field_E8_yPos = screenY + FP_FromInteger(offYScaled) + FP_FromInteger((Math_NextRandom() % 3));
        field_EC_xOff = screenX + FP_FromInteger(offXScaled) + frameWScaled_converted + FP_FromInteger(Math_NextRandom() % 3);
        field_F0_yOff = screenY + FP_FromInteger(offYScaled) + frameHScaled + FP_FromInteger(Math_NextRandom() % 3);
    }

    s32 field_D4[4];

    FP field_E4_xPos;
    FP field_E8_yPos;
    FP field_EC_xOff;
    FP field_F0_yOff;
};
ALIVE_ASSERT_SIZEOF(FireBackgroundGlow, 0xF4);

struct FlameSpark final
{
    FP x;
    FP y;
    FP field_8_off_x;
    FP field_C_off_y;
    s16 field_10_random64;
    s16 field_12_bVisible;
    AnimationUnknown field_14;
};
ALIVE_ASSERT_SIZEOF(FlameSpark, 0x84);

class FlameSparks final : public BaseAnimatedWithPhysicsGameObject
{
public:
    FlameSparks(FP xpos, FP ypos)
        : BaseAnimatedWithPhysicsGameObject(0)
    {
        mBaseGameObjectTypeId = ReliveTypes::eNone;
        const AnimRecord rec = AO::AnimRec(AnimId::ChantOrb_Particle_Small);
        u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
        Animation_Init(AnimId::ChantOrb_Particle_Small, ppRes);
        mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);

        mVisualFlags.Set(VisualFlags::eApplyShadowZoneColour);
        mAnim.mRenderLayer = Layer::eLayer_Foreground_Half_17;

        mXPos = xpos;
        mYPos = ypos;
        field_400_xpos = xpos;
        field_404_ypos = ypos;

        mSpriteScale = FP_FromDouble(0.3);

        for (auto& anim : field_E8_sparks)
        {
            anim.field_14.field_68_anim_ptr = &mAnim;

            anim.field_14.mFlags.Set(AnimFlags::eBit3_Render);
            anim.field_14.mFlags.Set(AnimFlags::eBit16_bBlending);

            const s16 rndLayer = static_cast<s16>(mAnim.mRenderLayer) + Math_RandomRange(-1, 1);
            anim.field_14.mRenderLayer = static_cast<Layer>(rndLayer);
            anim.field_14.field_6C_scale = mSpriteScale;

            anim.x = mXPos;
            anim.y = mYPos;

            anim.field_8_off_x = FP_FromInteger(0);
            anim.field_C_off_y = FP_FromInteger(0);

            anim.field_10_random64 = Math_RandomRange(0, 64);
            anim.field_12_bVisible = 0;
        }

        field_E4_bRender = 0;
    }

    virtual void VUpdate() override
    {
        PSX_RECT rect = {};
        gMap.Get_Camera_World_Rect(CameraPos::eCamCurrent_0, &rect);
        mXPos = FP_FromInteger(rect.w + 16);
        mYPos = FP_FromInteger(rect.y - 16);
        if (field_E4_bRender)
        {
            for (auto& anim : field_E8_sparks)
            {
                anim.field_10_random64--;
                if (anim.field_12_bVisible == 0)
                {
                    if (anim.field_10_random64 <= 0)
                    {
                        anim.field_12_bVisible = 1;
                        anim.field_10_random64 = Math_RandomRange(7, 9);

                        anim.x = field_400_xpos;
                        anim.y = field_404_ypos;

                        anim.field_8_off_x = FP_FromInteger(Math_NextRandom() - 127) / FP_FromInteger(96);
                        anim.field_C_off_y = FP_FromInteger(-Math_NextRandom()) / FP_FromInteger(96);
                    }
                }
                else if (anim.field_10_random64 > 0)
                {
                    anim.x += anim.field_8_off_x;
                    anim.y += anim.field_C_off_y;

                    if (!(anim.field_10_random64 % 3))
                    {
                        anim.field_8_off_x += FP_FromInteger(Math_NextRandom() - 127) / FP_FromInteger(64);
                        anim.field_C_off_y += FP_FromInteger(Math_NextRandom() - 127) / FP_FromInteger(64);
                    }
                }
                else
                {
                    anim.field_12_bVisible = 0;
                    anim.field_10_random64 = Math_RandomRange(90, 240);
                }
            }
        }
    }

    virtual void VRender(PrimHeader** ppOt) override
    {
        if (sNumCamSwappers_507668 == 0)
        {
            if (field_E4_bRender)
            {
                mAnim.mGreen = 32;
                mAnim.mBlue = 32;
                mAnim.mRed = 240;

                const FP_Point* pCamPos = pScreenManager->mCamPos;

                const FP screen_left = pCamPos->x - FP_FromInteger(pScreenManager->mCamXOff);
                const FP screen_right = pCamPos->x + FP_FromInteger(pScreenManager->mCamXOff);
                const FP screen_top = pCamPos->y - FP_FromInteger(pScreenManager->mCamYOff);
                const FP screen_bottom = pCamPos->y + FP_FromInteger(pScreenManager->mCamYOff);

                mAnim.VRender(
                    FP_GetExponent(PsxToPCX(mXPos - screen_left)),
                    FP_GetExponent(mYPos - screen_top),
                    ppOt,
                    0,
                    0);

                PSX_RECT frameRect = {};
                mAnim.Get_Frame_Rect(&frameRect);
                pScreenManager->InvalidateRectCurrentIdx(
                    frameRect.x,
                    frameRect.y,
                    frameRect.w,
                    frameRect.h);

                for (auto& anim : field_E8_sparks)
                {
                    if (anim.field_12_bVisible)
                    {
                        if (anim.x >= screen_left && anim.x <= screen_right)
                        {
                            if (anim.y >= screen_top && anim.y <= screen_bottom)
                            {
                                anim.field_14.VRender(
                                    FP_GetExponent(PsxToPCX(anim.x - screen_left)),
                                    FP_GetExponent(anim.y - screen_top),
                                    ppOt, 0, 0);

                                anim.field_14.GetRenderedSize(&frameRect);
                                pScreenManager->InvalidateRectCurrentIdx(
                                    frameRect.x,
                                    frameRect.y,
                                    frameRect.w,
                                    frameRect.h);
                            }
                        }
                    }
                }
            }
        }
    }

    s16 field_E4_bRender;
    FlameSpark field_E8_sparks[6];
    FP field_400_xpos;
    FP field_404_ypos;
};
ALIVE_ASSERT_SIZEOF(FlameSparks, 0x408);

void DoorFlame::VStopAudio()
{
    if (pFlameControllingTheSound_507734 == this)
    {
        pFlameControllingTheSound_507734 = nullptr;
        SND_Stop_Channels_Mask(mSoundsMask);
    }
}

DoorFlame::~DoorFlame()
{
    if (mFireBackgroundGlow)
    {
        mFireBackgroundGlow->mBaseGameObjectRefCount--;
        mFireBackgroundGlow->mBaseGameObjectFlags.Set(Options::eDead);
        mFireBackgroundGlow = nullptr;
    }

    if (mFlameSparks)
    {
        mFlameSparks->mBaseGameObjectRefCount--;
        mFlameSparks->mBaseGameObjectFlags.Set(Options::eDead);
        mFlameSparks = nullptr;
    }

    VStopAudio();

    Path::TLV_Reset(mTlvInfo, -1, 0, 0);
}

DoorFlame::DoorFlame(relive::Path_DoorFlame* pTlv, const Guid& tlvId)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    mBaseGameObjectTypeId = ReliveTypes::eNone;
    mTlvInfo = tlvId;
    const AnimRecord rec = AO::AnimRec(AnimId::Fire);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
    Animation_Init(AnimId::Fire, ppRes);

    mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);
    mVisualFlags.Set(VisualFlags::eApplyShadowZoneColour);
    mAnim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
    mFrameCount = mAnim.Get_Frame_Count();
    mSwitchId = pTlv->mSwitchId;

    if (pTlv->mScale == relive::reliveScale::eHalf)
    {
        mSpriteScale = FP_FromDouble(0.5);
        mXPos = FP_FromInteger(pTlv->mTopLeftX + 12);
        mYPos = FP_FromInteger(pTlv->mTopLeftY + 15);
    }
    else if (pTlv->mScale == relive::reliveScale::eFull)
    {
        mSpriteScale = FP_FromInteger(1);
        mXPos = FP_FromInteger(pTlv->mTopLeftX + 12);
        mYPos = FP_FromInteger(pTlv->mTopLeftY + 15);
    }

    switch (pTlv->mColour)
    {
        case relive::Path_DoorFlame::Colour::eRed:
            mRGB.r = 127;
            break;
        case relive::Path_DoorFlame::Colour::eGreen:
            mRGB.g = 127;
            break;
        case relive::Path_DoorFlame::Colour::eBlue:
            mRGB.b = 127;
            break;
        
        case relive::Path_DoorFlame::Colour::eDefault:
        default:
            break;
    }

    mFireBackgroundGlow = 0;

    if (SwitchStates_Get(pTlv->mSwitchId))
    {
        mAnim.mFlags.Set(AnimFlags::eBit3_Render);
        mState = States::eEnabled_1;
    }
    else
    {
        mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
        mState = States::eDisabled_0;
    }

    mAnim.mFlags.Set(AnimFlags::eBit2_Animate);
    mRandom = Math_NextRandom() & 1;

    mFlameSparks = relive_new FlameSparks(mXPos, mYPos);
    if (mFlameSparks)
    {
        mFlameSparks->mBaseGameObjectRefCount++;
    }
}

void DoorFlame::VUpdate()
{
    switch (mState)
    {
        case States::eDisabled_0:
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            if (mFlameSparks)
            {
                mFlameSparks->field_E4_bRender = 0;
            }

            if (SwitchStates_Get(mSwitchId))
            {
                mState = States::eEnabled_1;
            }

            if (mFireBackgroundGlow)
            {
                mFireBackgroundGlow->mBaseGameObjectRefCount--;
                mFireBackgroundGlow->mBaseGameObjectFlags.Set(Options::eDead);
                mFireBackgroundGlow = nullptr;
            }
            break;

        case States::eEnabled_1:
            if (!pFlameControllingTheSound_507734)
            {
                pFlameControllingTheSound_507734 = this;
                mSoundsMask = SfxPlayMono(relive::SoundEffects::Fire, 40, 0);
            }

            if (--mRandom <= 0)
            {
                mRandom = 2;
                if (mFireBackgroundGlow)
                {
                    mFireBackgroundGlow->Calc_Rect();
                }
            }

            mAnim.mFlags.Set(AnimFlags::eBit3_Render);
            if (mFlameSparks)
            {
                mFlameSparks->field_E4_bRender = 1;
            }

            if (!SwitchStates_Get(mSwitchId))
            {
                mState = States::eDisabled_0;
            }

            if (!mFireBackgroundGlow)
            {
                mFireBackgroundGlow = relive_new FireBackgroundGlow(mXPos,
                    mYPos + FP_FromInteger(4),
                    FP_FromDouble(0.5));
                if (mFireBackgroundGlow)
                {
                    mFireBackgroundGlow->mBaseGameObjectRefCount++;
                    mFireBackgroundGlow->mRGB = mRGB;
                }
            }
            break;

        default:
            break;
    }

    if (!gMap.Is_Point_In_Current_Camera(
            mCurrentLevel,
            mCurrentPath,
            mXPos,
            mYPos,
            0))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

} // namespace AO
