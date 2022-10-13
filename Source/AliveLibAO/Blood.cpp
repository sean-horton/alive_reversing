#include "stdafx_ao.h"
#include "Function.hpp"
#include "Blood.hpp"
#include "ResourceManager.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "Game.hpp"
#include "Math.hpp"
#include "Map.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "Primitives_common.hpp"
#include <algorithm>

#undef min
#undef max

namespace AO {

void Blood_ForceLink()
{ }

Blood::Blood(FP xpos, FP ypos, FP xOff, FP yOff, FP scale, s32 count)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    mSpriteScale = scale;

    mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::BloodDrop));
    Animation_Init(GetAnimRes(AnimId::BloodDrop));

    mAnim.mFlags.Clear(AnimFlags::eSemiTrans);
    mAnim.mRed = 127;
    mAnim.mGreen = 127;
    mAnim.mBlue = 127;

    if (mSpriteScale == FP_FromInteger(1))
    {
        mOtLayer = Layer::eLayer_Foreground_36;
    }
    else
    {
        mOtLayer = Layer::eLayer_Foreground_Half_17;
    }

    if (mSpriteScale != FP_FromInteger(1))
    {
        mAnim.SetFrame((mAnim.Get_Frame_Count() >> 1) + 1);
    }

    mTotalBloodCount = static_cast<s16>(count);
    mCurrentBloodCount = static_cast<s16>(count);

    mBloodParticle = relive_new BloodParticle[count];
    if (mBloodParticle)
    {
        mUpdateCalls = 0;

        mXPos = xpos - FP_FromInteger(12);
        mYPos = ypos - FP_FromInteger(12);

        mBloodXPos = FP_GetExponent(xpos - FP_FromInteger(12) + FP_FromInteger(pScreenManager->mCamXOff) - pScreenManager->mCamPos->x);
        mBloodYPos = FP_GetExponent(ypos - FP_FromInteger(12) + FP_FromInteger(pScreenManager->mCamYOff) - pScreenManager->mCamPos->y);

        if (mAnim.mFlags.Get(AnimFlags::eIs8Bit))
        {
            mTextureMode = TPageMode::e8Bit_1;
        }
        else if (mAnim.mFlags.Get(AnimFlags::eIs16Bit))
        {
            mTextureMode = TPageMode::e16Bit_2;
        }
        else
        {
            mTextureMode = TPageMode::e4Bit_0;
        }

        u8 u0 = 0;// mAnim.mVramRect.x & 0x3F;
        if (mTextureMode == TPageMode::e8Bit_1)
        {
            u0 = 2 * u0;
        }
        else if (mTextureMode == TPageMode::e4Bit_0)
        {
            u0 = 4 * u0;
        }

        u8 v0 = 0;//mAnim.mVramRect.y & 0xFF;

        const PerFrameInfo* pFrameHeader = mAnim.Get_FrameHeader(-1);

        const s32 frameW = pFrameHeader->mWidth;
        const s32 frameH = pFrameHeader->mHeight;

        mAnim.mFlags.Set(AnimFlags::eBlending);

        for (s32 i = 0; i < mTotalBloodCount; i++)
        {
            for (s32 j = 0; j < 2; j++)
            {
                BloodParticle* pParticle = &mBloodParticle[i];
                Prim_Sprt* pSprt = &pParticle->field_10_prims[j];

                Sprt_Init(pSprt);
                Poly_Set_SemiTrans(&pSprt->mBase.header, 1);

                if (mAnim.mFlags.Get(AnimFlags::eBlending))
                {
                    Poly_Set_Blending(&pSprt->mBase.header, 1);
                }
                else
                {
                    Poly_Set_Blending(&pSprt->mBase.header, 0);

                    SetRGB0(pSprt, mAnim.mRed, mAnim.mGreen, mAnim.mBlue);
                }

                /* TODO: Just set anim ptr
                SetClut(pSprt,
                        static_cast<s16>(
                            PSX_getClut(
                                mAnim.mPalVramXY.x,
                                mAnim.mPalVramXY.y)));
                                */
                SetUV0(pSprt, u0, v0);
                pSprt->field_14_w = static_cast<s16>(frameW - 1);
                pSprt->field_16_h = static_cast<s16>(frameH - 1);
            }
        }
        // Has its own random seed based on the frame counter.. no idea why
        mRandSeed = static_cast<u8>(sGnFrame);

        for (s32 i = 0; i < mCurrentBloodCount; i++)
        {
            mBloodParticle[i].x = FP_FromInteger(mBloodXPos);
            mBloodParticle[i].y = FP_FromInteger(mBloodYPos);

            const FP randX = (FP_FromInteger(gRandomBytes[mRandSeed++]) / FP_FromInteger(16));
            const FP adjustedX = FP_FromDouble(1.3) * (randX - FP_FromInteger(8));
            mBloodParticle[i].mOffX = mSpriteScale * (xOff + adjustedX);

            const FP randY = (FP_FromInteger(gRandomBytes[mRandSeed++]) / FP_FromInteger(16));
            const FP adjustedY = FP_FromDouble(1.3) * (randY - FP_FromInteger(8));
            mBloodParticle[i].mOffY = mSpriteScale * (yOff + adjustedY);
        }
    }
    else
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

