#include "stdafx.h"
#include "Grinder.hpp"
#include "Function.hpp"
#include "stdlib.hpp"
#include "Shadow.hpp"
#include "Sfx.hpp"
#include "SwitchStates.hpp"
#include "Midi.hpp"
#include "Abe.hpp"
#include "Events.hpp"
#include "Game.hpp"

const TintEntry stru_551548[18] =
{
    { '\x01', 127u, 127u, 127u },
    { '\x02', 137u, 137u, 137u },
    { '\x03', 127u, 127u, 127u },
    { '\x04', 127u, 127u, 127u },
    { '\x05', 127u, 127u, 127u },
    { '\x06', 127u, 127u, 127u },
    { '\a', 127u, 127u, 127u },
    { '\b', 127u, 127u, 127u },
    { '\t', 127u, 127u, 127u },
    { '\n', 127u, 127u, 127u },
    { '\v', 127u, 127u, 127u },
    { '\f', 127u, 127u, 127u },
    { '\r', 127u, 127u, 127u },
    { '\x0E', 127u, 127u, 127u },
    { '\xFF', 127u, 127u, 127u },
    { '\0', 0u, 0u, 0u },
    { '\0', 0u, 0u, 0u },
    { '\0', 0u, 0u, 0u }
};


Grinder* Grinder::ctor_4200D0(Path_Grinder* pTlv, DWORD tlvInfo)
{
    BaseAnimatedWithPhysicsGameObject_ctor_424930(0);
    SetVTable(this, 0x544AD8);

    field_4_typeId = BaseGameObject::Types::eGrinder_30;

    BYTE** ppRes = Add_Resource_4DC130(ResourceManager::Resource_Animation, 6004); // TODO: Id
    Animation_Init_424E10(6676, 65, 33, ppRes, 1, 1);
    field_20_animation.field_4_flags.Set(AnimFlags::eBit15_bSemiTrans);
    field_20_animation.field_B_render_mode = 0;

    SetTint_425600(stru_551548, gMap_5C3030.sCurrentLevelId_5C3030);
    Path_Grinder_Data tlvData = pTlv->field_10_data;

    field_128_flags.Clear(Flags::eBit2_StartOn);
    field_128_flags.Clear(Flags::eBit5);
    field_128_flags.Clear(Flags::eBit4_Toggle);

    if (tlvData.field_1C_start_state)
    {
        field_128_flags.Clear(Flags::eBit1);
    }
    else
    {
        field_128_flags.Set(Flags::eBit1);
    }

    field_F8_id = tlvData.field_16_id;

    if (SwitchStates_Get_466020(field_F8_id) && field_128_flags.Get(Flags::eBit1))
    {
        field_128_flags.Set(Flags::eBit2_StartOn);
    }

    if (tlvData.field_10_scale == 0)
    {
        field_CC_sprite_scale = FP_FromInteger(1);
        field_20_animation.field_C_render_layer = 24;
        field_D6_scale = 1;
    }
    else
    {
        field_CC_sprite_scale = FP_FromDouble(0.5);
        field_20_animation.field_C_render_layer = 5;
        field_D6_scale = 0;
    }

    field_FA_direction = tlvData.field_26_direction;
    if (tlvData.field_24_start_position & 1)
    {
        field_128_flags.Set(Flags::eBit6_StartPos);
    }
    else
    {
        field_128_flags.Clear(Flags::eBit6_StartPos);
    }

    if (field_128_flags.Get(Flags::eBit2_StartOn))
    {
        if (field_128_flags.Get(Flags::eBit6_StartPos))
        {
            field_F4_state = GrinderStates::State_2_GoingUp;
        }
        else
        {
            field_F4_state = GrinderStates::State_1_Going_Down;
        }

        const __int16 direction = gMap_5C3030.sub_4811A0(
            field_C2_lvl_number,
            field_C0_path_number,
            field_B8_xpos,
            field_BC_ypos);
        field_10C_audio_channels_mask = SFX_Play_46FC20(0x61u, 25, direction, 0x10000);
    }

    switch (field_FA_direction)
    {
    case 0:
        field_110_xPos = FP_FromInteger(pTlv->field_8_top_left.field_0_x + 12);
        field_B8_xpos = field_110_xPos;
        field_114_yPos = FP_FromInteger(pTlv->field_C_bottom_right.field_2_y);

        if (field_128_flags.Get(Flags::eBit2_StartOn))
        {
            field_20_animation.Set_Animation_Data_409C80(6688, nullptr);
        }
        else
        {
            field_20_animation.Set_Animation_Data_409C80(6676, nullptr);
        }

        field_F6_width = pTlv->field_C_bottom_right.field_2_y - pTlv->field_8_top_left.field_2_y;
        if (field_128_flags.Get(Flags::eBit6_StartPos))
        {
            field_124_xyoff = FP_FromInteger(0);
        }
        else
        {
            field_124_xyoff = FP_FromInteger(field_F6_width);
        }
        field_BC_ypos = field_114_yPos - field_124_xyoff;
        break;

    case 1:
        field_110_xPos = FP_FromInteger(pTlv->field_8_top_left.field_0_x + 12);
        field_114_yPos = FP_FromInteger(pTlv->field_C_bottom_right.field_2_y);
        field_BC_ypos = field_114_yPos;

        if (field_128_flags.Get(Flags::eBit2_StartOn))
        {
            field_20_animation.Set_Animation_Data_409C80(6712, nullptr);
        }
        else
        {
            field_20_animation.Set_Animation_Data_409C80(6736, nullptr);
        }

        field_F6_width = pTlv->field_C_bottom_right.field_0_x - pTlv->field_8_top_left.field_0_x;
        if (field_128_flags.Get(Flags::eBit6_StartPos))
        {
            field_124_xyoff = FP_FromInteger(0);
        }
        else
        {
            field_124_xyoff = FP_FromInteger(field_F6_width);
        }
        field_B8_xpos = field_124_xyoff + field_110_xPos;
        break;

    case 2:
        field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX);

        field_110_xPos = FP_FromInteger(pTlv->field_C_bottom_right.field_0_x - 12);
        field_114_yPos = FP_FromInteger(pTlv->field_C_bottom_right.field_2_y);
        field_BC_ypos = field_114_yPos;

        if (field_128_flags.Get(Flags::eBit2_StartOn))
        {
            field_20_animation.Set_Animation_Data_409C80(6712, nullptr);
        }
        else
        {
            field_20_animation.Set_Animation_Data_409C80(6736, nullptr);
        }

        field_F6_width = pTlv->field_C_bottom_right.field_0_x - pTlv->field_8_top_left.field_0_x;
        if (field_128_flags.Get(Flags::eBit6_StartPos))
        {
            field_124_xyoff = FP_FromInteger(0);
        }
        else
        {
            field_124_xyoff = FP_FromInteger(field_F6_width);
        }
        field_B8_xpos = field_110_xPos - field_124_xyoff;
        break;

    }

    field_FE_max_off_time = tlvData.field_14_max_off_time;
    field_FC_min_off_time = tlvData.field_12_min_off_time;

    switch (tlvData.field_18_behavior)
    {
    case 1:
        field_128_flags.Set(Flags::eBit3_UseId);
        field_128_flags.Clear(Flags::eBit4_Toggle);
        break;

    case 2:
        field_128_flags.Set(Flags::eBit3_UseId);
        field_128_flags.Set(Flags::eBit4_Toggle);
        break;

    default:
        field_128_flags.Clear(Flags::eBit3_UseId);
        field_128_flags.Clear(Flags::eBit4_Toggle);
        break;
    }

    field_118_speed = FP_FromInteger(tlvData.field_1A_speed);
    if (tlvData.field_1A_speed == 250)
    {
        field_118_speed = FP_FromDouble(0.2);
    }

    field_11C_speed2 = field_118_speed;
    field_120_off_speed = FP_FromInteger(tlvData.field_1E_off_speed);
    if (tlvData.field_1E_off_speed == 250)
    {
        field_120_off_speed = FP_FromDouble(0.2);
    }

    field_100_min_off_time2 = tlvData.field_20_min_off_time2;
    field_102_max_off_time2 = tlvData.field_22_max_off_time2;
    field_108_off_timer = 0;
    field_F4_state = GrinderStates::State_0_Restart_Cycle;
    field_104_tlv = tlvInfo;
    field_10C_audio_channels_mask = 0;

    auto pShadow = alive_new<Shadow>();
    if (pShadow)
    {
        pShadow->ctor_4AC990();
    }
    field_E0_176_ptr = pShadow;

    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kAbeblowResID);
    return this;
}

