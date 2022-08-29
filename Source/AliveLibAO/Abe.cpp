#include "stdafx_ao.h"
#include "Function.hpp"
#include "Abe.hpp"
#include "BellSong.hpp"
#include "Blood.hpp"
#include "BoomMachine.hpp"
#include "Bullet.hpp"
#include "CheatController.hpp"
#include "HoistRocksEffect.hpp"
#include "DeathBirdParticle.hpp"
#include "DemoPlayback.hpp"
#include "Door.hpp"
#include "Dove.hpp"
#include "ThrowableArray.hpp"
#include "Elum.hpp"
#include "Flash.hpp"
#include "LiftPoint.hpp"
#include "ResourceManager.hpp"
#include "../relive_lib/Shadow.hpp"
#include "Game.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "Midi.hpp"
#include "Movie.hpp"
#include "CircularFade.hpp"
#include "DeathFadeOut.hpp"
#include "Throwable.hpp"
#include "OrbWhirlWind.hpp"
#include "Particle.hpp"
#include "PossessionFlicker.hpp"
#include "PullRingRope.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "ThrowableTotalIndicator.hpp"
#include "../relive_lib/Events.hpp"
#include "DDCheat.hpp"
#include "LiftPoint.hpp"
#include "Well.hpp"
#include "Input.hpp"
#include "PullRingRope.hpp"
#include "ScreenShake.hpp"
#include "Sfx.hpp"
#include "MusicController.hpp"
#include "AbilityRing.hpp"
#include "MusicTrigger.hpp"
#include "Math.hpp"
#include "Input.hpp"
#include "Grenade.hpp"
#include "../relive_lib/Collisions.hpp"
#include "BirdPortal.hpp"
#include "Rope.hpp"
#include "SaveGame.hpp"
#include "BeeSwarm.hpp"
#include "Shrykull.hpp"
#include "Lever.hpp"
#include "GameSpeak.hpp"
#include "ZBall.hpp"
#include "Gibs.hpp"
#include "Camera.hpp"
#include "Sys_common.hpp"
#include "AnimationCallBacks.hpp"

#include "TestAnimation.hpp"

namespace AO {

ALIVE_VAR(1, 0x5076E4, s16, gAbeInvulnerableCheat_5076E4, 0);
ALIVE_VAR(1, 0x5076F8, s16, gAbeInvisibleCheat_5076F8, 0);

ALIVE_VAR_EXTERN(SaveData, gSaveBuffer_505668);

using TAbeMotionFunction = decltype(&Abe::Motion_0_Idle_423520);

#define MAKE_STRINGS(VAR) #VAR,
const char_type* const sAbeMotionNames[] = {
    AO_ABE_MOTIONS_ENUM(MAKE_STRINGS)};

const TAbeMotionFunction sAbeMotionMachineTable_4C5F08[] = {
    &Abe::Motion_0_Idle_423520,
    &Abe::Motion_1_WalkLoop_423F90,
    &Abe::Motion_2_StandingTurn_426040,
    &Abe::Motion_3_Fall_42E7F0,
    &Abe::Motion_4_WalkToIdle_4243C0,
    &Abe::Motion_5_MidWalkToIdle_424490,
    &Abe::Motion_6_WalkBegin_424300,
    &Abe::Motion_7_Speak_42F950,
    &Abe::Motion_8_Speak_42F9D0,
    &Abe::Motion_9_Speak_42FA50,
    &Abe::Motion_10_Speak_42FAD0,
    &Abe::Motion_11_Speak_42FB50,
    &Abe::Motion_12_Speak_42FBD0,
    &Abe::Motion_13_Speak_42FC50,
    &Abe::Motion_14_Speak_42FCD0,
    &Abe::Motion_15_Null_42A210,
    &Abe::Motion_16_HoistBegin_426E40,
    &Abe::Motion_17_HoistIdle_4269E0,
    &Abe::Motion_18_HoistLand_426EB0,
    &Abe::Motion_19_CrouchIdle_4284C0,
    &Abe::Motion_20_CrouchToStand_428AF0,
    &Abe::Motion_21_StandToCrouch_427F40,
    &Abe::Motion_22_CrouchSpeak_428A30,
    &Abe::Motion_23_CrouchSpeak_428A90,
    &Abe::Motion_24_RollBegin_427A20,
    &Abe::Motion_25_RollLoop_427BB0,
    &Abe::Motion_26_RollEnd_427EA0,
    &Abe::Motion_27_RunSlideStop_425B60,
    &Abe::Motion_28_RunTurn_425CE0,
    &Abe::Motion_29_HopBegin_4267B0,
    &Abe::Motion_30_HopMid_4264D0,
    &Abe::Motion_31_HopLand_426940,
    &Abe::Motion_32_RunJumpBegin_427440,
    &Abe::Motion_33_RunJumpMid_426FA0,
    &Abe::Motion_34_RunJumpLand_427560,
    &Abe::Motion_35_RunLoop_425060,
    &Abe::Motion_36_DunnoBegin_423260,
    &Abe::Motion_37_DunnoMid_4232C0,
    &Abe::Motion_38_DunnoEnd_423310,
    &Abe::Motion_39_CrouchTurn_4288C0,
    &Abe::Motion_40_RunToRoll_427AE0,
    &Abe::Motion_41_StandingToRun_425530,
    &Abe::Motion_42_SneakLoop_424BB0,
    &Abe::Motion_43_WalkToSneak_424790,
    &Abe::Motion_44_SneakToWalk_4249A0,
    &Abe::Motion_45_MidWalkToSneak_424890,
    &Abe::Motion_46_MidSneakToWalk_424AA0,
    &Abe::Motion_47_SneakBegin_424ED0,
    &Abe::Motion_48_SneakToIdle_424F80,
    &Abe::Motion_49_MidSneakToIdle_424FF0,
    &Abe::Motion_50_WalkToRun_424560,
    &Abe::Motion_51_MidWalkToRun_424670,
    &Abe::Motion_52_RunToWalk_4255E0,
    &Abe::Motion_53_MidRunToWalk_4256E0,
    &Abe::Motion_54_RunTurnToRun_425EA0,
    &Abe::Motion_55_RunTurnToWalk_425F70,
    &Abe::Motion_56_RunJumpLandRun_4278E0,
    &Abe::Motion_57_RunJumpLand_Walk_427980,
    &Abe::Motion_58_ToSpeak_42F8D0,
    &Abe::Motion_59_DeathDropFall_42CBE0,
    &Abe::Motion_60_Dead_42C4C0,
    &Abe::Motion_61_Respawn_42CD20,
    &Abe::Motion_62_LoadedSaveSpawn_45ADD0,
    &Abe::Motion_63_TurnToRun_42A0A0,
    &Abe::Motion_64_LedgeAscend_428B60,
    &Abe::Motion_65_LedgeDescend_428C00,
    &Abe::Motion_66_LedgeHang_428D90,
    &Abe::Motion_67_ToOffScreenHoist_428C50,
    &Abe::Motion_68_LedgeHangWobble_428E50,
    &Abe::Motion_69_RingRopePullHang_4299B0,
    &Abe::Motion_70_Knockback_428FB0,
    &Abe::Motion_71_KnockbackGetUp_429240,
    &Abe::Motion_72_PushWall_4292A0,
    &Abe::Motion_73_RollingKnockback_4291D0,
    &Abe::Motion_74_JumpIntoWell_430EC0,
    &Abe::Motion_75_ToInsideOfAWellLocal_431090,
    &Abe::Motion_76_ToWellShotOut_431720,
    &Abe::Motion_77_WellBegin_430F10,
    &Abe::Motion_78_InsideWellLocal_4310A0,
    &Abe::Motion_79_WellShotOut_431730,
    &Abe::Motion_80_ToWellBegin_430EF0,
    &Abe::Motion_81_InsideWellExpress_431320,
    &Abe::Motion_82_WellExpressShotOut_4315A0,
    &Abe::Motion_83_ToWellBegin_430F00,
    &Abe::Motion_84_ToInsideWellLocal_431080,
    &Abe::Motion_85_ToWellShotOut_431710,
    &Abe::Motion_86_FallLandDie_42EDD0,
    &Abe::Motion_87_ToFall_428FA0,
    &Abe::Motion_88_HandstoneBegin_430590,
    &Abe::Motion_89_HandstoneEnd_430E80,
    &Abe::Motion_90_GrenadeMachineUse_430EA0,
    &Abe::Motion_91_FallingFromGrab_429780,
    &Abe::Motion_92_ForceDownFromHoist_4297C0,
    &Abe::Motion_93_WalkOffEdge_429840,
    &Abe::Motion_94_RunOffEdge_429860,
    &Abe::Motion_95_SneakOffEdge_429880,
    &Abe::Motion_96_HopToFall_4298A0,
    &Abe::Motion_97_RunJumpToFall_429930,
    &Abe::Motion_98_LandSoft_42ED40,
    &Abe::Motion_99_HoistBeginLong_426DC0,
    &Abe::Motion_100_RollOffLedge_429950,
    &Abe::Motion_101_LeverUse_429970,
    &Abe::Motion_102_ElumWalkLoop_42DCA0,
    &Abe::Motion_103_ElumIdle_42DCD0,
    &Abe::Motion_104_ElumRunSlideStop_42DF00,
    &Abe::Motion_105_ElumRunTurn_42DF10,
    &Abe::Motion_106_Null_42DF20,
    &Abe::Motion_107_ElumHopBegin_42DF30,
    &Abe::Motion_108_ElumHopMid_42DF40,
    &Abe::Motion_109_ElumHopLand_42DF50,
    &Abe::Motion_110_ElumRunJumpBegin_42DF60,
    &Abe::Motion_111_ElumRunJumpMid_42DF70,
    &Abe::Motion_112_ElumRunJumpLand_42DF80,
    &Abe::Motion_113_ElumTurn_42DF90,
    &Abe::Motion_114_ElumRunLoop_42DFA0,
    &Abe::Motion_115_ElumSpeak_4299F0,
    &Abe::Motion_116_Null_42DFB0,
    &Abe::Motion_117_ElumWalkBegin_42DFC0,
    &Abe::Motion_118_ElumRunBegin_42DFD0,
    &Abe::Motion_119_Null_42DFE0,
    &Abe::Motion_120_ElumRunToWalk_42DFF0,
    &Abe::Motion_121_ElumMidRunToWalk_42E000,
    &Abe::Motion_122_ElumRunTurnToRun_42E010,
    &Abe::Motion_123_ElumRunTurnToWalk_42E020,
    &Abe::Motion_124_ElumWalkEnd_42DCB0,
    &Abe::Motion_125_ElumMidWalkEnd_42DCC0,
    &Abe::Motion_126_ElumBeesStruggling_42E080,
    &Abe::Motion_127_SlapBomb_429A20,
    &Abe::Motion_128_KnockForward_429330,
    &Abe::Motion_129_RollingKnockForward_4294F0,
    &Abe::Motion_130_KnockForwardGetUp_429560,
    &Abe::Motion_131_LiftUseUp_42F150,
    &Abe::Motion_132_LiftUseDown_42F170,
    &Abe::Motion_133_LiftGrabBegin_42EF20,
    &Abe::Motion_134_LiftGrabEnd_42EFE0,
    &Abe::Motion_135_LiftGrabIdle_42F000,
    &Abe::Motion_136_ElumMountEnd_42E110,
    &Abe::Motion_137_ElumUnmountBegin_42E2B0,
    &Abe::Motion_138_ElumUnmountEnd_42E390,
    &Abe::Motion_139_ElumMountBegin_42E090,
    &Abe::Motion_140_BeesStruggling_423F30,
    &Abe::Motion_141_BeesStrugglingOnLift_42F390,
    &Abe::Motion_142_RockThrowStandingHold_429CE0,
    &Abe::Motion_143_RockThrowStandingThrow_429FD0,
    &Abe::Motion_144_RockThrowStandingEnd_429DE0,
    &Abe::Motion_145_RockThrowCrouchingHold_428930,
    &Abe::Motion_146_RockThrowCrouchingThrow_4289F0,
    &Abe::Motion_147_ShotRolling_4295C0,
    &Abe::Motion_148_Shot_4296A0,
    &Abe::Motion_149_PickupItem_42A030,
    &Abe::Motion_150_Chant_42FD50,
    &Abe::Motion_151_ChantEnd_430530,
    &Abe::Motion_152_ElumFallOffEdge_42E030,
    &Abe::Motion_153_ElumFall_42E040,
    &Abe::Motion_154_ElumLand_42E050,
    &Abe::Motion_155_ElumJumpToFall_42E060,
    &Abe::Motion_156_DoorEnter_42D370,
    &Abe::Motion_157_DoorExit_42D780,
    &Abe::Motion_158_ElumKnockback_42E070,
    &Abe::Motion_159_Idle_RubEyes_423360,
    &Abe::Motion_160_Idle_Stretch_Arms_4233A0,
    &Abe::Motion_161_Idle_Yawn_4233E0,
    &Abe::Motion_162_ToShrykull_42F410,
    &Abe::Motion_163_ShrykullEnd_42F520,
    &Abe::Motion_164_PoisonGasDeath_42A120};

const AnimId sAbeMotionAnimIds[166] = {
    AnimId::Mudokon_Idle,
    AnimId::Mudokon_Walk,
    AnimId::Mudokon_StandingTurn,
    AnimId::Mudokon_Idle,
    AnimId::Mudokon_WalkToIdle,
    AnimId::Mudokon_WalkToIdle,
    AnimId::Mudokon_WalkBegin,
    AnimId::Mudokon_Speak1,
    AnimId::Mudokon_Speak3,
    AnimId::Mudokon_Speak2,
    AnimId::Mudokon_SpeakFart,
    AnimId::Mudokon_Speak1,
    AnimId::Mudokon_Speak2,
    AnimId::Mudokon_Speak3,
    AnimId::Mudokon_SpeakFart,
    AnimId::Mudokon_AO_M_15_Null,
    AnimId::Mudokon_HoistBegin,
    AnimId::Mudokon_HoistIdle,
    AnimId::Mudokon_LandSoft,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchToStand,
    AnimId::Mudokon_StandToCrouch,
    AnimId::Mudokon_CrouchSpeak1,
    AnimId::Mudokon_CrouchSpeak2,
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
    AnimId::Mudokon_DunnoMid,
    AnimId::Mudokon_DunnoEnd,
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
    AnimId::Mudokon_ToSpeak,
    AnimId::Mudokon_CrouchIdle, // double check these
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_TurnToRun,
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
    AnimId::Mudokon_WellBegin,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_FallLandDie,
    AnimId::Mudokon_Fall,
    AnimId::Mudokon_HandstoneBegin, 
    AnimId::Mudokon_HandstoneEnd,
    AnimId::Mudokon_GrenadeMachineUse,
    AnimId::Mudokon_FallingFromGrab,
    AnimId::Mudokon_FallingFromGrab,
    AnimId::Mudokon_WalkOffEdge,
    AnimId::Mudokon_RunOffEdge,
    AnimId::Mudokon_SneakOffEdge,
    AnimId::Mudokon_HopToFall,
    AnimId::Mudokon_RunJumpToFall,
    AnimId::Mudokon_AO_LandSoft_Long,
    AnimId::Mudokon_AO_HoistBegin_Long,
    AnimId::Mudokon_RollOffEdge,
    AnimId::Mudokon_LeverUse,
    AnimId::Mudokon_ElumWalkLoop,
    AnimId::Mudokon_ElumIdle,
    AnimId::Mudokon_ElumRunSlideStop,
    AnimId::Mudokon_ElumRunTurn,
    AnimId::Mudokon_AO_M_106_Null,
    AnimId::Mudokon_ElumHopBegin,
    AnimId::Mudokon_ElumHopMid,
    AnimId::Mudokon_ElumHopLand,
    AnimId::Mudokon_ElumRunJumpBegin,
    AnimId::Mudokon_ElumRunJumpMid,
    AnimId::Mudokon_ElumRunJumpLand,
    AnimId::Mudokon_ElumTurn,
    AnimId::Mudokon_ElumRunLoop,
    AnimId::Mudokon_ElumSpeak,
    AnimId::Mudokon_AO_M_116_Null,
    AnimId::Mudokon_ElumWalkBegin,
    AnimId::Mudokon_ElumRunBegin,
    AnimId::Mudokon_AO_M_119_Null,
    AnimId::Mudokon_ElumRunToWalk,
    AnimId::Mudokon_ElumMidRunToWalk,
    AnimId::Mudokon_ElumRunTurnToRun,
    AnimId::Mudokon_ElumRunTurnToWalk,
    AnimId::Mudokon_ElumWalkEnd,
    AnimId::Mudokon_ElumMidWalkEnd,
    AnimId::Mudokon_ElumBeesStruggling,
    AnimId::Mudokon_SlapBomb,
    AnimId::Mudokon_KnockForward,
    AnimId::Mudokon_RollingKnockForward,
    AnimId::Mudokon_Idle, // knock forward get up?
    AnimId::Mudokon_AO_Null, // lift use up
    AnimId::Mudokon_AO_LiftUse, // lift use down
    AnimId::Mudokon_LiftGrabBegin,
    AnimId::Mudokon_LiftGrabEnd,
    AnimId::Mudokon_LiftGrabIdle,
    AnimId::Mudokon_ElumMountEnd,
    AnimId::Mudokon_ElumUnmountBegin,
    AnimId::Mudokon_ElumUnmountEnd,
    AnimId::Mudokon_ElumMountBegin,
    AnimId::Mudokon_Struggle,
    AnimId::Mudokon_Struggle,
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
    AnimId::Mudokon_ElumFallOffEdge,
    AnimId::Mudokon_ElumFall,
    AnimId::Mudokon_ElumLand,
    AnimId::Mudokon_ElumJumpToFall,
    AnimId::Mudokon_DoorEnter,
    AnimId::Mudokon_DoorExit,
    AnimId::Mudokon_ElumKnockback,
    AnimId::Mudokon_Idle_RubEyes,
    AnimId::Mudokon_Idle_StretchArms,
    AnimId::Mudokon_Idle_Yawn,
    AnimId::Mudokon_AO_ToShrykull,
    AnimId::Mudokon_AO_ShrykullEnd,
    AnimId::Mudokon_PoisonGasDeath,
    AnimId::None};

/*const s32 sAbeMotionAnimIds[166] = {
    55968,
    55888,
    56144,
    55968,
    55868,
    55868,
    55848,
    56108,
    56072,
    56036,
    56000,
    56108,
    56036,
    56072,
    56000,
    255776,
    255484,
    255532,
    255436,
    255600,
    255568,
    255384,
    256660,
    256700,
    255196,
    255216,
    255272,
    256424,
    255868,
    256584,
    256636,
    256544,
    256008,
    255312,
    256028,
    256312,
    255716,
    255688,
    256180,
    255968,
    256272,
    255788,
    256048,
    256252,
    256160,
    256404,
    256292,
    255828,
    255668,
    255848,
    255628,
    255808,
    256232,
    256384,
    255948,
    255648,
    255292,
    255364,
    256136,
    255600,
    255600,
    255600,
    255600,
    256524,
    54208,
    54348,
    54308,
    54308,
    54480,
    54448,
    48272,
    48332,
    48460,
    48404,
    19644,
    19624,
    19624,
    19476,
    19624,
    19624,
    19476,
    19624,
    19624,
    19476,
    19624,
    19624,
    7880,
    5560,
    15484,
    15428,
    15608,
    40652,
    40652,
    40680,
    40708,
    40752,
    40852,
    40836,
    40868,
    40772,
    40816,
    10988,
    144920,
    145132,
    145736,
    145804,
    145000,
    145104,
    145164,
    145196,
    145220,
    145688,
    145240,
    145456,
    145312,
    145512,
    145588,
    145608,
    145548,
    145416,
    145436,
    145568,
    145272,
    145292,
    145648,
    145668,
    145860,
    6360,
    16772,
    16712,
    55968,
    21744,
    21644,
    21696,
    21720,
    21612,
    23568,
    13716,
    34676,
    16256,
    21496,
    21496,
    30440,
    30328,
    30568,
    30512,
    30368,
    23996,
    24044,
    5828,
    9516,
    9564,
    21672,
    21700,
    21724,
    21780,
    17520,
    17568,
    11652,
    9860,
    13152,
    12392,
    8240,
    8280,
    27748,
    0};*/

ALIVE_VAR(1, 0x507678, Abe*, sActiveHero, nullptr);
ALIVE_VAR(1, 0x50767C, BaseAliveGameObject*, sControlledCharacter, nullptr);

SfxDefinition sSFXList_4C6638[49] = {
    {0, 3, 69, 60, -1, 1, 0},
    {0, 3, 70, 60, -1, 1, 0},
    {0, 3, 59, 67, -1, 1, 0},
    {0, 3, 61, 67, -1, 1, 0},
    {0, 3, 58, 52, -1, 1, 0},
    {0, 3, 67, 45, -1, 1, 0},
    {0, 3, 57, 60, -1, 1, 0},
    {0, 3, 65, 50, -1, 1, 0},
    {0, 3, 68, 60, -1, 1, 0},
    {0, 3, 72, 70, -1, 1, 0},
    {0, 4, 36, 50, -127, 0, 0},
    {0, 4, 37, 50, -127, 0, 0},
    {0, 4, 38, 50, -127, 0, 0},
    {0, 4, 36, 55, 0, 127, 0},
    {0, 4, 37, 55, 0, 127, 0},
    {0, 4, 38, 55, 0, 127, 0},
    {0, 4, 59, 50, -1, 1, 0},
    {0, 4, 72, 127, -1, 1, 0},
    {0, 4, 80, 127, -1, 1, 0},
    {0, 11, 61, 60, -1, 0, 0},
    {0, 11, 62, 60, -1, 1, 0},
    {0, 11, 64, 60, -1, 1, 0},
    {0, 11, 65, 50, -1, 1, 0},
    {0, 11, 64, 50, -1, 1, 0},
    {0, 11, 66, 50, -1, 1, 0},
    {0, 23, 60, 90, 0, 0, 0},
    {0, 23, 61, 90, 0, 0, 0},
    {0, 23, 62, 90, 0, 0, 0},
    {0, 23, 63, 90, 0, 0, 0},
    {0, 23, 64, 90, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 58, 61, 97, 0, 0, 0},
    {0, 58, 60, 97, 0, 0, 0},
    {0, 59, 60, 127, 0, 0, 0},
    {0, 59, 61, 127, 0, 0, 0},
    {0, 59, 62, 127, 0, 0, 0},
    {0, 59, 63, 110, 0, 0, 0},
    {0, 60, 61, 127, 0, 0, 0},
    {0, 60, 63, 127, 0, 0, 0},
    {0, 61, 55, 127, 0, 0, 0},
    {0, 61, 56, 127, 0, 0, 0},
    {0, 61, 57, 127, 0, 0, 0},
    {0, 61, 58, 127, 0, 0, 0},
    {0, 61, 59, 127, 0, 0, 0},
    {0, 61, 60, 127, 0, 0, 0},
    {0, 61, 61, 127, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 65, 60, 127, 0, 0, 0},
    {0, 65, 64, 80, 0, 0, 0}};

s32 Environment_SFX_42A220(EnvironmentSfx sfxId, s32 volume, s32 pitchMin, BaseAliveGameObject* pAliveObj)
{
    s16 sndIndex = 0;
    switch (sfxId)
    {
        case EnvironmentSfx::eSlideStop_0:
            sndIndex = 11;
            volume = 40;
            break;
        case EnvironmentSfx::eWalkingFootstep_1:
            sndIndex = Math_RandomRange(10, 12);
            if (volume == 0)
            {
                volume = Math_RandomRange(54, 58);
            }
            break;
        case EnvironmentSfx::eRunningFootstep_2:
            sndIndex = Math_RandomRange(13, 15);
            if (volume == 0)
            {
                volume = Math_RandomRange(66, 70);
            }
            break;
        case EnvironmentSfx::eSneakFootstep_3:
            sndIndex = 5;
            break;
        case EnvironmentSfx::eRunSlide_4:
            sndIndex = 4;
            break;
        case EnvironmentSfx::eLandingSoft_5:
        {
            s32 v4 = 0;
            s32 v5 = 0;
            if (volume > 0 || !pAliveObj || pAliveObj->mSpriteScale != FP_FromDouble(0.5))
            {
                v4 = SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[2], volume, pitchMin, 0x7FFF);
                v5 = SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[48], volume, pitchMin, 0x7FFF);
            }
            else
            {
                v4 = SFX_SfxDefinition_Play_4770F0(
                    &sSFXList_4C6638[2],
                    sSFXList_4C6638[2].field_C_default_volume / 2,
                    pitchMin,
                    0x7FFF);
                v5 = SFX_SfxDefinition_Play_4770F0(
                    &sSFXList_4C6638[48],
                    sSFXList_4C6638[18].field_C_default_volume / 2,
                    pitchMin,
                    0x7FFF);
            }
            return v5 | v4;
        }
        case EnvironmentSfx::eHitGroundSoft_6:
            sndIndex = 2;
            break;
        case EnvironmentSfx::eDeathNoise_7:
            sndIndex = 16;
            break;
        case EnvironmentSfx::eRollingNoise_8:
            sndIndex = 6;
            break;
        case EnvironmentSfx::eGenericMovement_9:
        case EnvironmentSfx::eRunJumpOrLedgeHoist_11:
        {
            s32 result = 0;
            if (pAliveObj && pAliveObj->mSpriteScale == FP_FromDouble(0.5))
            {
                result = SfxPlayMono(SoundEffect::AbeGenericMovement_37, 20, 0);
            }
            else
            {
                result = SfxPlayMono(SoundEffect::AbeGenericMovement_37, 35, 0);
            }
            return result;
        }
        case EnvironmentSfx::eExhaustingHoistNoise_10:
        case EnvironmentSfx::eExhaustingElumMount_16:
            sndIndex = 19;
            break;
        case EnvironmentSfx::eUnknown_12:
            sndIndex = 25;
            break;
        case EnvironmentSfx::eKnockback_13:
            if (gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarms
                || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom
                || gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn)
            {
                sndIndex = 2;
            }
            else
            {
                sndIndex = 9;
            }
            break;
        case EnvironmentSfx::eElumHitWall_14:
            sndIndex = 17;
            break;
        case EnvironmentSfx::eFallingDeathScreamHitGround_15:
            return 0;
        case EnvironmentSfx::eMountElumSmackNoise_17:
            sndIndex = 20;
            break;
        case EnvironmentSfx::eElumGetMountedNoise_18:
            sndIndex = 21;
            break;
        case EnvironmentSfx::eAbeMountedElumNoise_19:
            sndIndex = 22;
            break;
        case EnvironmentSfx::eElumHowl_20:
            sndIndex = 23;
            break;
        case EnvironmentSfx::eElumOkay_21:
            sndIndex = 24;
            break;
        default:
            break;
    }
    if (volume == 0)
    {
        volume = sSFXList_4C6638[sndIndex].field_C_default_volume;
    }
    if (pAliveObj)
    {
        if (pAliveObj->mSpriteScale == FP_FromDouble(0.5))
        {
            volume *= 2;
            volume /= 3;
        }
    }
    return SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[sndIndex], volume, pitchMin, 0x7FFF);
}

s32 Mudokon_SFX(MudSounds idx, s32 volume, s32 pitch, BaseAliveGameObject* pHero)
{
    if (idx == MudSounds::eLaugh1_8
        && pHero == sActiveHero
        && (gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom))
    {
        idx = MudSounds::eLaugh2_11;
    }
    if (idx == MudSounds::eOops_16)
    {
        if (pHero && pHero->mSpriteScale == FP_FromDouble(0.5))
        {
            SND_SEQ_Play_477760(SeqId::eAbeOops_23, 1, 85, 85);
            return 0;
        }
        else
        {
            SND_SEQ_Play_477760(SeqId::eAbeOops_23, 1, 110, 110);
            return 0;
        }
    }
    else
    {
        auto idxShort = static_cast<s16>(idx);
        if (volume == 0)
        {
            volume = sSFXList_4C6638[idxShort + 30].field_C_default_volume;
        }
        if (pHero)
        {
            if (pHero->mSpriteScale == FP_FromDouble(0.5))
            {
                volume *= 2;
                volume /= 3;
            }
        }
        return SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[idxShort + 30], volume, pitch, pitch);
    }
}

void Abe::VOnTrapDoorOpen()
{
    if (mLiftPoint)
    {
        if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
        {
            VSetMotion(eAbeMotions::Motion_93_WalkOffEdge_429840);
        }

        mLiftPoint->VRemove(this);
        mLiftPoint->mBaseGameObjectRefCount--;
        mLiftPoint = nullptr;
        BaseAliveGameObjectLastLineYPos = mYPos;
    }
}

const TintEntry sAbeTints_4C6438[] = {
    {EReliveLevelIds::eStockYards, 25u, 25u, 25u},
    {EReliveLevelIds::eStockYardsReturn, 25u, 25u, 25u},
    {EReliveLevelIds::eDesert, 125u, 125u, 95u},
    {EReliveLevelIds::eDesertTemple, 120u, 120u, 90u},
    {EReliveLevelIds::eNone, 102u, 102u, 102u}};


Abe::Abe(s32 frameTableOffset, s32 /*r*/, s32 /*g*/, s32 /*b*/)
{
    mBaseGameObjectTypeId = ReliveTypes::eAbe;

    mBaseGameObjectFlags.Set(Options::eSurviveDeathReset_Bit9);

    Init_GameStates();

    // Zero out the resource array
    field_1A4_resources = {};

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEBSIC.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
    }

    field_1A4_resources.res[0] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 0, 0);

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEBSIC1.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 1, 0);
    }

    field_1A4_resources.res[45] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 0, 0);

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeedgeAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEEDGE.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeedgeAOResID, 1, 0);
    }

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeknfdAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEKNFD.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeknfdAOResID, 1, 0);
    }

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEOMM.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
    }

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeknbkAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEKNBK.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeknbkAOResID, 1, 0);
    }

    ResourceManager::LoadResourceFile_455270("ABENOELM.BND", nullptr);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("OMMFLARE.BAN", nullptr);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kOmmflareAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("SQBSMK.BAN", nullptr);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSquibSmokeAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("BLOODROP.BAN", nullptr);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kBloodropAOResID, 1, 0);
    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kObjectShadowAOResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_455270("SHADOW.BAN", nullptr);
    }
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kObjectShadowAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("DEADFLR.BAN", nullptr);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kDeathFlareAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("DOVBASIC.BAN", nullptr);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kDovbasicAOResID, 1, 0);

    field_128_resource_idx = 45;
    Animation_Init(frameTableOffset, 135, 80, field_1A4_resources.res[45]);

    mAnim.mFnPtrArray = kAbe_Anim_Frame_Fns_4CEBEC;

    PSX_Point pPoint = {};
    gMap.GetCurrentCamCoords(&pPoint);
    mXPos = FP_FromInteger(pPoint.x + XGrid_Index_To_XPos(mSpriteScale, 4));
    mYPos = FP_FromInteger(pPoint.y + 240);
    field_120_x_vel_slow_by = FP_FromInteger(0);
    field_124_unused = 0;
    BaseAliveGameObjectLastLineYPos = mYPos;
    mVelX = FP_FromInteger(0);
    mVelY = FP_FromInteger(0);
    BaseAliveGameObjectCollisionLine = nullptr;
    mCurrentMotion = eAbeMotions::Motion_3_Fall_42E7F0;

    field_112_prev_motion = -1;
    mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
    field_15C_pThrowable = nullptr;
    field_19C_throwable_count = 0;
    field_198_pThrowable = nullptr;
    field_1A0_portal = 0;
    field_158_pDeathFadeout = nullptr;
    field_164_pCircularFade = nullptr;
    field_188_pOrbWhirlWind = nullptr;
    field_18C_pObjToPossess = nullptr;
    mContinueTopLeft = {};
    mContinueBottomRight = {};
    mContinueCamera = -1;
    mBaseAliveGameObjectFlags.Set(Flags_10A::e10A_Bit4_SetOffExplosives);

    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit1);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit3_ElumMountBegin);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit4_ElumMountEnd);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);

    mContinueSpriteScale = mSpriteScale;
    mContinueLevel = gMap.mCurrentLevel;
    mContinuePath = -1;
    mContinueClearFromId = 0;
    mContinueClearToId = 0;
    mContinueZoneNumber = 0;
    field_150_saved_ring_timer = 0;
    field_154_bSavedHaveShrykull = 0;

    field_2A8_flags.Raw().all = 0;
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit8_bLandSoft);

    // Changes Abe's "default" colour depending on the level we are in
    SetTint(sAbeTints_4C6438, gMap.mCurrentLevel);

    mAnim.mFlags.Set(AnimFlags::eBit15_bSemiTrans);
    mAnim.mRenderMode = TPageAbr::eBlend_0;

    field_10C_prev_held = 0; // lowest to base class
    mBaseAliveGameObjectLastAnimFrame = 0;
    field_110_state.raw = 0;
    field_168_ring_pulse_timer = 0;
    field_114_gnFrame = sGnFrame;
    BaseAliveGameObjectPathTLV = nullptr;
    field_160_pRope = nullptr;
    mLiftPoint = nullptr;
    field_130_say = -1;
    field_134_auto_say_timer = 0;
    field_EC = 1;
    field_12A_unused = 161;

    // Set Abe to be the current player controlled object
    sControlledCharacter = this;

    // Create shadow
    mShadow = relive_new Shadow();

    // Animation test code
    //auto testAnim = relive_new TestAnimation(); testAnim->ctor();
}

