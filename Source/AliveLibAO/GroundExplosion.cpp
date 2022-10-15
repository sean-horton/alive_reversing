#include "stdafx_ao.h"
#include "Function.hpp"
#include "GroundExplosion.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "ParticleBurst.hpp"
#include "ScreenShake.hpp"
#include "Midi.hpp"
#include "../relive_lib/Events.hpp"
#include "Flash.hpp"
#include "../relive_lib/Particle.hpp"
#include "BaseAliveGameObject.hpp"

namespace AO {

void GroundExplosion::VUpdate()
{
    PSX_RECT rect = {};

    EventBroadcast(kEventShooting, this);
    EventBroadcast(kEventLoudNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    switch (GetAnimation().GetCurrentFrame())
    {
        case 0:
            rect.x = FP_GetExponent(FP_FromInteger(-30) * mObjectScale);
            rect.w = FP_GetExponent(FP_FromInteger(30) * mObjectScale);
            rect.y = FP_GetExponent(FP_FromInteger(-20) * mObjectScale);
            rect.h = FP_GetExponent(FP_FromInteger(20) * mObjectScale);
            DealDamageRect(&rect);
            break;

        case 1:
            rect.x = FP_GetExponent(FP_FromInteger(-50) * mObjectScale);
            rect.w = FP_GetExponent(FP_FromInteger(50) * mObjectScale);
            rect.y = FP_GetExponent(FP_FromInteger(-30) * mObjectScale);
            rect.h = FP_GetExponent(FP_FromInteger(30) * mObjectScale);
            DealDamageRect(&rect);
            break;

        case 2:
            rect.x = FP_GetExponent(FP_FromInteger(-80) * mObjectScale);
            rect.w = FP_GetExponent(FP_FromInteger(80) * mObjectScale);
            rect.y = FP_GetExponent(FP_FromInteger(-40) * mObjectScale);
            rect.h = FP_GetExponent(FP_FromInteger(40) * mObjectScale);
            DealDamageRect(&rect);
            break;

        case 3:
        {
            relive_new ParticleBurst(
                mXPos,
                mYPos,
                20,
                GetSpriteScale(),
                BurstType::eBigRedSparks_3);

            relive_new Flash(Layer::eLayer_Above_FG1_39, 255u, 255u, 255u);

            rect.x = FP_GetExponent(FP_FromInteger(-113) * mObjectScale);
            rect.w = FP_GetExponent(FP_FromInteger(113) * mObjectScale);
            rect.y = FP_GetExponent(FP_FromInteger(-50) * mObjectScale);
            rect.h = FP_GetExponent(FP_FromInteger(50) * mObjectScale);
            DealDamageRect(&rect);
            break;
        }

        case 4:
        {
            relive_new Flash(Layer::eLayer_Above_FG1_39, 255u, 255u, 255u, TPageAbr::eBlend_1, 1);
            break;
        }

        case 7:
        {
            relive_new ParticleBurst(
                mXPos,
                mYPos,
                20,
                GetSpriteScale(),
                BurstType::eBigRedSparks_3);

            relive_new Flash(Layer::eLayer_Above_FG1_39, 255u, 255u, 255u);
            break;
        }

        default:
            break;
    }

    if (GetAnimation().GetCurrentFrame() == 3)
    {
        Particle* pParticle = relive_new Particle(
            mXPos,
            mYPos,
            GetAnimRes(AnimId::GroundExplosion));
        if (pParticle)
        {
            pParticle->GetAnimation().mFlags.Set(AnimFlags::eFlipX);
            pParticle->mVisualFlags.Clear(VisualFlags::eApplyShadowZoneColour);
            pParticle->GetAnimation().SetRenderMode(TPageAbr::eBlend_1);
            pParticle->SetSpriteScale(GetSpriteScale() * FP_FromDouble(0.7));
        }
    }

    if (GetAnimation().mFlags.Get(AnimFlags::eForwardLoopCompleted)) // Animation ended
    {
        // Time to die
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

void GroundExplosion::DealDamageRect(const PSX_RECT* pRect)
{
    if (gBaseAliveGameObjects)
    {
        s16 min_w_x = pRect->w;
        if (pRect->x <= pRect->w)
        {
            min_w_x = pRect->x;
        }

        auto min_x_w = pRect->w;
        if (pRect->w <= pRect->x)
        {
            min_x_w = pRect->x;
        }

        auto min_y_h = pRect->h;
        if (pRect->y <= pRect->h)
        {
            min_y_h = pRect->y;
        }

        s16 min_h_y = pRect->h;
        if (pRect->h <= pRect->y)
        {
            min_h_y = pRect->y;
        }

        auto right = FP_GetExponent(mXPos) + min_x_w;
        auto left = FP_GetExponent(mXPos) + min_w_x;
        auto top = FP_GetExponent(mYPos) + min_y_h;
        auto bottom = FP_GetExponent(mYPos) + min_h_y;

        if ((abs(left) & 1023) < 256)
        {
            left -= 656;
        }

        if ((abs(right) & 1023) > 624)
        {
            right += 656;
        }

        if (top % 480 < 120)
        {
            top -= 240;
        }

        if (bottom % 480 > 360)
        {
            bottom += 240;
        }

        for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
        {
            BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            const s16 obj_xpos = FP_GetExponent(pObj->mXPos);
            if (obj_xpos >= left && obj_xpos <= right)
            {
                const s16 obj_ypos = FP_GetExponent(pObj->mYPos);
                if (obj_ypos >= top && obj_ypos <= bottom && GetSpriteScale() == (pObj->GetSpriteScale() * FP_FromDouble(2.75)))
                {
                    pObj->VTakeDamage(this);
                }
            }
        }
    }
}

GroundExplosion::GroundExplosion(FP xpos, FP ypos, FP scale)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(ReliveTypes::eGroundExplosion);

    mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::GroundExplosion));
    Animation_Init(GetAnimRes(AnimId::GroundExplosion));

    GetAnimation().mFlags.Clear(AnimFlags::eIsLastFrame);

    GetAnimation().SetRenderMode(TPageAbr::eBlend_1);

    GetAnimation().SetRGB(128, 128, 128);

    mObjectScale = scale;

    if (scale == FP_FromInteger(1))
    {
        GetAnimation().SetRenderLayer(Layer::eLayer_Foreground_36);
    }
    else
    {
        GetAnimation().SetRenderLayer(Layer::eLayer_Foreground_Half_17);
    }

    mVisualFlags.Clear(VisualFlags::eApplyShadowZoneColour);
    SetSpriteScale(scale * FP_FromDouble(2.75));

    mXPos = xpos;
    mYPos = ypos;

    relive_new ScreenShake(1);

    relive_new ParticleBurst(
        mXPos,
        mYPos,
        35,
        mObjectScale,
        BurstType::eFallingRocks_0);

    PSX_RECT damageRect = {
        FP_GetExponent(FP_FromInteger(-10) * mObjectScale),
        FP_GetExponent(FP_FromInteger(-10) * mObjectScale),
        FP_GetExponent(FP_FromInteger(10) * mObjectScale),
        FP_GetExponent(FP_FromInteger(10) * mObjectScale)};
    DealDamageRect(&damageRect);

    SND_SEQ_PlaySeq_4775A0(SeqId::eExplosion1_21, 1, 1);
}

} // namespace AO