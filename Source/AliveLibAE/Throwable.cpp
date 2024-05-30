#include "stdafx.h"
#include "Throwable.hpp"
#include "../relive_lib/Function.hpp"
#include "Bone.hpp"
#include "Grenade.hpp"
#include "Rock.hpp"
#include "Meat.hpp"
#include "../relive_lib/Collisions.hpp"
#include "stdlib.hpp"
#include "../relive_lib/GameObjects/PlatformBase.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "../relive_lib/GameType.hpp"

bool gInfiniteThrowables = false;

const AOTypes gThrowableFromOverlayIdAO[54] = {
    AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eGrenade_40, AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eRock_70,
    AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0,
    AOTypes::eMeat_54, AOTypes::eNone_0, AOTypes::eMeat_54, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eRock_70, AOTypes::eRock_70, AOTypes::eNone_0,
    AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eRock_70, AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eGrenade_40,
    AOTypes::eNone_0, AOTypes::eGrenade_40, AOTypes::eGrenade_40, AOTypes::eGrenade_40, AOTypes::eGrenade_40, AOTypes::eGrenade_40, AOTypes::eGrenade_40, AOTypes::eGrenade_40, AOTypes::eNone_0, AOTypes::eGrenade_40,
    AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eNone_0, AOTypes::eNone_0};

const AETypes gThrowableFromOverlayIdAE[252] = {
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eRock_105, AETypes::eRock_105, AETypes::eRock_105, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eRock_105, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eRock_105, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eRock_105, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eRock_105, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eRock_105, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eMeat_84, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eMeat_84, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eMeat_84, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eRock_105, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eBone_11, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eGrenade_65, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0, AETypes::eNone_0,
    AETypes::eNone_0, AETypes::eNone_0};

static BaseThrowable* Make_Throwable_AO(FP xpos, FP ypos, s16 count)
{
    switch (gThrowableFromOverlayIdAO[gMap.mOverlayId])
    {
        case AOTypes::eGrenade_40:
            return relive_new Grenade(xpos, ypos, count);
        case AOTypes::eMeat_54:
            return relive_new Meat(xpos, ypos, count);
        case AOTypes::eRock_70:
            return relive_new Rock(xpos, ypos, count);
        default:
            return nullptr;
    }
}

static BaseThrowable* Make_Throwable_AE(FP xpos, FP ypos, s16 count)
{
    switch (gThrowableFromOverlayIdAE[gMap.mOverlayId])
    {
        case AETypes::eBone_11:
            return relive_new Bone(xpos, ypos, count);
        case AETypes::eMetal_24:
            return relive_new Grenade(xpos, ypos, count, false, nullptr);
        case AETypes::eGrenade_65:
            return relive_new Grenade(xpos, ypos, count, false, nullptr);
        case AETypes::eMeat_84:
            return relive_new Meat(xpos, ypos, count);
        case AETypes::eRock_105:
            return relive_new Rock(xpos, ypos, count);
        default:
            return nullptr;
    }
}

BaseThrowable* Make_Throwable(FP xpos, FP ypos, s16 count)
{
    if (GetGameType() == GameType::eAo)
    {
        return Make_Throwable_AO(xpos, ypos, count);
    }
    else
    {
        return Make_Throwable_AE(xpos, ypos, count);
    }
}

BaseThrowable::BaseThrowable()
    : BaseAliveGameObject(0)
{

}

void BaseThrowable::BaseAddToPlatform()
{
    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;

    CollisionMask fgMask;
    CollisionMask bgMask;
    if (GetGameType() == GameType::eAo)
    {
        fgMask = kFgWallsOrFloor;
        bgMask = kBgWallsOrFloor;
    }
    else
    {
        // todo: mouze check me 0x10F changed to 0x0F
        fgMask = kFgFloorCeilingOrWalls;
        bgMask = kBgFloorCeilingOrWalls;
    }
    if (gCollisions->Raycast(
            mXPos,
            mYPos - FP_FromInteger(20),
            mXPos,
            mYPos + FP_FromInteger(20),
            &pLine,
            &hitX,
            &hitY,
            PerGameScale() == Scale::Fg ? fgMask : bgMask))
    {
        if (pLine->mLineType == eLineTypes::eDynamicCollision_32 ||
            pLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
        {
            if (gPlatformsArray)
            {
                for (s32 idx = 0; idx < gPlatformsArray->Size(); idx++)
                {
                    BaseGameObject* pObjIter = gPlatformsArray->ItemAt(idx);
                    if (!pObjIter)
                    {
                        break;
                    }

                    // NOTE: meat in AE didn't check the trap door for some reason
                    if (pObjIter->Type() == ReliveTypes::eLiftPoint || pObjIter->Type() == ReliveTypes::eTrapDoor)
                    {
                        auto pPlatformBase = static_cast<PlatformBase*>(pObjIter);

                        const PSX_RECT bRect = pPlatformBase->VGetBoundingRect();

                        if (FP_GetExponent(mXPos) > bRect.x && FP_GetExponent(mXPos) < bRect.w && FP_GetExponent(mYPos) < bRect.h)
                        {
                            pPlatformBase->VAdd(this);
                            BaseAliveGameObject_PlatformId = pPlatformBase->mBaseGameObjectId;
                            return;
                        }
                    }
                }
            }
        }
    }
}

void BaseThrowable::VToDead()
{
    SetDead(true);
    mBaseThrowableDead = true;
}

void BaseThrowable::VOnAbeInteraction()
{
    VToDead();
}

s16 BaseThrowable::VGetCount()
{
    return mBaseThrowableCount;
}
