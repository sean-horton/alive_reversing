#include "stdafx.h"
#include "Abe.hpp"
#include "Function.hpp"
#include "Map.hpp"
#include "Sound/Midi.hpp"
#include "Sfx.hpp"
#include "DebugHelpers.hpp"
#include "stdlib.hpp"
#include "../relive_lib/Shadow.hpp"
#include "../relive_lib/ObjectIds.hpp"
#include "Input.hpp"
#include "../relive_lib/Events.hpp"
#include "QuikSave.hpp"
#include "MainMenu.hpp"
#include "ThrowableArray.hpp"
#include "MusicController.hpp"
#include "Path.hpp"
#include "GameSpeak.hpp"
#include "TrapDoor.hpp"
#include "MusicTrigger.hpp"
#include "ScreenShake.hpp"
#include "InvisibleEffect.hpp"
#include "Gibs.hpp"
#include "Throwable.hpp"
#include "ThrowableTotalIndicator.hpp"
#include "AbilityRing.hpp"
#include "OrbWhirlWind.hpp"
#include "Blood.hpp"
#include "PullRingRope.hpp"
#include "CircularFade.hpp"
#include "DeathFadeOut.hpp"
#include "Movie.hpp"
#include "PossessionFlicker.hpp"
#include "Door.hpp"
#include "QuikSave.hpp"
#include "DeathBirdParticle.hpp"
#include "WorkWheel.hpp"
#include "LevelLoader.hpp"
#include "../relive_lib/Particle.hpp"
#include "Lever.hpp"
#include "Throwable.hpp"
#include "LiftPoint.hpp"
#include "PullRingRope.hpp"
#include "BrewMachine.hpp"
#include "MineCar.hpp"
#include "EvilFart.hpp"
#include "../relive_lib/Particle.hpp"
#include "Mudokon.hpp"
#include "Electrocute.hpp"
#include "BirdPortal.hpp"
#include "BoomMachine.hpp"
#include "Shrykull.hpp"
#include "Bullet.hpp"
#include "Spark.hpp"
#include "TestAnimation.hpp"
#include "Sys_common.hpp"
#include "Grid.hpp"
#include "../relive_lib/Math.hpp"
#include "AnimationCallBacks.hpp"

using TAbeMotionFunction = decltype(&Abe::Motion_0_Idle_44EEB0);

#define MAKE_STRINGS(VAR) #VAR,
const char_type* const sAbeMotionNames[] = {
    ABE_MOTIONS_ENUM(MAKE_STRINGS)};

const TAbeMotionFunction sAbeMotionMachineTable_554910[] = {
    &Abe::Motion_0_Idle_44EEB0,
    &Abe::Motion_1_WalkLoop_44FBA0,
    &Abe::Motion_2_StandingTurn_451830,
    &Abe::Motion_3_Fall_459B60,
    &Abe::Motion_4_WalkToIdle_44FFC0,
    &Abe::Motion_5_MidWalkToIdle_450080,
    &Abe::Motion_6_WalkBegin_44FEE0,
    &Abe::Motion_7_Speak_45B140,
    &Abe::Motion_8_Speak_45B160,
    &Abe::Motion_9_Speak_45B180,
    &Abe::Motion_10_Fart_45B1A0,
    &Abe::Motion_11_ToSpeak_45B0A0,
    &Abe::Motion_12_Null_4569C0,
    &Abe::Motion_13_HoistBegin_452B20,
    &Abe::Motion_14_HoistIdle_452440,
    &Abe::Motion_15_HoistLand_452BA0,
    &Abe::Motion_16_LandSoft_45A360,
    &Abe::Motion_17_CrouchIdle_456BC0,
    &Abe::Motion_18_CrouchToStand_454600,
    &Abe::Motion_19_StandToCrouch_453DC0,
    &Abe::Motion_20_CrouchSpeak_454550,
    &Abe::jMotion_21_ToCrouchSpeak_4545E0,
    &Abe::Motion_22_RollBegin_4539A0,
    &Abe::Motion_23_RollLoop_453A90,
    &Abe::Motion_24_453D00,
    &Abe::Motion_25_RunSlideStop_451330,
    &Abe::Motion_26_RunTurn_451500,
    &Abe::Motion_27_HopBegin_4521C0,
    &Abe::Motion_28_HopMid_451C50,
    &Abe::Motion_29_HopLand_4523D0,
    &Abe::Motion_30_RunJumpBegin_4532E0,
    &Abe::Motion_31_RunJumpMid_452C10,
    &Abe::Motion_32_RunJumpLand_453460,
    &Abe::Motion_33_RunLoop_4508E0,
    &Abe::Motion_34_DunnoBegin_44ECF0,
    &Abe::Motion_35_DunnoEnd_44ED10,
    &Abe::Motion_36_Null_45BC50,
    &Abe::Motion_37_CrouchTurn_454390,
    &Abe::jMotion_38_RunToRoll_453A70,
    &Abe::Motion_39_StandingToRun_450D40,
    &Abe::Motion_40_SneakLoop_450550,
    &Abe::Motion_41_WalkToSneak_450250,
    &Abe::Motion_42_SneakToWalk_4503D0,
    &Abe::Motion_43_MidWalkToSneak_450380,
    &Abe::Motion_44_MidSneakToWalk_450500,
    &Abe::Motion_45_SneakBegin_4507A0,
    &Abe::Motion_46_SneakToIdle_450870,
    &Abe::jMotion_47_MidSneakToIdle_4508C0,
    &Abe::Motion_48_WalkToRun_4500A0,
    &Abe::Motion_49_MidWalkToRun_450200,
    &Abe::Motion_50_RunToWalk_450E20,
    &Abe::Motion_51_MidRunToWalk_450F50,
    &Abe::Motion_52_RunTurnToRun_451710,
    &Abe::Motion_53_RunTurnToWalk_451800,
    &Abe::Motion_54_RunJumpLandRun_4538F0,
    &Abe::Motion_55_RunJumpLandWalk_453970,
    &Abe::Motion_56_DeathDropFall_4591F0,
    &Abe::Motion_57_Dead_4589A0,
    &Abe::Motion_58_DeadPre_4593E0,
    &Abe::Motion_59_Null_459450,
    &Abe::Motion_60_Unused_4A3200,
    &Abe::Motion_61_TurnToRun_456530,
    &Abe::Motion_62_Punch_454750,
    &Abe::Motion_63_Sorry_454670,
    &Abe::Motion_64_AfterSorry_454730,
    &Abe::Motion_65_LedgeAscend_4548E0,
    &Abe::Motion_66_LedgeDescend_454970,
    &Abe::Motion_67_LedgeHang_454E20,
    &Abe::Motion_68_ToOffScreenHoist_454B80,
    &Abe::Motion_69_LedgeHangWobble_454EF0,
    &Abe::Motion_70_RingRopePullHang_455AF0,
    &Abe::Motion_71_Knockback_455090,
    &Abe::Motion_72_KnockbackGetUp_455340,
    &Abe::Motion_73_PushWall_4553A0,
    &Abe::Motion_74_RollingKnockback_455290,
    &Abe::Motion_75_JumpIntoWell_45C7B0,
    &Abe::Motion_76_ToInsideOfAWellLocal_45CA40,
    &Abe::Motion_77_ToWellShotOut_45D130,
    &Abe::Motion_78_WellBegin_45C810,
    &Abe::Motion_79_InsideWellLocal_45CA60,
    &Abe::Motion_80_WellShotOut_45D150,
    &Abe::jMotion_81_WellBegin_45C7F0,
    &Abe::Motion_82_InsideWellExpress_45CC80,
    &Abe::Motion_83_WellExpressShotOut_45CF70,
    &Abe::Motion_84_FallLandDie_45A420,
    &Abe::jMotion_85_Fall_455070,
    &Abe::Motion_86_HandstoneBegin_45BD00,
    &Abe::Motion_87_HandstoneEnd_45C4F0,
    &Abe::Motion_88_GrenadeMachineUse_45C510,
    &Abe::Motion_89_BrewMachineBegin_4584C0,
    &Abe::Motion_90_BrewMachineEnd_4585B0,
    &Abe::Motion_91_FallingFromGrab_4557B0,
    &Abe::Motion_92_ForceDownFromHoist_455800,
    &Abe::Motion_93_WalkOffEdge_455970,
    &Abe::Motion_94_RunOffEdge_4559A0,
    &Abe::Motion_95_SneakOffEdge_4559C0,
    &Abe::Motion_96_HopToFall_4559E0,
    &Abe::Motion_97_RunJumpToFall_455A80,
    &Abe::Motion_98_RollOffEdge_455AA0,
    &Abe::Motion_99_LeverUse_455AC0,
    &Abe::Motion_100_SlapBomb_455B60,
    &Abe::Motion_101_KnockForward_455420,
    &Abe::Motion_102_RollingKnockForward_455310,
    &Abe::jMotion_103_KnockForwardGetUp_455380,
    &Abe::Motion_104_RockThrowStandingHold_455DF0,
    &Abe::Motion_105_RockThrowStandingThrow_456460,
    &Abe::Motion_106_RockThrowStandingEnd_455F20,
    &Abe::Motion_107_RockThrowCrouchingHold_454410,
    &Abe::Motion_108_RockThrowCrouchingThrow_454500,
    &Abe::Motion_109_ZShotRolling_455550,
    &Abe::Motion_110_ZShot_455670,
    &Abe::Motion_111_PickupItem_4564A0,
    &Abe::Motion_112_Chant_45B1C0,
    &Abe::Motion_113_ChantEnd_45BBE0,
    &Abe::Motion_114_DoorEnter_459470,
    &Abe::Motion_115_DoorExit_459A40,
    &Abe::Motion_116_MineCarEnter_458780,
    &Abe::Motion_117_InMineCar_4587C0,
    &Abe::Motion_118_MineCarExit_458890,
    &Abe::Motion_119_ToShrykull_45A990,
    &Abe::Motion_120_EndShrykull_45AB00,
    &Abe::Motion_121_LiftGrabBegin_45A600,
    &Abe::Motion_122_LiftGrabEnd_45A670,
    &Abe::Motion_123_LiftGrabIdle_45A6A0,
    &Abe::Motion_124_LiftUseUp_45A780,
    &Abe::Motion_125_LiftUseDown_45A7B0,
    &Abe::Motion_126_TurnWheelBegin_456700,
    &Abe::Motion_127_TurnWheelLoop_456750,
    &Abe::Motion_128_TurnWheelEnd_4569A0,
    &Abe::Motion_129_PoisonGasDeath_4565C0};

const relive::SfxDefinition sAbeSFXList_555250[41] = {
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 24u, 60u, 115u, 0, 0},
    {0u, 24u, 61u, 110u, 0, 0},
    {0u, 24u, 62u, 127u, 0, 0},
    {0u, 24u, 63u, 90u, 0, 0},
    {0u, 24u, 66u, 127u, 0, 0},
    {0u, 24u, 67u, 100u, 0, 0},
    {0u, 24u, 56u, 127u, 0, 0},
    {0u, 24u, 57u, 100u, 0, 0},
    {0u, 23u, 48u, 127u, 0, 0},
    {0u, 24u, 59u, 127u, 0, 0},
    {0u, 24u, 58u, 127u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 24u, 65u, 127u, 0, 0},
    {0u, 24u, 64u, 80u, 0, 0},
    {0u, 23u, 60u, 90u, 0, 0},
    {0u, 23u, 68u, 127u, 0, 0},
    {0u, 23u, 69u, 127u, 0, 0},
    {0u, 23u, 70u, 127u, 0, 0},
    {0u, 23u, 72u, 127u, 0, 0},
    {0u, 23u, 73u, 127u, 0, 0},
    {0u, 23u, 58u, 127u, 0, 0},
    {0u, 23u, 64u, 127u, 0, 0},
    {0u, 23u, 66u, 115u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 23u, 63u, 115u, 0, 0},
    {0u, 23u, 62u, 90u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0}};

const AnimId sAbeAnimIdTable[130] = {
    AnimId::Mudokon_Idle,
    AnimId::Mudokon_Walk,
    AnimId::Mudokon_StandingTurn,
    AnimId::Mudokon_Idle,
    AnimId::Mudokon_WalkToIdle,
    AnimId::Mudokon_MidWalkToIdle,
    AnimId::Mudokon_WalkBegin,
    AnimId::Mudokon_Speak1,
    AnimId::Mudokon_Speak2,
    AnimId::Mudokon_Speak3,
    AnimId::Mudokon_SpeakFart,
    AnimId::Mudokon_ToSpeak,
    AnimId::Mudokon_Null,
    AnimId::Mudokon_HoistBegin,
    AnimId::Mudokon_HoistIdle,
    AnimId::Mudokon_LandSoft,
    AnimId::Mudokon_LandSoft,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchToStand,
    AnimId::Mudokon_StandToCrouch,
    AnimId::Mudokon_CrouchSpeak,
    AnimId::Mudokon_ToCrouchSpeak,
    AnimId::Mudokon_RollBegin,
    AnimId::Mudokon_Rolling,
    AnimId::Mudokon_RollingEnd_Unused,
    AnimId::Mudokon_RunSlideStop,
    AnimId::Mudokon_RunSlideTurn,
    AnimId::Mudokon_HopBegin,
    AnimId::Mudokon_HopMid,
    AnimId::Mudokon_HopLand,
    AnimId::Mudokon_RunJumpBegin,
    AnimId::Mudokon_RunJumpMid,
    AnimId::Mudokon_RunJumpLand,
    AnimId::Mudokon_Run,
    AnimId::Mudokon_DunnoBegin,
    AnimId::Mudokon_DunnoEnd,
    AnimId::Mudokon_DunnoBegin,
    AnimId::Mudokon_CrouchTurn,
    AnimId::Mudokon_RunToRoll,
    AnimId::Mudokon_StandToRun,
    AnimId::Mudokon_Sneak,
    AnimId::Mudokon_WalkToSneak,
    AnimId::Mudokon_SneakToWalk,
    AnimId::Mudokon_MidWalkToSneak,
    AnimId::Mudokon_MidSneakToWalk,
    AnimId::Mudokon_SneakBegin,
    AnimId::Mudokon_SneakToIdle,
    AnimId::Mudokon_MidSneakToIdle,
    AnimId::Mudokon_WalkToRun,
    AnimId::Mudokon_MidWalkToRun,
    AnimId::Mudokon_RunToWalk,
    AnimId::Mudokon_MidRunToWalk,
    AnimId::Mudokon_RunTurnToRun,
    AnimId::Mudokon_RunTurnToWalk,
    AnimId::Mudokon_RunJumpLandRun,
    AnimId::Mudokon_RunJumpLandWalk,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_TurnToRun,
    AnimId::Mudokon_Punch,
    AnimId::Mudokon_Sorry,
    AnimId::Mudokon_AfterSorry,
    AnimId::Mudokon_LedgeAscend,
    AnimId::Mudokon_LedgeDescend,
    AnimId::Mudokon_LedgeHang,
    AnimId::Mudokon_LedgeHang,
    AnimId::Mudokon_LedgeHangWobble,
    AnimId::Mudokon_RingRopePullHang,
    AnimId::Mudokon_Knockback,
    AnimId::Mudokon_KnockbackGetUp,
    AnimId::Mudokon_PushWall,
    AnimId::Mudokon_RollingKnockback,
    AnimId::Mudokon_JumpIntoWell,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_WellBegin,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_WellBegin,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_FallLandDie,
    AnimId::Mudokon_Fall,
    AnimId::Mudokon_HandstoneBegin,
    AnimId::Mudokon_HandstoneEnd,
    AnimId::Mudokon_GrenadeMachineUse,
    AnimId::Mudokon_HandstoneBegin,
    AnimId::Mudokon_HandstoneEnd,
    AnimId::Mudokon_FallingFromGrab,
    AnimId::Mudokon_FallingFromGrab,
    AnimId::Mudokon_WalkOffEdge,
    AnimId::Mudokon_RunOffEdge,
    AnimId::Mudokon_SneakOffEdge,
    AnimId::Mudokon_HopToFall,
    AnimId::Mudokon_RunJumpToFall,
    AnimId::Mudokon_RollOffEdge,
    AnimId::Mudokon_LeverUse,
    AnimId::Mudokon_SlapBomb,
    AnimId::Mudokon_KnockForward,
    AnimId::Mudokon_RollingKnockForward,
    AnimId::Mudokon_Idle, // KnockForwardGetUp?
    AnimId::Mudokon_RockThrowStandingHold,
    AnimId::Mudokon_RockThrowStandingThrow,
    AnimId::Mudokon_RockThrowStandingEnd,
    AnimId::Mudokon_RockThrowCrouchingHold,
    AnimId::Mudokon_RockThrowCrouchingThrow,
    AnimId::Mudokon_ZShotRolling,
    AnimId::Mudokon_ZShot,
    AnimId::Mudokon_PickupItem,
    AnimId::Mudokon_Chant,
    AnimId::Mudokon_ChantEnd,
    AnimId::Mudokon_DoorEnter,
    AnimId::Mudokon_DoorExit,
    AnimId::Mudokon_MineCarEnter,
    AnimId::Mudokon_MineCarEnter,
    AnimId::Mudokon_MineCarExit,
    AnimId::Mudokon_ToShrykull,
    AnimId::Mudokon_EndShrykull,
    AnimId::Mudokon_LiftGrabBegin,
    AnimId::Mudokon_LiftGrabEnd,
    AnimId::Mudokon_LiftGrabIdle,
    AnimId::Mudokon_LiftUseUp,
    AnimId::Mudokon_LiftUseDown,
    AnimId::Mudokon_TurnWheelBegin,
    AnimId::Mudokon_TurnWheel,
    AnimId::Mudokon_TurnWheelEnd,
    AnimId::Mudokon_PoisonGasDeath};

const TintEntry sAbeTintTable[15] = {
    {EReliveLevelIds::eMines, 102u, 102u, 102u},
    {EReliveLevelIds::eNecrum, 102u, 102u, 80u},
    {EReliveLevelIds::eMudomoVault, 120u, 90u, 120u},
    {EReliveLevelIds::eMudancheeVault, 102u, 70u, 90u},
    {EReliveLevelIds::eFeeCoDepot, 120u, 102u, 82u},
    {EReliveLevelIds::eBarracks, 102u, 102u, 102u},
    {EReliveLevelIds::eMudancheeVault_Ender, 102u, 70u, 90u},
    {EReliveLevelIds::eBonewerkz, 102u, 102u, 102u},
    {EReliveLevelIds::eBrewery, 102u, 102u, 102u},
    {EReliveLevelIds::eBrewery_Ender, 102u, 102u, 102u},
    {EReliveLevelIds::eMudomoVault_Ender, 120u, 90u, 120u},
    {EReliveLevelIds::eFeeCoDepot_Ender, 120u, 102u, 82u},
    {EReliveLevelIds::eBarracks_Ender, 102u, 102u, 102u},
    {EReliveLevelIds::eBonewerkz_Ender, 120u, 90u, 80u},
    {EReliveLevelIds::eNone, 102u, 102u, 102u}};

const relive::SfxDefinition sSFXList_555160[] = {
    {0u, 3u, 69u, 60u, -1, 1},
    {0u, 3u, 70u, 60u, -1, 1},
    {0u, 3u, 59u, 67u, -1, 1},
    {0u, 3u, 61u, 67u, -1, 1},
    {0u, 3u, 58u, 52u, -1, 1},
    {0u, 3u, 67u, 45u, -1, 1},
    {0u, 3u, 57u, 60u, -1, 1},
    {0u, 3u, 65u, 50u, -1, 1},
    {0u, 3u, 68u, 60u, -1, 1},
    {0u, 3u, 72u, 70u, -1, 1},
    {0u, 3u, 36u, 50u, -127, 0},
    {0u, 3u, 37u, 50u, -127, 0},
    {0u, 3u, 38u, 50u, -127, 0},
    {0u, 3u, 36u, 55u, 0, 127},
    {0u, 3u, 37u, 55u, 0, 127},
    {0u, 3u, 38u, 55u, 0, 127},
    {0u, 3u, 61u, 50u, -1, 1},
    {0u, 3u, 73u, 127u, -1, 1},
    {0u, 4u, 80u, 127u, -1, 1},
    {0u, 65u, 64u, 60u, -1, 0},
    {0u, 11u, 62u, 60u, -1, 1},
    {0u, 11u, 64u, 60u, -1, 1},
    {0u, 11u, 65u, 50u, -1, 1},
    {0u, 11u, 64u, 50u, -1, 1},
    {0u, 11u, 66u, 50u, -1, 1},
    {0u, 23u, 60u, 90u, 0, 0},
    {0u, 23u, 61u, 90u, 0, 0},
    {0u, 23u, 62u, 90u, 0, 0},
    {0u, 23u, 63u, 90u, 0, 0},
    {0u, 23u, 64u, 90u, 0, 0}};


bool IsActiveHero(BaseGameObject* pObj)
{
    if (sActiveHero)
    {
        return sActiveHero == pObj;
    }
    return false;
}

s32 Environment_SFX_457A40(EnvironmentSfx sfxId, s32 volume, s32 pitchMin, BaseAliveGameObject* pAliveObj)
{
    s32 sndVolume;
    s16 sndIndex = 0;

    switch (sfxId)
    {
        case EnvironmentSfx::eSlideStop_0:
            sndIndex = 11;
            sndVolume = 40;
            break;

        case EnvironmentSfx::eWalkingFootstep_1:
            sndVolume = volume;
            sndIndex = Math_RandomRange(10, 12);
            if (volume)
            {
                break;
            }
            sndVolume = Math_RandomRange(54, 58);
            if (pAliveObj)
            {
                if (pAliveObj->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible))
                {
                    sndVolume *= 3;
                }
            }
            break;

        case EnvironmentSfx::eRunningFootstep_2:
            sndVolume = volume;
            sndIndex = Math_RandomRange(13, 15);
            if (volume)
            {
                break;
            }

            sndVolume = Math_RandomRange(66, 70);

            if (pAliveObj)
            {
                if (pAliveObj->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible))
                {
                    sndVolume *= 3;
                }
            }
            break;

        case EnvironmentSfx::eSneakFootstep_3:
            sndIndex = 5;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eRunSlide_4:
            sndIndex = 4;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eLandingSoft_5:
            if (volume || !pAliveObj || pAliveObj->mSpriteScale != FP_FromDouble(0.5))
            {
                return SFX_SfxDefinition_Play_Mono(sSFXList_555160[2], static_cast<s16>(volume), static_cast<s16>(pitchMin), 0x7FFF) | SFX_SfxDefinition_Play_Mono(sAbeSFXList_555250[16], static_cast<s16>(volume), static_cast<s16>(pitchMin), 0x7FFF);
            }
            else
            {
                return SFX_SfxDefinition_Play_Mono(sSFXList_555160[2], sSFXList_555160[2].field_C_default_volume / 2, static_cast<s16>(pitchMin), 0x7FFF) | SFX_SfxDefinition_Play_Mono(sAbeSFXList_555250[16], sSFXList_555160[16].field_C_default_volume / 2, static_cast<s16>(pitchMin), 0x7FFF);
            }

        case EnvironmentSfx::eHitGroundSoft_6:
            sndIndex = 2;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eDeathNoise_7:
            sndIndex = 16;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eRollingNoise_8:
            sndIndex = 6;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eGenericMovement_9:
        case EnvironmentSfx::eRunJumpOrLedgeHoist_11:
            if (pAliveObj && pAliveObj->mSpriteScale == FP_FromDouble(0.5))
            {
                return SfxPlayMono(relive::SoundEffects::AbeGenericMovement, 20);
            }
            else
            {
                return SfxPlayMono(relive::SoundEffects::AbeGenericMovement, 35);
            }

        case EnvironmentSfx::eExhaustingHoistNoise_10:
            sndIndex = 19;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eAllOYa_12:
            sndIndex = 25;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eKnockback_13:
            if (gMap.mCurrentLevel == EReliveLevelIds::eMines
                || gMap.mCurrentLevel == EReliveLevelIds::eBonewerkz
                || gMap.mCurrentLevel == EReliveLevelIds::eFeeCoDepot
                || gMap.mCurrentLevel == EReliveLevelIds::eBarracks
                || gMap.mCurrentLevel == EReliveLevelIds::eBrewery)
            {
                sndIndex = 2;
            }
            else
            {
                sndIndex = 9;
            }
            sndVolume = volume;
            break;

        case EnvironmentSfx::eElumHitWall_14:
            sndIndex = 17;
            sndVolume = volume;
            break;

        case EnvironmentSfx::eFallingDeathScreamHitGround_15:
            return 0;

        default:
            sndVolume = volume;
            break;
    }

    if (!sndVolume)
    {
        sndVolume = sSFXList_555160[sndIndex].field_C_default_volume;
    }

    if (!pAliveObj)
    {
        return SFX_SfxDefinition_Play_Mono(sSFXList_555160[sndIndex], static_cast<s16>(sndVolume), static_cast<s16>(pitchMin), 0x7FFF);
    }

    if (pAliveObj->mSpriteScale == FP_FromDouble(0.5))
    {
        sndVolume = 2 * sndVolume / 3;
    }

    if (!IsActiveHero(pAliveObj))
    {
        switch (gMap.GetDirection(
            pAliveObj->mCurrentLevel,
            pAliveObj->mCurrentPath,
            pAliveObj->mXPos,
            pAliveObj->mYPos))
        {
            case CameraPos::eCamCurrent_0:
                return SFX_SfxDefinition_Play_Mono(sSFXList_555160[sndIndex], static_cast<s16>(sndVolume), static_cast<s16>(pitchMin), 0x7FFF);
            case CameraPos::eCamTop_1:
            case CameraPos::eCamBottom_2:
                return SFX_SfxDefinition_Play_Mono(sSFXList_555160[sndIndex], static_cast<s16>(2 * sndVolume / 3), static_cast<s16>(pitchMin), 0x7FFF);
            case CameraPos::eCamLeft_3:
                return SFX_SfxDefinition_Play_Stereo(
                    sSFXList_555160[sndIndex],
                    static_cast<s16>(2 * sndVolume / 9),
                    static_cast<s16>(2 * sndVolume / 9),
                    static_cast<s16>(pitchMin),
                    0x7FFF);
                break;
            case CameraPos::eCamRight_4:
                return SFX_SfxDefinition_Play_Stereo(
                    sSFXList_555160[sndIndex],
                    static_cast<s16>(2 * sndVolume / 3),
                    static_cast<s16>(2 * sndVolume / 3),
                    static_cast<s16>(pitchMin),
                    0x7FFF);
                break;
            default:
                return 0;
        }
    }
    else
    {
        return SFX_SfxDefinition_Play_Mono(sSFXList_555160[sndIndex], static_cast<s16>(sndVolume), static_cast<s16>(pitchMin), 0x7FFF);
    }
}

const FP_Point sThrowVelocities_555118[9] = {
    {FP_FromInteger(3), FP_FromInteger(-14)},
    {FP_FromInteger(10), FP_FromInteger(-10)},
    {FP_FromInteger(15), FP_FromInteger(-8)},
    {FP_FromInteger(10), FP_FromInteger(3)},
    {FP_FromInteger(10), FP_FromInteger(-4)},
    {FP_FromInteger(4), FP_FromInteger(-3)},
    {FP_FromInteger(0), FP_FromInteger(0)},
    {FP_FromInteger(0), FP_FromInteger(0)},
    {FP_FromInteger(0), FP_FromInteger(0)}};


void Animation_OnFrame_Abe_455F80(BaseGameObject* pPtr, u32&, const Point32& point)
{
    auto pAbe = static_cast<Abe*>(pPtr);

    auto pThrowable = static_cast<BaseThrowable*>(sObjectIds.Find_Impl(sActiveHero->mThrowableId));

    auto tableX = sThrowVelocities_555118[pAbe->mThrowDirection].x * pAbe->mSpriteScale;
    const auto tableY = sThrowVelocities_555118[pAbe->mThrowDirection].y * pAbe->mSpriteScale;

    FP xOff = {};
    if (sActiveHero->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        tableX = -tableX;
        xOff = -(pAbe->mSpriteScale * FP_FromInteger(point.x));
    }
    else
    {
        xOff = pAbe->mSpriteScale * FP_FromInteger(point.x);
    }

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    if (sCollisions->Raycast(
            pAbe->mXPos,
            pAbe->mYPos + FP_FromInteger(point.y),
            xOff + pAbe->mXPos,
            pAbe->mYPos + FP_FromInteger(point.y),
            &pLine,
            &hitX,
            &hitY,
            pAbe->mScale == Scale::Fg ? kFgWalls : kBgWalls))
    {
        xOff = hitX - pAbe->mXPos;
        tableX = -tableX;
    }

    if (pThrowable)
    {
        pThrowable->mXPos = xOff + sActiveHero->mXPos;
        pThrowable->mYPos = (pAbe->mSpriteScale * FP_FromInteger(point.y)) + sActiveHero->mYPos;
        pThrowable->VThrow(tableX, tableY);
        pThrowable->mSpriteScale = pAbe->mSpriteScale;
        pThrowable->mScale = pAbe->mScale;
        sActiveHero->mThrowableId = Guid{};
    }
}

s32 XGrid_Index_To_XPos_4498F0(FP scale, s32 xGridIndex)
{
    if (scale == FP_FromDouble(0.5))
    {
        // 12.5 = half grid size
        return (13 * xGridIndex) - 8;
    }

    if (scale == FP_FromDouble(1.0))
    {
        // 25 = full grid size
        return (25 * xGridIndex) - 13;
    }

    // Default to middle of the screen
    return (374 / 2);
}

ALIVE_VAR(1, 0x5c1b8c, BaseAliveGameObject*, sControlledCharacter, nullptr);

static constexpr s32 kResourceArraySize = 28;

void Abe::LoadAnimations()
{
    for (auto& animId : sAbeAnimIdTable)
    {
        mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(animId));
    }
}

Abe::Abe()
    : BaseAliveGameObject(kResourceArraySize)
{
    SetType(ReliveTypes::eAbe);

    mBaseGameObjectFlags.Set(BaseGameObject::eSurviveDeathReset_Bit9);

    // Set the well level to the current level for the path start quick save
    mDstWellLevel = gMap.mCurrentLevel;

    Init_GameStates_43BF40();

    LoadAnimations();
    Animation_Init(GetAnimRes(AnimId::Mudokon_Idle));

    mAnim.mFnPtrArray = kAbe_Anim_Frame_Fns_55EF98;

    PSX_Point point = {};
    gMap.GetCurrentCamCoords(&point);

    mXPos = FP_FromInteger(point.x + XGrid_Index_To_XPos_4498F0(mSpriteScale, 4));
    mYPos = FP_FromInteger(point.y + 120);

    BaseAliveGameObjectLastLineYPos = mYPos;
    field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
    field_128.field_C_unused = 0;

    mVelX = FP_FromInteger(0);
    mVelY = FP_FromInteger(0);
    BaseAliveGameObjectCollisionLine = nullptr;
    mCurrentMotion = eAbeMotions::Motion_3_Fall_459B60;
    mKnockdownMotion = -1;
    mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
    mHasEvilFart = 0;
    mThrowableCount = 0;

    field_1AE_flags.Clear(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender);
    field_1AE_flags.Clear(Flags_1AE::e1AE_Bit2_do_quicksave);

    mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit6_SetOffExplosives);

    field_1AC_flags.Raw().all = 0;

    field_1AC_flags.Set(Flags_1AC::e1AC_Bit6_prevent_chanting);
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit7_land_softly);

    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit5_shrivel);
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3_WalkToRun);
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit1_lift_point_dead_while_using_lift);

    // Changes Abe's "default" colour depending on the level we are in
    SetTint(&sAbeTintTable[0], gMap.mCurrentLevel);

    mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);
    mAnim.mRenderMode = TPageAbr::eBlend_0;

    mPrevHeld = 0;
    mBaseAliveGameObjectLastAnimFrame = 0;
    field_120_state.raw = 0;
    mRingPulseTimer = 0;
    mHaveInvisibility = 0;
    mInvisibilityTimer = 0;
    mInvisibilityDuration = 0;
    field_124_timer = sGnFrame;
    BaseAliveGameObjectPathTLV = nullptr;
    field_128.mMood = Mud_Emotion::eNormal_0;
    field_128.mSay = MudSounds::eNone;
    mAutoSayTimer = 0;

    // Set Abe to be the current player controlled object
    sControlledCharacter = this;

    // Create shadow
    mShadow = relive_new Shadow();

    // Animation test code
    //relive_new TestAnimation();

}

Abe::~Abe()
{
    BaseGameObject* pFadeObject = sObjectIds.Find_Impl(mDeathFadeOutId);
    BaseGameObject* pCircularFade = sObjectIds.Find_Impl(mCircularFadeId);
    BaseGameObject* pOrbWhirlWind = sObjectIds.Find_Impl(mOrbWhirlWindId);
    BaseGameObject* pPossessedObject = sObjectIds.Find_Impl(mPossessedObjectId);
    BaseGameObject* pThrowable = sObjectIds.Find_Impl(mThrowableId);
    BaseGameObject* pPullRope = sObjectIds.Find_Impl(mPullRingRopeId);
    BaseGameObject* pItem = sObjectIds.Find_Impl(mSlappableOrPickupId);
    BaseGameObject* pInvisibleEffect = sObjectIds.Find_Impl(mInvisibleEffectId);

    SND_SEQ_Stop(SeqId::MudokonChant1_10);

    if (pFadeObject)
    {
        pFadeObject->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mDeathFadeOutId = Guid{};
    }

    if (pItem)
    {
        mSlappableOrPickupId = Guid{};
    }

    if (pPullRope)
    {
        pPullRope->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mPullRingRopeId = Guid{};
    }

    if (pCircularFade)
    {
        pCircularFade->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mCircularFadeId = Guid{};
    }

    if (pOrbWhirlWind)
    {
        pOrbWhirlWind->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mOrbWhirlWindId = Guid{};
    }

    if (pPossessedObject)
    {
        mPossessedObjectId = Guid{};
    }

    if (pThrowable)
    {
        pThrowable->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mThrowableId = Guid{};
    }

    if (pInvisibleEffect)
    {
        pInvisibleEffect->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mInvisibleEffectId = Guid{};
    }

    mWorkWheelId = Guid{};

    sActiveHero = nullptr;
}


