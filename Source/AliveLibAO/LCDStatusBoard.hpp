#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Font.hpp"
#include "Map.hpp"

namespace AO {

struct Path_LCDStatusBoard final : public Path_TLV
{
    // No fields
};

class LCDStatusBoard final : public BaseGameObject
{
public:
    LCDStatusBoard(relive::Path_LCDStatusBoard* pTlv, const Guid& tlvId);
    ~LCDStatusBoard();

    virtual void VScreenChanged() override;
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;

    FontContext field_10_fontContext;
    AliveFont field_20_font1;
    AliveFont field_58_font2;
    AliveFont field_90_font3;
    Guid field_C8_tlv;
    s16 field_CC_xpos = 0;
    s16 field_CE_ypos = 0;
};
ALIVE_ASSERT_SIZEOF(LCDStatusBoard, 0xD0);

} // namespace AO