BaseGameObject* Grinder::VDestructor(signed int flags)
{
    return vdtor_4206A0(flags);
}

void Grinder::VUpdate()
{
    vUpdate_420C50();
}

void Grinder::VRender(int** pOrderingTable)
{
    vRender_4213D0(pOrderingTable);
}

void Grinder::VScreenChanged()
{
    vScreenChanged_4214B0();
}

void Grinder::VStopAudio()
{
    vStopAudio_4215C0();
}

int Grinder::VGetSaveState(BYTE* pSaveBuffer)
{
    return vGetSaveState_4217B0(pSaveBuffer);
}

signed int CC Grinder::CreateFromSaveState_421600(const BYTE* pData)
{
    const Grinder_State* pState = reinterpret_cast<const Grinder_State*>(pData);

    Path_Grinder* pTlv = static_cast<Path_Grinder*>(sPath_dword_BB47C0->TLV_From_Offset_Lvl_Cam_4DB770(pState->field_8_tlvInfo));
    
    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeblowResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("ABEBLOW.BAN", 0);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kSlogBlowResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_49C170("DOGBLOW.BAN", 0);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 6004, 0, 0)) // TODO: Id
    {
        ResourceManager::LoadResourceFile_49C170("DRILL.BAN", 0);
    }

    auto pGrinder = alive_new<Grinder>();
    if (pGrinder)
    {
        pGrinder->ctor_4200D0(pTlv, pState->field_8_tlvInfo);
    }

    if (pState->field_10_state != GrinderStates::State_0_Restart_Cycle)
    {
        if (pGrinder->field_FA_direction)
        {
            if (pGrinder->field_FA_direction > 0 && pGrinder->field_FA_direction <= 2)
            {
                pGrinder->field_20_animation.Set_Animation_Data_409C80(6712, 0);
            }
        }
        else
        {
            pGrinder->field_20_animation.Set_Animation_Data_409C80(6688, 0);
        }
    }

    pGrinder->field_108_off_timer = pState->field_C_off_timer;
    pGrinder->field_F4_state = pState->field_10_state;
    pGrinder->field_124_xyoff = FP_FromInteger(pState->field_12_xyoff);
    return sizeof(Grinder_State);
}