s32 Abe::CreateFromSaveState(const u8* pData)
{
    const Abe_SaveState* pSaveState = reinterpret_cast<const Abe_SaveState*>(pData);

    Abe* pAbe = sActiveHero;
    if (!sActiveHero)
    {
        pAbe = relive_new Abe();
        sActiveHero = pAbe;
    }

    if (pSaveState->mIsAbeControlled)
    {
        sControlledCharacter = pAbe;
    }

    sActiveHero->BaseAliveGameObjectPathTLV = nullptr;
    sActiveHero->BaseAliveGameObjectCollisionLine = nullptr;
    sActiveHero->mXPos = pSaveState->mXPos;
    sActiveHero->mYPos = pSaveState->mYPos;
    sActiveHero->mVelX = pSaveState->mVelX;
    sActiveHero->mVelY = pSaveState->mVelY;
    sActiveHero->field_128.field_8_x_vel_slow_by = pSaveState->field_48_x_vel_slow_by;
    sActiveHero->field_128.field_C_unused = pSaveState->field_4C_unused;
    sActiveHero->mCurrentPath = pSaveState->mCurrentPath;
    sActiveHero->mCurrentLevel = MapWrapper::FromAESaveData(pSaveState->mCurrentLevel);
    sActiveHero->mSpriteScale = pSaveState->mSpriteScale;
    sActiveHero->mScale = pSaveState->mScale;

    sActiveHero->mCurrentMotion = pSaveState->mCurrentMotion;

    /* TODO: Async load if res unloaded
    u8** animFromState = sActiveHero->MotionToAnimResource_44AAB0(sActiveHero->mCurrentMotion);
    if (!animFromState)
    {
        u32 id = sAbeResourceIDTable_554D60[sActiveHero->field_128.field_10_resource_index];
        ResourceManager::LoadResourceFile_49C170(sAbe_ResNames_545830[sActiveHero->field_128.field_10_resource_index], 0);
        sActiveHero->field_10_resources_array.SetAt(sActiveHero->field_128.field_10_resource_index, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, id, TRUE, FALSE));
        animFromState = sActiveHero->field_10_resources_array.ItemAt(sActiveHero->field_128.field_10_resource_index);
    }*/

    sActiveHero->mAnim.Set_Animation_Data(sActiveHero->GetAnimRes(sAbeAnimIdTable[sActiveHero->mCurrentMotion]));
    //sActiveHero->mAnim.Set_Animation_Data_409C80(sAbeAnimIdTable[sActiveHero->mCurrentMotion], animFromState);

    sActiveHero->mAnim.mCurrentFrame = pSaveState->mCurrentFrame;
    sActiveHero->mAnim.mFrameChangeCounter = pSaveState->mFrameChangeCounter;

    sActiveHero->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pSaveState->bAnimFlipX & 1);
    sActiveHero->mAnim.mFlags.Set(AnimFlags::eBit3_Render, pSaveState->mAnimRender & 1);
    sActiveHero->mBaseGameObjectFlags.Set(BaseGameObject::eDrawable_Bit4, pSaveState->mIsDrawable & 1);

    sActiveHero->mAnim.mRenderLayer = static_cast<Layer>(pSaveState->mRenderLayer);

    if (IsLastFrame(&sActiveHero->mAnim))
    {
        sActiveHero->mAnim.mFlags.Set(AnimFlags::eBit18_IsLastFrame);
    }

    // TODO: Pal re-loading
    /*
    const PerFrameInfo* pFrameInfoHeader = sActiveHero->mAnim.Get_FrameHeader(-1);
    sActiveHero->mAnim.LoadPal(sActiveHero->mAnim.field_20_ppBlock, pFrameHeader->field_0_clut_offset);
    */
    sActiveHero->mAnim.ReloadPal();

    sActiveHero->SetTint(sAbeTintTable, gMap.mCurrentLevel);
    sActiveHero->mAnim.mRenderMode = TPageAbr::eBlend_0;
    sActiveHero->mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);
    sActiveHero->mAnim.mFlags.Clear(AnimFlags::eBit16_bBlending);
    sActiveHero->mHealth = pSaveState->mHealth;
    sActiveHero->mCurrentMotion = pSaveState->mCurrentMotion2;
    sActiveHero->mNextMotion = pSaveState->mNextMotion;
    sActiveHero->BaseAliveGameObjectLastLineYPos = FP_FromInteger(pSaveState->mLastLineYPos);
    sActiveHero->BaseAliveGameObject_PlatformId = pSaveState->mPlatformId;
    sActiveHero->field_120_state.raw = static_cast<u16>(pSaveState->field_50_state);
    sActiveHero->field_124_timer = pSaveState->field_54_timer;
    sActiveHero->field_128.field_0_abe_timer = pSaveState->field_58_abe_timer;
    sActiveHero->field_128.mRegenHealthTimer = pSaveState->mRegenHealthTimer;
    sActiveHero->field_128.mMood = pSaveState->mMood;
    sActiveHero->field_128.mSay = pSaveState->mSay;
    sActiveHero->mAutoSayTimer = pSaveState->mAutoSayTimer;
    sActiveHero->mThrowableCount = pSaveState->mThrowableCount;
    sActiveHero->mRingPulseTimer = pSaveState->mRingPulseTimer;
    sActiveHero->mHaveShrykull = pSaveState->mHaveShrykull;

    if (sActiveHero->mRingPulseTimer && sActiveHero->mHaveShrykull)
    {
        if (!sActiveHero->field_10_resources_array.ItemAt(25))
        {
            if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbemorphResID, FALSE, FALSE))
            {
                ResourceManager::LoadResourceFile_49C170("SHRYPORT.BND", nullptr);
            }
            if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kSplineResID, FALSE, FALSE))
            {
                ResourceManager::LoadResourceFile_49C170("SPLINE.BAN", nullptr);
            }
            sActiveHero->Get_Shrykull_Resources_45AA20();
        }
    }
    else
    {
        if (sActiveHero->field_10_resources_array.ItemAt(25))
        {
            sActiveHero->Free_Shrykull_Resources_45AA90();
        }
    }

    sActiveHero->mHaveInvisibility = pSaveState->bHaveInvisiblity;
    sActiveHero->BaseAliveGameObjectCollisionLineType = pSaveState->mCollisionLineType;

    sActiveHero->mPrevHeld = InputObject::PsxButtonsToKeyboardInput_45EE40(pSaveState->mPrevHeld);
    sActiveHero->mReleasedButtons = InputObject::PsxButtonsToKeyboardInput_45EE40(pSaveState->mReleasedButtons);
    sActiveHero->mKnockdownMotion = pSaveState->mKnockdownMotion;
    sActiveHero->field_128.mRollingMotionTimer = sGnFrame - pSaveState->mRollingMotionTimer;

    sActiveHero->mDeathFadeOutId = pSaveState->mDeathFadeOutId;
    sActiveHero->mCircularFadeId = pSaveState->mCircularFadeId;
    sActiveHero->mOrbWhirlWindId = pSaveState->mOrbWhirlWindId;
    sActiveHero->mPossessedObjectId = pSaveState->mPossessedObjectId;
    sActiveHero->mThrowableId = pSaveState->mThrowableId;
    sActiveHero->mPullRingRopeId = pSaveState->mPullRingRopeId;
    sActiveHero->mSlappableOrPickupId = pSaveState->mSlappableOrPickupId;
    sActiveHero->mWorkWheelId = pSaveState->mWorkWheelId;
    sActiveHero->mInvisibleEffectId = Guid{};

    sActiveHero->mInvisibilityTimer = pSaveState->mInvisibilityTimer;
    sActiveHero->field_174_unused = pSaveState->field_A0_unused;
    sActiveHero->mInvisibilityDuration = pSaveState->mInvisibilityDuration;

    sActiveHero->mHandStoneCamIdx = pSaveState->mHandStoneCamIdx;
    sActiveHero->mHandStoneType = pSaveState->mHandStoneType;
    sActiveHero->mFmvId = pSaveState->mFmvId;
    sActiveHero->mHandStoneCams[0] = pSaveState->mHandStoneCam1;
    sActiveHero->mHandStoneCams[1] = pSaveState->mHandStoneCam2;
    sActiveHero->mHandStoneCams[2] = pSaveState->mHandStoneCam3;

    sActiveHero->field_18C_unused = pSaveState->field_B4_unused;
    sActiveHero->field_18E_unused = pSaveState->field_B6_unused;
    sActiveHero->field_190_unused = pSaveState->field_B8_unused;
    sActiveHero->field_192_unused = pSaveState->field_BA_unused;
    sActiveHero->field_194_unused = pSaveState->field_BC_unused;
    sActiveHero->field_196_unused = pSaveState->field_BE_unused;

    sActiveHero->mHasEvilFart = pSaveState->mHasEvilFart;
    sActiveHero->mDstWellLevel = MapWrapper::FromAESaveData(pSaveState->mDstWellLevel);
    sActiveHero->mDstWellPath = pSaveState->mDstWellPath;
    sActiveHero->mDstWellCamera = pSaveState->mDstWellCamera;
    sActiveHero->field_1A0_door_id = pSaveState->door_id;
    sActiveHero->mThrowDirection = pSaveState->mThrowDirection;
    sActiveHero->mBirdPortalSubState = static_cast<PortalSubStates>(pSaveState->mBirdPortalSubState);
    sActiveHero->mBirdPortalId = pSaveState->mBirdPortalId;

    sActiveHero->mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit7_Electrocuted, pSaveState->mIsElectrocuted & 1);
    sActiveHero->mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit8_bInvisible, pSaveState->mIsInvisible & 1);
    sActiveHero->mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit10_Teleporting, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_eBit13_teleporting));

    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit1_lift_point_dead_while_using_lift, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit1_lift_point_dead_while_using_lift));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit2_return_to_previous_motion));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit3_WalkToRun, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit3_WalkToRun));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit4_unused, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit4_unused));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit5_shrivel, pSaveState->bShrivel);
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit6_prevent_chanting, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit5_prevent_chanting));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit7_land_softly, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit6_land_softly));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit8_unused, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit7_unused));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit9_laugh_at_chant_end, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit8_laugh_at_chant_end));

    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_Bit12_unused, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit9_unused));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit10_play_ledge_grab_sounds));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_eBit14_unused, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit11_unused));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_eBit15_have_healing, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_Bit12_have_healing));
    sActiveHero->mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit10_Teleporting, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_eBit13_teleporting));
    sActiveHero->field_1AC_flags.Set(Flags_1AC::e1AC_eBit16_is_mudanchee_vault_ender, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_eBit14_is_mudanchee_vault_ender));

    sActiveHero->field_1AE_flags.Set(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_eBit15_is_mudomo_vault_ender));
    sActiveHero->mShadow->mFlags.Set(Shadow::Flags::eEnabled, pSaveState->field_D4_flags.Get(Abe_SaveState::eD4_eBit16_shadow_enabled));

    sActiveHero->mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom, pSaveState->field_D6_flags.Get(Abe_SaveState::eD6_Bit1_shadow_at_bottom));

    if (sActiveHero->mHasEvilFart)
    {
        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kEvilFartResID, FALSE, FALSE))
        {
            ResourceManager::LoadResourceFile_49C170("EVILFART.BAN", nullptr);
        }

        if (!sActiveHero->field_10_resources_array.ItemAt(22))
        {
            sActiveHero->field_10_resources_array.SetAt(22, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kEvilFartResID, TRUE, FALSE));
        }

        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kExplo2ResID, 0, 0))
        {
            ResourceManager::LoadResourceFile_49C170("EXPLO2.BAN", nullptr);
        }

        if (!sActiveHero->field_10_resources_array.ItemAt(24))
        {
            sActiveHero->field_10_resources_array.SetAt(24, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kExplo2ResID, TRUE, FALSE));
        }

        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbeblowResID, 0, 0))
        {
            ResourceManager::LoadResourceFile_49C170("ABEBLOW.BAN", nullptr);
        }

        if (!sActiveHero->field_10_resources_array.ItemAt(23))
        {
            sActiveHero->field_10_resources_array.SetAt(23, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbeblowResID, TRUE, FALSE));
        }
    }

    return sizeof(Abe_SaveState);
}

const FP sAbe_xVel_table_545770[8] = {
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(0),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(0),
    FP_FromInteger(4)};

const FP sAbe_yVel_table_545790[8] = {
    FP_FromInteger(0),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(0),
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(4)};

ALIVE_VAR(1, 0x5c1bda, s16, gAbeBulletProof_5C1BDA, 0);


void Abe::VUpdate()
{
    if (gAbeBulletProof_5C1BDA) // Some flag to reset HP?
    {
        mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit7_Electrocuted);
        mHealth = FP_FromDouble(1.0);
    }

    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit9_RestoredFromQuickSave))
    {
        mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit9_RestoredFromQuickSave);
        if (BaseAliveGameObjectCollisionLineType != -1)
        {
            sCollisions->Raycast(
                mXPos,
                mYPos - FP_FromInteger(20),
                mXPos,
                mYPos + FP_FromInteger(20),
                &BaseAliveGameObjectCollisionLine,
                &mXPos,
                &mYPos,
                CollisionMask(static_cast<eLineTypes>(BaseAliveGameObjectCollisionLineType)));

            BaseAliveGameObjectCollisionLineType = -1;
        }

        BaseAliveGameObject_PlatformId = BaseGameObject::RefreshId(BaseAliveGameObject_PlatformId);
        mDeathFadeOutId = BaseGameObject::RefreshId(mDeathFadeOutId);
        mCircularFadeId = BaseGameObject::RefreshId(mCircularFadeId);
        mBirdPortalId = BaseGameObject::RefreshId(mBirdPortalId);
        mOrbWhirlWindId = BaseGameObject::RefreshId(mOrbWhirlWindId);
        mPossessedObjectId = BaseGameObject::RefreshId(mPossessedObjectId);
        mThrowableId = BaseGameObject::RefreshId(mThrowableId);
        mPullRingRopeId = BaseGameObject::RefreshId(mPullRingRopeId);
        mSlappableOrPickupId = BaseGameObject::RefreshId(mSlappableOrPickupId);
        mWorkWheelId = BaseGameObject::RefreshId(mWorkWheelId);

        if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible))
        {
            if (!mInvisibilityTimer)
            {
                mInvisibilityTimer = sGnFrame + 2;
            }

            auto pInvisibleEffect = relive_new InvisibleEffect(this);
            mInvisibleEffectId = pInvisibleEffect->mBaseGameObjectId;
            pInvisibleEffect->InstantInvisibility();
        }
    }

    if (field_1AC_flags.Get(Flags_1AC::e1AC_Bit12_unused))
    {
        return;
    }

    if (gAbeBulletProof_5C1BDA)
    {
        mHealth = FP_FromDouble(1.0);
    }

    if (!Input_IsChanting_45F260())
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_Bit6_prevent_chanting);
        field_174_unused = 1;
    }

    const s32 totalAliveSavedMuds = sRescuedMudokons_5C1BC2 - sKilledMudokons_5C1BC0;
    if (totalAliveSavedMuds > 0)
    {
        // "Happy" voice
        field_128.mMood = Mud_Emotion::eHappy_5;
    }
    else if (totalAliveSavedMuds < 0)
    {
        // "Sad" voice
        field_128.mMood = Mud_Emotion::eSad_3;
    }
    else
    {
        // "Normal" voice
        field_128.mMood = Mud_Emotion::eNormal_0;
    }

    // Handle DDCheat mode
    if (sDDCheat_FlyingEnabled_5C2C08 && sControlledCharacter == this)
    {
        VOnTrapDoorOpen();

        BaseAliveGameObjectLastLineYPos = mYPos;
        field_1AC_flags.Clear(Flags_1AC::e1AC_Bit5_shrivel);
        mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
        BaseAliveGameObjectCollisionLine = nullptr;

        if (Input().mPads[sCurrentControllerIndex].mPressed & (InputCommands::Enum::eRight | InputCommands::Enum::eLeft | InputCommands::Enum::eDown | InputCommands::Enum::eUp))
        {
            mVelX = sAbe_xVel_table_545770[(u8) Input().mPads[sCurrentControllerIndex].mDir >> 5];
            mVelY = sAbe_yVel_table_545790[(u8) Input().mPads[sCurrentControllerIndex].mDir >> 5];

            if (sInputKey_Run & Input().mPads[sCurrentControllerIndex].mPressed)
            {
                mVelX += sAbe_xVel_table_545770[(u8) Input().mPads[sCurrentControllerIndex].mDir >> 5];
                mVelX += sAbe_xVel_table_545770[(u8) Input().mPads[sCurrentControllerIndex].mDir >> 5];
                mVelY += sAbe_yVel_table_545790[(u8) Input().mPads[sCurrentControllerIndex].mDir >> 5];
            }

            mXPos += mVelX;
            mYPos += mVelY;

            // Keep within map max min bounds
            if (mXPos < FP_FromInteger(0))
            {
                mXPos = FP_FromInteger(0);
            }

            if (mYPos < FP_FromInteger(0))
            {
                mYPos = FP_FromInteger(0);
            }

            // Keep within map max bounds
            PSX_Point mapSize = {};
            gMap.Get_map_size(&mapSize);

            FP mapWidth = FP_FromInteger(mapSize.x);
            if (mXPos >= mapWidth)
            {
                mXPos = mapWidth - FP_FromDouble(1.0);
            }

            FP mapHeight = FP_FromInteger(mapSize.y);
            if (mYPos >= mapHeight)
            {
                mYPos = mapHeight - FP_FromDouble(1.0);
                SetActiveCameraDelayedFromDir();
                return;
            }
        }
        else
        {
            mVelX = FP_FromInteger(0);
            mVelY = FP_FromInteger(0);
        }

        SetActiveCameraDelayedFromDir();
    }
    else
    {
        // Handle none DDCheat mode

        mAnim.mFlags.Set(AnimFlags::eBit2_Animate);

        s16 motion_idx = mCurrentMotion;

        // Execute the current motion
        const FP oldXPos = mXPos;
        const FP oldYPos = mYPos;
        (this->*(sAbeMotionMachineTable_554910)[motion_idx])();

        if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit9_RestoredFromQuickSave) || field_1AC_flags.Get(Flags_1AC::e1AC_Bit5_shrivel))
        {
            return;
        }

        if (BaseAliveGameObjectCollisionLine)
        {
            // Snap to a whole number so we are "on" the line
            mYPos = FP_NoFractional(mYPos);
        }

        // Did position change?
        if (oldXPos != mXPos || oldYPos != mYPos)
        {
            // Get the TLV we are on
            BaseAliveGameObjectPathTLV = sPathInfo->TlvGetAt(
                nullptr,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
            VOnTlvCollision(BaseAliveGameObjectPathTLV);
        }

        if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit1_bShot))
        {
            motion_idx = mKnockdownMotion;
            ToKnockback_44E700(1, 1);
            if (motion_idx != -1)
            {
                mCurrentMotion = motion_idx;
            }

            mNextMotion = 0;
            field_1AC_flags.Clear(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
            mKnockdownMotion = eAbeMotions::Motion_0_Idle_44EEB0;
            mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
            mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
        }

        if (EventGet(kEventScreenShake) && mHealth > FP_FromInteger(0))
        {
            if (IsStanding_449D30())
            {
                ToKnockback_44E700(1, 0);
            }
        }

        if (field_128.mSay != MudSounds::eNone && static_cast<s32>(sGnFrame) >= mAutoSayTimer)
        {
            if (!gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0)
                || (mCurrentMotion == eAbeMotions::Motion_112_Chant_45B1C0)
                || mCurrentMotion == eAbeMotions::Motion_7_Speak_45B140
                || mCurrentMotion == eAbeMotions::Motion_8_Speak_45B160
                || mCurrentMotion == eAbeMotions::Motion_9_Speak_45B180
                || mCurrentMotion == eAbeMotions::Motion_10_Fart_45B1A0)
            {
                // Prevents f64 laugh when blowing up a slig as we prevent saying anything while chanting or various other states
                // or when abe isn't in the active screen
                field_128.mSay = MudSounds::eNone;
            }
            else
            {
                if (mCurrentMotion == eAbeMotions::Motion_0_Idle_44EEB0 || mCurrentMotion == eAbeMotions::Motion_12_Null_4569C0)
                {
                    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                    switch (field_128.mSay)
                    {
                        case MudSounds::eOops_14:
                            mCurrentMotion = eAbeMotions::Motion_34_DunnoBegin_44ECF0;
                            break;
                        case MudSounds::eAnger_5:
                            mCurrentMotion = eAbeMotions::Motion_10_Fart_45B1A0;
                            break;
                        case MudSounds::eSadUgh_28:
                            mCurrentMotion = eAbeMotions::Motion_10_Fart_45B1A0;
                            break;
                        default:
                            mCurrentMotion = eAbeMotions::Motion_9_Speak_45B180;
                            break;
                    }
                }

                if (field_128.mSay == MudSounds::eAnger_5)
                {
                    // Other evil muds laugh at the abe grr
                    EventBroadcast(kEventMudokonLaugh, sActiveHero);
                }

                if (field_128.mSay == MudSounds::eSadUgh_28)
                {
                    // This one has another volume for whatever reason
                    Mudokon_SFX(field_128.mSay, 80, 0, this);
                }
                else
                {
                    Mudokon_SFX(field_128.mSay, 0, 0, this);
                }

                field_128.mSay = MudSounds::eNone;
            }
        }

        if (motion_idx != mCurrentMotion || mBaseAliveGameObjectFlags.Get(Flags_114::e114_MotionChanged_Bit2))
        {
            mBaseAliveGameObjectFlags.Clear(Flags_114::e114_MotionChanged_Bit2);
            if (mCurrentMotion != eAbeMotions::Motion_12_Null_4569C0 && !(field_1AC_flags.Get(Flags_1AC::e1AC_Bit5_shrivel)))
            {
                mAnim.Set_Animation_Data(GetAnimRes(sAbeAnimIdTable[mCurrentMotion]));

                field_128.mRollingMotionTimer = sGnFrame;

                if (motion_idx == eAbeMotions::Motion_12_Null_4569C0 || motion_idx == eAbeMotions::Motion_60_Unused_4A3200)
                {
                    mAnim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
                }
            }
        }

        if (field_1AC_flags.Get(Flags_1AC::e1AC_Bit2_return_to_previous_motion))
        {
            mCurrentMotion = mPreviousMotion;

            mAnim.Set_Animation_Data(GetAnimRes(sAbeAnimIdTable[mCurrentMotion]));
            field_128.mRollingMotionTimer = sGnFrame;
            mAnim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
            field_1AC_flags.Clear(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
        }

        if (field_128.mRegenHealthTimer <= static_cast<s32>(sGnFrame) && mHealth > FP_FromInteger(0))
        {
            mHealth = FP_FromDouble(1.0);
        }

        // Draw power up ring "pulse"
        if (mRingPulseTimer > 0)
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
            {
                if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
                {
                    if (mRingPulseTimer > static_cast<s32>(sGnFrame))
                    {
                        if (!(sGnFrame % 32))
                        {
                            RingTypes ringType = RingTypes::eExplosive_Pulse_0;
                            if (mHaveShrykull)
                            {
                                ringType = RingTypes::eShrykull_Pulse_Small_4;
                            }
                            else if (mHaveInvisibility)
                            {
                                ringType = RingTypes::eInvisible_Pulse_Small_7;
                            }
                            else if (field_1AC_flags.Get(Flags_1AC::e1AC_eBit15_have_healing))
                            {
                                ringType = RingTypes::eHealing_Pulse_14;
                            }

                            const PSX_RECT rect = VGetBoundingRect();
                            AbilityRing::Factory(
                                FP_FromInteger((rect.x + rect.w) / 2),
                                FP_FromInteger((rect.y + rect.h) / 2),
                                ringType, mSpriteScale);

                            SFX_Play_Pitch(relive::SoundEffects::PossessEffect, 25, 2650);
                        }
                    }
                    else
                    {
                        if (mRingPulseTimer > 0 && mHaveShrykull > 0)
                        {
                            Free_Shrykull_Resources_45AA90();
                        }
                        mRingPulseTimer = 0;
                    }
                }
            }
        }


        InvisibleEffect* pObj_field_178 = static_cast<InvisibleEffect*>(sObjectIds.Find(mInvisibleEffectId, ReliveTypes::eInvisibleEffect));
        if (pObj_field_178 && mInvisibilityTimer > 0)
        {
            if (static_cast<s32>(sGnFrame) > mInvisibilityTimer)
            {
                mInvisibilityTimer = 0;
                pObj_field_178->BecomeVisible();
            }
        }

        // After the trials give Abe the healing power for the Necrum muds.
        if (field_1AC_flags.Get(Flags_1AC::e1AC_eBit16_is_mudanchee_vault_ender))
        {
            if (field_1AE_flags.Get(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender))
            {
                if (gMap.mCurrentLevel == EReliveLevelIds::eNecrum)
                {
                    mRingPulseTimer = sGnFrame + 200000;
                    mHaveShrykull = 0;
                    mHaveInvisibility = 0;
                    field_1AE_flags.Clear(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender);
                    field_1AC_flags.Clear(Flags_1AC::e1AC_eBit16_is_mudanchee_vault_ender);
                    field_1AC_flags.Set(Flags_1AC::e1AC_eBit15_have_healing);
                }
            }
        }

        if (EventGet(kEventMudokonDied))
        {
            field_128.mSay = MudSounds::eOops_14;
            mAutoSayTimer = sGnFrame + Math_RandomRange(22, 30);

            relive_new MusicTrigger(relive::Path_MusicTrigger::MusicTriggerMusicType::eDeathDrumShort, relive::Path_MusicTrigger::TriggeredBy::eTimer, 90, 0);
        }

        if (EventGet(kEventMudokonComfort))
        {
            field_128.mSay = MudSounds::eGiggle_8;
            mAutoSayTimer = sGnFrame + Math_RandomRange(22, 30);
        }

        if (EventGet(kScrabOrParamiteDied))
        {
            field_128.mSay = MudSounds::eOops_14;
            mAutoSayTimer = sGnFrame + Math_RandomRange(22, 30);
        }

        if (field_1AE_flags.Get(Flags_1AE::e1AE_Bit2_do_quicksave))
        {
            field_1AE_flags.Clear(Flags_1AE::e1AE_Bit2_do_quicksave);
            sActiveQuicksaveData.field_204_world_info.mSaveFileId = mSaveFileId;
            Quicksave_SaveWorldInfo(&sActiveQuicksaveData.field_244_restart_path_world_info);
            VGetSaveState(reinterpret_cast<u8*>(&sActiveQuicksaveData.field_284_restart_path_abe_state));
            sActiveQuicksaveData.field_35C_restart_path_switch_states = sSwitchStates_5C1A28;
            DoQuicksave();
        }
    }
}

BirdPortal* Abe::VIntoBirdPortal(s16 gridBlocks)
{
    auto pPortal = BaseAliveGameObject::VIntoBirdPortal(gridBlocks);
    if (pPortal && pPortal->mPortalType == relive::Path_BirdPortal::PortalType::eAbe)
    {
        return pPortal;
    }
    return nullptr;
}

void Abe::VOnTrapDoorOpen()
{
    // Handles falling when previously was on a platform, stop turning a wheel if we where turning one etc.
    PlatformBase* pPlatform = static_cast<PlatformBase*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));
    WorkWheel* pWheel = static_cast<WorkWheel*>(sObjectIds.Find(mWorkWheelId, ReliveTypes::eWheel));
    if (pPlatform)
    {
        if (!(field_1AC_flags.Get(Flags_1AC::e1AC_Bit5_shrivel)))
        {
            VSetMotion(eAbeMotions::Motion_93_WalkOffEdge_455970);
        }

        pPlatform->VRemove(this);

        BaseAliveGameObject_PlatformId = Guid{};
        BaseAliveGameObjectLastLineYPos = mYPos;

        if (pWheel)
        {
            pWheel->VStopTurning(FALSE);
        }
    }
}

void Abe::ToKnockback_44E700(s16 bKnockbackSound, s16 bDelayedAnger)
{
    OrbWhirlWind* pfield_150 = static_cast<OrbWhirlWind*>(sObjectIds.Find_Impl(mOrbWhirlWindId));
    BaseThrowable* pfield_158 = static_cast<BaseThrowable*>(sObjectIds.Find_Impl(mThrowableId));
    WorkWheel* pfield_164 = static_cast<WorkWheel*>(sObjectIds.Find(mWorkWheelId, ReliveTypes::eWheel));
    if (sControlledCharacter == this || mHealth <= FP_FromInteger(0))
    {
        // Chant music/orb kill ?
        SND_SEQ_Stop(SeqId::MudokonChant1_10);
        if (pfield_150)
        {
            pfield_150->ToStop();
            mOrbWhirlWindId = Guid{};
        }

        if (pfield_164)
        {
            pfield_164->VStopTurning(1);
            mWorkWheelId = Guid{};
        }

        if (mVelX != FP_FromInteger(0))
        {
            mXPos -= mVelX;
        }

        MapFollowMe(TRUE);

        mVelX = FP_FromInteger(0);

        if (mVelY < FP_FromInteger(0))
        {
            mVelY = FP_FromInteger(0);
        }

        // NOTE: This always seems to be set to true. This parameter might not be needed.
        if (bKnockbackSound)
        {
            Mudokon_SFX(MudSounds::eHurt2_9, 0, Math_RandomRange(-127, 127), this);
            Environment_SFX_457A40(EnvironmentSfx::eKnockback_13, 0, 32767, this);
        }

        mCurrentMotion = eAbeMotions::Motion_71_Knockback_455090;

        if (bDelayedAnger)
        {
            field_128.mSay = MudSounds::eAnger_5;    // anger in..
            mAutoSayTimer = sGnFrame + 27; // 27 ticks
        }

        if (pfield_158)
        {
            pfield_158->VToDead();
            mThrowableId = Guid{};
            if (!gInfiniteThrowables)
            {
                mThrowableCount++;
            }
        }
    }
}

void Abe::VRender(PrimHeader** ppOt)
{
    // When in death shrivel don't reset scale else can't shrivel into a black blob
    if (!(field_1AC_flags.Get(Flags_1AC::e1AC_Bit5_shrivel)))
    {
        mAnim.field_14_scale = mSpriteScale;
    }

    if (mCurrentMotion != eAbeMotions::Motion_79_InsideWellLocal_45CA60 && mCurrentMotion != eAbeMotions::Motion_82_InsideWellExpress_45CC80 && mCurrentMotion != eAbeMotions::Motion_76_ToInsideOfAWellLocal_45CA40)
    {
        BaseAnimatedWithPhysicsGameObject::VRender(ppOt);
    }
}

void Abe::VScreenChanged()
{
    if (sControlledCharacter == this)
    {
        mCurrentLevel = gMap.mNextLevel;
        mCurrentPath = gMap.mNextPath;
    }

    // Level has changed?
    if (gMap.mCurrentLevel != gMap.mNextLevel)
    {
        // Hack to make Abe mSay hello in the first screen of the mines
        if (gMap.mNextLevel == EReliveLevelIds::eMines && !gAttract_5C1BA0)
        {
            field_128.mSay = MudSounds::eHelloNeutral_3;
            mAutoSayTimer = sGnFrame + 35;
        }

        // Set the correct tint for this map
        SetTint(sAbeTintTable, gMap.mNextLevel);

        if (gMap.mCurrentLevel != EReliveLevelIds::eNone)
        {
            if (mThrowableCount > 0)
            {
                if (gpThrowableArray)
                {
                    gpThrowableArray->Remove(mThrowableCount);
                }
            }

            mThrowableCount = 0;

            if (mRingPulseTimer > 0 && mHaveShrykull)
            {
                Free_Shrykull_Resources_45AA90();
            }

            mRingPulseTimer = 0;
        }

        if (gMap.mNextLevel == EReliveLevelIds::eNecrum)
        {
            if (gMap.mCurrentLevel == EReliveLevelIds::eMudancheeVault_Ender)
            {
                field_1AC_flags.Set(Flags_1AC::e1AC_eBit16_is_mudanchee_vault_ender);
            }

            if (gMap.mCurrentLevel == EReliveLevelIds::eMudomoVault_Ender)
            {
                field_1AE_flags.Set(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender);
            }
        }

        if (gMap.mNextLevel == EReliveLevelIds::eCredits || gMap.mNextLevel == EReliveLevelIds::eMenu)
        {
            // Remove Abe for menu/credits levels?
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
    }

    // If level or path changed then kill rings and farts
    if (gMap.mCurrentLevel != gMap.mNextLevel || gMap.mCurrentPath != gMap.mNextPath)
    {
        mRingPulseTimer = 0;
        if (gMap.mCurrentLevel != EReliveLevelIds::eNone)
        {
            mHasEvilFart = 0;
        }
    }

    if (gMap.mCurrentLevel != gMap.mNextLevel && !(mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit9_RestoredFromQuickSave)))
    {
        for (s8& val : sSavedKilledMudsPerZulag_5C1B50.mData)
        {
            val = 0;
        }
    }
}

s32 Abe::VGetSaveState(u8* pSaveBuffer)
{
    Abe_SaveState* pSaveState = reinterpret_cast<Abe_SaveState*>(pSaveBuffer);

    pSaveState->mAEType = AETypes::eAbe_69;
    pSaveState->mXPos = mXPos;
    pSaveState->mYPos = mYPos;
    pSaveState->mVelX = mVelX;
    pSaveState->mVelY = mVelY;
    pSaveState->field_48_x_vel_slow_by = field_128.field_8_x_vel_slow_by;
    pSaveState->field_4C_unused = field_128.field_C_unused;
    pSaveState->mCurrentPath = mCurrentPath;
    pSaveState->mCurrentLevel = MapWrapper::ToAE(mCurrentLevel);
    pSaveState->mSpriteScale = mSpriteScale;
    pSaveState->mScale = mScale;
    pSaveState->mRed = mRGB.r;
    pSaveState->mGreen = mRGB.g;
    pSaveState->mBlue = mRGB.b;

    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit11_Electrocuting))
    {
        for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
        {
            auto pObj = gBaseGameObjects->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            if (pObj->Type() == ReliveTypes::eElectrocute)
            {
                auto pElectrocute = static_cast<const Electrocute*>(pObj);
                if (pElectrocute->field_20_target_obj_id == mBaseGameObjectId)
                {
                    pSaveState->mRed = pElectrocute->field_24_r;
                    pSaveState->mGreen = pElectrocute->field_26_g;
                    pSaveState->mBlue = pElectrocute->field_28_b;
                    break;
                }
            }
        }
    }

    pSaveState->bAnimFlipX = mAnim.mFlags.Get(AnimFlags::eBit5_FlipX);
    pSaveState->mCurrentMotion = mCurrentMotion;
    pSaveState->mCurrentFrame = static_cast<u16>(mAnim.mCurrentFrame);
    pSaveState->mFrameChangeCounter = static_cast<u16>(mAnim.mFrameChangeCounter);

    if (mAnim.mFrameChangeCounter == 0)
    {
        pSaveState->mFrameChangeCounter = 1;
    }

    pSaveState->mIsDrawable = mBaseGameObjectFlags.Get(BaseGameObject::eDrawable_Bit4);
    pSaveState->mAnimRender = mAnim.mFlags.Get(AnimFlags::eBit3_Render);
    pSaveState->mRenderLayer = static_cast<s8>(mAnim.mRenderLayer);
    pSaveState->mHealth = mHealth;
    pSaveState->mCurrentMotion2 = mCurrentMotion;
    pSaveState->mNextMotion = mNextMotion;
    pSaveState->mLastLineYPos = FP_GetExponent(BaseAliveGameObjectLastLineYPos);

    pSaveState->mIsElectrocuted = mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted);

    pSaveState->mIsInvisible = mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible);

    if (BaseAliveGameObjectCollisionLine)
    {
        pSaveState->mCollisionLineType = BaseAliveGameObjectCollisionLine->mLineType;
    }
    else
    {
        pSaveState->mCollisionLineType = -1;
    }

    pSaveState->mPlatformId = BaseAliveGameObject_PlatformId;

    if (BaseAliveGameObject_PlatformId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
        if (pObj)
        {
            pSaveState->mPlatformId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mIsAbeControlled = (this == sControlledCharacter);
    pSaveState->field_50_state = field_120_state.raw;
    pSaveState->field_54_timer = field_124_timer;
    pSaveState->field_58_abe_timer = field_128.field_0_abe_timer;
    pSaveState->mRegenHealthTimer = field_128.mRegenHealthTimer;
    pSaveState->mMood = field_128.mMood;
    pSaveState->mSay = field_128.mSay;
    pSaveState->mAutoSayTimer = mAutoSayTimer;
    pSaveState->mRingPulseTimer = mRingPulseTimer;
    pSaveState->mThrowableCount = mThrowableCount;
    pSaveState->mHaveShrykull = static_cast<s8>(mHaveShrykull);
    pSaveState->bHaveInvisiblity = static_cast<s8>(mHaveInvisibility);

    pSaveState->mPrevHeld = InputObject::KeyboardInputToPsxButtons_45EF70(mPrevHeld);
    pSaveState->mReleasedButtons = InputObject::KeyboardInputToPsxButtons_45EF70(mReleasedButtons);

    pSaveState->mKnockdownMotion = mKnockdownMotion;
    pSaveState->mRollingMotionTimer = sGnFrame - field_128.mRollingMotionTimer;
    pSaveState->mDeathFadeOutId = mDeathFadeOutId;

    if (mDeathFadeOutId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mDeathFadeOutId);
        if (pObj)
        {
            pSaveState->mDeathFadeOutId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mCircularFadeId = mCircularFadeId;

    if (mCircularFadeId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mCircularFadeId);
        if (pObj)
        {
            pSaveState->mCircularFadeId = pObj->mBaseGameObjectTlvInfo;
        }
    }
    pSaveState->mOrbWhirlWindId = mOrbWhirlWindId;

    if (mOrbWhirlWindId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mOrbWhirlWindId);
        if (pObj)
        {
            pSaveState->mOrbWhirlWindId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mPossessedObjectId = mPossessedObjectId;

    if (mPossessedObjectId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mPossessedObjectId);
        if (pObj)
        {
            pSaveState->mPossessedObjectId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mThrowableId = mThrowableId;

    if (mThrowableId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mThrowableId);
        if (pObj)
        {
            pSaveState->mThrowableId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mPullRingRopeId = mPullRingRopeId;

    if (mPullRingRopeId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mPullRingRopeId);
        if (pObj)
        {
            pSaveState->mPullRingRopeId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mSlappableOrPickupId = mSlappableOrPickupId;

    if (mSlappableOrPickupId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mSlappableOrPickupId);
        if (pObj)
        {
            pSaveState->mSlappableOrPickupId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mWorkWheelId = mWorkWheelId;

    if (mWorkWheelId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mWorkWheelId);
        if (pObj)
        {
            pSaveState->mWorkWheelId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mBirdPortalId = mBirdPortalId;

    if (mBirdPortalId != Guid{})
    {
        auto pObj = sObjectIds.Find_Impl(mBirdPortalId);
        if (pObj)
        {
            pSaveState->mBirdPortalId = pObj->mBaseGameObjectTlvInfo;
        }
    }

    pSaveState->mInvisibilityTimer = mInvisibilityTimer;
    pSaveState->field_A0_unused = field_174_unused;
    pSaveState->mInvisibilityDuration = mInvisibilityDuration;
    pSaveState->mHandStoneCamIdx = mHandStoneCamIdx;
    pSaveState->mHandStoneType = mHandStoneType;
    pSaveState->mFmvId = mFmvId;
    pSaveState->mHandStoneCam1 = mHandStoneCams[0];
    pSaveState->mHandStoneCam2 = mHandStoneCams[1];
    pSaveState->mHandStoneCam3 = mHandStoneCams[2];
    pSaveState->field_B4_unused = field_18C_unused;
    pSaveState->field_B6_unused = field_18E_unused;
    pSaveState->field_B8_unused = field_190_unused;
    pSaveState->field_BA_unused = field_192_unused;
    pSaveState->field_BC_unused = field_194_unused;
    pSaveState->field_BE_unused = field_196_unused;
    pSaveState->mHasEvilFart = mHasEvilFart;
    pSaveState->mDstWellLevel = MapWrapper::ToAE(mDstWellLevel);
    pSaveState->mDstWellPath = mDstWellPath;
    pSaveState->mDstWellCamera = mDstWellCamera;
    pSaveState->door_id = field_1A0_door_id;
    pSaveState->mThrowDirection = mThrowDirection;
    pSaveState->mBirdPortalSubState = static_cast<u16>(mBirdPortalSubState);

    pSaveState->mIsElectrocuted = mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted);
    pSaveState->mIsInvisible = mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible);
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_eBit13_teleporting, sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting));

    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit1_lift_point_dead_while_using_lift, field_1AC_flags.Get(Flags_1AC::e1AC_Bit1_lift_point_dead_while_using_lift));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit2_return_to_previous_motion, field_1AC_flags.Get(Flags_1AC::e1AC_Bit2_return_to_previous_motion));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit3_WalkToRun, field_1AC_flags.Get(Flags_1AC::e1AC_Bit3_WalkToRun));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit4_unused, field_1AC_flags.Get(Flags_1AC::e1AC_Bit4_unused));
    pSaveState->bShrivel = field_1AC_flags.Get(Flags_1AC::e1AC_Bit5_shrivel);
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit5_prevent_chanting, field_1AC_flags.Get(Flags_1AC::e1AC_Bit6_prevent_chanting));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit6_land_softly, field_1AC_flags.Get(Flags_1AC::e1AC_Bit7_land_softly));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit7_unused, field_1AC_flags.Get(Flags_1AC::e1AC_Bit8_unused));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit8_laugh_at_chant_end, field_1AC_flags.Get(Flags_1AC::e1AC_Bit9_laugh_at_chant_end));

    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit9_unused, field_1AC_flags.Get(Flags_1AC::e1AC_Bit12_unused));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit10_play_ledge_grab_sounds, field_1AC_flags.Get(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit11_unused, field_1AC_flags.Get(Flags_1AC::e1AC_eBit14_unused));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_Bit12_have_healing, field_1AC_flags.Get(Flags_1AC::e1AC_eBit15_have_healing));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_eBit13_teleporting, mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_eBit14_is_mudanchee_vault_ender, field_1AC_flags.Get(Flags_1AC::e1AC_eBit16_is_mudanchee_vault_ender));

    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_eBit15_is_mudomo_vault_ender, field_1AE_flags.Get(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender));
    pSaveState->field_D4_flags.Set(Abe_SaveState::eD4_eBit16_shadow_enabled, mShadow->mFlags.Get(Shadow::Flags::eEnabled));

    pSaveState->field_D6_flags.Set(Abe_SaveState::eD6_Bit1_shadow_at_bottom, mShadow->mFlags.Get(Shadow::Flags::eShadowAtBottom));

    return sizeof(Abe_SaveState);
}

