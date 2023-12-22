#include "stdafx.h"
#include "GroundExplosion.hpp"
#include "../Function.hpp"
#include "../Events.hpp"
#include "Sfx.hpp"
#include "../Sound/Midi.hpp"
#include "ScreenShake.hpp"
#include "ParticleBurst.hpp"
#include "Flash.hpp"
#include "Particle.hpp"
#include "../FixedPoint.hpp"
#include "IBaseAliveGameObject.hpp"
#include "../GameType.hpp"
#include "../../AliveLibAO/Midi.hpp"

GroundExplosion::GroundExplosion(FP xpos, FP ypos, FP scale)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(ReliveTypes::eGroundExplosion);

    mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::GroundExplosion));
    Animation_Init(GetAnimRes(AnimId::GroundExplosion));

    GetAnimation().SetIsLastFrame(false); // Double Check

    GetAnimation().SetBlendMode(relive::TBlendModes::eBlend_1);

    GetAnimation().SetRGB(128, 128, 128);

    mBombSpriteScale = scale;

    if (scale == FP_FromInteger(1))
    {
        GetAnimation().SetRenderLayer(Layer::eLayer_Foreground_36);
    }
    else
    {
        GetAnimation().SetRenderLayer(Layer::eLayer_Foreground_Half_17);
    }

    SetApplyShadowZoneColour(false);
    SetSpriteScale(scale * FP_FromDouble(2.75));

    mXPos = xpos;
    mYPos = ypos;

    relive_new ScreenShake(true, false);

    relive_new ParticleBurst(
        mXPos,
        mYPos,
        35,
        mBombSpriteScale,
        BurstType::eRocks);

    PSX_RECT damageRect = {
        FP_GetExponent(FP_FromInteger(-10) * mBombSpriteScale),
        FP_GetExponent(FP_FromInteger(-10) * mBombSpriteScale),
        FP_GetExponent(FP_FromInteger(10) * mBombSpriteScale),
        FP_GetExponent(FP_FromInteger(10) * mBombSpriteScale)};
    DealDamageRect(&damageRect);

    if (GetGameType() == GameType::eAe)
    {
        // alternate between Explosion1 and Explosion2 on each call
        static bool staticIdFlip = false;
        const u16 explosionSeqId = static_cast<u16>(staticIdFlip ? SeqId::Explosion1_14 : SeqId::Explosion2_15);
        SND_SEQ_PlaySeq(explosionSeqId, 1, 1);
        staticIdFlip = !staticIdFlip;

    }
    else
    {
        SND_SEQ_PlaySeq(AO::SeqId::eExplosion1_21, 1, 1);
    }
}

void GroundExplosion::VUpdate()
{
    PSX_RECT rect = {};

    EventBroadcast(kEventShooting, this);
    EventBroadcast(kEventLoudNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    switch (GetAnimation().GetCurrentFrame())
    {
        case 0:
            rect.x = FP_GetExponent(FP_FromInteger(-30) * mBombSpriteScale);
            rect.w = FP_GetExponent(FP_FromInteger(30) * mBombSpriteScale);
            rect.y = FP_GetExponent(FP_FromInteger(-20) * mBombSpriteScale);
            rect.h = FP_GetExponent(FP_FromInteger(20) * mBombSpriteScale);
            DealDamageRect(&rect);
            break;

        case 1:
            rect.x = FP_GetExponent(FP_FromInteger(-50) * mBombSpriteScale);
            rect.w = FP_GetExponent(FP_FromInteger(50) * mBombSpriteScale);
            rect.y = FP_GetExponent(FP_FromInteger(-30) * mBombSpriteScale);
            rect.h = FP_GetExponent(FP_FromInteger(30) * mBombSpriteScale);
            DealDamageRect(&rect);
            break;

        case 2:
            rect.x = FP_GetExponent(FP_FromInteger(-80) * mBombSpriteScale);
            rect.w = FP_GetExponent(FP_FromInteger(80) * mBombSpriteScale);
            rect.y = FP_GetExponent(FP_FromInteger(-40) * mBombSpriteScale);
            rect.h = FP_GetExponent(FP_FromInteger(40) * mBombSpriteScale);
            DealDamageRect(&rect);
            break;

        case 3:
        {
            relive_new ParticleBurst(
                mXPos,
                mYPos,
                20,
                GetSpriteScale(),
                BurstType::eBigRedSparks);

            relive_new Flash(Layer::eLayer_Above_FG1_39, 255, 255, 255);

            rect.x = FP_GetExponent(FP_FromInteger(-113) * mBombSpriteScale);
            rect.w = FP_GetExponent(FP_FromInteger(113) * mBombSpriteScale);
            rect.y = FP_GetExponent(FP_FromInteger(-50) * mBombSpriteScale);
            rect.h = FP_GetExponent(FP_FromInteger(50) * mBombSpriteScale);
            DealDamageRect(&rect);
            break;
        }

        case 4:
        {
            relive_new Flash(Layer::eLayer_Above_FG1_39, 255, 255, 255, relive::TBlendModes::eBlend_1, 1);
            break;
        }

        case 7:
        {
            relive_new ParticleBurst(
                mXPos,
                mYPos,
                20,
                GetSpriteScale(),
                BurstType::eBigRedSparks);

            relive_new Flash(Layer::eLayer_Above_FG1_39, 255, 255, 255);
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
            pParticle->GetAnimation().SetFlipX(true);
            pParticle->SetApplyShadowZoneColour(false);
            pParticle->GetAnimation().SetBlendMode(relive::TBlendModes::eBlend_1);
            pParticle->SetSpriteScale(GetSpriteScale() * FP_FromDouble(0.7));
        }
    }

    if (GetAnimation().GetForwardLoopCompleted()) // Animation ended
    {
        // Time to die
        SetDead(true);
    }
}

void GroundExplosion::DealDamageRect(const PSX_RECT* pRect)
{
    if (gBaseAliveGameObjects)
    {
        auto min_x_w = pRect->w;
        if (pRect->x <= pRect->w)
        {
            min_x_w = pRect->x;
        }

        auto min_w_x = pRect->w;
        if (pRect->w <= pRect->x)
        {
            min_w_x = pRect->x;
        }

        auto min_y_h = pRect->h;
        if (pRect->y <= pRect->h)
        {
            min_y_h = pRect->y;
        }

        auto min_h_y = pRect->h;
        if (pRect->h <= pRect->y)
        {
            min_h_y = pRect->y;
        }

        auto right = FP_GetExponent(mXPos) + min_w_x;
        auto left = FP_GetExponent(mXPos) + min_x_w;
        auto top = FP_GetExponent(mYPos) + min_y_h;
        auto bottom = FP_GetExponent(mYPos) + min_h_y;

        if (GetGameType() == GameType::eAo)
        {
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
        }

        for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
        {
            auto pObj = gBaseAliveGameObjects->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            const auto objXPos = FP_GetExponent(pObj->mXPos);
            const auto objYPos = FP_GetExponent(pObj->mYPos);

            if (objXPos >= left && objXPos <= right)
            {
                if (objYPos >= top && objYPos <= bottom)
                {
                    if (GetSpriteScale() == (pObj->GetSpriteScale() * FP_FromDouble(2.75)))
                    {
                        pObj->VTakeDamage(this);
                    }
                }
            }
        }
    }
}