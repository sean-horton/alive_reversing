#include "stdafx.h"
#include "BaseAnimatedWithPhysicsGameObject.hpp"
//#include "Function.hpp"
#include "MapWrapper.hpp"
//#include "Map.hpp"
//#include "Game.hpp"
//#include "stdlib.hpp"
#include "../relive_lib/Shadow.hpp"
#include "../relive_lib/ScreenManager.hpp"
//#include "ShadowZone.hpp"
//#include "BaseAliveGameObject.hpp"
//#include "AnimResources.hpp"
#include "Sfx.hpp"
#include "Particle.hpp"
#include "../AliveLibAE/Grid.hpp"
#include "../relive_lib/GameType.hpp"
#include "ShadowZone.hpp"

DynamicArrayT<BaseGameObject>* gObjListDrawables;

void BaseAnimatedWithPhysicsGameObject::MakeArray()
{
    gObjListDrawables = relive_new DynamicArrayT<BaseGameObject>(80);
}

void BaseAnimatedWithPhysicsGameObject::FreeArray()
{
    relive_delete gObjListDrawables;
    gObjListDrawables = nullptr;
}

BaseAnimatedWithPhysicsGameObject::BaseAnimatedWithPhysicsGameObject(s16 resourceArraySize)
    : IBaseAnimatedWithPhysicsGameObject(resourceArraySize)
{
    mVisualFlags.Clear(VisualFlags::eDoPurpleLightEffect);
    mVisualFlags.Set(VisualFlags::eApplyShadowZoneColour);

    mCurrentPath = GetMap().mCurrentPath;
    mCurrentLevel = GetMap().mCurrentLevel;
	
    mVelX = FP_FromInteger(0);
    mVelY = FP_FromInteger(0);

    mXPos = FP_FromInteger(0);
    mYPos = FP_FromInteger(0);

	// TODO: This can be removed if everything uses the tint table or passes down the RGB
	if (GetGameType() == GameType::eAe)
	{
    	mRGB.SetRGB(127, 127, 127);
	}
	else
	{
		mRGB.SetRGB(105, 105, 105);
	}
	
    mBaseGameObjectFlags.Clear(BaseGameObject::eInteractive_Bit8);
    mBaseGameObjectFlags.Clear(BaseGameObject::eCanExplode_Bit7);

    mBaseGameObjectFlags.Set(BaseGameObject::eDrawable_Bit4);
    mBaseGameObjectFlags.Set(BaseGameObject::eIsBaseAnimatedWithPhysicsObj_Bit5);

    mSpriteScale = FP_FromInteger(1);

    mScale = Scale::Fg;
	
    mXOffset = 0;
	
	// TODO: factor this out, not yet known why AO needs an offset of 5
	if (GetGameType() == GameType::eAe)
	{
    	mYOffset = 0;
	}
	else
	{
		mYOffset = 5;
	}
	
    mShadow = nullptr;
}

BaseAnimatedWithPhysicsGameObject::~BaseAnimatedWithPhysicsGameObject()
{
    if (!mBaseGameObjectFlags.Get(BaseGameObject::eListAddFailed_Bit1))
    {
        if (mBaseGameObjectFlags.Get(BaseGameObject::eDrawable_Bit4))
        {
            gObjListDrawables->Remove_Item(this);
            mAnim.VCleanUp();
        }

        delete mShadow;
    }
}