s16 Abe::VTakeDamage(BaseGameObject* pFrom)
{
    // Stop chant sound music.
    SND_SEQ_Stop(SeqId::MudokonChant1_10);

    const MudSounds oldSay = field_128.mSay;
    field_128.mSay = MudSounds::eNone;

    OrbWhirlWind* pWhirlWind = static_cast<OrbWhirlWind*>(sObjectIds.Find_Impl(mOrbWhirlWindId));
    if (pWhirlWind)
    {
        pWhirlWind->ToStop();
        mOrbWhirlWindId = Guid{};
    }

    if (CantBeDamaged_44BAB0())
    {
        return 0;
    }

    if (gAbeBulletProof_5C1BDA)
    {
        return 0;
    }

    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
    {
        return 0;
    }

    field_128.mRegenHealthTimer = sGnFrame + 180;
    s16 ret = mHealth > FP_FromInteger(0);

    switch (pFrom->Type())
    {
        case ReliveTypes::eGasCountDown:
            if (mHealth > FP_FromInteger(0))
            {
                if (ForceDownIfHoisting_44BA30())
                {
                    return 1;
                }

                if (IsStanding_449D30())
                {
                    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                    mHealth = FP_FromInteger(0);
                    mCurrentMotion = eAbeMotions::Motion_129_PoisonGasDeath_4565C0;
                    field_124_timer = 1;
                }
                else
                {
                    if (mCurrentMotion != eAbeMotions::Motion_71_Knockback_455090 && mCurrentMotion != eAbeMotions::Motion_72_KnockbackGetUp_455340)
                    {
                        ToKnockback_44E700(1, 1);
                        mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                    }
                }
            }
            break;

        case ReliveTypes::eDrill:
        {
            if (mHealth <= FP_FromInteger(0))
            {
                return 0;
            }

            mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
            mHealth = FP_FromInteger(0);
            ToKnockback_44E700(1, 1);

            mRGB.SetRGB(30, 30, 30);

            relive_new Gibs(GibType::Abe_0,
                mXPos,
                mYPos,
                FP_FromInteger(0),
                FP_FromInteger(0),
                mSpriteScale,
                false);

            // Note Check on word_5CC88C <= 3846 appeared always true, removed.
            relive_new Gibs(GibType::Abe_0,
                mXPos,
                mYPos,
                FP_FromInteger(0),
                FP_FromInteger(0),
                mSpriteScale,
                false);

            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
        }
        break;

        case ReliveTypes::eElectricWall:
            Mudokon_SFX(MudSounds::eOops_14, 0, 0, this);
            break;

        case ReliveTypes::eBaseBomb:
        case ReliveTypes::eMineCar:
        case ReliveTypes::eExplosion:
            if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
            {
                if (mHealth > FP_FromInteger(0))
                {
                    mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit1_bShot);
                    mKnockdownMotion = eAbeMotions::Motion_71_Knockback_455090;
                    mNextMotion = eAbeMotions::Motion_71_Knockback_455090;
                }

                mHealth = FP_FromInteger(0);

                mRGB.SetRGB(30, 30, 30);

                relive_new Gibs(GibType::Abe_0,
                    mXPos,
                    mYPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    mSpriteScale,
                    0);
                mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                mShadow->mFlags.Clear(Shadow::Flags::eEnabled);
            }
            break;

        case ReliveTypes::eSecurityClaw:
        case ReliveTypes::eSecurityOrb:
            field_128.mSay = MudSounds::eAnger_5;
            mAutoSayTimer = sGnFrame + 27;
            if (mCurrentMotion != eAbeMotions::Motion_123_LiftGrabIdle_45A6A0 && mCurrentMotion != eAbeMotions::Motion_124_LiftUseUp_45A780 && mCurrentMotion != eAbeMotions::Motion_125_LiftUseDown_45A7B0)
            {
                ToKnockback_44E700(1, 1);
                mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
            }

            // The zap makes Abe drop his stuff everywhere
            for (s32 i = 0; i < mThrowableCount; i++)
            {
                BaseThrowable* pThrowable = Make_Throwable_49AF30(
                    mXPos,
                    mYPos - FP_FromInteger(30),
                    0);

                // Random explode time ?
                const FP rand1 = FP_FromRaw((Math_NextRandom() - 127) << 11); // TODO: Wat?
                const FP rand2 = (FP_FromDouble(0.03125) * FP_FromRaw(Math_NextRandom())) - FP_FromInteger(2);
                pThrowable->VThrow(rand1, rand2);

                pThrowable->mSpriteScale = mSpriteScale;
                pThrowable->mScale = mScale;
                pThrowable->VTimeToExplodeRandom(); // Start count down ?
            }
            mThrowableCount = 0;
            break;

        case ReliveTypes::eRockSpawner:
            if (mHealth > FP_FromInteger(0))
            {
                mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                mHealth = FP_FromInteger(0);

                if (ForceDownIfHoisting_44BA30())
                {
                    return 1;
                }
                ToKnockback_44E700(1, 1);
                SfxPlayMono(relive::SoundEffects::KillEffect, 127);
            }
            break;

        case ReliveTypes::eFleech:
            if (mHealth > FP_FromInteger(0))
            {
                auto pAliveObj = static_cast<BaseAliveGameObject*>(pFrom);

                mHealth -= FP_FromDouble(0.15075); // Yes it has to be this accurate to match

                if (mHealth < FP_FromInteger(0))
                {
                    mHealth = FP_FromInteger(0);
                    Mudokon_SFX(MudSounds::eLaugh_10, 0, 1000, this);
                }

                if (mHealth > FP_FromInteger(0))
                {
                    // The damage sound from a Fleech keeps getting high and higher pitch till death
                    const FP hpRandSoundRange = (FP_FromInteger(1) - sActiveHero->mHealth) / FP_FromDouble(0.15);
                    const s16 pitchRand = Math_RandomRange(
                        200 * (FP_GetExponent(hpRandSoundRange)),
                        40 * (5 * (FP_GetExponent(hpRandSoundRange)) + 5));

                    Mudokon_SFX(MudSounds::eHurt2_9, 0, pitchRand, this);
                    return 1;
                }

                const PSX_RECT bRect = VGetBoundingRect();

                relive_new Blood(mXPos,
                    // Put YPos in the middle of who is getting damaged
                    FP_FromInteger(bRect.y + bRect.h) / FP_FromInteger(2),
                    // Put the blood on the left or the right depending on where the damage is coming from
                    FP_FromInteger((mXPos - pAliveObj->mXPos < FP_FromInteger(0)) ? -24 : 24),
                    FP_FromInteger(0),
                    mSpriteScale,
                    50);

                if (ForceDownIfHoisting_44BA30())
                {
                    return 1;
                }

                ToKnockback_44E700(1, 1);
                mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);

                if (pAliveObj->mXPos < mXPos && mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mCurrentMotion = eAbeMotions::Motion_101_KnockForward_455420;
                }

                if (pAliveObj->mXPos > mXPos && !(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)))
                {
                    mCurrentMotion = eAbeMotions::Motion_101_KnockForward_455420;
                }

                if (pAliveObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mVelX = mSpriteScale * FP_FromDouble(-7.8);
                }
                else
                {
                    mVelX = mSpriteScale * FP_FromDouble(7.8);
                }

                SfxPlayMono(relive::SoundEffects::KillEffect, 127);
                SfxPlayMono(relive::SoundEffects::FallingItemHit, 90);
            }
            break;

        case ReliveTypes::eGreeter:
            if (mHealth <= FP_FromInteger(0))
            {
                break;
            }

            Mudokon_SFX(MudSounds::eHurt2_9, 0, 0, this);
            Environment_SFX_457A40(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
            mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit1_bShot);
            mKnockdownMotion = eAbeMotions::Motion_101_KnockForward_455420;
            mNextMotion = eAbeMotions::Motion_101_KnockForward_455420;
            mHealth = FP_FromInteger(0);

            if (!ForceDownIfHoisting_44BA30())
            {
                break;
            }
            return 1;

        case ReliveTypes::eParamite:
        case ReliveTypes::eScrab:
        case ReliveTypes::eSlog:
            if (mHealth > FP_FromInteger(0))
            {
                auto pAliveObj = static_cast<BaseAliveGameObject*>(pFrom);

                mHealth = FP_FromInteger(0);

                const PSX_RECT bRect = VGetBoundingRect();

                relive_new Blood(
                    mXPos,
                    FP_FromInteger(bRect.y + bRect.h) / FP_FromInteger(2),
                    // Put the blood on the left or the right depending on where the damage is coming from
                    (pAliveObj->mVelX <= FP_FromInteger(0)) ? FP_FromInteger(-24) : FP_FromInteger(24),
                    FP_FromInteger(0),
                    mSpriteScale,
                    50);

                if (ForceDownIfHoisting_44BA30())
                {
                    return 1;
                }

                ToKnockback_44E700(1, 1);
                mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);

                if (pAliveObj->mXPos < mXPos)
                {
                    if (!(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_101_KnockForward_455420;
                    }
                }

                if (pAliveObj->mXPos > mXPos)
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_101_KnockForward_455420;
                    }
                }

                if (pAliveObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mVelX = mSpriteScale * FP_FromDouble(-7.8);
                }
                else
                {
                    mVelX = mSpriteScale * FP_FromDouble(7.8);
                }

                SfxPlayMono(relive::SoundEffects::KillEffect, 127);

                if (pFrom->Type() != ReliveTypes::eParamite)
                {
                    SfxPlayMono(relive::SoundEffects::FallingItemHit, 90);
                }
            }
            break;

        case ReliveTypes::eAbilityRing:
            return 0;

        case ReliveTypes::eMudokon:
            if (mHealth > FP_FromInteger(0) && mCurrentMotion != eAbeMotions::Motion_71_Knockback_455090)
            {
                mHealth -= FP_FromDouble(0.07);
                if (mHealth <= FP_FromInteger(0) || (mCurrentMotion != eAbeMotions::Motion_123_LiftGrabIdle_45A6A0 && mCurrentMotion != eAbeMotions::Motion_124_LiftUseUp_45A780 && mCurrentMotion != eAbeMotions::Motion_125_LiftUseDown_45A7B0))
                {
                    ToKnockback_44E700(1, 1);
                    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                    if (mHealth <= FP_FromInteger(0))
                    {
                        Mudokon_SFX(MudSounds::eHurt2_9, 0, 1000, this);
                        Environment_SFX_457A40(EnvironmentSfx::eDeathNoise_7, 0, 32767, this);
                        mHealth = FP_FromInteger(0);
                    }
                }
            }
            break;

        case ReliveTypes::eSlamDoor:
            if (mHealth > FP_FromInteger(0))
            {
                ToKnockback_44E700(1, 1);
                VCheckCollisionLineStillValid(5);
                mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
            }
            break;

        case ReliveTypes::eElectrocute:
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            ToDieFinal_458910();
            break;

        default:
            if (pFrom->Type() != ReliveTypes::eBullet)
            {
                LOG_ERROR("Expected default case to be bullets only but got: " << static_cast<s32>(pFrom->Type()));
            }
            BulletDamage_44C980(static_cast<Bullet*>(pFrom));
            if (!mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit1_bShot))
            {
                ret = 0;
                field_128.mSay = oldSay;
            }
            break;
    }

    if (sControlledCharacter->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit4_bPossesed))
    {
        if (mHealth == FP_FromInteger(0))
        {
            sControlledCharacter->VUnPosses();
            // We are the "active" player again
            GiveControlBackToMe_44BA10();
        }
    }

    return ret;
}

void Abe::VOnTlvCollision(relive::Path_TLV* pTlv)
{
    for (; pTlv; pTlv = sPathInfo->TlvGetAt(
                     pTlv,
                     mXPos,
                     mYPos,
                     mXPos,
                     mYPos))
    {
        if (pTlv->mTlvType == ReliveTypes::eContinuePoint)
        {
            auto pContinuePoint = static_cast<relive::Path_ContinuePoint*>(pTlv);
            if (pContinuePoint->mTlvSpecificMeaning == 0)
            {
                if ((pContinuePoint->mScale != relive::Path_ContinuePoint::Scale::eHalf || mSpriteScale == FP_FromInteger(1)) && (pContinuePoint->mScale != relive::Path_ContinuePoint::Scale::eFull || mSpriteScale == FP_FromDouble(0.5))
                    && mHealth > FP_FromInteger(0) && !(mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted)))
                {
                    pContinuePoint->mTlvSpecificMeaning = 1;
                    field_1AE_flags.Set(Flags_1AE::e1AE_Bit2_do_quicksave);
                    mSaveFileId = pContinuePoint->mSaveFileId;
                }
            }
        }
        else if (pTlv->mTlvType == ReliveTypes::eDeathDrop)
        {
            if (sControlledCharacter->Type() != ReliveTypes::eMineCar || gMap.mCurrentLevel != EReliveLevelIds::eMines)
            {
                Mudokon_SFX(MudSounds::eDeathDropScream_15, 0, 0, this);
                EventBroadcast(kEventNoise, this);
                EventBroadcast(kEventSuspiciousNoise, this);
                EventBroadcast(kEventLoudNoise, this);
                EventBroadcast(kEventSpeaking, this);
                ToDie_4588D0();
            }
        }
        else if (pTlv->mTlvType == ReliveTypes::eResetPath)
        {
            auto pResetSwitchRange = static_cast<relive::Path_ResetPath*>(pTlv);
            if (pResetSwitchRange->mTlvSpecificMeaning == 0 || pResetSwitchRange->mEnabled == relive::reliveChoice::eYes)
            {
                pResetSwitchRange->mTlvSpecificMeaning = 1;
                if (pResetSwitchRange->mClearIds == relive::reliveChoice::eYes)
                {
                    for (s16 i = pResetSwitchRange->mFrom; i <= pResetSwitchRange->mTo; i++)
                    {
                        if (i != pResetSwitchRange->mExclude && i > 1)
                        {
                            SwitchStates_Set(i, 0);
                        }
                    }
                }
                if (pResetSwitchRange->mClearObjects == relive::reliveChoice::eYes)
                {
                    Path::Reset_TLVs(pResetSwitchRange->mPath);
                }
            }
        }
    }
}

BaseAliveGameObject* Abe::FindObjectToPossess_44B7B0()
{
    BaseAliveGameObject* pTargetObj = nullptr;
    BaseAliveGameObject* pInRangeFart = nullptr;
    BaseAliveGameObject* pInRangeGlukkon = nullptr;

    s16 maxDistance = 32767;
    FP lastScale = {};
    for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
    {
        BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit3_Can_Be_Possessed))
        {
            switch (pObj->Type())
            {
                    // Third priority
                case ReliveTypes::eCrawlingSlig:
                case ReliveTypes::eFlyingSlig:
                case ReliveTypes::eParamite:
                case ReliveTypes::eScrab:
                case ReliveTypes::eSlig:
                    if (pObj->Is_In_Current_Camera() == CameraPos::eCamCurrent_0 && pObj->mHealth > FP_FromInteger(0))
                    {
                        const s16 distance = static_cast<s16>(Math_Distance(
                            FP_GetExponent(mXPos),
                            FP_GetExponent(mYPos),
                            FP_GetExponent(pObj->mXPos),
                            FP_GetExponent(pObj->mYPos)));

                        if (lastScale == mSpriteScale)
                        {
                            if (pObj->mSpriteScale == mSpriteScale && distance < maxDistance)
                            {
                                pTargetObj = pObj;
                                maxDistance = distance;
                            }
                        }
                        else if (pObj->mSpriteScale == mSpriteScale)
                        {
                            pTargetObj = pObj;
                            maxDistance = distance;
                            lastScale = pObj->mSpriteScale;
                        }
                        else if (distance < maxDistance)
                        {
                            pTargetObj = pObj;
                            maxDistance = distance;
                            lastScale = pObj->mSpriteScale;
                        }
                    }
                    break;

                    // First priority
                case ReliveTypes::eEvilFart:
                    pInRangeFart = pObj;
                    break;

                    // Second priority
                case ReliveTypes::eGlukkon:
                    if (pObj->Is_In_Current_Camera() == CameraPos::eCamCurrent_0)
                    {
                        pInRangeGlukkon = pObj;
                    }
                    break;

                default:
                    continue;
            }
        }
    }

    if (pInRangeFart)
    {
        return pInRangeFart;
    }

    if (pInRangeGlukkon)
    {
        return pInRangeGlukkon;
    }

    return pTargetObj;
}

void Abe::Load_Basic_Resources_44D460()
{
    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbebasicResID, FALSE, FALSE))
    {
        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbebasicResID, TRUE, FALSE))
        {
            ResourceManager::LoadResourceFile_49C170("ABEBSIC.BAN", nullptr);
            ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbebasicResID, TRUE, FALSE);
        }
        field_10_resources_array.SetAt(0, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbebasicResID, FALSE, FALSE));
    }
}

void Abe::Free_Resources_44D420()
{
    if (field_10_resources_array.field_4_used_size)
    {
        if (field_10_resources_array.ItemAt(0))
        {
            ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(0));
            field_10_resources_array.SetAt(0, nullptr);
        }
    }
}

bool Abe::IsStanding_449D30()
{
    return mCurrentMotion == eAbeMotions::Motion_0_Idle_44EEB0
        || mCurrentMotion == eAbeMotions::Motion_2_StandingTurn_451830
        || mCurrentMotion == eAbeMotions::Motion_34_DunnoBegin_44ECF0
        || mCurrentMotion == eAbeMotions::Motion_35_DunnoEnd_44ED10
        || mCurrentMotion == eAbeMotions::Motion_11_Speak_45B0A0
        || mCurrentMotion == eAbeMotions::Motion_7_Speak_45B140
        || mCurrentMotion == eAbeMotions::Motion_8_Speak_45B160
        || mCurrentMotion == eAbeMotions::Motion_9_Speak_45B180
        || mCurrentMotion == eAbeMotions::Motion_10_Fart_45B1A0
        || mCurrentMotion == eAbeMotions::Motion_99_LeverUse_455AC0
        || mCurrentMotion == eAbeMotions::Motion_105_RockThrowStandingThrow_456460
        || mCurrentMotion == eAbeMotions::Motion_104_RockThrowStandingHold_455DF0
        || mCurrentMotion == eAbeMotions::Motion_106_RockThrowStandingEnd_455F20
        || mCurrentMotion == eAbeMotions::Motion_112_Chant_45B1C0
        || mCurrentMotion == eAbeMotions::Motion_113_ChantEnd_45BBE0;
}

void Abe::Free_Shrykull_Resources_45AA90()
{
    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(25));
    field_10_resources_array.SetAt(25, nullptr);

    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(26));
    field_10_resources_array.SetAt(26, nullptr);

    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(27));
    field_10_resources_array.SetAt(27, nullptr);
}


static bool IsSameScaleAsHoist(relive::Path_Hoist* pHoist, BaseAliveGameObject* pObj)
{
    if (pHoist->mScale == relive::reliveScale::eFull && pObj->mScale == Scale::Bg)
    {
        return false;
    }
    else if (pHoist->mScale == relive::reliveScale::eHalf && pObj->mScale == Scale::Fg)
    {
        return false;
    }
    return true;
}

static bool IsSameScaleAsEdge(relive::Path_Edge* pEdge, BaseAliveGameObject* pObj)
{
    if (pEdge->mScale == relive::reliveScale::eFull && pObj->mScale == Scale::Bg)
    {
        return false;
    }
    else if (pEdge->mScale == relive::reliveScale::eHalf && pObj->mScale == Scale::Fg)
    {
        return false;
    }
    return true;
}

static bool IsFacingSameDirectionAsHoist(relive::Path_Hoist* pHoist, BaseAliveGameObject* pObj)
{
    if (pHoist->mGrabDirection == relive::Path_Hoist::GrabDirection::eFacingLeft && !pObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return false;
    }
    else if (pHoist->mGrabDirection == relive::Path_Hoist::GrabDirection::eFacingRight && pObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return false;
    }

    return true;
}

static bool isEdgeGrabbable(relive::Path_Edge* pEdge, BaseAliveGameObject* pObj)
{
    if (pEdge->mGrabDirection == relive::Path_Edge::GrabDirection::eFacingLeft && pObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return true;
    }
    else if (pEdge->mGrabDirection == relive::Path_Edge::GrabDirection::eFacingRight && !pObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return true;
    }
    else if (pEdge->mGrabDirection == relive::Path_Edge::GrabDirection::eFacingAnyDirection)
    {
        return true;
    }

    return false;
}

void Abe::Motion_0_Idle_44EEB0()
{
    if (Input_IsChanting_45F260() && !(field_1AC_flags.Get(Flags_1AC::e1AC_Bit6_prevent_chanting)))
    {
        if (mRingPulseTimer && mHaveShrykull)
        {
            mCurrentMotion = eAbeMotions::Motion_119_ToShrykull_45A990;
        }
        else
        {
            // Go to chanting.
            field_124_timer = sGnFrame + 90;
            mCurrentMotion = eAbeMotions::Motion_112_Chant_45B1C0;
            SND_SEQ_PlaySeq(SeqId::MudokonChant1_10, 0, 1);
        }
        field_120_state.raw = 0;
        return;
    }

    // Go to game speak motion.
    const u32 held = Input().mPads[sCurrentControllerIndex].mHeld;
    if (held & (InputCommands::Enum::eChant | InputCommands::Enum::eGameSpeak8 | InputCommands::Enum::eGameSpeak7 | InputCommands::Enum::eGameSpeak6 | InputCommands::Enum::eGameSpeak5 | InputCommands::Enum::eGameSpeak4 | InputCommands::Enum::eGameSpeak3 | InputCommands::Enum::eGameSpeak2 | InputCommands::Enum::eGameSpeak1))
    {
        mPrevHeld = held;
        mCurrentMotion = eAbeMotions::Motion_11_Speak_45B0A0;
        return;
    }

    if (Input().isPressed(sInputKey_Hop))
    {
        // Some strange alternative way of hoisting, hangover from PSX AO Demo?
        if (Input().isPressed(sInputKey_Up))
        {
            TryHoist_44ED30();
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_27_HopBegin_4521C0;

            BaseGameObject* pObj = VIntoBirdPortal(2);
            if (pObj)
            {
                mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
                mBirdPortalId = pObj->mBaseGameObjectId;
            }
        }
        return;
    }

    if (ToLeftRightMovement_44E340())
    {
        // To turn/walk/sneak/run
        return;
    }

    if (Input().isPressed(sInputKey_Down))
    {
        // Check for a lift rope (going down)
        BaseGameObject* pLiftPoint = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
        if (pLiftPoint)
        {
            if (pLiftPoint->Type() == ReliveTypes::eLiftPoint)
            {
                const FP halfGrid = ScaleToGridSize(mSpriteScale) / FP_FromInteger(2);
                const FP liftPlatformXMidPoint = FP_FromInteger((BaseAliveGameObjectCollisionLine->mRect.x + BaseAliveGameObjectCollisionLine->mRect.w) / 2);
                const FP xPosToMidLiftPlatformDistance = (mXPos - liftPlatformXMidPoint) >= FP_FromInteger(0) ? mXPos - liftPlatformXMidPoint : liftPlatformXMidPoint - mXPos;
                if (xPosToMidLiftPlatformDistance < halfGrid)
                {
                    mCurrentMotion = eAbeMotions::Motion_121_LiftGrabBegin_45A600;
                    return;
                }
            }
        }

        // Look below for a down hoist
        relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos) + 16,
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos) + 16,
            ReliveTypes::eHoist));

        if (pHoist)
        {
            if (!IsSameScaleAsHoist(pHoist, this))
            {
                return;
            }

            if (IsFacingSameDirectionAsHoist(pHoist, this))
            {
                // Yeah go down
                mCurrentMotion = eAbeMotions::Motion_66_LedgeDescend_454970;
            }
            else
            {
                if (pHoist->mGrabDirection == relive::Path_Hoist::GrabDirection::eFacingAnyDirection)
                {
                    // We can hoist down from any side
                    mCurrentMotion = eAbeMotions::Motion_66_LedgeDescend_454970;
                }
                else
                {
                    // Otherwise gotta turn around
                    mNextMotion = eAbeMotions::Motion_66_LedgeDescend_454970;
                    mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_451830;
                }
            }
        }
        else
        {
            // Isn't a hoist so just crouch
            mCurrentMotion = eAbeMotions::Motion_19_StandToCrouch_453DC0;
        }
        return;
    }

    if (Input().isHeld(sInputKey_FartRoll))
    {
        // Do the fart sound
        Mudokon_SFX(MudSounds::eFart_7, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eFart_3);

        // Let others hear the fart
        EventBroadcast(kEventNoise, this);
        EventBroadcast(kEventSuspiciousNoise, this);

        if (mHasEvilFart)
        {
            // An evil fart
            mHasEvilFart = FALSE;
            Create_Fart_421D20();

            if (field_10_resources_array.ItemAt(22))
            {
                ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(22));
                field_10_resources_array.SetAt(22, nullptr);
                mCurrentMotion = eAbeMotions::Motion_10_Fart_45B1A0;
                return;
            }
        }
        else
        {
            const FP fartScale = FP_FromDouble(0.5) * mSpriteScale;
            const FP fartYPos = mYPos - (FP_FromInteger(24) * mSpriteScale);
            FP fartXPos = {};

            // A normal fart, figure out the direction of Abe's Arse
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                fartXPos = mXPos + (FP_FromInteger(12) * mSpriteScale);
            }
            else
            {
                fartXPos = mXPos - (FP_FromInteger(12) * mSpriteScale);
            }

            New_Smoke_Particles(fartXPos, fartYPos, fartScale, 3, 32u, 128u, 32u);
        }

        mCurrentMotion = eAbeMotions::Motion_10_Fart_45B1A0;
        return;
    }

    bool handleDoActionOrThrow = false;
    if (Input().isPressed(sInputKey_Up))
    {
        // Check for lift rope.. (going up)
        BaseGameObject* pLiftPoint = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
        if (pLiftPoint)
        {
            if (pLiftPoint->Type() == ReliveTypes::eLiftPoint)
            {
                const FP halfGrid = ScaleToGridSize(mSpriteScale) / FP_FromInteger(2);
                const FP liftPlatformXMidPoint = FP_FromInteger((BaseAliveGameObjectCollisionLine->mRect.x + BaseAliveGameObjectCollisionLine->mRect.w) / 2);
                const FP xPosToMidLiftPlatformDistance = FP_Abs(mXPos - liftPlatformXMidPoint);
                if (xPosToMidLiftPlatformDistance < halfGrid)
                {
                    mCurrentMotion = eAbeMotions::Motion_121_LiftGrabBegin_45A600;
                    return;
                }
            }
        }

        // Get the first TLV
        relive::Path_TLV* pTlv = sPathInfo->TlvGetAt(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);

        // Handle objects that accept "up"
        while (pTlv)
        {
            switch (pTlv->mTlvType)
            {
                case ReliveTypes::eDoor:
                    if (NearDoorIsOpen_44EE10() && !mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted))
                    {
                        BaseAliveGameObjectPathTLV = pTlv;
                        field_120_state.door = AbeDoorStates::eAbeComesIn_0;
                        mCurrentMotion = eAbeMotions::Motion_114_DoorEnter_459470;
                    }
                    else
                    {
                        // Check for pressed + held so that Abe does a dunno only once, otherwise he will
                        // loop the dunno while up button is down.
                        if (Input().isHeld(sInputKey_Up))
                        {
                            mCurrentMotion = eAbeMotions::Motion_34_DunnoBegin_44ECF0;
                        }
                    }
                    return;

                case ReliveTypes::eWellLocal:
                {
                    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
                    {
                        break;
                    }

                    // Bail if scale doesn't match
                    relive::Path_WellLocal* pWell = static_cast<relive::Path_WellLocal*>(pTlv);
                    if ((pWell->mScale != relive::reliveScale::eFull || mSpriteScale != FP_FromDouble(1.0)) && (pWell->mScale != relive::reliveScale::eHalf || mSpriteScale != FP_FromDouble(0.5)))
                    {
                        break;
                    }

                    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3_WalkToRun);
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_78_WellBegin_45C810;
                }
                    return;

                case ReliveTypes::eWellExpress:
                {
                    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
                    {
                        break;
                    }

                    // Bail if scale doesn't match
                    relive::Path_WellBase* pWell = static_cast<relive::Path_WellBase*>(pTlv);
                    if ((pWell->mScale != relive::reliveScale::eFull || mSpriteScale != FP_FromDouble(1.0)) && (pWell->mScale != relive::reliveScale::eHalf || mSpriteScale != FP_FromDouble(0.5)))
                    {
                        break;
                    }

                    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3_WalkToRun);
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::jMotion_81_WellBegin_45C7F0;
                }
                    return;

                case ReliveTypes::eMovieHandStone:
                case ReliveTypes::eHandStone:
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_86_HandstoneBegin_45BD00;
                    field_120_state.stone = StoneStates::eHandstoneBegin_0;
                    return;

                case ReliveTypes::eBoomMachine:
                {
                    auto pMachineButton = static_cast<BoomMachine*>(FindObjectOfType(
                        ReliveTypes::eBoomMachine,
                        mXPos,
                        mYPos - mSpriteScale * FP_FromInteger(25)));
                    if (pMachineButton)
                    {
                        pMachineButton->VHandleButton();
                        mCurrentMotion = eAbeMotions::Motion_88_GrenadeMachineUse_45C510;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_34_DunnoBegin_44ECF0;
                    }
                }
                break;

                case ReliveTypes::eWorkWheel:
                {
                    bool bCanUseWheel = true;
                    for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
                    {
                        BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(i);
                        if (!pObj)
                        {
                            break;
                        }

                        if (pObj->Type() == ReliveTypes::eMudokon && pObj->mScale == mScale)
                        {
                            FP xDiff = pObj->mXPos - mXPos;
                            if (xDiff < FP_FromInteger(0))
                            {
                                xDiff = mXPos - pObj->mXPos;
                            }

                            FP gridWidth = ScaleToGridSize(mSpriteScale);
                            if (xDiff < gridWidth)
                            {
                                FP yDiff = pObj->mYPos - mYPos;
                                if (yDiff < FP_FromInteger(0))
                                {
                                    yDiff = mYPos - pObj->mYPos;
                                }

                                if (yDiff < gridWidth)
                                {
                                    bCanUseWheel = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (bCanUseWheel)
                    {
                        mCurrentMotion = eAbeMotions::Motion_126_TurnWheelBegin_456700;
                        BaseGameObject* pObj_148 = FindObjectOfType(ReliveTypes::eWheel, mXPos, mYPos - (mSpriteScale * FP_FromInteger(50)));
                        if (pObj_148)
                        {
                            mWorkWheelId = pObj_148->mBaseGameObjectId;
                        }
                    }
                }
                break;

                case ReliveTypes::eBrewMachine:
                    mCurrentMotion = eAbeMotions::Motion_89_BrewMachineBegin_4584C0;
                    field_120_state.raw = 0;
                    break;

                default:
                    break;
            }

            // To next TLV (if any)
            pTlv = sPathInfo->TlvGetAt(
                pTlv,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
        }

        if (!TryEnterMineCar_4569E0())
        {
            if (mCurrentMotion == eAbeMotions::Motion_0_Idle_44EEB0)
            {
                TryHoist_44ED30();
            }
            handleDoActionOrThrow = true;
        }
    }

    if (!Input().isPressed(sInputKey_Up) || handleDoActionOrThrow)
    {
        if ((sInputKey_ThrowItem & held) && mCurrentMotion == eAbeMotions::Motion_0_Idle_44EEB0)
        {
            if (mThrowableCount > 0 || gInfiniteThrowables)
            {
                mThrowableId = Make_Throwable_49AF30(
                                             mXPos,
                                             mYPos - FP_FromInteger(40),
                                             0)
                                             ->mBaseGameObjectId;

                if (!bThrowableIndicatorExists_5C112C)
                {
                    const FP xOffSet = ((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) ? FP_FromInteger(15) : FP_FromInteger(-15)) * mSpriteScale;
                    relive_new ThrowableTotalIndicator(
                        mXPos + xOffSet,
                        mYPos + (mSpriteScale * FP_FromInteger(-50)),
                        mAnim.mRenderLayer,
                        mAnim.field_14_scale,
                        mThrowableCount,
                        TRUE);
                }

                mCurrentMotion = eAbeMotions::Motion_104_RockThrowStandingHold_455DF0;

                if (!gInfiniteThrowables)
                {
                    mThrowableCount--;
                }
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_34_DunnoBegin_44ECF0;
            }
        }
        else
        {
            if (Input().isHeld(sInputKey_DoAction)) // not throwing, maybe pressing up and pressing action, so do action
            {
                mCurrentMotion = HandleDoAction_455BD0();
            }
        }
    }
}

void Abe::Motion_1_WalkLoop_44FBA0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    MoveForward_44E9A0();

    if (mCurrentMotion != eAbeMotions::Motion_1_WalkLoop_44FBA0)
    {
        return;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(9);
    }

    const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;

    if (mAnim.mCurrentFrame != 2 && mAnim.mCurrentFrame != 11)
    {
        if (mAnim.mCurrentFrame != 5 && mAnim.mCurrentFrame != 14)
        {
            return;
        }

        Environment_SFX_457A40(EnvironmentSfx::eWalkingFootstep_1, 0, 32767, this);

        MapFollowMe(TRUE);

        if (sInputKey_Run & pressed)
        {
            // Walk to run
            if (mAnim.mCurrentFrame == 5)
            {
                mCurrentMotion = eAbeMotions::Motion_49_MidWalkToRun_450200;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_48_WalkToRun_4500A0;
            }
        }
        else if (pressed & sInputKey_Sneak)
        {
            // Walk to sneak
            if (mAnim.mCurrentFrame != 5)
            {
                mCurrentMotion = eAbeMotions::Motion_43_MidWalkToSneak_450380;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_41_WalkToSneak_450250;
            }
        }
        return;
    }

    // Direction changed
    bool bEndWalking = false;
    if ((mVelX > FP_FromInteger(0) && (sInputKey_Left & pressed)) || (mVelX < FP_FromInteger(0) && (sInputKey_Right & pressed)))
    {
        bEndWalking = true;
    }

    // Hopping
    if (sInputKey_Hop & mPrevHeld)
    {
        mNextMotion = eAbeMotions::Motion_28_HopMid_451C50;
        bEndWalking = true;
    }

    if (!bEndWalking)
    {
        if ((sInputKey_Left | sInputKey_Right) & pressed)
        {
            // Check if walking into something
            FP gridSize = {};
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                gridSize = -ScaleToGridSize(mSpriteScale);
            }
            else
            {
                gridSize = ScaleToGridSize(mSpriteScale);
            }

            const FP offX = gridSize * FP_FromDouble(1.5);
            if (WallHit(mSpriteScale * FP_FromInteger(50), offX) || WallHit(mSpriteScale * FP_FromInteger(20), offX))
            {
                bEndWalking = true;
            }
        }
        else
        {
            // No longer trying to walk
            bEndWalking = true;
        }
    }

    if (bEndWalking)
    {
        if (mAnim.mCurrentFrame == 2)
        {
            mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_450080;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_4_WalkToIdle_44FFC0;
        }
        mPrevHeld = 0;
    }
}