Abe::~Abe()
{
    MusicController::ClearObject(this);

    SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);

    u8** ppRes = nullptr;

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 0, 0);
    if (ppRes)
    {
        if (mAnim.field_20_ppBlock != ppRes)
        {
            ResourceManager::FreeResource_455550(ppRes);
        }
    }

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 0, 0);
    if (ppRes)
    {
        if (mAnim.field_20_ppBlock != ppRes)
        {
            ResourceManager::FreeResource_455550(ppRes);
        }
    }

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeedgeAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeknbkAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeknfdAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kOmmflareAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kBloodropAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kObjectShadowAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kDeathFlareAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kDovbasicAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSquibSmokeAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    if (field_158_pDeathFadeout)
    {
        field_158_pDeathFadeout->mBaseGameObjectRefCount--;
        field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
        field_158_pDeathFadeout = nullptr;
    }

    if (field_15C_pThrowable)
    {
        field_15C_pThrowable->mBaseGameObjectRefCount--;
        field_15C_pThrowable->mBaseGameObjectFlags.Set(Options::eDead);
        field_15C_pThrowable = nullptr;
    }

    if (field_160_pRope)
    {
        field_160_pRope->mBaseGameObjectRefCount--;
        field_160_pRope->mBaseGameObjectFlags.Set(Options::eDead);
        field_160_pRope = nullptr;
    }

    if (field_164_pCircularFade)
    {
        field_164_pCircularFade->mBaseGameObjectRefCount--;
        field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
        field_164_pCircularFade = nullptr;
    }

    if (field_188_pOrbWhirlWind)
    {
        field_188_pOrbWhirlWind->mBaseGameObjectRefCount--;
        field_188_pOrbWhirlWind->mBaseGameObjectFlags.Set(Options::eDead);
        field_188_pOrbWhirlWind = nullptr;
    }

    if (field_18C_pObjToPossess)
    {
        field_18C_pObjToPossess->mBaseGameObjectRefCount--;
        field_18C_pObjToPossess->mBaseGameObjectFlags.Set(Options::eDead);
        field_18C_pObjToPossess = nullptr;
    }

    if (field_198_pThrowable)
    {
        field_198_pThrowable->mBaseGameObjectRefCount--;
        field_198_pThrowable->mBaseGameObjectFlags.Set(Options::eDead);
        field_198_pThrowable = nullptr;
    }

    sActiveHero = nullptr;

    // OG fix for going back to menu with DDCheat on and then it crashes reading a deleted pointer
    // ditto for the ending where MeatSaw/Invisible switch screen change/update funcs read it.
    sControlledCharacter = nullptr;
}

const u32 sAbe_xVel_table_4BB118[8] = {262144, 262144, 0, 4294705152, 4294705152, 4294705152, 0, 262144};
const u32 sAbe_yVel_table_4BB138[8] = {0, 4294705152, 4294705152, 4294705152, 0, 262144, 262144, 262144};

void Abe::VUpdate()
{
    if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit1))
    {
        if (gAbeInvulnerableCheat_5076E4)
        {
            mHealth = FP_FromInteger(1);
        }

        if (!Input_IsChanting())
        {
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit7);
        }

        if (sDDCheat_FlyingEnabled_50771C && sControlledCharacter == this)
        {
            VOnTrapDoorOpen();

            const FP old_y = mYPos;
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit6_bShrivel);
            BaseAliveGameObjectLastLineYPos = old_y;
            mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
            BaseAliveGameObjectCollisionLine = nullptr;

            if (Input().IsAnyPressed(0xF000u))
            {
                const s32 dir = Input().Dir();
                mVelX = FP_FromRaw(sAbe_xVel_table_4BB118[dir] * 2);
                mVelY = FP_FromRaw(sAbe_yVel_table_4BB138[dir]);

                if (Input().IsAnyPressed(sInputKey_Run))
                {
                    mVelX += FP_FromRaw(sAbe_xVel_table_4BB118[dir]);
                    mVelY += FP_FromRaw(sAbe_yVel_table_4BB138[dir]);
                }

                mXPos += mVelX;
                mYPos += mVelY;

                PSX_Point mapSize = {};
                gMap.Get_map_size(&mapSize);

                if (mXPos < FP_FromInteger(0))
                {
                    mXPos = FP_FromInteger(0);
                }

                if (mXPos >= FP_FromInteger(mapSize.x))
                {
                    mXPos = FP_FromInteger(mapSize.x) - FP_FromInteger(1);
                }

                if (mYPos < FP_FromInteger(0))
                {
                    mYPos = FP_FromInteger(0);
                }

                if (mYPos >= FP_FromInteger(mapSize.y))
                {
                    mYPos = FP_FromInteger(mapSize.y) - FP_FromInteger(1);
                    SetActiveCameraDelayedFromDir_401C90();
                    return;
                }
            }
            else
            {
                mVelX = FP_FromInteger(0);
                mVelY = FP_FromInteger(0);
            }
            SetActiveCameraDelayedFromDir_401C90();
        }
        else
        {
            mAnim.mFlags.Set(AnimFlags::eBit2_Animate);


            // Execute the current state
            s16 motion_idx = mCurrentMotion;
            const FP oldX = mXPos;
            const FP oldY = mYPos;
            (this->*sAbeMotionMachineTable_4C5F08[motion_idx])();

            if (BaseAliveGameObjectCollisionLine)
            {
                // Snap to a whole number so we are "on" the line
                mYPos = FP_NoFractional(mYPos);
            }

            if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
            {
                // Did position change?
                if (oldX != mXPos || oldY != mYPos || sControlledCharacter == gElum)
                {
                    // Get the TLV we are on
                    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                        nullptr,
                        mXPos,
                        mYPos,
                        mXPos,
                        mYPos);

                    VOnTlvCollision(BaseAliveGameObjectPathTLV);
                }

                if (field_106_shot)
                {
                    motion_idx = field_112_prev_motion;
                    ToKnockback_422D90(1, 0);
                    mCurrentMotion = motion_idx;
                    mNextMotion = 0;
                    field_112_prev_motion = 0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
#if ORIGINAL_GAME_FIXES || ORIGINAL_GAME_FIX_DEATH_DELAY_AO
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit2_return_to_previous_motion); // OG Change - Fixes "Death Delay Glitch"
#endif
                }

                if (EventGet(kEventScreenShake))
                {
                    if (IsStanding_41FC10())
                    {
                        ToKnockback_422D90(1, 0);
                    }
                }

                if (motion_idx != mCurrentMotion || field_108_bMotionChanged)
                {
                    field_108_bMotionChanged = FALSE;

                    if (mCurrentMotion != eAbeMotions::Motion_15_Null_42A210 && !field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
                    {
                        mAnim.Set_Animation_Data(
                            sAbeMotionAnimIds[mCurrentMotion],
                            StateToAnimResource_4204F0(mCurrentMotion));

                        field_12C_timer = sGnFrame;

                        if (motion_idx == eAbeMotions::Motion_15_Null_42A210 || motion_idx == eAbeMotions::Motion_62_LoadedSaveSpawn_45ADD0)
                        {
                            mAnim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
                        }
                    }
                }
                else if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit2_return_to_previous_motion))
                {
                    mCurrentMotion = mPreviousMotion;
                    mAnim.Set_Animation_Data(
                        sAbeMotionAnimIds[mCurrentMotion],
                        StateToAnimResource_4204F0(mCurrentMotion));

                    field_12C_timer = sGnFrame;
                    mAnim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
                }

                if (field_11C_regen_health_timer <= static_cast<s32>(sGnFrame) && mHealth > FP_FromInteger(0))
                {
                    mHealth = FP_FromInteger(1);
                }

                if (field_168_ring_pulse_timer)
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
                    {
                        if (static_cast<s32>(sGnFrame) <= field_168_ring_pulse_timer || field_16C_bHaveShrykull)
                        {
                            if (!(sGnFrame % 32))
                            {
                                const PSX_RECT bRect = VGetBoundingRect();
                                AbilityRing::Factory(
                                    FP_FromInteger((bRect.w + bRect.x) / 2),
                                    FP_FromInteger((bRect.h + bRect.y) / 2),
                                    field_16C_bHaveShrykull != 0 ? RingTypes::eShrykull_Pulse_Small_4 : RingTypes::eExplosive_Pulse_0);
                                SFX_Play_Pitch(SoundEffect::PossessEffect_21, 25, 2650, 0);
                            }
                        }
                        else
                        {
                            field_168_ring_pulse_timer = 0;
                        }
                    }
                }

                if (EventGet(kEventMudokonDead))
                {
                    field_130_say = 16;
                    field_134_auto_say_timer = sGnFrame + Math_RandomRange(22, 30);
                    relive_new MusicTrigger(relive::Path_MusicTrigger::MusicTriggerMusicType::eDeathDrumShort, relive::Path_MusicTrigger::TriggeredBy::eTouching, 0, 90);
                }

                if (field_130_say >= 0 && static_cast<s32>(sGnFrame) >= field_134_auto_say_timer)
                {
                    if (gMap.Is_Point_In_Current_Camera(
                            mCurrentLevel,
                            mCurrentPath,
                            mXPos,
                            mYPos,
                            0))
                    {
                        if (mCurrentMotion != eAbeMotions::Motion_150_Chant_42FD50
                            && mCurrentMotion != eAbeMotions::Motion_7_Speak_42F950
                            && mCurrentMotion != eAbeMotions::Motion_8_Speak_42F9D0
                            && mCurrentMotion != eAbeMotions::Motion_9_Speak_42FA50
                            && mCurrentMotion != eAbeMotions::Motion_10_Speak_42FAD0
                            && mCurrentMotion != eAbeMotions::Motion_11_Speak_42FB50
                            && mCurrentMotion != eAbeMotions::Motion_12_Speak_42FBD0
                            && mCurrentMotion != eAbeMotions::Motion_13_Speak_42FC50
                            && mCurrentMotion != eAbeMotions::Motion_14_Speak_42FCD0)
                        {
                            if (mCurrentMotion == eAbeMotions::Motion_0_Idle_423520 || mCurrentMotion == eAbeMotions::Motion_15_Null_42A210)
                            {
                                field_108_bMotionChanged = TRUE;
                                if (field_130_say == 5 || field_130_say == 16)
                                {
                                    mCurrentMotion = eAbeMotions::Motion_10_Speak_42FAD0;
                                }
                                else
                                {
                                    mCurrentMotion = eAbeMotions::Motion_9_Speak_42FA50;
                                }
                            }
                            if (field_130_say == 5)
                            {
                                EventBroadcast(kEventMudokonComfort, sActiveHero);
                            }
                            Mudokon_SFX(static_cast<MudSounds>(field_130_say), 0, 0, this);
                        }
                    }
                    field_130_say = -1;
                }

                if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit12_bParamoniaDone) && field_2A8_flags.Get(Flags_2A8::e2A8_eBit13_bScrabaniaDone))
                {
                    if (!field_2A8_flags.Get(Flags_2A8::e2A8_eBit15_bGiveShrykullFromBigFace) && gMap.mNextLevel == EReliveLevelIds::eLines)
                    {
                        LOG_INFO("Set e2A8_eBit15_bGiveShrykullFromBigFace");
                        field_2A8_flags.Set(Flags_2A8::e2A8_eBit15_bGiveShrykullFromBigFace);
                    }
                }

                if (field_2A8_flags.Get(Flags_2A8::e2A8_eBit15_bGiveShrykullFromBigFace))
                {
                    static bool bLogged = false;
                    if (!bLogged)
                    {
                        LOG_INFO("Have e2A8_eBit15_bGiveShrykullFromBigFace " << static_cast<s32>(gMap.mCurrentLevel));
                        bLogged = true;
                    }

                    if (!field_2A8_flags.Get(Flags_2A8::e2A8_eBit14_bGotShrykullFromBigFace) && gMap.mCurrentLevel == EReliveLevelIds::eLines)
                    {
                        LOG_INFO("Set mHaveShrykull TRUE");
                        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 1, 0))
                        {
                            ResourceManager::LoadResourceFile_455270("ABEMORPH.BAN", nullptr);
                            ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 1, 0);
                        }
                        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 1, 0))
                        {
                            ResourceManager::LoadResourceFile_455270("SHRMORPH.BAN", nullptr);
                            ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 1, 0);
                        }
                        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 1, 0))
                        {
                            ResourceManager::LoadResourceFile_455270("SPLINE.BAN", nullptr);
                            ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 1, 0);
                        }
                        field_16C_bHaveShrykull = TRUE;
                        field_168_ring_pulse_timer = sGnFrame + 32000;
                        field_2A8_flags.Set(Flags_2A8::e2A8_eBit14_bGotShrykullFromBigFace);
                    }
                }
            }
        }
    }
}

void Abe::VRender(PrimHeader** ppOt)
{
    // When in death shrivel don't reset scale else can't shrivel into a black blob
    if (!(field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel)))
    {
        mAnim.field_14_scale = mSpriteScale;
    }

    if (mCurrentMotion != eAbeMotions::Motion_15_Null_42A210 && mCurrentMotion != eAbeMotions::Motion_78_InsideWellLocal_4310A0 && mCurrentMotion != eAbeMotions::Motion_81_InsideWellExpress_431320 && mCurrentMotion != eAbeMotions::Motion_84_ToInsideWellLocal_431080 && mCurrentMotion != eAbeMotions::Motion_75_ToInsideOfAWellLocal_431090)
    {
        BaseAnimatedWithPhysicsGameObject::VRender(ppOt);
    }
}

void Abe::Free_Shrykull_Resources_42F4C0()
{
    ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 0, 0));
    ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 0, 0));
    ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 0, 0));
}

void Abe::FreeElumRes_420F80()
{
    if (mCurrentMotion == eAbeMotions::Motion_139_ElumMountBegin_42E090)
    {
        field_2AA_flags.Set(Flags_2AA::e2AA_Bit3_ElumMountBegin);
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit3_ElumMountBegin);
    }

    if (mCurrentMotion == eAbeMotions::Motion_136_ElumMountEnd_42E110)
    {
        field_2AA_flags.Set(Flags_2AA::e2AA_Bit4_ElumMountEnd);
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit4_ElumMountEnd);
    }

    if (mCurrentMotion == eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0)
    {
        field_2AA_flags.Set(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);
    }

    ElumFree_4228F0();

    while (!ResourceManager::FreeResource_455550(field_1A4_resources.res[58]))
    {
        // Empty
    }

    field_1A4_resources.res[58] = nullptr;
    ResourceManager::FreeResource_455550(field_1A4_resources.res[46]);

    field_1A4_resources.res[46] = nullptr;
    if (gElum)
    {
        gElum->VFreeMountedResources_411200();
    }

    if (mCurrentMotion != eAbeMotions::Motion_138_ElumUnmountEnd_42E390)
    {
        field_104_pending_resource_count++;
        ResourceManager::LoadResourceFile("ABEBSIC.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 0, 0))
        {
            field_104_pending_resource_count++;
            ResourceManager::LoadResourceFile("ANEPRMNT.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        }

        if (gElum)
        {
            if (gElum->mRespawnOnDead)
            {
                field_104_pending_resource_count++;
                ResourceManager::LoadResourceFile("ELMPRMNT.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

                if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElmaloneAOResID_230, 0, 0))
                {
                    field_104_pending_resource_count++;
                    ResourceManager::LoadResourceFile("ELMALONE.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
                }
            }
        }

        field_104_pending_resource_count++;
        ResourceManager::LoadResourceFile("ABENOELM.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 0, 0))
        {
            field_104_pending_resource_count++;
            ResourceManager::LoadResourceFile("ABEOMM.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        }
    }
}

void Abe::ToDeathDropFall_42C3D0()
{
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit6_bShrivel);
    mCurrentMotion = eAbeMotions::Motion_59_DeathDropFall_42CBE0;
    field_114_gnFrame = 0;
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 1, 0);
}

bool Abe::IsStanding_41FC10()
{
    return mCurrentMotion == eAbeMotions::Motion_0_Idle_423520
        || mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_423F90
        || mCurrentMotion == eAbeMotions::Motion_27_RunSlideStop_425B60
        || mCurrentMotion == eAbeMotions::Motion_28_RunTurn_425CE0
        || mCurrentMotion == eAbeMotions::Motion_35_RunLoop_425060
        || mCurrentMotion == eAbeMotions::Motion_2_StandingTurn_426040
        || mCurrentMotion == eAbeMotions::Motion_36_DunnoBegin_423260
        || mCurrentMotion == eAbeMotions::Motion_37_DunnoMid_4232C0
        || mCurrentMotion == eAbeMotions::Motion_38_DunnoEnd_423310
        || mCurrentMotion == eAbeMotions::Motion_4_WalkToIdle_4243C0
        || mCurrentMotion == eAbeMotions::Motion_5_MidWalkToIdle_424490
        || mCurrentMotion == eAbeMotions::Motion_6_WalkBegin_424300
        || mCurrentMotion == eAbeMotions::Motion_41_StandingToRun_425530
        || mCurrentMotion == eAbeMotions::Motion_42_SneakLoop_424BB0
        || mCurrentMotion == eAbeMotions::Motion_43_WalkToSneak_424790
        || mCurrentMotion == eAbeMotions::Motion_44_SneakToWalk_4249A0
        || mCurrentMotion == eAbeMotions::Motion_45_MidWalkToSneak_424890
        || mCurrentMotion == eAbeMotions::Motion_46_MidSneakToWalk_424AA0
        || mCurrentMotion == eAbeMotions::Motion_47_SneakBegin_424ED0
        || mCurrentMotion == eAbeMotions::Motion_48_SneakToIdle_424F80
        || mCurrentMotion == eAbeMotions::Motion_49_MidSneakToIdle_424FF0
        || mCurrentMotion == eAbeMotions::Motion_50_WalkToRun_424560
        || mCurrentMotion == eAbeMotions::Motion_51_MidWalkToRun_424670
        || mCurrentMotion == eAbeMotions::Motion_52_RunToWalk_4255E0
        || mCurrentMotion == eAbeMotions::Motion_53_MidRunToWalk_4256E0
        || mCurrentMotion == eAbeMotions::Motion_54_RunTurnToRun_425EA0
        || mCurrentMotion == eAbeMotions::Motion_55_RunTurnToWalk_425F70
        || mCurrentMotion == eAbeMotions::Motion_58_ToSpeak_42F8D0
        || mCurrentMotion == eAbeMotions::Motion_7_Speak_42F950
        || mCurrentMotion == eAbeMotions::Motion_8_Speak_42F9D0
        || mCurrentMotion == eAbeMotions::Motion_9_Speak_42FA50
        || mCurrentMotion == eAbeMotions::Motion_10_Speak_42FAD0
        || mCurrentMotion == eAbeMotions::Motion_11_Speak_42FB50
        || mCurrentMotion == eAbeMotions::Motion_12_Speak_42FBD0
        || mCurrentMotion == eAbeMotions::Motion_13_Speak_42FC50
        || mCurrentMotion == eAbeMotions::Motion_14_Speak_42FCD0
        || mCurrentMotion == eAbeMotions::Motion_101_LeverUse_429970
        || mCurrentMotion == eAbeMotions::Motion_140_BeesStruggling_423F30
        || mCurrentMotion == eAbeMotions::Motion_143_RockThrowStandingThrow_429FD0
        || mCurrentMotion == eAbeMotions::Motion_142_RockThrowStandingHold_429CE0
        || mCurrentMotion == eAbeMotions::Motion_144_RockThrowStandingEnd_429DE0
        || mCurrentMotion == eAbeMotions::Motion_150_Chant_42FD50
        || mCurrentMotion == eAbeMotions::Motion_151_ChantEnd_430530
        || mCurrentMotion == eAbeMotions::Motion_159_Idle_RubEyes_423360
        || mCurrentMotion == eAbeMotions::Motion_160_Idle_Stretch_Arms_4233A0
        || mCurrentMotion == eAbeMotions::Motion_161_Idle_Yawn_4233E0
        || mCurrentMotion == eAbeMotions::Motion_164_PoisonGasDeath_42A120;
}

void Abe::FollowLift_42EE90()
{
    if (mLiftPoint)
    {
        mVelY = mLiftPoint->mVelY;
        if (mLiftPoint->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
        {
            mLiftPoint->VOnPickUpOrSlapped();
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit1);
        }
        SetActiveCameraDelayedFromDir_401C90();
    }
}

void Abe::ExitShrykull_42F440(s16 bResetRingTimer)
{
    mAnim.mFlags.Set(AnimFlags::eBit2_Animate);
    mAnim.mFlags.Set(AnimFlags::eBit3_Render);

    mCurrentMotion = eAbeMotions::Motion_163_ShrykullEnd_42F520;

    field_108_bMotionChanged = 1;
    field_114_gnFrame = 1;

    if (bResetRingTimer)
    {
        field_168_ring_pulse_timer = 0;
    }
}

s16 Abe::RunTryEnterWell_425880()
{
    if (!Input().IsAnyPressed(sInputKey_Up) || mAnim.mCurrentFrame < 4)
    {
        return 0;
    }

    auto pWellLocal = static_cast<relive::Path_WellLocal*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellLocal));
    if (pWellLocal)
    {
        if ((pWellLocal->mScale == relive::reliveScale::eFull && mSpriteScale == FP_FromInteger(1)) ||
            (pWellLocal->mScale == relive::reliveScale::eHalf && mSpriteScale == FP_FromDouble(0.5)))
        {
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
            BaseAliveGameObjectPathTLV = pWellLocal;
            mCurrentMotion = eAbeMotions::Motion_77_WellBegin_430F10;
            return 1;
        }
    }

    auto pWellExpress = static_cast<relive::Path_WellExpress*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellExpress));
    if (pWellExpress)
    {
        if ((pWellExpress->mScale == relive::reliveScale::eFull && mSpriteScale == FP_FromInteger(1)) ||
            (pWellExpress->mScale == relive::reliveScale::eHalf && mSpriteScale == FP_FromDouble(0.5)))
        {
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
            BaseAliveGameObjectPathTLV = pWellExpress;
            mCurrentMotion = eAbeMotions::Motion_80_430EF0;
        }
    }

    return 0;
}

void Abe::ChangeChantState_430510(s16 bKeepChanting)
{
    if (bKeepChanting)
    {
        field_110_state.chant = ChantStates::eChantingForBirdPortal_6;
    }
    else
    {
        field_110_state.chant = ChantStates::eIdleChanting_0;
    }
}

BaseAliveGameObject* Abe::FindObjectToPossess_421410()
{
    for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
    {
        BaseAliveGameObject* pObj = gBaseAliveGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            if (pObj->mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit1_Can_Be_Possessed))
            {
                if (pObj->mBaseGameObjectTypeId != ReliveTypes::eSlig || (pObj->Is_In_Current_Camera() == CameraPos::eCamCurrent_0 && pObj->mHealth > FP_FromInteger(0)))
                {
                    return pObj;
                }
            }
        }
    }
    return nullptr;
}

void Abe::Get_Shrykull_Resources_42F480()
{
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 1, 0);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 1, 0);
    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 1, 0);
}

void Abe::ToDieFinal_42C400()
{
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit6_bShrivel);
    mCurrentMotion = eAbeMotions::Motion_60_Dead_42C4C0;
    field_114_gnFrame = 0;
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_14, this, 1, 0);
}

void Abe::ToKnockback_422D90(s16 bKnockbackSound, s16 bDelayedAnger)
{
    if (sControlledCharacter->mBaseGameObjectTypeId != ReliveTypes::eSlig || mHealth <= FP_FromInteger(0))
    {
        SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit3_ElumMountBegin);
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit4_ElumMountEnd);
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);

        if (field_188_pOrbWhirlWind)
        {
            field_188_pOrbWhirlWind->ToStop();
            field_188_pOrbWhirlWind = nullptr;
        }

        if (mVelX != FP_FromInteger(0))
        {
            mXPos -= mVelX;
        }

        MapFollowMe_401D30(1);

        mVelX = FP_FromInteger(0);
        if (mVelY < FP_FromInteger(0))
        {
            mVelY = FP_FromInteger(0);
        }

        field_114_gnFrame = sGnFrame + 10;

        if (bKnockbackSound)
        {
            Mudokon_SFX(MudSounds::eKnockbackOuch_10, 0, Math_RandomRange(-127, 127), this);
            Environment_SFX_42A220(EnvironmentSfx::eKnockback_13, 0, 0x7FFF, this);
        }

        if (!field_1A4_resources.res[0] && !field_104_pending_resource_count)
        {
            sControlledCharacter = this;
            BaseAliveGameObjectLastLineYPos = mYPos;
            BaseAliveGameObjectCollisionLine = nullptr;
            mYPos -= (mSpriteScale * FP_FromInteger(20));
            VOnTrapDoorOpen();
            FreeElumRes_420F80();
        }

        mCurrentMotion = eAbeMotions::Motion_70_Knockback_428FB0;

        if (bDelayedAnger)
        {
            field_130_say = 5;
            field_134_auto_say_timer = sGnFrame + 27;
        }

        if (field_198_pThrowable)
        {
            field_198_pThrowable->VToDead();
            field_198_pThrowable = nullptr;
            if (gInfiniteGrenades_5076EC == 0)
            {
                field_19C_throwable_count++;
            }
        }
    }
}

u8** Abe::StateToAnimResource_4204F0(s16 motion)
{
    s16 res_idx = 0;

    if (motion < eAbeMotions::Motion_15_Null_42A210)
    {
        res_idx = 45;
    }
    else if (motion < eAbeMotions::Motion_64_LedgeAscend_428B60)
    {
        res_idx = 0;
    }
    else if (motion < eAbeMotions::Motion_70_Knockback_428FB0)
    {
        res_idx = 32;
    }
    else if (motion < eAbeMotions::Motion_74_JumpIntoWell_430EC0)
    {
        res_idx = 16;
    }
    else if (motion < eAbeMotions::Motion_86_FallLandDie_42EDD0)
    {
        res_idx = 37;
    }
    else if (motion < eAbeMotions::Motion_87_ToFall_428FA0)
    {
        res_idx = 9;
    }
    else if (motion < eAbeMotions::Motion_88_HandstoneBegin_430590)
    {
        res_idx = 10;
    }
    else if (motion < eAbeMotions::Motion_91_FallingFromGrab_429780)
    {
        res_idx = 11;
    }
    else if (motion < eAbeMotions::Motion_101_LeverUse_429970)
    {
        res_idx = 33;
    }
    else if (motion < eAbeMotions::Motion_102_ElumWalkLoop_42DCA0)
    {
        res_idx = 1;
    }
    else if (motion < eAbeMotions::Motion_127_SlapBomb_429A20)
    {
        res_idx = 46;
    }
    else if (motion < eAbeMotions::Motion_128_KnockForward_429330)
    {
        res_idx = 3;
    }
    else if (motion < eAbeMotions::Motion_131_LiftUseUp_42F150)
    {
        res_idx = 17;
    }
    else if (motion < eAbeMotions::Motion_136_ElumMountEnd_42E110)
    {
        res_idx = 43;
    }
    else if (motion < eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0)
    {
        res_idx = 56;
    }
    else if (motion < eAbeMotions::Motion_138_ElumUnmountEnd_42E390)
    {
        res_idx = 58;
    }
    else if (motion < eAbeMotions::Motion_139_ElumMountBegin_42E090)
    {
        res_idx = 59;
    }
    else if (motion < eAbeMotions::Motion_140_BeesStruggling_423F30)
    {
        res_idx = 61;
    }
    else if (motion < eAbeMotions::Motion_142_RockThrowStandingHold_429CE0)
    {
        res_idx = 6;
    }
    else if (motion < eAbeMotions::Motion_147_ShotRolling_4295C0)
    {
        res_idx = 4;
    }
    else if (motion < eAbeMotions::Motion_149_PickupItem_42A030)
    {
        res_idx = 18;
    }
    else if (motion < eAbeMotions::Motion_150_Chant_42FD50)
    {
        res_idx = 2;
    }
    else if (motion < eAbeMotions::Motion_152_ElumFallOffEdge_42E030)
    {
        res_idx = 38;
    }
    else if (motion < eAbeMotions::Motion_156_DoorEnter_42D370)
    {
        res_idx = 54;
    }
    else if (motion < eAbeMotions::Motion_158_ElumKnockback_42E070)
    {
        res_idx = 35;
    }
    else if (motion < eAbeMotions::Motion_159_Idle_RubEyes_423360)
    {
        res_idx = 52;
    }
    else if (motion < eAbeMotions::Motion_160_Idle_Stretch_Arms_4233A0)
    {
        res_idx = 22;
    }
    else if (motion < eAbeMotions::Motion_161_Idle_Yawn_4233E0)
    {
        res_idx = 23;
    }
    else if (motion < eAbeMotions::Motion_162_ToShrykull_42F410)
    {
        res_idx = 21;
    }
    else if (motion >= eAbeMotions::Motion_164_PoisonGasDeath_42A120)
    {
        res_idx = 64;
        if (motion >= 165)
        {
            res_idx = motion;
        }
    }
    else
    {
        res_idx = 63;
    }


    if (res_idx == field_128_resource_idx)
    {
        return field_1A4_resources.res[field_128_resource_idx];
    }

    if (field_128_resource_idx)
    {
        if (field_128_resource_idx != 45 && field_128_resource_idx != 46)
        {
            ResourceManager::FreeResource_455550(field_1A4_resources.res[field_128_resource_idx]);
            field_1A4_resources.res[field_128_resource_idx] = nullptr;
        }
    }
    if (res_idx)
    {
        if (res_idx != 45 && res_idx != 46)
        {
            s32 resourceID = res_idx + 10;
            if (res_idx >= 46)
            {
                resourceID = res_idx + 54;
            }

            u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, resourceID, 1, 0);
            if (!ppRes)
            {
                LOG_ERROR("Abe resource failed to load " << resourceID);
            }
            field_1A4_resources.res[res_idx] = ppRes;
        }
    }
    field_128_resource_idx = res_idx;
    return field_1A4_resources.res[res_idx];
}

void Abe::ToIdle_422D50()
{
    field_120_x_vel_slow_by = FP_FromInteger(0);
    mVelX = FP_FromInteger(0);
    mVelY = FP_FromInteger(0);
    field_114_gnFrame = sGnFrame;
    mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
    field_10C_prev_held = 0;
    field_10E_released_buttons = 0;
}

