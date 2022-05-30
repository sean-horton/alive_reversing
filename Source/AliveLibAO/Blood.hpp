#pragma once

#include "../AliveLibCommon/FunctionFwd.hpp"
#include "Primitives.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "FixedPoint.hpp"
#include "Layer.hpp"

namespace AO {

void Blood_ForceLink();

struct BloodParticle final
{
    FP field_0_x;
    FP field_4_y;
    FP field_8_offx;
    FP field_C_offy;
    Prim_Sprt field_10_prims[2];
};
ALIVE_ASSERT_SIZEOF(BloodParticle, 0x40);

class Blood final : public BaseAnimatedWithPhysicsGameObject
{
public:
    Blood(FP xpos, FP ypos, FP xOff, FP yOff, FP scale, s32 count);
    ~Blood();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual void VRender(PrimHeader** ppOt) override;

    s32 field_D4_not_used[4];
    u8** field_E4_ppResBuf;
    BloodParticle* field_E8_pResBuf;
    Prim_SetTPage field_EC_tPages[2];
    TPageMode field_10C_texture_mode;
    // pad
    s16 field_10E_xpos;
    s16 field_110_ypos;
    s16 field_112_to_render_count;
    u8 field_114_rand_seed;
    s8 field_115_pad;
    s16 field_116_total_count;
    s32 field_118_timer;
    Layer field_11C_render_layer;
    s16 field_11E_pad;
};
ALIVE_ASSERT_SIZEOF(Blood, 0x120);

} // namespace AO