void Abe::Motion_2_StandingTurn_451830()
{
    const auto currentFrame = mAnim.mCurrentFrame;
    const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;

    if (currentFrame == 4 && (sInputKey_Run & pressed) && (sInputKey_Right | sInputKey_Left) & pressed)
    {
#if ORIGINAL_GAME_FIXES || ORIGINAL_GAME_FIX_AUTO_TURN
        mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0; // OG Change - Fixes "Auto-Turn" bug
#endif

        mCurrentMotion = eAbeMotions::Motion_61_TurnToRun_456530;
        mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);

        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
        }
        else
        {
            mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
        }
    }
    else
    {
        // Play "turning" sound effect
        if (currentFrame == 0)
        {
            Environment_SFX_457A40(EnvironmentSfx::eGenericMovement_9, 0, 32767, this);
        }

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);
            if (mNextMotion)
            {
                mCurrentMotion = mNextMotion;
                mNextMotion = 0;
            }
            else
            {
                ToIdle_44E6B0();
            }
        }
    }
}

void Abe::Motion_3_Fall_459B60()
{
    if (mVelX > FP_FromInteger(0))
    {
        mVelX -= (mSpriteScale * field_128.field_8_x_vel_slow_by);
        if (mVelX < FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }
    else if (mVelX < FP_FromInteger(0))
    {
        mVelX += (mSpriteScale * field_128.field_8_x_vel_slow_by);
        if (mVelX > FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pPathLine = nullptr;
    const s32 bCollision = InAirCollision(&pPathLine, &hitX, &hitY, FP_FromDouble(1.80));
    SetActiveCameraDelayedFromDir();

    // Are we falling into a local well?
    BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellLocal);

    if (!BaseAliveGameObjectPathTLV)
    {
        // No, are we falling into an express well?
        BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellExpress);
    }

    // Handle falling into a well
    if (BaseAliveGameObjectPathTLV)
    {
        if (mHealth > FP_FromInteger(0))
        {
            if (BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eWellLocal || BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eWellExpress)
            {
                // The well must be on the same scale/layer
                relive::Path_WellBase* pWellBase = static_cast<relive::Path_WellBase*>(BaseAliveGameObjectPathTLV);
                if ((pWellBase->mScale == relive::reliveScale::eFull && mSpriteScale == FP_FromInteger(1))
                    || (pWellBase->mScale == relive::reliveScale::eHalf && mSpriteScale == FP_FromDouble(0.5)))
                {
                    field_1AC_flags.Set(Flags_1AC::e1AC_Bit3_WalkToRun);
                    mCurrentMotion = eAbeMotions::Motion_75_JumpIntoWell_45C7B0;
                    return;
                }
            }
        }
    }

    if (bCollision)
    {
        switch (pPathLine->mLineType)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eDynamicCollision_32:
            case eLineTypes::eBackgroundDynamicCollision_36:
            {
                mXPos = hitX;
                mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));
                BaseAliveGameObjectCollisionLine = pPathLine;
                MapFollowMe(TRUE);
                field_124_timer = sGnFrame + 30;

                // See if there is a soft landing at our feet (given we known we just hit the floor)
                relive::Path_SoftLanding* pSoftLanding = static_cast<relive::Path_SoftLanding*>(sPathInfo->TLV_Get_At_4DB4B0(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    ReliveTypes::eSoftLanding));

                if (pSoftLanding)
                {
                    if (!SwitchStates_Get(static_cast<s16>(pSoftLanding->mSwitchId)))
                    {
                        pSoftLanding = nullptr;
                    }
                }

                if (field_1AC_flags.Get(Flags_1AC::e1AC_Bit7_land_softly)
                    || (pSoftLanding && mHealth > FP_FromInteger(0))                                   // If we are dead soft landing won't save us
                    || ((mYPos - BaseAliveGameObjectLastLineYPos) < (mSpriteScale * FP_FromInteger(180)) // Check we didn't fall far enough to be killed
                        && (mHealth > FP_FromInteger(0) || gAbeBulletProof_5C1BDA)))                   //TODO possibly OG bug: those conditions should probably be grouped the following way: ((A || B || C ) && D)
                {
                    mCurrentMotion = eAbeMotions::Motion_16_LandSoft_45A360;
                }
                else
                {
                    // Slam into the floor and break all your bones
                    mHealth = FP_FromInteger(0);
                    mCurrentMotion = eAbeMotions::Motion_84_FallLandDie_45A420;
                    field_128.mRegenHealthTimer = sGnFrame + 900;
                }

                mPreviousMotion = eAbeMotions::Motion_3_Fall_459B60;

                PSX_Point xy{FP_GetExponent(mXPos - FP_FromInteger(10)), FP_GetExponent(mYPos - FP_FromInteger(10))};
                PSX_Point wh{FP_GetExponent(mXPos + FP_FromInteger(10)), FP_GetExponent(mYPos + FP_FromInteger(10))};
                VOnCollisionWith(
                    xy,
                    wh,
                    ObjList_5C1B78,
                    reinterpret_cast<TCollisionCallBack>(&BaseAliveGameObject::OnTrapDoorIntersection)); // Danger danger.. but will probably work.. can't see how else they would have got this to work
            }
            break;

            case eLineTypes::eWallLeft_1:
            case eLineTypes::eWallRight_2:
            case eLineTypes::eBackgroundWallLeft_5:
            case eLineTypes::eBackgroundWallRight_6:
                mXPos = hitX;
                mYPos = hitY;
                ToKnockback_44E700(1, 1);
                break;
        }
        return;
    }

    if (mHealth <= FP_FromInteger(0))
    {
        return;
    }

    // Look down 75 for an edge
    relive::Path_Edge* pEdge = static_cast<relive::Path_Edge*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos - (mSpriteScale * FP_FromInteger(75))),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eEdge));

    bool tryToHang = false;
    if (pEdge)
    {
        if (pEdge->mCanGrab == relive::reliveChoice::eYes && IsSameScaleAsEdge(pEdge, this) && (isEdgeGrabbable(pEdge, this)))
        {
            tryToHang = true;
        }
        BaseAliveGameObjectPathTLV = pEdge;
    }
    else // Didn't find and edge to grab so check if falling onto a hoist
    {
        // Look down 20 for a hoist
        relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(20)),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(20)),
            ReliveTypes::eHoist));

        if (pHoist)
        {
            if (IsFacingSameDirectionAsHoist(pHoist, this) && IsSameScaleAsHoist(pHoist, this))
            {
                tryToHang = true;
            }
        }

        BaseAliveGameObjectPathTLV = pHoist;
    }

    if (tryToHang)
    {
        if (mVelX == FP_FromInteger(0))
        {
            return;
        }

        mXPos = FP_FromInteger((BaseAliveGameObjectPathTLV->mTopLeftX + BaseAliveGameObjectPathTLV->mBottomRightX) / 2);

        MapFollowMe(TRUE);

        if (!sCollisions->Raycast(
                mXPos,
                FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY - 10), // TODO: Negative ??
                mXPos,
                FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY + 10),
                &pPathLine,
                &hitX,
                &hitY,
                mScale == Scale::Fg ? kFgFloor : kBgFloor))
        {
            return;
        }

        mYPos = hitY;
        BaseAliveGameObjectCollisionLine = pPathLine;
        mVelY = FP_FromInteger(0);
        mVelX = FP_FromInteger(0);
        if (BaseAliveGameObjectPathTLV->mTlvType != ReliveTypes::eHoist || (FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY - 1 * BaseAliveGameObjectPathTLV->mTopLeftY)) >= (mSpriteScale * FP_FromInteger(70)))
        {
            mCurrentMotion = eAbeMotions::Motion_69_LedgeHangWobble_454EF0;
            mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
        }
        else
        {
            field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
            mPreviousMotion = eAbeMotions::Motion_65_LedgeAscend_4548E0;
            mBaseAliveGameObjectLastAnimFrame = 12;
            mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
        }
    }
}

void Abe::Motion_4_WalkToIdle_44FFC0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    MoveForward_44E9A0();

    if (mAnim.mCurrentFrame)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe(TRUE);

            if (mNextMotion == eAbeMotions::Motion_28_HopMid_451C50)
            {
                mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
                mCurrentMotion = eAbeMotions::Motion_27_HopBegin_4521C0;
                BaseGameObject* pObj = VIntoBirdPortal(2);
                if (pObj)
                {
                    mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
                    mBirdPortalId = pObj->mBaseGameObjectId;
                }
            }
            else
            {
                ToIdle_44E6B0();
            }
        }
    }
    else
    {
        Environment_SFX_457A40(EnvironmentSfx::eWalkingFootstep_1, 0, 32767, this);
    }
}

void Abe::Motion_5_MidWalkToIdle_450080()
{
    // TODO Jump func omitted jState_WalkEndLeftFoot_40459
    Motion_4_WalkToIdle_44FFC0();
}

void Abe::Motion_6_WalkBegin_44FEE0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    // They hear me walking, they hating
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_7_Speak_45B140()
{
    // TODO: Note jMotion_11_Speak_40388C omitted
    Motion_11_ToSpeak_45B0A0();
}

void Abe::Motion_8_Speak_45B160()
{
    // TODO: Note jMotion_11_Speak_40388C omitted
    Motion_11_ToSpeak_45B0A0();
}

void Abe::Motion_9_Speak_45B180()
{
    // TODO: Note jMotion_11_Speak_40388C omitted
    Motion_11_ToSpeak_45B0A0();
}

void Abe::Motion_10_Fart_45B1A0()
{
    // TODO: Note jMotion_11_Speak_40388C omitted
    Motion_11_ToSpeak_45B0A0();
}

void Abe::Motion_11_ToSpeak_45B0A0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mHeld;
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = DoGameSpeak_45AB70(mPrevHeld);
        if (mCurrentMotion == -1)
        {
            ToIdle_44E6B0();
        }
        else
        {
            if (mCurrentMotion != eAbeMotions::Motion_62_Punch_454750)
            {
                EventBroadcast(kEventSpeaking, this);
            }
            mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
        }
        mPrevHeld = 0;
    }
}

void Abe::Motion_12_Null_4569C0()
{
}

void Abe::Motion_13_HoistBegin_452B20()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mYPos;
        const FP velY = mSpriteScale * FP_FromInteger(-8);
        mVelY = velY;
        mYPos += velY;
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_14_HoistIdle_452440;
        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_14_HoistIdle_452440()
{
    //sObjectIds_5C1B70.Find_449CF0(mPullRingRopeId); // NOTE: Return never used
    BaseGameObject* pfield_110_id = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
    if (Is_Celling_Above_44E8D0())
    {
        ToKnockback_44E700(1, 1);
        return;
    }

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    const auto bCollision = InAirCollision(&pLine, &hitX, &hitY, FP_FromDouble(1.8));
    SetActiveCameraDelayedFromDir();

    if (bCollision)
    {
        switch (pLine->mLineType)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eDynamicCollision_32:
            case eLineTypes::eBackgroundDynamicCollision_36:
            {
                mXPos = hitX;
                mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));

                MapFollowMe(1);

                BaseAliveGameObjectCollisionLine = pLine;

                mCurrentMotion = eAbeMotions::Motion_15_HoistLand_452BA0;
                mPreviousMotion = eAbeMotions::Motion_14_HoistIdle_452440;

                VOnCollisionWith(
                    {FP_GetExponent(mXPos), FP_GetExponent(mYPos)},
                    {FP_GetExponent(mXPos), FP_GetExponent((mYPos + FP_FromInteger(5)))},
                    ObjList_5C1B78,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
                break;
            }
        }
        return;
    }

    PullRingRope* pPullRope = GetPullRope_44D120();
    if (pPullRope)
    {
        if (pPullRope->VPull(this))
        {
            mCurrentMotion = eAbeMotions::Motion_70_RingRopePullHang_455AF0;
            mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
            mPullRingRopeId = pPullRope->mBaseGameObjectId;
            return;
        }
        mPullRingRopeId = Guid{};
    }

    relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eHoist));
    BaseAliveGameObjectPathTLV = pHoist;

    if (mVelY < FP_FromInteger(0))
    {
        // Going down and no hoist, can't do anything
        if (!pHoist)
        {
            return;
        }

        // Hoist is too far away
        if (FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY + -BaseAliveGameObjectPathTLV->mTopLeftY) > (mSpriteScale * FP_FromInteger(90)) || mAnim.mCurrentFrame)
        {
            return;
        }
    }

    if (pHoist)
    {
        if (IsSameScaleAsHoist(pHoist, this) && (IsFacingSameDirectionAsHoist(pHoist, this) || pHoist->mGrabDirection == relive::Path_Hoist::GrabDirection::eFacingAnyDirection))
        {
            if (pHoist->mHoistType == relive::Path_Hoist::Type::eOffScreen)
            {
                if (gMap.SetActiveCameraDelayed(Map::MapDirections::eMapTop_2, this, -1))
                {
                    PSX_Prevent_Rendering_4945B0();
                    mCurrentMotion = eAbeMotions::Motion_68_ToOffScreenHoist_454B80;
                    return;
                }

                Environment_SFX_457A40(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);

                if (FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY - 1 * BaseAliveGameObjectPathTLV->mTopLeftY)
                    >= mSpriteScale * FP_FromInteger(70))
                {
                    mCurrentMotion = eAbeMotions::Motion_67_LedgeHang_454E20;
                }
                else
                {
                    field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
                    mPreviousMotion = eAbeMotions::Motion_65_LedgeAscend_4548E0;
                    mBaseAliveGameObjectLastAnimFrame = 12;
                }
                mYPos -= mSpriteScale * FP_FromInteger(75);
                mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
            }
            else
            {
                Environment_SFX_457A40(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);
                if (FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY - 1 * BaseAliveGameObjectPathTLV->mTopLeftY) >= mSpriteScale * FP_FromInteger(70))
                {
                    mCurrentMotion = eAbeMotions::Motion_67_LedgeHang_454E20;
                }
                else
                {
                    field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
                    mPreviousMotion = eAbeMotions::Motion_65_LedgeAscend_4548E0;
                    mBaseAliveGameObjectLastAnimFrame = 12;
                }
            }

            if (sCollisions->Raycast(
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY - 10),
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY + 10),
                    &pLine,
                    &hitX,
                    &hitY,
                    mScale == Scale::Fg ? kFgFloor : kBgFloor))
            {
                BaseAliveGameObjectCollisionLine = pLine;
                mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));
                mVelY = FP_FromInteger(0);
                if (pfield_110_id)
                {
                    if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 || 
                        BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
                    {
                        VOnCollisionWith(
                            {FP_GetExponent(mXPos), FP_GetExponent(mYPos)},
                            {FP_GetExponent(mXPos), FP_GetExponent(mYPos + FP_FromInteger(5))},
                            ObjList_5C1B78,
                            (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
                    }
                }
                mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_14_HoistIdle_452440;
            }
        }
    }
    else
    {
        BaseAliveGameObjectPathTLV = sPathInfo->TlvGetAt(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);
    }
}

void Abe::Motion_15_HoistLand_452BA0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mCurrentFrame == 2)
    {
        if (mPreviousMotion == eAbeMotions::Motion_3_Fall_459B60)
        {
            Environment_SFX_457A40(EnvironmentSfx::eLandingSoft_5, 0, 32767, this);
        }
        else
        {
            Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 0, 32767, this);
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        // Landing and standing
        ToIdle_44E6B0();
    }
}

void Abe::Motion_16_LandSoft_45A360()
{
    if (mAnim.mCurrentFrame == 2)
    {
        if (!(field_1AC_flags.Get(Flags_1AC::e1AC_Bit7_land_softly)))
        {
            // Hitting the floor events.
            EventBroadcast(kEventNoise, this);
            EventBroadcast(kEventSuspiciousNoise, this);
        }

        field_1AC_flags.Clear(Flags_1AC::e1AC_Bit7_land_softly);

        // Hitting the floor sounds.
        if (mPreviousMotion == eAbeMotions::Motion_3_Fall_459B60)
        {
            Environment_SFX_457A40(EnvironmentSfx::eLandingSoft_5, 0, 0x7FFF, this);
        }
        else
        {
            Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        }

        if (sControlledCharacter != this)
        {
            // If Abe is controlling something else then must be standing and chanting.
            mCurrentMotion = eAbeMotions::Motion_112_Chant_45B1C0;
        }

        if (Input().mPads[sCurrentControllerIndex].mPressed & (InputCommands::Enum::eRight | InputCommands::Enum::eLeft))
        {
            ToLeftRightMovement_44E340();
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_17_CrouchIdle_456BC0()
{
    if (!BaseAliveGameObjectCollisionLine)
    {
        mCurrentMotion = eAbeMotions::Motion_98_RollOffEdge_455AA0;
        return;
    }

    mPrevHeld = 0;
    mReleasedButtons = 0;

    // Crouching game speak
    if (CrouchingGameSpeak_453E10())
    {
        mPrevHeld = 0;
        EventBroadcast(kEventSpeaking, this);
        return;
    }

    // Hit bombs/pick up items ?
    if (sInputKey_DoAction & Input().mPads[sCurrentControllerIndex].mHeld)
    {
        if (!((sInputKey_Left | sInputKey_Right) & Input().mPads[sCurrentControllerIndex].mPressed))
        {
            FP gridSize = {};
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                gridSize = -ScaleToGridSize(mSpriteScale);
            }
            else
            {
                gridSize = ScaleToGridSize(mSpriteScale);
            }
            PickUpThrowabe_Or_PressBomb_454090(gridSize + mXPos, FP_GetExponent(mYPos - FP_FromInteger(5)), 0);
        }
    }

    const u32 held = Input().mPads[sCurrentControllerIndex].mHeld;

    // Crouching throw stuff
    if (sInputKey_ThrowItem & held
        && mCurrentMotion == eAbeMotions::Motion_17_CrouchIdle_456BC0
        && (mThrowableCount > 0 || gInfiniteThrowables))
    {
        mThrowableId = Make_Throwable_49AF30(mXPos, mYPos - FP_FromInteger(40), 0)->mBaseGameObjectId;
        if (!bThrowableIndicatorExists_5C112C)
        {
            const FP yOff = mYPos + (mSpriteScale * FP_FromInteger(-30));
            const FP xOff = mSpriteScale * (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(-10) : FP_FromInteger(10));
            relive_new ThrowableTotalIndicator(
                mXPos + xOff,
                yOff,
                mAnim.mRenderLayer,
                mAnim.field_14_scale,
                mThrowableCount,
                1);
        }

        mCurrentMotion = eAbeMotions::Motion_107_RockThrowCrouchingHold_454410;

        if (!gInfiniteThrowables)
        {
            mThrowableCount--;
        }
    }
    else
    {
        // Try to stand up
        if (held & sInputKey_Up && !Is_Celling_Above_44E8D0())
        {
            mCurrentMotion = eAbeMotions::Motion_18_CrouchToStand_454600;
            return;
        }

        // Crouching farts
        if (sInputKey_FartRoll & Input().mPads[sCurrentControllerIndex].mHeld)
        {
            pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eFart_3);

            Mudokon_SFX(MudSounds::eFart_7, 0, 0, this);

            if (mHasEvilFart)
            {
                mHasEvilFart = 0;
                Create_Fart_421D20();

                if (field_10_resources_array.ItemAt(22))
                {
                    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(22));
                    field_10_resources_array.SetAt(22, nullptr);
                }
            }
            else
            {
                const FP scale = mSpriteScale * FP_FromDouble(0.5);
                const FP ypos = mYPos - (FP_FromInteger(6) * mSpriteScale);
                FP xpos = {};
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    xpos = mXPos + (FP_FromInteger(10) * mSpriteScale);
                }
                else
                {
                    xpos = mXPos - (FP_FromInteger(10) * mSpriteScale);
                }
                New_Smoke_Particles(xpos, ypos, scale, 3, 32u, 128u, 32u);
            }

            mCurrentMotion = eAbeMotions::Motion_20_CrouchSpeak_454550;
        }
        else
        {
            // Crouching turns
            if (Input().mPads[sCurrentControllerIndex].mPressed & sInputKey_Right)
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mCurrentMotion = eAbeMotions::Motion_37_CrouchTurn_454390;
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_22_RollBegin_4539A0;
                    mReleasedButtons = 0;
                }
            }

            if (sInputKey_Left & Input().mPads[sCurrentControllerIndex].mPressed)
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mCurrentMotion = eAbeMotions::Motion_22_RollBegin_4539A0;
                    mReleasedButtons = 0;
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_37_CrouchTurn_454390;
                }
            }
        }
    }
}

void Abe::Motion_18_CrouchToStand_454600()
{
    if (mAnim.mCurrentFrame == 3)
    {
        if (Input().mPads[sCurrentControllerIndex].mPressed & (InputCommands::Enum::eRight | InputCommands::Enum::eLeft))
        {
            ToLeftRightMovement_44E340();
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
        mPrevHeld = 0;
    }
}

void Abe::Motion_19_StandToCrouch_453DC0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        PickUpThrowabe_Or_PressBomb_454090(mXPos, FP_GetExponent(mYPos - FP_FromInteger(5)), 1);
        mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
    }
}

// TODO: End crouching game speak/fart?
void Abe::Motion_20_CrouchSpeak_454550()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mHeld;

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;

        CrouchingGameSpeak_453E10();

        if (mCurrentMotion == eAbeMotions::Motion_20_CrouchSpeak_454550 || mCurrentMotion == eAbeMotions::jMotion_21_ToCrouchSpeak_4545E0)
        {
            EventBroadcast(kEventSpeaking, this);
        }
        mPrevHeld = 0;
    }
}

void Abe::jMotion_21_ToCrouchSpeak_4545E0()
{
    // Note j_401389 omitted
    Motion_20_CrouchSpeak_454550();
}

void Abe::Motion_22_RollBegin_4539A0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
    }

    const FP xpos = mSpriteScale * FP_FromInteger(20);
    if (WallHit(xpos, mVelX))
    {
        ToKnockback_44E700(1, 1);
        mCurrentMotion = eAbeMotions::Motion_74_RollingKnockback_455290;
    }
    else
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_23_RollLoop_453A90;
        }
        MoveForward_44E9A0();
    }
}

void Abe::Motion_23_RollLoop_453A90()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    mReleasedButtons |= Input().mPads[sCurrentControllerIndex].mReleased;

    if (WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_44E700(1, 1);
        mCurrentMotion = eAbeMotions::Motion_74_RollingKnockback_455290;
    }
    else
    {
        MoveForward_44E9A0();

        if (mCurrentMotion == eAbeMotions::Motion_23_RollLoop_453A90)
        {
            if (mAnim.mCurrentFrame == 1 || mAnim.mCurrentFrame == 5 || mAnim.mCurrentFrame == 9)
            {
                if (!Input().isPressed(sInputKey_Run)
                    || Input().isPressed(sInputKey_FartRoll)
                    || Is_Celling_Above_44E8D0()
                    || field_128.mRollingMotionTimer + 9 >= static_cast<s32>(sGnFrame))
                {
                    if (mReleasedButtons)
                    {
                        if (!Is_Celling_Above_44E8D0() && field_128.mRollingMotionTimer + 9 < static_cast<s32>(sGnFrame))
                        {
                            ToLeftRightMovement_44E340();
                            mReleasedButtons = 0;
                        }
                    }
                }
                else
                {
                    ToLeftRightMovement_44E340();
                    mPrevHeld = 0;
                }
            }
            else if (mAnim.mCurrentFrame == 0 || mAnim.mCurrentFrame == 4 || mAnim.mCurrentFrame == 8)
            {
                MapFollowMe(TRUE);

                if ((mVelX > FP_FromInteger(0) && !Input().isPressed(sInputKey_Right)) || (mVelX < FP_FromInteger(0) && !Input().isPressed(sInputKey_Left)))
                {
                    mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
                    mVelX = FP_FromInteger(0);
                }
            }

            if (mAnim.mCurrentFrame == 0 || mAnim.mCurrentFrame == 6)
            {
                Environment_SFX_457A40(EnvironmentSfx::eRollingNoise_8, 0, 32767, this);
            }
        }
    }
}

//TODO: probably unused?
void Abe::Motion_24_453D00()
{
    LOG_WARNING("never expected Motion_24_453D00 (roll loop end) to be called");
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);
    if (WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_44E700(1, 1);
        mCurrentMotion = eAbeMotions::Motion_74_RollingKnockback_455290;
    }
    else
    {
        MoveForward_44E9A0();
        if (mCurrentMotion == eAbeMotions::Motion_24_453D00)
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe(TRUE);
                mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
                mVelX = FP_FromInteger(0);
            }
        }
    }
}

void Abe::Motion_25_RunSlideStop_451330()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_44E700(1, 1);
    }
    else
    {
        MoveWithVelocity_450FA0(FP_FromDouble(0.375));

        if (mCurrentMotion == eAbeMotions::Motion_25_RunSlideStop_451330 && !RunTryEnterWell_451060() && !RunTryEnterDoor_451220())
        {
            if (mAnim.mCurrentFrame != 15)
            {
                MapFollowMe(FALSE);
            }

            const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
            if (mAnim.mCurrentFrame >= 9)
            {
                if (mAnim.mCurrentFrame == 15)
                {
                    Environment_SFX_457A40(EnvironmentSfx::eSlideStop_0, 0, 32767, this);
                    MapFollowMe(TRUE);

                    if (!ToLeftRightMovement_44E340())
                    {
                        ToIdle_44E6B0();
                    }
                }
            }
            else if ((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && (sInputKey_Right & pressed)) || (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && (sInputKey_Left & pressed)))
            {
                field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
                mPreviousMotion = eAbeMotions::Motion_26_RunTurn_451500;
                mBaseAliveGameObjectLastAnimFrame = mAnim.mCurrentFrame;
            }
        }
    }
}

void Abe::Motion_26_RunTurn_451500()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToKnockback_44E700(1, 1);
    }
    else
    {
        MoveWithVelocity_450FA0(FP_FromDouble(0.375));
        if (mCurrentMotion == eAbeMotions::Motion_26_RunTurn_451500
            && !RunTryEnterWell_451060()
            && !RunTryEnterDoor_451220())
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame) || (MapFollowMe(FALSE) && mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame)))
            {
                MapFollowMe(TRUE);

                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    if (sInputKey_Run & Input().mPads[sCurrentControllerIndex].mPressed)
                    {
                        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
                        mCurrentMotion = eAbeMotions::Motion_52_RunTurnToRun_451710;
                    }
                    else
                    {
                        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(9);
                        mCurrentMotion = eAbeMotions::Motion_53_RunTurnToWalk_451800;
                    }
                }
                else
                {
                    if (sInputKey_Run & Input().mPads[sCurrentControllerIndex].mPressed)
                    {
                        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                        mCurrentMotion = eAbeMotions::Motion_52_RunTurnToRun_451710;
                    }
                    else
                    {
                        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
                        mCurrentMotion = eAbeMotions::Motion_53_RunTurnToWalk_451800;
                    }
                }
            }
        }
    }
}

void Abe::Motion_27_HopBegin_4521C0()
{
    if (mAnim.mCurrentFrame == 9)
    {
        // Change velocity at this frame
        const FP velX = mSpriteScale * (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(-17) : FP_FromInteger(17));

        mVelX = velX;

        if (mBirdPortalId == Guid{})
        {
            // Check for hopping into a wall
            if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
            {
                EventBroadcast(kEventNoise, this);
                EventBroadcast(kEventSuspiciousNoise, this);
                mVelX = FP_FromInteger(0);
                ToKnockback_44E700(1, 1);
                return;
            }
        }
        mXPos += mVelX;
        SetActiveCameraDelayedFromDir();
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mYPos;
        const FP velX = mSpriteScale * (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromDouble(-13.57) : FP_FromDouble(13.57));
        mVelX = velX;
        mXPos += velX;

        const FP velY = mSpriteScale * FP_FromDouble(-2.7);
        mVelY = velY;
        mYPos += velY;

        VOnTrapDoorOpen();

        mCurrentMotion = eAbeMotions::Motion_28_HopMid_451C50;
        BaseAliveGameObjectCollisionLine = nullptr;

        if (mBirdPortalId == Guid{})
        {
            BaseGameObject* pObj = VIntoBirdPortal(2);
            if (pObj)
            {
                mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
                mBirdPortalId = pObj->mBaseGameObjectId;
            }
        }
    }
}

void Abe::Motion_28_HopMid_451C50()
{
    if (mBirdPortalId != Guid{})
    {
        IntoPortalStates_451990();
        return;
    }

    // Hopped into a wall?
    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        EventBroadcast(kEventNoise, this);
        EventBroadcast(kEventSuspiciousNoise, this);
        mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
        ToKnockback_44E700(1, 1);
        return;
    }

    // See if we've hit a path line floor type
    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    const auto bCollision = InAirCollision(&pLine, &hitX, &hitY, FP_FromDouble(1.80));
    SetActiveCameraDelayedFromDir();

    if (bCollision)
    {
        EventBroadcast(kEventNoise, this);
        EventBroadcast(kEventSuspiciousNoise, this);

        switch (pLine->mLineType)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eDynamicCollision_32:
            case eLineTypes::eBackgroundDynamicCollision_36:
                Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 0, 32767, this);
                BaseAliveGameObjectCollisionLine = pLine;
                mXPos = hitX;
                mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));
                mVelX = FP_FromInteger(0);
                mVelY = FP_FromInteger(0);

                VOnCollisionWith(
                    {FP_GetExponent(mXPos), FP_GetExponent(mYPos)},
                    {FP_GetExponent(mXPos), FP_GetExponent(mYPos + FP_FromInteger(5))},
                    ObjList_5C1B78,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);

                MapFollowMe(TRUE);
                mCurrentMotion = eAbeMotions::Motion_29_HopLand_4523D0;
                mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
                return;
        }
    }
    else
    {
        // Dead so can't continue
        if (mHealth <= FP_FromInteger(0))
        {
            return;
        }

        // Check for an edge
        relive::Path_Edge* pEdgeTlv = static_cast<relive::Path_Edge*>(sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos - (mSpriteScale * FP_FromInteger(75))),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eEdge));

        BaseAliveGameObjectPathTLV = pEdgeTlv;

        if (pEdgeTlv && pEdgeTlv->mCanGrab == relive::reliveChoice::eYes && IsSameScaleAsEdge(pEdgeTlv, this) && ((isEdgeGrabbable(pEdgeTlv, this) && mVelX != FP_FromInteger(0))))
        {
            mXPos = FP_FromInteger((pEdgeTlv->mTopLeftX + pEdgeTlv->mBottomRightX) / 2);

            MapFollowMe(TRUE);

            if (sCollisions->Raycast(
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY - 10),
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY + 10),
                    &pLine,
                    &hitX,
                    &hitY,
                    mScale == Scale::Fg ? kFgFloor : kBgFloor))
            {
                mYPos = hitY;
                BaseAliveGameObjectCollisionLine = pLine;
                mVelY = FP_FromInteger(0);
                mVelX = FP_FromInteger(0);
                mCurrentMotion = eAbeMotions::Motion_69_LedgeHangWobble_454EF0;
                mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
            }
        }
    }

    if (!(mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame)))
    {
        return;
    }

    if (mCurrentMotion != eAbeMotions::Motion_28_HopMid_451C50)
    {
        return;
    }

    mVelX = FP_FromRaw(mVelX.fpValue / 2);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mXPos = (mSpriteScale * FP_FromInteger(5)) + mXPos;
    }
    else
    {
        mXPos = mXPos - (mSpriteScale * FP_FromInteger(5));
    }

    mYPos += mSpriteScale * FP_FromInteger(2);

    field_128.field_8_x_vel_slow_by = FP_FromDouble(0.55);
    mCurrentMotion = eAbeMotions::Motion_96_HopToFall_4559E0;
    mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
}

void Abe::Motion_29_HopLand_4523D0()
{
    if (mAnim.mCurrentFrame == 2
        && sInputKey_Hop & Input().mPads[sCurrentControllerIndex].mPressed)
    {
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
        mPreviousMotion = eAbeMotions::Motion_27_HopBegin_4521C0;
        mBaseAliveGameObjectLastAnimFrame = 5;
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_30_RunJumpBegin_4532E0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    // Check if about to jump into a wall
    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(FP_FromInteger(10), mVelX)) // TODO: OG bug, why no scaling?
    {
        ToKnockback_44E700(1, 1);
    }
    else
    {
        mXPos += mVelX;

        if (mAnim.mCurrentFrame == 0)
        {
            Environment_SFX_457A40(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 32767, this);
        }

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            BaseAliveGameObjectLastLineYPos = mYPos;

            const FP velX = mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromDouble(-7.6) : FP_FromDouble(7.6);
            mVelX = mSpriteScale * velX;

            const FP velY = mSpriteScale * FP_FromDouble(-9.6);
            mVelY = velY;
            mYPos += velY;

            VOnTrapDoorOpen();

            mCurrentMotion = eAbeMotions::Motion_31_RunJumpMid_452C10;
            BaseAliveGameObjectCollisionLine = nullptr;
        }
    }
}