void BaseAnimatedWithPhysicsGameObject::VRender(PrimHeader** ppOt)
{
    if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
    {
        // Only render if in the active level, path and camera
        if (GetMap().mCurrentPath == mCurrentPath
            && GetMap().mCurrentLevel == mCurrentLevel
            && Is_In_Current_Camera() == CameraPos::eCamCurrent_0)
        {
            mAnim.field_14_scale = mSpriteScale;

            s16 r = mRGB.r;
            s16 g = mRGB.g;
            s16 b = mRGB.b;

            const PSX_RECT boundingRect = VGetBoundingRect();

            if (mVisualFlags.Get(VisualFlags::eApplyShadowZoneColour))
            {
                ShadowZone::ShadowZones_Calculate_Colour(
                    FP_GetExponent(mXPos),         // Left side
                    (boundingRect.y + boundingRect.h) / 2, // Middle of Height
                    mScale,
                    &r,
                    &g,
                    &b);
            }

            mAnim.mRed = static_cast<u8>(r);
            mAnim.mGreen = static_cast<u8>(g);
            mAnim.mBlue = static_cast<u8>(b);

            if (GetGameType() == GameType::eAe)
            {
                mAnim.VRender(
                    FP_GetExponent((FP_FromInteger(mXOffset) + mXPos - pScreenManager->CamXPos())),
                    FP_GetExponent((FP_FromInteger(mYOffset) + mYPos - pScreenManager->CamYPos())),
                    ppOt,
                    0,
                    0);
            }
            else
            {
                mAnim.VRender(
                    FP_GetExponent((FP_FromInteger(pScreenManager->mCamXOff + mXOffset))
                                   + mXPos - pScreenManager->mCamPos->x),
                    FP_GetExponent((FP_FromInteger(pScreenManager->mCamYOff + mYOffset))
                                   + mYPos - pScreenManager->mCamPos->y),
                    ppOt,
                    0,
                    0);
            }

            PSX_RECT frameRect = {};
            mAnim.Get_Frame_Rect(&frameRect);
            pScreenManager->InvalidateRectCurrentIdx(
                frameRect.x,
                frameRect.y,
                frameRect.w,
                frameRect.h);

            if (mShadow)
            {
                mShadow->Calculate_Position(
                    mXPos,
                    mYPos,
                    &frameRect,
                    mSpriteScale,
                    mScale);
                mShadow->Render(ppOt);
            }
        }
    }
}

void BaseAnimatedWithPhysicsGameObject::Animation_Init(const AnimResource& res)
{
    if (mAnim.Init(res, this))
    {
        if (mSpriteScale == FP_FromInteger(1))
        {
            mAnim.mRenderLayer = Layer::eLayer_27;
        }
        else
        {
            mAnim.mRenderLayer = Layer::eLayer_8;
            mScale = Scale::Bg;
        }

        const bool added = gObjListDrawables->Push_Back(this) ? true : false;
        if (added)
        {
            mAnim.mRenderMode = TPageAbr::eBlend_0;
            mAnim.mFlags.Clear(AnimFlags::eBit16_bBlending);
            mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);
        }
        else
        {
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            mBaseGameObjectFlags.Set(BaseGameObject::eListAddFailed_Bit1);
        }
    }
    else
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eListAddFailed_Bit1);
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

CameraPos BaseAnimatedWithPhysicsGameObject::Is_In_Current_Camera()
{
    const PSX_RECT rect = VGetBoundingRect();
    return GetMap().Rect_Location_Relative_To_Active_Camera(&rect);
}

void BaseAnimatedWithPhysicsGameObject::DeathSmokeEffect(bool bPlaySound)
{
    // note: mudokons used % 4
    if (!(sGnFrame % 5))
    {
        New_Smoke_Particles(
            mXPos + (FP_FromInteger(Math_RandomRange(-24, 24)) * mSpriteScale),
            mYPos - FP_FromInteger(6),
            mSpriteScale / FP_FromInteger(2),
            2,
            128u, 128u, 128u);

        if (bPlaySound == true)
        {
            SFX_Play_Pitch(relive::SoundEffects::Vaporize, 25, FP_GetExponent(FP_FromInteger(2200) * mSpriteScale));
        }
    }
}