void Grinder::vUpdate_420C50()
{
    if (Event_Get_422C00(kEventDeathReset))
    {
        field_6_flags.Set(BaseGameObject::eDead);
    }

    const __int16 soundDirection = gMap_5C3030.sub_4811A0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos);

    if (field_F4_state == GrinderStates::State_0_Restart_Cycle)
    {
        if (field_108_off_timer <= static_cast<int>(sGnFrame_5C1B84) || (field_128_flags.Get(Flags::eBit4_Toggle)))
        {
            if (!(field_128_flags.Get(Flags::eBit3_UseId)) || (!!SwitchStates_Get_466020(field_F8_id) == (field_128_flags.Get(Flags::eBit1))))
            {
                // TODO: Add enum/refactor all usage of direction
                __int16 direction = field_FA_direction;
                field_F4_state = GrinderStates::State_1_Going_Down;
                if (direction)
                {
                    __int16 directionM1 = direction - 1;
                    if (!directionM1 || directionM1 == 1)
                    {
                        field_20_animation.Set_Animation_Data_409C80(6712, 0);
                    }
                }
                else
                {
                    field_20_animation.Set_Animation_Data_409C80(6688, 0);
                }

                field_128_flags.Clear(Flags::eBit5);
                field_11C_speed2 = field_118_speed;
                field_10C_audio_channels_mask = SFX_Play_46FC20(0x61u, 25, soundDirection, 0x10000);
                return;
            }
        }

        if (field_128_flags.Get(Flags::eBit3_UseId) &&
            !(field_128_flags.Get(Flags::eBit4_Toggle)) &&
            FP_GetExponent(field_120_off_speed) &&
            field_108_off_timer <= static_cast<int>(sGnFrame_5C1B84))
        {
            __int16 direction3 = field_FA_direction;
            field_F4_state = GrinderStates::State_1_Going_Down;
            if (direction3)
            {
                __int16 directionM12 = direction3 - 1;
                if (directionM12)
                {
                    if (directionM12 == 1)
                    {
                        field_20_animation.Set_Animation_Data_409C80(6712, 0);
                        field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX);;
                    }
                }
                else
                {
                    field_20_animation.Set_Animation_Data_409C80(6712, 0);
                }
            }
            else
            {
                field_20_animation.Set_Animation_Data_409C80(6688, 0);
            }

            field_128_flags.Set(Flags::eBit5);
            field_11C_speed2 = field_120_off_speed;

            field_10C_audio_channels_mask = SFX_Play_46FC20(0x61u, 25, soundDirection, 0x10000);
            return;
        }
    }
    else if (field_F4_state == GrinderStates::State_2_GoingUp)
    {
        if (!field_10C_audio_channels_mask)
        {
            field_10C_audio_channels_mask = SFX_Play_46FC20(0x61u, 25, soundDirection, 0x10000);
        }

        DamageTouchingObjects_421060();

        field_124_xyoff = field_11C_speed2 + field_124_xyoff;
        if (field_124_xyoff >= FP_FromInteger(field_F6_width))
        {
            if (field_10C_audio_channels_mask)
            {
                SND_Stop_Channels_Mask_4CA810(field_10C_audio_channels_mask);
                field_10C_audio_channels_mask = 0;
            }

            field_F4_state = GrinderStates::State_0_Restart_Cycle;
            SFX_Play_46FC20(0x63u, 50, soundDirection, 0x10000);

            short max_off = 0;
            short min_off = 0;
            if (field_128_flags.Get(Flags::eBit5))
            {
                max_off = field_102_max_off_time2;
                min_off = field_100_min_off_time2;
            }
            else
            {
                max_off = field_FE_max_off_time;
                min_off = field_FC_min_off_time;
            }

            field_108_off_timer = sGnFrame_5C1B84 + Math_RandomRange_496AB0(min_off, max_off);

            if (field_FA_direction == 0)
            {
                field_20_animation.Set_Animation_Data_409C80(6676, 0);
            }
            else
            {
                field_20_animation.Set_Animation_Data_409C80(6736, 0);
            }

            if (field_128_flags.Get(Flags::eBit4_Toggle))
            {
                SwitchStates_Set_465FF0(field_F8_id, field_128_flags.Get(Flags::eBit1)); // TODO: Check correct way around
            }
        }

        EmitSparks_4206D0();
    }
    else if (field_F4_state == GrinderStates::State_1_Going_Down)
    {
        if (!field_10C_audio_channels_mask)
        {
            field_10C_audio_channels_mask = SFX_Play_46FC20(0x61u, 25, soundDirection, 0x10000);
        }

        DamageTouchingObjects_421060();
        field_124_xyoff = field_124_xyoff - field_11C_speed2;
        if (field_124_xyoff <= FP_FromInteger(0))
        {
            field_F4_state = GrinderStates::State_2_GoingUp;
            SFX_Play_46FC20(0x63u, 50, soundDirection, 0x10000);
        }

        EmitSparks_4206D0();
    }
}