void Abe::Motion_31_RunJumpMid_452C10()
{
    BaseGameObject* pLiftPoint = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);
    if (mBirdPortalId != Guid{})
    {
        IntoPortalStates_451990();
        return;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(FP_FromInteger(10), mVelX) || Is_Celling_Above_44E8D0())
    {
        mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
        ToKnockback_44E700(1, 1);
        return;
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    const auto bCollision = InAirCollision(&pLine, &hitX, &hitY, FP_FromDouble(1.80));

    SetActiveCameraDelayedFromDir();

    if (bCollision)
    {
        switch (pLine->mLineType)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eDynamicCollision_32:
            case eLineTypes::eBackgroundDynamicCollision_36:
                BaseAliveGameObjectCollisionLine = pLine;
                mCurrentMotion = eAbeMotions::Motion_32_RunJumpLand_453460;
                mXPos = hitX;
                mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));
                if (pLine->mLineType == eLineTypes::eDynamicCollision_32)
                {
                    VOnCollisionWith(
                        {FP_GetExponent(mXPos), FP_GetExponent(mYPos)},
                        {FP_GetExponent(mXPos), FP_GetExponent(mYPos + FP_FromInteger(5))},
                        ObjList_5C1B78,
                        (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
                }
                mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
                return;
        }
    }
    else
    {
        relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos - mVelX),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos - mVelX),
            FP_GetExponent(mYPos),
            ReliveTypes::eHoist));

        BaseAliveGameObjectPathTLV = pHoist;

        bool checkCollision = false;
        if (pHoist)
        {
            BaseAliveGameObjectPathTLV = pHoist;

            if (IsSameScaleAsHoist(pHoist, this) && (IsFacingSameDirectionAsHoist(pHoist, this) || pHoist->mGrabDirection == relive::Path_Hoist::GrabDirection::eFacingAnyDirection) && pHoist->mHoistType != relive::Path_Hoist::Type::eOffScreen)
            {
                checkCollision = true;
            }
        }
        else
        {
            relive::Path_Edge* pEdgeTlv = static_cast<relive::Path_Edge*>(sPathInfo->TLV_Get_At_4DB4B0(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos - (mSpriteScale * FP_FromInteger(60))),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eEdge));

            BaseAliveGameObjectPathTLV = pEdgeTlv;

            if (pEdgeTlv && pEdgeTlv->mCanGrab == relive::reliveChoice::eYes)
            {
                if (IsSameScaleAsEdge(pEdgeTlv, this) && (isEdgeGrabbable(pEdgeTlv, this)))
                {
                    checkCollision = true;
                }
            }
        }

        if (checkCollision)
        {
            if (sCollisions->Raycast(
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY - 10),
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY + 10),
                    &pLine,
                    &hitX,
                    &hitY,
                    mScale == Scale::Fg ? kFgFloor : kBgFloor))
            {
                mXPos = FP_FromInteger((BaseAliveGameObjectPathTLV->mTopLeftX + BaseAliveGameObjectPathTLV->mBottomRightX) / 2);

                MapFollowMe(TRUE);
                mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));
                mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
                BaseAliveGameObjectCollisionLine = pLine;
                mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
                mVelX = FP_FromInteger(0);
                mVelY = FP_FromInteger(0);

                if (BaseAliveGameObjectPathTLV->mTlvType != ReliveTypes::eHoist || FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY - 1 * BaseAliveGameObjectPathTLV->mTopLeftY) >= mSpriteScale * FP_FromInteger(70))
                {
                    mCurrentMotion = eAbeMotions::Motion_69_LedgeHangWobble_454EF0;
                }
                else
                {
                    field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
                    mPreviousMotion = eAbeMotions::Motion_65_LedgeAscend_4548E0;
                    mBaseAliveGameObjectLastAnimFrame = 12;
                }

                if (!pLiftPoint)
                {
                    if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 ||
                        BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
                    {
                        VOnCollisionWith(
                            {FP_GetExponent(mXPos), FP_GetExponent(mYPos)},
                            {FP_GetExponent(mXPos), FP_GetExponent(mYPos + FP_FromInteger(5))},
                            ObjList_5C1B78,
                            (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
                    }
                }
            }
        }
        else
        {
            BaseAliveGameObjectPathTLV = sPathInfo->TlvGetAt(
                nullptr,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
        }
    }

    if (!(mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame)))
    {
        return;
    }

    if (mCurrentMotion != eAbeMotions::Motion_31_RunJumpMid_452C10)
    {
        return;
    }

    field_128.field_8_x_vel_slow_by = FP_FromDouble(0.75);
    mCurrentMotion = eAbeMotions::Motion_97_RunJumpToFall_455A80;
    mNextMotion = eAbeMotions::Motion_0_Idle_44EEB0;
}

void Abe::Motion_32_RunJumpLand_453460()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 0, 32767, this);

        MapFollowMe(TRUE);

        const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
        if (sInputKey_Left & pressed)
        {
            if (sInputKey_Hop & mPrevHeld)
            {
                BaseGameObject* pPortal = VIntoBirdPortal(3);
                if (pPortal)
                {
                    mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
                    mBirdPortalId = pPortal->mBaseGameObjectId;
                    mCurrentMotion = eAbeMotions::Motion_30_RunJumpBegin_4532E0;
                    mPrevHeld = 0;
                    return;
                }
                mCurrentMotion = eAbeMotions::Motion_30_RunJumpBegin_4532E0;
                mPrevHeld = 0;
                return;
            }

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                if (pressed & sInputKey_Run)
                {
                    mCurrentMotion = eAbeMotions::Motion_54_RunJumpLandRun_4538F0;
                    mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                }
                else
                {
                    if (WallHit(mSpriteScale * FP_FromInteger(50), -ScaleToGridSize(mSpriteScale)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_25_RunSlideStop_451330;
                        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_55_RunJumpLandWalk_453970;
                        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
                    }
                }
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_26_RunTurn_451500;
                mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
                Environment_SFX_457A40(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
            }
        }
        else if (pressed & sInputKey_Right)
        {
            if (sInputKey_Hop & mPrevHeld)
            {
                BaseGameObject* pPortal = VIntoBirdPortal(3);
                if (pPortal)
                {
                    mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
                    mBirdPortalId = pPortal->mBaseGameObjectId;
                }
                mCurrentMotion = eAbeMotions::Motion_30_RunJumpBegin_4532E0;
                mPrevHeld = 0;
                return;
            }

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mCurrentMotion = eAbeMotions::Motion_26_RunTurn_451500;
                mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                Environment_SFX_457A40(EnvironmentSfx::eRunSlide_4, 0, 32767, this);
            }
            else if (pressed & sInputKey_Run)
            {
                mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
                mCurrentMotion = eAbeMotions::Motion_54_RunJumpLandRun_4538F0;
            }
            else
            {
                if (WallHit(mSpriteScale * FP_FromInteger(50), ScaleToGridSize(mSpriteScale)))
                {
                    mCurrentMotion = eAbeMotions::Motion_25_RunSlideStop_451330;
                    mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
                }
                else
                {
                    mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(9);
                    mCurrentMotion = eAbeMotions::Motion_55_RunJumpLandWalk_453970;
                }
            }
        }
        else if (sInputKey_Hop & mPrevHeld)
        {
            BaseGameObject* pPortal = VIntoBirdPortal(2);
            if (pPortal)
            {
                mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
                mBirdPortalId = pPortal->mBaseGameObjectId;
            }
            mCurrentMotion = eAbeMotions::Motion_27_HopBegin_4521C0;
            mPrevHeld = 0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_25_RunSlideStop_451330;
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
            }
            else
            {
                mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
            }
            Environment_SFX_457A40(EnvironmentSfx::eRunSlide_4, 0, 32767, this);
        }
    }
}

void Abe::DoRunJump()
{
    BaseGameObject* pObj = VIntoBirdPortal(3);
    if (pObj)
    {
        mBirdPortalSubState = PortalSubStates::eJumpingInsidePortal_0;
        mBirdPortalId = pObj->mBaseGameObjectId;
    }

    field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14_unused);
    mCurrentMotion = eAbeMotions::Motion_30_RunJumpBegin_4532E0;
    mPrevHeld = 0;
}

void Abe::Motion_33_RunLoop_4508E0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
    }

    // Ran into wall?
    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14_unused);
        ToKnockback_44E700(1, 1);
        return;
    }

    MoveForward_44E9A0();

    if (mCurrentMotion != eAbeMotions::Motion_33_RunLoop_4508E0)
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14_unused);
        return;
    }

    if (mAnim.mCurrentFrame == 0 || mAnim.mCurrentFrame == 8)
    {
        MapFollowMe(TRUE);
        if (mPrevHeld & sInputKey_Hop)
        {
            DoRunJump();
        }
    }
    else if (mAnim.mCurrentFrame == 4 || mAnim.mCurrentFrame == 12)
    {
        Environment_SFX_457A40(EnvironmentSfx::eRunningFootstep_2, 0, 32767, this);

        MapFollowMe(TRUE);

        // Turning around?
        if ((mVelX > FP_FromInteger(0) && Input().isPressed(sInputKey_Left)) || (mVelX < FP_FromInteger(0) && Input().isPressed(sInputKey_Right)))
        {
            field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14_unused);
            mCurrentMotion = eAbeMotions::Motion_26_RunTurn_451500;
            Environment_SFX_457A40(EnvironmentSfx::eRunSlide_4, 0, 32767, this);
            mPrevHeld = 0;
            return;
        }

        if (mPrevHeld & sInputKey_Hop)
        {
            DoRunJump();
            return;
        }

        // Run to roll
        if (mPrevHeld & sInputKey_FartRoll)
        {
            field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14_unused);
            mCurrentMotion = eAbeMotions::jMotion_38_RunToRoll_453A70;
            mReleasedButtons = 0;
            mPrevHeld = 0;
            return;
        }

        if (Input().isPressed(sInputKey_Left) || Input().isPressed(sInputKey_Right))
        {
            if (Input().isPressed(sInputKey_Run))
            {
                mPrevHeld = 0;
                return;
            }

            FP gridSize = {};
            if (mVelX >= FP_FromInteger(0))
            {
                gridSize = ScaleToGridSize(mSpriteScale);
            }
            else
            {
                gridSize = -ScaleToGridSize(mSpriteScale);
            }

            // Run to walk and hit wall
            if (WallHit(mSpriteScale * FP_FromInteger(50), gridSize) || WallHit(mSpriteScale * FP_FromInteger(20), gridSize))
            {
                ToKnockback_44E700(1, 1);
            }
            else
            {
                // Run to walk
                if (mAnim.mCurrentFrame == 4)
                {
                    mCurrentMotion = eAbeMotions::Motion_50_RunToWalk_450E20;
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_51_MidRunToWalk_450F50;
                }
            }
        }
        else
        {
            // No longer running or even moving, so slide stop
            mCurrentMotion = eAbeMotions::Motion_25_RunSlideStop_451330;
            Environment_SFX_457A40(EnvironmentSfx::eRunSlide_4, 0, 32767, this);
        }

        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14_unused);
        mPrevHeld = 0;
    }
}

void Abe::Motion_34_DunnoBegin_44ECF0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_35_DunnoEnd_44ED10;
    }
}

void Abe::Motion_35_DunnoEnd_44ED10()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_36_Null_45BC50()
{
}

void Abe::Motion_37_CrouchTurn_454390()
{
    if (mAnim.mCurrentFrame != 0)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);
            if (mNextMotion)
            {
                mCurrentMotion = mNextMotion;
                mNextMotion = 0;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
            }
        }
    }
    else
    {
        Environment_SFX_457A40(EnvironmentSfx::eGenericMovement_9, 0, 32767, this);
    }
}

void Abe::jMotion_38_RunToRoll_453A70()
{
    Motion_22_RollBegin_4539A0();
}

// Almost the same as Motion_6_WalkBegin_44FEE0
void Abe::Motion_39_StandingToRun_450D40()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_33_RunLoop_4508E0;
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_40_SneakLoop_450550()
{
    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_44E6B0();
        MapFollowMe(TRUE);
    }
    else
    {
        MoveForward_44E9A0();

        if (mCurrentMotion == eAbeMotions::Motion_40_SneakLoop_450550)
        {
            const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;

            if (mAnim.mCurrentFrame == 3 || mAnim.mCurrentFrame == 13)
            {
                FP gridSize = {};
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    gridSize = -ScaleToGridSize(mSpriteScale);
                }
                else
                {
                    gridSize = ScaleToGridSize(mSpriteScale);
                }

                // Hit wall, changed direction or no longer trying to sneak
                if (WallHit(mSpriteScale * FP_FromInteger(50), gridSize) || WallHit(mSpriteScale * FP_FromInteger(20), gridSize)
                    || (mVelX > FP_FromInteger(0) && (sInputKey_Left & pressed))
                    || (mVelX < FP_FromInteger(0) && (sInputKey_Right & pressed))
                    || !((sInputKey_Left | sInputKey_Right) & pressed))
                {
                    if (mAnim.mCurrentFrame != 3)
                    {
                        mCurrentMotion = eAbeMotions::Motion_46_SneakToIdle_450870;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::jMotion_47_MidSneakToIdle_4508C0;
                    }
                }
            }
            else if (mAnim.mCurrentFrame == 6 || mAnim.mCurrentFrame == 16)
            {
                Environment_SFX_457A40(EnvironmentSfx::eSneakFootstep_3, 0, 32767, this);
                MapFollowMe(TRUE);
                if ((sInputKey_Left | sInputKey_Right) & pressed)
                {
                    // Sneak to walk
                    if (!(pressed & sInputKey_Sneak))
                    {
                        if (mAnim.mCurrentFrame != 6)
                        {
                            mCurrentMotion = eAbeMotions::Motion_44_MidSneakToWalk_450500;
                        }
                        else
                        {
                            mCurrentMotion = eAbeMotions::Motion_42_SneakToWalk_4503D0;
                        }
                    }
                }
                mPrevHeld = 0;
            }
        }
    }
}

void Abe::Motion_41_WalkToSneak_450250()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(10));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(10);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_40_SneakLoop_450550;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
        MapFollowMe(TRUE);
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_42_SneakToWalk_4503D0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(9);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
        MapFollowMe(TRUE);
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_43_MidWalkToSneak_450380()
{
    Motion_41_WalkToSneak_450250();

    if (mCurrentMotion == eAbeMotions::Motion_40_SneakLoop_450550)
    {
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
        mCurrentMotion = eAbeMotions::Motion_43_MidWalkToSneak_450380;
        mPreviousMotion = eAbeMotions::Motion_40_SneakLoop_450550;
        mBaseAliveGameObjectLastAnimFrame = 10;
    }
}

void Abe::Motion_44_MidSneakToWalk_450500()
{
    Motion_42_SneakToWalk_4503D0();

    if (mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_44FBA0)
    {
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
        mCurrentMotion = eAbeMotions::Motion_44_MidSneakToWalk_450500;
        mPreviousMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
        mBaseAliveGameObjectLastAnimFrame = 9;
    }
}

void Abe::Motion_45_SneakBegin_4507A0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_40_SneakLoop_450550;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
        MapFollowMe(TRUE);
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_46_SneakToIdle_450870()
{
    if (mAnim.mCurrentFrame == 0)
    {
        Environment_SFX_457A40(EnvironmentSfx::eSneakFootstep_3, 0, 32767, this);
    }

    MoveForward_44E9A0();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe(TRUE);
        ToIdle_44E6B0();
    }
}

void Abe::jMotion_47_MidSneakToIdle_4508C0()
{
    // TODO: Skipped jmp func jAbe::State_SneakEnd_40330F
    Motion_46_SneakToIdle_450870();
}

void Abe::Motion_48_WalkToRun_4500A0()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(4);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_33_RunLoop_4508E0;
        mPrevHeld = 0;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
        MapFollowMe(TRUE);
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_49_MidWalkToRun_450200()
{
    Motion_48_WalkToRun_4500A0();

    if (mCurrentMotion == eAbeMotions::Motion_33_RunLoop_4508E0)
    {
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
        mCurrentMotion = eAbeMotions::Motion_49_MidWalkToRun_450200;
        mPreviousMotion = eAbeMotions::Motion_33_RunLoop_4508E0;
        mBaseAliveGameObjectLastAnimFrame = 8;
    }
}

void Abe::Motion_50_RunToWalk_450E20()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = ScaleToGridSize(mSpriteScale) / FP_FromInteger(9);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
    }

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
    }
    else
    {
        MoveForward_44E9A0();
    }
}

void Abe::Motion_51_MidRunToWalk_450F50()
{
    Motion_50_RunToWalk_450E20();

    if (mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_44FBA0)
    {
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit2_return_to_previous_motion);
        mCurrentMotion = eAbeMotions::Motion_51_MidRunToWalk_450F50;
        mPreviousMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
        mBaseAliveGameObjectLastAnimFrame = 9;
    }
}

void Abe::Motion_52_RunTurnToRun_451710()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mPressed;

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX) || WallHit(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToIdle_44E6B0();
    }
    else
    {
        MoveForward_44E9A0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_33_RunLoop_4508E0;
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);
        }
    }
}

void Abe::Motion_53_RunTurnToWalk_451800()
{
    Motion_52_RunTurnToRun_451710();

    if (mCurrentMotion == eAbeMotions::Motion_33_RunLoop_4508E0)
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
    }
}

void Abe::Motion_54_RunJumpLandRun_4538F0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_44E6B0();
    }
    else
    {
        MoveForward_44E9A0();
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_33_RunLoop_4508E0;
        }
    }
}

void Abe::Motion_55_RunJumpLandWalk_453970()
{
    Motion_54_RunJumpLandRun_4538F0();

    if (mCurrentMotion == eAbeMotions::Motion_33_RunLoop_4508E0)
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_44FBA0;
    }
}

void Abe::Motion_56_DeathDropFall_4591F0()
{
    mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);
    if (field_124_timer == 0)
    {
        field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
        field_128.field_C_unused = 0;
        mVelX = FP_FromInteger(0);
        mVelY = FP_FromInteger(0);
        field_128.field_0_abe_timer = sGnFrame + 90;
        field_124_timer++;
    }
    else if (field_124_timer == 1)
    {
        if (static_cast<s32>(sGnFrame) == field_128.field_0_abe_timer - 30)
        {
            SND_SEQ_Play(SeqId::HitBottomOfDeathPit_9, 1, 65, 65);
        }
        else if (static_cast<s32>(sGnFrame) == field_128.field_0_abe_timer - 24)
        {
            SfxPlayMono(relive::SoundEffects::KillEffect, 85);
            relive_new ScreenShake(true, false);
        }
        else if (static_cast<s32>(sGnFrame) >= field_128.field_0_abe_timer)
        {
            ToDieFinal_458910();
        }
    }
}

void Abe::Motion_57_Dead_4589A0()
{
    DeathFadeOut* pDeathFade_1 = static_cast<DeathFadeOut*>(sObjectIds.Find_Impl(mDeathFadeOutId));
    CircularFade* pCircularFade = static_cast<CircularFade*>(sObjectIds.Find_Impl(mCircularFadeId));

    mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);

    if (BaseAliveGameObject_PlatformId != Guid{})
    {
        BaseGameObject* pLiftPoint = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
        if (!pLiftPoint)
        {
            BaseAliveGameObject_PlatformId = Guid{};
        }
        else if (pLiftPoint->Type() == ReliveTypes::eLiftPoint)
        {
            static_cast<LiftPoint*>(pLiftPoint)->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
        }
    }

    switch (field_124_timer)
    {
        case 0:
            EventBroadcast(kEventAbeDead, this);
            EventBroadcast(kEventHeroDying, this);
            field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
            field_128.field_C_unused = 0;
            mVelX = FP_FromInteger(0);
            mVelY = FP_FromInteger(0);
            mPrevHeld = 0;
            field_124_timer++;
            field_128.field_0_abe_timer = sGnFrame + 30;
            if (BaseAliveGameObjectPathTLV && BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eDeathDrop)
            {
                const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mYPos + FP_FromInteger(15);
                const FP xpos = FP_FromInteger((Math_NextRandom() % 64) - 32) + mXPos;
                relive_new DeathBirdParticle(
                    xpos,
                    ypos,
                    (Math_NextRandom() % 8) + field_128.field_0_abe_timer + 60,
                    1,
                    mSpriteScale);
            }
            else
            {
                const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mYPos + FP_FromInteger(15);
                const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mXPos;
                relive_new DeathBirdParticle(
                    xpos,
                    ypos,
                    (Math_NextRandom() % 8) + field_128.field_0_abe_timer + 15,
                    1,
                    mSpriteScale);
            }
            return;

        case 1:
            EventBroadcast(kEventHeroDying, this);
            if (!(sGnFrame % 4))
            {
                if (BaseAliveGameObjectPathTLV && BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eDeathDrop)
                {
                    const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mYPos + FP_FromInteger(15);
                    const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mXPos;
                    relive_new DeathBirdParticle(
                        xpos,
                        ypos,
                        (Math_NextRandom() % 8) + field_128.field_0_abe_timer + 60,
                        0,
                        mSpriteScale);
                }
                else
                {
                    const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mYPos + FP_FromInteger(15);
                    const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mXPos;
                    relive_new DeathBirdParticle(
                        xpos,
                        ypos,
                        (Math_NextRandom() % 8) + field_128.field_0_abe_timer + 15,
                        0,
                        mSpriteScale);
                }
            }

            mSpriteScale -= FP_FromDouble(0.008);

            mRGB.r -= 2;
            mRGB.g -= 2;
            mRGB.b -= 2;

            if (static_cast<s32>(sGnFrame) > field_128.field_0_abe_timer)
            {
                field_128.field_0_abe_timer = sGnFrame + 60;

                if (BaseAliveGameObjectPathTLV)
                {
                    if (BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eDeathDrop)
                    {
                        field_128.field_0_abe_timer = (sGnFrame + 60) + 45;
                    }
                }
                ++field_124_timer;
                MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_11, this, 1, 0);
            }
            return;
        case 2:
            EventBroadcast(kEventHeroDying, this);
            if (static_cast<s32>(sGnFrame) > field_128.field_0_abe_timer)
            {
                ++field_124_timer;
            }
            return;
        case 3:
        {
            EventBroadcast(kEventHeroDying, this);
            if (pDeathFade_1)
            {
                pDeathFade_1->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                mDeathFadeOutId = Guid{};
            }
            auto pDeathFade = relive_new DeathFadeOut(Layer::eLayer_FadeFlash_40, 1, false, 8, TPageAbr::eBlend_2);
            if (pDeathFade)
            {
                mDeathFadeOutId = pDeathFade->mBaseGameObjectId;
            }

            if (pCircularFade)
            {
                pCircularFade->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            }
            ++field_124_timer;
        }
            return;

        case 4:
            EventBroadcast(kEventHeroDying, this);

            if (!pDeathFade_1->field_7E_bDone)
            {
                return;
            }

            if (field_10A_unused)
            {
                return;
            }

            VOnTrapDoorOpen();

            BaseAliveGameObjectCollisionLine = nullptr;
            field_128.field_0_abe_timer = sGnFrame + 8;
            ++field_124_timer;
            //dword_5C2C64 = 0; // TODO: Never read ?
            return;

        case 5:
            EventBroadcast(kEventDeathReset, this);
            if (static_cast<s32>(sGnFrame) <= field_128.field_0_abe_timer)
            {
                return;
            }
            Make_Circular_Fade_4CE8C0(
                FP_FromInteger(sActiveQuicksaveData.field_204_world_info.field_C_controlled_x),
                FP_FromInteger(sActiveQuicksaveData.field_204_world_info.field_E_controlled_y),
                sActiveQuicksaveData.field_204_world_info.field_10_controlled_scale != 0 ? FP_FromDouble(1.0) : FP_FromDouble(0.5),
                0,
                1,
                1);
            Quicksave_LoadActive();
            return;
        default:
            return;
    }
}

void Abe::Motion_58_DeadPre_4593E0()
{
    if (field_120_state.raw == 1)
    {
        mCurrentMotion = eAbeMotions::Motion_57_Dead_4589A0;
        field_124_timer = 2;
        field_128.field_0_abe_timer = sGnFrame + 60;
    }
    else
    {
        EventBroadcast(kEventHeroDying, this);
    }
}

void Abe::Motion_59_Null_459450()
{
}

void Abe::Motion_60_Unused_4A3200()
{
    
}

void Abe::Motion_61_TurnToRun_456530()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        // Was going to run into something
        ToKnockback_44E700(1, 1);
    }
    else
    {
        MoveForward_44E9A0();

        if (mCurrentMotion == eAbeMotions::Motion_61_TurnToRun_456530)
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mCurrentMotion = eAbeMotions::Motion_33_RunLoop_4508E0;
            }
        }
    }
}

void Abe::Motion_62_Punch_454750()
{
    if (mAnim.mCurrentFrame == 5)
    {
        FP gridSize = {};
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            gridSize = mXPos - ScaleToGridSize(mSpriteScale);
        }
        else
        {
            gridSize = ScaleToGridSize(mSpriteScale) + mXPos;
        }

        const FP kFP5 = FP_FromInteger(5);
        BaseGameObject* pSlapTarget = FindObjectOfType(ReliveTypes::eMudokon, gridSize, mYPos - kFP5);
        while (pSlapTarget)
        {
            // Is it in a motion where we can slap it?
            const s16 mud_motion = static_cast<Mudokon*>(pSlapTarget)->mCurrentMotion;
            if (mud_motion != 46 && mud_motion != 47)
            {
                // Can slap, so exit
                break;
            }

            // Try to get the next "stacked" mud - e.g if we have like 20 muds on 1 grid block this will iterate through them
            pSlapTarget = GetStackedSlapTarget(pSlapTarget->mBaseGameObjectId, ReliveTypes::eMudokon, gridSize, mYPos - kFP5);
        }

        if (!pSlapTarget)
        {
            pSlapTarget = FindObjectOfType(ReliveTypes::eLockedSoul, gridSize, mYPos - (FP_FromInteger(30) * mSpriteScale));
        }

        if (!pSlapTarget)
        {
            pSlapTarget = FindObjectOfType(ReliveTypes::eSlig, gridSize, mYPos - kFP5);
        }

        if (!pSlapTarget)
        {
            pSlapTarget = FindObjectOfType(ReliveTypes::eSlig, mXPos, mYPos - kFP5);
        }

        if (!pSlapTarget)
        {
            pSlapTarget = FindObjectOfType(ReliveTypes::eGlukkon, gridSize, mYPos - kFP5);
        }

        if (pSlapTarget)
        {
            static_cast<BaseAliveGameObject*>(pSlapTarget)->VTakeDamage(this);
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_63_Sorry_454670()
{
    if (mAnim.mCurrentFrame == 4)
    {
        FP yOff = {};
        FP xOff = {};
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            yOff = mYPos - FP_FromInteger(5);
            xOff = mXPos - ScaleToGridSize(mSpriteScale);
        }
        else
        {
            yOff = mYPos - FP_FromInteger(5);
            xOff = ScaleToGridSize(mSpriteScale) + mXPos;
        }

        auto pMud = static_cast<BaseAliveGameObject*>(FindObjectOfType(ReliveTypes::eMudokon, xOff, yOff));
        if (pMud)
        {
            pMud->VTakeDamage(this);
        }

        Mudokon_SFX(MudSounds::eSorry_27, 0, 0, this);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_64_AfterSorry_454730;
    }
}

void Abe::Motion_64_AfterSorry_454730()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_65_LedgeAscend_4548E0()
{
    const s32 curFrameNum = mAnim.mCurrentFrame;
    if (curFrameNum == 0)
    {
        Environment_SFX_457A40(EnvironmentSfx::eExhaustingHoistNoise_10, 0, 32767, this);
    }
    else if (curFrameNum == 4)
    {
        Environment_SFX_457A40(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 32767, this);
        mShadow->mFlags.Clear(Shadow::Flags::eShadowAtBottom);
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        // Now the ascend is done go back to stand idle
        mShadow->mFlags.Clear(Shadow::Flags::eShadowAtBottom);
        MapFollowMe(TRUE);
        ToIdle_44E6B0();
    }
}

void Abe::Motion_66_LedgeDescend_454970()
{
    const s32 curFrameNum = mAnim.mCurrentFrame;
    if (curFrameNum == 2)
    {
        Environment_SFX_457A40(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 32767, this);
        mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
    }
    else if (curFrameNum == 21)
    {
        relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos + FP_FromInteger(16)),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos + FP_FromInteger(16)),
            ReliveTypes::eHoist));

        if (pHoist)
        {
            if (FP_FromInteger((pHoist->mBottomRightY - 1 * pHoist->mTopLeftY)) < mSpriteScale * FP_FromInteger(70))
            {
                mYPos = (FP_FromInteger(60) * mSpriteScale) + mYPos;

                PathLine* pLine = nullptr;
                FP hitX = {};
                FP hitY = {};

                if (sCollisions->Raycast(
                        mXPos,
                        mYPos - FP_FromInteger(5),
                        mXPos,
                        mYPos + FP_FromInteger(5),
                        &pLine,
                        &hitX,
                        &hitY,
                        mScale == Scale::Fg ? kFgFloor : kBgFloor))
                {
                    BaseAliveGameObjectCollisionLine = pLine;
                    mYPos = hitY;
                    mCurrentMotion = eAbeMotions::Motion_16_LandSoft_45A360;
                    mShadow->mFlags.Clear(Shadow::Flags::eShadowAtBottom);
                }
                else
                {
                    mYPos -= FP_FromInteger(60) * mSpriteScale;
                }
            }
        }
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_67_LedgeHang_454E20;
    }
}

void Abe::Motion_67_LedgeHang_454E20()
{
    mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
    const s32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
    if (sInputKey_Up & pressed || mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
    {
        mCurrentMotion = eAbeMotions::Motion_65_LedgeAscend_4548E0;
    }
    else if (pressed & sInputKey_Down)
    {
        VOnTrapDoorOpen();
        BaseAliveGameObjectCollisionLine = nullptr;
        mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_4557B0;
        mYPos += mSpriteScale * FP_FromInteger(75);
        mShadow->mFlags.Clear(Shadow::Flags::eShadowAtBottom);
        BaseAliveGameObjectLastLineYPos = mYPos;
    }
}

void Abe::Motion_68_ToOffScreenHoist_454B80()
{
    BaseGameObject* pLiftPoint = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);

    // Get the current hoist - even though there is no need to?
    relive::Path_TLV* pHoist = sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eHoist);

    // Find the hoist we are "connecting" to
    BaseAliveGameObjectPathTLV = pHoist;
    mYPos -= mSpriteScale * FP_FromInteger(75);
    mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);

    const FP ypos = FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY) - (FP_FromInteger(40) * mSpriteScale);
    pHoist = sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(ypos),
        FP_GetExponent(mXPos),
        FP_GetExponent(ypos),
        ReliveTypes::eHoist);

    BaseAliveGameObjectPathTLV = pHoist;

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    if (pHoist && sCollisions->Raycast(mXPos, FP_FromInteger(pHoist->mTopLeftY - 10), mXPos, FP_FromInteger(pHoist->mTopLeftY + 10), &pLine, &hitX, &hitY, mScale == Scale::Fg ? kFgFloor : kBgFloor))
    {
        BaseAliveGameObjectCollisionLine = pLine;
        mYPos = FP_NoFractional(hitY + FP_FromDouble(0.5));
        mVelY = FP_FromInteger(0);
        if (!pLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 ||
                BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
            {
                VOnCollisionWith(
                    {FP_GetExponent(mXPos), FP_GetExponent(mYPos)},
                    {FP_GetExponent(mXPos), FP_GetExponent(mYPos + FP_FromInteger(5))},
                    ObjList_5C1B78,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
            }
        }
        mCurrentMotion = eAbeMotions::Motion_67_LedgeHang_454E20;
    }
    else
    {
        mCurrentMotion = eAbeMotions::Motion_14_HoistIdle_452440;
    }
}

void Abe::Motion_69_LedgeHangWobble_454EF0()
{
    if (mAnim.mCurrentFrame == 0)
    {
        if (!(field_1AC_flags.Get(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds)))
        {
            field_1AC_flags.Set(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds);
            Environment_SFX_457A40(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);
        }
    }
    else
    {
        if (mAnim.mCurrentFrame == 2)
        {
            if (!(field_1AC_flags.Get(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds)))
            {
                field_1AC_flags.Set(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds);
                Mudokon_SFX(MudSounds::eHurt1_16, 45, -200, this);
            }
        }
        else
        {
            field_1AC_flags.Clear(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds);
        }
    }

    // Going up the ledge on wobble?
    const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
    if (sInputKey_Up & pressed || mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds);
        mCurrentMotion = eAbeMotions::Motion_65_LedgeAscend_4548E0;
    }
    // Going down the ledge wobble?
    else if (pressed & sInputKey_Down)
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds);
        VOnTrapDoorOpen();
        BaseAliveGameObjectCollisionLine = nullptr;
        mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_4557B0;
        mYPos += mSpriteScale * FP_FromInteger(75);
        mShadow->mFlags.Clear(Shadow::Flags::eShadowAtBottom);
        BaseAliveGameObjectLastLineYPos = mYPos;
    }
    // Now stabilized when wobble anim is done
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit13_play_ledge_grab_sounds);
        mCurrentMotion = eAbeMotions::Motion_67_LedgeHang_454E20;
    }
}

void Abe::Motion_70_RingRopePullHang_455AF0()
{
    PullRingRope* pPullRing = static_cast<PullRingRope*>(sObjectIds.Find_Impl(mPullRingRopeId));
    if (pPullRing)
    {
        if (!pPullRing->VIsNotBeingPulled())
        {
            return;
        }
        pPullRing->VMarkAsPulled();
    }

    mPullRingRopeId = Guid{};
    mVelY = FP_FromInteger(0);
    mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_4557B0;
}

void Abe::Motion_71_Knockback_455090()
{
    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_44EC10();
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX))
            {
                mVelX = FP_FromInteger(0);
            }

            MoveWithVelocity_450FA0(FP_FromDouble(0.67));

            if ((gMap.mCurrentLevel == EReliveLevelIds::eMines
                 || gMap.mCurrentLevel == EReliveLevelIds::eBonewerkz
                 || gMap.mCurrentLevel == EReliveLevelIds::eFeeCoDepot
                 || gMap.mCurrentLevel == EReliveLevelIds::eBarracks
                 || gMap.mCurrentLevel == EReliveLevelIds::eBrewery)
                && mAnim.mCurrentFrame == 7)
            {
                Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
                EventBroadcast(kEventNoise, this);
                EventBroadcast(kEventSuspiciousNoise, this);
            }
        }
        else
        {
            if (mAnim.mCurrentFrame >= 6)
            {
                mAnim.SetFrame(5);
            }

            Motion_3_Fall_459B60();

            if (mCurrentMotion == eAbeMotions::Motion_84_FallLandDie_45A420)
            {
                mCurrentMotion = eAbeMotions::Motion_71_Knockback_455090;
                SfxPlayMono(relive::SoundEffects::KillEffect, 85);
                SND_SEQ_Play(SeqId::HitBottomOfDeathPit_9, 1, 95, 95);
            }
            else if (mCurrentMotion == eAbeMotions::Motion_16_LandSoft_45A360)
            {
                mCurrentMotion = eAbeMotions::Motion_71_Knockback_455090;
                Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
            }
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (!(mBaseAliveGameObjectFlags.Get(Flags_114::e114_MotionChanged_Bit2)) && (BaseAliveGameObjectCollisionLine || !(mAnim.mFlags.Get(AnimFlags::eBit3_Render))))
        {
            if (mHealth > FP_FromInteger(0) || gAbeBulletProof_5C1BDA || mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted))
            {
                mCurrentMotion = eAbeMotions::Motion_72_KnockbackGetUp_455340;
            }
            else
            {
                ToDieFinal_458910();
            }
        }
    }
}

void Abe::Motion_72_KnockbackGetUp_455340()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_73_PushWall_4553A0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);
    if (mAnim.mCurrentFrame == 10)
    {
        if (Math_NextRandom() <= 127)
        {
            Environment_SFX_457A40(EnvironmentSfx::eExhaustingHoistNoise_10, 0, 32767, this);
        }
    }
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_74_RollingKnockback_455290()
{
    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_44EC10();
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (!(mBaseAliveGameObjectFlags.Get(Flags_114::e114_MotionChanged_Bit2)))
        {
            if (mHealth > FP_FromInteger(0) || gAbeBulletProof_5C1BDA)
            {
                mCurrentMotion = eAbeMotions::Motion_72_KnockbackGetUp_455340;
            }
            else
            {
                ToDieFinal_458910();
            }
        }
    }
}