void Abe::MoveForward_422FC0()
{
    FollowLift_42EE90();

    const FP old_x = mXPos;

    if (BaseAliveGameObjectCollisionLine)
    {
        BaseAliveGameObjectCollisionLine = BaseAliveGameObjectCollisionLine->MoveOnLine(
            &mXPos,
            &mYPos,
            mVelX);
    }

    // TODO: Check mask is correct
    const s32 mask = mSpriteScale != FP_FromDouble(0.5) ? 1 : 0x10;
    if (BaseAliveGameObjectCollisionLine && (mask & (1 << BaseAliveGameObjectCollisionLine->mLineType)))
    {
        if (mLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->mLineType != eLineTypes ::eDynamicCollision_32 &&
                BaseAliveGameObjectCollisionLine->mLineType != eLineTypes::eBackgroundDynamicCollision_36)
            {
                mLiftPoint->VRemove(this);
                mLiftPoint->mBaseGameObjectRefCount--;
                mLiftPoint = nullptr;
            }
        }
        else if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 ||
                BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
        {
            PSX_RECT bRect = VGetBoundingRect();
            bRect.y += 5;
            bRect.h += 5;
            bRect.w += 5; // TODO: Seems wrong - same in AE

            VOnCollisionWith(
                {bRect.x, bRect.y},
                {bRect.w, bRect.h},
                ObjListPlatforms_50766C,
                1,
                (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
        }
    }
    else
    {
        BaseAliveGameObjectCollisionLine = nullptr;

        if (mLiftPoint)
        {
            mLiftPoint->VRemove(this);
            mLiftPoint->mBaseGameObjectRefCount--;
            mLiftPoint = nullptr;
        }

        field_10C_prev_held = 0;
        switch (mCurrentMotion)
        {
            case eAbeMotions::Motion_1_WalkLoop_423F90:
            case eAbeMotions::Motion_6_WalkBegin_424300:
            case eAbeMotions::Motion_4_WalkToIdle_4243C0:
            case eAbeMotions::Motion_5_MidWalkToIdle_424490:
                mCurrentMotion = eAbeMotions::Motion_93_WalkOffEdge_429840;
                break;

            case eAbeMotions::Motion_35_RunLoop_425060:
            case eAbeMotions::Motion_41_StandingToRun_425530:
                mCurrentMotion = eAbeMotions::Motion_94_RunOffEdge_429860;
                break;

            case eAbeMotions::Motion_40_RunToRoll_427AE0:
            case eAbeMotions::Motion_24_RollBegin_427A20:
            case eAbeMotions::Motion_25_RollLoop_427BB0:
            case eAbeMotions::Motion_26_RollEnd_427EA0:
                mCurrentMotion = eAbeMotions::Motion_100_RollOffLedge_429950;
                break;

            default:
                mCurrentMotion = eAbeMotions::Motion_95_SneakOffEdge_429880;
                break;
        }

        mXPos = old_x + mVelX;
        BaseAliveGameObjectLastLineYPos = mYPos;

        // TODO: OG bug, dead code due to switch default case ?
        if (mCurrentMotion == eAbeMotions::Motion_70_Knockback_428FB0 || mCurrentMotion == eAbeMotions::Motion_128_KnockForward_429330)
        {
            field_120_x_vel_slow_by = FP_FromDouble(0.67); // TODO: Check
        }
    }
}

void Abe::ElumFree_4228F0()
{
    if (field_2AA_flags.Get(Flags_2AA::e2AA_Bit4_ElumMountEnd))
    {
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumUnknownAOResID_110, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumAneMountAOResID_223, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElmprmntAOResID__222, 0, 0));

        if (gElum->mCurrentMotion != eElumMotions::Motion_1_Idle_412990)
        {
            gElum->Vsub_416120();
        }
    }

    if (field_2AA_flags.Get(Flags_2AA::e2AA_Bit4_ElumMountEnd))
    {
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeWElmAOResID_100, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumUnknownAOResID_112, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumRideAOResID_220, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumPdmntAOResID_221, 1, 0));
    }

    if (field_2AA_flags.Get(Flags_2AA::e2AA_Bit5_ElumUnmountBegin))
    {
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeANEDSMNTAOResID_113, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumANEDSMNTAOResID_224, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumPdmntAOResID_221, 0, 0));

        if (gElum->mCurrentMotion != eElumMotions::Motion_1_Idle_412990)
        {
            gElum->Vsub_416120();
        }
    }
}

s16 Abe::DoGameSpeak_42F5C0(u16 input)
{
    if (Input_IsChanting())
    {
        field_114_gnFrame = sGnFrame + 90;
        SND_SEQ_PlaySeq_4775A0(SeqId::eMudokonChant1_11, 0, 1);
        field_110_state.chant = ChantStates::eIdleChanting_0;
        return eAbeMotions::Motion_150_Chant_42FD50;
    }

#if ORIGINAL_PS1_BEHAVIOR // OG Change - Faster check for GameSpeak
    const bool leftGameSpeakPressed = (input & eLeftGamespeak);
    const bool rightGameSpeakPressed = (input & eRightGameSpeak);
#else
    const bool leftGameSpeakPressed = Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler);
    const bool rightGameSpeakPressed = Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler);
#endif

    if (leftGameSpeakPressed)
    {
        if (input & sInputKey_GameSpeak2)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFollowMe_10);
            Mudokon_SFX(MudSounds::eFollowMe_4, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_14_Speak_42FCD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_14_Speak_42FCD0;
        }
        if (input & sInputKey_GameSpeak4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWait_12);
            Mudokon_SFX(MudSounds::eWait_6, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_14_Speak_42FCD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_13_Speak_42FC50;
        }
        if (input & sInputKey_GameSpeak1)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eHello_9);
            Mudokon_SFX(MudSounds::eHello_3, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_9_Speak_42FA50)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_9_Speak_42FA50;
        }
        if (input & sInputKey_GameSpeak3)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eAnger_11);
            Mudokon_SFX(MudSounds::eAngry_5, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_10_Speak_42FAD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_10_Speak_42FAD0;
        }
    }

    if (rightGameSpeakPressed)
    {
        if (input & sInputKey_GameSpeak6)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleHigh_1);
            Mudokon_SFX(MudSounds::eWhistleHigh_1, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_9_Speak_42FA50)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_9_Speak_42FA50;
        }
        if (input & sInputKey_GameSpeak5)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleLow_2);
            Mudokon_SFX(MudSounds::eWhistleLow_2, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_8_Speak_42F9D0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_8_Speak_42F9D0;
        }
        if (input & sInputKey_GameSpeak8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eLaugh_4);
            Mudokon_SFX(MudSounds::eLaugh1_8, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_12_Speak_42FBD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_12_Speak_42FBD0;
        }
        if (input & sInputKey_GameSpeak7)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFart_3);
            Mudokon_SFX(MudSounds::eFart_7, 0, 0, this);
            if (sEnableFartGasCheat_507704)
            {
                FP xPos = mXPos;
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    xPos += (FP_FromInteger(12) * mSpriteScale);
                }
                else
                {
                    xPos -= (FP_FromInteger(12) * mSpriteScale);
                }
                New_Smoke_Particles_419A80(
                    xPos,
                    mYPos - (FP_FromInteger(24) * mSpriteScale),
                    FP_FromDouble(0.5) * mSpriteScale,
                    3,
                    1);
            }
            field_130_say = 8;
            field_134_auto_say_timer = sGnFrame + 15;
            if (mCurrentMotion == eAbeMotions::Motion_10_Speak_42FAD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_10_Speak_42FAD0;
        }
    }
    return -1;
}

void Abe::SyncToElum_42D850(s16 elumMotion)
{
    if (mCurrentMotion != eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0 && mCurrentMotion != eAbeMotions::Motion_138_ElumUnmountEnd_42E390)
    {
        switch (elumMotion)
        {
            case eElumMotions::Motion_1_Idle_412990:
                mCurrentMotion = eAbeMotions::Motion_103_ElumIdle_42DCD0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_3_WalkLoop_412C90:
                mCurrentMotion = eAbeMotions::Motion_102_ElumWalkLoop_42DCA0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_4_Turn_4140F0:
                mCurrentMotion = eAbeMotions::Motion_113_ElumTurn_42DF90;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_5_WalkToIdle_4132D0:
                mCurrentMotion = eAbeMotions::Motion_124_ElumWalkEnd_42DCB0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_6_MidWalkToIdle_4133F0:
                mCurrentMotion = eAbeMotions::Motion_125_ElumMidWalkEnd_42DCC0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_7_IdleToWalk1_413200:
                mCurrentMotion = eAbeMotions::Motion_116_Null_42DFB0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_8_IdleToWalk2_413270:
                mCurrentMotion = eAbeMotions::Motion_117_ElumWalkBegin_42DFC0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_12_RunTurn_414520:
                mCurrentMotion = eAbeMotions::Motion_105_ElumRunTurn_42DF10;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_13_RunTurnToWalk_4147C0:
                mCurrentMotion = eAbeMotions::Motion_123_ElumRunTurnToWalk_42E020;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_21_Land_414A20:
                mCurrentMotion = eAbeMotions::Motion_153_ElumFall_42E040;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_22_RunOffEdge_415810:
                mCurrentMotion = eAbeMotions::Motion_154_ElumLand_42E050;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_23_WalkOffEdge_415E90:
                mCurrentMotion = eAbeMotions::Motion_152_ElumFallOffEdge_42E030;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_24_JumpToFall_415ED0:
                mCurrentMotion = eAbeMotions::Motion_155_ElumJumpToFall_42E060;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_30_HopBegin_414E30:
                mCurrentMotion = eAbeMotions::Motion_107_ElumHopBegin_42DF30;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_31_HopMid_414C70:
                mCurrentMotion = eAbeMotions::Motion_108_ElumHopMid_42DF40;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_32_HopLand_415140:
                mCurrentMotion = eAbeMotions::Motion_109_ElumHopLand_42DF50;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_33_RunJumpBegin_415400:
                mCurrentMotion = eAbeMotions::Motion_110_ElumRunJumpBegin_42DF60;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_34_RunJumpMid_415240:
                mCurrentMotion = eAbeMotions::Motion_111_ElumRunJumpMid_42DF70;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_35_RunJumpLand_415580:
                mCurrentMotion = eAbeMotions::Motion_112_ElumRunJumpLand_42DF80;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_36_RunLoop_413720:
                mCurrentMotion = eAbeMotions::Motion_114_ElumRunLoop_42DFA0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_37_RunSlideStop_4142E0:
                mCurrentMotion = eAbeMotions::Motion_104_ElumRunSlideStop_42DF00;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_38_RunTurnToRun_414810:
                mCurrentMotion = eAbeMotions::Motion_122_ElumRunTurnToRun_42E010;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_39_IdleToRun_413B00:
                mCurrentMotion = eAbeMotions::Motion_118_ElumRunBegin_42DFD0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_40_WalkToRun_4134B0:
                mCurrentMotion = eAbeMotions::Motion_119_Null_42DFE0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_41_MidWalkToRun_413560:
                mCurrentMotion = eAbeMotions::Motion_120_ElumRunToWalk_42DFF0;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_43_MidRunToWalk_413E20:
                mCurrentMotion = eAbeMotions::Motion_121_ElumMidRunToWalk_42E000;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            case eElumMotions::Motion_50_Knockback_415DC0:
                mCurrentMotion = eAbeMotions::Motion_158_ElumKnockback_42E070;
                ToNewElumSyncMotion_422520(gElum->mAnim.mCurrentFrame);
                break;

            default:
                break;
        }
    }
}

void Abe::PickUpThrowabe_Or_PressBomb_428260(FP fpX, s32 fpY, s16 bStandToCrouch)
{
    BaseAliveGameObject* pSlapableOrCollectable = nullptr;
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
                    pSlapableOrCollectable = pAliveObj;
                    pSlapableOrCollectable->mBaseGameObjectRefCount++;
                    field_15C_pThrowable = static_cast<BaseThrowable*>(pSlapableOrCollectable);
                    break;
                }
            }
        }
    }


    if (pSlapableOrCollectable)
    {
        bool tryToSlapOrCollect = false;

        switch (pSlapableOrCollectable->mBaseGameObjectTypeId)
        {
            case ReliveTypes::eTimedMine:
            case ReliveTypes::eUXB:
                mCurrentMotion = eAbeMotions::Motion_127_SlapBomb_429A20;
                if (bStandToCrouch)
                {
                    field_15C_pThrowable->mBaseGameObjectRefCount--;
                    field_15C_pThrowable = nullptr;
                }
                tryToSlapOrCollect = true;
                break;

            case ReliveTypes::eGrenade:
            case ReliveTypes::eMeat:
            case ReliveTypes::eRock:
                mCurrentMotion = eAbeMotions::Motion_149_PickupItem_42A030;
                field_19C_throwable_count += static_cast<s8>(field_15C_pThrowable->VGetCount());

                if (!bThrowableIndicatorExists_504C70)
                {
                    const FP v16 = (mSpriteScale * FP_FromInteger(-30)) + mYPos;
                    relive_new ThrowableTotalIndicator(
                                                                          (mSpriteScale * FP_FromInteger(0)) + mXPos,
                                                                               v16,
                                                                               mAnim.mRenderLayer,
                                                                               mAnim.field_14_scale,
                                                                               field_19C_throwable_count,
                                                                               1);
                }
                tryToSlapOrCollect = true;
                break;

            case ReliveTypes::eMine:
                field_15C_pThrowable->mBaseGameObjectRefCount--;
                field_15C_pThrowable = nullptr;
                tryToSlapOrCollect = true;
                break;

            default:
                return;
        }

        if (tryToSlapOrCollect)
        {
            if (mCurrentMotion == eAbeMotions::Motion_149_PickupItem_42A030)
            {
                if (bStandToCrouch)
                {
                    SfxPlayMono(SoundEffect::PickupItem_33, 0, this);
                    field_15C_pThrowable->mBaseGameObjectRefCount--;
                    field_15C_pThrowable->VOnPickUpOrSlapped();
                    field_15C_pThrowable = nullptr;
                    mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
                }
            }
        }
    }
}

void Abe::CrouchingGameSpeak_427F90()
{
    field_10C_prev_held |= Input().Held();

    if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler))
    {
        if (field_10C_prev_held & sInputKey_GameSpeak2)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFollowMe_10);
            Mudokon_SFX(MudSounds::eFollowMe_4, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWait_12);
            Mudokon_SFX(MudSounds::eWait_6, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak1)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eHello_9);
            Mudokon_SFX(MudSounds::eHello_3, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak3)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eAnger_11);
            Mudokon_SFX(MudSounds::eAngry_5, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
    }
    else if (Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler))
    {
        if (field_10C_prev_held & sInputKey_GameSpeak6)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleHigh_1);
            Mudokon_SFX(MudSounds::eWhistleHigh_1, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak5)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleLow_2);
            Mudokon_SFX(MudSounds::eWhistleLow_2, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eLaugh_4);
            Mudokon_SFX(MudSounds::eLaugh1_8, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak7)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFart_3);
            Mudokon_SFX(MudSounds::eFart_7, 0, 0, this);
            if (sEnableFartGasCheat_507704)
            {
                FP xPos = {};
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    xPos = mXPos + FP_FromDouble(10) * mSpriteScale;
                }
                else
                {
                    xPos = mXPos - FP_FromDouble(10) * mSpriteScale;
                }
                New_Smoke_Particles_419A80(
                    xPos,
                    mYPos - FP_FromDouble(6) * mSpriteScale,
                    mSpriteScale * FP_FromDouble(0.5),
                    3,
                    1);
            }
            field_130_say = 8;
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
            field_134_auto_say_timer = sGnFrame + 15;
        }
    }
}

void Abe::FallOnBombs_4231B0()
{
    const PSX_RECT bOurRect = VGetBoundingRect();
    for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
    {
        BaseAliveGameObject* pObjIter = gBaseAliveGameObjects->ItemAt(i);
        if (!pObjIter)
        {
            break;
        }

        if (pObjIter->mBaseGameObjectTypeId == ReliveTypes::eMine || pObjIter->mBaseGameObjectTypeId == ReliveTypes::eUXB)
        {
            const PSX_RECT objRect = pObjIter->VGetBoundingRect();
            if (bOurRect.x <= objRect.w
                && bOurRect.w >= objRect.x
                && bOurRect.h >= objRect.y
                && bOurRect.y <= objRect.h)
            {
                pObjIter->VTakeDamage(this);
            }
        }
    }
}

s16 Abe::ToLeftRightMovement_422AA0()
{
    mVelY = FP_FromInteger(0);
    if (sControlledCharacter != this)
    {
        return 0;
    }

    const FP gridSize = ScaleToGridSize(mSpriteScale);
    const bool flipX = mAnim.mFlags.Get(AnimFlags::eBit5_FlipX);

    if ((flipX && Input().IsAnyPressed(sInputKey_Right)) || (!flipX && Input().IsAnyPressed(sInputKey_Left)))
    {
        mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
        return 1;
    }

    if (Input().IsAnyPressed(sInputKey_Right) || Input().IsAnyPressed(sInputKey_Left))
    {
        const FP directionX = FP_FromInteger(Input().IsAnyPressed(sInputKey_Right) ? 1 : -1);

        if (Input().IsAnyPressed(sInputKey_Run))
        {
            mVelX = directionX * (gridSize / FP_FromInteger(4));
            mCurrentMotion = eAbeMotions::Motion_41_StandingToRun_425530;
        }
        else if (Input().IsAnyPressed(sInputKey_Sneak))
        {
            mVelX = directionX * (gridSize / FP_FromInteger(10));
            mCurrentMotion = eAbeMotions::Motion_47_SneakBegin_424ED0;
        }
        else
        {
            mVelX = directionX * (gridSize / FP_FromInteger(9));
            mCurrentMotion = eAbeMotions::Motion_6_WalkBegin_424300;
        }

        if (!WallHit_401930(mSpriteScale * FP_FromInteger(50), directionX * gridSize))
        {
            if (!WallHit_401930(mSpriteScale * FP_FromInteger(20), directionX * gridSize))
            {
                return 1;
            }
        }

        if (WallHit_401930(mSpriteScale * FP_FromInteger(20), directionX * gridSize))
        {
            mVelX = FP_FromInteger(0);
            mCurrentMotion = eAbeMotions::Motion_72_PushWall_4292A0;
            Environment_SFX_42A220(EnvironmentSfx::eGenericMovement_9, 0, 0x7FFF, this);
            return 0;
        }

        mCurrentMotion = eAbeMotions::Motion_21_StandToCrouch_427F40;
        return 1;
    }

    return 0;
}


void Abe::MoveWithVelocity_4257F0(FP speed)
{
    if (mVelX > FP_FromInteger(0))
    {
        mVelX = mVelX - (mSpriteScale * speed);
        if (mVelX < FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }
    else if (mVelX < FP_FromInteger(0))
    {
        mVelX = (mSpriteScale * speed) + mVelX;
        if (mVelX > FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }

    if (FP_GetExponent(mVelX))
    {
        MoveForward_422FC0();
    }
}

void Abe::ToNewElumSyncMotion_422520(s16 elum_frame)
{
    mAnim.Set_Animation_Data(
        sAbeMotionAnimIds[mCurrentMotion],
        StateToAnimResource_4204F0(mCurrentMotion));

    field_12C_timer = sGnFrame;
    mAnim.SetFrame(elum_frame + 1);
    mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, gElum->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX));
}

void Abe::SetActiveControlledCharacter_421480()
{
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit7);
    sControlledCharacter = this;
}

PullRingRope* Abe::GetPullRope_422580()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectTypeId == ReliveTypes::ePullRingRope)
        {
            PullRingRope* pRope = static_cast<PullRingRope*>(pObj);

            const PSX_RECT bRect = pRope->VGetBoundingRect();
            if ((mYPos - pRope->mYPos - (mSpriteScale * FP_FromInteger(80))) <= FP_FromInteger(0))
            {
                if (mXPos > FP_FromInteger(bRect.x) && mXPos < FP_FromInteger(bRect.w))
                {
                    return pRope;
                }
            }
        }
    }
    return nullptr;
}

void Abe::Free_Resources_422870()
{
    if (field_1A4_resources.res[0])
    {
        ResourceManager::FreeResource_455550(field_1A4_resources.res[0]);
        field_1A4_resources.res[0] = nullptr;
    }
}

void Abe::Load_Basic_Resources_4228A0()
{
    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 0, 0) && !ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEBSIC.BAN", nullptr);
        ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
    }
}

void Abe::LoadMountElumResources_42E690()
{
    ResourceManager::FreeResource_455550(field_1A4_resources.res[0]);
    field_1A4_resources.res[0] = nullptr;

    field_1A4_resources.res[10] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 0, 0);
    ResourceManager::FreeResource_455550(field_1A4_resources.res[10]);
    field_1A4_resources.res[10] = nullptr;

    field_1A4_resources.res[38] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 0, 0);
    ResourceManager::FreeResource_455550(field_1A4_resources.res[38]);
    field_1A4_resources.res[38] = nullptr;

    field_1A4_resources.res[9] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 0, 0);
    ResourceManager::FreeResource_455550(field_1A4_resources.res[9]);
    field_1A4_resources.res[9] = nullptr;

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_455270("ANEPRMNT.BAN", nullptr);
        field_1A4_resources.res[61] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
    }

    field_104_pending_resource_count++;
    ResourceManager::LoadResourceFile("ANEMOUNT.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
}

void Abe::ElumKnockForward_42E780(s32 /*not_used*/)
{
    ToKnockback_422D90(1, 1);
    mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
    mNextMotion = eAbeMotions::Motion_0_Idle_423520;
    field_108_bMotionChanged = 1;
    mAnim.Set_Animation_Data(
        sAbeMotionAnimIds[mCurrentMotion],
        StateToAnimResource_4204F0(eAbeMotions::Motion_128_KnockForward_429330));

    sControlledCharacter = sActiveHero;
    gElum->field_154_bAbeForcedDownFromElum = 1;
}

s16 Abe::TryMountElum_42E600()
{
    if (gElum)
    {
        if (FP_Abs(mXPos - gElum->mXPos) <= FP_FromInteger(2) && FP_Abs(mYPos - gElum->mYPos) <= FP_FromInteger(2))
        {
            if (gElum->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mNextMotion = eAbeMotions::Motion_139_ElumMountBegin_42E090;
                return eAbeMotions::Motion_2_StandingTurn_426040;
            }

            if (gElum->mCurrentMotion != eElumMotions::Motion_1_Idle_412990
                || gElum->field_128_brain_idx == 1
                || gElum->field_170_flags.Get(Elum::Flags_170::eStrugglingWithBees_Bit1))
            {
                return eAbeMotions::Motion_0_Idle_423520;
            }

            LoadMountElumResources_42E690();
            return eAbeMotions::Motion_139_ElumMountBegin_42E090;
        }
    }
    return eAbeMotions::Motion_0_Idle_423520;
}

void Abe::BulletDamage_4220B0(Bullet* pBullet)
{
    const PSX_RECT rect = VGetBoundingRect();

    enum class ShootKind
    {
        eEverythingElse_0 = 0,
        eHanging_1 = 1,
        eRolling_2 = 2,
    };

    if (mCurrentMotion == eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0
        || mCurrentMotion == eAbeMotions::Motion_136_ElumMountEnd_42E110
        || mCurrentMotion == eAbeMotions::Motion_138_ElumUnmountEnd_42E390
        || mCurrentMotion == eAbeMotions::Motion_139_ElumMountBegin_42E090
        || !gMap.Is_Point_In_Current_Camera(
            mCurrentLevel,
            mCurrentPath,
            mXPos,
            mYPos,
            1)
        || mHealth <= FP_FromInteger(0))
    {
        return;
    }

    ShootKind shootKind = ShootKind::eEverythingElse_0;
    if (mCurrentMotion == eAbeMotions::Motion_24_RollBegin_427A20
        || mCurrentMotion == eAbeMotions::Motion_25_RollLoop_427BB0
        || mCurrentMotion == eAbeMotions::Motion_26_RollEnd_427EA0
        || mCurrentMotion == eAbeMotions::Motion_39_CrouchTurn_4288C0
        || mCurrentMotion == eAbeMotions::Motion_19_CrouchIdle_4284C0)
    {
        shootKind = ShootKind::eRolling_2;
    }
    else if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
             || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
             || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
             || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
             || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
    {
        shootKind = ShootKind::eHanging_1;
    }

    mHealth = FP_FromInteger(0);
    field_106_shot = 1;

    switch (pBullet->mBulletType)
    {
        case BulletType::ePossessedSlig_0:
        case BulletType::eNormalBullet_1:
        {
            FP bloodXOff = {};
            if (pBullet->mXDistance > FP_FromInteger(0))
            {
                bloodXOff = FP_FromInteger(-24);
            }
            else
            {
                bloodXOff = FP_FromInteger(24);
            }

            relive_new Blood(
                mXPos,
                pBullet->mYPos,
                bloodXOff,
                FP_FromInteger(0),
                mSpriteScale,
                50);

            switch (shootKind)
            {
                case ShootKind::eEverythingElse_0:
                {
                    if (field_1A4_resources.res[0])
                    {
                        ToKnockback_422D90(1, 1);
                    }
                    else
                    {
                        ElumKnockForward_42E780(1);
                    }
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != (pBullet->mXDistance > FP_FromInteger(0)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;

                    if (pBullet->mXDistance >= FP_FromInteger(0))
                    {
                        mVelX = mSpriteScale * FP_FromDouble(7.8);
                    }
                    else
                    {
                        mVelX = -mSpriteScale * FP_FromDouble(7.8);
                    }
                    break;
                }
                case ShootKind::eHanging_1:
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    break;
                }
                case ShootKind::eRolling_2:
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) == (pBullet->mXDistance > FP_FromInteger(0)))
                    {
                        mNextMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
                    }
                    else
                    {
                        mNextMotion = eAbeMotions::Motion_129_RollingKnockForward_4294F0;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case BulletType::eZBullet_2:
        {
            if (mSpriteScale == FP_FromDouble(0.5))
            {
                field_106_shot = 0;
                mHealth = FP_FromInteger(1);
                return;
            }
            if (Bullet::InZBulletCover(FP_FromInteger(rect.x), FP_FromInteger(rect.y), rect))
            {
                field_106_shot = 0;
                mHealth = FP_FromInteger(1);
                return;
            }
            if (shootKind != ShootKind::eEverythingElse_0)
            {
                if (shootKind == ShootKind::eHanging_1)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                }
                else if (shootKind == ShootKind::eRolling_2)
                {
                    mNextMotion = eAbeMotions::Motion_147_ShotRolling_4295C0;
                }
            }
            if (mCurrentMotion != eAbeMotions::Motion_114_ElumRunLoop_42DFA0)
            {
                if (field_1A4_resources.res[0])
                {
                    mNextMotion = eAbeMotions::Motion_148_Shot_4296A0;
                }
                else
                {
                    ElumKnockForward_42E780(1);
                    mCurrentMotion = eAbeMotions::Motion_148_Shot_4296A0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                }
            }

            if (mCurrentMotion != eAbeMotions::Motion_114_ElumRunLoop_42DFA0 || shootKind != ShootKind::eEverythingElse_0)
            {
                relive_new Blood(
                    mXPos,
                    mYPos - FP_FromInteger(45),
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    FP_FromInteger(1),
                    50);

                break;
            }
        }
        default:
            break;
    }

    if (field_106_shot)
    {
        field_112_prev_motion = mNextMotion;
    }

    Environment_SFX_42A220(EnvironmentSfx::eElumHitWall_14, 0, 0x7FFF, this);
    Mudokon_SFX(MudSounds::eKnockbackOuch_10, 127, 0, this);
    Environment_SFX_42A220(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
    SFX_Play_Pitch(SoundEffect::Eating1_79, 0, -500, this);
    SfxPlayMono(SoundEffect::KillEffect_78, 0, this);
}

bool Abe::NearDoorIsOpen()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectTypeId == ReliveTypes::eDoor)
        {
            auto pDoor = static_cast<Door*>(pObj);
            PSX_RECT Rect = VGetBoundingRect();
            PSX_RECT Rect2 = pDoor->VGetBoundingRect();

            if (Rect.x <= Rect2.w && Rect.w >= Rect2.x && Rect.h >= Rect2.y && Rect.y <= Rect2.h)
            {
                return pDoor->vIsOpen_40E800();
            }
        }
    }

    // We didn't find a door - so for some reason that makes no sense return that it is open...
    return TRUE;
}

s16 Abe::RunTryEnterDoor_4259C0()
{
    if (!Input().IsAnyPressed(sInputKey_Up))
    {
        return 0;
    }
    if (mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit5_Electrocuted))
    {
        return 0;
    }
    if (mAnim.mCurrentFrame < 4)
    {
        return 0;
    }

    // Are we actually on a door?
    relive::Path_TLV* pDoorTlv = gMap.TLV_Get_At_446260(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eDoor);

    if (!pDoorTlv)
    {
        return 0;
    }

    if (!NearDoorIsOpen())
    {
        return 0;
    }

    BaseAliveGameObjectPathTLV = pDoorTlv;
    field_110_state.raw = 0;
    mCurrentMotion = eAbeMotions::Motion_156_DoorEnter_42D370;
    mXPos = FP_FromInteger((pDoorTlv->mBottomRightX + pDoorTlv->mTopLeftX) / 2);
    MapFollowMe_401D30(TRUE);
    return 1;
}

s16 Abe::MoveLiftUpOrDown_42F190(FP yVelocity)
{
    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);

    pLiftPoint->Move(FP_FromInteger(0), yVelocity, 0);
    FollowLift_42EE90();

    if (gBeeInstanceCount && gBeesNearAbe)
    {
        return eAbeMotions::Motion_141_BeesStrugglingOnLift_42F390;
    }
    if (sControlledCharacter == this && !mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame) && mAnim.mCurrentFrame != 5)
    {
        return mCurrentMotion;
    }
    if (yVelocity >= FP_FromInteger(0))
    {
        if (yVelocity > FP_FromInteger(0))
        {
            if (pLiftPoint->OnBottomFloor())
            {
                return eAbeMotions::Motion_135_LiftGrabIdle_42F000;
            }
            if (Input().IsAnyPressed(sInputKey_Down))
            {
                return eAbeMotions::Motion_132_LiftUseDown_42F170;
            }
            if (Input().IsAnyPressed(sInputKey_Up))
            {
                return eAbeMotions::Motion_131_LiftUseUp_42F150;
            }
        }
    }
    else
    {
        if (pLiftPoint->OnTopFloor())
        {
            return eAbeMotions::Motion_135_LiftGrabIdle_42F000;
        }
        if (Input().IsAnyPressed(sInputKey_Up))
        {
            return eAbeMotions::Motion_131_LiftUseUp_42F150;
        }
        if (Input().IsAnyPressed(sInputKey_Down))
        {
            return eAbeMotions::Motion_132_LiftUseDown_42F170;
        }
    }

    if (Input().Pressed() && pLiftPoint->OnAnyFloor() && !(pLiftPoint->field_12C_bMoving & 1))
    {
        return eAbeMotions::Motion_134_LiftGrabEnd_42EFE0;
    }

    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);
    return eAbeMotions::Motion_135_LiftGrabIdle_42F000;
}

void Abe::VScreenChanged()
{
    if (sControlledCharacter == this || sControlledCharacter == gElum)
    {
        mCurrentLevel = gMap.mNextLevel;
        mCurrentPath = gMap.mNextPath;
    }

    // Level has changed?
    if (gMap.mCurrentLevel != gMap.mNextLevel)
    {
        // Set the correct tint for this map
        SetTint(sAbeTints_4C6438, gMap.mNextLevel);

        if (gMap.mCurrentLevel != EReliveLevelIds::eMenu)
        {
            if (field_19C_throwable_count > 0)
            {
                if (gpThrowableArray_50E26C)
                {
                    gpThrowableArray_50E26C->Remove(field_19C_throwable_count);
                }
            }

            field_19C_throwable_count = 0;

            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::ResourceType::Resource_Palt, AOResourceID::kAberockAOResID, 0, 0));

            if (field_168_ring_pulse_timer > 0 && field_16C_bHaveShrykull)
            {
                Free_Shrykull_Resources_42F4C0();
            }

            field_168_ring_pulse_timer = 0;
        }

        if (gMap.mNextLevel == EReliveLevelIds::eCredits || gMap.mNextLevel == EReliveLevelIds::eMenu)
        {
            // Remove Abe for menu/credits levels?
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
    }
}