void Grinder::dtor_420B60()
{
    SetVTable(this, 0x544AD8); // vTbl_Grinder_544AD8

    if (field_10C_audio_channels_mask)
    {
        SND_Stop_Channels_Mask_4CA810(field_10C_audio_channels_mask);
        field_10C_audio_channels_mask = 0;
    }

    if (field_128_flags.Get(Flags::eBit3_UseId) && !!SwitchStates_Get_466020(field_F8_id) != field_128_flags.Get(Flags::eBit1))
    {
        Path::TLV_Reset_4DB8E0(field_104_tlv, 1, 0, 0);
    }
    else
    {
        Path::TLV_Reset_4DB8E0(field_104_tlv, 0, 0, 0);
    }

    BaseAnimatedWithPhysicsGameObject_dtor_424AD0();
}

Grinder* Grinder::vdtor_4206A0(signed int flags)
{
    dtor_420B60();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
    return this;
}

void Grinder::vScreenChanged_4214B0()
{
    if (field_F4_state != GrinderStates::State_0_Restart_Cycle)
    {
        if (field_128_flags.Get(Flags::eBit6_StartPos))
        {
            field_124_xyoff = FP_FromInteger(0);
        }
        else
        {
            field_124_xyoff = FP_FromInteger(field_F6_width);
        }
    }

    // Stop that sound
    if (field_10C_audio_channels_mask)
    {
        SND_Stop_Channels_Mask_4CA810(field_10C_audio_channels_mask);
        field_10C_audio_channels_mask = 0;
    }

    // Seems the real function does this, but then always kill object at the end!
    // So it appears drills where supposed to survive for up to 1 screen away.

    /*
    // Map changed
    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId || gMap_5C3030.sCurrentPathId_5C3032 != gMap_5C3030.field_C_5C303C_pathId)
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return;
    }

    // More than 1 screen away on X?
    if (FP_Abs(sControlledCharacter_5C1B8C->field_B8_xpos - field_B8_xpos) > FP_FromInteger(375))
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return;
    }

    // More than 1 screen away on Y?
    if (FP_Abs(sControlledCharacter_5C1B8C->field_BC_ypos - field_BC_ypos) > FP_FromInteger(260))
    {
        field_6_flags.Set(BaseGameObject::eDead);
        return;
    }
    */

    field_6_flags.Set(BaseGameObject::eDead);
}