void Abe::Motion_75_JumpIntoWell_45C7B0()
{
    mShadow->mFlags.Clear(Shadow::eEnabled);

    if (mSpriteScale == FP_FromDouble(0.5))
    {
        mAnim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
    }
    else
    {
        mAnim.mRenderLayer = Layer::eLayer_BeforeWell_22;
    }
    jMotion_81_WellBegin_4017F8();
}

void Abe::Motion_76_ToInsideOfAWellLocal_45CA40()
{
    Motion_79_InsideWellLocal_45CA60();
}

void Abe::Motion_77_ToWellShotOut_45D130()
{
    Motion_80_WellShotOut_45D150();
}

void Abe::Motion_78_WellBegin_45C810()
{
    if (mAnim.mCurrentFrame > 10)
    {
        mShadow->mFlags.Clear(Shadow::eEnabled);

        // Get a local well
        BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellLocal);

        if (!BaseAliveGameObjectPathTLV)
        {
            // No local well, must be an express well
            BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eWellExpress);
        }

        const s16 xpos = FP_GetExponent(mXPos);
        const s16 tlv_mid_x = (BaseAliveGameObjectPathTLV->mTopLeftX + BaseAliveGameObjectPathTLV->mBottomRightX) / 2;
        if (xpos > tlv_mid_x)
        {
            mXPos -= mSpriteScale;
        }
        else if (xpos < tlv_mid_x)
        {
            mXPos += mSpriteScale;
        }
    }

    if (mAnim.mCurrentFrame == 11)
    {
        if (mSpriteScale == FP_FromDouble(0.5))
        {
            mAnim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
        }
        else
        {
            mAnim.mRenderLayer = Layer::eLayer_BeforeWell_22;
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_124_timer = 15;

        SfxPlayMono(relive::SoundEffects::WellEnter, 0, mSpriteScale);

        if (sPathInfo->TLV_Get_At_4DB4B0(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eWellExpress))
        {
            mCurrentMotion = eAbeMotions::Motion_82_InsideWellExpress_45CC80;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_79_InsideWellLocal_45CA60;
        }
    }
}

void Abe::Motion_79_InsideWellLocal_45CA60()
{
    const s32 gnFrame = field_124_timer;
    field_124_timer = gnFrame - 1;
    if (!gnFrame)
    {
        BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellLocal);

        if (!BaseAliveGameObjectPathTLV)
        {
            BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eWellExpress);
        }

        field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
        field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3_WalkToRun);

        relive::Path_WellBase* pBaseWell = static_cast<relive::Path_WellBase*>(BaseAliveGameObjectPathTLV);
        if (pBaseWell->mTlvType == ReliveTypes::eWellLocal)
        {
            relive::Path_WellLocal* pLocal = static_cast<relive::Path_WellLocal*>(pBaseWell);
            if (SwitchStates_Get(pBaseWell->mSwitchId))
            {
                Calc_Well_Velocity_45C530(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    pLocal->mOnDestX,
                    pLocal->mOnDestY);
            }
            else
            {
                Calc_Well_Velocity_45C530(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    pLocal->mOffDestX,
                    pLocal->mOffDestY);
            }
        }
        else if (pBaseWell->mTlvType == ReliveTypes::eWellExpress)
        {
            relive::Path_WellExpress* pExpress = static_cast<relive::Path_WellExpress*>(pBaseWell);
            Calc_Well_Velocity_45C530(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                pExpress->mExitX,
                pExpress->mExitY);
        }

        MapFollowMe(TRUE);

        mYPos += mVelY;

        if (mVelX >= FP_FromInteger(0))
        {
            mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
        }
        else
        {
            mAnim.mFlags.Set(AnimFlags::eBit5_FlipX);
        }

        SfxPlayMono(relive::SoundEffects::WellExit, 0, mSpriteScale);

        ++mCurrentMotion;
        BaseAliveGameObjectLastLineYPos = mYPos;

        if (mSpriteScale == FP_FromDouble(0.5))
        {
            mAnim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
        }
        else
        {
            mAnim.mRenderLayer = Layer::eLayer_BeforeWell_22;
        }

        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_80_WellShotOut_45D150()
{
    if (mVelY >= FP_FromInteger(0))
    {
        Motion_3_Fall_459B60();
    }
    else
    {
        mVelY += mSpriteScale * FP_FromDouble(1.8);

        mXPos += mVelX;
        mYPos += mVelY;

        SetActiveCameraDelayedFromDir();

        BaseAliveGameObjectPathTLV = sPathInfo->TlvGetAt(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted) || (mCurrentMotion != eAbeMotions::Motion_80_WellShotOut_45D150 && mCurrentMotion != eAbeMotions::Motion_77_ToWellShotOut_45D130))
    {
        if (mSpriteScale == FP_FromDouble(0.5))
        {
            mAnim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
        }
        else
        {
            mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
        }

        mShadow->mFlags.Set(Shadow::Flags::eEnabled);
    }

    if (mCurrentMotion == eAbeMotions::Motion_84_FallLandDie_45A420)
    {
        mHealth = FP_FromInteger(1);
        mCurrentMotion = eAbeMotions::Motion_16_LandSoft_45A360;
    }
}

void Abe::jMotion_81_WellBegin_45C7F0()
{
    jMotion_81_WellBegin_4017F8();
}

void Abe::Motion_82_InsideWellExpress_45CC80()
{
    BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellLocal);

    if (!BaseAliveGameObjectPathTLV)
    {
        BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellExpress);
    }

    relive::Path_WellExpress* pExpressWell = static_cast<relive::Path_WellExpress*>(BaseAliveGameObjectPathTLV);
    if (SwitchStates_Get(pExpressWell->mSwitchId))
    {
        mDstWellLevel = pExpressWell->mOnDestLevel;
        mDstWellPath = pExpressWell->mOnDestPath;
        mDstWellCamera = pExpressWell->mOnDestCamera;
        field_1A0_door_id = pExpressWell->mOnOtherWellId;
    }
    else
    {
        mDstWellLevel = pExpressWell->mOffDestLevel;
        mDstWellPath = pExpressWell->mOffDestPath;
        mDstWellCamera = pExpressWell->mOffDestCamera;
        field_1A0_door_id = pExpressWell->mOffOtherWellId;
    }

    field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
    BaseAliveGameObjectLastLineYPos = mYPos;

    if (mDstWellLevel != gMap.mCurrentLevel || mDstWellPath != gMap.mCurrentPath || mDstWellCamera != gMap.mCurrentCamera)
    {
        field_124_timer = 1;

        if (pExpressWell->mMovieId)
        {
            gMap.SetActiveCam(mDstWellLevel, mDstWellPath, mDstWellCamera, CameraSwapEffects::ePlay1FMV_5, pExpressWell->mMovieId, 0);
        }
        else
        {
            gMap.SetActiveCam(mDstWellLevel, mDstWellPath, mDstWellCamera, CameraSwapEffects::eInstantChange_0, 0, 0);
        }

        // FeeCo hack!
        if (mDstWellLevel == EReliveLevelIds::eFeeCoDepot && mDstWellPath == 1 && mDstWellCamera == 1)
        {
            mVelY = FP_FromInteger(0);
            mVelX = FP_FromInteger(0);
            mXPos = FP_FromInteger(1187);
            mYPos = FP_FromInteger(270);
            mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
            field_1AC_flags.Set(Flags_1AC::e1AC_Bit7_land_softly);
            mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
            mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
        }
        else
        {
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            mCurrentMotion = eAbeMotions::Motion_83_WellExpressShotOut_45CF70;
        }
    }
    else
    {
        Motion_83_WellExpressShotOut_45CF70();
        mYPos -= mVelY * mSpriteScale;
        mVelY = FP_FromInteger(0);
        mVelX = FP_FromInteger(0);
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit3_WalkToRun);
        mCurrentMotion = eAbeMotions::Motion_79_InsideWellLocal_45CA60;
    }
}

void Abe::Motion_83_WellExpressShotOut_45CF70()
{
    PSX_Point camPos = {};
    gMap.GetCurrentCamCoords(&camPos);

    mAnim.mFlags.Set(AnimFlags::eBit3_Render);

    relive::Path_TLV* pTlvIter = nullptr;
    relive::Path_WellBase* pWell = nullptr;
    for (;;)
    {
        pTlvIter = sPathInfo->TlvGetAt(
            pTlvIter,
            FP_FromInteger(camPos.x),
            FP_FromInteger(camPos.y),
            FP_FromInteger(camPos.x + 368),
            FP_FromInteger(camPos.y + 240));

        // At the end, exit.
        if (!pTlvIter)
        {
            break;
        }

        // Is it a well?
        if (pTlvIter->mTlvType == ReliveTypes::eWellLocal || pTlvIter->mTlvType == ReliveTypes::eWellExpress)
        {
            // Is it the target of the previous well?
            relive::Path_WellBase* pWellBase = static_cast<relive::Path_WellBase*>(pTlvIter);
            if (pWellBase->mOtherWellId == field_1A0_door_id)
            {
                pWell = pWellBase;
                break;
            }
        }
    }

    mCurrentLevel = gMap.mCurrentLevel;
    mCurrentPath = gMap.mCurrentPath;

    if (pWell)
    {
        if (pWell->mScale == relive::reliveScale::eHalf)
        {
            mSpriteScale = FP_FromDouble(0.5);
            mScale = Scale::Bg;
        }
        else
        {
            mSpriteScale = FP_FromInteger(1);
            mScale = Scale::Fg;
        }

        mXPos = FP_FromInteger((pWell->mTopLeftX + pWell->mBottomRightX) / 2);
        mYPos = FP_FromInteger(pWell->mBottomRightY);

        BaseAliveGameObjectPathTLV = pWell;

        field_1AC_flags.Set(Flags_1AC::e1AC_Bit3_WalkToRun);
        mCurrentMotion = eAbeMotions::Motion_79_InsideWellLocal_45CA60;
    }
    else
    {
        mXPos = FP_FromInteger(camPos.x + 184);
        mYPos = FP_FromInteger(camPos.y + 80);
        mVelX = mSpriteScale * FP_FromDouble(-2.68);
        mVelY = mSpriteScale * FP_FromInteger(-15);
    }
}

void Abe::Motion_84_FallLandDie_45A420()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mCurrentFrame == 0)
    {
        SfxPlayMono(relive::SoundEffects::KillEffect, 85);
        SND_SEQ_Play(SeqId::HitBottomOfDeathPit_9, 1, 95, 95);
        relive_new ScreenShake(true, false);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (static_cast<s32>(sGnFrame) >= field_124_timer)
        {
            ToDieFinal_458910();
        }
    }
}

void Abe::jMotion_85_Fall_455070()
{
    Motion_3_Fall_459B60();
}

ALIVE_VAR(1, 0x5c2c68, s32, sHandstoneSoundChannels_5C2C68, 0);

void Abe::Motion_86_HandstoneBegin_45BD00()
{
    CircularFade* pCircularFade = static_cast<CircularFade*>(sObjectIds.Find_Impl(mCircularFadeId));
    DeathFadeOut* pFade = static_cast<DeathFadeOut*>(sObjectIds.Find_Impl(mDeathFadeOutId));

    switch (field_120_state.stone)
    {
        case StoneStates::eHandstoneBegin_0:
            if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
            {
                // Add ref
                ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kSpotliteResID, TRUE, 0);

                CircularFade* pCircularFade2 = Make_Circular_Fade_4CE8C0(
                    mXPos,
                    mYPos,
                    mSpriteScale,
                    1,
                    0,
                    0);

                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    pCircularFade2->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX);
                }
                else
                {
                    pCircularFade2->mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
                }

                mCircularFadeId = pCircularFade2->mBaseGameObjectId;
                field_120_state.stone = StoneStates::eGetHandstoneType_1;

                SfxPlayMono(relive::SoundEffects::IngameTransition, 90);

                BaseAliveGameObjectPathTLV = sPathInfo->TLV_Get_At_4DB4B0(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    ReliveTypes::eMovieHandStone);

                sHandstoneSoundChannels_5C2C68 = SFX_Play_Pitch(relive::SoundEffects::HandstoneTransition, 127, -300);

                s32 switch_id = 0;
                relive::Path_MovieStone* pMovieStoneTlv = static_cast<relive::Path_MovieStone*>(BaseAliveGameObjectPathTLV);
                if (!pMovieStoneTlv)
                {
                    relive::Path_HandStone* pHandStoneTlv = static_cast<relive::Path_HandStone*>(sPathInfo->TLV_Get_At_4DB4B0(
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        ReliveTypes::eHandStone));

                    BaseAliveGameObjectPathTLV = pHandStoneTlv;

                    if (pHandStoneTlv)
                    {
                        switch_id = pHandStoneTlv->mTriggerSwitchId;

                        mFmvId = static_cast<s16>(pHandStoneTlv->mScale); // TODO: Never used for this type?

                        mHandStoneCams[0] = pHandStoneTlv->mCameraId1;
                        mHandStoneCams[1] = pHandStoneTlv->mCameraId2;
                        mHandStoneCams[2] = pHandStoneTlv->mCameraId3;

                        field_18C_unused = static_cast<s16>(pHandStoneTlv->mTriggerSwitchId); // TODO: Never used?
                    }
                }
                else
                {
                    switch_id = pMovieStoneTlv->mTriggerSwitchId;

                    mFmvId = pMovieStoneTlv->mMovieId;
                    mHandStoneCams[0] = static_cast<s16>(pMovieStoneTlv->mScale); // TODO: Never used?
                    mHandStoneCams[1] = static_cast<s16>(pMovieStoneTlv->mTriggerSwitchId);    // TODO: Never used?
                }

                if (BaseAliveGameObjectPathTLV)
                {
                    if (switch_id > 1)
                    {
                        SwitchStates_Set(static_cast<s16>(switch_id), 1);
                    }

                    mHandStoneType = BaseAliveGameObjectPathTLV->mTlvType;
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_87_HandstoneEnd_45C4F0;
                }
            }
            break;

        case StoneStates::eGetHandstoneType_1:
            if (pCircularFade->VDone())
            {
                if (mHandStoneType == ReliveTypes::eMovieHandStone)
                {
                    pScreenManager->EnableRendering();

                    FmvInfo* pFmvRec = Path_Get_FMV_Record(gMap.mCurrentLevel, mFmvId);
                    u32 pos = 0;

                    Get_fmvs_sectors(pFmvRec->field_0_pName, 0, 0, &pos, 0, 0);
                    sLevelId_dword_5CA408 = static_cast<u32>(MapWrapper::ToAE(gMap.mCurrentLevel));

                    relive_new Movie(pFmvRec->field_4_id, pos, static_cast<s16>(pFmvRec->field_6_flags & 1), static_cast<s16>(pFmvRec->field_8_flags), pFmvRec->field_A_volume);
                    field_120_state.stone = StoneStates::eHandstoneMovieDone_2;
                }
                else if (mHandStoneType == ReliveTypes::eHandStone)
                {
                    mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                    mHandStoneCamIdx = 1;
                    field_120_state.stone = StoneStates::eWaitForInput_4;
                    pCircularFade->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                    mCircularFadeId = Guid{};
                    DeathFadeOut* pFade33 = relive_new DeathFadeOut(Layer::eLayer_FadeFlash_40, 0, 0, 8, TPageAbr::eBlend_2);
                    if (pFade33)
                    {
                        mDeathFadeOutId = pFade33->mBaseGameObjectId;
                    }

                    mDstWellCamera = gMap.mCurrentCamera;
                    gMap.SetActiveCam(mCurrentLevel, mCurrentPath, mHandStoneCams[0], CameraSwapEffects::eInstantChange_0, 0, 0);
                }
            }
            break;

        case StoneStates::eHandstoneMovieDone_2:
            if (sMovie_ref_count_BB4AE4 == 0)
            {
                gPsxDisplay.PutCurrentDispEnv();
                pScreenManager->DecompressCameraToVRam((u16**) gMap.field_2C_camera_array[0]->field_C_pCamRes);
                pScreenManager->EnableRendering();
                pCircularFade->VFadeIn(0, 0);
                field_120_state.stone = StoneStates::eHandstoneEnd_3;
            }
            break;

        case StoneStates::eHandstoneEnd_3:
            if (pCircularFade->VDone())
            {
                pCircularFade->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                mCircularFadeId = Guid{};

                mCurrentMotion = eAbeMotions::Motion_87_HandstoneEnd_45C4F0;

                if (sHandstoneSoundChannels_5C2C68)
                {
                    SND_Stop_Channels_Mask(sHandstoneSoundChannels_5C2C68);
                    sHandstoneSoundChannels_5C2C68 = 0;
                }

                u8** ppResToFree = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kSpotliteResID, 0, 0);
                ResourceManager::FreeResource_49C330(ppResToFree);
            }
            break;

        case StoneStates::eWaitForInput_4:
            if (pFade->field_7E_bDone)
            {
                if (Input().mPads[sCurrentControllerIndex].mHeld & 0x300000)
                {
                    pFade->Init(Layer::eLayer_FadeFlash_40, 1, 0, 8);
                    field_120_state.stone = StoneStates::eCamChangeTransition_5;
                    SfxPlayMono(relive::SoundEffects::IngameTransition, 90);
                }
            }
            break;

        case StoneStates::eCamChangeTransition_5:
            if (pFade->field_7E_bDone)
            {
                if (mHandStoneCamIdx < 3 && mHandStoneCams[mHandStoneCamIdx] != 0)
                {
                    field_120_state.stone = StoneStates::eWaitForInput_4;

                    pFade->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                    pFade = relive_new DeathFadeOut(Layer::eLayer_FadeFlash_40, 0, 0, 8, TPageAbr::eBlend_2);
                    if (pFade)
                    {
                        mDeathFadeOutId = pFade->mBaseGameObjectId;
                    }

                    gMap.SetActiveCam(
                        mCurrentLevel,
                        mCurrentPath,
                        mHandStoneCams[mHandStoneCamIdx++],
                        CameraSwapEffects::eInstantChange_0,
                        0,
                        0);
                }
                else
                {
                    field_120_state.stone = StoneStates::eSetActiveCamToAbe_6;
                }
            }
            break;

        case StoneStates::eSetActiveCamToAbe_6:
            if (pFade->field_7E_bDone)
            {
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                field_120_state.stone = StoneStates::eCircularFadeExit_7;
                gMap.SetActiveCam(
                    mCurrentLevel,
                    mCurrentPath,
                    mDstWellCamera,
                    CameraSwapEffects::eInstantChange_0,
                    0,
                    0);
            }
            break;

        case StoneStates::eCircularFadeExit_7:
        {
            pFade->mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            mDeathFadeOutId = Guid{};

            CircularFade* pCircularFade2 = Make_Circular_Fade_4CE8C0(mXPos, mYPos, mSpriteScale, 0, 0, 0);
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                pCircularFade2->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX);
            }
            else
            {
                pCircularFade2->mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
            }

            mCircularFadeId = pCircularFade2->mBaseGameObjectId;
            field_120_state.stone = StoneStates::eHandstoneEnd_3;

            if (sHandstoneSoundChannels_5C2C68)
            {
                SND_Stop_Channels_Mask(sHandstoneSoundChannels_5C2C68);
                sHandstoneSoundChannels_5C2C68 = 0;
            }
        }
        break;

        default:
            return;
    }
}

void Abe::Motion_87_HandstoneEnd_45C4F0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_88_GrenadeMachineUse_45C510()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_89_BrewMachineBegin_4584C0()
{
    if (field_120_state.raw > 0)
    {
        if (field_120_state.raw <= 36u)
        {
            if (field_120_state.raw > 11u && !((field_120_state.raw - 12) % 6))
            {
                SFX_Play_Pitch(relive::SoundEffects::BrewMachineUseEnd, 0, 32 * field_120_state.raw);
            }
            field_120_state.raw++;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_90_BrewMachineEnd_4585B0;
        }
    }
    else if (mAnim.mCurrentFrame == 8)
    {
        if (GetEvilFart_4585F0(FALSE))
        {
            SfxPlayMono(relive::SoundEffects::BrewMachineUseStart, 0);
        }
        else
        {
            SfxPlayMono(relive::SoundEffects::BrewMachineUseEmpty, 0);
        }
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (GetEvilFart_4585F0(TRUE))
        {
            SfxPlayMono(relive::SoundEffects::BrewMachineUseMid, 0);
            field_120_state.raw = 1;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_90_BrewMachineEnd_4585B0;
        }
    }
}

void Abe::Motion_90_BrewMachineEnd_4585B0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
        mCurrentMotion = eAbeMotions::Motion_0_Idle_44EEB0;
        field_124_timer = 1;
    }
}

// Let go of an edge/hoist/pull ring
void Abe::Motion_91_FallingFromGrab_4557B0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
    }

    Motion_3_Fall_459B60();

    if (mCurrentMotion == eAbeMotions::Motion_84_FallLandDie_45A420)
    {
        mCurrentMotion = eAbeMotions::Motion_16_LandSoft_45A360;
    }

    mPreviousMotion = eAbeMotions::Motion_91_FallingFromGrab_4557B0;
}

void Abe::Motion_92_ForceDownFromHoist_455800()
{
    if (!field_124_timer)
    {
        mShadow->mFlags.Clear(Shadow::eShadowAtBottom);
        VOnTrapDoorOpen();
        FP hitX = {};
        FP hitY = {};
        if (sCollisions->Raycast(
                mXPos,
                mYPos + (mSpriteScale * FP_FromInteger(75)),
                mXPos,
                mYPos + FP_FromInteger(10),
                &BaseAliveGameObjectCollisionLine,
                &hitX,
                &hitY,
                mScale == Scale::Fg ? kFgFloor : kBgFloor)
            == 1)
        {
            mYPos = hitY;
            mCurrentMotion = eAbeMotions::Motion_84_FallLandDie_45A420;
            field_128.mRegenHealthTimer = sGnFrame + 900;
            mPreviousMotion = eAbeMotions::Motion_3_Fall_459B60;
            return;
        }
        mYPos += (mSpriteScale * FP_FromInteger(75));
        BaseAliveGameObjectLastLineYPos = mYPos;
        BaseAliveGameObjectCollisionLine = nullptr;
        field_124_timer = field_124_timer + 1;
    }
    Motion_3_Fall_459B60();
}

void Abe::Motion_93_WalkOffEdge_455970()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
    }
    Motion_3_Fall_459B60();
}

void Abe::Motion_94_RunOffEdge_4559A0()
{
    Motion_93_WalkOffEdge_455970();
}

void Abe::Motion_95_SneakOffEdge_4559C0()
{
    Motion_93_WalkOffEdge_455970();
}

void Abe::Motion_96_HopToFall_4559E0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mXPos = (mSpriteScale * FP_FromInteger(5)) + mXPos;
    }
    else
    {
        mXPos = mXPos - (mSpriteScale * FP_FromInteger(5));
    }

    mVelY += (mSpriteScale * FP_FromInteger(4));
    Motion_93_WalkOffEdge_455970();
}

void Abe::Motion_97_RunJumpToFall_455A80()
{
    Motion_93_WalkOffEdge_455970();
}

void Abe::Motion_98_RollOffEdge_455AA0()
{
    Motion_93_WalkOffEdge_455970();
}

void Abe::Motion_99_LeverUse_455AC0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
        {
            mCurrentMotion = eAbeMotions::Motion_34_DunnoBegin_44ECF0;
        }
        else
        {
            ToIdle_44E6B0();
        }
    }
}

void Abe::Motion_100_SlapBomb_455B60()
{
    BaseAliveGameObject* pItem = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(mSlappableOrPickupId));
    if (sActiveHero->mAnim.mCurrentFrame >= 6)
    {
        if (pItem)
        {
            pItem->VOnPickUpOrSlapped();
            mSlappableOrPickupId = Guid{};
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
    }
}

void Abe::Motion_101_KnockForward_455420()
{
    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_44EC10();
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            if (WallHit(mSpriteScale * FP_FromInteger(50), mVelX))
            {
                mVelX = FP_FromInteger(0);
            }
            MoveWithVelocity_450FA0(FP_FromDouble(0.7));
        }
        else
        {
            Motion_3_Fall_459B60();
            if (mCurrentMotion == eAbeMotions::Motion_84_FallLandDie_45A420 || mCurrentMotion == eAbeMotions::Motion_16_LandSoft_45A360)
            {
                mCurrentMotion = eAbeMotions::Motion_101_KnockForward_455420;
            }
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (!mBaseAliveGameObjectFlags.Get(Flags_114::e114_MotionChanged_Bit2) && (BaseAliveGameObjectCollisionLine || !mAnim.mFlags.Get(AnimFlags::eBit3_Render)))
        {
            if (mHealth > FP_FromInteger(0) || gAbeBulletProof_5C1BDA)
            {
                mCurrentMotion = eAbeMotions::jMotion_103_KnockForwardGetUp_455380;
            }
            else
            {
                ToDieFinal_458910();
            }
        }
    }
}

void Abe::Motion_102_RollingKnockForward_455310()
{
    Motion_74_RollingKnockback_455290();
    if (mCurrentMotion == eAbeMotions::Motion_72_KnockbackGetUp_455340)
    {
        mCurrentMotion = eAbeMotions::jMotion_103_KnockForwardGetUp_455380;
    }
}

void Abe::jMotion_103_KnockForwardGetUp_455380()
{
    Motion_72_KnockbackGetUp_455340();
}

void Abe::Motion_104_RockThrowStandingHold_455DF0()
{
    auto pRock = static_cast<BaseThrowable*>(sObjectIds.Find_Impl(mThrowableId));
    if (mAnim.mCurrentFrame >= 4)
    {
        if (Input().isPressed(sInputKey_Left | sInputKey_Right | sInputKey_Up | sInputKey_Down))
        {
            if (Input().isPressed(sInputKey_Right))
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mThrowDirection = 0;
                }
                else
                {
                    mThrowDirection = 2;
                }
            }
            else if (Input().isPressed(sInputKey_Left))
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mThrowDirection = 2;
                }
                else
                {
                    mThrowDirection = 0;
                }
            }
            else if (Input().isPressed(sInputKey_Up))
            {
                mThrowDirection = 1;
            }
            else
            {
                // Down
                mThrowDirection = 3;
            }
            mCurrentMotion = eAbeMotions::Motion_105_RockThrowStandingThrow_456460;
        }
    }

    if (!Input().isPressed(sInputKey_ThrowItem)) // ?? isn't released like in the crouching motion ??
    {
        pRock->VToDead();
        mThrowableId = Guid{};
        mCurrentMotion = eAbeMotions::Motion_106_RockThrowStandingEnd_455F20;
        if (!gInfiniteThrowables)
        {
            mThrowableCount++;
        }
    }
}

void Abe::Motion_105_RockThrowStandingThrow_456460()
{
    if (mAnim.mCurrentFrame == 0)
    {
        SfxPlayMono(relive::SoundEffects::AirStream, 0, mSpriteScale);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_106_RockThrowStandingEnd_455F20()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_107_RockThrowCrouchingHold_454410()
{
    auto pRock = static_cast<BaseThrowable*>(sObjectIds.Find_Impl(mThrowableId));
    if (mAnim.mCurrentFrame >= 4)
    {
        if (Input().isPressed(sInputKey_Left | sInputKey_Right | sInputKey_Up | sInputKey_Down))
        {
            mThrowDirection = 4;
            mCurrentMotion = eAbeMotions::Motion_108_RockThrowCrouchingThrow_454500;
            if (pRock->Type() == ReliveTypes::eMeat)
            {
                mThrowDirection = 5;
            }
        }
    }

    if (Input().IsReleased(sInputKey_ThrowItem))
    {
        pRock->VToDead();
        mThrowableId = Guid{};
        mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
        if (!gInfiniteThrowables)
        {
            mThrowableCount++;
        }
    }
}

void Abe::Motion_108_RockThrowCrouchingThrow_454500()
{
    if (mAnim.mCurrentFrame == 0)
    {
        SfxPlayMono(relive::SoundEffects::AirStream, 0, mSpriteScale);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
    }
}

void Abe::Motion_109_ZShotRolling_455550()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);
    Motion_3_Fall_459B60();

    if (mCurrentMotion != eAbeMotions::Motion_109_ZShotRolling_455550 && !gAbeBulletProof_5C1BDA)
    {
        if (BaseAliveGameObject_PlatformId != Guid{})
        {
            VOnTrapDoorOpen();
        }
        mCurrentMotion = eAbeMotions::Motion_109_ZShotRolling_455550;
        BaseAliveGameObjectCollisionLine = nullptr;
        mYPos += (mSpriteScale * FP_FromInteger(4));
    }

    if (!gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
        {
            if (!mBaseAliveGameObjectFlags.Get(Flags_114::e114_MotionChanged_Bit2))
            {
                mYPos += FP_FromInteger(240);
                Mudokon_SFX(MudSounds::eDeathDropScream_15, 0, 0, this);
                ToDie_4588D0();
            }
        }
    }
}

void Abe::Motion_110_ZShot_455670()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);
    Motion_3_Fall_459B60();

    if (mCurrentMotion != eAbeMotions::Motion_110_ZShot_455670 && !gAbeBulletProof_5C1BDA)
    {
        if (BaseAliveGameObject_PlatformId != Guid{})
        {
            BaseGameObject* pLiftPoint = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
            if (pLiftPoint->Type() == ReliveTypes::eLiftPoint)
            {
                static_cast<LiftPoint*>(pLiftPoint)->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
            }
            VOnTrapDoorOpen();
        }
        mCurrentMotion = eAbeMotions::Motion_110_ZShot_455670;
        BaseAliveGameObjectCollisionLine = nullptr;
        mYPos += (mSpriteScale * FP_FromInteger(4));
    }

    if (!gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        mYPos += FP_FromInteger(240);
        Mudokon_SFX(MudSounds::eDeathDropScream_15, 0, 0, this);
        ToDie_4588D0();
    }
}

void Abe::Motion_111_PickupItem_4564A0()
{
    auto pRock = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(mSlappableOrPickupId));

    if (mAnim.mCurrentFrame == 7)
    {
        SfxPlayMono(relive::SoundEffects::PickupItem, 0, mSpriteScale);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
    }

    if (sActiveHero->mAnim.mCurrentFrame >= 5)
    {
        if (pRock)
        {
            pRock->VOnPickUpOrSlapped();
            mSlappableOrPickupId = Guid{};
        }
    }
}

void Abe::Motion_112_Chant_45B1C0()
{
    BaseAliveGameObject* pPossessTarget = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(mPossessedObjectId));
    OrbWhirlWind* pOrbWhirlWind = static_cast<OrbWhirlWind*>(sObjectIds.Find_Impl(mOrbWhirlWindId));

    if (field_120_state.chant != ChantStates::eWaitForUnpossessing_3 && field_120_state.chant != ChantStates::eUnpossessing_4)
    {
        SND_SEQ_PlaySeq(SeqId::MudokonChant1_10, 0, 0);
    }

    if (!pOrbWhirlWind)
    {
        mOrbWhirlWindId = Guid{};
    }

    switch (field_120_state.chant)
    {
        case ChantStates::eIdleChanting_0:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);

            BaseAliveGameObject* pObj = FindObjectToPossess_44B7B0(); // Find a victim.

            if (mRingPulseTimer)
            {
                if (!mHaveShrykull && !mHaveInvisibility && !(field_1AC_flags.Get(Flags_1AC::e1AC_eBit15_have_healing)))
                {
                    const PSX_RECT bRect = VGetBoundingRect();

                    AbilityRing::Factory(
                        FP_FromInteger((bRect.x + bRect.w) / 2),
                        FP_FromInteger((bRect.y + bRect.h) / 2),
                        RingTypes::eExplosive_Emit_1,
                        mSpriteScale);

                    mRingPulseTimer = 0;
                }
            }

            if (mRingPulseTimer)
            {
                if (mHaveInvisibility)
                {
                    mRingPulseTimer = 0;
                    mHaveInvisibility = 0;

                    if (mInvisibilityTimer)
                    {
                        mInvisibilityTimer += mInvisibilityDuration;
                    }
                    else
                    {
                        mInvisibilityTimer = sGnFrame + mInvisibilityDuration;
                    }

                    field_174_unused = 0;

                    InvisibleEffect* pInvisible = static_cast<InvisibleEffect*>(sObjectIds.Find_Impl(mInvisibleEffectId));
                    if (!pInvisible || pInvisible->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
                    {
                        pInvisible = relive_new InvisibleEffect(this);
                        mInvisibleEffectId = pInvisible->mBaseGameObjectId;
                    }
                    pInvisible->BecomeInvisible();
                }

                if (mRingPulseTimer)
                {
                    if (field_1AC_flags.Get(Flags_1AC::e1AC_eBit15_have_healing))
                    {
                        bool bAliveMudIsInSameScreen = false;
                        for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
                        {
                            BaseAliveGameObject* pObjIter = gBaseAliveGameObjects->ItemAt(i);
                            if (!pObjIter)
                            {
                                break;
                            }

                            if (pObjIter->Type() == ReliveTypes::eMudokon)
                            {
                                if (pObjIter->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit3_Can_Be_Possessed)) // TODO: Is sick flag ?
                                {
                                    if (pObjIter->Is_In_Current_Camera() == CameraPos::eCamCurrent_0 && pObjIter->mHealth > FP_FromInteger(0))
                                    {
                                        bAliveMudIsInSameScreen = true;
                                    }
                                }
                            }
                        }

                        if (bAliveMudIsInSameScreen)
                        {
                            const PSX_RECT bRect = VGetBoundingRect();

                            AbilityRing::Factory(
                                FP_FromInteger((bRect.x + bRect.w) / 2),
                                FP_FromInteger((bRect.y + bRect.h) / 2),
                                RingTypes::eHealing_Emit_12,
                                mSpriteScale);

                            field_1AC_flags.Clear(Flags_1AC::e1AC_eBit15_have_healing);
                            mRingPulseTimer = 0;
                        }
                    }
                }
            }

            // Stopped chanting?
            if ((mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame) || mAnim.mCurrentFrame == 3) && !Input_IsChanting_45F260())
            {
                mCurrentMotion = eAbeMotions::Motion_113_ChantEnd_45BBE0;
                mPossessedObjectId = Guid{};
                if (pOrbWhirlWind)
                {
                    pOrbWhirlWind->ToStop();
                    mOrbWhirlWindId = Guid{};
                }
                return;
            }

            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle(this);
            }

            if (static_cast<s32>(sGnFrame) >= field_124_timer - 70)
            {
                if (pObj)
                {
                    if (!pOrbWhirlWind)
                    {
                        const FP yPos = mYPos - (mSpriteScale * FP_FromInteger(38));
                        const FP xOff = mSpriteScale * ((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? FP_FromInteger(-4) : FP_FromInteger(4));
                        pOrbWhirlWind = relive_new OrbWhirlWind(
                            xOff + mXPos,
                            yPos,
                            mSpriteScale,
                            0);

                        mOrbWhirlWindId = pOrbWhirlWind->mBaseGameObjectId;
                    }
                }
                else
                {
                    field_124_timer = sGnFrame + 70;
                    if (pOrbWhirlWind)
                    {
                        pOrbWhirlWind->ToStop();
                        pOrbWhirlWind = nullptr;
                        mOrbWhirlWindId = Guid{};
                    }
                }
            }


            if (static_cast<s32>(sGnFrame) <= field_124_timer)
            {
                return;
            }

            if (!pObj)
            {
                return;
            }

            mPossessedObjectId = pObj->mBaseGameObjectId;
            SFX_Play_Pitch(relive::SoundEffects::PossessEffect, 0, -600);
            field_120_state.chant = ChantStates::ePossessVictim_1;
            field_124_timer = sGnFrame + 30;

            const PSX_RECT bRect = pObj->VGetBoundingRect();
            pOrbWhirlWind->ToSpin(
                FP_FromInteger((bRect.w - bRect.x) / 2),
                FP_FromInteger((bRect.h - bRect.y) / 2),
                pObj->mSpriteScale,
                pObj);

            relive_new PossessionFlicker(sActiveHero, 30, 128, 255, 255);
        }
            return;

        case ChantStates::ePossessVictim_1:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);

            if (static_cast<s32>(sGnFrame) <= field_124_timer)
            {
                if (!pPossessTarget || pPossessTarget->mBaseGameObjectFlags.Get(BaseGameObject::eDead) || pPossessTarget->mHealth <= FP_FromInteger(0) || pPossessTarget->Is_In_Current_Camera() != CameraPos::eCamCurrent_0)
                {
                    mCurrentMotion = eAbeMotions::Motion_113_ChantEnd_45BBE0;
                    mPossessedObjectId = Guid{};
                    if (pOrbWhirlWind)
                    {
                        pOrbWhirlWind->ToStop();
                        mOrbWhirlWindId = Guid{};
                    }
                }
            }
            else
            {
                field_120_state.chant = ChantStates::ePossessedVictim_2;
            }
        }
            return;

        case ChantStates::ePossessedVictim_2:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);
            mOrbWhirlWindId = Guid{};

            if (!pPossessTarget)
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
                {
                    mCurrentMotion = eAbeMotions::Motion_113_ChantEnd_45BBE0;
                }
                return;
            }

            if (pPossessTarget->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
            {
                mPossessedObjectId = Guid{};
            }

            if (pPossessTarget->mHealth <= FP_FromInteger(0))
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
                {
                    mCurrentMotion = eAbeMotions::Motion_113_ChantEnd_45BBE0;
                }
                return;
            }

            sControlledCharacter = pPossessTarget;

            pPossessTarget->VPossessed();

            mPossessedObjectId = Guid{};

            if (sControlledCharacter->Type() == ReliveTypes::eSlig || sControlledCharacter->Type() == ReliveTypes::eFlyingSlig || sControlledCharacter->Type() == ReliveTypes::eCrawlingSlig || sControlledCharacter->Type() == ReliveTypes::eGlukkon)
            {
                field_1AC_flags.Set(Flags_1AC::e1AC_Bit9_laugh_at_chant_end);
            }

            relive_new PossessionFlicker(sControlledCharacter, 60, 128, 255, 255);

            SND_SEQ_Stop(SeqId::MudokonChant1_10);
            SFX_Play_Pitch(relive::SoundEffects::PossessEffect, 70, 400);
            field_120_state.chant = ChantStates::eWaitForUnpossessing_3;
        }
            return;

        case ChantStates::eWaitForUnpossessing_3:
        {
            if (sControlledCharacter != this)
            {
                return;
            }

            relive_new PossessionFlicker(sControlledCharacter, 15, 128, 255, 255);

            field_120_state.chant = ChantStates::eUnpossessing_4;
            field_124_timer = sGnFrame + 15;
        }
            return;

        case ChantStates::eUnpossessing_4:
        {
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle(this);
            }

            if (static_cast<s32>(sGnFrame) <= field_124_timer)
            {
                return;
            }

            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mCurrentMotion = eAbeMotions::Motion_113_ChantEnd_45BBE0;
            }
        }
            return;

        case ChantStates::eChantingForBirdPortal_6:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle(this);
            }
        }
            return;

        default:
            return;
    }
}