void BaseAnimatedWithPhysicsGameObject::VOnCollisionWith(PSX_Point xy, PSX_Point wh, DynamicArrayT<BaseGameObject>* pObjList, TCollisionCallBack pFn)
{
    if (pObjList)
    {
        for (s32 i = 0; i < pObjList->Size(); i++)
        {
            BaseGameObject* pObjIter = pObjList->ItemAt(i);
            if (!pObjIter)
            {
                break;
            }

            if (pObjIter->mBaseGameObjectFlags.Get(BaseGameObject::eIsBaseAnimatedWithPhysicsObj_Bit5))
            {
                if (pObjIter->mBaseGameObjectFlags.Get(BaseGameObject::eDrawable_Bit4))
                {
                    BaseAnimatedWithPhysicsGameObject* pObj = static_cast<BaseAnimatedWithPhysicsGameObject*>(pObjIter);
                    const PSX_RECT bRect = pObj->VGetBoundingRect();
                    if (xy.x <= bRect.w && wh.x >= bRect.x && wh.y >= bRect.y && xy.y <= bRect.h)
                    {
						// NOTE: AO ignored scale here
						if (GetGameType() == GameType::eAo || (GetGameType() == GameType::eAe && mScale == pObj->mScale))
						{
	                        if (!(this->*(pFn))(pObj))
	                        {
	                            break;
	                        }
						}
                    }
                }
            }
        }
    }
}

s16 BaseAnimatedWithPhysicsGameObject::VIsObjNearby(FP radius, BaseAnimatedWithPhysicsGameObject* pOtherObj)
{
    FP distance = FP_Abs(pOtherObj->mXPos - mXPos);
	// TODO: Factor out
	if (GetGameType() == GameType::eAo)
	{
 		if (distance > FP_FromInteger(400))
    	{
        	distance += ScaleToGridSize(mSpriteScale) - FP_FromInteger(656);
    	}	
	}
    return distance <= radius;
}

s16 BaseAnimatedWithPhysicsGameObject::VIsObj_GettingNear_On_X(BaseAnimatedWithPhysicsGameObject* pOther)
{
    if (pOther->mXPos < mXPos && pOther->mVelX > mVelX)
    {
        // Its before our xpos but its velocity is moving towards our xpos!
        return TRUE;
    }

    if (pOther->mXPos > mXPos && pOther->mVelX < mVelX)
    {
        // Its after our xpos but its velocity is moving towards our xpos!
        return TRUE;
    }

    // Not heading our way
    return FALSE;
}

// Muds use this to face "away" from Abe when stood on the same grid block. Also used to follow Abe in the correct direction etc.
s16 BaseAnimatedWithPhysicsGameObject::VIsFacingMe(BaseAnimatedWithPhysicsGameObject* pOther)
{
    if (pOther->mXPos == mXPos
        && pOther->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        // They are in the same spot as us, so they can only be facing us if they are NOT facing the same way.
        // This seems strange but its what causes muds to keep changing direction if you turn while you are stood in the same grid as them.
        return TRUE;
    }
    else if (pOther->mXPos > mXPos && !mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        // They are to the right of us and facing left
        return TRUE;
    }
    else if (pOther->mXPos < mXPos && mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        // They are to the left of using and facing right
        return TRUE;
    }

    return FALSE;
}

// This is how Scrabs, Fleeches (and probably other stuff) know you are on the same "floor"
s16 BaseAnimatedWithPhysicsGameObject::VOnSameYLevel(BaseAnimatedWithPhysicsGameObject* pOther)
{
    // Get bounding rects
    const PSX_RECT ourRect = VGetBoundingRect();
    const PSX_RECT theirRect = pOther->VGetBoundingRect();

    // Get mid Y of each
    const s32 theirMidY = (theirRect.h + theirRect.y) / 2;
    const s32 ourMidY = (ourRect.h + ourRect.y) / 2;

    if (theirMidY <= ourRect.h && theirMidY >= ourRect.y)
    {
        return TRUE;
    }

    if (ourMidY <= theirRect.h && ourMidY >= theirRect.y)
    {
        return TRUE;
    }

    return FALSE;
}

