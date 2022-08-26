#include "stdafx_ao.h"
#include "Function.hpp"
#include "SlogSpawner.hpp"
#include "stdlib.hpp"
#include "Game.hpp"
#include "SwitchStates.hpp"
#include "Slog.hpp"
#include "../relive_lib/Events.hpp"
#include "Math.hpp"

namespace AO {

void SlogSpawner::VScreenChanged()
{
    Path::TLV_Reset(mTlvInfo, mSpawnedSlogsCount, 0, 0);
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

SlogSpawner::SlogSpawner(relive::Path_SlogSpawner* pTlv, const TLVUniqueId& tlvId)
    : BaseGameObject(TRUE, 0)
{
    mTlvInfo = tlvId;
    mSpawnTimer = 0;

    mScale = pTlv->mScale;
    mMaxSlogs = pTlv->mMaxSlogs;
    mMaxSlogsAtATime = pTlv->mMaxSlogsAtATime;
    mStartDirection = pTlv->mStartDirection;
    mSlogSpawnInterval = pTlv->mSlogSpawnInterval;
    mSpawnerSwitchId = pTlv->mSpawnerSwitchId;

    mSpawnedSlogsCount = pTlv->mTlvSpecificMeaning;

    mXPos = FP_FromInteger(pTlv->mTopLeftX);
    mYPos = FP_FromInteger(pTlv->mTopLeftY);
}

void SlogSpawner::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if (static_cast<s32>(sGnFrame) > mSpawnTimer && gNumSlogs_9F11C8 < mMaxSlogsAtATime)
    {
        if (SwitchStates_Get(mSpawnerSwitchId))
        {
            mSpawnTimer = Math_NextRandom() % 8
                                 + sGnFrame
                                 + mSlogSpawnInterval;

            auto pSlog = relive_new Slog(
                    mXPos,
                    mYPos,
                    mScale != relive::reliveScale::eFull ? FP_FromDouble(0.5) : FP_FromInteger(1));;
            if (pSlog)
            {
                pSlog->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, mStartDirection == relive::Path_SlogSpawner::StartDirection::eLeft);
            }

            mSpawnedSlogsCount++;

            if (mSpawnedSlogsCount >= mMaxSlogs)
            {
                Path::TLV_Reset(mTlvInfo, mSpawnedSlogsCount, 0, 1);
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            }
        }
    }
}

} // namespace AO