void Abe::Motion_113_ChantEnd_45BBE0()
{
    SND_SEQ_Stop(SeqId::MudokonChant1_10);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_1AC_flags.Get(Flags_1AC::e1AC_Bit9_laugh_at_chant_end))
        {
            mCurrentMotion = eAbeMotions::Motion_9_Speak_45B180;
            Mudokon_SFX(MudSounds::eGiggle_8, 0, 0, this);
            field_1AC_flags.Clear(Flags_1AC::e1AC_Bit9_laugh_at_chant_end);
        }
        else
        {
            ToIdle_44E6B0();
        }
    }
}

void Abe::Motion_114_DoorEnter_459470()
{
    switch (field_120_state.door)
    {
        case AbeDoorStates::eAbeComesIn_0:
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_120_state.door = AbeDoorStates::eWaitABit_2;
                mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                field_128.field_0_abe_timer = sGnFrame + 3;
            }
            return;

        case AbeDoorStates::eWaitABit_2:
            if (field_128.field_0_abe_timer <= static_cast<s32>(sGnFrame))
            {
                field_120_state.door = AbeDoorStates::eToState4_3;
                field_128.field_0_abe_timer = sGnFrame + 3;
            }
            return;

        case AbeDoorStates::eToState4_3:
            if (field_128.field_0_abe_timer <= static_cast<s32>(sGnFrame))
            {
                field_120_state.door = AbeDoorStates::eSetNewActiveCamera_4;
            }
            return;

        case AbeDoorStates::eSetNewActiveCamera_4:
        {
            relive::Path_Door* pDoorTlv = static_cast<relive::Path_Door*>(sPathInfo->TLV_Get_At_4DB4B0(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eDoor));

            BaseAliveGameObjectPathTLV = pDoorTlv;

            if (pDoorTlv->mClearThrowables == relive::reliveChoice::eYes)
            {
                if (mThrowableCount > 0 && gpThrowableArray)
                {
                    gpThrowableArray->Remove(mThrowableCount);
                    mThrowableCount = 0;
                }
            }

            // An OWI hack. When both Mudomo and Mundanchee are done, force back to Necrum Mines.
            bool hackChange = false;
            if (gMap.mCurrentLevel == EReliveLevelIds::eMudomoVault_Ender)
            {
                if (gMap.mCurrentPath == 13 && gMap.mCurrentCamera == 14 && field_1AC_flags.Get(Flags_1AC::e1AC_eBit16_is_mudanchee_vault_ender))
                {
                    hackChange = true;
                }
            }
            else if (gMap.mCurrentLevel == EReliveLevelIds::eMudancheeVault_Ender)
            {
                if (gMap.mCurrentPath == 11 && gMap.mCurrentCamera == 2 && field_1AE_flags.Get(Flags_1AE::e1AE_Bit1_is_mudomo_vault_ender))
                {
                    hackChange = true;
                }
            }

            if (hackChange)
            {
                // Plays FMV where the weirdos give Abe the drunk mud healing power and then dumps Abe at the portal that leads
                // back to Necrum mines.
                gMap.SetActiveCam(EReliveLevelIds::eNecrum, 3, 10, CameraSwapEffects::ePlay1FMV_5, 22, 0);
                mVelY = FP_FromInteger(0);
                mVelX = FP_FromInteger(0);
                mXPos = FP_FromInteger(2287);
                mYPos = FP_FromInteger(800);
                field_1AC_flags.Set(Flags_1AC::e1AC_Bit7_land_softly);
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
                mSpriteScale = FP_FromInteger(1);
                mScale = Scale::Fg;
                mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                return;
            }

            gMap.mDoorTransition = 1;
            s16 bForceChange = 0;
            const CameraSwapEffects effect = kPathChangeEffectToInternalScreenChangeEffect_55D55C[pDoorTlv->mWipeEffect];
            if (effect == CameraSwapEffects::ePlay1FMV_5 || effect == CameraSwapEffects::eUnknown_11)
            {
                bForceChange = 1;
            }

            gMap.SetActiveCam(
                pDoorTlv->mNextLevel,
                pDoorTlv->mNextPath,
                pDoorTlv->mNextCamera,
                effect,
                pDoorTlv->mMovieId,
                bForceChange);

            field_120_state.door = AbeDoorStates::eSetNewAbePosition_5;
            field_1A0_door_id = pDoorTlv->mTargetDoorId;
        }
            return;

        case AbeDoorStates::eSetNewAbePosition_5:
        {
            gMap.mDoorTransition = 0;
            mCurrentLevel = gMap.mCurrentLevel;
            mCurrentPath = gMap.mCurrentPath;

            relive::Path_Door* pDoorTlv2 = static_cast<relive::Path_Door*>(sPathInfo->TLV_First_Of_Type_In_Camera(ReliveTypes::eDoor, 0));
            BaseAliveGameObjectPathTLV = pDoorTlv2;
            relive::Path_Door* pTargetDoorTlv = pDoorTlv2;
            if (pTargetDoorTlv->mDoorId != field_1A0_door_id)
            {
                do
                {
                    relive::Path_Door* pDoorIter = static_cast<relive::Path_Door*>(Path::TLV_Next_Of_Type(BaseAliveGameObjectPathTLV, ReliveTypes::eDoor));
                    BaseAliveGameObjectPathTLV = pDoorIter;
                    pTargetDoorTlv = pDoorIter;

                    if (!pTargetDoorTlv)
                    {
                        ALIVE_FATAL("Couldn't find target door. If this is a custom level, check if the level, path and camera is correct.");
                    }
                }
                while (pTargetDoorTlv->mDoorId != field_1A0_door_id);
            }

            if (pTargetDoorTlv->mScale == relive::reliveScale::eHalf)
            {
                mSpriteScale = FP_FromDouble(0.5);
                mAnim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
                mScale = Scale::Bg;
            }
            else
            {
                mSpriteScale = FP_FromDouble(1.0);
                mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                mScale = Scale::Fg;
            }

            // The door controls which way Abe faces when he exits it.
            if (pTargetDoorTlv->mExitDirection == relive::reliveXDirection::eRight)
            {
                mAnim.mFlags.Set(AnimFlags::eBit5_FlipX);
            }
            else
            {
                mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
            }

            mXPos = FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftX) + FP_FromInteger((BaseAliveGameObjectPathTLV->mBottomRightX - BaseAliveGameObjectPathTLV->mTopLeftX) / 2);


            MapFollowMe(TRUE);

            PathLine* pathLine = nullptr;
            FP hitX = {};
            FP hitY = {};
            if (sCollisions->Raycast(
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY),
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY),
                    &pathLine,
                    &hitX,
                    &hitY,
                    (mScale == Scale::Fg) ? kFgFloorCeilingOrWalls : kBgFloorCeilingOrWalls))
            {
                BaseAliveGameObjectCollisionLine = pathLine;
                mYPos = hitY;
            }
            else
            {
                BaseAliveGameObjectCollisionLine = nullptr;
                field_1AC_flags.Set(Flags_1AC::e1AC_Bit7_land_softly);
                mYPos = FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY);
                BaseAliveGameObjectLastLineYPos = FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY);
            }

            mRingPulseTimer = 0;
            InvisibleEffect* pInvisibleEffect = static_cast<InvisibleEffect*>(sObjectIds.Find_Impl(mInvisibleEffectId));
            if (pInvisibleEffect)
            {
                if (!(pInvisibleEffect->mBaseGameObjectFlags.Get(BaseGameObject::eDead)))
                {
                    pInvisibleEffect->ClearInvisibility();
                    mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit8_bInvisible);
                    mInvisibleEffectId = Guid{};
                    mInvisibilityTimer = 0;
                }
            }

            mHealth = FP_FromInteger(1);
            field_120_state.door = AbeDoorStates::eAbeComesOut_6;
            field_128.field_0_abe_timer = sGnFrame + 30;
        }
            return;

        case AbeDoorStates::eAbeComesOut_6:
            if (field_128.field_0_abe_timer > static_cast<s32>(sGnFrame))
            {
                return;
            }

            field_120_state.door = AbeDoorStates::eAbeComesIn_0;
            if (BaseAliveGameObjectCollisionLine)
            {
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                mCurrentMotion = eAbeMotions::Motion_115_DoorExit_459A40;
            }
            else
            {
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                // Abe opens the door and he falls through the floor.
                mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
            }
            return;

        default:
            return;
    }
}

void Abe::Motion_115_DoorExit_459A40()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        // Now that we've exited the door, should it close behind us?
        if (static_cast<relive::Path_Door*>(sPathInfo->TLV_Get_At_4DB4B0(
                                        FP_GetExponent(mXPos),
                                        FP_GetExponent(mYPos),
                                        FP_GetExponent(mXPos),
                                        FP_GetExponent(mYPos),
                                        ReliveTypes::eDoor))
                ->mCloseOnExit == relive::reliveChoice::eYes)
        {
            // TODO: Ret ignored even in real ??
            FindObjectOfType(
                ReliveTypes::eDoor,
                mXPos,
                mYPos - FP_FromInteger(5));

            // Yes, so find it
            for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
            {
                BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
                if (!pObj)
                {
                    break;
                }

                if (pObj->Type() == ReliveTypes::eDoor)
                {
                    Door* pDoor = static_cast<Door*>(pObj);
                    if (pDoor->field_FA_door_number == field_1A0_door_id)
                    {
                        // And close it
                        pDoor->vClose();
                        break;
                    }
                }
            }
        }

        BaseAliveGameObjectPathTLV = sPathInfo->TlvGetAt(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);

        VOnTlvCollision(BaseAliveGameObjectPathTLV);
        ToIdle_44E6B0();
    }
}

void Abe::Motion_116_MineCarEnter_458780()
{
    if (field_120_state.raw == 0)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);
            field_120_state.raw = 1;
            mCurrentMotion = eAbeMotions::Motion_117_InMineCar_4587C0;
        }
    }
}

void Abe::Motion_117_InMineCar_4587C0()
{
    if (Input().isPressed(sInputKey_DoAction))
    {
        auto pMineCar = static_cast<MineCar*>(sControlledCharacter);
        if (pMineCar->field_11C_state == MineCarStates::eParkedWithAbe_1 && pMineCar->field_1BC_turn_direction == MineCarDirs::eUp_3)
        {
            PathLine* pLine = nullptr;
            FP hitX = {};
            FP hitY = {};
            if (sCollisions->Raycast(
                    mXPos,
                    mYPos - FP_FromInteger(2),
                    mXPos,
                    mYPos + FP_FromInteger(2),
                    &pLine,
                    &hitX,
                    &hitY,
                    mScale == Scale::Fg ? kFgFloor : kBgFloor))
            {
                mAnim.mFlags.Set(AnimFlags::eBit2_Animate);
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);

                mCurrentMotion = eAbeMotions::Motion_118_MineCarExit_458890;
            }
        }
    }
}

void Abe::Motion_118_MineCarExit_458890()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
        mCurrentMotion = eAbeMotions::Motion_0_Idle_44EEB0;
        field_124_timer = 1;
    }
}

void Abe::Motion_119_ToShrykull_45A990()
{
    if (field_120_state.raw == 0)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);

            field_120_state.raw = 1;

            relive_new Shrykull();
        }
    }
}

void Abe::Motion_120_EndShrykull_45AB00()
{
    if (field_124_timer)
    {
        field_124_timer = field_124_timer - 1;
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (mRingPulseTimer == 0)
        {
            Free_Shrykull_Resources_45AA90();
        }

        // Abe finds transforming into a god rather funny.
        mCurrentMotion = eAbeMotions::Motion_9_Speak_45B180;
        Mudokon_SFX(MudSounds::eGiggle_8, 0, 0, this);
    }
}

void Abe::Motion_121_LiftGrabBegin_45A600()
{
    auto pLiftPoint = static_cast<LiftPoint*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));
    if (pLiftPoint)
    {
        pLiftPoint->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
    }

    mVelY = FP_FromInteger(0);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_123_LiftGrabIdle_45A6A0;
    }
}

void Abe::Motion_122_LiftGrabEnd_45A670()
{
    mVelY = FP_FromInteger(0);
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_123_LiftGrabIdle_45A6A0()
{
    LiftPoint* pLiftPoint = static_cast<LiftPoint*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));

    FollowLift_45A500();

    if (pLiftPoint)
    {
        pLiftPoint->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
    }

    mVelY = FP_FromInteger(0);

    const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
    if (sInputKey_Up & pressed)
    {
        if (!pLiftPoint->vOnTopFloor())
        {
            mCurrentMotion = eAbeMotions::Motion_124_LiftUseUp_45A780;
        }
    }
    else if (pressed & sInputKey_Down)
    {
        if (!pLiftPoint->vOnBottomFloor())
        {
            mCurrentMotion = eAbeMotions::Motion_125_LiftUseDown_45A7B0;
        }
    }
    else if (pLiftPoint->vOnAnyFloor())
    {
        // You ain't letting go unless you are on a floor where you can walk off.
        mCurrentMotion = eAbeMotions::Motion_122_LiftGrabEnd_45A670;
    }
}

void Abe::Motion_124_LiftUseUp_45A780()
{
    mCurrentMotion = MoveLiftUpOrDown_45A7E0(FP_FromInteger(-4));
}

void Abe::Motion_125_LiftUseDown_45A7B0()
{
    mCurrentMotion = MoveLiftUpOrDown_45A7E0(FP_FromInteger(4));
}

void Abe::Motion_126_TurnWheelBegin_456700()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        WorkWheel* pWheel = static_cast<WorkWheel*>(sObjectIds.Find_Impl(mWorkWheelId));
        if (pWheel)
        {
            pWheel->VStartTurning();
        }
        mCurrentMotion = eAbeMotions::Motion_127_TurnWheelLoop_456750;
        field_120_state.wheel = WorkWheelStates::eTurningWheel_0;
    }
}

void Abe::Motion_127_TurnWheelLoop_456750()
{
    if (field_120_state.wheel == WorkWheelStates::eTurningWheel_0 || field_120_state.wheel == WorkWheelStates::eCheckForNoLongerTurningWheel_1) // The state we enter the main state at.
    {
        relive::Path_LevelLoader* pLevelLoader = static_cast<relive::Path_LevelLoader*>(sPathInfo->TLV_First_Of_Type_In_Camera(ReliveTypes::eLevelLoader, 0));
        if (pLevelLoader && SwitchStates_Get(pLevelLoader->mSwitchId))
        {
            field_120_state.wheel = WorkWheelStates::eMapChanging_2;
            SND_SEQ_Play(SeqId::SaveTriggerMusic_31, 1, 127, 127);
            relive_new MusicTrigger(relive::Path_MusicTrigger::MusicTriggerMusicType::eChime, relive::Path_MusicTrigger::TriggeredBy::eTimer, 0, 0);
            return;
        }
        else
        {
            // Must ALSO do logic below in this instance.
            field_120_state.wheel = WorkWheelStates::eCheckForNoLongerTurningWheel_1;
        }
    }

    if (field_120_state.wheel == WorkWheelStates::eCheckForNoLongerTurningWheel_1)
    {
        if (!(Input().mPads[sCurrentControllerIndex].mPressed & sInputKey_Up))
        {
            // Not holding up anymore, stop.
            WorkWheel* pWheel = static_cast<WorkWheel*>(sObjectIds.Find_Impl(mWorkWheelId));
            if (pWheel)
            {
                pWheel->VStopTurning(1);
            }
            mWorkWheelId = Guid{};
            mCurrentMotion = eAbeMotions::Motion_128_TurnWheelEnd_4569A0;
        }
    }
    else if (field_120_state.wheel == WorkWheelStates::eMapChanging_2)
    {
        // This happens for the Mines Tunnel 1 ender.
        if (!gMap.Is_Point_In_Current_Camera(
                mCurrentLevel,
                mCurrentPath,
                mXPos,
                mYPos,
                0))
        {
            // When we've changed from the camera with the wheels to tunnel 2 this forces the falling state into the well.
            // Another tasty OWI hack.
            auto pWorkWheel = static_cast<WorkWheel*>(sObjectIds.Find_Impl(mWorkWheelId));
            if (pWorkWheel) // Most likely always nullptr here, maybe the whole "stop wheel" was an inlined function.
            {
                pWorkWheel->VStopTurning(1);
            }
            mWorkWheelId = Guid{};

            auto pPathAbeStart = static_cast<relive::Path_AbeStart*>(sPathInfo->TLV_First_Of_Type_In_Camera(ReliveTypes::eAbeStart, 0));
            mXPos = FP_FromInteger((pPathAbeStart->mTopLeftX + pPathAbeStart->mBottomRightX) / 2);
            mYPos = FP_FromInteger(pPathAbeStart->mBottomRightY);
            BaseAliveGameObjectLastLineYPos = FP_FromInteger(pPathAbeStart->mBottomRightY);
            // TODO: OG bug, scale not read from the TLV ??

            mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
            mCurrentMotion = eAbeMotions::jMotion_85_Fall_455070;
            field_1AC_flags.Set(Flags_1AC::e1AC_Bit7_land_softly);
        }
    }
}

void Abe::Motion_128_TurnWheelEnd_4569A0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::Motion_129_PoisonGasDeath_4565C0()
{
    // Play various choke/cough/death sounds as the dying animation progresses.
    switch (mAnim.mCurrentFrame)
    {
        case 0:
            SFX_Play_Pitch(relive::SoundEffects::Choke, 127, 128);
            break;
        case 9:
            SFX_Play_Pitch(relive::SoundEffects::Choke, 127, 384);
            break;
        case 28:
            SFX_Play_Pitch(relive::SoundEffects::Choke, 127, 640);
            break;
        case 32:
            Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 80, 0, this);
            break;
        case 50:
            Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 100, -200, this);
            break;
        case 53:
            Environment_SFX_457A40(EnvironmentSfx::eHitGroundSoft_6, 50, -200, this);
            break;
        default:
            break;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        const s32 previousValue = field_124_timer;
        field_124_timer = previousValue - 1;
        if (previousValue == 0)
        {
            ToDieFinal_458910();
        }
    }
}

void Abe::jMotion_81_WellBegin_4017F8()
{
    Motion_78_WellBegin_45C810();
}

void Abe::FleechDeath_459350()
{
    BaseGameObject* pInvisibleEffect = sObjectIds.Find_Impl(mInvisibleEffectId);
    if (pInvisibleEffect)
    {
        if (!pInvisibleEffect->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
        {
            static_cast<InvisibleEffect*>(pInvisibleEffect)->ClearInvisibility();
            mInvisibleEffectId = Guid{};
        }
    }
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit5_shrivel);
    mCurrentMotion = eAbeMotions::Motion_58_DeadPre_4593E0;
    field_120_state.raw = 0;
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_11, this, 1, 0);
    BaseAliveGameObjectCollisionLine = nullptr;
}

void Abe::ToDie_4588D0()
{
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit5_shrivel);
    mCurrentMotion = eAbeMotions::Motion_56_DeathDropFall_4591F0;
    field_124_timer = 0;
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eNone_0, this, 1, 0);
}

void Abe::ToIdle_44E6B0()
{
    field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
    mVelX = FP_FromInteger(0);
    mVelY = FP_FromInteger(0);
    field_124_timer = sGnFrame;
    mCurrentMotion = eAbeMotions::Motion_0_Idle_44EEB0;
    mPrevHeld = 0;
    mReleasedButtons = 0;
    MapFollowMe(TRUE);
}

void Abe::PickUpThrowabe_Or_PressBomb_454090(FP fpX, s32 fpY, s32 bStandToCrouch)
{
    BaseAliveGameObject* pSlappableOrCollectable = nullptr;
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eInteractive_Bit8))
        {
            BaseAliveGameObject* pAliveObj = static_cast<BaseAliveGameObject*>(pObj);
            if (fpX >= pAliveObj->mCollectionRect.x && fpX <= pAliveObj->mCollectionRect.w)
            {
                const FP yPos = FP_FromInteger(fpY);
                if (yPos >= pAliveObj->mCollectionRect.y && yPos <= pAliveObj->mCollectionRect.h)
                {
                    pSlappableOrCollectable = pAliveObj;
                    mSlappableOrPickupId = pAliveObj->mBaseGameObjectId;
                }
            }
        }
    }

    if (pSlappableOrCollectable)
    {
        bool trySlapOrCollect = false;
        switch (pSlappableOrCollectable->Type())
        {
            case ReliveTypes::eTimedMine_or_MovingBomb:
            case ReliveTypes::eUXB:
                mCurrentMotion = eAbeMotions::Motion_100_SlapBomb_455B60;
                if (bStandToCrouch)
                {
                    mSlappableOrPickupId = Guid{};
                }
                trySlapOrCollect = true;
                break;

            case ReliveTypes::eBone:
            case ReliveTypes::eGrenade:
            case ReliveTypes::eMeat:
            case ReliveTypes::eRock:
                mCurrentMotion = eAbeMotions::Motion_111_PickupItem_4564A0;
                mThrowableCount += static_cast<s8>(static_cast<BaseThrowable*>(pSlappableOrCollectable)->VGetCount()); // TODO: Check types are correct.
                if (!bThrowableIndicatorExists_5C112C)
                {
                    const FP yoff = (mSpriteScale * FP_FromInteger(-30)) + mYPos;
                    const FP xoff = mSpriteScale * FP_FromInteger(0);
                    relive_new ThrowableTotalIndicator(
                        xoff + mXPos,
                        yoff,
                        mAnim.mRenderLayer,
                        mAnim.field_14_scale,
                        mThrowableCount,
                        1);
                }
                trySlapOrCollect = true;
                break;

            case ReliveTypes::eMine:
                mSlappableOrPickupId = Guid{};
                trySlapOrCollect = true;
                break;
            default:
                break;
        }

        if (trySlapOrCollect)
        {
            if (mCurrentMotion == eAbeMotions::Motion_111_PickupItem_4564A0)
            {
                if (bStandToCrouch)
                {
                    SfxPlayMono(relive::SoundEffects::PickupItem, 0, mSpriteScale);
                    pSlappableOrCollectable->VOnPickUpOrSlapped();
                    mSlappableOrPickupId = Guid{};
                    mCurrentMotion = eAbeMotions::Motion_17_CrouchIdle_456BC0;
                }
            }
        }
    }
}

void Abe::Get_Shrykull_Resources_45AA20()
{
    field_10_resources_array.SetAt(25, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbemorphResID, TRUE, FALSE));
    field_10_resources_array.SetAt(26, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kShrmorphResID, TRUE, FALSE));
    field_10_resources_array.SetAt(27, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kSplineResID, TRUE, FALSE));
}

s16 Abe::ToLeftRightMovement_44E340()
{
    mVelY = FP_FromInteger(0);
    if (sControlledCharacter != this)
    {
        return 0;
    }

    const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
    const FP gridSize = ScaleToGridSize(mSpriteScale);
    const bool flipX = mAnim.mFlags.Get(AnimFlags::eBit5_FlipX);

    if ((flipX && (pressed & sInputKey_Right)) || (!flipX && (pressed & sInputKey_Left)))
    {
        mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_451830;
        return 1;
    }

    if ((pressed & sInputKey_Right) || (pressed & sInputKey_Left))
    {
        const FP directionX = FP_FromInteger((pressed & sInputKey_Right) ? 1 : -1);

        if (pressed & sInputKey_Run)
        {
            mVelX = directionX * (gridSize / FP_FromInteger(4));
            mCurrentMotion = eAbeMotions::Motion_39_StandingToRun_450D40;
        }
        else if (pressed & sInputKey_Sneak)
        {
            mVelX = directionX * (gridSize / FP_FromInteger(10));
            mCurrentMotion = eAbeMotions::Motion_45_SneakBegin_4507A0;
        }
        else
        {
            mVelX = directionX * (gridSize / FP_FromInteger(9));
            mCurrentMotion = eAbeMotions::Motion_6_WalkBegin_44FEE0;
        }

        if (!WallHit(mSpriteScale * FP_FromInteger(50), directionX * gridSize))
        {
            if (!WallHit(mSpriteScale * FP_FromInteger(20), directionX * gridSize))
            {
                return 1;
            }
        }

        // Walking into wall?
        if (WallHit(mSpriteScale * FP_FromInteger(20), directionX * gridSize))
        {
            PushWall_44E890();
            return 0;
        }

        mCurrentMotion = eAbeMotions::Motion_19_StandToCrouch_453DC0;
        return 1;
    }

    return 0;
}

void Abe::TryHoist_44ED30()
{
    mCurrentMotion = eAbeMotions::Motion_13_HoistBegin_452B20;

    const FP xpos = mXPos;
    const FP ypos = mYPos - FP_FromInteger(10); // Look up 10 for a hoist.

    relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(xpos),
        FP_GetExponent(ypos),
        FP_GetExponent(xpos),
        FP_GetExponent(ypos),
        ReliveTypes::eHoist));

    if (pHoist)
    {
        if (IsSameScaleAsHoist(pHoist, this))
        {
            if (!IsFacingSameDirectionAsHoist(pHoist, this) && pHoist->mGrabDirection != relive::Path_Hoist::GrabDirection::eFacingAnyDirection)
            {
                // No, so auto turn around to face it.
                mNextMotion = mCurrentMotion;
                mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_451830;
            }
        }

        BaseAliveGameObjectPathTLV = pHoist;
    }
}

void Abe::Create_Fart_421D20()
{
    relive_new EvilFart();
}

s16 Abe::TryEnterMineCar_4569E0()
{
    if (Input().mPads[sCurrentControllerIndex].mPressed & sInputKey_Up)
    {
        for (s32 idx = 0; idx < gBaseAliveGameObjects->Size(); idx++)
        {
            BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(idx);
            if (!pObj)
            {
                break;
            }

            if (pObj->mAnim.mFlags.Get(AnimFlags::eBit3_Render))
            {
                const PSX_RECT abeRect = VGetBoundingRect();
                const PSX_RECT mineCarRect = pObj->VGetBoundingRect();

                if (PSX_Rects_overlap_no_adjustment(&abeRect, &mineCarRect) && pObj->mSpriteScale == mSpriteScale && pObj->Type() == ReliveTypes::eMineCar)
                {
                    const FP distanceCheck = ScaleToGridSize(mSpriteScale) * FP_FromDouble(0.5);
                    if (mXPos - pObj->mXPos < distanceCheck)
                    {
                        if (pObj->mXPos - mXPos < distanceCheck)
                        {
                            field_120_state.raw = 0;
                            mCurrentMotion = eAbeMotions::Motion_116_MineCarEnter_458780;
                            mXPos = FP_FromInteger((mineCarRect.x + mineCarRect.w) / 2);
                            MapFollowMe(TRUE);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

s32 Abe::NearDoorIsOpen_44EE10()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->Type() == ReliveTypes::eDoor)
        {
            auto pDoor = static_cast<Door*>(pObj);
            if (FP_Abs(mXPos - pDoor->mXPos) < FP_FromInteger(15) && FP_Abs(mYPos - pDoor->mYPos) < FP_FromInteger(20))
            {
                return pDoor->vIsOpen();
            }
        }
    }
    // We didn't find a door - so for some reason that makes no sense return that it is open...
    return TRUE;
}

s16 Abe::HandleDoAction_455BD0()
{
    relive::Path_TLV* pTlv = sPathInfo->TlvGetAt(
        nullptr,
        mXPos,
        mYPos,
        mXPos,
        mYPos);

    if (!pTlv)
    {
        // Why ya trying to use nothing?
        return eAbeMotions::Motion_34_DunnoBegin_44ECF0;
    }

    for (;;)
    {
        switch (pTlv->mTlvType)
        {
            case ReliveTypes::eWellLocal:
                BaseAliveGameObjectPathTLV = pTlv;
                return eAbeMotions::Motion_78_WellBegin_45C810;

            case ReliveTypes::eLever:
            {
                FP xpos = {};
                FP ypos = {};
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    xpos = mYPos - FP_FromInteger(5);
                    ypos = mXPos - ScaleToGridSize(mSpriteScale);
                }
                else
                {
                    xpos = mYPos - FP_FromInteger(5);
                    ypos = ScaleToGridSize(mSpriteScale) + mXPos;
                }

                Lever* pSwitch = static_cast<Lever*>(FindObjectOfType(ReliveTypes::eLever, ypos, xpos));
                if (!pSwitch || !(pSwitch->VPull(mXPos < pSwitch->mXPos)))
                {
                    return eAbeMotions::Motion_34_DunnoBegin_44ECF0;
                }

                return eAbeMotions::Motion_99_LeverUse_455AC0;
            }

            case ReliveTypes::eWellExpress:
                BaseAliveGameObjectPathTLV = pTlv;
                return eAbeMotions::Motion_78_WellBegin_45C810;

            case ReliveTypes::eBoomMachine:
            {
                auto pGrenadeMachine = static_cast<BoomMachine*>(FindObjectOfType(ReliveTypes::eBoomMachine, mXPos, mYPos - (mSpriteScale * FP_FromInteger(25))));
                if (!pGrenadeMachine || !(pGrenadeMachine->VIsButtonOn()))
                {
                    return eAbeMotions::Motion_34_DunnoBegin_44ECF0;
                }
                pGrenadeMachine->VHandleButton();
                return eAbeMotions::Motion_88_GrenadeMachineUse_45C510;
            }

            default:
                // Next TLV, exit if we're at the end.
                pTlv = sPathInfo->TlvGetAt(
                    pTlv,
                    mXPos,
                    mYPos,
                    mXPos,
                    mYPos);

                if (!pTlv)
                {
                    return eAbeMotions::Motion_34_DunnoBegin_44ECF0;
                }
                continue;
        }
    }
}

void Abe::PushWall_44E890()
{
    mVelX = FP_FromInteger(0);
    mCurrentMotion = eAbeMotions::Motion_73_PushWall_4553A0;
    Environment_SFX_457A40(EnvironmentSfx::eGenericMovement_9, 0, 32767, this);
}

void Abe::MoveForward_44E9A0()
{
    const FP oldXPos = mXPos;
    if (BaseAliveGameObjectCollisionLine)
    {
        BaseAliveGameObjectCollisionLine = BaseAliveGameObjectCollisionLine->MoveOnLine(
            &mXPos,
            &mYPos,
            mVelX);
    }

    TrapDoor* pTrapdoor = static_cast<TrapDoor*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));
    if (BaseAliveGameObjectCollisionLine && (mScale == Scale::Fg ? kFgFloor : kBgFloor).Mask() == CollisionMask(BaseAliveGameObjectCollisionLine->mLineType).Mask())
    {
        // Handle trap door collision.
        if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 ||
            BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
        {
            if (pTrapdoor)
            {
                pTrapdoor->VRemove(this);
                BaseAliveGameObject_PlatformId = Guid{};
            }

            const PSX_RECT bRect = VGetBoundingRect();
            VOnCollisionWith(
                {bRect.x, static_cast<s16>(bRect.y + 5)},
                {static_cast<s16>(bRect.w + 5), 
                 static_cast<s16>(bRect.h + 5)}, // TODO: Is it really on both ??
                ObjList_5C1B78,
                (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
        }
        else if (pTrapdoor)
        {
            pTrapdoor->VRemove(this);
            BaseAliveGameObject_PlatformId = Guid{};
        }
    }
    else
    {
        BaseAliveGameObjectCollisionLine = 0;
        if (pTrapdoor)
        {
            pTrapdoor->VRemove(this);
            BaseAliveGameObject_PlatformId = Guid{};
        }

        mPrevHeld = 0;

        switch (mCurrentMotion)
        {
            case eAbeMotions::Motion_1_WalkLoop_44FBA0:
            case eAbeMotions::Motion_6_WalkBegin_44FEE0:
            case eAbeMotions::Motion_4_WalkToIdle_44FFC0:
            case eAbeMotions::Motion_5_MidWalkToIdle_450080:
                mCurrentMotion = eAbeMotions::Motion_93_WalkOffEdge_455970;
                break;

            case eAbeMotions::Motion_33_RunLoop_4508E0:
            case eAbeMotions::Motion_39_StandingToRun_450D40:
                mCurrentMotion = eAbeMotions::Motion_94_RunOffEdge_4559A0;
                break;

            case eAbeMotions::jMotion_38_RunToRoll_453A70:
            case eAbeMotions::Motion_22_RollBegin_4539A0:
            case eAbeMotions::Motion_23_RollLoop_453A90:
            case eAbeMotions::Motion_24_453D00:
                mCurrentMotion = eAbeMotions::Motion_98_RollOffEdge_455AA0;
                break;

            default:
                mCurrentMotion = eAbeMotions::Motion_95_SneakOffEdge_4559C0;
                break;
        }

        field_128.field_8_x_vel_slow_by = FP_FromDouble(0.3); // TODO: Check.
        mXPos = oldXPos + mVelX;
        BaseAliveGameObjectLastLineYPos = mYPos;

        // TODO: OG bug, dead code due to switch default case?
        if (mCurrentMotion == eAbeMotions::Motion_71_Knockback_455090 || mCurrentMotion == eAbeMotions::Motion_101_KnockForward_455420)
        {
            field_128.field_8_x_vel_slow_by = FP_FromDouble(0.67); // TODO: Check.
        }
    }
}

s16 Abe::CrouchingGameSpeak_453E10()
{
    mPrevHeld |= Input().mPads[sCurrentControllerIndex].mHeld;

    if (sInputKey_GameSpeak2 & mPrevHeld)
    {
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eFollowMe_10);
        Mudokon_SFX(MudSounds::eFollowMe_4, 0, 0, this);
        mCurrentMotion = eAbeMotions::Motion_20_CrouchSpeak_454550;
        return TRUE;
    }
    else if (sInputKey_GameSpeak3 & mPrevHeld)
    {
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eWait_12);
        Mudokon_SFX(MudSounds::eWait_6, 0, 0, this);
        mCurrentMotion = eAbeMotions::jMotion_21_ToCrouchSpeak_4545E0;
        return TRUE;
    }
    else if (mPrevHeld & sInputKey_GameSpeak1)
    {
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eHello_9);

        if (field_128.mMood == Mud_Emotion::eHappy_5 || field_128.mMood == Mud_Emotion::eWired_6)
        {
            Mudokon_SFX(MudSounds::eHiHappy_19, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_20_CrouchSpeak_454550;
        }
        else
        {
            if (field_128.mMood == Mud_Emotion::eSad_3)
            {
                Mudokon_SFX(MudSounds::eHiSad_20, 0, 0, this);
            }
            else
            {
                Mudokon_SFX(MudSounds::eHelloNeutral_3, 0, 0, this);
            }
            mCurrentMotion = eAbeMotions::Motion_20_CrouchSpeak_454550;
        }
        return TRUE;
    }
    else if (mPrevHeld & sInputKey_GameSpeak4)
    {
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eWork_21);
        Mudokon_SFX(MudSounds::eWork_25, 0, 0, this);
        mCurrentMotion = eAbeMotions::jMotion_21_ToCrouchSpeak_4545E0;
        return TRUE;
    }
    else if (mPrevHeld & sInputKey_GameSpeak6)
    {
        Mudokon_SFX(MudSounds::eAllOYa_17, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eAllYa_23);
        mCurrentMotion = eAbeMotions::jMotion_21_ToCrouchSpeak_4545E0;
        return TRUE;
    }
    else if (mPrevHeld & sInputKey_GameSpeak5)
    {
        Mudokon_SFX(MudSounds::eAnger_5, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eAnger_11);
        mCurrentMotion = eAbeMotions::Motion_20_CrouchSpeak_454550;
        return TRUE;
    }
    else if (mPrevHeld & sInputKey_GameSpeak8)
    {
        Mudokon_SFX(MudSounds::eStopIt_26, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eStopIt_22);
        mCurrentMotion = eAbeMotions::jMotion_21_ToCrouchSpeak_4545E0;
        return TRUE;
    }
    else if (mPrevHeld & sInputKey_GameSpeak7)
    {
        Mudokon_SFX(MudSounds::eSadUgh_28, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eSorry_24);
        mCurrentMotion = eAbeMotions::Motion_20_CrouchSpeak_454550;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool Abe::Is_Celling_Above_44E8D0()
{
    FP hitY = {};
    FP hitX = {};
    PathLine* pLine = nullptr;
    return sCollisions->Raycast(
               mXPos,
               mYPos - FP_FromInteger(5),
               mXPos,
               mYPos - (mSpriteScale * FP_FromInteger(45)),
               &pLine,
               &hitX,
               &hitY,
               mScale == Scale::Fg ? kFgCeiling : kBgCeiling)
        != 0;
}

void Abe::MoveWithVelocity_450FA0(FP velocityX)
{
    if (mVelX > FP_FromInteger(0))
    {
        const FP newVelX = mVelX - (mSpriteScale * velocityX);
        mVelX = newVelX;
        if (newVelX < FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }
    else if (mVelX < FP_FromInteger(0))
    {
        const FP newVelX = (mSpriteScale * velocityX) + mVelX;
        mVelX = newVelX;
        if (newVelX > FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }

    if (FP_GetExponent(mVelX))
    {
        MoveForward_44E9A0();
    }
}

s16 Abe::RunTryEnterDoor_451220()
{
    // Can't be entering a door if we're not pressing up.
    if (!Input().isPressed(sInputKey_Up))
    {
        return 0;
    }

    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted))
    {
        return 0;
    }

    if (mAnim.mCurrentFrame < 4)
    {
        return 0;
    }

    // Are we actually on a door?
    relive::Path_TLV* pDoorTlv = sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eDoor);

    if (!pDoorTlv)
    {
        return 0;
    }

    if (!NearDoorIsOpen_44EE10())
    {
        return 0;
    }

    BaseAliveGameObjectPathTLV = pDoorTlv;
    field_120_state.raw = 0;
    mCurrentMotion = eAbeMotions::Motion_114_DoorEnter_459470;
    mXPos = FP_FromInteger((pDoorTlv->mTopLeftX + pDoorTlv->mBottomRightX) / 2);
    MapFollowMe(TRUE);
    return 1;
}

s16 Abe::RunTryEnterWell_451060()
{
    if (!Input().isPressed(sInputKey_Up) || mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted) || mAnim.mCurrentFrame < 4)
    {
        return 0;
    }

    auto pWellLocal = static_cast<relive::Path_WellLocal*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellLocal));
    if (pWellLocal)
    {
        if (!(mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting)))
        {
            if ((pWellLocal->mScale == relive::reliveScale::eFull && mSpriteScale == FP_FromInteger(1)) || (pWellLocal->mScale == relive::reliveScale::eHalf && mSpriteScale == FP_FromDouble(0.5)))
            {
                field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3_WalkToRun);
                BaseAliveGameObjectPathTLV = pWellLocal;
                mCurrentMotion = eAbeMotions::Motion_78_WellBegin_45C810;
                return 1;
            }
        }
    }

    auto pWellExpress = static_cast<relive::Path_WellExpress*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellExpress));
    if (pWellExpress)
    {
        if (!(mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting)))
        {
            if ((pWellExpress->mScale == relive::reliveScale::eFull && mSpriteScale == FP_FromInteger(1)) || (pWellExpress->mScale == relive::reliveScale::eHalf && mSpriteScale == FP_FromDouble(0.5)))
            {
                field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3_WalkToRun);
                BaseAliveGameObjectPathTLV = pWellExpress;
                mCurrentMotion = eAbeMotions::jMotion_81_WellBegin_45C7F0;
                return 1;
            }
        }
    }

    return 0;
}