void Grinder::vRender_4213D0(int** pOt)
{
    if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(
        field_C2_lvl_number,
        field_C0_path_number,
        field_B8_xpos,
        field_BC_ypos,
        0))
    {
        if (field_FA_direction == 0)
        {
            field_BC_ypos = field_114_yPos - field_124_xyoff;
            BaseAnimatedWithPhysicsGameObject::VRender(pOt);
        }
        else if (field_FA_direction == 1)
        {
            field_B8_xpos = field_110_xPos + field_124_xyoff;
            BaseAnimatedWithPhysicsGameObject::VRender(pOt);
        }
        else if (field_FA_direction == 2)
        {
            field_B8_xpos = field_110_xPos - field_124_xyoff;
            BaseAnimatedWithPhysicsGameObject::VRender(pOt);
        }
    }
}

void Grinder::vStopAudio_4215C0()
{
    if (field_10C_audio_channels_mask)
    {
        SND_Stop_Channels_Mask_4CA810(field_10C_audio_channels_mask);
        field_10C_audio_channels_mask = 0;
    }
}

int Grinder::vGetSaveState_4217B0(BYTE* pSaveBuffer)
{
    Grinder_State* pState = reinterpret_cast<Grinder_State*>(pSaveBuffer);
    pState->field_0 = 30;
    pState->field_8_tlvInfo = field_104_tlv;
    pState->field_C_off_timer = field_108_off_timer;
    pState->field_10_state = field_F4_state;
    pState->field_12_xyoff = FP_GetExponent(field_124_xyoff);
    return sizeof(Grinder_State);
}

void Grinder::EmitSparks_4206D0()
{
    NOT_IMPLEMENTED();
}

__int16 Grinder::DamageTouchingObjects_421060()
{
    NOT_IMPLEMENTED();
    return 0;
}