void Abe::VOnTlvCollision(relive::Path_TLV* pTlv)
{
    while (pTlv)
    {
        if (pTlv->mTlvType == ReliveTypes::eContinuePoint)
        {
            relive::Path_ContinuePoint* pContinuePointTlv = static_cast<relive::Path_ContinuePoint*>(pTlv);

            if ((pContinuePointTlv->mZoneNumber != mContinueZoneNumber || mContinueLevel != gMap.mCurrentLevel) && !mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit5_Electrocuted) && mCurrentMotion != eAbeMotions::Motion_156_DoorEnter_42D370)
            {
                mContinueZoneNumber = pContinuePointTlv->mZoneNumber;
                mContinueClearFromId = pContinuePointTlv->mClearFromId;
                mContinueClearToId = pContinuePointTlv->mClearToId;

                mContinueTopLeft.x = pContinuePointTlv->mTopLeftX;
                mContinueTopLeft.y = pContinuePointTlv->mTopLeftY;
                mContinueBottomRight.x = pContinuePointTlv->mBottomRightX;
                mContinueBottomRight.y = pContinuePointTlv->mBottomRightY;
                mContinueSpriteScale = mSpriteScale;

                field_2A8_flags.Set(Flags_2A8::eAbeSpawnDir, pContinuePointTlv->mAbeSpawnDir == relive::Path_ContinuePoint::spawnDirection::eLeft);

                const auto bHaveShry = field_168_ring_pulse_timer - sGnFrame;
                field_150_saved_ring_timer = bHaveShry < 0 ? 0 : bHaveShry;
                field_154_bSavedHaveShrykull = field_16C_bHaveShrykull;

                mContinueLevel = gMap.mCurrentLevel;
                mContinuePath = gMap.mCurrentPath;
                mContinueCamera = gMap.mCurrentCamera;

                if (gRestartRuptureFarmsSavedMuds_5076C8 == 0 && gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn && gMap.mCurrentPath == 19 && gMap.mCurrentCamera == 3)
                {
                    gRestartRuptureFarmsKilledMuds_5076C4 = sKilledMudokons_5076BC;
                    gRestartRuptureFarmsSavedMuds_5076C8 = sRescuedMudokons_5076C0;
                }
                gOldKilledMuds_5076D0 = sKilledMudokons_5076BC;
                gOldSavedMuds_5076D4 = sRescuedMudokons_5076C0;

                SaveGame::SaveToMemory(&gSaveBuffer_505668);

                const FP camXPos = FP_NoFractional(pScreenManager->CamXPos());

                FP indicator_xpos = {};
                if (mXPos - camXPos >= FP_FromInteger(384 / 2)) // mid screen x
                {
                    indicator_xpos = mXPos - ScaleToGridSize(mSpriteScale);
                }
                else
                {
                    indicator_xpos = ScaleToGridSize(mSpriteScale) + mXPos;
                }
                const FP indicator_ypos = mYPos + (mSpriteScale * FP_FromInteger(-50));

                relive_new ThrowableTotalIndicator(indicator_xpos, indicator_ypos, mAnim.mRenderLayer,
                                                                            mAnim.field_14_scale, 11, 1);
            }
        }
        else if (pTlv->mTlvType == ReliveTypes::eDeathDrop)
        {
            Mudokon_SFX(MudSounds::eDeathDropScream_17, 0, 0, this);

            EventBroadcast(kEventNoise, this);
            EventBroadcast(kEventSuspiciousNoise, this);
            EventBroadcast(kEventLoudNoise, this);
            EventBroadcast(kEventSpeaking, this);

            if (!field_1A4_resources.res[0] && sControlledCharacter != this)
            {
                sControlledCharacter = sActiveHero;
                FreeElumRes_420F80();
            }
            ToDeathDropFall_42C3D0();
        }

        // To next TLV
        pTlv = gMap.TLV_Get_At_446060(pTlv, mXPos, mYPos, mXPos, mYPos);
    }
}

s16 Abe::HandleDoAction_429A70()
{
    s16 mountMotion = TryMountElum_42E600();
    if (mountMotion != eAbeMotions::Motion_0_Idle_423520)
    {
        return mountMotion;
    }

    relive::Path_TLV* pTlv = gMap.TLV_Get_At_446060(
        nullptr,
        mXPos,
        mYPos,
        mXPos,
        mYPos);

    while (pTlv)
    {
        switch (pTlv->mTlvType)
        {
            case ReliveTypes::eWellLocal:
                BaseAliveGameObjectPathTLV = pTlv;
                return eAbeMotions::Motion_77_WellBegin_430F10;

            case ReliveTypes::eLever:
                if (FP_FromInteger(FP_GetExponent(mXPos) - pTlv->mTopLeftX) < ScaleToGridSize(mSpriteScale))
                {
                    // Wrong dir
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        return eAbeMotions::Motion_36_DunnoBegin_423260;
                    }

                    // Get switch
                    auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(
                        ReliveTypes::eLever,
                        mXPos + ScaleToGridSize(mSpriteScale),
                        mYPos - FP_FromInteger(5)));

                    // Pull it
                    if (pSwitch)
                    {
                        pSwitch->VPull(mXPos < pSwitch->mXPos);
                        return eAbeMotions::Motion_101_LeverUse_429970;
                    }
                }
                else if (FP_FromInteger(pTlv->mBottomRightX - FP_GetExponent(mXPos)) < ScaleToGridSize(mSpriteScale))
                {
                    // Wrong dir
                    if (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        return eAbeMotions::Motion_36_DunnoBegin_423260;
                    }

                    // Get switch
                    auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(
                        ReliveTypes::eLever,
                        mXPos - ScaleToGridSize(mSpriteScale),
                        mYPos - FP_FromInteger(5)));

                    // Pull it
                    if (pSwitch)
                    {
                        pSwitch->VPull(mXPos < pSwitch->mXPos);
                        return eAbeMotions::Motion_101_LeverUse_429970;
                    }
                }
                break;

            case ReliveTypes::eWellExpress:
                BaseAliveGameObjectPathTLV = pTlv;
                return eAbeMotions::Motion_80_430EF0;

            case ReliveTypes::eBoomMachine:
            {
                auto pBoomMachine = static_cast<BoomMachine*>(FindObjectOfType_418280(
                    ReliveTypes::eBoomMachine,
                    mXPos,
                    mYPos - (mSpriteScale * FP_FromInteger(25))));

                if (pBoomMachine && pBoomMachine->VIsButtonOn())
                {
                    pBoomMachine->VHandleButton();
                    return eAbeMotions::Motion_90_GrenadeMachineUse_430EA0;
                }
                return eAbeMotions::Motion_36_DunnoBegin_423260;
            }

            default:
                break;
        }

        pTlv = gMap.TLV_Get_At_446060(
            pTlv,
            mXPos,
            mYPos,
            mXPos,
            mYPos);
    }
    return eAbeMotions::Motion_36_DunnoBegin_423260;
}

s16 Abe::VTakeDamage(BaseGameObject* pFrom)
{
    SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);

    const auto old_say = field_130_say;
    field_130_say = -1;

    if (field_188_pOrbWhirlWind)
    {
        field_188_pOrbWhirlWind->ToStop();
        field_188_pOrbWhirlWind = nullptr;
    }

    if (field_18C_pObjToPossess)
    {
        field_18C_pObjToPossess->mBaseGameObjectRefCount--;
        field_18C_pObjToPossess = nullptr;
    }

    // CantBeDamaged_44BAB0() helper func in AE
    switch (mCurrentMotion)
    {
        case eAbeMotions::Motion_74_JumpIntoWell_430EC0:
        case eAbeMotions::Motion_75_ToInsideOfAWellLocal_431090:
        case eAbeMotions::Motion_76_ToWellShotOut_431720:
        case eAbeMotions::Motion_77_WellBegin_430F10:
        case eAbeMotions::Motion_78_InsideWellLocal_4310A0:
        case eAbeMotions::Motion_79_WellShotOut_431730:
        case eAbeMotions::Motion_80_430EF0:
        case eAbeMotions::Motion_81_InsideWellExpress_431320:
        case eAbeMotions::Motion_82_WellExpressShotOut_4315A0:
        case eAbeMotions::Motion_83_430F00:
        case eAbeMotions::Motion_84_ToInsideWellLocal_431080:
        case eAbeMotions::Motion_85_ToWellShotOut_431710:
        case eAbeMotions::Motion_156_DoorEnter_42D370:
        case eAbeMotions::Motion_157_DoorExit_42D780:
        case eAbeMotions::Motion_162_ToShrykull_42F410:
        case eAbeMotions::Motion_163_ShrykullEnd_42F520:
            return 0;
    }

    if (gAbeInvulnerableCheat_5076E4 || field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel) || !mAnim.mFlags.Get(AnimFlags::eBit3_Render))
    {
        return 0;
    }

    field_11C_regen_health_timer = sGnFrame + 900;

    auto oldHp = mHealth;

    switch (pFrom->mBaseGameObjectTypeId)
    {
        case ReliveTypes::eBat:
            if (mHealth > FP_FromInteger(0))
            {
                mHealth -= FP_FromInteger(1);
                if (mHealth > FP_FromInteger(0))
                {
                    Mudokon_SFX(MudSounds::eKnockbackOuch_10, 0, 0, this);
                }
                else
                {
                    Mudokon_SFX(MudSounds::eKnockbackOuch_10, 0, 0, this);
                    Environment_SFX_42A220(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
                    mHealth = FP_FromInteger(0);
                    field_106_shot = 1;
                    field_112_prev_motion = eAbeMotions::Motion_128_KnockForward_429330;
                    mNextMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    if (mCurrentMotion != eAbeMotions::Motion_64_LedgeAscend_428B60
                        && mCurrentMotion != eAbeMotions::Motion_66_LedgeHang_428D90
                        && mCurrentMotion != eAbeMotions::Motion_68_LedgeHangWobble_428E50
                        && mCurrentMotion != eAbeMotions::Motion_65_LedgeDescend_428C00
                        && mCurrentMotion != eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                    {
                        break;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                        field_108_bMotionChanged = 1;
                        field_106_shot = 0;
                        field_114_gnFrame = 0;
                        return 1;
                    }
                }
            }
            break;

        case ReliveTypes::eGasCountDown:
            if (mHealth > FP_FromInteger(0))
            {
                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    field_108_bMotionChanged = 1;
                    return 1;
                }

                if (IsStanding_41FC10())
                {
                    mHealth = FP_FromInteger(0);
                    mCurrentMotion = eAbeMotions::Motion_164_PoisonGasDeath_42A120;
                    field_108_bMotionChanged = 1;
                    field_114_gnFrame = 1;
                }
                else
                {
                    if (mCurrentMotion != eAbeMotions::Motion_70_Knockback_428FB0 && mCurrentMotion != eAbeMotions::Motion_71_KnockbackGetUp_429240)
                    {
                        ToKnockback_422D90(1, 1);
                        field_108_bMotionChanged = 1;
                    }
                }
            }
            break;

        case ReliveTypes::eElectricWall:
            Mudokon_SFX(MudSounds::eOops_16, 0, 0, this);
            break;

        case ReliveTypes::eBaseBomb:
        case ReliveTypes::eExplosion:
            if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
            {
                if (mHealth > FP_FromInteger(0))
                {
                    field_106_shot = 1;
                    field_112_prev_motion = eAbeMotions::Motion_70_Knockback_428FB0;
                    mNextMotion = eAbeMotions::Motion_70_Knockback_428FB0;
                }

                mHealth = FP_FromInteger(0);
                mRGB.SetRGB(30, 30, 30);

                relive_new Gibs(
                    GibType::Abe_0,
                    mXPos,
                    mYPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    mSpriteScale);

                mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                mShadow->mFlags.Clear(Shadow::eEnabled);
            }
            break;

        case ReliveTypes::eSecurityClaw:
        case ReliveTypes::eSecurityOrb:
            field_130_say = 5;
            field_134_auto_say_timer = sGnFrame + 27;
            // The zap makes Abe drop his stuff everywhere
            for (s32 i = 0; i < field_19C_throwable_count; i++)
            {
                field_198_pThrowable = Make_Throwable(mXPos, mYPos - FP_FromInteger(30), 0);

                const FP rand1 = FP_FromRaw((Math_NextRandom() - 127) << 11); // TODO: Wat?
                const FP rand2 = (FP_FromDouble(0.03125) * FP_FromRaw(Math_NextRandom())) - FP_FromInteger(2);
                field_198_pThrowable->VThrow(rand1, rand2);
                field_198_pThrowable->mSpriteScale = mSpriteScale;
                field_198_pThrowable->VTimeToExplodeRandom();
                field_198_pThrowable = nullptr;
            }
            field_19C_throwable_count = 0;
            break;

        case ReliveTypes::eRockSpawner:
            if (mHealth > FP_FromInteger(0))
            {
                field_108_bMotionChanged = 1;
                mHealth = FP_FromInteger(0);

                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    return 1;
                }
                ToKnockback_422D90(1, 1);
                SfxPlayMono(SoundEffect::KillEffect_78, 127);
            }
            break;

        case ReliveTypes::eMeatSaw:
            if (mHealth > FP_FromInteger(0))
            {
                field_108_bMotionChanged = 1;
                mHealth = FP_FromInteger(0);
                ToKnockback_422D90(1, 1);
                mRGB.SetRGB(30, 30, 30);

                relive_new Gibs(
                    GibType::Abe_0,
                    mXPos,
                    mYPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    mSpriteScale);

                relive_new Gibs(
                    GibType::Abe_0,
                    mXPos,
                    mYPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    mSpriteScale);

                mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            }
            break;

        case ReliveTypes::eParamite:
        case ReliveTypes::eScrab:
        case ReliveTypes::eSlog:
            if (mHealth > FP_FromInteger(0))
            {
                auto pAliveObj = static_cast<BaseAliveGameObject*>(pFrom);
                mHealth = FP_FromInteger(0);
                const PSX_RECT abeRect = VGetBoundingRect();
                if (pAliveObj->mVelX <= FP_FromInteger(0))
                {
                    relive_new Blood(
                        mXPos,
                        FP_FromInteger(abeRect.h + abeRect.y) / FP_FromInteger(2),
                        FP_FromInteger(-24),
                        FP_FromInteger(0),
                        mSpriteScale,
                        50);
                }
                else
                {
                    relive_new Blood(
                        mXPos,
                        FP_FromInteger(abeRect.h + abeRect.y) / FP_FromInteger(2),
                        FP_FromInteger(24),
                        FP_FromInteger(0),
                        mSpriteScale,
                        50);
                }

                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    return 1;
                }

                if (mCurrentMotion >= eAbeMotions::Motion_102_ElumWalkLoop_42DCA0
                    && mCurrentMotion <= eAbeMotions::Motion_125_ElumMidWalkEnd_42DCC0)
                {
                    mNextMotion = eAbeMotions::Motion_148_Shot_4296A0;
                    field_112_prev_motion = eAbeMotions::Motion_148_Shot_4296A0;
                    field_106_shot = 1;
                    return 1;
                }

                ToKnockback_422D90(1, 1);
                field_108_bMotionChanged = 1;

                if (pAliveObj->mXPos < mXPos)
                {
                    if (!(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }
                else if (pAliveObj->mXPos > mXPos)
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }

                if (pAliveObj->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mVelX = (mSpriteScale * FP_FromDouble(-7.8));
                }
                else
                {
                    mVelX = (mSpriteScale * FP_FromDouble(7.8));
                }

                SfxPlayMono(SoundEffect::KillEffect_78, 127, 0);
                if (pAliveObj->mBaseGameObjectTypeId != ReliveTypes::eParamite)
                {
                    SfxPlayMono(SoundEffect::FallingItemHit_53, 90);
                }
            }
            break;

        case ReliveTypes::eAbilityRing:
            return 0;

        case ReliveTypes::eRollingBall:
            if (mHealth > FP_FromInteger(0))
            {
                field_108_bMotionChanged = 1;
                mHealth = FP_FromInteger(0);
                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    return 1;
                }

                auto pAliveObj = static_cast<BaseAliveGameObject*>(pFrom);

                ToKnockback_422D90(1, 1);

                if (pAliveObj->mXPos < mXPos)
                {
                    if (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }
                else if (pAliveObj->mXPos > mXPos)
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }

                if (pAliveObj->mVelX >= FP_FromInteger(0))
                {
                    mVelX = (mSpriteScale * FP_FromDouble(7.8));
                }
                else
                {
                    mVelX = (mSpriteScale * FP_FromDouble(-7.8));
                }

                SfxPlayMono(SoundEffect::KillEffect_78, 127, 0);
            }
            break;

        case ReliveTypes::eUnknown:
            break;

        case ReliveTypes::eZBall:
            if (mHealth > FP_FromInteger(0))
            {
                field_106_shot = 1;
                mHealth = FP_FromInteger(0);
                if (static_cast<ZBall*>(pFrom)->mFrameAbove12 == 1)
                {
                    field_112_prev_motion = eAbeMotions::Motion_148_Shot_4296A0;
                    mNextMotion = eAbeMotions::Motion_148_Shot_4296A0;
                }
                else
                {
                    field_112_prev_motion = eAbeMotions::Motion_147_ShotRolling_4295C0;
                    mNextMotion = eAbeMotions::Motion_147_ShotRolling_4295C0;
                }
            }
            break;

        case ReliveTypes::eBeeSwarm:
            if (mHealth > FP_FromInteger(0))
            {
                mHealth -= FP_FromDouble(0.15);
                if (mHealth > FP_FromInteger(0))
                {
                    const auto rnd_sfx = Math_RandomRange(0, 127) >= 64 ? MudSounds::eBeesStruggle_18 : MudSounds::eKnockbackOuch_10;
                    const FP v16 = (FP_FromInteger(1) - sActiveHero->mHealth) / FP_FromDouble(0.15);
                    const s16 calc_pitch = Math_RandomRange(200 * FP_GetExponent(v16), 200 * FP_GetExponent(v16) + 1);
                    Mudokon_SFX(rnd_sfx, 0, calc_pitch, this);
                }
                else
                {
                    Mudokon_SFX(MudSounds::eKnockbackOuch_10, 0, 1000, this);
                    Environment_SFX_42A220(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
                    mHealth = FP_FromInteger(0);
                    field_106_shot = 1;
                    field_112_prev_motion = eAbeMotions::Motion_128_KnockForward_429330;
                    mNextMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                        || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                        || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                        || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                        || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                    {
                        mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                        field_108_bMotionChanged = 1;
                        field_106_shot = 0;
                        field_114_gnFrame = 0;
                        return 1;
                    }

                    if (!field_1A4_resources.res[0])
                    {
                        ElumKnockForward_42E780(1);
                        field_106_shot = 0;
                    }
                }

                if (mCurrentMotion == eAbeMotions::Motion_103_ElumIdle_42DCD0)
                {
                    mCurrentMotion = eAbeMotions::Motion_126_ElumBeesStruggling_42E080;
                    field_108_bMotionChanged = 1;
                }
            }
            break;

        case ReliveTypes::eElectrocute:
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            ToDieFinal_42C400();
            break;

        case ReliveTypes::eBullet:
            // NOTE: This was in the default case! The type may not be bullet in there which would corrupt memory or crash
            BulletDamage_4220B0(static_cast<Bullet*>(pFrom));
            if (!field_106_shot)
            {
                field_130_say = old_say;
                oldHp = FP_FromInteger(0);
            }
            break;

        default:
            break;
    }

    if (sControlledCharacter->mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit2_bPossesed))
    {
        if (mHealth == FP_FromInteger(0))
        {
            sControlledCharacter->VUnPosses();
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit7);
            sControlledCharacter = this;
        }
    }

    return oldHp > FP_FromInteger(0) ? 1 : 0;
}

static bool IsSameScaleAsHoist(relive::Path_Hoist* pHoist, BaseAliveGameObject* pObj)
{
    auto width = pHoist->Width();

    //The width is used to determine the layer as there is no layer property in the TLV
    if (pObj->mSpriteScale == FP_FromInteger(1))
    {
        return width > 18;
    }
    else
    {
        return width <= 18;
    }
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

void Abe::TryHoist_423420()
{
    mCurrentMotion = eAbeMotions::Motion_16_HoistBegin_426E40;

    auto pHoist = static_cast<relive::Path_Hoist*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eHoist));

    if (pHoist && IsSameScaleAsHoist(pHoist, this))
    {
        if (FP_FromInteger(pHoist->Height()) <= mSpriteScale * FP_FromInteger(95))
        {
            mCurrentMotion = eAbeMotions::Motion_16_HoistBegin_426E40;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_99_HoistBeginLong_426DC0;
        }
        if (!IsFacingSameDirectionAsHoist(pHoist, this))
        {
            mNextMotion = mCurrentMotion;
            mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
        }
        BaseAliveGameObjectPathTLV = pHoist;
    }
}

void Abe::Motion_0_Idle_423520()
{
    FollowLift_42EE90();
    if (Input_IsChanting() && !field_2A8_flags.Get(Flags_2A8::e2A8_Bit7))
    {
        if (field_168_ring_pulse_timer && field_16C_bHaveShrykull)
        {
            mCurrentMotion = eAbeMotions::Motion_162_ToShrykull_42F410;
        }
        else
        {
            field_114_gnFrame = sGnFrame + 90;
            mCurrentMotion = eAbeMotions::Motion_150_Chant_42FD50;
            SND_SEQ_PlaySeq_4775A0(SeqId::eMudokonChant1_11, 0, 1);
        }
        field_110_state.raw = 0;
        return;
    }
    if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler | sInputKey_RightGameSpeakEnabler))
    {
        const auto held = Input().Held();
        if (held & 0xF0)
        {
            field_10C_prev_held = held;
            mCurrentMotion = eAbeMotions::Motion_58_ToSpeak_42F8D0;
            return;
        }
    }
    if (Input().IsAnyPressed(sInputKey_Hop))
    {
        if (Input().IsAnyPressed(sInputKey_Up))
        {
            TryHoist_423420();
        }
        else if (!Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler | sInputKey_RightGameSpeakEnabler))
        {
            mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
            auto pObj = IntoBirdPortal_402350(2);
            if (pObj)
            {
                if (pObj->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                {
                    pObj = nullptr;
                }
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }
            field_1A0_portal = pObj;
        }
        return;
    }

    if (ToLeftRightMovement_422AA0())
    {
        return;
    }

    if (Input().IsAnyPressed(sInputKey_Down))
    {
        if (mLiftPoint)
        {
            const FP liftPlatformXMidPoint = FP_FromInteger((BaseAliveGameObjectCollisionLine->mRect.x + BaseAliveGameObjectCollisionLine->mRect.w) / 2);
            const FP halfGrid = ScaleToGridSize(mSpriteScale) / FP_FromInteger(2);

            if (mLiftPoint->mBaseGameObjectTypeId == ReliveTypes::eLiftPoint && FP_Abs(mXPos - liftPlatformXMidPoint) < halfGrid)
            {
                //AO exclusive - Abe only uses lift facing one side
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
                    mNextMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                }
                return;
            }
        }


        const auto pHoist = static_cast<relive::Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos + FP_FromInteger(16)),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos + FP_FromInteger(16)),
            ReliveTypes::eHoist));

        if (pHoist)
        {
            if (!IsSameScaleAsHoist(pHoist, this))
            {
                return;
            }

            if (IsFacingSameDirectionAsHoist(pHoist, this))
            {
                mCurrentMotion = eAbeMotions::Motion_65_LedgeDescend_428C00;
            }
            else
            {
                mNextMotion = eAbeMotions::Motion_65_LedgeDescend_428C00;
                mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
            }
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_21_StandToCrouch_427F40;
        }
        return;
    }
    if (Input().IsAnyPressed(sInputKey_FartRoll))
    {
        mCurrentMotion = eAbeMotions::Motion_21_StandToCrouch_427F40;
    }

    bool handleDoActionOrThrow = false;
    if (Input().IsAnyPressed(sInputKey_Up))
    {
        if (mLiftPoint)
        {
            if (mLiftPoint->mBaseGameObjectTypeId == ReliveTypes::eLiftPoint)
            {
                const FP halfGrid = ScaleToGridSize(mSpriteScale) / FP_FromInteger(2);
                const FP liftPlatformXMidPoint = FP_FromInteger((BaseAliveGameObjectCollisionLine->mRect.x + BaseAliveGameObjectCollisionLine->mRect.w) / 2);
                const FP xPosToMidLiftPlatformDistance = FP_Abs(mXPos - liftPlatformXMidPoint);
                if (xPosToMidLiftPlatformDistance < halfGrid)
                {
                    //AO exclusive - Abe only uses lift facing one side
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
                        mNextMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                    }
                    return;
                }
            }
        }

        mCurrentMotion = TryMountElum_42E600();
        if (mCurrentMotion != eAbeMotions::Motion_0_Idle_423520)
        {
            return;
        }
        auto pTlv = gMap.TLV_Get_At_446060(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);

        while (pTlv)
        {
            switch (pTlv->mTlvType)
            {
                case ReliveTypes::eDoor:
                {
                    if (NearDoorIsOpen() && !mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit5_Electrocuted))
                    {
                        BaseAliveGameObjectPathTLV = pTlv;
                        field_110_state.raw = 0;
                        mCurrentMotion = eAbeMotions::Motion_156_DoorEnter_42D370;
                    }
                    else
                    {
                        if (Input().IsAnyHeld(sInputKey_Up))
                        {
                            mCurrentMotion = eAbeMotions::Motion_36_DunnoBegin_423260;
                        }
                    }
                    return;
                }
                case ReliveTypes::eWellLocal:
                {
                    auto well = static_cast<relive::Path_WellLocal*>(pTlv);
                    if ((well->mScale != relive::reliveScale::eFull || mSpriteScale != FP_FromInteger(1)) &&
                        (well->mScale != relive::reliveScale::eHalf || mSpriteScale != FP_FromDouble(0.5)))
                    {
                        break;
                    }
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_77_WellBegin_430F10;
                    return;
                }
                case ReliveTypes::eWellExpress:
                {
                    auto well = static_cast<relive::Path_WellExpress*>(pTlv);
                    if ((well->mScale != relive::reliveScale::eFull || mSpriteScale != FP_FromInteger(1)) &&
                        (well->mScale != relive::reliveScale::eHalf || mSpriteScale != FP_FromDouble(0.5)))
                    {
                        break;
                    }
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_80_430EF0;
                    return;
                }
                case ReliveTypes::eMovieHandStone:
                case ReliveTypes::eBellSongStone:
                case ReliveTypes::eDemoPlaybackStone:
                case ReliveTypes::eHandStone:
                {
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_88_HandstoneBegin_430590;
                    field_110_state.stone = StoneStates::eHandstoneStart_0;
                    return;
                }
                case ReliveTypes::eBoomMachine:
                {
                    auto pMachineButton = static_cast<BoomMachine*>(FindObjectOfType_418280(
                        ReliveTypes::eBoomMachine,
                        mXPos,
                        mYPos - mSpriteScale * FP_FromInteger(25)));
                    if (pMachineButton)
                    {
                        pMachineButton->VHandleButton();
                        mCurrentMotion = eAbeMotions::Motion_90_GrenadeMachineUse_430EA0;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_36_DunnoBegin_423260;
                    }
                    break;
                }
                default:
                    break;
            }

            pTlv = gMap.TLV_Get_At_446060(
                pTlv,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
        }
        if (mCurrentMotion == eAbeMotions::Motion_0_Idle_423520)
        {
            TryHoist_423420();
        }
        handleDoActionOrThrow = true;
    }

    if (!Input().IsAnyPressed(sInputKey_Up) || handleDoActionOrThrow)
    {
        if (Input().IsAnyHeld(sInputKey_ThrowItem) && mCurrentMotion == eAbeMotions::Motion_0_Idle_423520)
        {
            if (field_19C_throwable_count > 0 || gInfiniteGrenades_5076EC)
            {
                field_198_pThrowable = Make_Throwable(
                    mXPos,
                    mYPos - FP_FromInteger(40),
                    0);

                if (bThrowableIndicatorExists_504C70 == 0)
                {
                    const FP xOffSet = mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(15) : FP_FromInteger(-15) * mSpriteScale;

                    relive_new ThrowableTotalIndicator(mXPos + xOffSet,
                                                                                    mYPos + mSpriteScale * FP_FromInteger(-50),
                                                                                    mAnim.mRenderLayer,
                                                                                    mAnim.field_14_scale,
                                                                                    field_19C_throwable_count,
                                                                                    TRUE);
                }
                mCurrentMotion = eAbeMotions::Motion_142_RockThrowStandingHold_429CE0;

                if (gInfiniteGrenades_5076EC == 0)
                {
                    field_19C_throwable_count--;
                }
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_36_DunnoBegin_423260;
            }
        }
        else
        {
            if (Input().IsAnyHeld(sInputKey_DoAction))
            {
                mCurrentMotion = HandleDoAction_429A70();
            }
            else if (gBeeInstanceCount && gBeesNearAbe)
            {
                mCurrentMotion = eAbeMotions::Motion_140_BeesStruggling_423F30;
            }
            else if (sGnFrame - field_114_gnFrame > 150)
            {
                u16 loaded = 0;
                field_114_gnFrame = sGnFrame;


#if 0
                // Force load idle anims to restore the feature, it kinda sucks though
                if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeyawnAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ABEYAWN.BAN", nullptr, ResourceManager::BlockAllocMethod::eFirstMatching);
                }
                if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAberubAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ABERUB.BAN", nullptr, ResourceManager::BlockAllocMethod::eFirstMatching);
                }
                if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesizeAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ABESIZE.BAN", nullptr, ResourceManager::BlockAllocMethod::eFirstMatching);
                }
#endif

                if (ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeyawnAOResID, 0, 0)) //yawn ABEYAWN.BAN
                {
                    loaded |= 1;
                }
                if (ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAberubAOResID, 0, 0)) // rub ABERUB.BAN
                {
                    loaded |= 2;
                }
                if (ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesizeAOResID, 0, 0)) // size ABESIZE.BAN
                {
                    loaded |= 4;
                }
                const s16 rnd = Math_RandomRange(0, 2);
                if ((1 << rnd) & loaded)
                {
                    switch (rnd)
                    {
                        case 0:
                        {
                            mCurrentMotion = eAbeMotions::Motion_161_Idle_Yawn_4233E0;
                            break;
                        }
                        case 1:
                        {
                            mCurrentMotion = eAbeMotions::Motion_159_Idle_RubEyes_423360;
                            break;
                        }
                        case 2:
                        {
                            mCurrentMotion = eAbeMotions::Motion_160_Idle_Stretch_Arms_4233A0;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void Abe::Motion_1_WalkLoop_423F90()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    MoveForward_422FC0();

    if (mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_423F90)
    {
        switch (mAnim.mCurrentFrame)
        {
            case 2:
            {
                if ((mVelX > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left)) || (mVelX < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right)))
                {
                    mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                    field_10C_prev_held = 0;
                    return;
                }

                if (field_10C_prev_held & sInputKey_Hop)
                {
                    mNextMotion = eAbeMotions::Motion_30_HopMid_4264D0;
                    mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                    field_10C_prev_held = 0;
                    return;
                }

                if (!Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
                {
                    mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                    field_10C_prev_held = 0;
                }
                else
                {
                    FP directedScale = {};
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        directedScale = -ScaleToGridSize(mSpriteScale);
                    }
                    else
                    {
                        directedScale = ScaleToGridSize(mSpriteScale);
                    }

                    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), directedScale * FP_FromDouble(1.5)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                        field_10C_prev_held = 0;
                        return;
                    }
                    else
                    {
                        field_10C_prev_held = 0;
                    }
                }
                break;
            }

            case 11:
                if ((mVelX <= FP_FromInteger(0) || !(Input().IsAnyPressed(sInputKey_Left))) && (mVelX >= FP_FromInteger(0) || !(Input().IsAnyPressed(sInputKey_Right))))
                {
                    if (field_10C_prev_held & sInputKey_Hop)
                    {
                        mNextMotion = eAbeMotions::Motion_30_HopMid_4264D0;
                    }
                    else if (Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
                    {
                        FP directedScale = {};
                        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            directedScale = -ScaleToGridSize(mSpriteScale);
                        }
                        else
                        {
                            directedScale = ScaleToGridSize(mSpriteScale);
                        }

                        if (!WallHit_401930(mSpriteScale * FP_FromInteger(50), directedScale * FP_FromDouble(1.5)))
                        {
                            field_10C_prev_held = 0;
                            return;
                        }
                    }
                }
                mCurrentMotion = eAbeMotions::Motion_4_WalkToIdle_4243C0;
                field_10C_prev_held = 0;
                return;

            case 5:
                Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);

                if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit3_WalkToRun))
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                    MapFollowMe_401D30(1);
                }

                if (Input().IsAnyPressed(sInputKey_Run))
                {
                    mCurrentMotion = eAbeMotions::Motion_51_MidWalkToRun_424670;
                }
                else if (Input().IsAnyPressed(sInputKey_Sneak))
                {
                    mCurrentMotion = eAbeMotions::Motion_43_WalkToSneak_424790;
                }
                break;

            case 14:
                Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);

                if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit3_WalkToRun))
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                    MapFollowMe_401D30(1);
                }

                if (Input().IsAnyPressed(sInputKey_Run))
                {
                    mCurrentMotion = eAbeMotions::Motion_50_WalkToRun_424560;
                }
                else if (Input().IsAnyPressed(sInputKey_Sneak))
                {
                    mCurrentMotion = eAbeMotions::Motion_45_MidWalkToSneak_424890;
                }
                break;

            default:
                field_2A8_flags.Clear(Flags_2A8::e2A8_Bit3_WalkToRun);
                break;
        }
    }
}