void Abe::ToDieFinal_458910()
{
    InvisibleEffect* pInvisibleEffect = static_cast<InvisibleEffect*>(sObjectIds.Find_Impl(mInvisibleEffectId));
    if (pInvisibleEffect)
    {
        if (!(pInvisibleEffect->mBaseGameObjectFlags.Get(BaseGameObject::eDead)))
        {
            pInvisibleEffect->ClearInvisibility();
            mInvisibleEffectId = Guid{};
        }
    }

    field_1AC_flags.Set(Flags_1AC::e1AC_Bit5_shrivel);
    mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
    mCurrentMotion = eAbeMotions::Motion_57_Dead_4589A0;
    field_124_timer = 0;
    mHealth = FP_FromInteger(0);

    MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_11, this, 1, 0);
}

s16 Abe::DoGameSpeak_45AB70(s32 input)
{
    s16 nextMotion = -1;
    if (Input_IsChanting_45F260())
    {
        // Fixes an OG bug where Abe doesn't transform into Shrykull when you immediately chant after using GameSpeak.
        if (!(mRingPulseTimer && mHaveShrykull))
        {
            field_124_timer = sGnFrame + 90;
            SND_SEQ_PlaySeq(SeqId::MudokonChant1_10, 0, 1);
            field_120_state.chant = ChantStates::eIdleChanting_0;
            nextMotion = eAbeMotions::Motion_112_Chant_45B1C0;
        }
    }
    else if (input & sInputKey_GameSpeak2)
    {
        Mudokon_SFX(MudSounds::eFollowMe_4, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eFollowMe_10);
        nextMotion = eAbeMotions::Motion_7_Speak_45B140;
    }
    else if (input & sInputKey_GameSpeak3)
    {
        Mudokon_SFX(MudSounds::eWait_6, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eWait_12);
        nextMotion = eAbeMotions::Motion_8_Speak_45B160;
    }
    else if (input & sInputKey_GameSpeak1)
    {
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eHello_9);
        if (field_128.mMood == Mud_Emotion::eHappy_5 || field_128.mMood == Mud_Emotion::eWired_6)
        {
            Mudokon_SFX(MudSounds::eHiHappy_19, 0, 0, this);
            nextMotion = eAbeMotions::Motion_9_Speak_45B180;
        }
        else
        {
            if (field_128.mMood == Mud_Emotion::eSad_3)
            {
                Mudokon_SFX(MudSounds::eHiSad_20, 0, 0, this);
            }
            else
            {
                Mudokon_SFX(MudSounds::eHelloNeutral_3, 0, 0, this);
            }
            nextMotion = eAbeMotions::Motion_9_Speak_45B180;
        }
    }
    else if (input & sInputKey_GameSpeak4)
    {
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eWork_21);
        Mudokon_SFX(MudSounds::eWork_25, 0, 0, this);
        nextMotion = eAbeMotions::Motion_10_Fart_45B1A0;
    }
    else if (input & sInputKey_GameSpeak6)
    {
        Mudokon_SFX(MudSounds::eAllOYa_17, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eAllYa_23);
        nextMotion = eAbeMotions::Motion_9_Speak_45B180;
    }
    else if (input & sInputKey_GameSpeak5)
    {
        FP gridSize = {};
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            gridSize = -ScaleToGridSize(mSpriteScale);
        }
        else
        {
            gridSize = ScaleToGridSize(mSpriteScale);
        }

        if (FindObjectOfType(ReliveTypes::eMudokon, mXPos + gridSize, mYPos - FP_FromInteger(5)))
        {
            nextMotion = eAbeMotions::Motion_62_Punch_454750;
        }
        else if (FindObjectOfType(ReliveTypes::eMudokon, mXPos + (gridSize * FP_FromInteger(2)), mYPos - FP_FromInteger(5)))
        {
            nextMotion = eAbeMotions::Motion_62_Punch_454750;
        }
        else
        {
            // NOTE: Extra check for locks, it must also be being rendered in order to for us to try to hit it.
            BaseAnimatedWithPhysicsGameObject* pLockedSoul = static_cast<BaseAliveGameObject*>(FindObjectOfType(ReliveTypes::eLockedSoul, mXPos + gridSize, mYPos - (FP_FromInteger(30) * mSpriteScale)));
            if (pLockedSoul && pLockedSoul->mAnim.mFlags.Get(AnimFlags::eBit3_Render))
            {
                nextMotion = eAbeMotions::Motion_62_Punch_454750;
            }
            else if (FindObjectOfType(ReliveTypes::eSlig, mXPos + gridSize, mYPos - FP_FromInteger(5)))
            {
                nextMotion = eAbeMotions::Motion_62_Punch_454750;
            }
            else if (FindObjectOfType(ReliveTypes::eSlig, mXPos + (gridSize * FP_FromInteger(2)), mYPos - FP_FromInteger(5)))
            {
                nextMotion = eAbeMotions::Motion_62_Punch_454750;
            }
            else if (FindObjectOfType(ReliveTypes::eGlukkon, mXPos + gridSize, mYPos - FP_FromInteger(5)))
            {
                nextMotion = eAbeMotions::Motion_62_Punch_454750;
            }
            else if (FindObjectOfType(ReliveTypes::eGlukkon, mXPos + (gridSize * FP_FromInteger(2)), mYPos - FP_FromInteger(5)))
            {
                nextMotion = eAbeMotions::Motion_62_Punch_454750;
            }
            else
            {
                // Didn't hit anything, just anger.
                Mudokon_SFX(MudSounds::eAnger_5, 0, 0, this);
                pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eAnger_11);
                nextMotion = eAbeMotions::Motion_8_Speak_45B160;
            }
        }
    }
    else if (input & sInputKey_GameSpeak8)
    {
        Mudokon_SFX(MudSounds::eStopIt_26, 0, 0, this);
        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eStopIt_22);
        nextMotion = eAbeMotions::Motion_7_Speak_45B140;
    }
    else if (input & sInputKey_GameSpeak7)
    {
        FP gridSize = {};
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            gridSize = -ScaleToGridSize(mSpriteScale);
        }
        else
        {
            gridSize = ScaleToGridSize(mSpriteScale);
        }

        pEventSystem_5BC11C->PushEvent(GameSpeakEvents::eSorry_24);
        if (FindObjectOfType(ReliveTypes::eMudokon, mXPos + gridSize, mYPos - (mSpriteScale * FP_FromInteger(40))))
        {
            nextMotion = eAbeMotions::Motion_63_Sorry_454670;
        }
        else
        {
            Mudokon_SFX(MudSounds::eSadUgh_28, 0, 0, this);
            nextMotion = eAbeMotions::Motion_10_Fart_45B1A0; // TODO: Correct but isn't fart in this case ??
        }
    }

    return nextMotion;
}

s16 Abe::CantBeDamaged_44BAB0()
{
    switch (mCurrentMotion)
    {
        case eAbeMotions::Motion_75_JumpIntoWell_45C7B0:
        case eAbeMotions::Motion_76_ToInsideOfAWellLocal_45CA40:
        case eAbeMotions::Motion_77_ToWellShotOut_45D130:
        case eAbeMotions::Motion_78_WellBegin_45C810:
        case eAbeMotions::Motion_79_InsideWellLocal_45CA60:
        case eAbeMotions::Motion_80_WellShotOut_45D150:
        case eAbeMotions::jMotion_81_WellBegin_45C7F0:
        case eAbeMotions::Motion_82_InsideWellExpress_45CC80:
        case eAbeMotions::Motion_83_WellExpressShotOut_45CF70:
        case eAbeMotions::Motion_114_DoorEnter_459470:
        case eAbeMotions::Motion_115_DoorExit_459A40:
        case eAbeMotions::Motion_119_ToShrykull_45A990:
        case eAbeMotions::Motion_120_EndShrykull_45AB00:
            return TRUE;
    }

    // TODO: Unknown what this is checking, condition should probably be inverted.
    if ((!(field_1AC_flags.Get(Flags_1AC::e1AC_Bit5_shrivel)) && mAnim.mFlags.Get(AnimFlags::eBit3_Render)) || mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void Abe::FallOnBombs_44EC10()
{
    const PSX_RECT bOurRect = VGetBoundingRect();
    for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
    {
        BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->Type() == ReliveTypes::eMine || pObj->Type() == ReliveTypes::eUXB)
        {
            const PSX_RECT objRect = pObj->VGetBoundingRect();
            if (bOurRect.x <= objRect.w && bOurRect.w >= objRect.x && bOurRect.h >= objRect.y && bOurRect.y <= objRect.h)
            {
                pObj->VTakeDamage(this);
            }
        }
    }
}

s16 Abe::ForceDownIfHoisting_44BA30()
{
    if (mCurrentMotion != eAbeMotions::Motion_65_LedgeAscend_4548E0 && mCurrentMotion != eAbeMotions::Motion_67_LedgeHang_454E20 && mCurrentMotion != eAbeMotions::Motion_69_LedgeHangWobble_454EF0 && mCurrentMotion != eAbeMotions::Motion_66_LedgeDescend_454970 && mCurrentMotion != eAbeMotions::Motion_68_ToOffScreenHoist_454B80)
    {
        return 0;
    }

    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_455800;

    field_124_timer = 0;

    mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);

    return 1;
}

void Abe::BulletDamage_44C980(Bullet* pBullet)
{
    const PSX_RECT rect = VGetBoundingRect();

    enum class ShootKind
    {
        eEverythingElse_0 = 0,
        eHanging_1 = 1,
        eRolling_2 = 2,
    };

    if (Is_In_Current_Camera() != CameraPos::eCamCurrent_0 || mHealth <= FP_FromInteger(0))
    {
        return;
    }

    ShootKind shootKind = ShootKind::eEverythingElse_0;
    if (mCurrentMotion == eAbeMotions::Motion_22_RollBegin_4539A0 || mCurrentMotion == eAbeMotions::Motion_23_RollLoop_453A90 || mCurrentMotion == eAbeMotions::Motion_24_453D00 || mCurrentMotion == eAbeMotions::Motion_37_CrouchTurn_454390 || mCurrentMotion == eAbeMotions::Motion_17_CrouchIdle_456BC0)
    {
        shootKind = ShootKind::eRolling_2;
    }
    else if (mCurrentMotion == eAbeMotions::Motion_65_LedgeAscend_4548E0 || mCurrentMotion == eAbeMotions::Motion_67_LedgeHang_454E20 || mCurrentMotion == eAbeMotions::Motion_69_LedgeHangWobble_454EF0 || mCurrentMotion == eAbeMotions::Motion_66_LedgeDescend_454970 || mCurrentMotion == eAbeMotions::Motion_68_ToOffScreenHoist_454B80)
    {
        shootKind = ShootKind::eHanging_1;
    }

    mHealth -= FP_FromDouble(0.34);
    if (mHealth > FP_FromInteger(0))
    {
        FP xOffset = {};
        if (mHealth <= FP_FromDouble(0.5))
        {
            if (pBullet->mXDistance > FP_FromInteger(0))
            {
                xOffset = mXPos - ScaleToGridSize(mSpriteScale);
            }
            else
            {
                xOffset = ScaleToGridSize(mSpriteScale) + mXPos;
            }
        }
        else
        {
            if (pBullet->mXDistance > FP_FromInteger(0))
            {
                xOffset = mXPos - (ScaleToGridSize(mSpriteScale) * FP_FromInteger(2));
            }
            else
            {
                xOffset = mXPos + (ScaleToGridSize(mSpriteScale) * FP_FromInteger(2));
            }
        }

        PathLine* pathLine = nullptr;
        FP hitX = {};
        FP hitY = {};
        if (sCollisions->Raycast(
                xOffset,
                mYPos - FP_FromInteger(5),
                xOffset,
                mYPos + FP_FromInteger(5),
                &pathLine,
                &hitX,
                &hitY,
                mScale == Scale::Fg ? kFgFloor : kBgFloor)
            == 1)
        {
            if (pBullet->mBulletType != BulletType::ePossessedSligZBullet_1 && pBullet->mBulletType != BulletType::eZBullet_3)
            {
                relive_new Spark(hitX, hitY, mSpriteScale, 9, -31, 159, SparkType::eSmallChantParticle_0);
                New_Smoke_Particles(hitX, hitY, mSpriteScale, 3, 128u, 128u, 128u);
            }
        }
        return;
    }

    mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit1_bShot);

    switch (pBullet->mBulletType)
    {
        case BulletType::eSligPossessedOrUnderGlukkonCommand_0:
        case BulletType::eNormalBullet_2:
        {
            FP bloodXOffset = {};
            if (pBullet->mXDistance <= FP_FromInteger(0))
            {
                bloodXOffset = FP_FromInteger(-24);
            }
            else
            {
                bloodXOffset = FP_FromInteger(24);
            }
            
            relive_new Blood(
                mXPos,
                pBullet->mYPos,
                bloodXOffset,
                FP_FromInteger(0),
                mSpriteScale,
                50);

            switch (shootKind)
            {
                case ShootKind::eEverythingElse_0:
                {
                    ToKnockback_44E700(1, 1);
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != (pBullet->mXDistance > FP_FromInteger(0)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_101_KnockForward_455420;
                    }
                    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                    mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
                    mVelX = mSpriteScale * FP_FromDouble(7.8);
                    if (pBullet->mXDistance < FP_FromInteger(0))
                    {
                        mVelX = -mSpriteScale;
                    }
                    break;
                }
                case ShootKind::eHanging_1:
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_455800;
                    field_124_timer = 0;
                    mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
                    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                    break;
                }
                case ShootKind::eRolling_2:
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) == (pBullet->mXDistance > FP_FromInteger(0)))
                    {
                        mNextMotion = eAbeMotions::Motion_74_RollingKnockback_455290;
                    }
                    else
                    {
                        mNextMotion = eAbeMotions::Motion_102_RollingKnockForward_455310;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }

        case BulletType::ePossessedSligZBullet_1:
        case BulletType::eZBullet_3:
        {
            if (mSpriteScale == FP_FromDouble(0.5))
            {
                mHealth = FP_FromInteger(1);
                mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
                return;
            }

            const FP boundsY = FP_FromInteger(rect.y);
            if (Bullet::InZBulletCover(mXPos, boundsY, rect) || !gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, boundsY, 0))
            {
                mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
                mHealth = FP_FromInteger(1);
                return;
            }

            FP yOffset = {};
            if (shootKind == ShootKind::eEverythingElse_0)
            {
                yOffset = (FP_FromInteger(-45) * mSpriteScale);
                mNextMotion = eAbeMotions::Motion_110_ZShot_455670;
            }
            else if (shootKind == ShootKind::eHanging_1)
            {
                yOffset = (FP_FromInteger(45) * mSpriteScale);
                mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_455800;
                mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit1_bShot);
                mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);
                field_124_timer = 0;
            }
            else if (shootKind == ShootKind::eRolling_2)
            {
                yOffset = (FP_FromInteger(-25) * mSpriteScale);
                mNextMotion = eAbeMotions::Motion_109_ZShotRolling_455550;
            }

            relive_new Blood(mXPos, yOffset + mYPos, FP_FromInteger(0), FP_FromInteger(0), FP_FromInteger(1), 50);
            break;
        }

        default:
            break;
    }

    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit1_bShot))
    {
        mKnockdownMotion = mNextMotion;
    }

    Environment_SFX_457A40(EnvironmentSfx::eElumHitWall_14, 0, 32767, this);
    Mudokon_SFX(MudSounds::eHurt2_9, 127, 0, this);
    Environment_SFX_457A40(EnvironmentSfx::eDeathNoise_7, 0, 32767, this);
    SFX_Play_Pitch(relive::SoundEffects::Eating1, 0, -500, mSpriteScale);
    SfxPlayMono(relive::SoundEffects::KillEffect, 0, mSpriteScale);
}

void Abe::GiveControlBackToMe_44BA10()
{
    sControlledCharacter = this;
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit6_prevent_chanting);
}

PullRingRope* Abe::GetPullRope_44D120()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        // Find a rope.
        if (pObj->Type() == ReliveTypes::ePullRingRope)
        {
            // Is it on the same scale as us?
            PullRingRope* pRope = static_cast<PullRingRope*>(pObj);
            if (pRope->mSpriteScale == mSpriteScale)
            {
                const PSX_RECT bRect = pRope->VGetBoundingRect();

                // Check we are near its ypos.
                if ((mYPos - (mSpriteScale * FP_FromInteger(75))) <= pRope->mYPos && mYPos > pRope->mYPos)
                {
                    // Check we are near its xpos.
                    if (mXPos > FP_FromInteger(bRect.x) && mXPos < FP_FromInteger(bRect.w))
                    {
                        // Found a rope we can pull.
                        return pRope;
                    }
                }
            }
        }
    }
    return nullptr;
}

void Abe::IntoPortalStates_451990()
{
    auto pBirdPortal = static_cast<BirdPortal*>(sObjectIds.Find_Impl(mBirdPortalId));
    if (pBirdPortal)
    {
        PSX_RECT bRect = {};
        switch (mBirdPortalSubState)
        {
            case PortalSubStates::eJumpingInsidePortal_0:
                bRect = VGetBoundingRect();
                if ((mVelX > FP_FromInteger(0) && FP_FromInteger(bRect.x) > pBirdPortal->mXPos) || (mVelX < FP_FromInteger(0) && FP_FromInteger(bRect.w) < pBirdPortal->mXPos))
                {
                    mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                    mVelY = FP_FromInteger(0);
                    mVelX = FP_FromInteger(0);
                    pBirdPortal->VKillPortalClipper();
                    pBirdPortal->VGiveShrykull(TRUE);
                    mBirdPortalSubState = PortalSubStates::eSetNewActiveCamera_1;
                }

                mVelY += mSpriteScale * FP_FromDouble(1.8);
                mXPos += mVelX;
                mYPos += mVelY;
                return;

            case PortalSubStates::eSetNewActiveCamera_1:
                if (pBirdPortal->VAbeInsidePortal())
                {
                    EReliveLevelIds level = {};
                    u16 path = 0;
                    u16 camera = 0;
                    CameraSwapEffects screenChangeEffect = {};
                    u16 movieId = 0;

                    pBirdPortal->VGetMapChange(&level, &path, &camera, &screenChangeEffect, &movieId);
                    gMap.SetActiveCam(level, path, camera, screenChangeEffect, movieId, FALSE);
                    mBirdPortalSubState = PortalSubStates::eSetNewAbePosition_4;
                }
                break;

            case PortalSubStates::eHopOutOfPortal_2:
                if (pBirdPortal->VPortalExit_AbeExitting())
                {
                    pBirdPortal->VPortalClipper(0);
                    mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                    mCurrentMotion = eAbeMotions::Motion_27_HopBegin_4521C0;
                    pBirdPortal->VIncreaseTimerAndKillPortalClipper();
                    mBirdPortalId = Guid{};
                }
                break;

            case PortalSubStates::eSetNewAbePosition_4:
                pBirdPortal->VExitPortal();
                mBirdPortalSubState = PortalSubStates::eHopOutOfPortal_2;

                mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pBirdPortal->mEnterSide == relive::Path_BirdPortal::PortalSide::eLeft);

                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mXPos = ScaleToGridSize(mSpriteScale) + pBirdPortal->mExitX;
                }
                else
                {
                    mXPos = pBirdPortal->mExitX - ScaleToGridSize(mSpriteScale);
                }
                mYPos = pBirdPortal->mExitY;
                BaseAliveGameObjectLastLineYPos = pBirdPortal->mExitY;
                mVelY = FP_FromInteger(0);
                field_128.field_8_x_vel_slow_by = FP_FromInteger(0);
                break;

            default:
                return;
        }
    }
}

void Abe::Calc_Well_Velocity_45C530(s16 xPosSource, s16 yPosSource, s16 xPosDest, s16 yPosDest)
{
    PSX_Point abeSpawnPos = {};
    gMap.Get_Abe_Spawn_Pos(&abeSpawnPos);

    const FP gravity = mSpriteScale == FP_FromInteger(1) ? FP_FromDouble(1.8) : FP_FromDouble(0.9);
    const FP xPosDistance = FP_FromInteger(xPosDest - xPosSource);
    FP yPosRealDistance = {};
    if (yPosDest > 0)
    {
        const s32 yPosSourceFull = abeSpawnPos.y + yPosSource;
        if (yPosDest > yPosSourceFull)
        {
            const FP yPosDistance = FP_FromInteger(yPosDest - yPosSourceFull);
            FP yPosDistanceOffset = {};
            if (yPosDistance <= (FP_FromInteger(41) * mSpriteScale))
            {
                yPosDistanceOffset = FP_FromInteger(0);
            }
            else
            {
                yPosDistanceOffset = yPosDistance - (FP_FromInteger(41) * mSpriteScale);
            }

            const FP spriteScaleFactor = FP_FromInteger(20) * mSpriteScale;
            FP yPosDistanceCalc = (yPosDistanceOffset / spriteScaleFactor) + FP_FromDouble(20.01);
            if (xPosDest > 0)
            {
                mVelX = (xPosDistance - FP_FromInteger(abeSpawnPos.x)) / yPosDistanceCalc;
            }
            else
            {
                mVelX = FP_FromDouble(2.796) * mSpriteScale;
            }
            mVelY = FP_FromDouble(-16.1) * mSpriteScale;
            return;
        }

        const s32 yPosFullDistanceInverse = yPosSourceFull - yPosDest;
        if (yPosFullDistanceInverse >= 0)
        {
            yPosRealDistance = FP_FromInteger(yPosFullDistanceInverse);
        }
        else
        {
            yPosRealDistance = FP_FromInteger(yPosDest - yPosSourceFull);
        }
    }
    else
    {
        yPosRealDistance = FP_FromInteger(0);
    }

    const FP yPosRealDistanceFull = (FP_FromInteger(80) * mSpriteScale) + yPosRealDistance;
    const FP gravityFactor = FP_FromInteger(8) * gravity;
    const FP gravityCalc = Math_SquareRoot_FP_Wrapper(((gravityFactor * yPosRealDistanceFull) + (gravity * gravity)));
    mVelY = (gravityCalc - gravity) * FP_FromDouble(0.5);

    const FP yVelocityAfterGravity = mVelY / gravity;
    mVelY = -mVelY;

    if (xPosDest > 0)
    {
        mVelX = (xPosDistance - FP_FromInteger(abeSpawnPos.x)) / (yVelocityAfterGravity + FP_FromDouble(8.9));
    }
    else
    {
        mVelX = FP_FromDouble(2.796) * mSpriteScale;
    }
}

void Abe::FollowLift_45A500()
{
    LiftPoint* pLift = static_cast<LiftPoint*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));
    if (pLift)
    {
        mVelY = pLift->mVelY;
        if (pLift->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
        {
            VOnTrapDoorOpen();
            field_1AC_flags.Set(Flags_1AC::e1AC_Bit1_lift_point_dead_while_using_lift);
        }
        SetActiveCameraDelayedFromDir();
    }
}

s16 Abe::MoveLiftUpOrDown_45A7E0(FP yVelocity)
{
    LiftPoint* pLiftPoint = static_cast<LiftPoint*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));
    if (!pLiftPoint)
    {
        return eAbeMotions::Motion_123_LiftGrabIdle_45A6A0;
    }

    pLiftPoint->vMove_4626A0(FP_FromInteger(0), yVelocity, 0);
    FollowLift_45A500();

    if (sControlledCharacter == this && !(mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame)) && mAnim.mCurrentFrame != 5)
    {
        return mCurrentMotion;
    }

    if (yVelocity >= FP_FromInteger(0))
    {
        if (yVelocity > FP_FromInteger(0))
        {
            if (pLiftPoint->vOnBottomFloor())
            {
                return eAbeMotions::Motion_123_LiftGrabIdle_45A6A0;
            }

            const u32 pressed = Input().mPads[sCurrentControllerIndex].mPressed;
            if (sInputKey_Down & pressed)
            {
                return eAbeMotions::Motion_125_LiftUseDown_45A7B0;
            }

            if (pressed & sInputKey_Up)
            {
                return eAbeMotions::Motion_124_LiftUseUp_45A780;
            }
        }
    }
    else
    {
        if (pLiftPoint->vOnTopFloor())
        {
            return eAbeMotions::Motion_123_LiftGrabIdle_45A6A0;
        }

        if (Input().isPressed(sInputKey_Up))
        {
            return eAbeMotions::Motion_124_LiftUseUp_45A780;
        }

        if (Input().isPressed(sInputKey_Down))
        {
            return eAbeMotions::Motion_125_LiftUseDown_45A7B0;
        }
    }

    if (Input().mPads[sCurrentControllerIndex].mPressed && pLiftPoint->vOnAnyFloor() && !(pLiftPoint->field_12C_bMoving & 1))
    {
        return eAbeMotions::Motion_122_LiftGrabEnd_45A670;
    }

    pLiftPoint->vMove_4626A0(FP_FromInteger(0), FP_FromInteger(0), 0);
    return eAbeMotions::Motion_123_LiftGrabIdle_45A6A0;
}

s16 Abe::GetEvilFart_4585F0(s16 bDontLoad)
{
    const PSX_RECT abeRect = VGetBoundingRect();

    BrewMachine* pBrewMachine = nullptr;
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            return 0;
        }

        if (pObj->Type() == ReliveTypes::eBrewMachine)
        {
            pBrewMachine = static_cast<BrewMachine*>(pObj);

            const PSX_RECT bRect = pBrewMachine->VGetBoundingRect();

            if (RectsOverlap(abeRect, bRect) && pBrewMachine->mSpriteScale == mSpriteScale && pBrewMachine->mTotalBrewCount > 0 && mHasEvilFart == FALSE)
            {
                break;
            }

            pBrewMachine = nullptr;
        }
    }

    if (!pBrewMachine)
    {
        return 0;
    }

    if (!bDontLoad)
    {
        return 1;
    }

    field_10_resources_array.SetAt(22, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kEvilFartResID, TRUE, FALSE));
    field_10_resources_array.SetAt(23, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kAbeblowResID, TRUE, FALSE));
    field_10_resources_array.SetAt(24, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kExplo2ResID, TRUE, FALSE));
    pBrewMachine->mTotalBrewCount--;
    mHasEvilFart = TRUE;

    return 1;
}

void Abe::ChangeChantState_45BB90(s16 bLaughAtChantEnd)
{
    if (bLaughAtChantEnd)
    {
        field_1AC_flags.Set(Flags_1AC::e1AC_Bit9_laugh_at_chant_end);
        field_120_state.chant = ChantStates::eChantingForBirdPortal_6; // Holds chant, then laughs.
    }
    else if (sControlledCharacter == this)
    {
        field_120_state.chant = ChantStates::eIdleChanting_0; // Chants briefly, then stops.
    }
    else
    {
        field_120_state.chant = ChantStates::eWaitForUnpossessing_3; // Chants briefly with a possession flicker, then stops.
    }
}

void Abe::SetAsDead_459430()
{
    field_120_state.raw = 1;
}

void Abe::ExitShrykull_45A9D0(s16 bResetRingTimer)
{
    mAnim.mFlags.Set(AnimFlags::eBit2_Animate);
    mAnim.mFlags.Set(AnimFlags::eBit3_Render);

    mBaseAliveGameObjectFlags.Set(Flags_114::e114_MotionChanged_Bit2);

    mCurrentMotion = eAbeMotions::Motion_120_EndShrykull_45AB00;
    field_124_timer = 1;

    if (bResetRingTimer)
    {
        mRingPulseTimer = 0;
    }
}

static void playAbeSFX(MudSounds idx, s16 volume, s32 pitch)
{
    SFX_SfxDefinition_Play_Mono(
        sAbeSFXList_555250[static_cast<u8>(idx)],
        volume,
        static_cast<s16>(pitch), static_cast<s16>(pitch));
}

void Mudokon_SFX(MudSounds idx, s16 volume, s32 pitch, BaseAliveGameObject* pHero)
{
    switch (idx)
    {
        case MudSounds::eOops_14:
        {
            if (pHero && pHero->mSpriteScale == FP_FromDouble(0.5))
            {
                SND_SEQ_Play(SeqId::AbeOops_16, 1, 90, 90);
            }
            else
            {
                SND_SEQ_Play(SeqId::AbeOops_16, 1, 127, 127);
            }
            break;
        }
        case MudSounds::eStopIt_26:
        {
            if (pHero && pHero->mSpriteScale == FP_FromDouble(0.5))
            {
                SND_SEQ_Play(SeqId::AbeStopIt_18, 1, 80, 80);
            }
            else
            {
                SND_SEQ_Play(SeqId::AbeStopIt_18, 1, 115, 115);
            }
            break;
        }
        case MudSounds::eGiggle_8:
        {
            if (IsActiveHero(pHero) && gMap.mCurrentLevel == EReliveLevelIds::eBrewery_Ender)
            {
                idx = MudSounds::eLaugh_10;
            }

            [[fallthrough]];
        }
        default:
        {
            auto idxToVal = static_cast<u8>(idx);
            if (!volume)
            {
                volume = sAbeSFXList_555250[idxToVal].field_C_default_volume;
            }

            // OG bug - isn't null checked in other cases before de-ref?
            if (!pHero)
            {
                playAbeSFX(idx, volume, pitch);
                return;
            }

            if (pHero->mSpriteScale == FP_FromDouble(0.5))
            {
                volume = 2 * volume / 3;
            }

            if (IsActiveHero(pHero))
            {
                playAbeSFX(idx, volume, pitch);
                return;
            }

            switch (gMap.GetDirection(
                pHero->mCurrentLevel,
                pHero->mCurrentPath,
                pHero->mXPos,
                pHero->mYPos))
            {
                case CameraPos::eCamCurrent_0:
                {
                    playAbeSFX(idx, volume, pitch);
                    break;
                }
                case CameraPos::eCamTop_1:
                case CameraPos::eCamBottom_2:
                {
                    playAbeSFX(idx, 2 * volume / 3, pitch);
                    break;
                }
                case CameraPos::eCamLeft_3:
                {
                    SFX_SfxDefinition_Play_Stereo(
                        sAbeSFXList_555250[idxToVal],
                        2 * volume / 3,
                        2 * volume / 9,
                        static_cast<s16>(pitch), static_cast<s16>(pitch));
                    break;
                }
                case CameraPos::eCamRight_4:
                {
                    SFX_SfxDefinition_Play_Stereo(
                        sAbeSFXList_555250[idxToVal],
                        2 * volume / 9,
                        2 * volume / 3,
                        static_cast<s16>(pitch), static_cast<s16>(pitch));
                    break;
                }
                default:
                    break;
            }
        }
    }
}
