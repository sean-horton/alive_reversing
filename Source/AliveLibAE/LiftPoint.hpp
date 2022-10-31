#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "PlatformBase.hpp"
#include "../relive_lib/data_conversion/relive_tlvs.hpp"

struct LiftPointSaveState final
{
    AETypes field_0_type;
    s16 field_2_pad;
    FP field_4_xpos;
    FP field_8_ypos;
    Guid field_C_tlvInfo;
    Guid field_10_pTlv;
    FP field_14_floorYLevel;
    relive::Path_LiftPoint::LiftPointStopType field_18_lift_point_stop_type;
    enum Flags
    {
        eBit1_bMoving = 0x1,
        eBit2_bTopFloor = 0x2,
        eBit3_bMiddleFloor = 0x4,
        eBit4_bBottomFloor = 0x8,
        eBit5_bMoveToFloorLevel = 0x10,
        eBit6 = 0x20,
        eBit7_KeepOnMiddleFloor = 0x40,
    };
    BitField16<Flags> field_1A;
};
//ALIVE_ASSERT_SIZEOF_ALWAYS(LiftPointSaveState, 0x1C);

class LiftPoint final : public PlatformBase
{
public:
    LiftPoint(relive::Path_LiftPoint* pTlv, const Guid& tlvId);
    ~LiftPoint();
    
    void LoadAnimations();

    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;

    static s32 CreateFromSaveState(const u8* pData);

    void vKeepOnMiddleFloor();
    bool vOnTopFloor();
    bool vOnMiddleFloor();
    bool vOnBottomFloor();
    bool vOnAnyFloor();
    bool vOnAFloorLiftMoverCanUse();
    bool vMovingToFloorLevel();

    void vMove_4626A0(FP xSpeed, FP ySpeed, s32 not_used);

private:
    void MoveObjectsOnLift(FP xVelocity);
    static void sub_461000(relive::Path_TLV* pTlv);
    void vStayOnFloor(s16 floor, relive::Path_LiftPoint* pTlv);

    void CreatePulleyIfExists();

public:
    s16 field_12C_bMoving = 0;

private:
    relive::Path_LiftPoint::LiftPointStopType field_130_lift_point_stop_type = relive::Path_LiftPoint::LiftPointStopType::eTopFloor;
    Guid field_134_rope2_id;
    Guid field_138_rope1_id;
    Animation field_13C_lift_wheel = {};
    Animation field_1D4_pulley_anim = {};
    s16 field_26C_pulley_xpos = 0;
    s16 field_26E_pulley_ypos = 0;
    FP field_270_floorYLevel = {};

public:
    u8 field_278_lift_point_id = 0;

private:
    Guid field_27C_pTlv;
    enum LiftFlags
    {
        eBit1_bTopFloor = 0x1,
        eBit2_bMiddleFloor = 0x2,
        eBit3_bBottomFloor = 0x4,
        eBit4_bHasPulley = 0x8,
        eBit5_bMoveToFloorLevel = 0x10,
        eBit6 = 0x20, // This never seems to be used for anything
        eBit7_KeepOnMiddleFloor = 0x40,
        eBit8_bIgnoreLiftMover = 0x80,
    };
    BitField16<LiftFlags> field_280_flags = {};
};