void Abe::Motion_2_StandingTurn_426040()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 4)
    {
        if (Input().IsAnyPressed(sInputKey_Run) && Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
        {
#if ORIGINAL_GAME_FIXES || ORIGINAL_GAME_FIX_AUTO_TURN
            mNextMotion = eAbeMotions::Motion_0_Idle_423520; // OG Change - Fixes "Auto-Turn" bug
#endif

            mCurrentMotion = eAbeMotions::Motion_63_TurnToRun_42A0A0;
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
            }
            else
            {
                mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
            }
            return;
        }
    }

    if (!mAnim.mCurrentFrame)
    {
        Environment_SFX_42A220(EnvironmentSfx::eGenericMovement_9, 0, 0x7FFF, this);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);

        if (mNextMotion)
        {
            // OG bug: this local variable allows you to "store" your next state if you face the opposite
            // ledge direction and press down/up and then interrupt it by running away before you hoist.
            const s16 kNext_state = mNextMotion;
            if (mNextMotion != eAbeMotions::Motion_139_ElumMountBegin_42E090)
            {
                if (mNextMotion == eAbeMotions::Motion_101_LeverUse_429970)
                {
                    Lever* pSwitch;
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        pSwitch = static_cast<Lever*>(FindObjectOfType_418280(ReliveTypes::eLever, mXPos - ScaleToGridSize(mSpriteScale), mYPos - FP_FromInteger(5)));
                    }
                    else
                    {
                        pSwitch = static_cast<Lever*>(FindObjectOfType_418280(ReliveTypes::eLever, mXPos + ScaleToGridSize(mSpriteScale), mYPos - FP_FromInteger(5)));
                    }

                    if (pSwitch)
                    {
                        pSwitch->VPull(mXPos < pSwitch->mXPos);
                    }
                }
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                mCurrentMotion = kNext_state;
                return;
            }

            if (gElum)
            {
                if (gElum->mCurrentMotion == eElumMotions::Motion_1_Idle_412990 && !(gElum->field_170_flags.Get(Elum::Flags_170::eStrugglingWithBees_Bit1)))
                {
                    LoadMountElumResources_42E690();
                    mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                    mCurrentMotion = kNext_state;
                    return;
                }
            }
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
        }
        else
        {
            if (ToLeftRightMovement_422AA0())
            {
                mAnim.Set_Animation_Data(mAnim.mFrameTableOffset, nullptr);
                return;
            }
        }
        ToIdle_422D50();
    }
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

void Abe::Motion_3_Fall_42E7F0()
{
    if (mVelX > FP_FromInteger(0))
    {
        mVelX -= (mSpriteScale * field_120_x_vel_slow_by);
        if (mVelX < FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }
    else if (mVelX < FP_FromInteger(0))
    {
        mVelX += (mSpriteScale * field_120_x_vel_slow_by);
        if (mVelX > FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pPathLine = nullptr;
    const s32 bCollision = InAirCollision_4019C0(&pPathLine, &hitX, &hitY, FP_FromDouble(1.8));
    SetActiveCameraDelayedFromDir_401C90();

    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
        nullptr,
        mXPos,
        mYPos,
        mXPos,
        mYPos);

    if (BaseAliveGameObjectPathTLV)
    {
        if (mHealth > FP_FromInteger(0))
        {
            if (BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eWellLocal || BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eWellExpress)
            {
                // The well must be on the same scale/layer
                relive::Path_WellBase* pWellBase = static_cast<relive::Path_WellBase*>(BaseAliveGameObjectPathTLV);
                if ((pWellBase->mScale == relive::reliveScale::eFull && mSpriteScale == FP_FromInteger(1)) ||
                    (pWellBase->mScale == relive::reliveScale::eHalf && mSpriteScale == FP_FromDouble(0.5)))
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit4_snap_abe);
                    mCurrentMotion = eAbeMotions::Motion_74_JumpIntoWell_430EC0;
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
                mYPos = hitY;
                BaseAliveGameObjectCollisionLine = pPathLine;
                MapFollowMe_401D30(1);
                field_114_gnFrame = sGnFrame + 30;
                if (mYPos - BaseAliveGameObjectLastLineYPos > FP_FromInteger(240))
                {
                    BaseAliveGameObjectLastLineYPos += FP_FromInteger(240);
                }

                relive::Path_SoftLanding* pSoftLanding = static_cast<relive::Path_SoftLanding*>(gMap.TLV_Get_At_446260(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    ReliveTypes::eSoftLanding));

                if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit8_bLandSoft)
                    || (pSoftLanding && mHealth > FP_FromInteger(0))
                    || ((mYPos - BaseAliveGameObjectLastLineYPos) < (mSpriteScale * FP_FromInteger(180))
                        && (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)))
                {
                    mCurrentMotion = eAbeMotions::Motion_98_LandSoft_42ED40;
                }
                else
                {
                    mHealth = FP_FromInteger(0);
                    mCurrentMotion = eAbeMotions::Motion_86_FallLandDie_42EDD0;
                    field_11C_regen_health_timer = sGnFrame + 900;
                }
                mPreviousMotion = eAbeMotions::Motion_3_Fall_42E7F0;

                PSX_Point xy{FP_GetExponent(mXPos - FP_FromInteger(25)), FP_GetExponent(mYPos - FP_FromInteger(25))};
                PSX_Point wh{FP_GetExponent(mXPos + FP_FromInteger(25)), FP_GetExponent(mYPos + FP_FromInteger(25))};
                VOnCollisionWith(
                    xy,
                    wh,
                    ObjListPlatforms_50766C,
                    1,
                    reinterpret_cast<TCollisionCallBack>(&BaseAliveGameObject::OnTrapDoorIntersection_401C10));
                break;
            }
            case eLineTypes::eWallLeft_1:
            case eLineTypes::eWallRight_2:
            case eLineTypes::eBackgroundWallLeft_5:
            case eLineTypes::eBackgroundWallRight_6:
                mXPos = hitX;
                mYPos = hitY;
                ToKnockback_422D90(1, 1);
                break;
            default:
                return;
        }
        return;
    }

    if (mHealth <= FP_FromInteger(0))
    {
        return;
    }

    bool tryToHang = false;
    relive::Path_Edge* pEdge = static_cast<relive::Path_Edge*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(80)),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eEdge));

    if (pEdge)
    {
        if (pEdge->mCanGrab == relive::reliveChoice::eYes && isEdgeGrabbable(pEdge, this))
        {
            tryToHang = true;
        }
        BaseAliveGameObjectPathTLV = pEdge;
    }
    else
    {
        relive::Path_Hoist* pHoist = static_cast<relive::Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(20)),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(20)),
            ReliveTypes::eHoist));

        if (pHoist)
        {
            if (IsFacingSameDirectionAsHoist(pHoist, this))
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

        MapFollowMe_401D30(TRUE);

        if (sCollisions->Raycast(
                mXPos,
                mYPos - mSpriteScale * FP_FromInteger(20) - mSpriteScale * FP_FromInteger(80),
                mXPos,
                mYPos,
                &pPathLine,
                &hitX,
                &hitY,
                mSpriteScale != FP_FromDouble(0.5) ? kFgFloor : kBgFloor))
        {
            mVelX = FP_FromInteger(0);
            mVelY = FP_FromInteger(0);
            mYPos = hitY;
            BaseAliveGameObjectCollisionLine = pPathLine;
            mCurrentMotion = eAbeMotions::Motion_68_LedgeHangWobble_428E50;
            mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
        }
    }
}

void Abe::Motion_4_WalkToIdle_4243C0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    MoveForward_422FC0();

    if (mAnim.mCurrentFrame != 0)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe_401D30(1);

            if (mNextMotion == eAbeMotions::Motion_30_HopMid_4264D0)
            {
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;

                field_1A0_portal = IntoBirdPortal_402350(2);
                if (field_1A0_portal)
                {
                    if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }
            }
            else
            {
                ToIdle_422D50();
            }
        }
    }
    else
    {
        Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);
    }
}

void Abe::Motion_5_MidWalkToIdle_424490()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    MoveForward_422FC0();

    if (mAnim.mCurrentFrame)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe_401D30(1);
            if (mNextMotion == eAbeMotions::Motion_30_HopMid_4264D0)
            {
                mNextMotion = 0;
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
                field_1A0_portal = IntoBirdPortal_402350(2);
                if (field_1A0_portal)
                {
                    if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }
            }
            else
            {
                ToIdle_422D50();
            }
        }
    }
    else
    {
        Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);
    }
}

void Abe::Motion_6_WalkBegin_424300()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_7_Speak_42F950()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_8_Speak_42F9D0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_9_Speak_42FA50()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_10_Speak_42FAD0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_11_Speak_42FB50()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_12_Speak_42FBD0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_13_Speak_42FC50()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_14_Speak_42FCD0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_15_Null_42A210()
{
    // Empty
}

void Abe::Motion_16_HoistBegin_426E40()
{
    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mYPos;
        const FP velY = mSpriteScale * FP_FromInteger(-8);
        mVelY = velY;
        mYPos += velY;
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_17_HoistIdle_4269E0()
{
    PathLine* pPathLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    const auto bCollision = InAirCollision_4019C0(&pPathLine, &hitX, &hitY, FP_FromDouble(1.8));
    SetActiveCameraDelayedFromDir_401C90();
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
                mYPos = hitY;

                MapFollowMe_401D30(1);

                BaseAliveGameObjectCollisionLine = pPathLine;

                mCurrentMotion = eAbeMotions::Motion_18_HoistLand_426EB0;
                mPreviousMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;

                PSX_RECT rect = VGetBoundingRect();
                rect.y += 5;
                rect.h += 5;

                VOnCollisionWith(
                    {rect.x, rect.y},
                    {rect.w, rect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                break;
            }
        }
        return;
    }

    field_160_pRope = GetPullRope_422580();
    if (field_160_pRope)
    {
        if (field_160_pRope->Pull(this))
        {
            mCurrentMotion = eAbeMotions::Motion_69_RingRopePullHang_4299B0;
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
            field_160_pRope->mBaseGameObjectRefCount++;
            return;
        }
        field_160_pRope = nullptr;
    }

    if (mVelY >= FP_FromInteger(0))
    {
        auto pHoist = static_cast<relive::Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eHoist));
        BaseAliveGameObjectPathTLV = pHoist;
        if (pHoist && IsSameScaleAsHoist(pHoist, this))
        {
            if (IsFacingSameDirectionAsHoist(pHoist, this))
            {
                if (pHoist->mHoistType == relive::Path_Hoist::Type::eOffScreen)
                {
                    if (gMap.SetActiveCameraDelayed(Map::MapDirections::eMapTop_2, this, -1))
                    {
                        PSX_Prevent_Rendering_44FFB0();
                        mCurrentMotion = eAbeMotions::Motion_67_ToOffScreenHoist_428C50;
                        return;
                    }
                    mYPos -= mSpriteScale * FP_FromInteger(80);
                    mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
                }

                mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
                Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);


                if (sCollisions->Raycast(
                        mXPos,
                        mYPos - mSpriteScale * FP_FromInteger(80),
                        mXPos,
                        mYPos,
                        &pPathLine,
                        &hitX,
                        &hitY,
                        mSpriteScale != FP_FromDouble(0.5) ? kFgFloor : kBgFloor))
                {
                    mYPos = hitY;
                    BaseAliveGameObjectCollisionLine = pPathLine;
                    mVelY = FP_FromInteger(0);
                    if (!mLiftPoint)
                    {
                        if (pPathLine->mLineType == eLineTypes::eDynamicCollision_32 ||
                            pPathLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
                        {
                            PSX_RECT rect = VGetBoundingRect();
                            rect.y += 5;
                            rect.h += 5;

                            VOnCollisionWith(
                                {rect.x, rect.y},
                                {rect.w, rect.h},
                                ObjListPlatforms_50766C,
                                1,
                                (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                        }
                    }
                    mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
                }
            }
        }
        else
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                nullptr,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
        }
    }
}

void Abe::Motion_18_HoistLand_426EB0()
{
    FollowLift_42EE90();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mCurrentFrame == 2)
    {
        if (mPreviousMotion == 3)
        {
            Environment_SFX_42A220(EnvironmentSfx::eLandingSoft_5, 0, 0x7FFF, this);
        }
        else
        {
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        }

        if (Input().IsAnyPressed(sInputKey_Hop))
        {
            if (Input().IsAnyPressed(sInputKey_Up))
            {
                mCurrentMotion = eAbeMotions::Motion_16_HoistBegin_426E40;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
                field_1A0_portal = IntoBirdPortal_402350(2);

                if (field_1A0_portal)
                {
                    if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }
            }
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_19_CrouchIdle_4284C0()
{
    if (!BaseAliveGameObjectCollisionLine)
    {
        mCurrentMotion = eAbeMotions::Motion_100_RollOffLedge_429950;
        return;
    }

    FollowLift_42EE90();

    if (Input().IsAllPressed(5) && Input().IsAllHeld(5))
    {
        Mudokon_SFX(MudSounds::eDunno_15, 0, 0, this);
        mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        return;
    }

    // Crouching game speak
    CrouchingGameSpeak_427F90();

    field_10C_prev_held = 0;
    field_10E_released_buttons = 0;

    if (mCurrentMotion == eAbeMotions::Motion_22_CrouchSpeak_428A30 || mCurrentMotion == eAbeMotions::Motion_23_CrouchSpeak_428A90)
    {
        EventBroadcast(kEventSpeaking, this);
        return;
    }


    // Hit bombs/pick up items ?
    if (Input().IsAnyHeld(sInputKey_DoAction))
    {
        if (!Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
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

            PickUpThrowabe_Or_PressBomb_428260(
                gridSize + mXPos,
                FP_GetExponent(mYPos - FP_FromInteger(5)),
                0);
        }
    }


    // Crouching throw stuff
    if (Input().IsAnyHeld(sInputKey_ThrowItem))
    {
        if (mCurrentMotion == eAbeMotions::Motion_19_CrouchIdle_4284C0)
        {
            if (field_19C_throwable_count > 0 || gInfiniteGrenades_5076EC)
            {
                field_198_pThrowable = Make_Throwable(
                    mXPos,
                    mYPos - FP_FromInteger(40),
                    0);

                if (!bThrowableIndicatorExists_504C70)
                {
                    const FP yOff = mYPos + (mSpriteScale * FP_FromInteger(-30));
                    const FP xOff = mSpriteScale * (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(-10) : FP_FromInteger(10));
                    relive_new ThrowableTotalIndicator(mXPos + xOff,
                                                                             yOff,
                                                                             mAnim.mRenderLayer,
                                                                             mAnim.field_14_scale,
                                                                             field_19C_throwable_count,
                                                                             1);
                }

                mCurrentMotion = eAbeMotions::Motion_145_RockThrowCrouchingHold_428930;

                if (!gInfiniteGrenades_5076EC)
                {
                    field_19C_throwable_count--;
                }

                return;
            }
        }

        if (!field_19C_throwable_count && !gInfiniteGrenades_5076EC)
        {
            Mudokon_SFX(MudSounds::eDunno_15, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
            return;
        }
    }

    // Try to stand up
    if (Input().IsAnyHeld(sInputKey_Up) || Input().IsAnyHeld(sInputKey_FartRoll))
    {
        PathLine* pLine = nullptr;
        FP hitX = {};
        FP hitY = {};
        if (!sCollisions->Raycast(
                mXPos,
                mYPos,
                mXPos,
                mYPos - (mSpriteScale * FP_FromInteger(60)),
                &pLine,
                &hitX,
                &hitY,
                mSpriteScale != FP_FromDouble(0.5) ? kFgCeiling : kBgCeiling))
        {
            mCurrentMotion = eAbeMotions::Motion_20_CrouchToStand_428AF0;
            return;
        }
    }

    // Crouching turns
    if (Input().IsAnyPressed(sInputKey_Right))
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mCurrentMotion = eAbeMotions::Motion_39_CrouchTurn_4288C0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_24_RollBegin_427A20;
            field_10E_released_buttons = 0;
        }
    }

    if (Input().IsAnyPressed(sInputKey_Left))
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mCurrentMotion = eAbeMotions::Motion_24_RollBegin_427A20;
            field_10E_released_buttons = 0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_39_CrouchTurn_4288C0;
        }
    }
}

void Abe::Motion_20_CrouchToStand_428AF0()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 3)
    {
        if (Input().IsAnyPressed(0xA000)) // TODO: Flags
        {
            ToLeftRightMovement_422AA0();
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_21_StandToCrouch_427F40()
{
    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        PickUpThrowabe_Or_PressBomb_428260(
            mXPos,
            FP_GetExponent(mYPos - FP_FromInteger(5)),
            1);
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }
}

void Abe::Motion_22_CrouchSpeak_428A30()
{
    Motion_23_CrouchSpeak_428A90();
}

void Abe::Motion_23_CrouchSpeak_428A90()
{
    field_10C_prev_held |= Input().Held();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;

        CrouchingGameSpeak_427F90();

        if (mCurrentMotion == eAbeMotions::Motion_22_CrouchSpeak_428A30 || mCurrentMotion == eAbeMotions::Motion_23_CrouchSpeak_428A90)
        {
            EventBroadcast(kEventSpeaking, this);
        }

        field_10C_prev_held = 0;
    }
}

void Abe::Motion_24_RollBegin_427A20()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_422D90(1, 1);

        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (mCurrentMotion == eAbeMotions::Motion_24_RollBegin_427A20)
            {
                mCurrentMotion = eAbeMotions::Motion_25_RollLoop_427BB0;
            }
        }
    }
}

bool Abe::Is_Celling_Above()
{
    FP hitY = {};
    FP hitX = {};
    PathLine* pLine = nullptr;
    return sCollisions->Raycast(
               mXPos,
               mYPos,
               mXPos,
               mYPos - (mSpriteScale * FP_FromInteger(60)),
               &pLine,
               &hitX,
               &hitY,
               mSpriteScale != FP_FromDouble(0.5) ? kFgCeiling : kBgCeiling)
        != 0;
}

void Abe::Motion_25_RollLoop_427BB0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    field_10E_released_buttons |= Input().Released();

    if (WallHit_401930(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_422D90(1, 1);
        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (mCurrentMotion == eAbeMotions::Motion_25_RollLoop_427BB0)
        {
            if (mAnim.mCurrentFrame == 1 || mAnim.mCurrentFrame == 5 || mAnim.mCurrentFrame == 9)
            {
                if (!Input().IsAnyPressed(sInputKey_Run)
                    || Input().IsAnyPressed(sInputKey_FartRoll)
                    || Is_Celling_Above()
                    || field_12C_timer + 9 >= static_cast<s32>(sGnFrame))
                {
                    if (field_10E_released_buttons && sInputKey_FartRoll)
                    {
                        if (!Is_Celling_Above() && field_12C_timer + 9 < static_cast<s32>(sGnFrame))
                        {
                            ToLeftRightMovement_422AA0();
                            field_10E_released_buttons = 0;
                        }
                    }
                }
                else
                {
                    ToLeftRightMovement_422AA0();
                    field_10C_prev_held = 0;
                }
            }
            else if (mAnim.mCurrentFrame == 0 || mAnim.mCurrentFrame == 4 || mAnim.mCurrentFrame == 8)
            {
                MapFollowMe_401D30(TRUE);

                if ((mVelX > FP_FromInteger(0) && !Input().IsAnyPressed(sInputKey_Right)) || (mVelX < FP_FromInteger(0) && !Input().IsAnyPressed(sInputKey_Left)))
                {
                    mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
                    mVelX = FP_FromInteger(0);
                }
            }

            if (mAnim.mCurrentFrame == 0 || mAnim.mCurrentFrame == 6)
            {
                Environment_SFX_42A220(EnvironmentSfx::eRollingNoise_8, 0, 0x7FFF, this);
            }
        }
    }
}

void Abe::Motion_26_RollEnd_427EA0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_422D90(1, 1);
        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (mCurrentMotion == eAbeMotions::Motion_26_RollEnd_427EA0)
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_401D30(1);
                mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
                mVelX = FP_FromInteger(0);
            }
        }
    }
}

void Abe::Motion_27_RunSlideStop_425B60()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        MoveWithVelocity_4257F0(FP_FromDouble(0.375));
        if (mCurrentMotion == eAbeMotions::Motion_27_RunSlideStop_425B60
            && !RunTryEnterWell_425880()
            && !RunTryEnterDoor_4259C0())
        {
            if (mAnim.mCurrentFrame >= 9)
            {
                if (mAnim.mCurrentFrame == 15)
                {
                    Environment_SFX_42A220(EnvironmentSfx::eSlideStop_0, 0, 0x7FFF, this);
                    MapFollowMe_401D30(1);

                    if (!ToLeftRightMovement_422AA0())
                    {
                        ToIdle_422D50();
                    }
                }
            }
            else if ((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Right)) || (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Left)))
            {
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
                mPreviousMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
                mBaseAliveGameObjectLastAnimFrame = mAnim.mCurrentFrame;
            }
        }
    }
}

void Abe::Motion_28_RunTurn_425CE0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        MoveWithVelocity_4257F0(FP_FromDouble(0.375));
        if (mCurrentMotion == eAbeMotions::Motion_28_RunTurn_425CE0
            && !RunTryEnterWell_425880()
            && !RunTryEnterDoor_4259C0())
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_401D30(TRUE);

                const FP gridSize = ScaleToGridSize(mSpriteScale);
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    if (Input().IsAnyPressed(sInputKey_Run))
                    {
                        mVelX = gridSize / FP_FromInteger(4);
                        mCurrentMotion = eAbeMotions::Motion_54_RunTurnToRun_425EA0;
                    }
                    else
                    {
                        mVelX = gridSize / FP_FromInteger(9);
                        mCurrentMotion = eAbeMotions::Motion_55_RunTurnToWalk_425F70;
                    }
                }
                else
                {
                    FP velX = {};
                    if (Input().IsAnyPressed(sInputKey_Run))
                    {
                        velX = gridSize / FP_FromInteger(4);
                        mCurrentMotion = eAbeMotions::Motion_54_RunTurnToRun_425EA0;
                    }
                    else
                    {
                        velX = gridSize / FP_FromInteger(9);
                        mCurrentMotion = eAbeMotions::Motion_55_RunTurnToWalk_425F70;
                    }
                    mVelX = -velX;
                }
            }
        }
    }
}

void Abe::Motion_29_HopBegin_4267B0()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 9)
    {
        const FP velX = mSpriteScale * (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(-17) : FP_FromInteger(17));
        mVelX = velX;

        if (!field_1A0_portal)
        {
            if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
            {
                EventBroadcast(kEventNoise, this);
                EventBroadcast(kEventSuspiciousNoise, this);
                mVelX = FP_FromInteger(0);
                ToKnockback_422D90(1, 1);
                return;
            }
        }
        mXPos += mVelX;
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

        mCurrentMotion = eAbeMotions::Motion_30_HopMid_4264D0;
        BaseAliveGameObjectCollisionLine = nullptr;

        if (!field_1A0_portal)
        {
            field_1A0_portal = IntoBirdPortal_402350(2);
            if (field_1A0_portal)
            {
                if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                {
                    field_1A0_portal = nullptr;
                }
            }

            if (field_1A0_portal)
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }
        }
    }
}

void Abe::IntoPortalStates_4262A0()
{
    switch (field_19E_portal_sub_state)
    {
        case PortalSubStates::eJumpingInsidePortal_0:
        {
            PSX_RECT bRect = VGetBoundingRect();
            if ((mVelX > FP_FromInteger(0) && FP_FromInteger(bRect.x) > field_1A0_portal->mXPos) || (mVelX < FP_FromInteger(0) && FP_FromInteger(bRect.w) < field_1A0_portal->mXPos))
            {
                mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                mVelY = FP_FromInteger(0);
                mVelX = FP_FromInteger(0);
                field_1A0_portal->VKillPortalClipper();
                field_1A0_portal->VGiveShrykull(TRUE);
                field_19E_portal_sub_state = PortalSubStates::eSetNewActiveCamera_1;
            }
            mVelY += mSpriteScale * FP_FromDouble(1.8);
            mXPos += mVelX;
            mYPos += mVelY;
            return;
        }
        case PortalSubStates::eSetNewActiveCamera_1:
        {
            if (field_1A0_portal->VAbeInsidePortal())
            {
                EReliveLevelIds level = {};
                u16 path = 0;
                u16 camera = 0;
                CameraSwapEffects screenChangeEffect = {};
                u16 movieId = 0;
                field_1A0_portal->VGetMapChange(&level, &path, &camera, &screenChangeEffect, &movieId);
                gMap.SetActiveCam(level, path, camera, screenChangeEffect, movieId, FALSE);
                field_19E_portal_sub_state = PortalSubStates::eSetNewAbePosition_4;
            }
            break;
        }
        case PortalSubStates::eHopOutOfPortal_2:
        {
            if (field_1A0_portal->VPortalExit_AbeExitting())
            {
                field_1A0_portal->VPortalClipper(0);
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
                field_1A0_portal->VIncreaseTimerAndKillPortalClipper();
                field_1A0_portal = 0;
            }
            break;
        }
        case PortalSubStates::eSetNewAbePosition_4:
        {
            field_1A0_portal->VExitPortal();
            field_19E_portal_sub_state = PortalSubStates::eHopOutOfPortal_2;
            mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, field_1A0_portal->mEnterSide == relive::Path_BirdPortal::PortalSide::eLeft);

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mXPos = ScaleToGridSize(mSpriteScale) + field_1A0_portal->mExitX;
            }
            else
            {
                mXPos = field_1A0_portal->mExitX - ScaleToGridSize(mSpriteScale);
            }

            mYPos = field_1A0_portal->mExitY;
            mVelY = FP_FromInteger(0);
            field_120_x_vel_slow_by = FP_FromInteger(0);
            break;
        }
        default:
            return;
    }
}

void Abe::Motion_30_HopMid_4264D0()
{
    if (field_1A0_portal)
    {
        IntoPortalStates_4262A0();
    }
    else
    {
        if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
        {
            EventBroadcast(kEventNoise, this);
            EventBroadcast(kEventSuspiciousNoise, this);
            if (gMap.TLV_Get_At_446260(
                    FP_GetExponent(mVelX + mXPos),
                    FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(50)),
                    FP_GetExponent(mVelX + mXPos),
                    FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(50)),
                    ReliveTypes::eElumStart))
            {
                SfxPlayMono(SoundEffect::RingBellHammer_9, 0, 0);
            }
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
            ToKnockback_422D90(1, 1);
        }
        else
        {
            PathLine* pLine = nullptr;
            FP hitX = {};
            FP hitY = {};

            // this has to be called before SetActiveCameraDelayedFromDir_401C90,
            // due to both of them modifying the same private fields in a fixed order
            bool hasCollidedWithAir = InAirCollision_4019C0(&pLine, &hitX, &hitY, FP_FromDouble(1.80));

            SetActiveCameraDelayedFromDir_401C90();

            if (hasCollidedWithAir)
            {
                EventBroadcast(kEventNoise, this);
                EventBroadcast(kEventSuspiciousNoise, this);
                switch (pLine->mLineType)
                {
                    case eLineTypes::eFloor_0:
                    case eLineTypes::eBackgroundFloor_4:
                    case eLineTypes::eDynamicCollision_32:
                    case eLineTypes::eBackgroundDynamicCollision_36:
                    {
                        Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
                        BaseAliveGameObjectCollisionLine = pLine;
                        mVelY = FP_FromInteger(0);
                        mCurrentMotion = eAbeMotions::Motion_31_HopLand_426940;

                        PSX_RECT rect = VGetBoundingRect();
                        rect.y += 5;
                        rect.h += 5;

                        VOnCollisionWith(
                            {rect.x, rect.y},
                            {rect.w, rect.h},
                            ObjListPlatforms_50766C,
                            1,
                            (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                        mXPos = hitX;
                        mYPos = hitY;
                        mVelX = FP_FromInteger(0);
                        MapFollowMe_401D30(1);
                        mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                        return;
                    }
                    default:
                        break;
                }
            }
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                if (mCurrentMotion == eAbeMotions::Motion_30_HopMid_4264D0)
                {
                    mVelX = FP_FromRaw(mVelX.fpValue / 2);
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mXPos += mSpriteScale * FP_FromInteger(5);
                    }
                    else
                    {
                        mXPos -= mSpriteScale * FP_FromInteger(5);
                    }
                    field_120_x_vel_slow_by = FP_FromDouble(0.55);
                    mYPos += mSpriteScale * FP_FromInteger(2);
                    mCurrentMotion = eAbeMotions::Motion_96_HopToFall_4298A0;
                    mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                }
            }
        }
    }
}

void Abe::Motion_31_HopLand_426940()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 2 && Input().IsAnyPressed(sInputKey_Hop))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
        mBaseAliveGameObjectLastAnimFrame = 5;
    }
    else
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (!ToLeftRightMovement_422AA0())
            {
                ToIdle_422D50();
            }
        }
    }
}

void Abe::Motion_32_RunJumpBegin_427440()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        FollowLift_42EE90();

        mXPos += mVelX;
        if (mAnim.mCurrentFrame == 0)
        {
            Environment_SFX_42A220(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 0x7FFF, this);
        }

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            BaseAliveGameObjectLastLineYPos = mYPos;

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mVelX = (mSpriteScale * FP_FromDouble(-7.6));
            }
            else
            {
                mVelX = (mSpriteScale * FP_FromDouble(7.6));
            }

            mVelY = (mSpriteScale * FP_FromDouble(-9.6));
            mYPos += mVelY;
            VOnTrapDoorOpen();
            mCurrentMotion = eAbeMotions::Motion_33_RunJumpMid_426FA0;
            BaseAliveGameObjectCollisionLine = nullptr;
        }
    }
}

