#pragma once

#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Path.hpp"
#include "Font.hpp"
#include "../AliveLibCommon/Function.hpp"

struct Path_BrewMachine final : public Path_TLV
{
    s16 field_10_brew_count;
    s16 field_12_pad;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_BrewMachine, 0x14);

class BrewMachine final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    BrewMachine(Path_BrewMachine* pTlv, s32 tlvInfo);
    ~BrewMachine();
    
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;

private:
    Font_Context field_F4_font_context;
    Alive::Font field_104_font;
    s16 field_13C_textX;
    s16 field_13E_textY;
    s32 field_140_tlvInfo;

public:
    s16 field_144_total_brew_count;

private:
    Animation field_14C_anim;
    s16 field_1E4_remaining_brew_count;
    s16 field_1E6_cam_id;
};
ALIVE_ASSERT_SIZEOF(BrewMachine, 0x1E8);
