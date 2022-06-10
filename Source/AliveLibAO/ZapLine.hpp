#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"

void ZapLine_ForceLink();

namespace AO {

struct ZapLineSprites final
{
    Prim_Sprt field_0_sprts[2];
};
ALIVE_ASSERT_SIZEOF(ZapLineSprites, 0x30);

struct ZapPoint final
{
    FP field_0;
    FP field_4;
    FP field_8;
};
ALIVE_ASSERT_SIZEOF(ZapPoint, 0xC);

enum class ZapLineType : s16
{
    eThick_0 = 0, // Used by Chant Suppressors and Greeters.
    eThin_1 = 1   // Used by the Shrykull.
};

class ZapLine final : public BaseAnimatedWithPhysicsGameObject
{
public:
    ZapLine(FP x1, FP y1, FP x2, FP y2, s32 aliveTime, ZapLineType type, Layer layer);
    ~ZapLine();

    void CalculateSourceAndDestinationPositions(FP xPosSource, FP yPosSource, FP xPosDest, FP yPosDest);

    virtual void VScreenChanged() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VUpdate() override;

    // Note inlined
    void CalculateSpritePositionsOuter();

    void CalculateZapPoints_479380();
    void CalculateThinSpriteSegmentPositions();
    void CalculateThickSpriteSegmentPositions();
    void UpdateSpriteVertexPositions();
    void CalculateSpritePositionsInner(s32 idx1, s32 idx2, s32 idx3, s16 idx4);

    s32 field_D4[4];

    enum class ZapLineState : s16
    {
        eInit_0 = 0,
        eInitSpritePositions_1 = 1,
        eInitSpriteVertices_2 = 2,
        eUpdateSpritePositions_3 = 3,
        eUpdateSpriteVertices_4 = 4
    };

    ZapLineState field_E4_state;

    u8** field_E8_ppRes;
    Prim_SetTPage field_EC_tPage_p8[2];
    s16 field_10C_x_position_source;
    s16 field_10E_y_position_source;
    s16 field_110_x_position_destination;
    s16 field_112_y_position_destination;
    TPageMode field_114_tPageMode;
    s16 field_116_alive_timer;
    s16 field_118_max_alive_time;
    ZapLineType field_11A_type;
    TPageAbr field_11C_tPageAbr;
    s16 field_11E_number_of_segments;
    s16 field_120_number_of_pieces_per_segment;
    s16 field_122_number_of_sprites;
    ZapLineSprites* field_124_pSprts;
    PSX_Point* field_128_sprite_positions;
    ZapPoint* field_12C_zap_points;
    FP_Point* field_130_sprite_segment_positions;
    PSX_RECT field_134_rects[2];
};
ALIVE_ASSERT_SIZEOF(ZapLine, 0x144);

} // namespace AO