void Abe::Motion_33_RunJumpMid_426FA0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (field_1A0_portal)
    {
        IntoPortalStates_4262A0();
        return;
    }
    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        if (gMap.TLV_Get_At_446260(
                FP_GetExponent(mVelX + mXPos),
                FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(50)),
                FP_GetExponent(mVelX + mXPos),
                FP_GetExponent(mYPos - mSpriteScale * FP_FromInteger(50)),
                ReliveTypes::eElumStart))
        {
            SfxPlayMono(SoundEffect::RingBellHammer_9, 0, 0);
        }
        mNextMotion = eAbeMotions::Motion_0_Idle_423520;
        ToKnockback_422D90(1, 1);
        return;
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    auto bCollision = InAirCollision_4019C0(&pLine, &hitX, &hitY, FP_FromDouble(1.8));

    SetActiveCameraDelayedFromDir_401C90();

    if (bCollision)
    {
        switch (pLine->mLineType)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eDynamicCollision_32:
            case eLineTypes::eBackgroundDynamicCollision_36:
            {
                BaseAliveGameObjectCollisionLine = pLine;
                mCurrentMotion = eAbeMotions::Motion_34_RunJumpLand_427560;
                mXPos = hitX;
                mYPos = hitY;

                PSX_RECT rect = VGetBoundingRect();
                rect.y += 5;
                rect.h += 5;

                if (pLine->mLineType == eLineTypes::eDynamicCollision_32)
                {
                    VOnCollisionWith(
                        {rect.x, rect.y},
                        {rect.w, rect.h},
                        ObjListPlatforms_50766C,
                        1,
                        (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                }
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                return;
            }
        }
    }
    else
    {
        auto pHoist = static_cast<relive::Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos - mVelX),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos - mVelX),
            FP_GetExponent(mYPos),
            ReliveTypes::eHoist));

        bool checkCollision = false;
        if (pHoist)
        {
            BaseAliveGameObjectPathTLV = pHoist;

            if (IsSameScaleAsHoist(pHoist, this) && (IsFacingSameDirectionAsHoist(pHoist, this)) && pHoist->mHoistType != relive::Path_Hoist::Type::eOffScreen)
            {
                checkCollision = true;
            }
        }
        else
        {
            auto pEdgeTlv = static_cast<relive::Path_Edge*>(gMap.TLV_Get_At_446260(
                FP_GetExponent(mXPos - mVelX),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos - mVelX),
                FP_GetExponent(mYPos),
                ReliveTypes::eEdge));
            BaseAliveGameObjectPathTLV = pEdgeTlv;
            if (pEdgeTlv && pEdgeTlv->mCanGrab == relive::reliveChoice::eYes)
            {
                if (isEdgeGrabbable(pEdgeTlv, this))
                {
                    checkCollision = true;
                }
            }
        }
        if (checkCollision)
        {
            if (sCollisions->Raycast(
                    mXPos,
                    mYPos - mSpriteScale * FP_FromInteger(100),
                    mXPos,
                    mYPos,
                    &pLine,
                    &hitX,
                    &hitY,
                    mSpriteScale != FP_FromDouble(0.5) ? kFgFloor : kBgFloor))
            {
                mXPos = FP_FromInteger(
                    (BaseAliveGameObjectPathTLV->mBottomRightX + BaseAliveGameObjectPathTLV->mTopLeftX) / 2);
                MapFollowMe_401D30(TRUE);
                mYPos = hitY;
                mCurrentMotion = eAbeMotions::Motion_68_LedgeHangWobble_428E50;
                mShadow->mFlags.Set(Shadow::Flags::eShadowAtBottom);
                BaseAliveGameObjectCollisionLine = pLine;
                mVelX = FP_FromInteger(0);
                mVelY = FP_FromInteger(0);
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                if (!mLiftPoint)
                {
                    if (pLine->mLineType == eLineTypes ::eDynamicCollision_32 ||
                        pLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
                    {
                        PSX_RECT rect = VGetBoundingRect();
                        rect.y += 5;
                        rect.h += 5;

                        VOnCollisionWith(
                            {rect.x, rect.y},
                            {rect.w, rect.h},
                            ObjListPlatforms_50766C,
                            1,
                            (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                    }
                }
            }
        }
        else
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                nullptr,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (mCurrentMotion == eAbeMotions::Motion_33_RunJumpMid_426FA0)
        {
            field_120_x_vel_slow_by = FP_FromDouble(0.75);
            mCurrentMotion = eAbeMotions::Motion_97_RunJumpToFall_429930;
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
        }
    }
}

void Abe::Motion_34_RunJumpLand_427560()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        MapFollowMe_401D30(1);

        if (Input().IsAnyPressed(sInputKey_Left))
        {
            if (!(sInputKey_Hop & field_10C_prev_held))
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    if (Input().IsAnyPressed(sInputKey_Run))
                    {
                        mCurrentMotion = eAbeMotions::Motion_56_RunJumpLandRun_4278E0;
                        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                    }
                    else
                    {
                        if (WallHit_401930(mSpriteScale * FP_FromInteger(50), -ScaleToGridSize(mSpriteScale)))
                        {
                            mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
                            mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                        }
                        else
                        {
                            mCurrentMotion = eAbeMotions::Motion_57_RunJumpLand_Walk_427980;
                            mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
                        }
                    }
                    return;
                }

                mCurrentMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
                mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                return;
            }

            field_1A0_portal = IntoBirdPortal_402350(3);
            if (field_1A0_portal)
            {
                if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                {
                    field_1A0_portal = nullptr;
                }
            }

            if (field_1A0_portal)
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }

            mCurrentMotion = eAbeMotions::Motion_32_RunJumpBegin_427440;
            field_10C_prev_held = 0;
            return;
        }

        if (Input().IsAnyPressed(sInputKey_Right))
        {
            if (sInputKey_Hop & field_10C_prev_held)
            {
                field_1A0_portal = IntoBirdPortal_402350(3);
                if (field_1A0_portal)
                {
                    if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }

                mCurrentMotion = eAbeMotions::Motion_32_RunJumpBegin_427440;
                field_10C_prev_held = 0;
                return;
            }

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mCurrentMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
                Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                return;
            }

            if (Input().IsAnyPressed(sInputKey_Run))
            {
                mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                mCurrentMotion = eAbeMotions::Motion_56_RunJumpLandRun_4278E0;
            }
            else
            {
                if (WallHit_401930(mSpriteScale * FP_FromInteger(50), ScaleToGridSize(mSpriteScale)))
                {
                    mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
                    mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                }
                else
                {
                    mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
                    mCurrentMotion = eAbeMotions::Motion_57_RunJumpLand_Walk_427980;
                }
            }
        }
        else
        {
            if (!(sInputKey_Hop & field_10C_prev_held))
            {
                mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                    Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                }
                else
                {
                    mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
                    Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                }
                return;
            }

            field_1A0_portal = IntoBirdPortal_402350(3);
            if (field_1A0_portal)
            {
                if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
                {
                    field_1A0_portal = nullptr;
                }
            }

            if (field_1A0_portal)
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }

            mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
            field_10C_prev_held = 0;
        }
    }
}

bool Abe::CheckForPortalAndRunJump()
{
    if (field_10C_prev_held & sInputKey_Hop)
    {
        field_1A0_portal = IntoBirdPortal_402350(3);
        if (field_1A0_portal)
        {
            if (field_1A0_portal->mPortalType != relive::Path_BirdPortal::PortalType::eAbe)
            {
                field_1A0_portal = nullptr;
            }
            else
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }
        }

        mCurrentMotion = eAbeMotions::Motion_32_RunJumpBegin_427440;
        field_10C_prev_held = 0;
        return true;
    }
    return false;
}

void Abe::Motion_35_RunLoop_425060()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToKnockback_422D90(1, 1);
        return;
    }

    MoveForward_422FC0();

    if (mCurrentMotion != eAbeMotions::Motion_35_RunLoop_425060)
    {
        return;
    }

    if (mAnim.mCurrentFrame == 0 || mAnim.mCurrentFrame == 8)
    {
        if (!field_2A8_flags.Get(e2A8_Bit3_WalkToRun))
        {
            field_2A8_flags.Set(e2A8_Bit3_WalkToRun);
            MapFollowMe_401D30(TRUE);
        }

        CheckForPortalAndRunJump();
    }
    else if (mAnim.mCurrentFrame == 4 || mAnim.mCurrentFrame == 12)
    {
        Environment_SFX_42A220(EnvironmentSfx::eRunningFootstep_2, 0, 0x7FFF, this);

        // Snap
        if (!field_2A8_flags.Get(e2A8_Bit3_WalkToRun))
        {
            field_2A8_flags.Set(e2A8_Bit3_WalkToRun);
            MapFollowMe_401D30(TRUE);
        }

        // Check turning in middle of run (pressing reverse direction of movement)
        if ((mVelX > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left)) || (mVelX < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right)))
        {
            mCurrentMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
            Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
            field_10C_prev_held = 0;
            return;
        }

        // Check jumping into a portal
        if (CheckForPortalAndRunJump())
        {
            return;
        }

        // Running to roll
        if (field_10C_prev_held & sInputKey_FartRoll)
        {
            mCurrentMotion = eAbeMotions::Motion_40_RunToRoll_427AE0;

            // For some reason dont clear released in the frame 12 case
            if (mAnim.mCurrentFrame == 4)
            {
                field_10E_released_buttons = 0;
            }
            field_10C_prev_held = 0;
            return;
        }

        // No longer running
        if (!Input().IsAnyPressed(sInputKey_Right) && !Input().IsAnyPressed(sInputKey_Left))
        {
            mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
            Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
            field_10C_prev_held = 0;
            return;
        }

        // Continue running
        if (Input().IsAnyPressed(sInputKey_Run))
        {
            field_10C_prev_held = 0;
            return;
        }

        // Stop running
        FP gridSize = {};
        if (mVelX >= FP_FromInteger(0))
        {
            gridSize = ScaleToGridSize(mSpriteScale);
        }
        else
        {
            gridSize = -ScaleToGridSize(mSpriteScale);
        }

        if (WallHit_401930(mSpriteScale * FP_FromInteger(50), gridSize))
        {
            ToKnockback_422D90(1, 1);
        }
        else
        {
            if (mAnim.mCurrentFrame == 4)
            {
                mCurrentMotion = eAbeMotions::Motion_52_RunToWalk_4255E0;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_53_MidRunToWalk_4256E0;
            }
        }

        field_10C_prev_held = 0;
    }
    else
    {
        field_2A8_flags.Clear(e2A8_Bit3_WalkToRun);
    }
}

void Abe::Motion_36_DunnoBegin_423260()
{
    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Mudokon_SFX(MudSounds::eDunno_15, 0, 0, this);

        if (Input().IsAnyPressed(sInputKey_DoAction | sInputKey_ThrowItem))
        {
            mCurrentMotion = eAbeMotions::Motion_37_DunnoMid_4232C0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_38_DunnoEnd_423310;
        }
    }
}

void Abe::Motion_37_DunnoMid_4232C0()
{
    FollowLift_42EE90();

    if (!Input().IsAnyPressed(sInputKey_DoAction | sInputKey_ThrowItem) || mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_38_DunnoEnd_423310;
    }
}

void Abe::Motion_38_DunnoEnd_423310()
{
    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_39_CrouchTurn_4288C0()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);

            if (mNextMotion == eAbeMotions::Motion_0_Idle_423520)
            {
                mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
            }
            else
            {
                mCurrentMotion = mNextMotion;
                mNextMotion = 0;
            }
        }
    }
    else
    {
        Environment_SFX_42A220(EnvironmentSfx::eGenericMovement_9, 0, 0x7FFF, this);
    }
}

void Abe::Motion_40_RunToRoll_427AE0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(20), mVelX))
    {
        ToKnockback_422D90(1, 1);
        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (mCurrentMotion == eAbeMotions::Motion_40_RunToRoll_427AE0)
            {
                mCurrentMotion = eAbeMotions::Motion_25_RollLoop_427BB0;
            }
        }
    }
}

void Abe::Motion_41_StandingToRun_425530()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    field_10C_prev_held |= Input().Pressed();

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_42_SneakLoop_424BB0()
{
    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
        return;
    }

    MoveForward_422FC0();

    if (mCurrentMotion == eAbeMotions::Motion_42_SneakLoop_424BB0)
    {
        if (mAnim.mCurrentFrame == 3)
        {
            FP directedScale = {};
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                directedScale = -ScaleToGridSize(mSpriteScale);
            }
            else
            {
                directedScale = ScaleToGridSize(mSpriteScale);
            }

            if (WallHit_401930(mSpriteScale * FP_FromInteger(50), directedScale) || (mVelX > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left)) || (mVelX < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right)) || !Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
            {
                mCurrentMotion = eAbeMotions::Motion_48_SneakToIdle_424F80;
            }
            return;
        }

        if (mAnim.mCurrentFrame == 6)
        {
            Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
            MapFollowMe_401D30(1);

            if (Input().IsAnyPressed(sInputKey_Right | sInputKey_Left) && !Input().IsAnyPressed(sInputKey_Sneak))
            {
                mCurrentMotion = eAbeMotions::Motion_44_SneakToWalk_4249A0;
                field_10C_prev_held = 0;
                return;
            }

            field_10C_prev_held = 0;
            return;
        }

        if (mAnim.mCurrentFrame != 13)
        {
            if (mAnim.mCurrentFrame != 16)
            {
                return;
            }

            Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
            MapFollowMe_401D30(1);

            if (Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
            {
                if (!Input().IsAnyPressed(sInputKey_Sneak))
                {
                    mCurrentMotion = eAbeMotions::Motion_46_MidSneakToWalk_424AA0;
                }
            }
            field_10C_prev_held = 0;
            return;
        }

        FP directedScale = {};
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            directedScale = -ScaleToGridSize(mSpriteScale);
        }
        else
        {
            directedScale = ScaleToGridSize(mSpriteScale);
        }

        if (WallHit_401930(mSpriteScale * FP_FromInteger(50), directedScale) || (mVelX > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left)) || (mVelX < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right)) || !Input().IsAnyPressed(sInputKey_Right | sInputKey_Left))
        {
            mCurrentMotion = eAbeMotions::Motion_49_MidSneakToIdle_424FF0;
        }
    }
}

void Abe::Motion_43_WalkToSneak_424790()
{
    field_10C_prev_held |= Input().Pressed();

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(10));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(10));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_42_SneakLoop_424BB0;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_44_SneakToWalk_4249A0()
{
    field_10C_prev_held |= Input().Pressed();

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_45_MidWalkToSneak_424890()
{
    field_10C_prev_held |= Input().Pressed();

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(10));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(10));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 42;
        mBaseAliveGameObjectLastAnimFrame = 10;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_46_MidSneakToWalk_424AA0()
{
    field_10C_prev_held |= Input().Pressed();

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 1;
        mBaseAliveGameObjectLastAnimFrame = 9;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_47_SneakBegin_424ED0()
{
    field_10C_prev_held |= Input().Pressed();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_42_SneakLoop_424BB0;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_48_SneakToIdle_424F80()
{
    if (mAnim.mCurrentFrame == 0)
    {
        Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
    }

    MoveForward_422FC0();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);
        ToIdle_422D50();
    }
}

void Abe::Motion_49_MidSneakToIdle_424FF0()
{
    if (!mAnim.mCurrentFrame)
    {
        Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
    }

    MoveForward_422FC0();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);

        ToIdle_422D50();
    }
}

void Abe::Motion_50_WalkToRun_424560()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
        field_10C_prev_held = 0;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_51_MidWalkToRun_424670()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(4));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 35;
        mBaseAliveGameObjectLastAnimFrame = 8;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_52_RunToWalk_4255E0()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_53_MidRunToWalk_4256E0()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(9));
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 1;
        mBaseAliveGameObjectLastAnimFrame = 9;
    }

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_54_RunTurnToRun_425EA0()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);
        }
    }
}

void Abe::Motion_55_RunTurnToWalk_425F70()
{
    field_10C_prev_held |= Input().Pressed();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);


    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
            mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);
        }
    }
}

void Abe::Motion_56_RunJumpLandRun_4278E0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
        }
    }
}

void Abe::Motion_57_RunJumpLand_Walk_427980()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
        }
    }
}

void Abe::Motion_58_ToSpeak_42F8D0()
{
    FollowLift_42EE90();

    field_10C_prev_held |= Input().Held();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = DoGameSpeak_42F5C0(field_10C_prev_held);
        if (mCurrentMotion == -1)
        {
            ToIdle_422D50();
        }
        else
        {
            EventBroadcast(kEventSpeaking, this);
        }
        field_10C_prev_held = 0;
    }
}

void Abe::Motion_59_DeathDropFall_42CBE0()
{
    mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);

    FollowLift_42EE90();

    if (field_114_gnFrame == 0)
    {
        field_120_x_vel_slow_by = FP_FromInteger(0);
        field_124_unused = 0;
        mVelX = FP_FromInteger(0);
        mVelY = FP_FromInteger(0);
        field_118_timer = sGnFrame + 90;
        field_114_gnFrame = 1;
    }
    else if (field_114_gnFrame == 1)
    {
        if (static_cast<s32>(sGnFrame) == field_118_timer - 30)
        {
            SND_SEQ_Play_477760(SeqId::eHitBottomOfDeathPit_10, 1, 65, 65);
        }
        else if (static_cast<s32>(sGnFrame) == field_118_timer - 24)
        {
            Environment_SFX_42A220(EnvironmentSfx::eFallingDeathScreamHitGround_15, 0, 0x7FFF, this);

            relive_new ScreenShake(true);
        }
        else if (static_cast<s32>(sGnFrame) >= field_118_timer)
        {
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit6_bShrivel);
            mCurrentMotion = eAbeMotions::Motion_60_Dead_42C4C0;
            field_114_gnFrame = 0;
            mHealth = FP_FromInteger(0);
            MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_14, this, 1, 0);
        }
    }
}

void Abe::Motion_60_Dead_42C4C0()
{
    mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);
    FollowLift_42EE90();

    switch (field_114_gnFrame)
    {
        case 0:
        {
            EventBroadcast(kEventHeroDying, this);
            field_118_timer = sGnFrame + 30;
            field_120_x_vel_slow_by = FP_FromInteger(0);
            field_124_unused = 0;
            mVelX = FP_FromInteger(0);
            mVelY = FP_FromInteger(0);
            field_10C_prev_held = 0;
            field_114_gnFrame++;

            auto aux = 0;
            if (BaseAliveGameObjectPathTLV && BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eDeathDrop)
            {
                aux = 60;
            }
            else
            {
                aux = 15;
            }
            const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mYPos + FP_FromInteger(15);
            const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mXPos;
            relive_new DeathBirdParticle(
                xpos,
                ypos,
                (Math_NextRandom() % 8) + field_118_timer + aux,
                1,
                mSpriteScale);

            return;
        }
        case 1:
        {
            EventBroadcast(kEventHeroDying, this);
            if (!(sGnFrame % 4))
            {
                auto aux = 0;
                if (BaseAliveGameObjectPathTLV && BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eDeathDrop)
                {
                    aux = 60;
                }
                else
                {
                    aux = 15;
                }
                const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mYPos + FP_FromInteger(15);
                const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mXPos;
                relive_new DeathBirdParticle(
                    xpos,
                    ypos,
                    (Math_NextRandom() % 8) + field_118_timer + aux,
                    0,
                    mSpriteScale);
            }
            mSpriteScale -= FP_FromDouble(0.008);

            mRGB.r -= 2;
            mRGB.g -= 2;
            mRGB.b -= 2;
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                field_118_timer = sGnFrame + 60;
                if (BaseAliveGameObjectPathTLV)
                {
                    if (BaseAliveGameObjectPathTLV->mTlvType == ReliveTypes::eDeathDrop)
                    {
                        field_118_timer = (sGnFrame + 60) + 45;
                    }
                }
                field_114_gnFrame++;
                MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_14, this, 1, 0);
            }
            return;
        }
        case 2:
        {
            EventBroadcast(kEventHeroDying, this);
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                field_114_gnFrame++;
            }
            return;
        }
        case 3:
        {
            EventBroadcast(kEventHeroDying, this);
            if (field_158_pDeathFadeout)
            {
                field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
                field_158_pDeathFadeout->mBaseGameObjectRefCount--;
            }
            field_158_pDeathFadeout = relive_new DeathFadeOut(Layer::eLayer_FadeFlash_40, 1, 0, 8, TPageAbr::eBlend_2);
            field_158_pDeathFadeout->mBaseGameObjectRefCount++;

            if (field_164_pCircularFade)
            {
                field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                field_164_pCircularFade = nullptr;
            }
            field_114_gnFrame++;
            return;
        }
        case 4:
        {
            EventBroadcast(kEventHeroDying, this);
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                if (!field_104_pending_resource_count)
                {
                    VOnTrapDoorOpen();
                    BaseAliveGameObjectCollisionLine = nullptr;
                    if (gElum)
                    {
                        if (!gElum->mRespawnOnDead)
                        {
                            gElum->mBaseGameObjectFlags.Set(Options::eDead);
                        }
                    }
                    if (!field_1A4_resources.res[0])
                    {
                        field_1A4_resources.res[0] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
                        field_1A4_resources.res[10] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
                        field_1A4_resources.res[38] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
                        field_1A4_resources.res[9] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);
                        field_1A4_resources.res[61] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
                        if (gElum)
                        {
                            if (gElum->mRespawnOnDead)
                            {
                                gElum->VLoadUnmountedResources_411260();
                            }
                            else
                            {
                                ResourceManager::FreeResource_455550(
                                    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 0, 0));
                            }
                        }
                    }
                    field_118_timer = sGnFrame + 8;
                    field_114_gnFrame++;
                    //todo never used? dword_507720 = 0;
                }
            }
            return;
        }
        case 5:
        {
            EventBroadcast(kEventDeathReset, this);
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                mCurrentMotion = eAbeMotions::Motion_61_Respawn_42CD20;
                field_118_timer = sGnFrame + 2;
                field_114_gnFrame = 0;
                MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 1, 0);
                if (field_168_ring_pulse_timer && field_16C_bHaveShrykull)
                {
                    Abe::Free_Shrykull_Resources_42F4C0();
                }
                else if (mContinueLevel != EReliveLevelIds::eRuptureFarmsReturn || mContinuePath != 6)
                {
                    field_168_ring_pulse_timer = 0;
                }
                field_130_say = -1;
                mShadow->mFlags.Clear(Shadow::Flags::eEnabled);
            }
            return;
        }
        default:
            return;
    }
}

void Abe::Motion_61_Respawn_42CD20()
{
    // This will crash the game if abe didnt touch a checkpoint yet

    if (gAttract_507698)
    {
        // Depending on the randomn seed value abe can die in a demo, if so the checkpoint save will load
        // depending on the saved camera number on returning the main menu this can crash. Hack fix it
        // by killing abe so the bad save cant get loaded before we return to the menu.
        LOG_WARNING("Destroying abe to prevent game crash, he isnt supposed to die in a demo!");
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        sActiveHero = nullptr;
        sControlledCharacter = nullptr;
        return;
    }

    mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);
    FollowLift_42EE90();
    EventBroadcast(kEventResetting, this);

    // TODO: states
    switch (field_114_gnFrame)
    {
        case 0:
        {
            mHealth = FP_FromInteger(1);
            if (field_19C_throwable_count != 0)
            {
                if (gpThrowableArray_50E26C)
                {
                    gpThrowableArray_50E26C->Remove(field_19C_throwable_count);
                }
            }
            field_19C_throwable_count = 0;

            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                if (mLiftPoint)
                {
                    if (mLiftPoint->mBaseGameObjectFlags.Get(Options::eDrawable_Bit4))
                    {
                        mLiftPoint->VRemove(this);
                        mLiftPoint->mBaseGameObjectRefCount--;
                        mLiftPoint = nullptr;
                    }
                }
                if (mContinueCamera > 300u)
                {
                    mContinueCamera = gMap.mCurrentCamera;
                    mContinuePath = gMap.mCurrentPath;
                    mContinueLevel = gMap.mCurrentLevel;

                    PSX_Point camPos = {};
                    gMap.GetCurrentCamCoords(&camPos);
                    mContinueTopLeft.x = camPos.x + 512;
                    mContinueTopLeft.y = camPos.y + 240;
                }
                SaveGame::LoadFromMemory(&gSaveBuffer_505668, 0);
                if (field_19C_throwable_count)
                {
                    LoadRockTypes(MapWrapper::FromAO(gSaveBuffer_505668.field_234_current_level), gSaveBuffer_505668.field_236_current_path);
                    if (!gpThrowableArray_50E26C)
                    {
                        gpThrowableArray_50E26C = relive_new ThrowableArray();
                    }
                    gpThrowableArray_50E26C->Add(field_19C_throwable_count);
                }
                field_114_gnFrame = 1;
                mCurrentMotion = eAbeMotions::Motion_61_Respawn_42CD20;
            }
            break;
        }
        case 1:
        {
            mCurrentLevel = mContinueLevel;
            mCurrentPath = mContinuePath;
            mXPos = FP_FromInteger(mContinueTopLeft.x);
            mYPos = FP_FromInteger(mContinueTopLeft.y) + mSpriteScale * FP_FromInteger(30);

            BaseAliveGameObjectLastLineYPos = mYPos;

            mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, field_2A8_flags.Get(Flags_2A8::eAbeSpawnDir));
            MapFollowMe_401D30(TRUE);
            SetTint(sAbeTints_4C6438, gMap.mCurrentLevel);
            if (gElum)
            {
                gElum->mSpriteScale = mSpriteScale;
            }
            if (mSpriteScale == FP_FromDouble(0.5))
            {
                mAnim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
                mScale = Scale::Bg;
                if (gElum)
                {
                    gElum->mAnim.mRenderLayer = Layer::eLayer_ZapLinesMudsElum_Half_9;
                    gElum->mScale = Scale::Bg;
                }
            }
            else
            {
                mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                mScale = Scale::Fg;
                if (gElum)
                {
                    gElum->mAnim.mRenderLayer = Layer::eLayer_ZapLinesElumMuds_28;
                    gElum->mScale = Scale::Fg;
                }
            }
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            EventBroadcast(kEventDeathResetEnd, this);

            //TODO not used?
            //if (dword_507720)
            //{
            //    *(_BYTE *) (dword_507720 + 6) |= 4u;
            //}
            mBaseAliveGameObjectFlags.Clear(Flags_10A::e10A_Bit5_Electrocuted);

            field_158_pDeathFadeout->Init(Layer::eLayer_FadeFlash_40, 0, 1, 8);
            field_158_pDeathFadeout->mBaseGameObjectRefCount--;
            field_158_pDeathFadeout = nullptr;
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
            field_118_timer = sGnFrame + 60;
            field_114_gnFrame = 2;
            break;
        }
        case 2:
        {
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                auto xDiff = pScreenManager->CamXPos();
                auto yDiff = pScreenManager->CamYPos();

                for (s32 i = 0; i < 8; i++)
                {
                    auto pDove = relive_new Dove(
                        AnimId::Dove_Flying,
                        xDiff + FP_FromInteger(Math_NextRandom() * 2),
                        yDiff - FP_FromInteger(Math_NextRandom() % 32),
                        mSpriteScale);
                    if (pDove)
                    {
                        pDove->AsJoin(
                            mXPos + FP_FromInteger((Math_NextRandom() % 16) - 8),
                            mYPos + FP_FromInteger((Math_NextRandom() % 16) - 20));
                        pDove->mSpriteScale = mSpriteScale;
                    }
                }
                SfxPlayMono(SoundEffect::RespawnDove_17, 0, this);
                field_118_timer = sGnFrame + 45;
                field_114_gnFrame = 3;
            }
            break;
        }
        case 3:
        {
            if (field_118_timer - sGnFrame == 10)
            {
                SfxPlayMono(SoundEffect::Respawn_22, 90, 0);
            }
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                New_DestroyOrCreateObject_Particle_419D00(
                    mXPos,
                    mSpriteScale * FP_FromInteger(25) + mYPos,
                    mSpriteScale);
                field_114_gnFrame = 4;
                field_118_timer = sGnFrame + 2;
            }
            break;
        }
        case 4:
        {
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                mShadow->mFlags.Set(Shadow::Flags::eEnabled);
                mShadow->mFlags.Clear(Shadow::Flags::eShadowAtBottom);
                MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit8_bLandSoft);
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                mBaseGameObjectFlags.Set(Options::eDrawable_Bit4);
                mCurrentMotion = eAbeMotions::Motion_3_Fall_42E7F0;

                relive_new Flash(Layer::eLayer_Above_FG1_39, 255u, 0, 255u);
                field_106_shot = 0;
                field_2A8_flags.Clear(Flags_2A8::e2A8_Bit6_bShrivel);
                field_114_gnFrame = sGnFrame;
            }
            break;
        }
        default:
            return;
    }
}

using elumSpawn = decltype(&Elum::Spawn);
const elumSpawn dword_4CF550[] = {
    nullptr,
    nullptr,
    &Elum::Spawn,
    &Elum::Spawn,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &Elum::Spawn,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr};

void Abe::Motion_62_LoadedSaveSpawn_45ADD0()
{
    EventBroadcast(kEventResetting, this);

    if (field_114_gnFrame)
    {
        auto pSaveData = field_2AC_pSaveData;
        mYPos = FP_FromInteger(pSaveData->field_228_ypos);
        mXPos = FP_FromInteger(pSaveData->field_224_xpos);

        PathLine* pLine2 = nullptr;
        FP hitX2 = {};
        FP hitY2 = {};
        if (sCollisions->Raycast(
                sActiveHero->mXPos,
                sActiveHero->mYPos - FP_FromInteger(60),
                sActiveHero->mXPos,
                sActiveHero->mYPos + FP_FromInteger(60),
                &pLine2,
                &hitX2,
                &hitY2,
                CollisionMask(static_cast<eLineTypes>(pSaveData->field_23A_mode_mask))))
        {
            sActiveHero->BaseAliveGameObjectCollisionLine = pLine2;
            sActiveHero->mYPos = hitY2;
            sActiveHero->mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
        }
        else
        {
            sActiveHero->mCurrentMotion = eAbeMotions::Motion_3_Fall_42E7F0;
        }
        sActiveHero->field_2A8_flags.Clear(Flags_2A8::e2A8_Bit8_bLandSoft);
        sActiveHero->BaseAliveGameObjectLastLineYPos = sActiveHero->mYPos;
        sActiveHero->field_110_state.raw = static_cast<s16>(pSaveData->field_244_stone_state);
        sActiveHero->field_114_gnFrame = pSaveData->field_248_gnFrame;
        sActiveHero->mBaseAliveGameObjectLastAnimFrame = pSaveData->field_240_last_anim_frame;
        sActiveHero->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pSaveData->field_23C_ah_flipX & 1);
        sActiveHero->MapFollowMe_401D30(TRUE);
        sActiveHero->mAnim.mFlags.Set(AnimFlags::eBit3_Render);
        if (sActiveHero->field_19C_throwable_count)
        {
            if (!gpThrowableArray_50E26C)
            {
                LoadRockTypes(MapWrapper::FromAO(gSaveBuffer_505668.field_234_current_level), gSaveBuffer_505668.field_236_current_path);

                gpThrowableArray_50E26C = relive_new ThrowableArray();
            }
            gpThrowableArray_50E26C->Add(sActiveHero->field_19C_throwable_count);
        }
        if (pSaveData->field_264_bInfiniteGrenades == -1)
        {
            LoadRockTypes(EReliveLevelIds::eRuptureFarmsReturn, 19);
            if (!gpThrowableArray_50E26C)
            {
                gpThrowableArray_50E26C = relive_new ThrowableArray();
            }
            gpThrowableArray_50E26C->Add(1);
            gInfiniteGrenades_5076EC = 1;
        }
        else
        {
            gInfiniteGrenades_5076EC = 0;
        }
        if (pSaveData->field_25A_bElumExists)
        {
            if (!gElum)
            {
                Elum::Spawn(Guid{});
            }

            ResourceManager::LoadResourceFile_455270("ANEPRMNT.BAN", 0);
            ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
            gElum->mBaseGameObjectFlags.Clear(Options::eUpdatable_Bit2);
            gElum->mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
            gElum->mContinueRect = pSaveData->field_28C_elum_continue_rect;
            gElum->mContinueZoneNumber = pSaveData->field_294_continue_zone_number;
            gElum->field_142_zone_number = pSaveData->field_296_elum_zone_number;
            gElum->mContinuePath = pSaveData->field_298_elum_continue_path;
            gElum->mContinueLevel = MapWrapper::FromAO(pSaveData->field_29A_continue_level);
            gElum->mContinueSpriteScale = pSaveData->field_29C_elum_sprite_scale;
            gElum->mRespawnOnDead = pSaveData->field_25E_bElumRespawnOnDead;
            gElum->mCurrentLevel = MapWrapper::FromAO(pSaveData->field_260_elum_lvl_number);
            gElum->mCurrentPath = pSaveData->field_262_elum_path_number;
            gElum->mXPos = FP_FromInteger(pSaveData->field_268_elum_xpos);
            gElum->mYPos = FP_FromInteger(pSaveData->field_26C_elum_ypos);
            gElum->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pSaveData->field_272_elum_flipX & 1);
            gElum->mBaseAliveGameObjectLastAnimFrame = 0;
            gElum->field_120_bUnknown = 1;
            gElum->mDontFollowAbe = pSaveData->field_276_bDontFollowAbe;
            gElum->field_128_brain_idx = pSaveData->field_278_brain_idx;
            gElum->field_12A_brain_sub_state = pSaveData->field_27A_elum_brain_state;
            gElum->field_12C_honey_xpos = static_cast<s16>(pSaveData->field_27C_honey_xpos);
            gElum->field_146_honey_ypos = pSaveData->field_280_honey_ypos;
            gElum->field_130_unused = pSaveData->field_284_unused;

            gElum->field_170_flags.Set(Elum::Flags_170::eFoundHoney_Bit4, pSaveData->field_28B_elum_FoundHoney & 1);
            gElum->field_170_flags.Set(Elum::Flags_170::eFalling_Bit3, pSaveData->field_28A_elum_Falling & 1);
            gElum->field_170_flags.Set(Elum::Flags_170::eStungByBees_Bit2, pSaveData->field_289_elum_StungByBees & 1);
            if (gElum->mCurrentPath == sActiveHero->mCurrentPath)
            {
                if (pSaveData->field_270_elum_line_type != -1)
                {
                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions->Raycast(
                            gElum->mXPos,
                            gElum->mYPos - FP_FromInteger(60),
                            gElum->mXPos,
                            gElum->mYPos + FP_FromInteger(60),
                            &pLine,
                            &hitX,
                            &hitY,
                            CollisionMask(static_cast<eLineTypes>(pSaveData->field_270_elum_line_type))))
                    {
                        gElum->BaseAliveGameObjectCollisionLine = pLine;
                        gElum->mCurrentMotion = eElumMotions::Motion_1_Idle_412990;
                        gElum->mPreviousMotion = eElumMotions::Motion_1_Idle_412990;
                    }
                    else
                    {
                        gElum->mCurrentMotion = eElumMotions::Motion_21_Land_414A20;
                        gElum->mPreviousMotion = eElumMotions::Motion_21_Land_414A20;
                    }
                }
            }
            else
            {
                //TODO fix this madness
                gElum->BaseAliveGameObjectCollisionLine = reinterpret_cast<PathLine*>(-2);
            }
            if (gElum->field_170_flags.Get(Elum::Flags_170::eFoundHoney_Bit4))
            {
                if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElmHoneyAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ELMHONEY.BAN", 0);
                }
                gElum->mCurrentMotion = eElumMotions::Motion_25_LickingHoney_415B50;
                gElum->mPreviousMotion = eElumMotions::Motion_25_LickingHoney_415B50;
            }
            gElum->MapFollowMe_401D30(TRUE);
            gElum->mBaseGameObjectFlags.Set(Options::eUpdatable_Bit2);
            gElum->mAnim.mFlags.Set(AnimFlags::eBit3_Render);
        }
    }
    else
    {
        field_114_gnFrame = 1;
    }
}

