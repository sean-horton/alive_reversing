#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"

namespace AO {

struct ParticleBurst_Item;

enum class BurstType : s16
{
    eFallingRocks_0 = 0,
    eSticks_1 = 1,
    eBigPurpleSparks_2 = 2,
    eBigRedSparks_3 = 3,
    eMeat_4 = 4,
};

class ParticleBurst final : public BaseAnimatedWithPhysicsGameObject
{
public:
    ParticleBurst(FP xpos, FP ypos, s32 particleCount, FP scale, BurstType type);
    ~ParticleBurst();

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;

    u8** field_E4_ppRes;
    ParticleBurst_Item* field_E8_pRes;
    s16 field_EC_count;
    s32 field_F0_timer;
    BurstType field_F4_type;
};
ALIVE_ASSERT_SIZEOF(ParticleBurst, 0xF8);

} // namespace AO