void Blood::VUpdate()
{
    if (mUpdateCalls > 0)
    {
        if (mUpdateCalls > 5)
        {
            mCurrentBloodCount -= 10;
        }

        if (mCurrentBloodCount <= 0)
        {
            mCurrentBloodCount = 0;
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            return;
        }

        for (s32 i = 0; i < mCurrentBloodCount; i++)
        {
            mBloodParticle[i].mOffY += FP_FromDouble(1.8);

            mBloodParticle[i].mOffX = mBloodParticle[i].mOffX * FP_FromDouble(0.9);
            mBloodParticle[i].mOffY = mBloodParticle[i].mOffY * FP_FromDouble(0.9);

            mBloodParticle[i].x += mBloodParticle[i].mOffX;
            mBloodParticle[i].y += mBloodParticle[i].mOffY;
        }
    }

    mUpdateCalls++;
}


Blood::~Blood()
{
     relive_delete[] mBloodParticle;
}

void Blood::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

void Blood::VRender(PrimHeader** ppOt)
{
    //const auto bufferIdx = gPsxDisplay.mBufferIndex;
    if (gMap.Is_Point_In_Current_Camera(
            mCurrentLevel,
            mCurrentPath,
            mXPos,
            mYPos,
            0))
    {
        PSX_Point xy = {32767, 32767};
        PSX_Point wh = {-32767, -32767};

        for (s32 i = 0; i < mCurrentBloodCount; i++)
        {
            BloodParticle* pParticle = &mBloodParticle[i];
            Prim_Sprt* pSprt = &pParticle->field_10_prims[gPsxDisplay.mBufferIndex];

            u8 u0 = 0; // mAnim.mVramRect.x & 63;
            if (mTextureMode == TPageMode::e8Bit_1)
            {
                u0 *= 2;
            }
            else if (mTextureMode == TPageMode::e4Bit_0)
            {
                u0 *= 4;
            }

            SetUV0(pSprt, u0, 0 /*static_cast<u8>(mAnim.mVramRect.y)*/);

            const PerFrameInfo* pFrameHeader = mAnim.Get_FrameHeader(-1);

            pSprt->field_14_w = static_cast<s16>(pFrameHeader->mWidth - 1);
            pSprt->field_16_h = static_cast<s16>(pFrameHeader->mHeight - 1);

            const s16 x0 = PsxToPCX(FP_GetExponent(pParticle->x));
            const s16 y0 = FP_GetExponent(pParticle->y);

            SetXY0(pSprt, x0, y0);

            if (!mAnim.mFlags.Get(AnimFlags::eBlending))
            {
                SetRGB0(pSprt, mAnim.mRed, mAnim.mGreen, mAnim.mBlue);
            }

            OrderingTable_Add(OtLayer(ppOt, mOtLayer), &pSprt->mBase.header);

            xy.x = std::min(x0, xy.x);
            xy.y = std::min(y0, xy.y);

            wh.x = std::max(x0, wh.x);
            wh.y = std::max(y0, wh.y);
        }

        /*
        // TODO: Just set the anim ptr
        s16 tpageY = 256;
        if (!mAnim.mFlags.Get(AnimFlags::eBit10_alternating_flag)
            && mAnim.mVramRect.y < 256)
        {
            tpageY = 0;
        }

        const auto tpage = PSX_getTPage(
            mTextureMode,
            TPageAbr::eBlend_0,
            mAnim.mVramRect.x & 0xFFC0,
            tpageY);
        Prim_SetTPage* pTPage = &mTPages[bufferIdx];
        Init_SetTPage(pTPage, 0, 0, tpage);
        OrderingTable_Add(OtLayer(ppOt, mOtLayer), &pTPage->mBase);
        */
    }
}

} // namespace AO