void Abe::Motion_63_TurnToRun_42A0A0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        MoveForward_422FC0();

        if (mCurrentMotion == eAbeMotions::Motion_63_TurnToRun_42A0A0)
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
            }
        }
    }
}

void Abe::Motion_64_LedgeAscend_428B60()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 0)
    {
        Environment_SFX_42A220(EnvironmentSfx::eExhaustingHoistNoise_10, 0, 0x7FFF, this);
    }
    if (mAnim.mCurrentFrame == 4)
    {
        Environment_SFX_42A220(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 0x7FFF, this);
        mShadow->mFlags.Clear(Shadow::eShadowAtBottom);
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);
        ToIdle_422D50();
    }
}

void Abe::Motion_65_LedgeDescend_428C00()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 2)
    {
        Environment_SFX_42A220(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 0x7FFF, this);
        mShadow->mFlags.Toggle(Shadow::eShadowAtBottom);
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
    }
}

void Abe::Motion_66_LedgeHang_428D90()
{
    FollowLift_42EE90();

    mShadow->mFlags.Set(Shadow::eShadowAtBottom);

    if (Input().IsAnyPressed(sInputKey_Up))
    {
        mCurrentMotion = eAbeMotions::Motion_64_LedgeAscend_428B60;
    }
    else if (Input().IsAnyPressed(sInputKey_Down))
    {
        VOnTrapDoorOpen();

        BaseAliveGameObjectCollisionLine = nullptr;
        mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
        mYPos += (mSpriteScale * FP_FromInteger(80)) + FP_FromInteger(3);
        BaseAliveGameObjectLastLineYPos = mYPos;
        mShadow->mFlags.Clear(Shadow::eShadowAtBottom);
    }
}

void Abe::Motion_67_ToOffScreenHoist_428C50()
{
    mYPos -= (mSpriteScale * FP_FromInteger(80));

    mShadow->mFlags.Toggle(Shadow::eShadowAtBottom);

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    if (sCollisions->Raycast(
            mXPos,
            mYPos - (mSpriteScale * FP_FromInteger(80)),
            mXPos,
            mYPos,
            &pLine,
            &hitX,
            &hitY,
            mSpriteScale != FP_FromDouble(0.5) ? kFgFloor : kBgFloor))
    {
        mYPos = hitY;
        BaseAliveGameObjectCollisionLine = pLine;
        mVelY = FP_FromInteger(0);
        if (!mLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes ::eDynamicCollision_32 ||
                BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
            {
                PSX_RECT bRect = VGetBoundingRect();
                bRect.y += 5;
                bRect.h += 5;

                VOnCollisionWith(
                    {bRect.x, bRect.y},
                    {bRect.w, bRect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
            }
        }
        mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
    }
    else
    {
        mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
    }
}

void Abe::Motion_68_LedgeHangWobble_428E50()
{
    if (mAnim.mCurrentFrame == 0)
    {
        if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
        {
            field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);
        }
    }
    else if (mAnim.mCurrentFrame == 2)
    {
        if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
        {
            field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            Mudokon_SFX(MudSounds::eBeesStruggle_18, 45, -200, this);
        }
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    FollowLift_42EE90();

    if (Input().IsAnyPressed(sInputKey_Up))
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
        mCurrentMotion = eAbeMotions::Motion_64_LedgeAscend_428B60;
    }
    else
    {
        if (Input().IsAnyPressed(sInputKey_Down))
        {
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);

            VOnTrapDoorOpen();
            BaseAliveGameObjectCollisionLine = nullptr;

            mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
            mYPos += (mSpriteScale * FP_FromInteger(80)) + FP_FromInteger(3);
            mShadow->mFlags.Clear(Shadow::eShadowAtBottom);
            BaseAliveGameObjectLastLineYPos = mYPos;
        }
        else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
        }
    }
}

void Abe::Motion_69_RingRopePullHang_4299B0()
{
    if (field_160_pRope->vIsNotBeingPulled())
    {
        mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
        field_160_pRope->mBaseGameObjectRefCount--;
        field_160_pRope = nullptr;
        mVelY = FP_FromInteger(0);
    }
}

void Abe::Motion_70_Knockback_428FB0()
{
    ElumFree_4228F0();

    if (field_1A0_portal)
    {
        field_1A0_portal->VKillPortalClipper();
        field_1A0_portal = nullptr;
    }

    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_4231B0();
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
            {
                mVelX = FP_FromInteger(0);
            }

            MoveWithVelocity_4257F0(FP_FromDouble(0.7));

            if ((gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarms
                 || gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn
                 || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom)
                && mAnim.mCurrentFrame == 7)
            {
                Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
                EventBroadcast(kEventNoise, this);
                EventBroadcast(kEventSuspiciousNoise, this);
            }
        }
        else
        {
            Motion_3_Fall_42E7F0();

            if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0 || mCurrentMotion == eAbeMotions::Motion_98_LandSoft_42ED40)
            {
                field_114_gnFrame = sGnFrame + 10;
                mCurrentMotion = eAbeMotions::Motion_70_Knockback_428FB0;
                Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
            }
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if ((BaseAliveGameObjectCollisionLine || !mAnim.mFlags.Get(AnimFlags::eBit3_Render)) && !field_104_pending_resource_count)
        {
            if (!field_1A4_resources.res[0])
            {
                field_1A4_resources.res[0] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
                field_1A4_resources.res[10] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
                field_1A4_resources.res[38] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
                field_1A4_resources.res[9] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);

                if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit3_ElumMountBegin))
                {
                    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
                }
            }

            if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
            {
                if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
                {
                    mCurrentMotion = eAbeMotions::Motion_71_KnockbackGetUp_429240;
                }
                else
                {
                    ToDieFinal_42C400();
                }
            }
        }
    }
}

void Abe::Motion_71_KnockbackGetUp_429240()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_72_PushWall_4292A0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mCurrentFrame == 10)
    {
        if (Math_NextRandom() <= 127u)
        {
            Environment_SFX_42A220(EnvironmentSfx::eExhaustingHoistNoise_10, 0, 0x7FFF, this);
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_73_RollingKnockback_4291D0()
{
    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_4231B0();
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
        {
            if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
            {
                mCurrentMotion = eAbeMotions::Motion_71_KnockbackGetUp_429240;
            }
            else
            {
                ToDieFinal_42C400();
            }
        }
    }
}

void Abe::Motion_74_JumpIntoWell_430EC0()
{
    mShadow->mFlags.Clear(Shadow::Flags::eEnabled);

    if (mSpriteScale == FP_FromDouble(0.5))
    {
        mAnim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
    }
    else
    {
        mAnim.mRenderLayer = Layer::eLayer_BeforeWell_22;
    }

    Motion_77_WellBegin_430F10();
}

void Abe::Motion_75_ToInsideOfAWellLocal_431090()
{
    Motion_78_InsideWellLocal_4310A0();
}

void Abe::Motion_76_ToWellShotOut_431720()
{
    Motion_79_WellShotOut_431730();
}

void Abe::Motion_77_WellBegin_430F10()
{
    EventBroadcast(kEventNoise, this);
    if (mAnim.mCurrentFrame > 10)
    {
        mShadow->mFlags.Clear(Shadow::Flags::eEnabled);

        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellLocal);
        if (!BaseAliveGameObjectPathTLV)
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eWellExpress);
        }

        const s16 xpos = FP_GetExponent(mXPos);
        const auto tlv_mid_x = (BaseAliveGameObjectPathTLV->mBottomRightX + BaseAliveGameObjectPathTLV->mTopLeftX) / 2;
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
        field_114_gnFrame = 15;
        SfxPlayMono(SoundEffect::WellEnter_25, 0, this);

        switch (mCurrentMotion)
        {
            case eAbeMotions::Motion_77_WellBegin_430F10:
            {
                mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
                break;
            }
            case eAbeMotions::Motion_80_430EF0:
            {
                mCurrentMotion = eAbeMotions::Motion_81_InsideWellExpress_431320;
                break;
            }
            case eAbeMotions::Motion_83_430F00:
            {
                mCurrentMotion = eAbeMotions::Motion_84_ToInsideWellLocal_431080;
                break;
            }
            case eAbeMotions::Motion_74_JumpIntoWell_430EC0:
            {
                mCurrentMotion = eAbeMotions::Motion_75_ToInsideOfAWellLocal_431090;
                break;
            }
            default:
            {
                LOG_ERROR("Unrecognized state called: " << mCurrentMotion);
                ALIVE_FATAL("Unrecognized state in Abe::Motion_77_WellBegin_430F10 called!");
                break;
            }
        }
    }
}

ALIVE_VAR(1, 0x4C73CC, FP, gPointlessWellScale_4C73CC, FP_FromDouble(1.8));

void Abe::Motion_78_InsideWellLocal_4310A0()
{
    const s32 old_gnFrame = field_114_gnFrame;
    field_114_gnFrame--;

    if (old_gnFrame == 0)
    {
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellLocal);

        if (!BaseAliveGameObjectPathTLV)
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eWellExpress);
        }

        auto pWellBase = static_cast<relive::Path_WellBase*>(BaseAliveGameObjectPathTLV);

        field_120_x_vel_slow_by = FP_FromInteger(0);

        if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit4_snap_abe))
        {
            // Snap to exit point
            mVelX = (mSpriteScale * (FP_FromInteger(pWellBase->mExitX) / FP_FromInteger(100)));
            mVelY = (mSpriteScale * (FP_FromInteger(pWellBase->mExitY) / FP_FromInteger(100)));
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
        }
        else
        {
            if (SwitchStates_Get(pWellBase->mSwitchId))
            {
                auto pLocalWell = static_cast<relive::Path_WellLocal*>(BaseAliveGameObjectPathTLV);
                mVelX = (mSpriteScale * FP_FromInteger(pLocalWell->mOnDestX) / FP_FromInteger(100));
                mVelY = (mSpriteScale * FP_FromInteger(pLocalWell->mOnDestY) / FP_FromInteger(100));
            }
            else
            {
                mVelX = (mSpriteScale * FP_FromInteger(pWellBase->mOffDestX) / FP_FromInteger(100));
                mVelY = (mSpriteScale * FP_FromInteger(pWellBase->mOffDestY) / FP_FromInteger(100));
            }
        }

        MapFollowMe_401D30(1);

        mYPos += mVelY;
        gPointlessWellScale_4C73CC = FP_FromDouble(1.8);

        if (mVelX >= FP_FromInteger(0))
        {
            mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
        }
        else
        {
            mAnim.mFlags.Set(AnimFlags::eBit5_FlipX);
        }

        SfxPlayMono(SoundEffect::WellExit_24, 0, this);

        mCurrentMotion++; // can be motion 76 and 79 maybe more?

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

void Abe::Motion_79_WellShotOut_431730()
{
    if (mVelY >= FP_FromInteger(0))
    {
        Motion_3_Fall_42E7F0();
    }
    else
    {
        mVelY += (mSpriteScale * gPointlessWellScale_4C73CC);

        mXPos += mVelX;
        mYPos += mVelY;

        SetActiveCameraDelayedFromDir_401C90();
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted)
        || (mCurrentMotion != eAbeMotions::Motion_79_WellShotOut_431730
            && mCurrentMotion != eAbeMotions::Motion_85_ToWellShotOut_431710
            && mCurrentMotion != eAbeMotions::Motion_76_ToWellShotOut_431720))
    {
        if (mSpriteScale == FP_FromDouble(0.5))
        {
            mAnim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
        }
        else
        {
            mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
        }

        mShadow->mFlags.Set(Shadow::eEnabled);
    }

    if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0)
    {
        mHealth = FP_FromInteger(1);
        mCurrentMotion = eAbeMotions::Motion_98_LandSoft_42ED40;
    }
}

void Abe::Motion_80_ToWellBegin_430EF0()
{
    Motion_77_WellBegin_430F10();
}

void Abe::Motion_81_InsideWellExpress_431320()
{
    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(mXPos),
        FP_GetExponent(mYPos),
        ReliveTypes::eWellLocal);

    if (!BaseAliveGameObjectPathTLV)
    {
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            FP_GetExponent(mXPos),
            FP_GetExponent(mYPos),
            ReliveTypes::eWellExpress);
    }


    if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit4_snap_abe))
    {
        mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
        return;
    }

    relive::Path_WellExpress* pExpressWell = static_cast<relive::Path_WellExpress*>(BaseAliveGameObjectPathTLV);
    if (SwitchStates_Get(pExpressWell->mSwitchId))
    {
        field_190_level = pExpressWell->mOnDestLevel;
        field_192_path = pExpressWell->mOnDestPath;
        field_194_camera = pExpressWell->mOnDestCamera;
        field_196_door_id = pExpressWell->mOnOtherWellId;
    }
    else
    {
        field_190_level = pExpressWell->mOffDestLevel;
        field_192_path = pExpressWell->mOffDestPath;
        field_194_camera = pExpressWell->mOffDestCamera;
        field_196_door_id = pExpressWell->mOffOtherWellId;
    }

    field_120_x_vel_slow_by = FP_FromInteger(0);

    if (gMap.mCurrentLevel == EReliveLevelIds::eLines)
    {
        if (field_190_level == EReliveLevelIds::eForest)
        {
            if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit12_bParamoniaDone))
            {
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                field_114_gnFrame = 0;
                mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
                Motion_78_InsideWellLocal_4310A0();
                return;
            }
            LOG_INFO("set bParamoniaDone");
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit12_bParamoniaDone);
        }

        if (field_190_level == EReliveLevelIds::eDesert)
        {
            if (field_2A8_flags.Get(Flags_2A8::e2A8_eBit13_bScrabaniaDone))
            {
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                field_114_gnFrame = 0;
                mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
                Motion_78_InsideWellLocal_4310A0();
                return;
            }
            LOG_INFO("set bScrabinaDone");
            field_2A8_flags.Set(Flags_2A8::e2A8_eBit13_bScrabaniaDone);
        }
    }
    if (field_190_level != gMap.mCurrentLevel
        || field_192_path != gMap.mCurrentPath
        || field_194_camera != gMap.mCurrentCamera)
    {
        field_114_gnFrame = 1;
        if (pExpressWell->mMovieId)
        {
            gMap.SetActiveCam(field_190_level, field_192_path, field_194_camera, CameraSwapEffects::ePlay1FMV_5, pExpressWell->mMovieId, 0);
        }
        else
        {
            gMap.SetActiveCam(field_190_level, field_192_path, field_194_camera, CameraSwapEffects::eInstantChange_0, 0, 0);
        }
        mCurrentMotion = eAbeMotions::Motion_82_WellExpressShotOut_4315A0;
    }
    else
    {
        Motion_82_WellExpressShotOut_4315A0();
        mVelX = FP_FromInteger(0);
        mVelY = FP_FromInteger(0);
        mYPos = mYPos - mVelY;
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
        mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
    }
}

void Abe::Motion_82_WellExpressShotOut_4315A0()
{
    PSX_Point camCoords = {};
    gMap.GetCurrentCamCoords(&camCoords);
    relive::Path_WellBase* pWell = nullptr;
    relive::Path_TLV* pTlvIter = nullptr;
    do
    {
        pTlvIter = gMap.TLV_Get_At_446060(
            pTlvIter,
            FP_FromInteger(camCoords.x + 256),
            FP_FromInteger(camCoords.y + 120),
            FP_FromInteger(camCoords.x + 624),
            FP_FromInteger(camCoords.y + 360));
        if (!pTlvIter)
        {
            break;
        }

        if ((pTlvIter->mTlvType == ReliveTypes::eWellLocal || pTlvIter->mTlvType == ReliveTypes::eWellExpress) && static_cast<relive::Path_WellBase*>(pTlvIter)->mOtherWellId == field_196_door_id)
        {
            pWell = static_cast<relive::Path_WellBase*>(pTlvIter);
            break;
        }
    }
    while (pTlvIter);


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

        mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;

        BaseAliveGameObjectPathTLV = pWell;
        mXPos = FP_FromInteger((pWell->mTopLeftX + pWell->mBottomRightX) / 2);
        mYPos = FP_FromInteger(pWell->mBottomRightY);
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit4_snap_abe);
    }
    else
    {
        mXPos = FP_FromInteger(camCoords.x + 450);
        mYPos = FP_FromInteger(camCoords.y + 320);
        mVelX = (mSpriteScale * -FP_FromDouble(2.7));
        mVelY = (mSpriteScale * -FP_FromInteger(15));
    }
}

void Abe::Motion_83_ToWellBegin_430F00()
{
    Motion_77_WellBegin_430F10();
}

void Abe::Motion_84_ToInsideWellLocal_431080()
{
    Motion_78_InsideWellLocal_4310A0();
}

void Abe::Motion_85_ToWellShotOut_431710()
{
    Motion_79_WellShotOut_431730();
}

void Abe::Motion_86_FallLandDie_42EDD0()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mCurrentFrame == 0)
    {
        SfxPlayMono(SoundEffect::KillEffect_78, 85, 0);
        SND_SEQ_Play_477760(SeqId::eHitBottomOfDeathPit_10, 1, 95, 95);
        relive_new ScreenShake(true);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (static_cast<s32>(sGnFrame) >= field_114_gnFrame)
        {
            ToDieFinal_42C400();
        }
    }
}

void Abe::Motion_87_ToFall_428FA0()
{
    Motion_3_Fall_42E7F0();
}

ALIVE_VAR(1, 0x507728, s32, gCounter_507728, 0);
ALIVE_VAR(1, 0x50772C, u8**, gpDemoPlaybackRes_50772C, nullptr);
ALIVE_VAR(1, 0x507730, s32, sAbeSound_507730, 0);
ALIVE_VAR(1, 0x507724, BellSong*, sBellSong, nullptr);

void Abe::Motion_88_HandstoneBegin_430590()
{
    switch (field_110_state.stone)
    {
        case StoneStates::eHandstoneStart_0:
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
            {
                ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSpotliteAOResID, 1, 0);
                field_164_pCircularFade = Make_Circular_Fade(
                    mXPos,
                    mYPos,
                    mSpriteScale,
                    1,
                    0);

                field_164_pCircularFade->mAnim.mFlags.Set(
                    AnimFlags::eBit5_FlipX,
                    mAnim.mFlags.Get(AnimFlags::eBit5_FlipX));

                field_110_state.stone = StoneStates::eGetHandstoneType_1;
                SfxPlayMono(SoundEffect::IngameTransition_107, 90, 0);
                BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    ReliveTypes::eDemoPlaybackStone);
                if (!BaseAliveGameObjectPathTLV)
                    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        ReliveTypes::eBellSongStone);
                if (!BaseAliveGameObjectPathTLV)
                {
                    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        ReliveTypes::eMovieHandStone);
                    sAbeSound_507730 = SFX_Play_Pitch(SoundEffect::HandstoneTransition_13, 127, -300, 0);
                    if (!BaseAliveGameObjectPathTLV)
                        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                            FP_GetExponent(mXPos),
                            FP_GetExponent(mYPos),
                            FP_GetExponent(mXPos),
                            FP_GetExponent(mYPos),
                            ReliveTypes::eHandStone);
                }

                if (BaseAliveGameObjectPathTLV)
                {
                    mHandStoneType = BaseAliveGameObjectPathTLV->mTlvType;
                    switch (mHandStoneType)
                    {
                        case ReliveTypes::eMovieHandStone:
                        {
                            mMovieStone = static_cast<relive::Path_MovieStone*>(BaseAliveGameObjectPathTLV);
                            break;
                        }
                        case ReliveTypes::eBellSongStone:
                        {
                            mBellsongStone = static_cast<relive::Path_BellsongStone*>(BaseAliveGameObjectPathTLV);
                            break;
                        }
                        case ReliveTypes::eDemoPlaybackStone:
                        {
                            ALIVE_FATAL("never expected eDemoPlaybackStone to be used");
                            //field_174_pathStone.demoId = ptlv->field_18_data.demoId;
                            break;
                        }
                        case ReliveTypes::eHandStone:
                        {
                            mHandStone = static_cast<relive::Path_HandStone*>(BaseAliveGameObjectPathTLV);
                            break;
                        }
                        default:
                            return;
                    }
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_89_HandstoneEnd_430E80;
                }
            }
            break;
        }
        case StoneStates::eGetHandstoneType_1:
        {
            if (field_164_pCircularFade->VDone())
            {
                switch (mHandStoneType)
                {
                    case ReliveTypes::eMovieHandStone:
                    {
                        auto pFmvInfo = Path_Get_FMV_Record_434680(
                            gMap.mCurrentLevel,
                            mMovieStone->mMovieId);
                        u32 aux = 0;
                        Get_fmvs_sectors_44FEB0(
                            pFmvInfo->field_0_pName, 0, 0, &aux, 0, 0);

                        relive_new Movie(
                            pFmvInfo->field_4_id,
                            aux,
                            static_cast<s8>(pFmvInfo->field_6),
                            pFmvInfo->field_A,
                            pFmvInfo->field_C_volume);

                        field_110_state.stone = StoneStates::eHandstoneMovieDone_2;
                        break;
                    }
                    case ReliveTypes::eBellSongStone:
                    {
                        sBellSong = relive_new BellSong(
                            mBellsongStone->mType,
                            Code_Convert(mBellsongStone->mCode1, mBellsongStone->mCode2));

                        SwitchStates_Do_Operation(mBellsongStone->mSwitchId, relive::reliveSwitchOp::eSetTrue);
                        field_110_state.stone = StoneStates::eBellSongDone_4;
                        break;
                    }
                    case ReliveTypes::eDemoPlaybackStone:
                        ALIVE_FATAL("never expected eDemoPlaybackStone to be used");
                        /*field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                        field_164_pCircularFade = nullptr;
                        field_110_state.stone = StoneStates::eFreeDemoPlaybackResources_3;
                        gCounter_507728 = 2;
                        gpDemoPlaybackRes_50772C = ResourceManager::GetLoadedResource(ResourceManager::Resource_Plbk, field_174_pathStone.demoId, 1, 0);
                        if (gpDemoPlaybackRes_50772C)
                        {
                            relive_new DemoPlayback(gpDemoPlaybackRes_50772C, 1);
                        }
                        break;*/
                    case ReliveTypes::eHandStone:
                    {
                        mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                        field_110_state.stone = StoneStates::eWaitForInput_6;
                        field_16E_cameraIdx = 1;
                        field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                        field_164_pCircularFade = 0;
                        field_158_pDeathFadeout = relive_new DeathFadeOut(Layer::eLayer_FadeFlash_40, 0, 0, 8, TPageAbr::eBlend_2);
                        field_190_level = gMap.mCurrentLevel;
                        field_192_path = gMap.mCurrentPath;
                        field_194_camera = gMap.mCurrentCamera;
                        gMap.SetActiveCam(
                            mHandStone->mLevel1,
                            mHandStone->mPath1,
                            mHandStone->mCameraId1,
                            CameraSwapEffects::eInstantChange_0, 0, 0);
                        break;
                    }
                    default:
                        return;
                }
            }
            break;
        }
        case StoneStates::eHandstoneMovieDone_2:
        {
            if (sMovie_ref_count_9F309C == 0)
            {
                gPsxDisplay.PutCurrentDispEnv();
                pScreenManager->DecompressCameraToVRam(
                    reinterpret_cast<u16**>(gMap.field_34_camera_array[0]->field_C_ppBits));
                pScreenManager->MoveImage();
                pScreenManager->EnableRendering();
                field_164_pCircularFade->VFadeIn(0, 0);
                field_110_state.stone = StoneStates::eHandstoneEnd_5;
            }
            break;
        }
        case StoneStates::eFreeDemoPlaybackResources_3:
        {
            gCounter_507728--;
            if (gCounter_507728 == 0)
            {
                field_110_state.stone = StoneStates::eHandstoneEnd_5;
                ResourceManager::FreeResource_455550(gpDemoPlaybackRes_50772C);
                field_164_pCircularFade = Make_Circular_Fade(
                    mXPos,
                    mYPos,
                    mSpriteScale,
                    0,
                    0);

                field_164_pCircularFade->mAnim.mFlags.Set(
                    AnimFlags::eBit5_FlipX,
                    mAnim.mFlags.Get(AnimFlags::eBit5_FlipX));
            }
            break;
        }
        case StoneStates::eBellSongDone_4:
        {
            if (sBellSong->mDone)
            {
                sBellSong->mBaseGameObjectFlags.Set(Options::eDead);
                field_164_pCircularFade->VFadeIn(0, 0);
                field_110_state.stone = StoneStates::eHandstoneEnd_5;
            }
            break;
        }
        case StoneStates::eHandstoneEnd_5:
        {
            if (field_164_pCircularFade->VDone())
            {
                field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                mCurrentMotion = eAbeMotions::Motion_89_HandstoneEnd_430E80;
                field_164_pCircularFade = 0;
                if (sAbeSound_507730)
                {
                    SND_Stop_Channels_Mask(sAbeSound_507730);
                    sAbeSound_507730 = 0;
                }
                ResourceManager::FreeResource_455550(
                    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSpotliteAOResID, 0, 0));
            }
            break;
        }
        case StoneStates::eWaitForInput_6:
        {
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                if (Input().IsAnyHeld(0xF0))
                {
                    field_158_pDeathFadeout->Init(Layer::eLayer_FadeFlash_40, 1, 0, 8);
                    field_110_state.stone = StoneStates::eSetActiveCamToAbeOrWaitForInput_7;
                    SfxPlayMono(SoundEffect::IngameTransition_107, 90, 0);
                }
            }
            break;
        }
        case StoneStates::eSetActiveCamToAbeOrWaitForInput_7:
        {
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                Path_Stone_camera camera = {};
                switch (field_16E_cameraIdx)
                {
                    case 0:
                        camera.level = MapWrapper::ToAO(mHandStone->mLevel1);
                        camera.path = mHandStone->mPath1;
                        camera.camera = mHandStone->mCameraId1;
                        break;

                    case 1:
                        camera.level = MapWrapper::ToAO(mHandStone->mLevel2);
                        camera.path = mHandStone->mPath2;
                        camera.camera = mHandStone->mCameraId2;
                        break;

                    case 2:
                        camera.level = MapWrapper::ToAO(mHandStone->mLevel3);
                        camera.path = mHandStone->mPath3;
                        camera.camera = mHandStone->mCameraId3;
                        break;

                    default:
                        LOG_ERROR("CameraIdx out of bounds " << field_16E_cameraIdx);
                }
                if (field_16E_cameraIdx > 2 || (camera.level == LevelIds::eForestChase_14 || camera.level == LevelIds::eDesertEscape_15))
                {
                    field_110_state.stone = StoneStates::eSetActiveCamToAbe_12;
                }
                else
                {
                    field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
                    field_110_state.stone = StoneStates::eWaitForInput_6;
                    field_16E_cameraIdx++;
                    field_158_pDeathFadeout = relive_new DeathFadeOut(Layer::eLayer_FadeFlash_40, 0, 0, 8, TPageAbr::eBlend_2);
                    gMap.SetActiveCam(MapWrapper::FromAO(camera.level), camera.path, camera.camera, CameraSwapEffects::eInstantChange_0, 0, 0);
                }
            }
            break;
        }
        case StoneStates::eSetActiveCamToAbe_12:
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                field_110_state.stone = StoneStates::eCircularFadeExit_13;
                gMap.SetActiveCam(field_190_level, field_192_path, field_194_camera, CameraSwapEffects::eInstantChange_0, 0, 0);
            }
            break;
        case StoneStates::eCircularFadeExit_13:
        {
            field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
            field_158_pDeathFadeout = 0;

            field_164_pCircularFade = Make_Circular_Fade(mXPos, mYPos, mSpriteScale, 0, 0);
            field_110_state.stone = StoneStates::eHandstoneEnd_5;
            field_164_pCircularFade->mAnim.mFlags.Set(
                AnimFlags::eBit5_FlipX,
                mAnim.mFlags.Get(AnimFlags::eBit5_FlipX));

            if (sAbeSound_507730)
            {
                SND_Stop_Channels_Mask(sAbeSound_507730);
                sAbeSound_507730 = 0;
            }
            break;
        }
        default:
            return;
    }
}

void Abe::Motion_89_HandstoneEnd_430E80()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
    }
}

void Abe::Motion_90_GrenadeMachineUse_430EA0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
    }
}

void Abe::Motion_91_FallingFromGrab_429780()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }

    Motion_3_Fall_42E7F0();

    if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0)
    {
        mCurrentMotion = eAbeMotions::Motion_98_LandSoft_42ED40;
    }

    mPreviousMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
}

void Abe::Motion_92_ForceDownFromHoist_4297C0()
{
    if (field_114_gnFrame == 0)
    {
        mYPos += (mSpriteScale * FP_FromInteger(80));
        mShadow->mFlags.Clear(Shadow::eShadowAtBottom);
        VOnTrapDoorOpen();
        BaseAliveGameObjectCollisionLine = nullptr;
        BaseAliveGameObjectLastLineYPos = mYPos;
        field_114_gnFrame++;
    }

    Motion_3_Fall_42E7F0();
}

void Abe::Motion_93_WalkOffEdge_429840()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_94_RunOffEdge_429860()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_95_SneakOffEdge_429880()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_96_HopToFall_4298A0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mXPos += (mSpriteScale * FP_FromInteger(5));
    }
    else
    {
        mXPos -= (mSpriteScale * FP_FromInteger(5));
    }

    mVelY += (mSpriteScale * FP_FromInteger(4));

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }

    Motion_3_Fall_42E7F0();
}

void Abe::Motion_97_RunJumpToFall_429930()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_98_LandSoft_42ED40()
{
    FollowLift_42EE90();

    if (mAnim.mCurrentFrame == 2)
    {
        if (!(field_2A8_flags.Get(Flags_2A8::e2A8_Bit8_bLandSoft)))
        {
            EventBroadcast(kEventNoise, this);
            EventBroadcast(kEventSuspiciousNoise, this);
        }

        field_2A8_flags.Clear(Flags_2A8::e2A8_Bit8_bLandSoft);

        if (mPreviousMotion == eAbeMotions::Motion_3_Fall_42E7F0)
        {
            Environment_SFX_42A220(EnvironmentSfx::eLandingSoft_5, 0, 0x7FFF, this);
        }
        else
        {
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        }

        if (Input().IsAnyPressed(0xA000u))
        {
            ToLeftRightMovement_422AA0();
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_99_HoistBeginLong_426DC0()
{
    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mYPos;
        mVelY = (mSpriteScale * FP_FromInteger(-8)) * FP_FromDouble(1.3);
        mYPos += mVelY;
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_100_RollOffLedge_429950()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_101_LeverUse_429970()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_102_ElumWalkLoop_42DCA0()
{
    // Empty
}

void Abe::Motion_103_ElumIdle_42DCD0()
{
    if (!Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler | sInputKey_RightGameSpeakEnabler) || !Input().IsAnyHeld(0xF0))
    {
        if (Input().Held() == sInputKey_Down && !sDDCheat_FlyingEnabled_50771C)
        {
            ResourceManager::FreeResource_455550(field_1A4_resources.res[46]);
            field_104_pending_resource_count++;
            field_1A4_resources.res[46] = nullptr;
            ResourceManager::LoadResourceFile("ANEDSMNT.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
            mCurrentMotion = eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0;
        }
    }
    else
    {
        mCurrentMotion = eAbeMotions::Motion_115_ElumSpeak_4299F0;
        if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler))
        {
            if (Input().IsAnyHeld(sInputKey_GameSpeak2))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFollowMe_10);
                Mudokon_SFX(MudSounds::eFollowMe_4, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak4))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWait_12);
                Mudokon_SFX(MudSounds::eWait_6, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak1))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eHello_9);
                Mudokon_SFX(MudSounds::eHello_3, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak3))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eAnger_11);
                Mudokon_SFX(MudSounds::eAngry_5, 0, 0, this);
            }
        }

        if (Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler))
        {
            if (Input().IsAnyHeld(sInputKey_GameSpeak6))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleHigh_1);
                Mudokon_SFX(MudSounds::eWhistleHigh_1, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak5))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleLow_2);
                Mudokon_SFX(MudSounds::eWhistleLow_2, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak8))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eLaugh_4);
                Mudokon_SFX(MudSounds::eLaugh1_8, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak7))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFart_3);
                Mudokon_SFX(MudSounds::eFart_7, 0, 0, this);
            }
        }
    }
}