void BaseAnimatedWithPhysicsGameObject::VStackOnObjectsOfType(ReliveTypes typeToFind)
{
    static const s16 offsets[6] = {
        0, 3, -3, 6, -6, 2};

    s32 array_idx = 0;
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->Type() == typeToFind && pObj != this)
        {
            array_idx++;
            if (array_idx >= ALIVE_COUNTOF(offsets))
            {
                array_idx = 0;
            }
        }
    }

	// NOTE: AO ignored scale here
	if (GetGameType() == GameType::eAe)
	{
    	mXOffset = FP_GetExponent(FP_FromInteger(offsets[array_idx]) * mSpriteScale);
	}
	else
	{
        mXOffset = offsets[array_idx];
	}
}

void BaseAnimatedWithPhysicsGameObject::VOnPickUpOrSlapped()
{
    // Empty
}

void BaseAnimatedWithPhysicsGameObject::VOnThrowableHit(BaseGameObject* /*pFrom*/)
{
    // Empty
}

PSX_RECT BaseAnimatedWithPhysicsGameObject::VGetBoundingRect()
{
    const PerFrameInfo* pAnimFrameHeader = mAnim.Get_FrameHeader(-1);

    PSX_RECT rect = {};

    // TODO: don't narrow the types
    rect.x = static_cast<s16>(pAnimFrameHeader->mBoundMin.x);
    rect.y = static_cast<s16>(pAnimFrameHeader->mBoundMin.y);
    rect.w = static_cast<s16>(pAnimFrameHeader->mBoundMax.x);
    rect.h = static_cast<s16>(pAnimFrameHeader->mBoundMax.y);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        std::swap(rect.x, rect.w);
        rect.x = -rect.x;
        rect.w = -rect.w;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit6_FlipY))
    {
        std::swap(rect.y, rect.h);
        rect.y = -rect.y;
        rect.h = -rect.h;
    }

    rect.x = FP_GetExponent((FP_FromInteger(rect.x) * mSpriteScale));
    rect.y = FP_GetExponent((FP_FromInteger(rect.y) * mSpriteScale));
    rect.w = FP_GetExponent((FP_FromInteger(rect.w) * mSpriteScale));
    rect.h = FP_GetExponent((FP_FromInteger(rect.h) * mSpriteScale));

    const s16 xpos = FP_GetExponent(mXPos);
    const s16 ypos = FP_GetExponent(mYPos);

    rect.x += xpos;
    rect.y += ypos;
    rect.w += xpos;
    rect.h += ypos;

    return rect;
}

void BaseAnimatedWithPhysicsGameObject::SetTint(const TintEntry* pTintArray, EReliveLevelIds level_id)
{
    while (pTintArray->field_0_level != level_id)
    {
        if (pTintArray->field_0_level == level_id || pTintArray->field_0_level == EReliveLevelIds::eNone)
        {
            break;
        }
        pTintArray++;
    }

    mRGB.SetRGB(pTintArray->field_1_r, pTintArray->field_2_g, pTintArray->field_3_b);
}

// AO only
BaseAnimatedWithPhysicsGameObject::BetweenCamPos BaseAnimatedWithPhysicsGameObject::BetweenCameras_418500()
{
    // TODO: Try to understand how the hell these calcs are supposed to work
    const s32 xPosMinusHalfCameraSpace = FP_GetExponent(mXPos - FP_FromInteger(512 / 2));
    if (xPosMinusHalfCameraSpace / 512 % 2)
    {
        return BetweenCamPos::Left_1;
    }
    // TODO :This seems wrong, won't it always be false ??
    else if (FP_FromInteger(xPosMinusHalfCameraSpace % 512) > FP_FromInteger(640))
    {
        return BetweenCamPos::Right_2;
    }
    else
    {
        return BetweenCamPos::None_0;
    }
}
