#include "stdafx.h"
#include "MultiSwitchController.hpp"
#include "Map.hpp"
#include "../relive_lib/Events.hpp"
#include "../relive_lib/SwitchStates.hpp"
#include "Game.hpp"
#include "stdlib.hpp"
#include "Path.hpp"

MultiSwitchController::MultiSwitchController(relive::Path_MultiSwitchController* pTlv, const Guid& tlvId)
    : BaseGameObject(true, 0)
{
    mIsOn = false;
    mBaseGameObjectTlvInfo = tlvId;
    mTlvId = tlvId;

    mLastSwitchOnTime = 0;
    mAllSwitchesOnOrOffTime = 0;

    mOutputSwitchId = pTlv->mOutputSwitchId;

    mAction = pTlv->mAction;

    // Time after all switches on/off to activate id switch
    mOnOffDelay = pTlv->mOnOffDelay;

    mInputSwitchId1 = pTlv->mInputSwitchId1;
    mInputSwitchId2 = pTlv->mInputSwitchId2;
    mInputSwitchId3 = pTlv->mInputSwitchId3;
    mInputSwitchId4 = pTlv->mInputSwitchId4;
    mInputSwitchId5 = pTlv->mInputSwitchId5;
    mInputSwitchId6 = pTlv->mInputSwitchId6;
}

MultiSwitchController::~MultiSwitchController()
{
    Path::TLV_Reset(mTlvId);
}

void MultiSwitchController::VScreenChanged()
{
    if (gMap.LevelChanged() || gMap.PathChanged())
    {
        SetDead(true);
    }
}

void MultiSwitchController::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        SetDead(true);
    }

    if (mIsOn)
    {
        WaitingForAllOff();
    }
    else
    {
        WaitingForAllOn();
    }
}

void MultiSwitchController::WaitingForAllOn()
{
    const s32 id1_value = SwitchStates_Get(mInputSwitchId1);
    if (id1_value)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId1 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    const s32 id2_value = SwitchStates_Get(mInputSwitchId2);
    if (id2_value)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId2 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    const s32 id3_value = SwitchStates_Get(mInputSwitchId3);
    if (id3_value)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId3 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    const s32 id4_value = SwitchStates_Get(mInputSwitchId4);
    if (id4_value)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId4 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    const s32 id5_value = SwitchStates_Get(mInputSwitchId5);
    if (id5_value)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId5 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    const s32 id6_value = SwitchStates_Get(mInputSwitchId6);
    if (id6_value)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId6 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    if ((!id1_value || mInputSwitchId1 == 1) && (!id2_value || mInputSwitchId2 == 1) && (!id3_value || mInputSwitchId3 == 1) && (!id4_value || mInputSwitchId4 == 1) && (!id5_value || mInputSwitchId5 == 1) && (!id6_value || mInputSwitchId6 == 1))
    {
        mLastSwitchOnTime = 0;
    }

    if (id1_value && id2_value && id3_value && id4_value && id5_value && id6_value && mAllSwitchesOnOrOffTime == 0)
    {
        mAllSwitchesOnOrOffTime = sGnFrame;
        if (mAllSwitchesOnOrOffTime - mLastSwitchOnTime <= mOnOffDelay)
        {
            SwitchStates_Do_Operation(mOutputSwitchId, mAction);
            mIsOn = true;
            mLastSwitchOnTime = 0;
            mAllSwitchesOnOrOffTime = 0;
        }
    }
    else if (static_cast<s32>(sGnFrame) - mLastSwitchOnTime > mOnOffDelay)
    {
        if (mInputSwitchId1 > 1u)
        {
            SwitchStates_Set(mInputSwitchId1, 0);
        }

        if (mInputSwitchId2 > 1u)
        {
            SwitchStates_Set(mInputSwitchId2, 0);
        }

        if (mInputSwitchId3 > 1u)
        {
            SwitchStates_Set(mInputSwitchId3, 0);
        }

        if (mInputSwitchId4 > 1u)
        {
            SwitchStates_Set(mInputSwitchId4, 0);
        }

        if (mInputSwitchId5 > 1u)
        {
            SwitchStates_Set(mInputSwitchId5, 0);
        }

        if (mInputSwitchId6 > 1u)
        {
            SwitchStates_Set(mInputSwitchId6, 0);
        }

        mLastSwitchOnTime = 0;
    }
}

void MultiSwitchController::WaitingForAllOff()
{
    s32 id1_value = 0;
    if (mInputSwitchId1 > 1u)
    {
        id1_value = SwitchStates_Get(mInputSwitchId1);
    }
    if (id1_value == 0)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId1 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    s32 id2_value = 0;
    if (mInputSwitchId2 > 1u)
    {
        id2_value = SwitchStates_Get(mInputSwitchId2);
    }
    if (id2_value == 0)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId2 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    s32 id3_value = 0;
    if (mInputSwitchId3 > 1u)
    {
        id3_value = SwitchStates_Get(mInputSwitchId3);
    }
    if (id3_value == 0)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId3 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    s32 id4_value = 0;
    if (mInputSwitchId4 > 1u)
    {
        id4_value = SwitchStates_Get(mInputSwitchId4);
    }
    if (id4_value == 0)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId4 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    s32 id5_value = 0;
    if (mInputSwitchId5 > 1u)
    {
        id5_value = SwitchStates_Get(mInputSwitchId5);
    }
    if (id5_value == 0)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId5 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    s32 id6_value = 0;
    if (mInputSwitchId6 > 1u)
    {
        id6_value = SwitchStates_Get(mInputSwitchId6);
    }
    if (id6_value == 0)
    {
        if (mLastSwitchOnTime == 0 && mInputSwitchId6 > 1u)
        {
            mLastSwitchOnTime = sGnFrame;
        }
    }

    if ((id1_value || mInputSwitchId1 == 1) && (id2_value || mInputSwitchId2 == 1) && (id3_value || mInputSwitchId3 == 1) && (id4_value || mInputSwitchId4 == 1) && (id5_value || mInputSwitchId5 == 1) && (id6_value || mInputSwitchId6 == 1))
    {
        mLastSwitchOnTime = 0;
    }

    if (!id1_value && !id2_value && !id3_value && !id4_value && !id5_value && !id6_value && mAllSwitchesOnOrOffTime == 0)
    {
        mAllSwitchesOnOrOffTime = sGnFrame;
        if (mAllSwitchesOnOrOffTime - mLastSwitchOnTime <= mOnOffDelay)
        {
            SwitchStates_Do_Operation(mOutputSwitchId, mAction);
            mIsOn = false;
            mLastSwitchOnTime = 0;
        }
        // TODO: OG bug, why is this always reset ??
        mAllSwitchesOnOrOffTime = 0;
    }
}
