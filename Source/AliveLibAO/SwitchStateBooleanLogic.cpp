#include "stdafx_ao.h"
#include "Function.hpp"
#include "SwitchStateBooleanLogic.hpp"
#include "SwitchStates.hpp"
#include "stdlib.hpp"
#include "Events.hpp"

namespace AO {

void SwitchStateBooleanLogic::VUpdate()
{
    VUpdate_436B60();
}

void SwitchStateBooleanLogic::VScreenChanged_436C40()
{
    if (gMap.mOverlayId != gMap.GetOverlayId())
    {
        mFlags.Set(BaseGameObject::eDead);
    }
}

void SwitchStateBooleanLogic::VScreenChanged()
{
    VScreenChanged_436C40();
}

SwitchStateBooleanLogic::~SwitchStateBooleanLogic()
{
    gMap.TLV_Reset_446870(field_18_tlvInfo, -1, 0, 0);
}

SwitchStateBooleanLogic::SwitchStateBooleanLogic(Path_SwitchStateBooleanLogic* pTlv, s32 tlvInfo)
    : BaseGameObject(1)
{
    field_18_tlvInfo = tlvInfo;

    field_10_input_1 = pTlv->field_18_input1;
    field_12_input_2 = pTlv->field_1A_input2;

    field_14_output = pTlv->field_1C_output;

    field_16_operator = pTlv->field_1E_operator;
}


void SwitchStateBooleanLogic::VUpdate_436B60()
{
    const s16 id1_value = SwitchStates_Get(field_10_input_1);
    const s16 id2_value = SwitchStates_Get(field_12_input_2);

    s8 id_value = 0;
    switch (field_16_operator)
    {
        case BooleanOperatorType::eAnd_0:
            if (id1_value && id2_value)
            {
                id_value = 1;
            }
            else
            {
                id_value = 0;
            }
            break;

        case BooleanOperatorType::eAndNot_1:
            if (id1_value && !id2_value)
            {
                id_value = 1;
            }
            else
            {
                id_value = 0;
            }
            break;

        case BooleanOperatorType::eOr_2:
            if (id1_value || id2_value)
            {
                id_value = 1;
            }
            else
            {
                id_value = 0;
            }
            break;

        case BooleanOperatorType::eOrNot_3:
            if (id1_value || !id2_value)
            {
                id_value = 1;
            }
            else
            {
                id_value = 0;
            }
            break;

        default:
            id_value = 0;
            break;
    }

    SwitchStates_Set(field_14_output, id_value);

    if (Event_Get(kEventDeathReset_4))
    {
        mFlags.Set(BaseGameObject::eDead);
    }
}

} // namespace AO
