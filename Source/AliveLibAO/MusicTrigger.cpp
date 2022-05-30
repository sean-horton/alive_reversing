#include "stdafx_ao.h"
#include "Function.hpp"
#include "MusicTrigger.hpp"
#include "SwitchStates.hpp"
#include "stdlib.hpp"
#include "Events.hpp"
#include "MusicController.hpp"
#include "Game.hpp"

namespace AO {

MusicTrigger::MusicTrigger(MusicTriggerMusicType type, TriggeredBy triggeredBy, s32 switchId, s32 delay)
    : BaseGameObject(1)
{
    Init_443AD0(type, triggeredBy, static_cast<s16>(switchId), static_cast<s16>(delay));
    field_10_tlvInfo = -1;
}

MusicTrigger::MusicTrigger(Path_MusicTrigger* pTlv, s32 tlvInfo)
    : BaseGameObject(1)
{
    Init_443AD0(pTlv->field_18_music_type, pTlv->field_1A_triggered_by, pTlv->field_1C_switch_id, pTlv->field_1E_music_delay);
    field_10_tlvInfo = tlvInfo;
}

void MusicTrigger::Init_443AD0(MusicTriggerMusicType type, TriggeredBy triggeredBy, u16 switchId, s16 delay)
{
    field_14_flags &= ~7u;
    field_4_typeId = Types::eNone_0;

    switch (type)
    {
        case MusicTriggerMusicType::eDrumAmbience_0:
            field_1C_music_type = MusicController::MusicTypes::eDrumAmbience_3;
            field_18_counter = 400;
            break;

        case MusicTriggerMusicType::eDeathDrumShort_1:
            field_1C_music_type = MusicController::MusicTypes::eDeathDrumShort_13;
            field_18_counter = 30;
            break;

        case MusicTriggerMusicType::eSecretAreaLong_2:
            field_1C_music_type = MusicController::MusicTypes::eSecretAreaLong_16;
            field_18_counter = 30;
            break;

        case MusicTriggerMusicType::eSoftChase_3:
            field_1C_music_type = MusicController::MusicTypes::eSlogChase_5;
            field_14_flags |= 4;
            break;

        case MusicTriggerMusicType::eIntenseChase_4:
            field_1C_music_type = MusicController::MusicTypes::eIntenseChase_8;
            field_14_flags |= 4;
            break;

        case MusicTriggerMusicType::eChime_5:
            field_1C_music_type = MusicController::MusicTypes::eChime_2;
            field_18_counter = delay;
            break;

        case MusicTriggerMusicType::eSecretAreaShort_6:
            field_1C_music_type = MusicController::MusicTypes::eSecretAreaShort_15;
            field_18_counter = 30;
            break;

        default:
            break;
    }

    switch (triggeredBy)
    {
        case TriggeredBy::eTimer_0:
            field_8_update_delay = 0;
            break;

        case TriggeredBy::eTouching_1:
            field_8_update_delay = delay;
            break;

        case TriggeredBy::eSwitchID_2: // removed in AE
            field_14_flags |= 1u;
            field_1E_switch_id = switchId;
            field_8_update_delay = 0;
            field_18_counter = delay;
            if (switchId > 1)
            {
                if (SwitchStates_Get(switchId))
                {
                    mFlags.Set(BaseGameObject::eDead);
                }
            }
            break;

        case TriggeredBy::eUnknown_3: // removed in AE
            field_14_flags |= 1u;
            field_1E_switch_id = switchId;
            field_8_update_delay = 0;
            field_18_counter = -1;
            break;

        default:
            return;
    }
}

MusicTrigger::~MusicTrigger()
{
    if (field_14_flags & 4)
    {
        MusicController::PlayMusic_443810(MusicController::MusicTypes::eType0, this, 0, 0);
    }
    MusicController::ClearObject(this);
}


void MusicTrigger::VScreenChanged()
{
    VScreenChanged_443DD0();
}

void MusicTrigger::VScreenChanged_443DD0()
{
    if (gMap.mCurrentLevel != gMap.mLevel)
    {
        mFlags.Set(BaseGameObject::eDead);
    }
}

void MusicTrigger::VUpdate()
{
    VUpdate_443C90();
}

void MusicTrigger::VUpdate_443C90()
{
    if (Event_Get(kEventHeroDying_3))
    {
        mFlags.Set(BaseGameObject::eDead);
        if (field_10_tlvInfo >= 0)
        {
            gMap.TLV_Reset_446870(field_10_tlvInfo, -1, 0, 0);
        }
    }

    if (field_14_flags & 1)
    {
        if (SwitchStates_Get(field_1E_switch_id))
        {
            field_14_flags &= ~1u;

            MusicController::PlayMusic_443810(
                field_1C_music_type,
                this,
                ((u8) field_14_flags >> 2) & 1,
                1);
            field_14_flags |= 2u;

            if (field_18_counter >= 0)
            {
                field_18_counter += gnFrameCount_507670;
            }
        }
    }
    else
    {
        if (!(field_14_flags & 2))
        {
            MusicController::PlayMusic_443810(field_1C_music_type, this, (field_14_flags >> 2) & 1, 1);
            field_14_flags |= 2u;
            field_18_counter += gnFrameCount_507670;
            return;
        }

        if (field_18_counter < 0)
        {
            if (!SwitchStates_Get(field_1E_switch_id))
            {
                mFlags.Set(BaseGameObject::eDead);
                return;
            }

            if (field_18_counter < 0)
            {
                MusicController::PlayMusic_443810(field_1C_music_type, this, (field_14_flags >> 2) & 1, 0);
                return;
            }
        }

        if (static_cast<s32>(gnFrameCount_507670) < field_18_counter)
        {
            MusicController::PlayMusic_443810(field_1C_music_type, this, (field_14_flags >> 2) & 1, 0);
        }
        else
        {
            mFlags.Set(BaseGameObject::eDead);
        }
    }
}

} // namespace AO