void Abe::Motion_104_ElumRunSlideStop_42DF00()
{
    // Empty
}

void Abe::Motion_105_ElumRunTurn_42DF10()
{
    // Empty
}

void Abe::Motion_106_Null_42DF20()
{
    // Empty
}

void Abe::Motion_107_ElumHopBegin_42DF30()
{
    // Empty
}

void Abe::Motion_108_ElumHopMid_42DF40()
{
    // Empty
}

void Abe::Motion_109_ElumHopLand_42DF50()
{
    // Empty
}

void Abe::Motion_110_ElumRunJumpBegin_42DF60()
{
    // Empty
}

void Abe::Motion_111_ElumRunJumpMid_42DF70()
{
    // Empty
}

void Abe::Motion_112_ElumRunJumpLand_42DF80()
{
    // Empty
}

void Abe::Motion_113_ElumTurn_42DF90()
{
    // Empty
}

void Abe::Motion_114_ElumRunLoop_42DFA0()
{
    // Empty
}

void Abe::Motion_115_ElumSpeak_4299F0()
{
    EventBroadcast(kEventSpeaking, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_103_ElumIdle_42DCD0;
    }
}

void Abe::Motion_116_Null_42DFB0()
{
    // Empty
}

void Abe::Motion_117_ElumWalkBegin_42DFC0()
{
    // Empty
}

void Abe::Motion_118_ElumRunBegin_42DFD0()
{
    // Empty
}

void Abe::Motion_119_Null_42DFE0()
{
    // Empty
}

void Abe::Motion_120_ElumRunToWalk_42DFF0()
{
    // Empty
}

void Abe::Motion_121_ElumMidRunToWalk_42E000()
{
    // Empty
}

void Abe::Motion_122_ElumRunTurnToRun_42E010()
{
    // Empty
}

void Abe::Motion_123_ElumRunTurnToWalk_42E020()
{
    // Empty
}

void Abe::Motion_124_ElumWalkEnd_42DCB0()
{
    // Empty
}

void Abe::Motion_125_ElumMidWalkEnd_42DCC0()
{
    // Empty
}

void Abe::Motion_126_ElumBeesStruggling_42E080()
{
    // Empty
}

void Abe::Motion_127_SlapBomb_429A20()
{
    if (sActiveHero->mAnim.mCurrentFrame >= 6)
    {
        if (field_15C_pThrowable)
        {
            field_15C_pThrowable->mBaseGameObjectRefCount--;
            field_15C_pThrowable->VOnPickUpOrSlapped();
            field_15C_pThrowable = nullptr;
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }
}

void Abe::Motion_128_KnockForward_429330()
{
    ElumFree_4228F0();

    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_4231B0();
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit3_Render))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            if (WallHit_401930(mSpriteScale * FP_FromInteger(50), mVelX))
            {
                mVelX = FP_FromInteger(0);
            }
            MoveWithVelocity_4257F0(FP_FromDouble(0.7));
        }
        else
        {
            Motion_3_Fall_42E7F0();

            if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0 || mCurrentMotion == eAbeMotions::Motion_98_LandSoft_42ED40)
            {
                mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                field_114_gnFrame = sGnFrame + 10;
            }
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if ((BaseAliveGameObjectCollisionLine || !mAnim.mFlags.Get(AnimFlags::eBit3_Render)) && !field_104_pending_resource_count)
        {
            if (!field_1A4_resources.res[0])
            {
                field_1A4_resources.res[0] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
                field_1A4_resources.res[10] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
                field_1A4_resources.res[38] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
                field_1A4_resources.res[9] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);

                if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit3_ElumMountBegin))
                {
                    ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
                }
            }

            if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
            {
                if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
                {
                    mCurrentMotion = eAbeMotions::Motion_130_KnockForwardGetUp_429560;
                }
                else
                {
                    ToDieFinal_42C400();
                }
            }
        }
    }
}

void Abe::Motion_129_RollingKnockForward_4294F0()
{
    if (mAnim.mCurrentFrame == 12)
    {
        FallOnBombs_4231B0();
    }

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
        {
            if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
            {
                mCurrentMotion = eAbeMotions::Motion_130_KnockForwardGetUp_429560;
            }
            else
            {
                ToDieFinal_42C400();
            }
        }
    }
}

void Abe::Motion_130_KnockForwardGetUp_429560()
{
    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_131_LiftUseUp_42F150()
{
    mCurrentMotion = MoveLiftUpOrDown_42F190(FP_FromInteger(-4));
}

void Abe::Motion_132_LiftUseDown_42F170()
{
    mCurrentMotion = MoveLiftUpOrDown_42F190(FP_FromInteger(4));
}

void Abe::Motion_133_LiftGrabBegin_42EF20()
{
    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);
    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);

    mVelY = FP_FromInteger(0);
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (Input().IsAnyPressed(sInputKey_Up))
        {
            if (!pLiftPoint->OnTopFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_131_LiftUseUp_42F150;
                return;
            }
        }
        else if (Input().IsAnyPressed(sInputKey_Down))
        {
            if (!pLiftPoint->OnBottomFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_132_LiftUseDown_42F170;
                return;
            }
        }
        mCurrentMotion = eAbeMotions::Motion_135_LiftGrabIdle_42F000;
    }
}

void Abe::Motion_134_LiftGrabEnd_42EFE0()
{
    mVelY = FP_FromInteger(0);
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_135_LiftGrabIdle_42F000()
{
    FollowLift_42EE90();

    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);
    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);

    mVelY = FP_FromInteger(0);

    if (gBeeInstanceCount > 0 && gBeesNearAbe)
    {
        mCurrentMotion = eAbeMotions::Motion_141_BeesStrugglingOnLift_42F390;
    }
    else
    {
        if (Input().IsAnyPressed(sInputKey_Up))
        {
            if (!pLiftPoint->OnTopFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_131_LiftUseUp_42F150;
            }
        }
        else if (Input().IsAnyPressed(sInputKey_Down))
        {
            if (!pLiftPoint->OnBottomFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_132_LiftUseDown_42F170;
            }
        }
        else
        {
            if (pLiftPoint->OnAnyFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_134_LiftGrabEnd_42EFE0;
            }
        }
    }
}

void Abe::Motion_136_ElumMountEnd_42E110()
{
    switch (mAnim.mCurrentFrame)
    {
        case 0:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                SfxPlayMono(SoundEffect::AbeGenericMovement_37, 0, this);
            }
            break;

        case 5:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eExhaustingElumMount_16, 0, 0x7FFF, this);
            }
            break;

        case 12:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eMountElumSmackNoise_17, 0, 0x7FFF, this);
                SfxPlayMono(SoundEffect::MountingElum_38, 0, this);
            }
            break;

        case 15:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eElumGetMountedNoise_18, 0, 0x7FFF, this);
            }
            break;

        default:
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            break;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (!field_104_pending_resource_count)
        {
            field_1A4_resources.res[46] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeWElmAOResID_100, 1, 0);
            field_1A4_resources.res[58] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kElumUnknownAOResID_112, 1, 0);
            mCurrentMotion = eAbeMotions::Motion_103_ElumIdle_42DCD0;
            sControlledCharacter = gElum;
            MusicController::static_PlayMusic(MusicController::MusicTypes::eAbeOnElum_1, nullptr, 0, 0);
            sActiveHero->mShadow->mFlags.Clear(Shadow::Flags::eEnabled);
            Environment_SFX_42A220(EnvironmentSfx::eAbeMountedElumNoise_19, 0, 0x7FFF, this);
        }
    }
}

void Abe::Motion_137_ElumUnmountBegin_42E2B0()
{
    if (!field_104_pending_resource_count && mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        while (!ResourceManager::FreeResource_455550(field_1A4_resources.res[58]))
        {
            // Empty
        }

        field_1A4_resources.res[58] = nullptr;
        field_104_pending_resource_count = 3;

        ResourceManager::LoadResourceFile("ABEBSIC.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        ResourceManager::LoadResourceFile("ANEPRMNT.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        ResourceManager::LoadResourceFile("ABENOELM.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

        if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, FALSE, FALSE))
        {
            field_104_pending_resource_count++;
            ResourceManager::LoadResourceFile("ABEOMM.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        }
        mCurrentMotion = eAbeMotions::Motion_138_ElumUnmountEnd_42E390;
    }
}

void Abe::Motion_138_ElumUnmountEnd_42E390()
{
    switch (mAnim.mCurrentFrame)
    {
        case 4:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                SfxPlayMono(SoundEffect::AbeGenericMovement_37, 17, this);
            }
            break;

        case 12:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eExhaustingElumMount_16, 0, 0x7FFF, this);
            }
            break;

        case 19:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eElumGetMountedNoise_18, 0, 0x7FFF, this);
            }
            break;

        case 20:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                SfxPlayMono(SoundEffect::MountingElum_38, 0, this);
            }
            break;

        default:
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            break;
    }

    if (mAnim.mCurrentFrame >= 28 && field_104_pending_resource_count == 0)
    {
        field_1A4_resources.res[0] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
        field_1A4_resources.res[61] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
        field_1A4_resources.res[10] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
        field_1A4_resources.res[38] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
        field_1A4_resources.res[9] = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);

        BaseAliveGameObjectCollisionLine = gElum->BaseAliveGameObjectCollisionLine;

        if (mLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->mLineType != eLineTypes ::eDynamicCollision_32 &&
                BaseAliveGameObjectCollisionLine->mLineType != eLineTypes::eBackgroundDynamicCollision_36)
            {
                mPreviousMotion = mCurrentMotion;
                VOnTrapDoorOpen();
                mCurrentMotion = mPreviousMotion;
            }
        }
        else
        {
            if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 ||
                BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
            {
                PSX_RECT bRect = VGetBoundingRect();
                bRect.y += 5;
                bRect.h += 5;
                VOnCollisionWith(
                    {bRect.x, bRect.y},
                    {bRect.w, bRect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
            }
        }
        sControlledCharacter = sActiveHero;
        MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
        sActiveHero->mShadow->mFlags.Clear(Shadow::Flags::eEnabled);
        ToIdle_422D50();
    }
}

void Abe::Motion_139_ElumMountBegin_42E090()
{
    if (!field_104_pending_resource_count && mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        while (!ResourceManager::FreeResource_455550(field_1A4_resources.res[61]))
        {
            // Empty
        }

        field_1A4_resources.res[61] = {};
        field_104_pending_resource_count = 1;

        ResourceManager::LoadResourceFile("ABEWELM.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_136_ElumMountEnd_42E110;
    }
}

void Abe::Motion_140_BeesStruggling_423F30()
{
    Motion_0_Idle_423520();
    if ((!gBeeInstanceCount || !gBeesNearAbe) && mCurrentMotion == eAbeMotions::Motion_140_BeesStruggling_423F30)
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_141_BeesStrugglingOnLift_42F390()
{
    LiftPoint* pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);

    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(12), 0);
    if (pLiftPoint)
    {
        mVelY = pLiftPoint->mVelY;
        if (pLiftPoint->mBaseGameObjectFlags.Get(Options::eDead))
        {
            VOnTrapDoorOpen();
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit1);
        }
        SetActiveCameraDelayedFromDir_401C90();
    }

    mVelY = pLiftPoint->mVelY;

    if (pLiftPoint->OnBottomFloor())
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_142_RockThrowStandingHold_429CE0()
{
    if (mAnim.mCurrentFrame >= 4)
    {
        if (Input().IsAnyPressed(sInputKey_Right | sInputKey_Left | sInputKey_Up | sInputKey_Down))
        {
            if (Input().IsAnyPressed(sInputKey_Right))
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_19D_throw_direction = 0;
                }
                else
                {
                    field_19D_throw_direction = 2;
                }
            }
            else if (Input().IsAnyPressed(sInputKey_Left))
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_19D_throw_direction = 2;
                }
                else
                {
                    field_19D_throw_direction = 0;
                }
            }
            else if (Input().IsAnyPressed(sInputKey_Up))
            {
                field_19D_throw_direction = 1;
            }
            else
            {
                field_19D_throw_direction = 3;
            }
            mCurrentMotion = eAbeMotions::Motion_143_RockThrowStandingThrow_429FD0;
        }
    }

    if (Input().IsAnyReleased(sInputKey_ThrowItem))
    {
        field_198_pThrowable->VToDead();
        field_198_pThrowable = nullptr;
        mCurrentMotion = eAbeMotions::Motion_144_RockThrowStandingEnd_429DE0;
        if (!gInfiniteGrenades_5076EC)
        {
            field_19C_throwable_count++;
        }
    }
}

void Abe::Motion_143_RockThrowStandingThrow_429FD0()
{
    if (mAnim.mCurrentFrame == 0)
    {
        SfxPlayMono(SoundEffect::AirStream_28, 0, this);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_144_RockThrowStandingEnd_429DE0()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_145_RockThrowCrouchingHold_428930()
{
    if (mAnim.mCurrentFrame >= 4)
    {
        if (Input().IsAnyPressed(sInputKey_Right | sInputKey_Left | sInputKey_Up | sInputKey_Down))
        {
            field_19D_throw_direction = 4;
            mCurrentMotion = eAbeMotions::Motion_146_RockThrowCrouchingThrow_4289F0;
            if (field_198_pThrowable->mBaseGameObjectTypeId == ReliveTypes::eMeat)
            {
                field_19D_throw_direction = 5;
            }
        }
    }

    if (Input().IsAnyReleased(sInputKey_ThrowItem))
    {
        field_198_pThrowable->VToDead();
        field_198_pThrowable = nullptr;
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
        if (!gInfiniteGrenades_5076EC)
        {
            field_19C_throwable_count++;
        }
    }
}

void Abe::Motion_146_RockThrowCrouchingThrow_4289F0()
{
    FollowLift_42EE90();

    if (!mAnim.mCurrentFrame)
    {
        SfxPlayMono(SoundEffect::AirStream_28, 0, this);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }
}

void Abe::Motion_147_ShotRolling_4295C0()
{
    ElumFree_4228F0();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    Motion_3_Fall_42E7F0();

    if (mCurrentMotion != eAbeMotions::Motion_147_ShotRolling_4295C0 && !gAbeInvulnerableCheat_5076E4)
    {
        mCurrentMotion = eAbeMotions::Motion_147_ShotRolling_4295C0;
        BaseAliveGameObjectCollisionLine = nullptr;
        mYPos += (mSpriteScale * FP_FromInteger(4));
    }

    if (!gMap.Is_Point_In_Current_Camera(
            mCurrentLevel,
            mCurrentPath,
            mXPos,
            mYPos,
            0))
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
        {
            mYPos += FP_FromInteger(240);
            Mudokon_SFX(MudSounds::eDeathDropScream_17, 0, 0, this);
            ToDeathDropFall_42C3D0();
        }
    }
}

void Abe::Motion_148_Shot_4296A0()
{
    ElumFree_4228F0();

    EventBroadcast(kEventNoise, this);
    EventBroadcast(kEventSuspiciousNoise, this);

    Motion_3_Fall_42E7F0();

    if (mCurrentMotion != eAbeMotions::Motion_148_Shot_4296A0 && !gAbeInvulnerableCheat_5076E4)
    {
        mCurrentMotion = eAbeMotions::Motion_148_Shot_4296A0;
        BaseAliveGameObjectCollisionLine = nullptr;
        mYPos += (mSpriteScale * FP_FromInteger(4));
    }

    if (!gMap.Is_Point_In_Current_Camera(
            mCurrentLevel,
            mCurrentPath,
            mXPos,
            mYPos,
            0))
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
        {
            mYPos += FP_FromInteger(240);
            Mudokon_SFX(MudSounds::eDeathDropScream_17, 0, 0, this);
            ToDeathDropFall_42C3D0();
        }
    }
}

void Abe::Motion_149_PickupItem_42A030()
{
    if (mAnim.mCurrentFrame == 7)
    {
        SfxPlayMono(SoundEffect::PickupItem_33, 0, this);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }

    if (sActiveHero->mAnim.mCurrentFrame >= 5)
    {
        if (field_15C_pThrowable)
        {
            field_15C_pThrowable->mBaseGameObjectRefCount--;
            field_15C_pThrowable->VOnPickUpOrSlapped();
            field_15C_pThrowable = nullptr;
        }
    }
}

void Abe::New_RandomizedChant_Particle()
{
    const auto xpos = mXPos + mSpriteScale * FP_FromInteger(40 * Math_NextRandom() / 256 - 20);
    const auto ypos = mYPos - (mSpriteScale * FP_FromInteger(30 * Math_NextRandom() / 256 + 30));
    New_Orb_Particle(
        xpos,
        ypos,
        mSpriteScale,
        Layer::eLayer_0);
}

void Abe::Motion_150_Chant_42FD50()
{
    FollowLift_42EE90();
    if (field_110_state.chant != ChantStates::eWaitForUnpossessing_3 && field_110_state.chant != ChantStates::eUnpossessing_4)
    {
        SND_SEQ_PlaySeq_4775A0(SeqId::eMudokonChant1_11, 0, 0);
    }

    switch (field_110_state.chant)
    {
        case ChantStates::eIdleChanting_0:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);
            auto pObjToPossess = FindObjectToPossess_421410();
            if (field_168_ring_pulse_timer)
            {
                if (!field_16C_bHaveShrykull)
                {
                    const PSX_RECT rect = VGetBoundingRect();
                    AbilityRing::Factory(
                        FP_FromInteger((rect.w + rect.x) / 2),
                        FP_FromInteger((rect.h + rect.y) / 2),
                        RingTypes::eExplosive_Emit_1);
                    field_168_ring_pulse_timer = 0;
                }
            }

            if ((mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame)
                 || mAnim.mCurrentFrame == 3)
                && !Input_IsChanting())
            {
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
                if (field_188_pOrbWhirlWind)
                {
                    field_188_pOrbWhirlWind->ToStop();
                    field_188_pOrbWhirlWind = nullptr;
                }
                return;
            }
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle();
            }
            if (static_cast<s32>(sGnFrame) >= field_114_gnFrame - 70)
            {
                if (pObjToPossess)
                {
                    if (!field_188_pOrbWhirlWind)
                    {
                        FP xPos = {};
                        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            xPos = mXPos + FP_FromInteger(-4);
                        }
                        else
                        {
                            xPos = mXPos + FP_FromInteger(4);
                        }
                        field_188_pOrbWhirlWind = relive_new OrbWhirlWind(
                            xPos,
                            mYPos - mSpriteScale * FP_FromInteger(38),
                            mSpriteScale);;
                    }
                }
                else
                {
                    field_114_gnFrame = sGnFrame + 70;
                    if (field_188_pOrbWhirlWind)
                    {
                        field_188_pOrbWhirlWind->ToStop();
                        field_188_pOrbWhirlWind = nullptr;
                    }
                }
            }

            if (static_cast<s32>(sGnFrame) > field_114_gnFrame)
            {
                field_18C_pObjToPossess = pObjToPossess;
                if (field_18C_pObjToPossess)
                {
                    field_18C_pObjToPossess->mBaseGameObjectRefCount++;
                    SFX_Play_Pitch(SoundEffect::PossessEffect_21, 0, -600, 0);
                    field_114_gnFrame = sGnFrame + 30;
                    field_110_state.chant = ChantStates::ePossessVictim_1;

                    const PSX_RECT rect = field_18C_pObjToPossess->VGetBoundingRect();
                    field_188_pOrbWhirlWind->ToSpin(
                        FP_FromInteger((rect.w + rect.x) / 2),
                        FP_FromInteger((rect.h + rect.y) / 2),
                        pObjToPossess);

                    relive_new PossessionFlicker(sActiveHero, 30, 128, 255, 255);
                }
            }
            break;
        }
        case ChantStates::ePossessVictim_1:
        {
            if (static_cast<s32>(sGnFrame) > field_114_gnFrame)
            {
                field_110_state.chant = ChantStates::ePossessedVictim_2;
                return;
            }
            if (field_18C_pObjToPossess)
            {
                if (field_18C_pObjToPossess->mBaseGameObjectFlags.Get(Options::eDead))
                {
                    field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                    field_18C_pObjToPossess = nullptr;
                }
            }
            if (field_18C_pObjToPossess)
            {
                if (field_18C_pObjToPossess->Is_In_Current_Camera() == CameraPos::eCamCurrent_0)
                {
                    return;
                }
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
                field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                field_18C_pObjToPossess = nullptr;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
            }
            if (field_188_pOrbWhirlWind)
            {
                field_188_pOrbWhirlWind->ToStop();
                field_188_pOrbWhirlWind = nullptr;
            }
            break;
        }
        case ChantStates::ePossessedVictim_2:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);
            field_188_pOrbWhirlWind = nullptr;
            if (field_18C_pObjToPossess)
            {
                if (field_18C_pObjToPossess->mBaseGameObjectFlags.Get(Options::eDead))
                {
                    field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                    field_18C_pObjToPossess = nullptr;
                }
            }
            if (field_18C_pObjToPossess)
            {
                sControlledCharacter = field_18C_pObjToPossess;
                field_18C_pObjToPossess->VPossessed();
                field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                field_18C_pObjToPossess = nullptr;
                if (sControlledCharacter->mBaseGameObjectTypeId == ReliveTypes::eSlig)
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit11_bLaughAtChantEnd);
                }

                relive_new PossessionFlicker(sControlledCharacter, 60, 128, 255, 255);

                SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);
                SFX_Play_Pitch(SoundEffect::PossessEffect_21, 70, 400, 0);
                field_110_state.chant = ChantStates::eWaitForUnpossessing_3;
            }
            else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
            }
            break;
        }
        case ChantStates::eWaitForUnpossessing_3:
        {
            if (sControlledCharacter == this)
            {
                relive_new PossessionFlicker(sControlledCharacter, 15, 128, 255, 255);

                field_110_state.chant = ChantStates::eUnpossessing_4;
                field_114_gnFrame = sGnFrame + 15;
            }
            break;
        }
        case ChantStates::eUnpossessing_4:
        {
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle();
            }
            if (static_cast<s32>(sGnFrame) > field_114_gnFrame)
            {
                if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
                {
                    mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
                }
            }
            break;
        }
        case ChantStates::eChantingForBirdPortal_6:
        {
            EventBroadcast(kEventSpeaking, this);
            EventBroadcast(kEventAbeOhm, this);
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle();
            }

            break;
        }
        default:
            return;
    }
}

void Abe::Motion_151_ChantEnd_430530()
{
    SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);

    FollowLift_42EE90();

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit11_bLaughAtChantEnd))
        {
            mCurrentMotion = eAbeMotions::Motion_12_Speak_42FBD0;
            Mudokon_SFX(MudSounds::eLaugh1_8, 0, 0, this);
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit11_bLaughAtChantEnd);
        }
        else
        {
            ToIdle_422D50();
        }
    }
}

void Abe::Motion_152_ElumFallOffEdge_42E030()
{
    // Empty
}

void Abe::Motion_153_ElumFall_42E040()
{
    // Empty
}

void Abe::Motion_154_ElumLand_42E050()
{
    // Empty
}

void Abe::Motion_155_ElumJumpToFall_42E060()
{
    // Empty
}

void Abe::Motion_156_DoorEnter_42D370()
{
    switch (field_110_state.door)
    {
        case AbeDoorStates::eAbeComesIn_0:
        {
            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_110_state.door = AbeDoorStates::eWaitABit_2;
                mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                field_118_timer = sGnFrame + 3;
            }
            return;
        }
        case AbeDoorStates::eUnused_1:
        {
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                field_110_state.door = AbeDoorStates::eWaitABit_2;
                field_118_timer = sGnFrame + 5;
            }
            ALIVE_FATAL("never expected AbeDoorStates::eUnused_1 to be called");
            return;
        }
        case AbeDoorStates::eWaitABit_2:
        {
            if (field_118_timer <= static_cast<s32>(sGnFrame))
            {
                field_110_state.door = AbeDoorStates::eClearTlvIds_3;
                field_118_timer = sGnFrame + 3;
            }
            return;
        }
        case AbeDoorStates::eClearTlvIds_3:
        {
            if (field_118_timer <= static_cast<s32>(sGnFrame))
            {
                field_110_state.door = AbeDoorStates::eSetNewActiveCamera_4;
                auto pTlv = static_cast<relive::Path_ResetPath*>(gMap.TLV_Get_At_446260(
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos),
                    ReliveTypes::eResetPath));
                BaseAliveGameObjectPathTLV = pTlv;
                if (pTlv)
                {
                    if (pTlv->mClearIds == relive::reliveChoice::eYes)
                    {
                        for (s16 i = pTlv->mFrom; i <= pTlv->mTo; i++)
                        {
                            if (i != pTlv->mExclude && i > 1)
                            {
                                SwitchStates_Set(i, 0);
                            }
                        }
                    }
                    if (pTlv->mClearObjects == relive::reliveChoice::eYes)
                    {
                        gMap.ResetPathObjects(pTlv->mPath);
                    }
                }
            }
            return;
        }
        case AbeDoorStates::eSetNewActiveCamera_4:
        {
            auto pDoorTlv = static_cast<relive::Path_Door*>(gMap.TLV_Get_At_446260(
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                FP_GetExponent(mXPos),
                FP_GetExponent(mYPos),
                ReliveTypes::eDoor));
            BaseAliveGameObjectPathTLV = pDoorTlv;
            gMap.field_1E_door = 1;
            const auto changeEffect = kPathChangeEffectToInternalScreenChangeEffect_4CDC78[pDoorTlv->mWipeEffect];
            s16 flag = 0;
            if (changeEffect == CameraSwapEffects::ePlay1FMV_5 || changeEffect == CameraSwapEffects::eUnknown_11)
            {
                flag = 1;
            }
            gMap.SetActiveCam(
                pDoorTlv->mNextLevel,
                pDoorTlv->mNextPath,
                pDoorTlv->mNextCamera,
                changeEffect,
                pDoorTlv->mMovieId,
                flag);
            field_110_state.door = AbeDoorStates::eSetNewAbePosition_5;
            field_196_door_id = pDoorTlv->mTargetDoorId;
            return;
        }
        case AbeDoorStates::eSetNewAbePosition_5:
        {
            mCurrentLevel = gMap.mCurrentLevel;
            mCurrentPath = gMap.mCurrentPath;
            gMap.field_1E_door = 0;
            auto pPathDoor = static_cast<relive::Path_Door*>(gMap.TLV_First_Of_Type_In_Camera(ReliveTypes::eDoor, 0));
            BaseAliveGameObjectPathTLV = pPathDoor;

            while (pPathDoor->mDoorId != field_196_door_id)
            {
                pPathDoor = static_cast<relive::Path_Door*>(Path_TLV::TLV_Next_Of_Type_446500(BaseAliveGameObjectPathTLV, ReliveTypes::eDoor));
                BaseAliveGameObjectPathTLV = pPathDoor;
                
                if (!BaseAliveGameObjectPathTLV)
                {
                    ALIVE_FATAL("Couldn't find target door. If this is a custom level, check if the level, path and camera is correct.");
                }
            }

            if (pPathDoor->mDoorType == relive::Path_Door::DoorTypes::eBasicDoor)
            {
                if (pPathDoor->mScale == relive::reliveScale::eHalf)
                {
                    mSpriteScale = FP_FromDouble(0.5);
                    mAnim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
                    mScale = Scale::Bg;
                }
                else
                {
                    mSpriteScale = FP_FromInteger(1);
                    mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                    mScale = Scale::Fg;
                }
            }
            else if (pPathDoor->mDoorType == relive::Path_Door::DoorTypes::eTrialDoor || pPathDoor->mDoorType == relive::Path_Door::DoorTypes::eHubDoor)
            {
                if (gMap.mCurrentLevel != EReliveLevelIds::eRuptureFarmsReturn)
                {
                    mSpriteScale = FP_FromDouble(0.5);
                    mScale = Scale::Bg;
                }
                else
                {
                    mSpriteScale = FP_FromInteger(1);
                    mScale = Scale::Fg;
                }
            }
            mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pPathDoor->mExitDirection == relive::reliveXDirection::eRight);
            mXPos = FP_FromInteger((BaseAliveGameObjectPathTLV->Width()) / 2)
                          + FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftX);
            MapFollowMe_401D30(TRUE);

            FP hitX = {};
            FP hitY = {};
            if (sCollisions->Raycast(
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mTopLeftY),
                    mXPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->mBottomRightY),
                    &BaseAliveGameObjectCollisionLine,
                    &hitX,
                    &hitY,
                    mSpriteScale != FP_FromDouble(0.5) ? kFgWallsOrFloor : kBgWallsOrFloor))
            {
                mYPos = hitY;
            }

            field_110_state.door = AbeDoorStates::eAbeComesOut_6;
            field_118_timer = sGnFrame + 30;
            return;
        }
        case AbeDoorStates::eAbeComesOut_6:
        {
            if (field_118_timer <= static_cast<s32>(sGnFrame))
            {
                mAnim.mFlags.Set(AnimFlags::eBit3_Render);
                field_110_state.door = AbeDoorStates::eAbeComesIn_0;
                mCurrentMotion = eAbeMotions::Motion_157_DoorExit_42D780;
            }
            return;
        }
        default:
            return;
    }
}

void Abe::Motion_157_DoorExit_42D780()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
            nullptr,
            mXPos,
            mYPos,
            mXPos,
            mYPos);

        VOnTlvCollision(BaseAliveGameObjectPathTLV);

        ToIdle_422D50();
    }
}

void Abe::Motion_158_ElumKnockback_42E070()
{
    // Empty
}

void Abe::Motion_159_Idle_RubEyes_423360()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_160_Idle_Stretch_Arms_4233A0()
{
    Motion_159_Idle_RubEyes_423360();
}

void Abe::Motion_161_Idle_Yawn_4233E0()
{
    Motion_159_Idle_RubEyes_423360();
}

void Abe::Motion_162_ToShrykull_42F410()
{
    if (field_110_state.raw == 0)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mAnim.mFlags.Clear(AnimFlags::eBit2_Animate);
            mAnim.mFlags.Clear(AnimFlags::eBit3_Render);

            field_110_state.raw = 1;

            relive_new Shrykull();
        }
    }
}

void Abe::Motion_163_ShrykullEnd_42F520()
{
    if (field_114_gnFrame)
    {
        field_114_gnFrame = field_114_gnFrame - 1;
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (!field_168_ring_pulse_timer)
        {
            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 0, 0));
            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 0, 0));
            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 0, 0));
        }

        mCurrentMotion = eAbeMotions::Motion_9_Speak_42FA50;
        Mudokon_SFX(MudSounds::eLaugh1_8, 0, 0, this);
    }
}

void Abe::Motion_164_PoisonGasDeath_42A120()
{
    switch (mAnim.mCurrentFrame)
    {
        case 0:
            SFX_Play_Pitch(SoundEffect::Choke_98, 127, 128, 0);
            break;
        case 9:
            SFX_Play_Pitch(SoundEffect::Choke_98, 127, 384, 0);
            break;
        case 28:
            SFX_Play_Pitch(SoundEffect::Choke_98, 127, 640, 0);
            break;
        case 32:
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, 0, this);
            break;
        case 50:
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 100, -200, this);
            break;
        case 53:
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 50, -200, this);
            break;
        default:
            break;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        const s32 v2 = field_114_gnFrame;
        field_114_gnFrame--;
        if (v2 == 0)
        {
            ToDieFinal_42C400();
        }
    }
}

} // namespace AO
