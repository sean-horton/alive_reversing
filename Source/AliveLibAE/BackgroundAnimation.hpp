#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Animation.hpp"
#include "Path.hpp"
#include "Factory.hpp"
#include "../relive_lib/Layer.hpp"

struct Path_BackgroundAnimation final : public Path_TLV
{
    u16 field_10_anim_id;
    Choice_short field_12_is_semi_trans;
    TPageAbr field_14_semi_trans_mode;
    // pad
    s16 field_16_sound_effect;
    s16 field_18_id;
    Layer field_1A_layer;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_BackgroundAnimation, 0x1C);

class BackgroundAnimation final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

    BackgroundAnimation(Path_BackgroundAnimation* pPathParams, TlvItemInfoUnion tlvInfo);
    ~BackgroundAnimation();

private:
    AnimHeader** field_F4_res = nullptr;
    TlvItemInfoUnion field_F8_tlvInfo = {};
    FP field_FC_animXPos = {};
    FP field_100_animYPos = {};
};
ALIVE_ASSERT_SIZEOF(BackgroundAnimation, 0x104);
