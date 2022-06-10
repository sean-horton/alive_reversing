#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Layer.hpp"

ALIVE_VAR_EXTERN(s32, gDeathGasCount_5BD24C);

class DeathGas final : public BaseGameObject
{
public:
    DeathGas(Layer layer, s32 amount);
    ~DeathGas();

    virtual void VScreenChanged() override;
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;

private:
    s16 field_20_total;
    s16 field_22_unused; // Gets increased by two every vUpdate_43C300. Isn't used anywhere else -- Nemin (6/7/2020)
    s16 field_24_amount;
    s16 field_26_flag;
    Layer field_28_layer;
};
ALIVE_ASSERT_SIZEOF(DeathGas, 0x30);
