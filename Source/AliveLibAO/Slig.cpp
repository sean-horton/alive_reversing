#include "stdafx_ao.h"
#include "AmbientSound.hpp"
#include "Function.hpp"
#include "Slig.hpp"
#include "Lever.hpp"
#include "ResourceManager.hpp"
#include "stdlib.hpp"
#include "Shadow.hpp"
#include "Collisions.hpp"
#include "Math.hpp"
#include "Abe.hpp"
#include "Elum.hpp"
#include "Events.hpp"
#include "MusicController.hpp"
#include "Game.hpp"
#include "DDCheat.hpp"
#include "Input.hpp"
#include "Particle.hpp"
#include "Blood.hpp"
#include "Gibs.hpp"
#include "Sfx.hpp"
#include "CameraSwapper.hpp"
#include "PlatformBase.hpp"
#include "LiftPoint.hpp"
#include "Dove.hpp"
#include "Bullet.hpp"
#include "Particle.hpp"
#include "Midi.hpp"
#include "GameEnderController.hpp"
#include "SnoozeParticle.hpp"
#include "GameSpeak.hpp"
#include "ScreenShake.hpp"
#include "SwitchStates.hpp"
#include <algorithm>
#include "Psx_common.hpp"

// TODO: fix
#undef max
#undef min

namespace AO {

ALIVE_VAR(1, 0x9F11BC, s32, unused_9F11BC, 0);
ALIVE_VAR(1, 0x9F11C0, s32, unused_9F11C0, 0);

const TintEntry kSligTints_4CFB10[3] = {
    {EReliveLevelIds::eStockYards, 127u, 127u, 127u},
    {EReliveLevelIds::eStockYardsReturn, 127u, 127u, 127u},
    {EReliveLevelIds::eNone, 102u, 127u, 118u}};

using TSligStateFunction = decltype(&Slig::Motion_0_StandIdle_467640);

const TSligStateFunction sSligMotionTable_4CF960[] = {
    &Slig::Motion_0_StandIdle_467640,
    &Slig::Motion_1_StandToWalk_4695D0,
    &Slig::Motion_2_Walking_469130,
    &Slig::Motion_3_StandToRun_469C00,
    &Slig::Motion_4_Running_469690,
    &Slig::Motion_5_TurnAroundStanding_469C80,
    &Slig::Motion_6_Shoot_468820,
    &Slig::Motion_7_Falling_46A1A0,
    &Slig::Motion_8_Unknown_4673E0,
    &Slig::Motion_9_SlidingToStand_469DF0,
    &Slig::Motion_10_SlidingTurn_469F10,
    &Slig::Motion_11_SlidingTurnToWalk_46A120,
    &Slig::Motion_12_SlidingTurnToRun_46A160,
    &Slig::Motion_13_ReloadGun_4687B0,
    &Slig::Motion_14_ShootToStand_468810,
    &Slig::Motion_15_SteppingToStand_469080,
    &Slig::Motion_16_StandingToStep_468FD0,
    &Slig::Motion_17_DepossessingAbort_468750,
    &Slig::Motion_18_GameSpeak_467B10,
    &Slig::Motion_19_WalkToStand_469610,
    &Slig::Motion_20_Recoil_468D30,
    &Slig::Motion_21_SpeakHereBoy_467BD0,
    &Slig::Motion_22_SpeakHi_467C90,
    &Slig::Motion_23_SpeakFreeze_467D50,
    &Slig::Motion_24_SpeakGetHim_467E10,
    &Slig::Motion_25_SpeakLaugh_467ED0,
    &Slig::Motion_26_SpeakBullshit1_467F90,
    &Slig::Motion_27_SpeakLookOut_468050,
    &Slig::Motion_28_SpeakBullshit2_468110,
    &Slig::Motion_29_SpeakPanic_4681D0,
    &Slig::Motion_30_SpeakWhat_468290,
    &Slig::Motion_31_SpeakAIFreeze_468350,
    &Slig::Motion_32_Blurgh_468410,
    &Slig::Motion_33_Sleeping_46A410,
    &Slig::Motion_34_SleepingToStand_46A5F0,
    &Slig::Motion_35_Knockback_46A720,
    &Slig::Motion_36_KnockbackToStand_46A7F0,
    &Slig::Motion_37_Depossessing_4684D0,
    &Slig::Motion_38_Possess_46B050,
    &Slig::Motion_39_OutToFall_46A9E0,
    &Slig::Motion_40_FallingInitiate_46AA60,
    &Slig::Motion_41_LandingSoft_46A390,
    &Slig::Motion_42_LandingFatal_46AFE0,
    &Slig::Motion_43_ShootZ_468E30,
    &Slig::Motion_44_ShootZtoStand_468F70,
    &Slig::Motion_45_Smash_46A990,
    &Slig::Motion_46_ToIdle_46A590,
    &Slig::Motion_47_LiftUp_4665A0,
    &Slig::Motion_48_LiftDown_4665C0,
    &Slig::Motion_49_LiftGrip_4663A0,
    &Slig::Motion_50_LiftUngrip_466460,
    &Slig::Motion_51_LiftGripping_466480,
    &Slig::Motion_52_Beat_46AA90,
};

const AnimId sSligFrameTables_4CFA38[] = {
    AnimId::Slig_Idle,
    AnimId::Slig_StandToWalk,
    AnimId::Slig_Walking,
    AnimId::Slig_StandToRun,
    AnimId::Slig_Running,
    AnimId::Slig_TurnAroundStanding,
    AnimId::Slig_Shoot,
    AnimId::Slig_Idle,
    AnimId::Slig_Idle,
    AnimId::Slig_SlidingToStand,
    AnimId::Slig_SlidingTurn,
    AnimId::Slig_SlidingTurnToWalk,
    AnimId::Slig_SlidingTurnToRun,
    AnimId::Slig_ReloadGun,
    AnimId::Slig_ShootToStand,
    AnimId::Slig_SteppingToStand,
    AnimId::Slig_StandingToStep,
    AnimId::Slig_Idle,
    AnimId::Slig_Gamespeak,
    AnimId::Slig_WalkToStand,
    AnimId::Slig_Recoil,
    AnimId::Slig_Speak1,
    AnimId::Slig_Speak2,
    AnimId::Slig_Speak3,
    AnimId::Slig_Speak4,
    AnimId::Slig_Speak1,
    AnimId::Slig_Speak2,
    AnimId::Slig_Speak3,
    AnimId::Slig_Speak4,
    AnimId::Slig_Speak1,
    AnimId::Slig_Speak2,
    AnimId::Slig_Speak3,
    AnimId::Slig_Speak4,
    AnimId::Slig_Sleeping,
    AnimId::Slig_SleepingToStand,
    AnimId::Slig_Knockback,
    AnimId::Slig_KnockbackToStand,
    AnimId::Slig_PossessShake,
    AnimId::Slig_PossessShake,
    AnimId::Slig_OutToFall,
    AnimId::Slig_FallingInitiate,
    AnimId::Slig_LandingSoft,
    AnimId::Slig_LandingFatal,
    AnimId::Slig_ShootZ,
    AnimId::Slig_ShootZtoStand,
    AnimId::Slig_Smash,
    AnimId::Slig_Beat,
    AnimId::Slig_LiftUp,
    AnimId::Slig_LiftDown,
    AnimId::Slig_LiftGrip,
    AnimId::Slig_LiftUngrip,
    AnimId::Slig_LiftGripping,
    AnimId::Slig_Beat,
    AnimId::None};

static Slig::TBrainFn sSligBrainTable[]{
    &Slig::Brain_SpottedEnemy_465EB0,
    &Slig::Brain_Paused_466030,
    &Slig::Brain_EnemyDead_466190,
    &Slig::Brain_KilledEnemy_4662A0,
    &Slig::Brain_Unknown_46B250,
    &Slig::Brain_Sleeping_46B4E0,
    &Slig::Brain_WakingUp_46B700,
    &Slig::Brain_Inactive_46B780,
    &Slig::Brain_Possessed_46C190,
    &Slig::Brain_Death_46C3A0,
    &Slig::Brain_DeathDropDeath_46C5A0,
    &Slig::Brain_ReturnControlToAbeAndDie_46C760,
    &Slig::Brain_PanicTurning_46C7C0,
    &Slig::Brain_PanicRunning_46CA20,
    &Slig::Brain_PanicYelling_46CC50,
    &Slig::Brain_Chasing_46CD60,
    &Slig::Brain_StopChasing_46CF20,
    &Slig::Brain_StartChasing_46CF90,
    &Slig::Brain_Idle_46D6E0,
    &Slig::Brain_Turning_46DC70,
    &Slig::Brain_Walking_46DE90,
    &Slig::Brain_GetAlertedTurn_46E520,
    &Slig::Brain_GetAlerted_46E800,
    &Slig::Brain_StoppingNextToMudokon_46EBB0,
    &Slig::Brain_BeatingUp_46EC40,
    &Slig::Brain_Discussion_46ECE0,
    &Slig::Brain_ChaseAndDisappear_46EEE0,
    &Slig::Brain_Shooting_46EFD0,
    &Slig::Brain_ZSpottedEnemy_46F260,
    &Slig::Brain_ZShooting_46F290,
};

SfxDefinition sSligSounds_4CFB30[] = {
    {0, 1, 58, 40, -256, -256, 0},
    {0, 1, 58, 50, 0, 0, 0},
    {0, 1, 59, 60, 0, 0, 0},
    {0, 1, 59, 60, 127, 127, 0},
    {0, 1, 60, 60, 0, 0, 0},
    {0, 1, 61, 60, 0, 0, 0}};

SfxDefinition sSligSounds2[] = {
    {0, 62, 60, 127, 0, 0, 0},
    {0, 62, 62, 127, 0, 0, 0},
    {0, 62, 61, 127, 0, 0, 0},
    {0, 62, 63, 127, 0, 0, 0},
    {0, 63, 60, 127, 0, 0, 0},
    {0, 63, 37, 127, 0, 0, 0},
    {0, 63, 61, 127, 0, 0, 0},
    {0, 63, 38, 127, 0, 0, 0},
    {0, 64, 61, 127, 0, 0, 0},
    {0, 64, 62, 127, 0, 0, 0},
    {0, 64, 63, 127, 0, 0, 0},
    {0, 64, 39, 127, 0, 0, 0},
    {0, 64, 36, 127, 0, 0, 0}};

void Slig::Slig_SoundEffect_46F310(SligSfx sfxIdx)
{
    PSX_RECT worldRect;
    s32 volRight = 0;
    s32 volLeft = 0;

    auto dir = gMap.GetDirection_444A40(
        mBaseAnimatedWithPhysicsGameObject_LvlNumber,
        mBaseAnimatedWithPhysicsGameObject_PathNumber,
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos);

    auto sfxIdxInt = static_cast<s32>(sfxIdx);
    if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromInteger(1))
    {
        volRight = sSligSounds_4CFB30[sfxIdxInt].field_C_default_volume;
    }
    else
    {
        volRight = sSligSounds_4CFB30[sfxIdxInt].field_C_default_volume / 2;
    }
    gMap.Get_Camera_World_Rect(dir, &worldRect);
    switch (dir)
    {
        case CameraPos::eCamCurrent_0:
        {
            volLeft = volRight;
            break;
        }
        case CameraPos::eCamTop_1:
        case CameraPos::eCamBottom_2:
        {
            volLeft = sSligSounds_4CFB30[sfxIdxInt].field_C_default_volume * 2 / 3;
            volRight = volLeft;
            break;
        }
        case CameraPos::eCamLeft_3:
        {
            FP percentHowFar = (FP_FromInteger(worldRect.w) - mBaseAnimatedWithPhysicsGameObject_XPos) / FP_FromInteger(640);
            volLeft = volRight - FP_GetExponent(percentHowFar * FP_FromInteger(volRight - (volRight / 3)));
            volRight -= FP_GetExponent(percentHowFar * FP_FromInteger(volRight));
            break;
        }
        case CameraPos::eCamRight_4:
        {
            FP percentHowFar = (mBaseAnimatedWithPhysicsGameObject_XPos - FP_FromInteger(worldRect.x)) / FP_FromInteger(640);
            volLeft = volRight - FP_GetExponent(percentHowFar * FP_FromInteger(volRight));
            volRight -= FP_GetExponent(percentHowFar * FP_FromInteger(volRight - (volRight / 3)));
            break;
        }
        default:
            return;
    }
    if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
    {
        volLeft = volLeft * 2 / 3;
        volRight = volRight * 2 / 3;
    }
    auto pitch = Math_RandomRange_450F20(
        sSligSounds_4CFB30[sfxIdxInt].field_E_pitch_min,
        sSligSounds_4CFB30[sfxIdxInt].field_E_pitch_min);
    SFX_SfxDefinition_Play_477330(&sSligSounds_4CFB30[sfxIdxInt], static_cast<s16>(volLeft), static_cast<s16>(volRight), pitch, pitch);
}

Slig::Slig(Path_Slig* pTlv, s32 tlvInfo)
    : BaseAliveGameObject()
{
    field_15C_last_event_index = -1;
    field_172_unused = -1;
    field_170_unused = 0;

    field_210_resources = {};

    u8** ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgbasicAOResID, 1, 0);
    field_210_resources.res[0] = ppRes;
    const AnimRecord& rec = AO::AnimRec(AnimId::Slig_Idle);
    Animation_Init_417FD0(rec.mFrameTableOffset, rec.mMaxW, rec.mMaxH, ppRes, 1);

    mBaseAliveGameObjectFlags.Clear(Flags_10A::e10A_Bit2_bPossesed);
    mBaseAliveGameObjectFlags.Set(Flags_10A::e10A_Bit1_Can_Be_Possessed);
    mBaseAliveGameObjectFlags.Set(Flags_10A::e10A_Bit4_SetOffExplosives);

    mBaseGameObjectTypeId = ReliveTypes::eSlig;

    field_114_timer = 0;
    field_118_unused = 0;
    field_11C_current_camera = -1;
    field_10C_unused = 0;
    field_10E_brain_sub_state = 0;
    mNextMotion = 0;
    field_EC = 3;
    field_158_explode_timer = 0;
    field_154_death_by_being_shot_timer = 0;
    mLiftPoint = nullptr;
    mCurrentMotion = eSligMotions::Motion_7_Falling_46A1A0;
    field_11E_return_to_previous_motion = 0;
    field_144_unused = 0;
    field_12C_falling_velx_scale_factor = FP_FromInteger(0);

    field_110_pitch_min = 45 * ((Math_NextRandom() % 5) - 2);

    BaseAliveGameObjectPathTLV = pTlv;
    field_174_tlv = *pTlv;
    mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(pTlv->field_10_top_left.field_0_x);
    mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pTlv->field_10_top_left.field_2_y);
    field_134_tlvInfo = tlvInfo;
    field_254_prevent_depossession &= ~7u;
    field_126_input = 0;
    field_130_game_ender_pause_time = 100;
    unused_9F11BC = 0;
    unused_9F11C0 = 0;
    field_200_num_times_to_shoot = 0;
    field_204_unused = 0;
    field_208_unused = 0;
    field_20C_force_alive_state = 0;
    field_13A_shot_motion = -1;
    field_138_res_idx = 0;

    mBaseAnimatedWithPhysicsGameObject_Anim.field_1C_fn_ptr_array = kSlig_Anim_Frame_Fns_4CEBF0;

    if (pTlv->field_18_scale == Scale_short::eFull_0)
    {
        mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromInteger(1);
        mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_SligBat_33;
        mBaseAnimatedWithPhysicsGameObject_Scale = Scale::Fg;
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromDouble(0.5);
        mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_SligBat_Half_14;
        mBaseAnimatedWithPhysicsGameObject_Scale = Scale::Bg;
    }

    SetBaseAnimPaletteTint(
        &kSligTints_4CFB10[0],
        gMap.mCurrentLevel,
        412);

    FP hitX = {};
    FP hitY = {};
    if (sCollisions->RayCast(
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(24),
            &BaseAliveGameObjectCollisionLine,
            &hitX,
            &hitY,
            mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 1 : 0x10)
        == 1)
    {
        mCurrentMotion = 0;
        mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
    }

    MapFollowMe_401D30(TRUE);

    Init();

    VStackOnObjectsOfType(ReliveTypes::eSlig);

    mBaseAliveGameObjectFlags.Set(Flags_10A::e10A_Bit6);

    field_146_unused = 0;
    field_14A_unused = 0;
    field_148_unused = 0;
    field_122_unused = 0;

    mShadow = relive_new Shadow();
}

Slig::~Slig()
{
    if (sControlledCharacter_50767C == this)
    {
        sControlledCharacter_50767C = sActiveHero_507678;
        MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);

        if (gMap.mLevel != EReliveLevelIds::eMenu && gMap.mLevel != EReliveLevelIds::eNone)
            gMap.SetActiveCam(
                field_14E_level,
                field_150_path,
                field_152_camera,
                CameraSwapEffects::eInstantChange_0,
                0,
                0);
    }

    auto pTlv = gMap.TLV_Get_At_446260(
        field_174_tlv.field_10_top_left.field_0_x,
        field_174_tlv.field_10_top_left.field_2_y,
        field_174_tlv.field_10_top_left.field_0_x,
        field_174_tlv.field_10_top_left.field_2_y,
        field_174_tlv.field_4_type.mType);

    if (mHealth <= FP_FromInteger(0))
    {
        if (pTlv)
        {
            pTlv->field_0_flags.Clear(TLV_Flags::eBit1_Created);
            pTlv->field_0_flags.Set(TLV_Flags::eBit2_Destroyed);
        }
    }
    else if (pTlv)
    {
        pTlv->field_0_flags.Clear(TLV_Flags::eBit1_Created);
        pTlv->field_0_flags.Clear(TLV_Flags::eBit2_Destroyed);
    }

    for (u8**& ppRes : field_210_resources.res)
    {
        if (ppRes && mBaseAnimatedWithPhysicsGameObject_Anim.field_20_ppBlock != ppRes)
        {
            ResourceManager::FreeResource_455550(ppRes);
            ppRes = nullptr;
        }
    }
    
    MusicController::ClearObject(this);
}

void Slig::VScreenChanged()
{
    if (gMap.mCurrentLevel != gMap.mLevel
        || gMap.mOverlayId != gMap.GetOverlayId()
        || (gMap.mCurrentPath != gMap.mPath && this != sControlledCharacter_50767C))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

void Slig::Init()
{
    field_210_resources.res[10] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kBigflashAOResID, 1, 0);
    field_210_resources.res[11] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSligBlowAOResID, 1, 0);
    field_210_resources.res[12] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kShellAOResID, 1, 0);
    field_210_resources.res[2] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgknbkAOResID, 1, 0);
    field_210_resources.res[16] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSquibSmokeAOResID, 1, 0);

    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit8_SligKnfd))
    {
        field_210_resources.res[6] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgknfdAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit9_SligEdge))
    {
        field_210_resources.res[3] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgedgeAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit1_SligLever))
    {
        field_210_resources.res[7] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgleverAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit2_SligLift))
    {
        field_210_resources.res[8] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgliftAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit10_SligSmash))
    {
        field_210_resources.res[4] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgsmashAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit11_SligBeat))
    {
        field_210_resources.res[9] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgbeatAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit3_SligZ))
    {
        field_210_resources.res[5] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgzshotAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit7_SligSleep))
    {
        field_210_resources.res[1] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSlgsleepAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit4))
    {
        field_210_resources.res[13] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kZflashAOResID, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit6))
    {
        field_210_resources.res[14] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kUnknownAOResID_333, 1, 0);
    }
    if (!field_174_tlv.field_50_disable_resources.Get(SligFlags_DisabledRes::eDisabledRes_Bit5))
    {
        field_210_resources.res[15] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknokzAOResID, 1, 0);
    }
    field_11C_current_camera = gMap.mCurrentCamera;
    field_20E_spotted_possessed_slig = 0;
    field_114_timer = sGnFrame + field_174_tlv.field_1C_pause_time;

    switch (field_174_tlv.field_1A_start_state)
    {
        case Path_Slig::StartState::Patrol_1:
        {
            SetBrain(&Slig::Brain_Inactive_46B780);
            SetBrain2(&Slig::Brain_Inactive_46B780);
            break;
        }
        case Path_Slig::StartState::Sleeping_2:
        {
            if (field_174_tlv.field_1_unknown && field_174_tlv.field_4E_stay_awake == Choice_short::eYes_1)
            {
                SetBrain(&Slig::Brain_Inactive_46B780);
                SetBrain2(&Slig::Brain_Inactive_46B780);
            }
            else
            {
                SetBrain(&Slig::Brain_Sleeping_46B4E0);
                SetBrain2(&Slig::Brain_Sleeping_46B4E0);
                mCurrentMotion = eAbeMotions::Motion_33_RunJumpMid_426FA0;
                VUpdateAnimData();
            }
            break;
        }
        case Path_Slig::StartState::Chase_3:
        {
            SetBrain(&Slig::Brain_StartChasing_46CF90);
            SetBrain2(&Slig::Brain_StartChasing_46CF90);
            field_114_timer = sGnFrame + field_174_tlv.field_3E_time_to_wait_before_chase;
            break;
        }
        case Path_Slig::StartState::ChaseAndDisappear_4:
        {
            field_114_timer = sGnFrame + field_174_tlv.field_1C_pause_time;
            SetBrain(&Slig::Brain_ChaseAndDisappear_46EEE0);
            SetBrain2(&Slig::Brain_ChaseAndDisappear_46EEE0);
            field_130_game_ender_pause_time = field_174_tlv.field_1C_pause_time;
            break;
        }
        case Path_Slig::StartState::FallingToChase_5:
        {
            SetBrain(&Slig::Brain_Paused_466030);
            SetBrain2(&Slig::Brain_Paused_466030);
            break;
        }
        default:
        {
            SetBrain(&Slig::Brain_Unknown_46B250);
            SetBrain2(&Slig::Brain_Unknown_46B250);
            break;
        }
    }

    if (field_174_tlv.field_34_start_direction == XDirection_short::eLeft_0)
    {
        mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX);
    }
    field_1F4_points_count = 0;

    field_1CC_points[field_1F4_points_count].field_0_x = FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos);
    field_1CC_points[field_1F4_points_count].field_2_y = FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos);
    field_1F4_points_count++;

    field_13C_zone_rect = {};
    bool zoneRectSet = false;

    for (s16 yCam = -2; yCam < 3; yCam++)
    {
        for (s16 xCam = -2; xCam < 3; xCam++)
        {
            auto pTlvIter = gMap.Get_First_TLV_For_Offsetted_Camera(xCam, yCam);
            while (pTlvIter)
            {
                bool addPoint = false;
                if (pTlvIter->field_4_type == TlvTypes::eSligBoundLeft_57)
                {
                    if (static_cast<Path_SligLeftBound*>(pTlvIter)->field_18_slig_id == field_174_tlv.field_40_slig_bound_id)
                    {
                        field_13C_zone_rect.x = pTlvIter->field_10_top_left.field_0_x;
                        addPoint = true;
                        zoneRectSet = true;
                    }
                }
                else if (pTlvIter->field_4_type == TlvTypes::eSligBoundRight_76)
                {
                    if (static_cast<Path_SligRightBound*>(pTlvIter)->field_18_slig_id == field_174_tlv.field_40_slig_bound_id)
                    {
                        field_13C_zone_rect.w = pTlvIter->field_10_top_left.field_0_x;
                        addPoint = true;
                        zoneRectSet = true;
                    }
                }
                else if (pTlvIter->field_4_type == TlvTypes::eSligPersist_77)
                {
                    if (static_cast<Path_SligPersist*>(pTlvIter)->field_18_slig_id == field_174_tlv.field_40_slig_bound_id)
                    {
                        addPoint = true;
                    }
                }

                if (addPoint)
                {
                    if (field_1F4_points_count < ALIVE_COUNTOF(field_1CC_points))
                    {
                        field_1CC_points[field_1F4_points_count].field_0_x = pTlvIter->field_10_top_left.field_0_x;
                        field_1CC_points[field_1F4_points_count].field_2_y = pTlvIter->field_10_top_left.field_2_y;
                        field_1F4_points_count++;
                    }
                }

                pTlvIter = Path_TLV::Next_446460(pTlvIter);
            }
        }
    }

    // HACK FIX: Some slig spawners don't set a slig id that matches any left/right bound.
    // In the OG this leaves the left/right zone bounds set as random values, here we fix
    // to some of these seen random values that gives the slig some what predictable patrol zones.
    if (!zoneRectSet)
    {
        LOG_INFO("Hack fix the slig walking zone (if you see this in a custom map please give your spwaned slig a left/right bound that matches the spawn id!)");
        field_13C_zone_rect.x = 12809;
        field_13C_zone_rect.w = 6405;
    }
}

const u32 sSligVelXTable_4BCA30[] = {262144, 262144, 0, 4294705152, 4294705152, 4294705152, 0, 262144};
const u32 sSligVelYTable_4BCA50[] = {0, 4294705152, 4294705152, 4294705152, 0, 262144, 262144, 262144};


void Slig::VUpdate()
{
    if (!Input_IsChanting())
    {
        field_254_prevent_depossession &= ~4u;
    }

    if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::ePossessed_6, this, 1, 0);
    }

    if (sDDCheat_FlyingEnabled_50771C && sControlledCharacter_50767C == this)
    {
        BaseAliveGameObjectCollisionLine = nullptr;
        if (Input().IsAnyPressed(0xF000))
        {
            const s32 dir = Input().Dir();
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromRaw(sSligVelXTable_4BCA30[dir]);
            mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromRaw(sSligVelYTable_4BCA50[dir]);

            if (Input().IsAnyPressed(0x20))
            {
                const FP velX = FP_FromRaw(sSligVelXTable_4BCA30[dir]);
                const FP velY = FP_FromRaw(sSligVelYTable_4BCA50[dir]);
                mBaseAnimatedWithPhysicsGameObject_VelX += velX;
                mBaseAnimatedWithPhysicsGameObject_VelX += velX;
                mBaseAnimatedWithPhysicsGameObject_VelY += velY;
            }

            mBaseAnimatedWithPhysicsGameObject_XPos += mBaseAnimatedWithPhysicsGameObject_VelX;
            mBaseAnimatedWithPhysicsGameObject_YPos += mBaseAnimatedWithPhysicsGameObject_VelY;

            PSX_Point mapSize = {};
            gMap.Get_map_size(&mapSize);

            if (mBaseAnimatedWithPhysicsGameObject_XPos < FP_FromInteger(0))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(0);
            }

            if (mBaseAnimatedWithPhysicsGameObject_XPos >= FP_FromInteger(mapSize.field_0_x))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(mapSize.field_0_x) - FP_FromInteger(1);
            }

            if (mBaseAnimatedWithPhysicsGameObject_YPos < FP_FromInteger(0))
            {
                mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(0);
            }

            if (mBaseAnimatedWithPhysicsGameObject_YPos >= FP_FromInteger(mapSize.field_2_y))
            {
                mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(mapSize.field_2_y) - FP_FromInteger(1);
            }
        }
        else
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
            mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
        }

        SetActiveCameraDelayedFromDir_401C90();

        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
    }
    else
    {
        const auto old_motion = mCurrentMotion;

        const auto oldBrain = field_1F8_fn;

        field_10E_brain_sub_state = (this->*field_1F8_fn)();

        if (field_1F8_fn != oldBrain)
        {
            //LOG_INFO("Brain changed from " << GetOriginalFn(oldBrain, sSligBrainTable).fnName << " to " << GetOriginalFn(field_1F8_fn, sSligBrainTable).fnName);
        }

        if (field_106_shot)
        {
            Vshot();
        }

        if (showDebugCreatureInfo_5076E0)
        {
            DDCheat::DebugStr(
                "Slig %d %d %d %d\n",
                field_10E_brain_sub_state,
                field_114_timer,
                mCurrentMotion,
                mNextMotion);
        }

        const FP new_x = mBaseAnimatedWithPhysicsGameObject_XPos;
        const FP new_y = mBaseAnimatedWithPhysicsGameObject_YPos;

        (this->*sSligMotionTable_4CF960[mCurrentMotion])();

        if (new_x != mBaseAnimatedWithPhysicsGameObject_XPos || new_y != mBaseAnimatedWithPhysicsGameObject_YPos)
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                nullptr,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos);

            VOn_TLV_Collision(BaseAliveGameObjectPathTLV);
        }

        if (old_motion != mCurrentMotion || field_108_bMotionChanged)
        {
            field_108_bMotionChanged = FALSE;
            VUpdateAnimData();

            if (VIs8_465630(old_motion))
            {
                mBaseAnimatedWithPhysicsGameObject_Anim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
            }
        }
        else if (field_11E_return_to_previous_motion)
        {
            mCurrentMotion = mPreviousMotion;

            VUpdateAnimData();

            mBaseAnimatedWithPhysicsGameObject_Anim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
            field_11E_return_to_previous_motion = 0;
        }
    }
}

void Slig::VRender(PrimHeader** ppOt)
{
    if (mBaseGameObjectUpdateDelay == 0)
    {
        BaseAnimatedWithPhysicsGameObject::VRender(ppOt);
    }
}

void Slig::VOnTrapDoorOpen()
{
    if (mLiftPoint)
    {
        mLiftPoint->VRemove(this);
        mLiftPoint->mBaseGameObjectRefCount--;
        mLiftPoint = nullptr;
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        VSetMotion(eSligMotions::Motion_39_OutToFall_46A9E0);
    }
}

void Slig::VUnPosses()
{
    mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    field_11C_current_camera = gMap.mCurrentCamera;
    field_114_timer = sGnFrame + 180;
    MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
}

enum Brain_Possessed
{
    eStartPossession_0 = 0,
    ePossessionShaking_1 = 1,
    ePossessionInactive_2 = 2,
    ePossessionSpeak_3 = 3,
    eControlledByPlayer_4 = 4
};

void Slig::VPossessed()
{
    mBaseAliveGameObjectFlags.Set(Flags_10A::e10A_Bit2_bPossesed);
    field_254_prevent_depossession |= 4u;
    if (mNextMotion != eSligMotions::Motion_36_KnockbackToStand_46A7F0 && mNextMotion != eSligMotions::Motion_35_Knockback_46A720)
    {
        mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    }

    SetBrain(&Slig::Brain_Possessed_46C190);
    field_10E_brain_sub_state = Brain_Possessed::eStartPossession_0;

    field_14E_level = gMap.mCurrentLevel;
    field_150_path = gMap.mCurrentPath;
    field_152_camera = gMap.mCurrentCamera;

    MusicController::static_PlayMusic(MusicController::MusicTypes::ePossessed_6, this, 1, 0);
}

s16 Slig::VTakeDamage(BaseGameObject* pFrom)
{
    switch (pFrom->mBaseGameObjectTypeId)
    {
        case ReliveTypes::eBullet:
        {
            auto pBullet = static_cast<Bullet*>(pFrom);
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
            {
                {
                    const FP yOff = FP_FromInteger(Math_NextRandom() % 16) - FP_FromInteger(8);
                    const FP xOff = (pBullet->field_20_x_distance <= FP_FromInteger(0) ? FP_FromInteger(-1) : FP_FromInteger(1) * FP_FromInteger(Math_NextRandom() & 15) + FP_FromInteger(16));
                    const FP xPos = (mBaseAnimatedWithPhysicsGameObject_SpriteScale * pBullet->field_20_x_distance <= FP_FromInteger(0) ? FP_FromInteger(-6) : FP_FromInteger(6));

                    relive_new Blood(
                        xPos + mBaseAnimatedWithPhysicsGameObject_XPos,
                        pBullet->field_1C_ypos,
                        xOff,
                        yOff,
                        mBaseAnimatedWithPhysicsGameObject_SpriteScale,
                        12);
                }

                {
                    const FP xPos = (mBaseAnimatedWithPhysicsGameObject_SpriteScale * pBullet->field_20_x_distance <= FP_FromInteger(0) ? FP_FromInteger(-12) : FP_FromInteger(12));
                    const FP xOff = pBullet->field_20_x_distance <= FP_FromInteger(0) ? FP_FromInteger(-6) : FP_FromInteger(6);

                    relive_new Blood(
                        xOff + mBaseAnimatedWithPhysicsGameObject_XPos,
                        pBullet->field_1C_ypos,
                        xPos,
                        FP_FromInteger(0),
                        mBaseAnimatedWithPhysicsGameObject_SpriteScale,
                        8);
                }
            }

            field_106_shot = TRUE;
            SetBrain(&Slig::Brain_Death_46C3A0);
            field_154_death_by_being_shot_timer = sGnFrame + 5;

            if (mCurrentMotion != eSligMotions::Motion_38_Possess_46B050 && mCurrentMotion != eSligMotions::Motion_45_Smash_46A990 && mCurrentMotion != eSligMotions::Motion_35_Knockback_46A720)
            {
                field_158_explode_timer = sGnFrame + 20;
                mNextMotion = eSligMotions::Motion_38_Possess_46B050;
                field_13A_shot_motion = eSligMotions::Motion_38_Possess_46B050;
                Vshot();
                field_108_bMotionChanged = TRUE;
                if (pBullet->field_20_x_distance >= FP_FromInteger(0))
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromDouble(0.001);
                }
                else
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromDouble(-0.001);
                }
            }

            if (mHealth <= FP_FromInteger(0))
            {
                return mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit3_Render) ? 1 : 0;
            }

            if (mCurrentMotion != eSligMotions::Motion_45_Smash_46A990 && mCurrentMotion != eSligMotions::Motion_35_Knockback_46A720)
            {
                mNextMotion = eSligMotions::Motion_38_Possess_46B050;
                field_13A_shot_motion = eSligMotions::Motion_38_Possess_46B050;
            }
            mHealth = FP_FromInteger(0);
            Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
            return 1;
        }

        case ReliveTypes::eElectricWall:
            Slig_GameSpeak_SFX_46F560(SligSpeak::eHelp_10, 0, field_110_pitch_min, this);
            return 1;

        case ReliveTypes::eBaseBomb:
        case ReliveTypes::eMeatSaw:
        case ReliveTypes::eExplosion:
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
            {
                relive_new Gibs(
                    GibType::Slig_1,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    mBaseAnimatedWithPhysicsGameObject_VelX,
                    mBaseAnimatedWithPhysicsGameObject_VelY,
                    mBaseAnimatedWithPhysicsGameObject_SpriteScale);

                mHealth = FP_FromInteger(0);
                SFX_Play_Mono(SoundEffect::FallingItemHit_53, 90);
                mBaseGameObjectUpdateDelay = 40;
                mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
                mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit2_Animate);
                SetBrain(&Slig::Brain_ReturnControlToAbeAndDie_46C760);
                mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
                VUpdateAnimData();
                Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
            }
            return 1;

        case ReliveTypes::eAbilityRing:
            return 1;

        case ReliveTypes::eSlog:
            if (mHealth <= FP_FromInteger(0)
                && (mCurrentMotion == eSligMotions::Motion_35_Knockback_46A720 || mCurrentMotion == eSligMotions::Motion_45_Smash_46A990))
            {
                return 1;
            }
            mHealth = FP_FromInteger(0);
            SetBrain(&Slig::Brain_Death_46C3A0);
            field_106_shot = 1;
            Environment_SFX_42A220(EnvironmentSfx::eKnockback_13, 0, 0x7FFF, this);
            if (VIsFacingMe(static_cast<BaseAnimatedWithPhysicsGameObject*>(pFrom)))
            {
                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                }
                else
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                }
                field_108_bMotionChanged = TRUE;
                field_128_timer = sGnFrame + 10;
                mCurrentMotion = eSligMotions::Motion_35_Knockback_46A720;
                mNextMotion = eSligMotions::Motion_35_Knockback_46A720;
                field_13A_shot_motion = eSligMotions::Motion_35_Knockback_46A720;
            }
            else
            {
                mNextMotion = eSligMotions::Motion_45_Smash_46A990;
                field_13A_shot_motion = eSligMotions::Motion_45_Smash_46A990;
            }
            return 1;

        case ReliveTypes::eBeeSwarm:
            if (mHealth > FP_FromInteger(0))
            {
                mHealth -= FP_FromDouble(0.34);
                Slig_GameSpeak_SFX_46F560(SligSpeak::eHelp_10, 0, field_110_pitch_min, this);
                if (mHealth <= FP_FromInteger(0))
                {
                    mHealth = FP_FromInteger(0);
                    field_106_shot = 1;
                    mNextMotion = eSligMotions::Motion_35_Knockback_46A720;
                    field_13A_shot_motion = eSligMotions::Motion_35_Knockback_46A720;
                }
            }
            return 1;

        case ReliveTypes::eElectrocute:
            if (mHealth > FP_FromInteger(0))
            {
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                mHealth = FP_FromInteger(0);
                Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
            }
            return 1;

        case ReliveTypes::eBat:
            break;

        default:
            if (mHealth > FP_FromInteger(0))
            {
                SFX_Play_Mono(SoundEffect::KillEffect_78, 127);
                SFX_Play_Mono(SoundEffect::FallingItemHit_53, 90);
            }
            break;
    }

    if (mHealth > FP_FromInteger(0))
    {
        mHealth = FP_FromInteger(0);
        mNextMotion = eSligMotions::Motion_45_Smash_46A990;
        field_13A_shot_motion = eSligMotions::Motion_45_Smash_46A990;
        field_106_shot = 1;
    }
    return 1;
}

enum Brain_DeathDropDeath
{
    eSayHelpOnce_0 = 0,
    eSayHelpAndDie_1 = 1,
    eSwitchCamToAbe_2 = 2
};

void Slig::VOn_TLV_Collision(Path_TLV* pTlv)
{
    while (pTlv)
    {
        if (pTlv->field_4_type == TlvTypes::DeathDrop_5)
        {
            if (mHealth > FP_FromInteger(0))
            {
                mHealth = FP_FromInteger(0);
                field_10E_brain_sub_state = Brain_DeathDropDeath::eSayHelpOnce_0;
                SetBrain(&Slig::Brain_DeathDropDeath_46C5A0);
                mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
                mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
                VSetMotion(eSligMotions::Motion_7_Falling_46A1A0);
                Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
            }
        }

        pTlv = gMap.TLV_Get_At_446060(
            pTlv,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos);
    }
}

s16 Slig::VOnSameYLevel(BaseAnimatedWithPhysicsGameObject* pOther)
{
    PSX_RECT ourRect = VGetBoundingRect();
    PSX_RECT objRect = pOther->VGetBoundingRect();
    return ((objRect.y + objRect.h) / 2) <= ourRect.h && objRect.h >= ourRect.y;
}

s16 Slig::VIsFacingMe(BaseAnimatedWithPhysicsGameObject* pWho)
{
    if (mCurrentMotion != eSligMotions::Motion_5_TurnAroundStanding_469C80
        || mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame < 6)
    {
        if (pWho->mBaseAnimatedWithPhysicsGameObject_XPos <= mBaseAnimatedWithPhysicsGameObject_XPos && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }

        if (pWho->mBaseAnimatedWithPhysicsGameObject_XPos >= mBaseAnimatedWithPhysicsGameObject_XPos && !mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }
    }
    else
    {
        if (pWho->mBaseAnimatedWithPhysicsGameObject_XPos <= mBaseAnimatedWithPhysicsGameObject_XPos && !mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }

        if (pWho->mBaseAnimatedWithPhysicsGameObject_XPos >= mBaseAnimatedWithPhysicsGameObject_XPos && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            return 1;
        }
    }
    return 0;
}

void Slig::VUpdateAnimData()
{
    u8** ppRes = ResBlockForMotion_4654D0(mCurrentMotion);
    if (!ppRes)
    {
        mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
        ppRes = ResBlockForMotion_4654D0(mCurrentMotion);
    }
    const AnimRecord& rec = AO::AnimRec(sSligFrameTables_4CFA38[mCurrentMotion]);
    mBaseAnimatedWithPhysicsGameObject_Anim.Set_Animation_Data(rec.mFrameTableOffset, ppRes);
}

void Slig::Vshot()
{
    if (field_13A_shot_motion != -1)
    {
        mCurrentMotion = field_13A_shot_motion;
    }

    mNextMotion = -1;
    field_13A_shot_motion = -1;
    field_106_shot = FALSE;
    field_114_timer = sGnFrame + 60;
    SetBrain(&Slig::Brain_Death_46C3A0);
}

u8** Slig::ResBlockForMotion_4654D0(s16 motion)
{
    s16 new_idx = 0;
    if (motion < eSligMotions::Motion_33_Sleeping_46A410)
    {
        new_idx = 0;
    }
    else if (motion < eSligMotions::Motion_35_Knockback_46A720)
    {
        new_idx = 1;
    }
    else if (motion < eSligMotions::Motion_39_OutToFall_46A9E0)
    {
        new_idx = 2;
    }
    else if (motion < eSligMotions::Motion_42_LandingFatal_46AFE0)
    {
        new_idx = 3;
    }
    else if (motion < eSligMotions::Motion_43_ShootZ_468E30)
    {
        new_idx = 4;
    }
    else if (motion < eSligMotions::Motion_45_Smash_46A990)
    {
        new_idx = 5;
    }
    else if (motion < eSligMotions::State_46_PullLever_46A590)
    {
        new_idx = 6;
    }
    else if (motion < eSligMotions::Motion_47_LiftUp_4665A0)
    {
        new_idx = 7;
    }
    else if (motion < eSligMotions::Motion_52_Beat_46AA90)
    {
        new_idx = 8;
    }
    else
    {
        new_idx = motion >= 53 ? 0 : 9;
    }

    if (new_idx == field_138_res_idx)
    {
        return field_210_resources.res[field_138_res_idx];
    }

    field_138_res_idx = new_idx;
    return field_210_resources.res[field_138_res_idx];
}

void Slig::ToShoot_46F1D0()
{
    mNextMotion = eSligMotions::Motion_6_Shoot_468820;
    SetBrain(&Slig::Brain_Shooting_46EFD0);
    field_200_num_times_to_shoot = 0;
    MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
}

void Slig::ToZShoot_46F200()
{
    mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    field_114_timer = sGnFrame + field_174_tlv.field_4C_z_shoot_delay;
    SetBrain(&Slig::Brain_ZSpottedEnemy_46F260);
    field_118_unused = Math_RandomRange_450F20(3, 5);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
}

void Slig::ShouldStilBeAlive_46C0D0()
{
    if (!field_20C_force_alive_state)
    {
        // Check not falling and not in the current screen
        if (mCurrentMotion != eSligMotions::Motion_7_Falling_46A1A0 && mCurrentMotion != eSligMotions::Motion_39_OutToFall_46A9E0)
        {
            if (!gMap.Is_Point_In_Current_Camera_4449C0(
                    mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                    mBaseAnimatedWithPhysicsGameObject_PathNumber,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    0))
            {
                if (field_1F4_points_count <= 0)
                {
                    // No patrol points, die
                    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                }
                else
                {
                    s32 i = 0;
                    while (!gMap.Is_Point_In_Current_Camera_4449C0(
                        mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                        mBaseAnimatedWithPhysicsGameObject_PathNumber,
                        FP_FromInteger(field_1CC_points[i].field_0_x),
                        FP_FromInteger(field_1CC_points[i].field_2_y),
                        0))
                    {
                        if (i >= field_1F4_points_count)
                        {
                            // No within any out our patrol points, die
                            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                            break;
                        }
                        i++;
                    }
                }
            }
        }
    }
}

void Slig::ToAbeDead_466270()
{
    mNextMotion = eSligMotions::Motion_25_SpeakLaugh_467ED0;
    SetBrain(&Slig::Brain_EnemyDead_466190);
    field_114_timer = sGnFrame + 45;
}

void Slig::WaitOrWalk_46E440()
{
    mNextMotion = eSligMotions::Motion_2_Walking_469130;
    SetBrain(&Slig::Brain_Walking_46DE90);

    // Right rect bound
    if (!IsFacingEffectiveLeft_46BD70(this) && (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(2)) + mBaseAnimatedWithPhysicsGameObject_XPos >= FP_FromInteger(field_13C_zone_rect.w))
    {
        PauseALittle_46DBD0();
        MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
        return;
    }

    // Left rect bound
    if (IsFacingEffectiveLeft_46BD70(this) && (mBaseAnimatedWithPhysicsGameObject_XPos - (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(2))) <= FP_FromInteger(field_13C_zone_rect.x))
    {
        PauseALittle_46DBD0();
        MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
        return;
    }

    Brain_Walking_46DE90();
    MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
}

s32 Slig::IsFacingEffectiveLeft_46BD70(Slig* pSlig)
{
    s32 bFlipX = pSlig->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX);
    if (pSlig->mCurrentMotion == eSligMotions::Motion_5_TurnAroundStanding_469C80
        && pSlig->mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame > 4)
    {
        // Flip the result
        return bFlipX == 0;
    }
    return bFlipX;
}

void Slig::PauseALittle_46DBD0()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_114_timer = sGnFrame + field_174_tlv.field_1E_pause_left_min;
        if (field_174_tlv.field_20_pause_left_max > field_174_tlv.field_1E_pause_left_min)
        {
            field_114_timer += Math_NextRandom() % (field_174_tlv.field_20_pause_left_max - field_174_tlv.field_1E_pause_left_min);
        }
    }
    else
    {
        field_114_timer = sGnFrame + field_174_tlv.field_22_pause_right_min;
        if (field_174_tlv.field_24_pause_right_max > field_174_tlv.field_22_pause_right_min)
        {
            field_114_timer += Math_NextRandom() % (field_174_tlv.field_24_pause_right_max - field_174_tlv.field_22_pause_right_min);
        }
    }

    mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    SetBrain(&Slig::Brain_Idle_46D6E0);
}

void Slig::ToTurn_46DE70()
{
    mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
    SetBrain(&Slig::Brain_Turning_46DC70);
}

void Slig::ToPanicRunning_46CC20()
{
    mNextMotion = eSligMotions::Motion_4_Running_469690;
    SetBrain(&Slig::Brain_PanicRunning_46CA20);
    Brain_PanicRunning_46CA20();
    MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
}

void Slig::ToPanic_46CD40()
{
    mNextMotion = eSligMotions::Motion_29_SpeakPanic_4681D0;
    SetBrain(&Slig::Brain_PanicYelling_46CC50);
}

void Slig::ToChase_46D080()
{
    field_114_timer = sGnFrame + field_174_tlv.field_3E_time_to_wait_before_chase;

    if (!VIsFacingMe(sControlledCharacter_50767C))
    {
        mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
    }
    mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    SetBrain(&Slig::Brain_StartChasing_46CF90);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
}

void Slig::ToKilledAbe_4662E0()
{
    mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    SetBrain(&Slig::Brain_KilledEnemy_4662A0);
    field_114_timer = sGnFrame + 15;
}

inline PSX_RECT MakeRectFromFP(FP x, FP y, FP w, FP h)
{
    PSX_RECT r = {};
    r.x = FP_GetExponent(x);
    r.w = FP_GetExponent(w);
    r.y = FP_GetExponent(y);
    r.h = FP_GetExponent(h);
    return r;
}

inline PSX_RECT MakeMinMaxRect(FP x, FP y, FP w, FP h, bool flipToMaxMin = false)
{
    if (flipToMaxMin)
    {
        return MakeRectFromFP(
            std::max(x, w),
            std::max(y, h),
            std::min(x, w),
            std::min(y, h));
    }
    else
    {
        return MakeRectFromFP(
            std::min(x, w),
            std::min(y, h),
            std::max(x, w),
            std::max(y, h));
    }
}

s16 Slig::FindBeatTarget_46D0E0(s32 /*typeToFind*/, s32 gridBlocks)
{
    const FP kGridSize = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
    const FP k2Scaled = FP_FromInteger(2) * kGridSize;
    const FP kGridBlocksScaled = FP_FromInteger(gridBlocks) * kGridSize;

    const FP xAndW = mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) ? mBaseAnimatedWithPhysicsGameObject_XPos - kGridBlocksScaled : mBaseAnimatedWithPhysicsGameObject_XPos + kGridBlocksScaled;

    PSX_RECT hitRect = MakeMinMaxRect(
        xAndW,
        mBaseAnimatedWithPhysicsGameObject_YPos,
        xAndW,
        mBaseAnimatedWithPhysicsGameObject_YPos - k2Scaled,
        true);

    for (s32 i = 0; i < gBaseAliveGameObjects_4FC8A0->Size(); i++)
    {
        auto pTargetObj = gBaseAliveGameObjects_4FC8A0->ItemAt(i);
        if (!pTargetObj)
        {
            break;
        }
        if (pTargetObj != this && pTargetObj->mBaseGameObjectTypeId == ReliveTypes::eMudokon)
        {
            const PSX_RECT bRect = pTargetObj->VGetBoundingRect();
            if (hitRect.w <= bRect.w && hitRect.x >= bRect.x && hitRect.y >= bRect.y && hitRect.h <= bRect.h && !Slig::IsInInvisibleZone_418870(pTargetObj))
            {
                return 1;
            }
        }
    }
    return 0;
}

s16 Slig::HandleEnemyStopper_46BF30(s32 gridBlocks)
{
    s32 directedGirdBlocks = gridBlocks;
    auto bFacingLeft = IsFacingEffectiveLeft_46BD70(this);
    if (bFacingLeft)
    {
        directedGirdBlocks = -gridBlocks;
    }

    const auto dirScaled = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(directedGirdBlocks) + mBaseAnimatedWithPhysicsGameObject_XPos;
    auto pStopper = static_cast<Path_EnemyStopper*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        FP_GetExponent(dirScaled),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::EnemyStopper_79));

    if (!pStopper)
    {
        return 0;
    }

    //TODO different from Exoddus (inverted) - watch out!
    if (SwitchStates_Get(pStopper->field_1A_switch_id))
    {
        return 0;
    }

    if (pStopper->field_18_direction == Path_EnemyStopper::StopDirection::Both_2)
    {
        return 1;
    }

    if (bFacingLeft && pStopper->field_18_direction == Path_EnemyStopper::StopDirection::Left_0)
    {
        return 1;
    }

    if (!bFacingLeft && pStopper->field_18_direction == Path_EnemyStopper::StopDirection::Right_1)
    {
        return 1;
    }

    return 0;
}

void Slig::RespondToEnemyOrPatrol_465DF0()
{
    field_14C_unused = 0;

    if (field_174_tlv.field_28_shoot_on_sight_delay)
    {
        if (sControlledCharacter_50767C->mBaseGameObjectTypeId != ReliveTypes::eSlig
            || field_174_tlv.field_26_shoot_possessed_sligs != Path_Slig::ShootPossessedSligs::eNo_0)
        {
            SetBrain(&Slig::Brain_SpottedEnemy_465EB0);
            mNextMotion = eSligMotions::Motion_31_SpeakAIFreeze_468350;
            field_114_timer = field_174_tlv.field_28_shoot_on_sight_delay + sGnFrame;
        }
        else
        {
            field_20E_spotted_possessed_slig = 1;
            TurnOrWalk_46D5B0(0);
        }
    }
    else if (VIsFacingMe(sControlledCharacter_50767C))
    {
        if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_SpriteScale)
        {
            ToShoot_46F1D0();
        }
        else
        {
            ToZShoot_46F200();
        }
    }
    else
    {
        ToTurn_46DE70();
    }
}

void Slig::TurnOrWalk_46D5B0(s32 a2)
{
    if (a2 == 1)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (mBaseAnimatedWithPhysicsGameObject_XPos > FP_FromInteger(field_13C_zone_rect.x) + (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(4)))
            {
                ToTurn_46DE70();
                return;
            }
        }
        else
        {
            if (mBaseAnimatedWithPhysicsGameObject_XPos < FP_FromInteger(field_13C_zone_rect.w) - (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(4)))
            {
                ToTurn_46DE70();
                return;
            }
        }
    }

    if (!mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        if (mBaseAnimatedWithPhysicsGameObject_XPos > FP_FromInteger(field_13C_zone_rect.w) - (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(4)))
        {
            ToTurn_46DE70();
            return;
        }
    }
    else
    {
        if (mBaseAnimatedWithPhysicsGameObject_XPos < FP_FromInteger(field_13C_zone_rect.x) + (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(4)))
        {
            ToTurn_46DE70();
            return;
        }
    }

    WaitOrWalk_46E440();
}

void Slig::ToPanicTurn()
{
    mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
    SetBrain(&Slig::Brain_PanicTurning_46C7C0);
}

s16 Slig::GetNextMotionIncGameSpeak_467700(u16 input)
{
    if (sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
    {
        switch (mNextMotion)
        {
            case eSligMotions::Motion_21_SpeakHereBoy_467BD0:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eHereBoy_1, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_21_SpeakHereBoy_467BD0;

            case eSligMotions::Motion_22_SpeakHi_467C90:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eHi_0, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_22_SpeakHi_467C90;

            case eSligMotions::Motion_23_SpeakFreeze_467D50:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eStay_3, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_23_SpeakFreeze_467D50;

            case eSligMotions::Motion_24_SpeakGetHim_467E10:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eGetHim_2, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_24_SpeakGetHim_467E10;

            case eSligMotions::Motion_25_SpeakLaugh_467ED0:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eLaugh_7, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_25_SpeakLaugh_467ED0;

            case eSligMotions::Motion_26_SpeakBullshit1_467F90:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eBullshit_4, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_26_SpeakBullshit1_467F90;

            case eSligMotions::Motion_27_SpeakLookOut_468050:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eLookOut_5, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_27_SpeakLookOut_468050;

            case eSligMotions::Motion_28_SpeakBullshit2_468110:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eBullshit2_6, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_28_SpeakBullshit2_468110;

            case eSligMotions::Motion_29_SpeakPanic_4681D0:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eHelp_10, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_29_SpeakPanic_4681D0;

            case eSligMotions::Motion_30_SpeakWhat_468290:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eWhat_9, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_30_SpeakWhat_468290;

            case eSligMotions::Motion_31_SpeakAIFreeze_468350:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eFreeze_8, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_31_SpeakAIFreeze_468350;

            case eSligMotions::Motion_32_Blurgh_468410:
                mNextMotion = -1;
                Slig_GameSpeak_SFX_46F560(SligSpeak::eBlurgh_11, 0, field_110_pitch_min, this);
                return eSligMotions::Motion_32_Blurgh_468410;

            default:
                return -1;
        }
    }

    if (Input_IsChanting())
    {
        if (field_254_prevent_depossession & 4)
        {
            return -1;
        }

        field_128_timer = sGnFrame + 30;
        SFX_Play_Mono(SoundEffect::PossessEffect_21, 0, 0);
        return eSligMotions::Motion_37_Depossessing_4684D0;
    }

    if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8))
    {
        if (input & sInputKey_GameSpeak2_4C65BC)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::Slig_HereBoy_24);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eHereBoy_1, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_21_SpeakHereBoy_467BD0;
        }
        if (input & sInputKey_GameSpeak1_4C65C8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::Slig_Hi_23);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eHi_0, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_22_SpeakHi_467C90;
        }

        if (input & sInputKey_GameSpeak3_4C65C0)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eUnknown_27);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eFreeze_8, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_23_SpeakFreeze_467D50;
        }

        if (input & sInputKey_GameSpeak4_4C65C4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eUnknown_25);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eGetHim_2, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_24_SpeakGetHim_467E10;
        }
        return -1;
    }
    else if (Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler_4C65DC))
    {
        if (input & sInputKey_GameSpeak8_4C65E0)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eUnknown_8);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eLaugh_7, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_25_SpeakLaugh_467ED0;
        }

        if (input & sInputKey_GameSpeak6_4C65E8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eUnknown_5);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eBullshit_4, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_26_SpeakBullshit1_467F90;
        }

        if (input & sInputKey_GameSpeak7_4C65E4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::Slig_LookOut_6);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eLookOut_5, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_27_SpeakLookOut_468050;
        }

        if (input & sInputKey_GameSpeak5_4C65EC)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eUnknown_7);
            Slig_GameSpeak_SFX_46F560(SligSpeak::eBullshit2_6, 0, field_110_pitch_min, this);
            return eSligMotions::Motion_28_SpeakBullshit2_468110;
        }
    }
    return -1;
}

Bool32 Slig::RenderLayerIs_46C0A0(BaseAliveGameObject* pThis)
{
    return pThis->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer == Layer::eLayer_BeforeWell_Half_3 || pThis->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer == Layer::eLayer_BeforeWell_22;
}

s16 Slig::IsAbeEnteringDoor_46BEE0(BaseAliveGameObject* pThis)
{
    if (((pThis->mBaseGameObjectTypeId == ReliveTypes::eAbe) && (pThis->mCurrentMotion == eAbeMotions::Motion_156_DoorEnter_42D370 && pThis->mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame > 7)) || (pThis->mCurrentMotion == eAbeMotions::Motion_157_DoorExit_42D780 && pThis->mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame < 4))
    {
        return 1;
    }
    return 0;
}

s16 Slig::IsWallBetween_46BE60(Slig* pLeft, BaseAliveGameObject* pRight)
{
    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    return sCollisions->RayCast(
               pLeft->mBaseAnimatedWithPhysicsGameObject_XPos,
               pLeft->mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(25),
               pRight->mBaseAnimatedWithPhysicsGameObject_XPos,
               pRight->mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(25),
               &pLine,
               &hitX,
               &hitY,
               pLeft->mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60)
        == 1;
}

void Slig::Slig_GameSpeak_SFX_46F560(SligSpeak effectId, s32 defaultVol, s32 pitch_min, BaseAliveGameObject* pObj)
{
    s32 volume = defaultVol;
    if (defaultVol == 0)
    {
        volume = sSligSounds2[static_cast<s32>(effectId)].field_C_default_volume;
    }
    if (pObj)
    {
        if (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
        {
            volume = FP_GetExponent(FP_FromInteger(volume * 2) / FP_FromInteger(3));
        }
    }
    SFX_SfxDefinition_Play_4770F0(&sSligSounds2[static_cast<s32>(effectId)], volume, pitch_min, pitch_min);
}

s16 Slig::IsInInvisibleZone_418870(BaseAnimatedWithPhysicsGameObject* pObj)
{
    /* TODO: Not used in AE but might be possible to activate in AO
    if (gAbeInvisibleCheat_5076F8)
    {
        return TRUE;
    }
    */

    if (Event_Get(kEventAbeOhm))
    {
        return FALSE;
    }

    const PSX_RECT rect = pObj->VGetBoundingRect();

    Path_TLV* pTlv = gMap.TLV_Get_At_446260(rect.x, rect.y, rect.w, rect.h, TlvTypes::InvisibleZone_58);
    if (pTlv)
    {
        if (rect.x >= pTlv->field_10_top_left.field_0_x && rect.x <= pTlv->field_14_bottom_right.field_0_x && rect.y >= pTlv->field_10_top_left.field_2_y)
        {
            if (rect.y <= pTlv->field_14_bottom_right.field_2_y && rect.w >= pTlv->field_10_top_left.field_0_x && rect.w <= pTlv->field_14_bottom_right.field_0_x && rect.h >= pTlv->field_10_top_left.field_2_y && rect.h <= pTlv->field_14_bottom_right.field_2_y)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

void Slig::ToStand()
{
    field_12C_falling_velx_scale_factor = FP_FromInteger(0);
    mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
    mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
    mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
    field_126_input = 0;
    field_128_timer = Math_RandomRange_450F20(0, 60) + sGnFrame + 120;
    MapFollowMe_401D30(TRUE);
}

s16 Slig::IsInZCover_46BDA0(BaseAnimatedWithPhysicsGameObject* pObj)
{
    const PSX_RECT bRect = pObj->VGetBoundingRect();
    return Bullet::InZBulletCover(FP_FromInteger(bRect.x), FP_FromInteger(bRect.y), bRect);
}

void Slig::CheckPlatformVanished()
{
    if (mLiftPoint)
    {
        if (mLiftPoint->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
        {
            // Platform is somehow gone, fall.
            const auto oldMotion = mCurrentMotion;
            VOnTrapDoorOpen();
            mCurrentMotion = oldMotion;
        }
        SetActiveCameraDelayedFromDir_401C90();
    }
}


s16 Slig::MoveLift_4665E0(FP ySpeed)
{
    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);

    pLiftPoint->Move(FP_FromInteger(0), ySpeed, 0);
    CheckPlatformVanished();
    mBaseAnimatedWithPhysicsGameObject_VelY = pLiftPoint->mBaseAnimatedWithPhysicsGameObject_VelY;

    if (sControlledCharacter_50767C == this
        && !(mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        && mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame != 5)
    {
        return mCurrentMotion;
    }

    if (ySpeed < FP_FromInteger(0))
    {
        if (pLiftPoint->OnTopFloor())
        {
            return eSligMotions::Motion_51_LiftGripping_466480;
        }

        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            return eSligMotions::Motion_47_LiftUp_4665A0;
        }

        if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            return eSligMotions::Motion_48_LiftDown_4665C0;
        }
    }
    else if (ySpeed > FP_FromInteger(0))
    {
        if (pLiftPoint->OnBottomFloor())
        {
            return eSligMotions::Motion_51_LiftGripping_466480;
        }

        if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            return eSligMotions::Motion_48_LiftDown_4665C0;
        }

        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            return eSligMotions::Motion_47_LiftUp_4665A0;
        }
    }

    // Strange how this isn't "if nothing pressed and on a floor then let go ??"
    if (Input().Pressed() && pLiftPoint->OnAnyFloor())
    {
        return eSligMotions::Motion_50_LiftUngrip_466460;
    }

    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);
    return eSligMotions::Motion_51_LiftGripping_466480;
}

void Slig::GameSpeakResponse_46ED60()
{
    GameSpeakEvents speak = GameSpeakEvents::eNone_m1;

    const s32 lastIdx = pEventSystem_4FF954->field_18_last_event_index;
    if (field_15C_last_event_index == lastIdx)
    {
        if (pEventSystem_4FF954->field_10_last_event == GameSpeakEvents::eNone_m1)
        {
            speak = GameSpeakEvents::eNone_m1;
        }
        else
        {
            speak = GameSpeakEvents::eSameAsLast_m2;
        }
    }
    else
    {
        field_15C_last_event_index = lastIdx;
        speak = pEventSystem_4FF954->field_10_last_event;
    }

    switch (speak)
    {
        case GameSpeakEvents::eWhistleHigh_1:
        case GameSpeakEvents::eWhistleLow_2:
            if (!(Math_NextRandom() & 4))
            {
                field_258_next_gamespeak_motion = eSligMotions::Motion_26_SpeakBullshit1_467F90;
            }
            else
            {
                field_258_next_gamespeak_motion = eSligMotions::Motion_28_SpeakBullshit2_468110;
            }
            break;

        case GameSpeakEvents::eFart_3:
        case GameSpeakEvents::eLaugh_4:
        case GameSpeakEvents::eUnknown_8:
        case GameSpeakEvents::eUnknown_14:
        case GameSpeakEvents::eUnknown_15:
        case GameSpeakEvents::eUnknown_25:
        case GameSpeakEvents::eUnknown_30:
            field_258_next_gamespeak_motion = eSligMotions::Motion_32_Blurgh_468410;
            return;

        case GameSpeakEvents::eUnknown_5:
            field_258_next_gamespeak_motion = eSligMotions::Motion_26_SpeakBullshit1_467F90;
            break;

        case GameSpeakEvents::Slig_LookOut_6:
            if (!(Math_NextRandom() & 4))
            {
                field_258_next_gamespeak_motion = eSligMotions::Motion_30_SpeakWhat_468290;
            }
            else
            {
                field_258_next_gamespeak_motion = eSligMotions::Motion_29_SpeakPanic_4681D0;
            }
            break;

        case GameSpeakEvents::eUnknown_7:
            field_258_next_gamespeak_motion = eSligMotions::Motion_28_SpeakBullshit2_468110;
            break;

        case GameSpeakEvents::eHello_9:
        case GameSpeakEvents::Slig_Hi_23:
            field_258_next_gamespeak_motion = eSligMotions::Motion_22_SpeakHi_467C90;
            break;

        case GameSpeakEvents::eFollowMe_10:
        case GameSpeakEvents::eWait_12:
            if (Math_NextRandom() & 8)
            {
                field_258_next_gamespeak_motion = eSligMotions::Motion_26_SpeakBullshit1_467F90;
            }
            else
            {
                field_258_next_gamespeak_motion = eSligMotions::Motion_28_SpeakBullshit2_468110;
            }
            break;

        case GameSpeakEvents::eAnger_11:
        case GameSpeakEvents::eUnknown_13:
        case GameSpeakEvents::eUnknown_16:
        case GameSpeakEvents::eUnknown_17:
        case GameSpeakEvents::eUnknown_18:
        case GameSpeakEvents::eUnknown_19:
        case GameSpeakEvents::eUnknown_20:
        case GameSpeakEvents::eUnknown_21:
        case GameSpeakEvents::eUnknown_22:
        case GameSpeakEvents::eUnknown_26:
        case GameSpeakEvents::eUnknown_27:
        case GameSpeakEvents::eUnknown_28:
        case GameSpeakEvents::eUnknown_31:
            field_258_next_gamespeak_motion = eSligMotions::Motion_25_SpeakLaugh_467ED0;
            break;

        default:
            field_258_next_gamespeak_motion = eSligMotions::Motion_30_SpeakWhat_468290;
            break;
    }
}

Bool32 Slig::VIs8_465630(s16 motion)
{
    return motion == eSligMotions::Motion_8_Unknown_4673E0;
}

void Slig::MoveOnLine()
{
    const FP oldX = mBaseAnimatedWithPhysicsGameObject_XPos;
    if (BaseAliveGameObjectCollisionLine)
    {
        BaseAliveGameObjectCollisionLine = BaseAliveGameObjectCollisionLine->MoveOnLine(
            &mBaseAnimatedWithPhysicsGameObject_XPos,
            &mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_VelX);
        if (BaseAliveGameObjectCollisionLine)
        {
            if (mLiftPoint)
            {
                if (BaseAliveGameObjectCollisionLine->field_8_type != eLineTypes::eDynamicCollision_32 && BaseAliveGameObjectCollisionLine->field_8_type != eLineTypes::eBackgroundDynamicCollision_36)
                {
                    const auto oldMotion = mCurrentMotion;
                    VOnTrapDoorOpen();
                    mCurrentMotion = oldMotion;
                }
            }
            else
            {
                if (BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eDynamicCollision_32 || BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eBackgroundDynamicCollision_36)
                {
                    // TODO: Inlined
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
        }
        else
        {
            VOnTrapDoorOpen();
            BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
            if (mCurrentMotion == eSligMotions::Motion_9_SlidingToStand_469DF0 || mCurrentMotion == eSligMotions::Motion_10_SlidingTurn_469F10)
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = (mBaseAnimatedWithPhysicsGameObject_VelX * FP_FromDouble(0.5));
            }
            mCurrentMotion = eSligMotions::Motion_40_FallingInitiate_46AA60;
            mBaseAnimatedWithPhysicsGameObject_XPos = mBaseAnimatedWithPhysicsGameObject_VelX + oldX;
        }
    }
    else
    {
        VOnTrapDoorOpen();
        mCurrentMotion = eSligMotions::Motion_39_OutToFall_46A9E0;
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
    }
}

void Slig::OperateLift()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mCurrentMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
        mNextMotion = eSligMotions::Motion_49_LiftGrip_4663A0;

        const auto camPos = gMap.GetDirection_444A40(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos);
        if ((camPos != CameraPos::eCamCurrent_0 && camPos != CameraPos::eCamInvalid_m1)
            && MusicController::GetAbmientAndMusicInfo(nullptr, nullptr, nullptr) <= MusicController::MusicTypes::eChase_4)
        {
            MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
        }
        Slig::Slig_SoundEffect_46F310(SligSfx::eStandingTurn_1);
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit5_FlipX);
            ToStand();
        }
    }
    else
    {
        mCurrentMotion = eSligMotions::Motion_49_LiftGrip_4663A0;
    }
}

s16 Slig::HandlePlayerControlled()
{
    FP kScaleGrid = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);

    const auto pressed = Input().Pressed();
    if (pressed & sInputKey_Right_4C6590)
    {
        if (!mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (pressed & sInputKey_Run_4C65A8)
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = kScaleGrid / FP_FromInteger(4);
                mCurrentMotion = eSligMotions::Motion_3_StandToRun_469C00;
                return 1;
            }

            if (!WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), kScaleGrid * FP_FromInteger(2)))
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = kScaleGrid / FP_FromInteger(9);
                mCurrentMotion = eSligMotions::Motion_16_StandingToStep_468FD0;
                return 1;
            }

            if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), kScaleGrid))
            {
                return 0;
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = kScaleGrid / FP_FromInteger(6);
                mCurrentMotion = eSligMotions::Motion_15_SteppingToStand_469080;
                return 1;
            }
        }
        else
        {
            mCurrentMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            return 1;
        }
    }

    if (pressed & sInputKey_Left_4C6594)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (pressed & sInputKey_Run_4C65A8)
            {
                mCurrentMotion = eSligMotions::Motion_3_StandToRun_469C00;
                mBaseAnimatedWithPhysicsGameObject_VelX = -(kScaleGrid / FP_FromInteger(4));
                return 1;
            }
            if (!WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), -kScaleGrid * FP_FromInteger(2)))
            {
                mCurrentMotion = eSligMotions::Motion_16_StandingToStep_468FD0;
                mBaseAnimatedWithPhysicsGameObject_VelX = -(kScaleGrid / FP_FromInteger(9));
                return 1;
            }
            if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), -kScaleGrid))
            {
                return 0;
            }
            else
            {
                mCurrentMotion = eSligMotions::Motion_15_SteppingToStand_469080;
                mBaseAnimatedWithPhysicsGameObject_VelX = -(kScaleGrid / FP_FromInteger(6));
                return 1;
            }
        }
        else
        {
            mCurrentMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            return 1;
        }
    }

    if (Input().IsAnyHeld(sInputKey_DoAction_4C65A4)
        && !(pressed & (sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC)))
    {
        if (!Input_IsChanting())
        {
            Path_Lever* pTlv = static_cast<Path_Lever*>(gMap.TLV_Get_At_446260(
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                TlvTypes::Lever_26));
            BaseAliveGameObjectPathTLV = pTlv;
            if (pTlv)
            {
                if (FP_FromInteger(FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos) - pTlv->field_10_top_left.field_0_x) < kScaleGrid)
                {
                    if (!(mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX)))
                    {
                        auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(
                            ReliveTypes::eLever,
                            mBaseAnimatedWithPhysicsGameObject_XPos + kScaleGrid,
                            mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));
                        if (pSwitch)
                        {
                            pSwitch->VPull(
                                mBaseAnimatedWithPhysicsGameObject_XPos < pSwitch->mBaseAnimatedWithPhysicsGameObject_XPos);
                            mCurrentMotion = eSligMotions::State_46_PullLever_46A590;
                            return 1;
                        }
                        mCurrentMotion = eSligMotions::State_46_PullLever_46A590;
                        return 1;
                    }
                    mNextMotion = eSligMotions::State_46_PullLever_46A590;
                    mCurrentMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
                    return 1;
                }
                if (FP_FromInteger(pTlv->field_14_bottom_right.field_0_x - FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos)) < kScaleGrid)
                {
                    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(ReliveTypes::eLever, mBaseAnimatedWithPhysicsGameObject_XPos - kScaleGrid, mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));
                        if (pSwitch)
                        {
                            pSwitch->VPull(
                                mBaseAnimatedWithPhysicsGameObject_XPos < pSwitch->mBaseAnimatedWithPhysicsGameObject_XPos);
                        }
                        mCurrentMotion = eSligMotions::State_46_PullLever_46A590;
                        return 1;
                    }
                    mNextMotion = eSligMotions::State_46_PullLever_46A590;
                    mCurrentMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
                    return 1;
                }
                Slig::Slig_GameSpeak_SFX_46F560(SligSpeak::eWhat_9, 0, field_110_pitch_min, this);
            }
            else
            {
                Slig::Slig_GameSpeak_SFX_46F560(SligSpeak::eWhat_9, 0, field_110_pitch_min, this);
            }
            mCurrentMotion = eSligMotions::Motion_30_SpeakWhat_468290;
            return 1;
        }
    }
    if (pressed & sInputKey_ThrowItem_4C65B4
        && !(pressed & (sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC)))
    {
        if (!Input_IsChanting())
        {
            mCurrentMotion = eSligMotions::Motion_6_Shoot_468820;
            field_128_timer = sGnFrame + 60;
            return 1;
        }
    }
    if (pressed & sInputKey_FartRoll_4C65B0
        && !(pressed & (sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC)))
    {
        if (!Input_IsChanting())
        {
            mCurrentMotion = eSligMotions::Motion_52_Beat_46AA90;
            field_128_timer = sGnFrame + 60;
            return 1;
        }
    }

    if (pressed & sInputKey_Down_4C659C)
    {
        if (mLiftPoint)
        {
            if (mLiftPoint && mLiftPoint->mBaseGameObjectTypeId == ReliveTypes::eLiftPoint)
            {
                if (FP_Abs(mBaseAnimatedWithPhysicsGameObject_XPos - FP_FromInteger((BaseAliveGameObjectCollisionLine->field_0_rect.x + BaseAliveGameObjectCollisionLine->field_0_rect.w) / 2)) < kScaleGrid / FP_FromInteger(2))
                {
                    OperateLift();
                    return 1;
                }
            }
        }
        else
        {
            if (Input().IsAnyHeld(sInputKey_Down_4C659C))
            {
                Slig::Slig_GameSpeak_SFX_46F560(SligSpeak::eWhat_9, 0, field_110_pitch_min, this);
                mCurrentMotion = eSligMotions::Motion_30_SpeakWhat_468290;
                return 1;
            }
            ToStand();
            return 0;
        }
    }
    if (pressed & sInputKey_Up_4C6598)
    {
        if (mLiftPoint)
        {
            if (mLiftPoint->field_10C == 1)
            {
                if (FP_Abs(mBaseAnimatedWithPhysicsGameObject_XPos - FP_FromInteger((BaseAliveGameObjectCollisionLine->field_0_rect.x + BaseAliveGameObjectCollisionLine->field_0_rect.w) / 2)) < kScaleGrid / FP_FromInteger(2))
                {
                    OperateLift();
                    return 1;
                }
            }
        }
        else
        {
            if (Input().IsAnyHeld(sInputKey_Up_4C6598))
            {
                Slig::Slig_GameSpeak_SFX_46F560(SligSpeak::eWhat_9, 0, field_110_pitch_min, this);
                mCurrentMotion = eSligMotions::Motion_30_SpeakWhat_468290;
                return 1;
            }
            ToStand();
            return 0;
        }
    }

    if (Input().IsAnyHeld(sInputKey_Hop_4C65A0 | sInputKey_FartRoll_4C65B0) && !(Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC)))
    {
        Slig::Slig_GameSpeak_SFX_46F560(SligSpeak::eBlurgh_11, 0, field_110_pitch_min, this);
        mCurrentMotion = eSligMotions::Motion_32_Blurgh_468410;
        return 1;
    }
    ToStand();
    return 0;
}

void Slig::PlayerControlRunningSlideStopOrTurn(s16 last_anim_frame)
{
    if (mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left_4C6594))
    {
        mBaseAnimatedWithPhysicsGameObject_VelX = mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromDouble(13.2);
        mCurrentMotion = eSligMotions::Motion_10_SlidingTurn_469F10;
        field_126_input = 0;
        return;
    }

    if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right_4C6590))
    {
        mBaseAnimatedWithPhysicsGameObject_VelX = mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromDouble(-13.2);
        mCurrentMotion = eSligMotions::Motion_10_SlidingTurn_469F10;
        field_126_input = 0;
        return;
    }

    if (!Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
    {
        if (mBaseAnimatedWithPhysicsGameObject_VelX >= FP_FromInteger(0))
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromDouble(13.2);
        }
        else
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromDouble(-13.2);
        }

        mCurrentMotion = eSligMotions::Motion_9_SlidingToStand_469DF0;
        field_126_input = 0;
        return;
    }

    if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
    {
        field_126_input = 0;
        return;
    }

    mPreviousMotion = 2;
    mBaseAliveGameObjectLastAnimFrame = last_anim_frame;
    field_11E_return_to_previous_motion = 1;

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_VelX = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9);
    }
    field_126_input = 0;
}

void Slig::PlayerControlRunningSlideStopOrTurnFrame4()
{
    PlayerControlRunningSlideStopOrTurn(6);
}

void Slig::PlayerControlRunningSlideStopOrTurnFrame12()
{
    PlayerControlRunningSlideStopOrTurn(15);
}

void Slig::SlowDown(FP speed)
{
    if (FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        MoveOnLine();

        if (mBaseAnimatedWithPhysicsGameObject_VelX <= FP_FromInteger(0))
        {
            if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0))
            {
                mBaseAnimatedWithPhysicsGameObject_VelX += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * speed);
                if (mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0))
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
                }
            }
        }
        else
        {
            mBaseAnimatedWithPhysicsGameObject_VelX -= (mBaseAnimatedWithPhysicsGameObject_SpriteScale * speed);
            if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0))
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
            }
        }
    }
}

s16 Slig::MainMovement_467020()
{
    if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
    {
        return HandlePlayerControlled();
    }

    switch (mNextMotion)
    {
        case eSligMotions::Motion_5_TurnAroundStanding_469C80:

            mCurrentMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            mNextMotion = -1;
            break;
        case eSligMotions::Motion_2_Walking_469130:

            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), -ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale)))
                {
                    return 0;
                }
                mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
            }
            else
            {
                if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale)))
                {
                    return 0;
                }
                mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
            }

            mCurrentMotion = eSligMotions::Motion_1_StandToWalk_4695D0;
            mNextMotion = -1;
            break;
        case eSligMotions::Motion_4_Running_469690:

            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
            }

            mCurrentMotion = eSligMotions::Motion_3_StandToRun_469C00;
            mNextMotion = -1;
            break;
        case eSligMotions::Motion_6_Shoot_468820:
        case eSligMotions::Motion_43_ShootZ_468E30:
            field_12C_falling_velx_scale_factor = FP_FromInteger(0);
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
            mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
            field_128_timer = sGnFrame + 60;
            mCurrentMotion = mNextMotion;
            mNextMotion = -1;
            break;
        default:
            if (mNextMotion < eSligMotions::Motion_21_SpeakHereBoy_467BD0 || mNextMotion > eSligMotions::Motion_32_Blurgh_468410)
            {
                if (mNextMotion == eSligMotions::Motion_13_ReloadGun_4687B0
                    || mNextMotion == eSligMotions::State_46_PullLever_46A590
                    || mNextMotion == eSligMotions::Motion_52_Beat_46AA90)
                {
                    mCurrentMotion = mNextMotion;
                    mNextMotion = -1;
                    break;
                }
            }
            else
            {
                mCurrentMotion = GetNextMotionIncGameSpeak_467700(0);
                if (mCurrentMotion != -1)
                {
                    Event_Broadcast(kEventSpeaking, this);
                    break;
                }
            }

            ToStand();
            return 0;
    }

    return 1;
}

void Slig::ToKnockBack()
{
    Environment_SFX_42A220(EnvironmentSfx::eKnockback_13, 0, 0x7FFF, this);
    if (FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        mBaseAnimatedWithPhysicsGameObject_XPos -= mBaseAnimatedWithPhysicsGameObject_VelX;
    }

    if (BaseAliveGameObjectCollisionLine)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
        }
        else
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
        }
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
    }

    if (mNextMotion == eSligMotions::Motion_45_Smash_46A990)
    {
        mBaseAnimatedWithPhysicsGameObject_VelX = -mBaseAnimatedWithPhysicsGameObject_VelX;
    }

    MapFollowMe_401D30(1);

    if (mBaseAnimatedWithPhysicsGameObject_VelY < FP_FromInteger(0))
    {
        mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
    }

    mCurrentMotion = eSligMotions::Motion_35_Knockback_46A720;
    field_128_timer = sGnFrame + 10;
}

void Slig::Motion_0_StandIdle_467640()
{
    if (!MainMovement_467020())
    {
        if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
        {
            if (Input_IsChanting())
            {
                if (!(field_254_prevent_depossession & 4))
                {
                    mCurrentMotion = eSligMotions::Motion_37_Depossessing_4684D0;
                    field_128_timer = sGnFrame + 30;
                    SFX_Play_Mono(SoundEffect::PossessEffect_21, 0, 0);
                    return;
                }
            }
            else if (Input().IsAnyPressed(0x04 | 0x01))
            {
                if (Input().IsAnyHeld(0xF0))
                {
                    field_126_input = Input().Held();
                    mCurrentMotion = eSligMotions::Motion_18_GameSpeak_467B10;
                    return;
                }
            }
        }

        if (static_cast<s32>(sGnFrame) >= field_128_timer)
        {
            mCurrentMotion = eSligMotions::Motion_13_ReloadGun_4687B0;
        }
    }
}

void Slig::Motion_1_StandToWalk_4695D0()
{
    field_126_input |= Input().Held();

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eSligMotions::Motion_2_Walking_469130;
    }

    MoveOnLine();
}

void Slig::Motion_2_Walking_469130()
{
    if (gMap.GetDirection_444A40(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos)
            >= CameraPos::eCamCurrent_0
        && MusicController::GetAbmientAndMusicInfo(nullptr, nullptr, nullptr) <= MusicController::MusicTypes::eChase_4)
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
    }

    field_126_input |= Input().Held();

    if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), mBaseAnimatedWithPhysicsGameObject_VelX * FP_FromInteger(2)))
    {
        Motion_46_ToIdle_46A590();
        return;
    }

    MoveOnLine();

    if (mCurrentMotion == eSligMotions::Motion_2_Walking_469130)
    {
        FP v12 = {};
        switch (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame)
        {
            case 5:

                Slig_SoundEffect_46F310(SligSfx::eWalkingStep_2);
                if (!field_120_checked_if_off_screen)
                {
                    field_120_checked_if_off_screen = 1;
                    MapFollowMe_401D30(1);
                }
                if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
                {
                    if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                    {
                        mPreviousMotion = eSligMotions::Motion_4_Running_469690;
                        mBaseAliveGameObjectLastAnimFrame = 5;
                        field_11E_return_to_previous_motion = 1;

                        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            field_126_input = 0;
                            mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                            return;
                        }

                        mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                        field_126_input = 0;
                        return;
                    }
                    field_126_input = 0;
                    return;
                }
                break;
            case 11:

                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    v12 = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale));
                }
                else
                {
                    v12 = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale));
                }

                if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), v12 * FP_FromDouble(2.5)))
                {
                    mCurrentMotion = eSligMotions::Motion_19_WalkToStand_469610;
                }
                else if (sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
                {
                    if (mNextMotion == eSligMotions::Motion_6_Shoot_468820)
                    {
                        mCurrentMotion = eSligMotions::Motion_19_WalkToStand_469610;
                        field_128_timer = sGnFrame + 60;
                    }
                    else if (mNextMotion != -1)
                    {
                        mCurrentMotion = eSligMotions::Motion_19_WalkToStand_469610;
                    }
                }
                else
                {
                    if ((mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left_4C6594))
                        || (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right_4C6590))
                        || !(Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594)))
                    {
                        mCurrentMotion = eSligMotions::Motion_19_WalkToStand_469610;
                    }
                    field_126_input = 0;
                }
                break;
            case 14:

                Slig_SoundEffect_46F310(SligSfx::eWalkingStep_2);

                if (!field_120_checked_if_off_screen)
                {
                    field_120_checked_if_off_screen = 1;
                    MapFollowMe_401D30(1);
                }

                if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
                {
                    if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                    {
                        mPreviousMotion = 4;
                        mBaseAliveGameObjectLastAnimFrame = 13;
                        field_11E_return_to_previous_motion = 1;

                        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            field_126_input = 0;
                            mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                            return;
                        }

                        mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                        field_126_input = 0;
                        return;
                    }
                    field_126_input = 0;
                    return;
                }
                break;
            default:

                field_120_checked_if_off_screen = 0;
                break;
        }
    }
}

void Slig::Motion_3_StandToRun_469C00()
{
    field_126_input |= Input().Held();

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eSligMotions::Motion_4_Running_469690;
    }

    Event_Broadcast(kEventNoise, this);

    if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        ToKnockBack();
    }
    else
    {
        MoveOnLine();
    }
}

void Slig::Motion_4_Running_469690()
{
    if (gMap.GetDirection_444A40(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos)
            >= CameraPos::eCamCurrent_0
        && MusicController::GetAbmientAndMusicInfo(nullptr, nullptr, nullptr) != MusicController::MusicTypes::ePossessed_6)
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
    }

    field_126_input |= Input().Held();

    Event_Broadcast(kEventNoise, this);

    if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        ToKnockBack();
    }
    else
    {
        MoveOnLine();

        if (mCurrentMotion == eSligMotions::Motion_4_Running_469690)
        {
            if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 4 || mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 12)
            {
                Slig_SoundEffect_46F310(SligSfx::eRunningStep_3);

                if (field_120_checked_if_off_screen == 0)
                {
                    field_120_checked_if_off_screen = 1;
                    MapFollowMe_401D30(TRUE);
                }

                if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
                {
                    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 4)
                    {
                        PlayerControlRunningSlideStopOrTurnFrame4();
                    }
                    else
                    {
                        PlayerControlRunningSlideStopOrTurnFrame12();
                    }
                }
                else
                {
                    if (mNextMotion == eSligMotions::Motion_2_Walking_469130)
                    {
                        mCurrentMotion = eSligMotions::Motion_2_Walking_469130;
                        mNextMotion = -1;

                        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
                        }
                        else
                        {
                            mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
                        }
                    }
                    else if (mNextMotion == eSligMotions::Motion_6_Shoot_468820)
                    {
                        mCurrentMotion = eSligMotions::Motion_6_Shoot_468820;
                        mNextMotion = -1;
                        field_128_timer = sGnFrame + 60;
                    }
                    else if (mNextMotion != -1)
                    {
                        if (mBaseAnimatedWithPhysicsGameObject_VelX >= FP_FromInteger(0))
                        {
                            mBaseAnimatedWithPhysicsGameObject_VelX = (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromDouble(13.2));
                        }
                        else
                        {
                            mBaseAnimatedWithPhysicsGameObject_VelX = (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromDouble(-13.2));
                        }

                        mCurrentMotion = eSligMotions::Motion_9_SlidingToStand_469DF0;
                    }
                }
            }
            else
            {
                field_120_checked_if_off_screen = 0;
            }
        }
    }
}

void Slig::Motion_5_TurnAroundStanding_469C80()
{
    if (gMap.GetDirection_444A40(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos)
            >= CameraPos::eCamCurrent_0
        && MusicController::GetAbmientAndMusicInfo(nullptr, nullptr, nullptr) <= MusicController::MusicTypes::eChase_4)
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
    }

    Slig_SoundEffect_46F310(SligSfx::eStandingTurn_1);

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand();
        mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
    }
}

void Slig::Motion_6_Shoot_468820()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (sControlledCharacter_50767C == this && mHealth > FP_FromInteger(0))
        {
            if (Input().IsAnyPressed(sInputKey_ThrowItem_4C65B4))
            {
                const FP k35Scaled = mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35);
                const FP kGridSize = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
                const FP k8 = FP_FromInteger(8);

                // Recoil right
                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Right_4C6590))
                {
                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions->RayCast(
                            mBaseAnimatedWithPhysicsGameObject_XPos,
                            mBaseAnimatedWithPhysicsGameObject_YPos,
                            mBaseAnimatedWithPhysicsGameObject_XPos + (k8 * (kGridSize / k8)),
                            mBaseAnimatedWithPhysicsGameObject_YPos,
                            &pLine,
                            &hitX,
                            &hitY,
                            mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60)
                        || sCollisions->RayCast(
                            mBaseAnimatedWithPhysicsGameObject_XPos,
                            mBaseAnimatedWithPhysicsGameObject_YPos - k35Scaled,
                            mBaseAnimatedWithPhysicsGameObject_XPos + (k8 * (kGridSize / k8)),
                            mBaseAnimatedWithPhysicsGameObject_YPos - k35Scaled,
                            &pLine,
                            &hitX,
                            &hitY,
                            mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60))
                    {
                        return;
                    }
                    mBaseAnimatedWithPhysicsGameObject_VelX = (kGridSize / k8);
                    mCurrentMotion = eSligMotions::Motion_20_Recoil_468D30;
                    return;
                }

                // Recoil left
                if (!mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Left_4C6594))
                {
                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions->RayCast(
                            mBaseAnimatedWithPhysicsGameObject_XPos,
                            mBaseAnimatedWithPhysicsGameObject_YPos,
                            mBaseAnimatedWithPhysicsGameObject_XPos - (k8 * (kGridSize / k8)),
                            mBaseAnimatedWithPhysicsGameObject_YPos,
                            &pLine,
                            &hitX,
                            &hitY,
                            mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60)
                        || sCollisions->RayCast(
                            mBaseAnimatedWithPhysicsGameObject_XPos,
                            mBaseAnimatedWithPhysicsGameObject_YPos - k35Scaled,
                            mBaseAnimatedWithPhysicsGameObject_XPos - (k8 * (kGridSize / k8)),
                            mBaseAnimatedWithPhysicsGameObject_YPos - k35Scaled,
                            &pLine,
                            &hitX,
                            &hitY,
                            mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60))
                    {
                        return;
                    }
                    mBaseAnimatedWithPhysicsGameObject_VelX = -(kGridSize / k8);

                    mCurrentMotion = eSligMotions::Motion_20_Recoil_468D30;
                    return;
                }

                // General recoil
                // TODO: @ LABEL_27 is there a missing condition here, AE is checking
                // for the down key?
                if (field_128_timer > static_cast<s32>(sGnFrame))
                {
                    return;
                }

                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = (kGridSize / k8);
                }
                else
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = -(kGridSize / k8);
                }

                PathLine* pLine = nullptr;
                FP hitX = {};
                FP hitY = {};
                if (sCollisions->RayCast(
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos,
                        mBaseAnimatedWithPhysicsGameObject_XPos + (k8 * mBaseAnimatedWithPhysicsGameObject_VelX),
                        mBaseAnimatedWithPhysicsGameObject_YPos,
                        &pLine,
                        &hitX,
                        &hitY,
                        mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60)
                    || sCollisions->RayCast(
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos - k35Scaled,
                        mBaseAnimatedWithPhysicsGameObject_XPos + (k8 * mBaseAnimatedWithPhysicsGameObject_VelX),
                        mBaseAnimatedWithPhysicsGameObject_YPos - k35Scaled,
                        &pLine,
                        &hitX,
                        &hitY,
                        mBaseAnimatedWithPhysicsGameObject_SpriteScale != FP_FromDouble(0.5) ? 6 : 0x60))
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
                }
                else
                {
                    mCurrentMotion = eSligMotions::Motion_20_Recoil_468D30;
                }
                return;
            }
            else
            {
                SND_SEQ_PlaySeq_4775A0(SeqId::eHitBottomOfDeathPit_10, 1, 1);
                mCurrentMotion = eSligMotions::Motion_14_ShootToStand_468810;
                return;
            }
        }

        if (mNextMotion == eSligMotions::Motion_0_StandIdle_467640)
        {
            SND_SEQ_PlaySeq_4775A0(SeqId::eHitBottomOfDeathPit_10, 1, 1);
            mCurrentMotion = eSligMotions::Motion_14_ShootToStand_468810;
            mNextMotion = -1;
            return;
        }

        if (mNextMotion != -1 && mNextMotion != eSligMotions::Motion_6_Shoot_468820)
        {
            SND_SEQ_PlaySeq_4775A0(SeqId::eHitBottomOfDeathPit_10, 1, 1);
            mCurrentMotion = eSligMotions::Motion_14_ShootToStand_468810;
            return;
        }
    }
}

void Slig::Motion_7_Falling_46A1A0()
{
    if (mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0))
    {
        mBaseAnimatedWithPhysicsGameObject_VelX -= mBaseAnimatedWithPhysicsGameObject_SpriteScale * field_12C_falling_velx_scale_factor;
        if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0))
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
        }
    }
    else if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0))
    {
        mBaseAnimatedWithPhysicsGameObject_VelX += mBaseAnimatedWithPhysicsGameObject_SpriteScale * field_12C_falling_velx_scale_factor;
        if (mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0))
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
        }
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    const s16 bHit = InAirCollision_4019C0(&pLine, &hitX, &hitY, FP_FromDouble(1.8));
    SetActiveCameraDelayedFromDir_401C90();
    if (bHit)
    {
        switch (pLine->field_8_type)
        {
            case 0:
            case 4:
            case 32:
            case 36:
            {
                ToStand();

                BaseAliveGameObjectCollisionLine = pLine;

                PSX_RECT bRect = VGetBoundingRect();
                bRect.y += 5;
                bRect.h += 5;

                VOnCollisionWith(
                    {bRect.x, bRect.y},
                    {bRect.w, bRect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);

                mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                mCurrentMotion = eSligMotions::Motion_41_LandingSoft_46A390;
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                MapFollowMe_401D30(TRUE);
                break;
            }

            case 1:
            case 2:
            case 5:
            case 6:
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                ToKnockBack();
                break;

            default:
                break;
        }
    }
}

// uses slig idle anim
void Slig::Motion_8_Unknown_4673E0()
{
    if (sNumCamSwappers_507668 <= 0)
    {
        if (sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
        {
            mCurrentMotion = mPreviousMotion;
            if (mLiftPoint)
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger((BaseAliveGameObjectCollisionLine->field_0_rect.x + BaseAliveGameObjectCollisionLine->field_0_rect.w) / 2);
                mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(BaseAliveGameObjectCollisionLine->field_0_rect.y);
            }
        }
        else
        {
            mCurrentMotion = mPreviousMotion;
            if (mLiftPoint)
            {
                static_cast<LiftPoint*>(mLiftPoint)->field_12C_bMoving |= 1u;
            }
        }

        mBaseAnimatedWithPhysicsGameObject_LvlNumber = gMap.mCurrentLevel;
        mBaseAnimatedWithPhysicsGameObject_PathNumber = gMap.mCurrentPath;
    }
}

void Slig::Motion_9_SlidingToStand_469DF0()
{
    Event_Broadcast(kEventNoise, this);

    if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        ToKnockBack();
    }
    else
    {
        SlowDown(FP_FromDouble(2.125));
        if (mCurrentMotion == eSligMotions::Motion_9_SlidingToStand_469DF0)
        {
            if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame >= 6 || sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
            {
                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
                {
                    Environment_SFX_42A220(EnvironmentSfx::eSlideStop_0, 0, 0x7FFF, this);
                    MapFollowMe_401D30(1);
                    MainMovement_467020();
                }
            }
            else if ((mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Right_4C6590))
                     || (!(mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX)) && Input().IsAnyPressed(sInputKey_Left_4C6594)))
            {
                mPreviousMotion = eSligMotions::Motion_10_SlidingTurn_469F10;
                mBaseAliveGameObjectLastAnimFrame = mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame;
                field_11E_return_to_previous_motion = 1;
            }
        }
    }
}

void Slig::Motion_10_SlidingTurn_469F10()
{
    Event_Broadcast(kEventNoise, this);
    if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        ToKnockBack();
        return;
    }

    SlowDown(FP_FromDouble(2.125));

    if (mCurrentMotion == eSligMotions::Motion_10_SlidingTurn_469F10 && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);

        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
            {
                if (mNextMotion == 4)
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                    mCurrentMotion = eSligMotions::Motion_12_SlidingTurnToRun_46A160;
                    return;
                }
            }
            else
            {
                if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                {
                    mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                    mCurrentMotion = eSligMotions::Motion_12_SlidingTurnToRun_46A160;
                    return;
                }
            }
            mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
            mCurrentMotion = eSligMotions::Motion_11_SlidingTurnToWalk_46A120;
        }
        else
        {
            if (sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
            {
                if (mNextMotion == 4)
                {
                    mCurrentMotion = eSligMotions::Motion_12_SlidingTurnToRun_46A160;
                    mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                    return;
                }
            }
            else
            {
                if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                {
                    mCurrentMotion = eSligMotions::Motion_12_SlidingTurnToRun_46A160;
                    mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(4));
                    return;
                }
            }
            mCurrentMotion = eSligMotions::Motion_11_SlidingTurnToWalk_46A120;
            mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(9));
        }
    }
}

void Slig::Motion_11_SlidingTurnToWalk_46A120()
{
    Event_Broadcast(kEventNoise, this);
    MoveOnLine();

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
        mCurrentMotion = eSligMotions::Motion_2_Walking_469130;
    }
}

void Slig::Motion_12_SlidingTurnToRun_46A160()
{
    Event_Broadcast(kEventNoise, this);
    MoveOnLine();

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
        mCurrentMotion = eSligMotions::Motion_4_Running_469690;
    }
}

void Slig::Motion_13_ReloadGun_4687B0()
{
    Motion_46_ToIdle_46A590();
}

void Slig::Motion_14_ShootToStand_468810()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MainMovement_467020();
    }
}

void Slig::Motion_15_SteppingToStand_469080()
{
    if (!mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame)
    {
        Slig_SoundEffect_46F310(SligSfx::eWalkingStep_2);
    }

    if (WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), mBaseAnimatedWithPhysicsGameObject_VelX))
    {
        ToKnockBack();
    }
    else
    {
        MoveOnLine();
        if (mCurrentMotion == eSligMotions::Motion_15_SteppingToStand_469080)
        {
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_401D30(1);
                Motion_46_ToIdle_46A590();
            }
        }
    }
}

void Slig::Motion_16_StandingToStep_468FD0()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (Input().IsAnyPressed(sInputKey_Left_4C6594 | sInputKey_Right_4C6590))
        {
            mCurrentMotion = eSligMotions::Motion_1_StandToWalk_4695D0;
        }
        else if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mCurrentMotion = eSligMotions::Motion_15_SteppingToStand_469080;
            mBaseAnimatedWithPhysicsGameObject_VelX = -(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(6));
        }
        else
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) / FP_FromInteger(6));
            mCurrentMotion = eSligMotions::Motion_15_SteppingToStand_469080;
        }
    }
}

void Slig::Motion_17_DepossessingAbort_468750()
{
    Motion_46_ToIdle_46A590();
}

void Slig::Motion_18_GameSpeak_467B10()
{
    field_126_input |= Input().Held();

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = GetNextMotionIncGameSpeak_467700(field_126_input);
        if (mCurrentMotion == -1)
        {
            ToStand();
        }
        else
        {
            Event_Broadcast(kEventSpeaking, this);
        }
        field_126_input = 0;
    }
}

void Slig::Motion_19_WalkToStand_469610()
{
    MoveOnLine();

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);
        if (!MainMovement_467020())
        {
            Motion_46_ToIdle_46A590();
        }
    }
}

void Slig::Motion_20_Recoil_468D30()
{
    MoveOnLine();

    if (mCurrentMotion == eSligMotions::Motion_20_Recoil_468D30)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe_401D30(TRUE);

            if (sControlledCharacter_50767C != this || mHealth <= FP_FromInteger(0))
            {
                if (mNextMotion != -1)
                {
                    SND_SEQ_PlaySeq_4775A0(SeqId::eHitBottomOfDeathPit_10, 1, 1);
                    mCurrentMotion = eSligMotions::Motion_14_ShootToStand_468810;
                    mNextMotion = -1;
                }
            }
            else if (Input().IsAnyPressed(sInputKey_ThrowItem_4C65B4))
            {
                mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
                mPreviousMotion = eSligMotions::Motion_6_Shoot_468820;
                field_128_timer = sGnFrame + 60;
                mBaseAliveGameObjectLastAnimFrame = 2;
                field_11E_return_to_previous_motion = 1;
            }
            else
            {
                SND_SEQ_PlaySeq_4775A0(SeqId::eHitBottomOfDeathPit_10, 1, 1);
                mCurrentMotion = eSligMotions::Motion_14_ShootToStand_468810;
            }
        }
    }
    else if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
    {
        SFX_Play_Mono(SoundEffect::SligShoot_6, 85, 0);
    }
    else
    {
        SFX_Play_Mono(SoundEffect::SligShoot_6, 0, 0);
    }
}

void Slig::Motion_21_SpeakHereBoy_467BD0()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_22_SpeakHi_467C90()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_23_SpeakFreeze_467D50()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_24_SpeakGetHim_467E10()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_25_SpeakLaugh_467ED0()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_26_SpeakBullshit1_467F90()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_27_SpeakLookOut_468050()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_28_SpeakBullshit2_468110()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_29_SpeakPanic_4681D0()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_30_SpeakWhat_468290()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_31_SpeakAIFreeze_468350()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_32_Blurgh_468410()
{
    Motion_18_GameSpeak_467B10();
}

void Slig::Motion_33_Sleeping_46A410()
{
    if (mNextMotion == eSligMotions::Motion_34_SleepingToStand_46A5F0)
    {
        mCurrentMotion = eSligMotions::Motion_34_SleepingToStand_46A5F0;
        mNextMotion = -1;
        return;
    }

    if (sGnFrame % 60)
    {
        if (!((sGnFrame - 20) % 60))
        {
            Slig_SoundEffect_46F310(SligSfx::eSnooze2_5);

            if (gMap.Is_Point_In_Current_Camera_4449C0(
                    mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                    mBaseAnimatedWithPhysicsGameObject_PathNumber,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    0))
            {
                relive_new SnoozeParticle(
                    mBaseAnimatedWithPhysicsGameObject_XPos
                        + ((mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? FP_FromInteger(20) : FP_FromInteger(-20)),
                    mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(10),
                    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer,
                    mBaseAnimatedWithPhysicsGameObject_Anim.field_14_scale);
                return;
            }
        }
    }
    else
    {
        Slig_SoundEffect_46F310(SligSfx::eSnooze1_4);

        if (gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0))
        {
            relive_new SnoozeParticle(
                mBaseAnimatedWithPhysicsGameObject_XPos
                    + ((mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? FP_FromInteger(20) : FP_FromInteger(-20)),
                mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(10),
                mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer,
                mBaseAnimatedWithPhysicsGameObject_Anim.field_14_scale);
            return;
        }
    }
}

void Slig::Motion_34_SleepingToStand_46A5F0()
{
    // OWI hack - kill all particles, even if they're not ours!
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        auto pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectTypeId == ReliveTypes::eSnoozParticle)
        {
            static_cast<SnoozeParticle*>(pObj)->field_1D4_state = SnoozeParticle::SnoozeParticleState::eBlowingUp_2;
        }
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame >= 2 && mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame <= 10)
    {
        Slig_SoundEffect_46F310(SligSfx::eToStand_0);
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 9)
    {
        Slig_SoundEffect_46F310(SligSfx::eWalkingStep_2);
    }

    switch (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame)
    {
        case 9:
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos -= (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(7));
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(7));
            }
            break;

        case 10:
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos -= (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(12));
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(12));
            }
            break;

        case 11:
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos -= (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(6));
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(6));
            }
            break;

        default:
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
                MainMovement_467020();
            }
            break;
    }
}

void Slig::Motion_35_Knockback_46A720()
{
    if (BaseAliveGameObjectCollisionLine)
    {
        SlowDown(FP_FromDouble(0.39));
    }
    else
    {
        Motion_7_Falling_46A1A0();

        if (mCurrentMotion == eSligMotions::Motion_41_LandingSoft_46A390)
        {
            mCurrentMotion = eSligMotions::Motion_35_Knockback_46A720;
            field_128_timer = sGnFrame + 10;
        }
    }

    Event_Broadcast(kEventNoise, this);

    if ((gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarms
         || gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn
         || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom)
        && mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 4)
    {
        Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);

            if (mHealth > FP_FromInteger(0) && field_128_timer <= static_cast<s32>(sGnFrame) && sActiveHero_507678->mHealth > FP_FromInteger(0))
            {
                mCurrentMotion = eSligMotions::Motion_36_KnockbackToStand_46A7F0;
            }
        }
    }
}

void Slig::Motion_36_KnockbackToStand_46A7F0()
{
    Event_Broadcast(kEventNoise, this);

    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame >= 2 && mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame <= 10)
    {
        Slig_SoundEffect_46F310(SligSfx::eToStand_0);
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 9)
    {
        Slig_SoundEffect_46F310(SligSfx::eWalkingStep_2);
    }

    FP gridSize = {};
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        gridSize = -ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
    }
    else
    {
        gridSize = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
    }

    if (!WallHit_401930(mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(35), gridSize))
    {
        switch (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame)
        {
            case 9:
                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(-3);
                }
                else
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(3);
                }
                break;

            case 10:
                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(-13);
                }
                else
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos += (mBaseAnimatedWithPhysicsGameObject_SpriteScale * mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(13);
                }

                break;

            case 11:
                if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos += ((mBaseAnimatedWithPhysicsGameObject_SpriteScale * mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(-9));
                }
                else
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos += ((mBaseAnimatedWithPhysicsGameObject_SpriteScale * mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(9));
                }
                break;

            default:
                break;
        }
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand();
    }
}

void Slig::Motion_37_Depossessing_4684D0()
{
    if (sControlledCharacter_50767C == this)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (!Input_IsChanting())
            {
                mCurrentMotion = eSligMotions::Motion_17_DepossessingAbort_468750;
            }
        }

        if (!(sGnFrame % 4))
        {
            New_Chant_Particle_4198E0(
                mBaseAnimatedWithPhysicsGameObject_XPos + (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(Math_RandomRange_450F20(-20, 20))),
                mBaseAnimatedWithPhysicsGameObject_YPos - (mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(Math_RandomRange_450F20(20, 50))),
                mBaseAnimatedWithPhysicsGameObject_SpriteScale,
                Layer::eLayer_0);
        }

        if (static_cast<s32>(sGnFrame) > field_128_timer)
        {
            BlowToGibs_4685A0();
        }
    }
}

void Slig::Motion_38_Possess_46B050()
{
    if (!BaseAliveGameObjectCollisionLine)
    {
        Motion_7_Falling_46A1A0();
        if (mCurrentMotion != eSligMotions::Motion_38_Possess_46B050)
        {
            mCurrentMotion = eSligMotions::Motion_38_Possess_46B050;
        }
    }

    if (static_cast<s32>(sGnFrame) >= field_158_explode_timer)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
        {
            FP xOff = (FP_FromInteger(20) * mBaseAnimatedWithPhysicsGameObject_SpriteScale);
            if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0))
            {
                xOff = -xOff;
            }

            relive_new Gibs(
                GibType::Slig_1,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                xOff,
                FP_FromInteger(0),
                mBaseAnimatedWithPhysicsGameObject_SpriteScale);

            New_Smoke_Particles_419A80(
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos - (FP_FromInteger(30) * mBaseAnimatedWithPhysicsGameObject_SpriteScale),
                mBaseAnimatedWithPhysicsGameObject_SpriteScale,
                3,
                0);

            if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
            {
                SFX_Play_Mono(SoundEffect::KillEffect_78, 80);
                SFX_Play_Mono(SoundEffect::FallingItemHit_53, 60);
            }
            else
            {
                SFX_Play_Mono(SoundEffect::KillEffect_78, 127);
                SFX_Play_Mono(SoundEffect::FallingItemHit_53, 90);
            }

            mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
            mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
            mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
            mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
            mHealth = FP_FromInteger(0);
            MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
            mBaseGameObjectUpdateDelay = 40;
            field_114_timer = sGnFrame + 60;
            SetBrain(&Slig::Brain_Death_46C3A0);
        }
    }

    if (static_cast<s32>(sGnFrame) > field_154_death_by_being_shot_timer)
    {
        if (mBaseAnimatedWithPhysicsGameObject_VelX >= FP_FromInteger(0))
        {
            if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mCurrentMotion = eSligMotions::Motion_35_Knockback_46A720;
                return;
            }
        }
        else if (!mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mCurrentMotion = eSligMotions::Motion_35_Knockback_46A720;
            return;
        }
        mCurrentMotion = eSligMotions::Motion_45_Smash_46A990;
    }
}

void Slig::Motion_39_OutToFall_46A9E0()
{
    Motion_7_Falling_46A1A0();

    const FP fallDepth = mBaseAnimatedWithPhysicsGameObject_YPos - BaseAliveGameObjectLastLineYPos;
    if (fallDepth > FP_FromInteger(16 * 640))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if (mCurrentMotion == eSligMotions::Motion_41_LandingSoft_46A390)
    {
        if (fallDepth > FP_FromInteger(240))
        {
            BaseAliveGameObjectLastLineYPos += FP_FromInteger(240);
        }

        if (mBaseAnimatedWithPhysicsGameObject_YPos - BaseAliveGameObjectLastLineYPos > FP_FromInteger(180))
        {
            mCurrentMotion = eSligMotions::Motion_42_LandingFatal_46AFE0;
            field_128_timer = sGnFrame + 30;
            mHealth = FP_FromInteger(0);
            Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
        }
    }
}

void Slig::Motion_40_FallingInitiate_46AA60()
{
    Event_Broadcast(kEventNoise, this);

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eSligMotions::Motion_39_OutToFall_46A9E0;
    }

    Motion_7_Falling_46A1A0();
}

void Slig::Motion_41_LandingSoft_46A390()
{
    if (!mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame)
    {
        Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, 0);
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Motion_46_ToIdle_46A590();
    }
}

void Slig::Motion_42_LandingFatal_46AFE0()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 0)
    {
        SND_SEQ_Play_477760(SeqId::eHitBottomOfDeathPit_10, 1, 65, 65);
        SFX_Play_Mono(SoundEffect::KillEffect_78, 80);
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (static_cast<s32>(sGnFrame) >= field_128_timer && !BrainIs(&Slig::Brain_Death_46C3A0))
        {
            mHealth = FP_FromInteger(0);
            field_114_timer = sGnFrame + 60;
            SetBrain(&Slig::Brain_Death_46C3A0);
        }
    }
}

void Slig::Motion_43_ShootZ_468E30()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (mNextMotion != -1)
        {
            SND_SEQ_PlaySeq_4775A0(SeqId::eHitBottomOfDeathPit_10, 1, 1);
            mCurrentMotion = eSligMotions::Motion_44_ShootZtoStand_468F70;
            mNextMotion = -1;
        }
    }
    else if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 7)
    {
        relive_new Bullet(
            this,
            BulletType::eZBullet_2,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(12),
            FP_FromInteger(640),
            0,
            mBaseAnimatedWithPhysicsGameObject_SpriteScale,
            field_174_tlv.field_2A_num_times_to_shoot - field_200_num_times_to_shoot - 1);

        New_ShootingZFire_Particle_419810(
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(12),
            mBaseAnimatedWithPhysicsGameObject_SpriteScale);

        if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
        {
            SFX_Play_Mono(SoundEffect::SligShoot_6, 85, 0);
        }
        else
        {
            SFX_Play_Mono(SoundEffect::SligShoot_6, 0, 0);
        }

        // The doves don't like bullets
        Dove::All_FlyAway();

        Event_Broadcast(kEventShooting, this);
        Event_Broadcast(kEventLoudNoise, this);
    }
}

void Slig::Motion_44_ShootZtoStand_468F70()
{
    Motion_46_ToIdle_46A590();
}

void Slig::Motion_45_Smash_46A990()
{
    if (BaseAliveGameObjectCollisionLine)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 4)
        {
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
        }
    }
    else
    {
        Motion_7_Falling_46A1A0();

        if (mCurrentMotion != eSligMotions::Motion_45_Smash_46A990)
        {
            mCurrentMotion = eSligMotions::Motion_45_Smash_46A990;
        }
    }
}

void Slig::Motion_46_ToIdle_46A590()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand();
    }
}

void Slig::Motion_47_LiftUp_4665A0()
{
    mCurrentMotion = MoveLift_4665E0(FP_FromInteger(-4));
}

void Slig::Motion_48_LiftDown_4665C0()
{
    mCurrentMotion = MoveLift_4665E0(FP_FromInteger(4));
}

void Slig::Motion_49_LiftGrip_4663A0()
{
    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);

    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);
    mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            if (pLiftPoint->OnTopFloor())
            {
                mCurrentMotion = eSligMotions::Motion_51_LiftGripping_466480;
            }
            else
            {
                mCurrentMotion = eSligMotions::Motion_47_LiftUp_4665A0;
            }
            return;
        }

        if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            if (pLiftPoint->OnBottomFloor())
            {
                mCurrentMotion = eSligMotions::Motion_51_LiftGripping_466480;
            }
            else
            {
                mCurrentMotion = eSligMotions::Motion_48_LiftDown_4665C0;
            }
            return;
        }

        mCurrentMotion = eSligMotions::Motion_51_LiftGripping_466480;
    }
}

void Slig::Motion_50_LiftUngrip_466460()
{
    mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToStand();
    }
}

void Slig::Motion_51_LiftGripping_466480()
{
    CheckPlatformVanished();

    auto pLift = static_cast<LiftPoint*>(mLiftPoint);

    pLift->Move(FP_FromInteger(0), FP_FromInteger(0), 0);
    mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);

    if (Input().IsAnyPressed(sInputKey_Up_4C6598))
    {
        if (!pLift->OnTopFloor())
        {
            mCurrentMotion = eSligMotions::Motion_47_LiftUp_4665A0;
        }
    }
    else
    {
        if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            if (!pLift->OnBottomFloor())
            {
                mCurrentMotion = eSligMotions::Motion_48_LiftDown_4665C0;
            }
        }
        else if (pLift->OnAnyFloor())
        {
            mCurrentMotion = eSligMotions::Motion_50_LiftUngrip_466460;
        }
    }
}

void Slig::Motion_52_Beat_46AA90()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 5)
    {
        SFX_Play_Pitch(SoundEffect::AirStream_28, 90, -300);
    }
    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 8)
    {
        const FP kGridSize = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
        const FP k2Scaled = FP_FromInteger(2) * kGridSize;

        PSX_RECT hitRect = {};
        hitRect = MakeMinMaxRect(
            mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) ? mBaseAnimatedWithPhysicsGameObject_XPos - kGridSize : mBaseAnimatedWithPhysicsGameObject_XPos + kGridSize,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos - k2Scaled);

        for (s32 idx = 0; idx < gBaseAliveGameObjects_4FC8A0->Size(); idx++)
        {
            auto pObjIter = gBaseAliveGameObjects_4FC8A0->ItemAt(idx);

            if (!pObjIter)
            {
                break;
            }
            if (pObjIter != this && pObjIter->mBaseGameObjectTypeId == ReliveTypes::eMudokon)
            {
                const PSX_RECT bRect = pObjIter->VGetBoundingRect();

                if (pObjIter->mHealth > FP_FromInteger(0)
                    && PSX_Rects_overlap_no_adjustment(&hitRect, &bRect))
                {
                    pObjIter->VTakeDamage(this);
                    Event_Broadcast(kEventNoise, this);
                    SFX_Play_Mono(SoundEffect::FallingItemHit_53, 60);
                    return;
                }
            }
        }
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
    }
}

s16 Slig::Brain_SpottedEnemy_465EB0()
{
    if (gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0)
        || field_174_tlv.field_32_chase_abe == Choice_short::eNo_0)
    {
        if (VOnSameYLevel(sControlledCharacter_50767C)
            && VIsObj_GettingNear_On_X(sControlledCharacter_50767C)
            && VIsObjNearby(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(3), sControlledCharacter_50767C) && !Event_Get(kEventResetting))
        {
            ToShoot_46F1D0();
        }
        else if (VOnSameYLevel(sControlledCharacter_50767C)
                 && Event_Get(kEventAbeOhm)
                 && VIsFacingMe(sControlledCharacter_50767C))
        {
            ToShoot_46F1D0();
        }
        else if (field_114_timer > static_cast<s32>(sGnFrame))
        {
            if (sActiveHero_507678->mHealth > FP_FromInteger(0))
            {
                ShouldStilBeAlive_46C0D0();
            }
            else
            {
                ToAbeDead_466270();
            }
        }
        else
        {
            if (VIsFacingMe(sControlledCharacter_50767C))
            {
                ToShoot_46F1D0();
            }
            else
            {
                ToTurn_46DE70();
            }
        }
    }
    else
    {
        ToChase_46D080();
    }
    return 302;
}

enum Brain_Paused
{
    eSearchGameEnderController_0 = 0,
    eSayFreezeOrTurnAround_1 = 1,
    eWaitForTurnAround_2 = 2,
    eStartRunning_3 = 3,
    eSetDead_4 = 4
};

s16 Slig::Brain_Paused_466030()
{
    if (Event_Get(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(Options::eDead);
    }

    switch (field_10E_brain_sub_state)
    {
        case Brain_Paused::eSearchGameEnderController_0:
            break;

        case Brain_Paused::eSayFreezeOrTurnAround_1:
            if (VIsFacingMe(sActiveHero_507678))
            {
                if (mCurrentMotion != eSligMotions::Motion_0_StandIdle_467640)
                {
                    return field_10E_brain_sub_state;
                }
                mNextMotion = eSligMotions::Motion_31_SpeakAIFreeze_468350;
                return Brain_Paused::eStartRunning_3;
            }
            else
            {
                mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
                return Brain_Paused::eWaitForTurnAround_2;
            }
            break;

        case Brain_Paused::eWaitForTurnAround_2:
            if (mCurrentMotion != eSligMotions::Motion_5_TurnAroundStanding_469C80
                || !mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                return field_10E_brain_sub_state;
            }
            return Brain_Paused::eSayFreezeOrTurnAround_1;

        case Brain_Paused::eStartRunning_3:
            if (mCurrentMotion != eSligMotions::Motion_31_SpeakAIFreeze_468350
                || !mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                return field_10E_brain_sub_state;
            }
            mNextMotion = eSligMotions::Motion_4_Running_469690;
            return Brain_Paused::eSetDead_4;

        case Brain_Paused::eSetDead_4:
            if (!gMap.Is_Point_In_Current_Camera_4449C0(
                    mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                    mBaseAnimatedWithPhysicsGameObject_PathNumber,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    0))
            {
                mBaseGameObjectFlags.Set(Options::eDead);
            }
            return field_10E_brain_sub_state;

        default:
            return field_10E_brain_sub_state;
    }

    bool found = false;
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObjIter = gBaseGameObjects->ItemAt(i);
        if (!pObjIter)
        {
            break;
        }

        if (pObjIter->mBaseGameObjectTypeId == ReliveTypes::eGameEnderController)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        GameEnderController::CreateGameEnderController();
    }

    mCurrentMotion = eSligMotions::Motion_7_Falling_46A1A0;
    mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
    return Brain_Paused::eSayFreezeOrTurnAround_1;
}

s16 Slig::Brain_EnemyDead_466190()
{
    if (Event_Get(kEventDeathReset)
        && !gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        return 113;
    }

    if (field_114_timer >= static_cast<s32>(sGnFrame))
    {
        ShouldStilBeAlive_46C0D0();
    }
    else
    {
        const auto rnd = Math_NextRandom();

        // Say this often
        if (rnd < 25u)
        {
            mNextMotion = eSligMotions::Motion_26_SpeakBullshit1_467F90;
            field_114_timer = sGnFrame + 15;
            return 113;
        }

        // Say this less often
        if (rnd < 50u)
        {
            mNextMotion = eSligMotions::Motion_28_SpeakBullshit2_468110;
            field_114_timer = sGnFrame + 15;
            return 113;
        }

        // And turn even less often
        if (sActiveHero_507678->mHealth > FP_FromInteger(0))
        {
            TurnOrWalk_46D5B0(0);
            return 113;
        }
    }
    return 113;
}

s16 Slig::Brain_KilledEnemy_4662A0()
{
    if (field_114_timer > static_cast<s32>(sGnFrame))
    {
        ShouldStilBeAlive_46C0D0();
    }
    else
    {
        mNextMotion = eSligMotions::Motion_25_SpeakLaugh_467ED0;
        field_114_timer = sGnFrame + 45;
        SetBrain(&Slig::Brain_EnemyDead_466190);
    }
    return 114;
}

s16 Slig::Brain_Unknown_46B250()
{
    if (!VOnSameYLevel(sControlledCharacter_50767C)
        || !VIsFacingMe(sControlledCharacter_50767C)
        || IsInInvisibleZone_418870(sControlledCharacter_50767C)
        || IsWallBetween_46BE60(this, sControlledCharacter_50767C)
        || !gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0)
        || (field_20E_spotted_possessed_slig
            && sControlledCharacter_50767C->mBaseGameObjectTypeId == ReliveTypes::eSlig)
        || Event_Get(kEventResetting))
    {
        if (!VOnSameYLevel(
                sControlledCharacter_50767C)
            || !VIsFacingMe(sControlledCharacter_50767C)
            || IsInInvisibleZone_418870(sControlledCharacter_50767C)
            || IsWallBetween_46BE60(this, sControlledCharacter_50767C)
            || !gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)
            || Event_Get(kEventResetting))
        {
            if (sActiveHero_507678->mHealth > FP_FromInteger(0))
            {
                BaseAliveGameObject* pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSuspiciousNoise));
                if (!pEvent)
                {
                    pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSpeaking));
                }

                if (pEvent && pEvent->mBaseAnimatedWithPhysicsGameObject_SpriteScale == mBaseAnimatedWithPhysicsGameObject_SpriteScale && pEvent != this && field_114_timer <= static_cast<s32>(sGnFrame) && !Event_Get(kEventResetting))
                {
                    ToTurn_46DE70();
                }
                else if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_SpriteScale <= mBaseAnimatedWithPhysicsGameObject_SpriteScale
                         || (sControlledCharacter_50767C != sActiveHero_507678
                             && sControlledCharacter_50767C != gElum_507680)
                         || !VIsFacingMe(sControlledCharacter_50767C)
                         || IsInInvisibleZone_418870(sControlledCharacter_50767C)
                         || !gMap.Is_Point_In_Current_Camera_4449C0(
                             mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                             mBaseAnimatedWithPhysicsGameObject_PathNumber,
                             mBaseAnimatedWithPhysicsGameObject_XPos,
                             mBaseAnimatedWithPhysicsGameObject_YPos,
                             0)
                         || IsInZCover_46BDA0(sControlledCharacter_50767C)
                         || IsInZCover_46BDA0(this)
                         || Event_Get(kEventResetting))
                {
                    ShouldStilBeAlive_46C0D0();
                }
                else
                {
                    ToZShoot_46F200();
                }
            }
            else
            {
                ToAbeDead_466270();
            }
        }
        else
        {
            ToShoot_46F1D0();
        }
    }
    else
    {
        RespondToEnemyOrPatrol_465DF0();
    }
    return 101;
}

void Slig::WakeUp()
{
    mNextMotion = eSligMotions::Motion_34_SleepingToStand_46A5F0;
    SetBrain(&Slig::Brain_WakingUp_46B700);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eChase_4, this, 0, 0);
    auto pTlv = static_cast<Path_Slig*>(gMap.TLV_Get_At_446260(
        field_174_tlv.field_10_top_left.field_0_x,
        field_174_tlv.field_10_top_left.field_2_y,
        field_174_tlv.field_10_top_left.field_0_x,
        field_174_tlv.field_10_top_left.field_2_y,
        TlvTypes::Slig_24));
    if (pTlv)
    {
        pTlv->field_1_unknown = 1;
    }
}

void Start_Slig_Sounds_Helper(Sound_Ambiance_Array array, CameraPos camPos, u8 ambianceId)
{
    if (!array.mArray[ambianceId].field_8_pScopedSeq)
    {
        array.mArray[ambianceId].field_8_pScopedSeq = relive_new ScopedSeq(ambianceId, camPos);
    }
}

s16 Slig::Brain_Sleeping_46B4E0()
{
    const auto pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventNoise));
    if (pEvent)
    {
        if (pEvent->mBaseAnimatedWithPhysicsGameObject_SpriteScale == mBaseAnimatedWithPhysicsGameObject_SpriteScale)
        {
            const auto kScaleGrid = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
            const auto wake_up_dist_scaled = kScaleGrid * FP_FromInteger(field_174_tlv.field_52_noise_wake_up_distance);
            if (VIsObjNearby(wake_up_dist_scaled, pEvent) && field_114_timer <= static_cast<s32>(sGnFrame) && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) && !Event_Get(kEventResetting))
            {
                WakeUp();
                return 102;
            }
        }
    }

    if (Event_Get(kEventSpeaking) || Event_Get(kEventAlarm) || Event_Get(kEventLoudNoise))
    {
        if (pEvent != this && field_114_timer <= static_cast<s32>(sGnFrame) && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) && !Event_Get(kEventResetting))
        {
            WakeUp();
            return 102;
        }
    }

    if (SwitchStates_Get(120) && field_114_timer <= static_cast<s32>(sGnFrame) && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) && !Event_Get(kEventResetting))
    {
        LOG_WARNING("if this is a custom level consider changing all switch id's with the value 120"
                    " to something else. sleeping sligs will always wake up if this switch id is set.");
        WakeUp();
        return 102;
    }

    ShouldStilBeAlive_46C0D0();

    if (mBaseGameObjectFlags.Get(Options::eDead))
    {
        Start_Slig_sounds(gMap.GetDirection_444A40(
                                     mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                                     mBaseAnimatedWithPhysicsGameObject_PathNumber,
                                     mBaseAnimatedWithPhysicsGameObject_XPos,
                                     mBaseAnimatedWithPhysicsGameObject_YPos),
                                 0);
    }
    return 102;
}

s16 Slig::Brain_WakingUp_46B700()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        WaitOrWalk_46E440();
    }
    return 0;
}

s16 Slig::Brain_Inactive_46B780()
{
    if (field_114_timer > static_cast<s32>(sGnFrame))
    {
        if (sActiveHero_507678->mHealth > FP_FromInteger(0))
        {
            if (!VOnSameYLevel(sControlledCharacter_50767C)
                || !VIsFacingMe(sControlledCharacter_50767C)
                || !VIsObjNearby(ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(1), sControlledCharacter_50767C)
                || IsInInvisibleZone_418870(sControlledCharacter_50767C)
                || IsWallBetween_46BE60(this, sControlledCharacter_50767C)
                || Event_Get(kEventResetting))
            {
                ShouldStilBeAlive_46C0D0();
            }
            else
            {
                ToShoot_46F1D0();
            }
        }
        else
        {
            ToAbeDead_466270();
        }
    }
    else
    {
        WaitOrWalk_46E440();
    }
    return 103;
}

s16 Slig::Brain_Possessed_46C190()
{
    switch (field_10E_brain_sub_state)
    {
        case Brain_Possessed::eStartPossession_0:
            Slig_GameSpeak_SFX_46F560(SligSpeak::eHelp_10, 0, field_110_pitch_min, this);
            field_10E_brain_sub_state = Brain_Possessed::ePossessionShaking_1;
            mHealth = FP_FromInteger(0);
            mCurrentMotion = eSligMotions::Motion_38_Possess_46B050;
            field_114_timer = sGnFrame + 30;
            field_158_explode_timer = sGnFrame + 1000;
            field_154_death_by_being_shot_timer = sGnFrame + 1000;
            return field_10E_brain_sub_state;

        case Brain_Possessed::ePossessionShaking_1:
            if (static_cast<s32>(sGnFrame) >= field_114_timer)
            {
                field_10E_brain_sub_state = Brain_Possessed::ePossessionInactive_2;
                field_114_timer = sGnFrame + 20;
                mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
                return field_10E_brain_sub_state;
            }
            break;

        case Brain_Possessed::ePossessionInactive_2:
            if (static_cast<s32>(sGnFrame) >= field_114_timer)
            {
                if (Math_NextRandom() & 1)
                {
                    field_114_timer = sGnFrame + 20;
                    mCurrentMotion = eSligMotions::Motion_22_SpeakHi_467C90;
                    Slig_GameSpeak_SFX_46F560(SligSpeak::eHi_0, 0, field_110_pitch_min, this);
                }
                else
                {
                    field_114_timer = sGnFrame + 20;
                    mCurrentMotion = eSligMotions::Motion_25_SpeakLaugh_467ED0;
                    Slig_GameSpeak_SFX_46F560(SligSpeak::eLaugh_7, 0, field_110_pitch_min, this);
                }
                field_10E_brain_sub_state = Brain_Possessed::ePossessionSpeak_3;
                return field_10E_brain_sub_state;
            }
            break;

        case Brain_Possessed::ePossessionSpeak_3:
            if (Event_Get(kEventDeathReset))
            {
                if (sControlledCharacter_50767C != this)
                {
                    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                }
            }

            if (static_cast<s32>(sGnFrame) >= field_114_timer)
            {
                field_10E_brain_sub_state = Brain_Possessed::eControlledByPlayer_4;
                mHealth = FP_FromInteger(1);
                return field_10E_brain_sub_state;
            }
            break;

        case Brain_Possessed::eControlledByPlayer_4:
            if (Event_Get(kEventDeathReset))
            {
                if (sControlledCharacter_50767C != this)
                {
                    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                }
            }

            if (mHealth <= FP_FromInteger(0))
            {
                SetBrain(&Slig::Brain_Death_46C3A0);
                field_114_timer = sGnFrame + 60;
                return field_10E_brain_sub_state;
            }
            break;

        default:
            return field_10E_brain_sub_state;
    }

    if (field_106_shot)
    {
        BlowToGibs_4685A0();
    }

    return field_10E_brain_sub_state;
}

s16 Slig::Brain_Death_46C3A0()
{
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit3_Render) && field_114_timer < static_cast<s32>(sGnFrame) + 30)
    {
        mBaseAnimatedWithPhysicsGameObject_SpriteScale -= FP_FromDouble(0.01);
        mBaseAnimatedWithPhysicsGameObject_Red -= 2;
        mBaseAnimatedWithPhysicsGameObject_Green -= 2;
        mBaseAnimatedWithPhysicsGameObject_Blue -= 2;

        if (mBaseAnimatedWithPhysicsGameObject_SpriteScale >= FP_FromDouble(0.3))
        {
            DeathSmokeEffect(true);
        }
    }
    else if (!mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if (sControlledCharacter_50767C == this)
    {
        if (field_114_timer < static_cast<s32>(sGnFrame))
        {
            sControlledCharacter_50767C = sActiveHero_507678;
            MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
            gMap.SetActiveCam(
                field_14E_level,
                field_150_path,
                field_152_camera,
                CameraSwapEffects::eInstantChange_0,
                0,
                0);
        }
    }

    if (sControlledCharacter_50767C != this)
    {
        if (!gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0))
        {
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
    }

    if (mBaseAnimatedWithPhysicsGameObject_SpriteScale < FP_FromInteger(0))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    return 116;
}

s16 Slig::Brain_DeathDropDeath_46C5A0()
{
    switch (field_10E_brain_sub_state)
    {
        case Brain_DeathDropDeath::eSayHelpOnce_0:
            Slig_GameSpeak_SFX_46F560(SligSpeak::eHelp_10, 0, field_110_pitch_min, this);
            field_114_timer = sGnFrame + 60;
            return Brain_DeathDropDeath::eSayHelpAndDie_1;

        case Brain_DeathDropDeath::eSayHelpAndDie_1:
        {
            if (static_cast<s32>(sGnFrame) < field_114_timer)
            {
                if (!((field_114_timer - sGnFrame) % 15))
                {
                    Slig_GameSpeak_SFX_46F560(
                        SligSpeak::eHelp_10,
                        static_cast<s16>(2 * ((field_114_timer & 0xFFFF) - sGnFrame)),
                        field_110_pitch_min,
                        this);
                }

                if (static_cast<s32>(sGnFrame) == (field_114_timer - 6))
                {
                    SND_SEQ_Play_477760(SeqId::eHitBottomOfDeathPit_10, 1, 65, 65);
                }
                return field_10E_brain_sub_state;
            }

            Environment_SFX_42A220(EnvironmentSfx::eFallingDeathScreamHitGround_15, 0, 32767, this);

            relive_new ScreenShake(0);
            field_114_timer = sGnFrame + 30;
            return Brain_DeathDropDeath::eSwitchCamToAbe_2;
        }

        case Brain_DeathDropDeath::eSwitchCamToAbe_2:
            if (static_cast<s32>(sGnFrame) > field_114_timer)
            {
                if (sControlledCharacter_50767C == this)
                {
                    MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
                    sControlledCharacter_50767C = sActiveHero_507678;
                    gMap.SetActiveCam(field_14E_level, field_150_path, field_152_camera, CameraSwapEffects::eInstantChange_0, 0, 0);
                }
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            }
            return field_10E_brain_sub_state;

        default:
            return field_10E_brain_sub_state;
    }
}

s16 Slig::Brain_ReturnControlToAbeAndDie_46C760()
{
    if (sControlledCharacter_50767C == this)
    {
        sControlledCharacter_50767C = sActiveHero_507678;
        MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
        gMap.SetActiveCam(
            field_14E_level,
            field_150_path,
            field_152_camera,
            CameraSwapEffects::eInstantChange_0,
            0,
            0);
    }
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    return 117;
}

s16 Slig::Brain_PanicTurning_46C7C0()
{
    if (Event_Get(kEventDeathReset)
        && !gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        return 107;
    }
    if (mCurrentMotion != eSligMotions::Motion_5_TurnAroundStanding_469C80
        || !(mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame)))
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            return 107;
        }
        if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame != 4)
        {
            ShouldStilBeAlive_46C0D0();
            return 107;
        }
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX >= FP_FromInteger(0) && (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX != FP_FromInteger(0) || sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_XPos >= mBaseAnimatedWithPhysicsGameObject_XPos))
            {
                ShouldStilBeAlive_46C0D0();
                return 107;
            }
        }
        else
        {
            if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX <= FP_FromInteger(0) && (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX != FP_FromInteger(0) || sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_XPos <= mBaseAnimatedWithPhysicsGameObject_XPos))
            {
                ShouldStilBeAlive_46C0D0();
                return 107;
            }
        }

        const PSX_RECT bRect = VGetBoundingRect();
        const PSX_RECT charRect = sControlledCharacter_50767C->VGetBoundingRect();

        if (sControlledCharacter_50767C->mBaseGameObjectTypeId != ReliveTypes::eSlig && !IsInInvisibleZone_418870(sControlledCharacter_50767C))
        {
            if (charRect.x <= bRect.w && charRect.w >= bRect.x && charRect.h >= bRect.y && charRect.y <= bRect.h)
            {
                mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
                return 107;
            }
        }
        ShouldStilBeAlive_46C0D0();
        return 107;
    }

    if (field_114_timer > static_cast<s32>(sGnFrame))
    {
        mNextMotion = eSligMotions::Motion_4_Running_469690;
        SetBrain(&Slig::Brain_PanicRunning_46CA20);
        Brain_PanicRunning_46CA20();
        MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
    }
    else
    {
        WaitOrWalk_46E440();
    }
    return 107;
}

s16 Slig::Brain_PanicRunning_46CA20()
{
    if ((mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(4) && (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(4)) + mBaseAnimatedWithPhysicsGameObject_XPos > FP_FromInteger(field_13C_zone_rect.w)) || (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(-4) && (mBaseAnimatedWithPhysicsGameObject_XPos - (ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale) * FP_FromInteger(4))) < FP_FromInteger(field_13C_zone_rect.x))
        || HandleEnemyStopper_46BF30(4))
    {
        mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
        SetBrain(&Slig::Brain_PanicTurning_46C7C0);
    }
    else if (mCurrentMotion || mNextMotion != -1)
    {
        if (VOnSameYLevel(sControlledCharacter_50767C)
            && VIsFacingMe(sControlledCharacter_50767C)
            && !IsInInvisibleZone_418870(sControlledCharacter_50767C)
            && !IsWallBetween_46BE60(this, sControlledCharacter_50767C)
            && gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)
            && gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)
            && !Event_Get(kEventResetting))
        {
            ToShoot_46F1D0();
        }
        else if (sActiveHero_507678->mHealth > FP_FromInteger(0))
        {
            if (field_114_timer > static_cast<s32>(sGnFrame))
            {
                ShouldStilBeAlive_46C0D0();
            }
            else
            {
                WaitOrWalk_46E440();
            }
        }
        else
        {
            ToAbeDead_466270();
        }
    }
    else
    {
        mNextMotion = eSligMotions::Motion_4_Running_469690;
        SetBrain(&Slig::Brain_PanicRunning_46CA20);
        Brain_PanicRunning_46CA20();
        MusicController::static_PlayMusic(MusicController::MusicTypes::eSlogChase_5, this, 0, 0);
    }
    return 109;
}

s16 Slig::Brain_PanicYelling_46CC50()
{
    if (mCurrentMotion == eSligMotions::Motion_29_SpeakPanic_4681D0
        && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Event_Broadcast(kEventAlarm, this);

        const bool bFlipX = mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX);
        field_114_timer = sGnFrame + field_174_tlv.field_36_panic_timeout;
        if ((!bFlipX
             || mBaseAnimatedWithPhysicsGameObject_XPos >= FP_FromInteger((field_13C_zone_rect.x + field_13C_zone_rect.w)
                                                / 2))
            && (bFlipX
                || mBaseAnimatedWithPhysicsGameObject_XPos <= FP_FromInteger((field_13C_zone_rect.x + field_13C_zone_rect.w)
                                                   / 2)))
        {
            ToPanicRunning_46CC20();
        }
        else
        {
            ToPanicTurn();
        }
    }
    else
    {
        ShouldStilBeAlive_46C0D0();
    }
    return 115;
}

s16 Slig::Brain_Chasing_46CD60()
{
    if (gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0)
        && VOnSameYLevel(sControlledCharacter_50767C)
        && VIsFacingMe(sControlledCharacter_50767C)
        && !IsInInvisibleZone_418870(sControlledCharacter_50767C)
        && !IsWallBetween_46BE60(this, sControlledCharacter_50767C)
        && !RenderLayerIs_46C0A0(sControlledCharacter_50767C)
        && !Event_Get(kEventResetting))
    {
        field_20C_force_alive_state = 0;
        RespondToEnemyOrPatrol_465DF0();
        return 118;
    }

    if (HandleEnemyStopper_46BF30(4))
    {
        mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
        SetBrain(&Slig::Brain_Idle_46D6E0);
        field_114_timer = sGnFrame + 1;
        return 118;
    }

    if (mBaseAnimatedWithPhysicsGameObject_PathNumber != gMap.mCurrentPath
        || mBaseAnimatedWithPhysicsGameObject_LvlNumber != gMap.mCurrentLevel
        || (Event_Get(kEventDeathReset)
            && !gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
    else if (gMap.Is_Point_In_Current_Camera_4449C0(
                 mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                 mBaseAnimatedWithPhysicsGameObject_PathNumber,
                 mBaseAnimatedWithPhysicsGameObject_XPos,
                 mBaseAnimatedWithPhysicsGameObject_YPos,
                 0))
    {
        SetBrain(&Slig::Brain_StopChasing_46CF20);
        field_114_timer = sGnFrame + field_174_tlv.field_3C_stop_chase_delay;
    }
    return 118;
}

s16 Slig::Brain_StopChasing_46CF20()
{
    if (field_114_timer > static_cast<s32>(sGnFrame))
    {
        if (HandleEnemyStopper_46BF30(4))
        {
            mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
            SetBrain(&Slig::Brain_Idle_46D6E0);
            field_114_timer = sGnFrame + 1;
        }
    }
    else
    {
        field_20C_force_alive_state = 0;
        field_11C_current_camera = gMap.mCurrentCamera;
        ToTurn_46DE70();
    }
    return 119;
}

s16 Slig::Brain_StartChasing_46CF90()
{
    if (field_114_timer > static_cast<s32>(sGnFrame))
    {
        if (gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0))
        {
            field_20C_force_alive_state = 0;
            ToShoot_46F1D0();
        }
    }
    else
    {
        if (mBaseAnimatedWithPhysicsGameObject_PathNumber != gMap.mCurrentPath
            || mBaseAnimatedWithPhysicsGameObject_LvlNumber != gMap.mCurrentLevel)
        {
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }

        if (!VIsFacingMe(sControlledCharacter_50767C))
        {
            mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
        }

        field_20C_force_alive_state = 1;
        mNextMotion = eSligMotions::Motion_4_Running_469690;
        SetBrain(&Slig::Brain_Chasing_46CD60);
        field_114_timer = field_174_tlv.field_1C_pause_time;
    }
    return 122;
}

s16 Slig::Brain_Idle_46D6E0()
{
    if (Event_Get(kEventAbeOhm) && !Event_Get(kEventResetting))
    {
        ToPanic_46CD40();
        return 104;
    }

    if (VOnSameYLevel(sControlledCharacter_50767C)
        && VIsFacingMe(sControlledCharacter_50767C)
        && !IsInInvisibleZone_418870(sControlledCharacter_50767C)
        && !IsWallBetween_46BE60(this, sControlledCharacter_50767C)
        && (!field_20E_spotted_possessed_slig
            || sControlledCharacter_50767C->mBaseGameObjectTypeId != ReliveTypes::eSlig)
        && !IsAbeEnteringDoor_46BEE0(sControlledCharacter_50767C)
        && !Event_Get(kEventResetting)
        && gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0))
    {
        Slig::RespondToEnemyOrPatrol_465DF0();
        return 104;
    }
    if (sActiveHero_507678->mHealth <= FP_FromInteger(0))
    {
        ToAbeDead_466270();
        return 104;
    }
    auto pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSuspiciousNoise));

    if (!pEvent)
    {
        pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSpeaking));
    }

    if (!pEvent || pEvent->mBaseAnimatedWithPhysicsGameObject_SpriteScale != mBaseAnimatedWithPhysicsGameObject_SpriteScale || pEvent == this || !gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) || Event_Get(kEventResetting))
    {
        if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_SpriteScale > mBaseAnimatedWithPhysicsGameObject_SpriteScale
            && (sControlledCharacter_50767C == sActiveHero_507678
                || sControlledCharacter_50767C == gElum_507680))
        {
            if (VIsFacingMe(sControlledCharacter_50767C) && !IsInInvisibleZone_418870(sControlledCharacter_50767C) && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) && !IsInZCover_46BDA0(static_cast<Slig*>(sControlledCharacter_50767C)) && !IsInZCover_46BDA0(this) && !Event_Get(kEventResetting))
            {
                ToZShoot_46F200();
                return 104;
            }
        }
        if (sControlledCharacter_50767C->mBaseGameObjectTypeId == ReliveTypes::eSlig)
        {
            if (mCurrentMotion)
            {
                ShouldStilBeAlive_46C0D0();
                return 104;
            }
            if (pEventSystem_4FF954->field_10_last_event == GameSpeakEvents::eUnknown_29)
            {
                auto pTlv = static_cast<Path_Lever*>(gMap.TLV_Get_At_446260(
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    TlvTypes::Lever_26));
                if (pTlv)
                {
                    FP kScaleGrid = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
                    if ((FP_FromInteger(FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos) - pTlv->field_10_top_left.field_0_x) < kScaleGrid && !(mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))) || (FP_FromInteger(pTlv->field_14_bottom_right.field_0_x - FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos)) < kScaleGrid && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX)))
                    {
                        auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(
                            ReliveTypes::eLever,
                            mBaseAnimatedWithPhysicsGameObject_XPos + kScaleGrid,
                            mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));
                        if (pSwitch)
                        {
                            pSwitch->VPull(mBaseAnimatedWithPhysicsGameObject_XPos < pSwitch->mBaseAnimatedWithPhysicsGameObject_XPos ? TRUE : FALSE);
                        }
                        mNextMotion = eSligMotions::State_46_PullLever_46A590;
                        return 104;
                    }
                }
            }
        }
        if (mCurrentMotion == eSligMotions::Motion_0_StandIdle_467640 && field_114_timer <= static_cast<s32>(sGnFrame))
        {
            mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            SetBrain(&Slig::Brain_Turning_46DC70);
            return 104;
        }
        ShouldStilBeAlive_46C0D0();
        return 104;
    }
    if (pEvent != sControlledCharacter_50767C)
    {
        if (Math_NextRandom() >= 192u)
        {
            return 104;
        }
    }
    if (VIsFacingMe(sControlledCharacter_50767C))
    {
        if (!Event_Get(kEventSpeaking) || IsInInvisibleZone_418870(sControlledCharacter_50767C))
        {
            mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
            field_258_next_gamespeak_motion = eSligMotions::Motion_30_SpeakWhat_468290;
            SetBrain(&Slig::Brain_GetAlerted_46E800);
            field_114_timer = static_cast<s32>(sGnFrame) + field_174_tlv.field_42_listen_time;
            return 104;
        }
        GameSpeakResponse_46ED60();
        field_114_timer = static_cast<s32>(sGnFrame) + 20;
    }
    else
    {
        if (!Event_Get(kEventSpeaking) || IsInInvisibleZone_418870(sControlledCharacter_50767C))
        {
            mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            SetBrain(&Slig::Brain_GetAlertedTurn_46E520);
            return 104;
        }
        GameSpeakResponse_46ED60();
        field_114_timer = static_cast<s32>(sGnFrame) + 20;
    }
    if (!VIsFacingMe(sControlledCharacter_50767C))
    {
        mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
    }
    SetBrain(&Slig::Brain_Discussion_46ECE0);
    return 104;
}

s16 Slig::Brain_Turning_46DC70()
{
    if (Event_Get(kEventDeathReset)
        && !gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0))
    {
        mBaseGameObjectFlags.Set(Options::eDead);
        return 106;
    }
    if (mCurrentMotion == eSligMotions::Motion_5_TurnAroundStanding_469C80
        && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        WaitOrWalk_46E440();
        return 106;
    }
    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 4)
    {
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX >= FP_FromInteger(0) && (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX != FP_FromInteger(0) || sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_XPos >= mBaseAnimatedWithPhysicsGameObject_XPos))
            {
                ShouldStilBeAlive_46C0D0();
                return 106;
            }
        }
        else
        {
            if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX <= FP_FromInteger(0) && (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX != FP_FromInteger(0) || sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_XPos <= mBaseAnimatedWithPhysicsGameObject_XPos))
            {
                ShouldStilBeAlive_46C0D0();
                return 106;
            }
        }

        const PSX_RECT hitRect = VGetBoundingRect();

        if (!Slig::IsInInvisibleZone_418870(sControlledCharacter_50767C)
            && !Slig::IsWallBetween_46BE60(this, sControlledCharacter_50767C))
        {
            const PSX_RECT bRect = sControlledCharacter_50767C->VGetBoundingRect();

            if (sControlledCharacter_50767C->mHealth > FP_FromInteger(0) && PSX_Rects_overlap_no_adjustment(&hitRect, &bRect) && sControlledCharacter_50767C->mBaseGameObjectTypeId != ReliveTypes::eSlig)
            {
                mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
                return 106;
            }
        }
    }

    ShouldStilBeAlive_46C0D0();
    return 106;
}

s16 Slig::Brain_Walking_46DE90()
{
    if (unused_9F11BC) // NOTE: This is never set to true, so this branch is never executed.
    {
        ToPanicRunning_46CC20();
        return 108;
    }

    FP kScaleGrid = ScaleToGridSize(mBaseAnimatedWithPhysicsGameObject_SpriteScale);
    FP kScaleGrid2 = kScaleGrid * FP_FromInteger(2);
    if (mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0))
    {
        if ((kScaleGrid2 + mBaseAnimatedWithPhysicsGameObject_XPos) >= FP_FromInteger(field_13C_zone_rect.w))
        {
            PauseALittle_46DBD0();
            return 108;
        }
    }
    if (mBaseAnimatedWithPhysicsGameObject_VelX < FP_FromInteger(0))
    {
        if ((mBaseAnimatedWithPhysicsGameObject_XPos - kScaleGrid2) <= FP_FromInteger(field_13C_zone_rect.x))
        {
            PauseALittle_46DBD0();
            return 108;
        }
    }
    if (mBaseAnimatedWithPhysicsGameObject_VelX == FP_FromInteger(0) && mCurrentMotion == eSligMotions::Motion_0_StandIdle_467640 && mNextMotion != eSligMotions::Motion_2_Walking_469130)
    {
        PauseALittle_46DBD0();
        return 108;
    }
    if (HandleEnemyStopper_46BF30(2))
    {
        PauseALittle_46DBD0();
        return 108;
    }

    if (VOnSameYLevel(sControlledCharacter_50767C) && VIsFacingMe(sControlledCharacter_50767C) && !IsInInvisibleZone_418870(sControlledCharacter_50767C) && !IsWallBetween_46BE60(this, sControlledCharacter_50767C) && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0))
    {
        if (!field_20E_spotted_possessed_slig
            || sControlledCharacter_50767C->mBaseGameObjectTypeId != ReliveTypes::eSlig)
        {
            if (!IsAbeEnteringDoor_46BEE0(sControlledCharacter_50767C) && !Event_Get(kEventResetting))
            {
                RespondToEnemyOrPatrol_465DF0();
                return 108;
            }
        }
    }

    if (VOnSameYLevel(sControlledCharacter_50767C) && VIsFacingMe(sControlledCharacter_50767C) && !IsWallBetween_46BE60(this, sControlledCharacter_50767C) && Event_Get(kEventAbeOhm) && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) && !Event_Get(kEventResetting))
    {
        ToShoot_46F1D0();
        return 108;
    }
    if (Event_Get(kEventAbeOhm) && !Event_Get(kEventResetting))
    {
        ToPanic_46CD40();
        return 108;
    }
    if (sActiveHero_507678->mHealth <= FP_FromInteger(0))
    {
        ToAbeDead_466270();
        return 108;
    }
    auto pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSuspiciousNoise));
    if (!pEvent)
    {
        pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSpeaking));
    }
    if (pEvent && pEvent->mBaseAnimatedWithPhysicsGameObject_SpriteScale == mBaseAnimatedWithPhysicsGameObject_SpriteScale && pEvent != this && gMap.Is_Point_In_Current_Camera_4449C0(mBaseAnimatedWithPhysicsGameObject_LvlNumber, mBaseAnimatedWithPhysicsGameObject_PathNumber, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, 0) && !Event_Get(kEventResetting))
    {
        if (VIsFacingMe(sControlledCharacter_50767C))
        {
            if (!Event_Get(kEventSpeaking) || IsInInvisibleZone_418870(sControlledCharacter_50767C))
            {
                mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
                field_258_next_gamespeak_motion = eSligMotions::Motion_30_SpeakWhat_468290;
                SetBrain(&Slig::Brain_GetAlerted_46E800);
                field_114_timer = static_cast<s32>(sGnFrame) + field_174_tlv.field_42_listen_time;
                return 108;
            }
        }
        else
        {
            if (!Event_Get(kEventSpeaking) || IsInInvisibleZone_418870(sControlledCharacter_50767C))
            {
                mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
                SetBrain(&Slig::Brain_GetAlertedTurn_46E520);
                return 108;
            }
        }
        GameSpeakResponse_46ED60();
        field_114_timer = sGnFrame + 20;
        if (!VIsFacingMe(sControlledCharacter_50767C))
        {
            mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
        }
        SetBrain(&Slig::Brain_Discussion_46ECE0);
        return 108;
    }
    else if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_SpriteScale <= mBaseAnimatedWithPhysicsGameObject_SpriteScale
             || (sControlledCharacter_50767C != sActiveHero_507678
                 && sControlledCharacter_50767C != gElum_507680)
             || !VIsFacingMe(sControlledCharacter_50767C)
             || IsInInvisibleZone_418870(sControlledCharacter_50767C)
             || !gMap.Is_Point_In_Current_Camera_4449C0(
                 mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                 mBaseAnimatedWithPhysicsGameObject_PathNumber,
                 mBaseAnimatedWithPhysicsGameObject_XPos,
                 mBaseAnimatedWithPhysicsGameObject_YPos,
                 0)
             || IsInZCover_46BDA0(sControlledCharacter_50767C)
             || IsInZCover_46BDA0(this)
             || Event_Get(kEventResetting))
    {
        if (Math_NextRandom() < field_174_tlv.field_46_percent_beat_mud
            && FindBeatTarget_46D0E0(52, 2))
        {
            mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
            SetBrain(&Slig::Brain_StoppingNextToMudokon_46EBB0);
            field_114_timer = static_cast<s32>(sGnFrame) + 30;
            return 108;
        }
        else
        {
            ShouldStilBeAlive_46C0D0();
            return 108;
        }
    }
    else
    {
        ToZShoot_46F200();
        return 108;
    }
}

s16 Slig::Brain_GetAlertedTurn_46E520()
{
    if (mCurrentMotion == eSligMotions::Motion_5_TurnAroundStanding_469C80 && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (!Event_Get(kEventSpeaking) || IsInInvisibleZone_418870(sControlledCharacter_50767C))
        {
            mNextMotion = eSligMotions::Motion_0_StandIdle_467640;
            field_258_next_gamespeak_motion = eSligMotions::Motion_30_SpeakWhat_468290;
            SetBrain(&Slig::Brain_GetAlerted_46E800);
            field_114_timer = sGnFrame + field_174_tlv.field_42_listen_time;
        }
        else
        {
            GameSpeakResponse_46ED60();
            field_114_timer = sGnFrame + 20;

            if (!VIsFacingMe(sControlledCharacter_50767C))
            {
                mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
            }

            SetBrain(&Slig::Brain_Discussion_46ECE0);
        }

        return 123;
    }

    if (mBaseAnimatedWithPhysicsGameObject_Anim.field_92_current_frame == 4)
    {
        bool tryTurningToPlayer = true;
        if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX >= FP_FromInteger(0) && (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0) || sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_XPos >= mBaseAnimatedWithPhysicsGameObject_XPos))
            {
                tryTurningToPlayer = false;
            }
        }
        else if (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX <= FP_FromInteger(0) && (sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_VelX > FP_FromInteger(0) || sControlledCharacter_50767C->mBaseAnimatedWithPhysicsGameObject_XPos <= mBaseAnimatedWithPhysicsGameObject_XPos))
        {
            tryTurningToPlayer = false;
        }

        if (tryTurningToPlayer)
        {
            if (!IsInInvisibleZone_418870(sControlledCharacter_50767C))
            {
                const PSX_RECT bRect = VGetBoundingRect();
                const PSX_RECT bRectChar = sControlledCharacter_50767C->VGetBoundingRect();

                if (PSX_Rects_overlap_no_adjustment(&bRectChar, &bRect))
                {
                    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
                    return 123;
                }
            }
        }
    }

    if (mCurrentMotion != eSligMotions::Motion_0_StandIdle_467640)
    {
        ShouldStilBeAlive_46C0D0();
    }
    else
    {
        mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
    }
    return 123;
}

s16 Slig::Brain_GetAlerted_46E800()
{
    if (field_114_timer == field_174_tlv.field_42_listen_time + static_cast<s32>(sGnFrame) - 2 && Math_RandomRange_450F20(0, 100) < field_174_tlv.field_44_percent_say_what)
    {
        mNextMotion = eSligMotions::Motion_30_SpeakWhat_468290;
    }

    if (!VOnSameYLevel(sControlledCharacter_50767C)
        || !VIsFacingMe(sControlledCharacter_50767C)
        || IsInInvisibleZone_418870(sControlledCharacter_50767C)
        || IsWallBetween_46BE60(this, sControlledCharacter_50767C)
        || !gMap.Is_Point_In_Current_Camera_4449C0(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0)
        || (sControlledCharacter_50767C->mBaseGameObjectTypeId == ReliveTypes::eSlig && field_20E_spotted_possessed_slig)
        || IsAbeEnteringDoor_46BEE0(sControlledCharacter_50767C)
        || Event_Get(kEventResetting))
    {
        if (!Event_Get(kEventAbeOhm) || Event_Get(kEventResetting))
        {
            BaseAliveGameObject* pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSuspiciousNoise));
            if (!pEvent)
            {
                pEvent = static_cast<BaseAliveGameObject*>(Event_Get(kEventSpeaking));
            }

            if (pEvent && (pEvent == sControlledCharacter_50767C || pEvent->mBaseGameObjectTypeId == ReliveTypes::eMudokon)
                && VOnSameYLevel(pEvent)
                && VIsFacingMe(pEvent)
                && gMap.Is_Point_In_Current_Camera_4449C0(
                    mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                    mBaseAnimatedWithPhysicsGameObject_PathNumber,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    0)
                && !Event_Get(kEventResetting))
            {
                ToShoot_46F1D0();
            }
            else
            {
                if (pEvent && (pEvent == sControlledCharacter_50767C || pEvent->mBaseGameObjectTypeId != ReliveTypes::eSlig)
                    && !VIsFacingMe(pEvent)
                    && gMap.Is_Point_In_Current_Camera_4449C0(
                        mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                        mBaseAnimatedWithPhysicsGameObject_PathNumber,
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos,
                        0)
                    && !Event_Get(kEventResetting))
                {
                    if (!Event_Get(kEventSpeaking) || IsInInvisibleZone_418870(sControlledCharacter_50767C))
                    {
                        mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
                        SetBrain(&Slig::Brain_GetAlertedTurn_46E520);
                    }
                    else
                    {
                        GameSpeakResponse_46ED60();
                        field_114_timer = sGnFrame + 20;
                        if (!VIsFacingMe(sControlledCharacter_50767C))
                        {
                            mNextMotion = eSligMotions::Motion_5_TurnAroundStanding_469C80;
                        }

                        SetBrain(&Slig::Brain_Discussion_46ECE0);
                    }
                }
                else
                {
                    if (field_114_timer > static_cast<s32>(sGnFrame))
                    {
                        ShouldStilBeAlive_46C0D0();
                    }
                    else
                    {
                        WaitOrWalk_46E440();
                    }
                }
            }
        }
        else
        {
            ToPanic_46CD40();
        }
    }
    else
    {
        RespondToEnemyOrPatrol_465DF0();
    }
    return 124;
}

s16 Slig::Brain_StoppingNextToMudokon_46EBB0()
{
    if (mCurrentMotion != eSligMotions::Motion_0_StandIdle_467640)
    {
        return 128;
    }

    //TODO OG BUG: Sligs beat up dead muds, fix from AE:
    //BaseAliveGameObject* pBeatTarget = FindBeatTarget_4BD070(static_cast<s32>(AOTypes::eRingOrLiftMud_81), 1);
    //if (!pBeatTarget || pBeatTarget->mHealth <= FP_FromInteger(0))
    if (!FindBeatTarget_46D0E0(static_cast<s32>(AOTypes::eRingOrLiftMud_52), 1))
    {
        WaitOrWalk_46E440();
        return 128;
    }

    if (Math_NextRandom() >= 100u)
    {
        if (Math_NextRandom() & 1)
        {
            mNextMotion = eSligMotions::Motion_26_SpeakBullshit1_467F90;
        }
        else
        {
            mNextMotion = eSligMotions::Motion_28_SpeakBullshit2_468110;
        }
    }
    else
    {
        mNextMotion = eSligMotions::Motion_52_Beat_46AA90;
        SetBrain(&Slig::Brain_BeatingUp_46EC40);
    }

    return 128;
}

s16 Slig::Brain_BeatingUp_46EC40()
{
    if (mCurrentMotion != eSligMotions::Motion_0_StandIdle_467640 || field_114_timer >= static_cast<s32>(sGnFrame))
    {
        return 129;
    }

    if (Math_NextRandom() < 100u)
    {
        mNextMotion = eSligMotions::Motion_52_Beat_46AA90;
        return 129;
    }

    if (Math_NextRandom() < 64u)
    {
        mNextMotion = eSligMotions::Motion_26_SpeakBullshit1_467F90;
        return 129;
    }

    if (Math_NextRandom() < 64u)
    {
        mNextMotion = eSligMotions::Motion_28_SpeakBullshit2_468110;
        return 129;
    }

    WaitOrWalk_46E440();
    return 129;
}

s16 Slig::Brain_Discussion_46ECE0()
{
    if (mCurrentMotion == eSligMotions::Motion_0_StandIdle_467640 && field_114_timer == static_cast<s32>(sGnFrame))
    {
        mNextMotion = static_cast<s16>(field_258_next_gamespeak_motion);
    }

    if (field_114_timer < static_cast<s32>(sGnFrame) - 5)
    {
        WaitOrWalk_46E440();
    }

    return 128;
}

enum Brain_ChaseAndDisappear
{
    eSummoned_0 = 0,
    eRunning_1 = 1,
    eReachedDestination_2 = 2
};

s16 Slig::Brain_ChaseAndDisappear_46EEE0()
{
    if (Event_Get(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if (field_10E_brain_sub_state == Brain_ChaseAndDisappear::eSummoned_0)
    {
        if (sNumCamSwappers_507668 > 0 || sActiveHero_507678->field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
        {
            return field_10E_brain_sub_state;
        }
        mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
        field_114_timer = sGnFrame + field_130_game_ender_pause_time;
        return Brain_ChaseAndDisappear::eRunning_1;
    }
    else if (field_10E_brain_sub_state == Brain_ChaseAndDisappear::eRunning_1)
    {
        if (static_cast<s32>(sGnFrame) < field_114_timer)
        {
            return field_10E_brain_sub_state;
        }
        mNextMotion = eSligMotions::Motion_4_Running_469690;
        return Brain_ChaseAndDisappear::eReachedDestination_2;
    }
    else
    {
        if (field_10E_brain_sub_state == Brain_ChaseAndDisappear::eReachedDestination_2
            && gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0))
        {
            return field_10E_brain_sub_state;
        }
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        mHealth = FP_FromInteger(0);
        return field_10E_brain_sub_state;
    }
}

s16 Slig::Brain_Shooting_46EFD0()
{
    if (mCurrentMotion == eSligMotions::Motion_6_Shoot_468820
        && mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_200_num_times_to_shoot++;

        if (field_200_num_times_to_shoot < field_174_tlv.field_2A_num_times_to_shoot
            || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0
            || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_139_ElumMountBegin_42E090
            || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_138_ElumUnmountEnd_42E390
            || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_136_ElumMountEnd_42E110)
        {
            mNextMotion = eSligMotions::Motion_6_Shoot_468820;
            return 111;
        }

        if (sActiveHero_507678->mHealth <= FP_FromInteger(0))
        {
            ToKilledAbe_4662E0();
            return 111;
        }

        if (sControlledCharacter_50767C->mHealth <= FP_FromInteger(0))
        {
            ToKilledAbe_4662E0();
            return 111;
        }

        if (!VOnSameYLevel(sControlledCharacter_50767C)
            || !VIsFacingMe(sControlledCharacter_50767C)
            || IsInInvisibleZone_418870(sControlledCharacter_50767C)
            || IsWallBetween_46BE60(this, sControlledCharacter_50767C)
            || !gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)
            || !gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)
            || Event_Get(kEventResetting))
        {
            PauseALittle_46DBD0();
            return 111;
        }

        if (!VIsFacingMe(sControlledCharacter_50767C))
        {
            ToTurn_46DE70();
            return 111;
        }

        if (!gMap.Is_Point_In_Current_Camera_4449C0(
                mBaseAnimatedWithPhysicsGameObject_LvlNumber,
                mBaseAnimatedWithPhysicsGameObject_PathNumber,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                0)
            && field_174_tlv.field_32_chase_abe == Choice_short::eYes_1)
        {
            ToChase_46D080();
            return 111;
        }
    }

    ShouldStilBeAlive_46C0D0();
    return 111;
}

s16 Slig::Brain_ZSpottedEnemy_46F260()
{
    if (field_114_timer > static_cast<s32>(sGnFrame))
    {
        return 126;
    }
    mNextMotion = eSligMotions::Motion_43_ShootZ_468E30;
    SetBrain(&Slig::Brain_ZShooting_46F290);
    return 126;
}


s16 Slig::Brain_ZShooting_46F290()
{
    if (mCurrentMotion != eSligMotions::Motion_43_ShootZ_468E30 || !mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ShouldStilBeAlive_46C0D0();
        return 127;
    }

    field_200_num_times_to_shoot++;

    if (field_200_num_times_to_shoot < field_174_tlv.field_2A_num_times_to_shoot)
    {
        return 127;
    }

    if (sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_138_ElumUnmountEnd_42E390
        || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_136_ElumMountEnd_42E110
        || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0
        || sActiveHero_507678->mCurrentMotion == eAbeMotions::Motion_139_ElumMountBegin_42E090)
    {
        return 127;
    }

    field_200_num_times_to_shoot = 0;

    if (sActiveHero_507678->mHealth > FP_FromInteger(0))
    {
        WaitOrWalk_46E440();
    }
    else
    {
        ToAbeDead_466270();
    }
    return 127;
}

void Slig::BlowToGibs_4685A0()
{
    relive_new Gibs(
        GibType::Slig_1,
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos,
        mBaseAnimatedWithPhysicsGameObject_VelX,
        mBaseAnimatedWithPhysicsGameObject_VelY,
        mBaseAnimatedWithPhysicsGameObject_SpriteScale);

    relive_new Blood(
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos - (FP_FromInteger(30) * mBaseAnimatedWithPhysicsGameObject_SpriteScale),
        FP_FromInteger(0),
        FP_FromInteger(0),
        mBaseAnimatedWithPhysicsGameObject_SpriteScale,
        20);

    New_Smoke_Particles_419A80(
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos - (FP_FromInteger(30) * mBaseAnimatedWithPhysicsGameObject_SpriteScale),
        mBaseAnimatedWithPhysicsGameObject_SpriteScale,
        3,
        0);

    if (mBaseAnimatedWithPhysicsGameObject_SpriteScale == FP_FromDouble(0.5))
    {
        SFX_Play_Mono(SoundEffect::KillEffect_78, 80, 0);
        SFX_Play_Mono(SoundEffect::FallingItemHit_53, 60, 0);
    }
    else
    {
        SFX_Play_Mono(SoundEffect::KillEffect_78, 127, 0);
        SFX_Play_Mono(SoundEffect::FallingItemHit_53, 90, 0);
    }

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
    mCurrentMotion = eSligMotions::Motion_0_StandIdle_467640;
    mBaseAnimatedWithPhysicsGameObject_VelY = FP_FromInteger(0);
    mBaseAnimatedWithPhysicsGameObject_VelX = FP_FromInteger(0);
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
    field_114_timer = sGnFrame + 60;
    mBaseGameObjectUpdateDelay = 40;
    SetBrain(&Slig::Brain_Death_46C3A0);
    Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
}

void Slig::SetBrain(Slig::TBrainFn fn)
{
    field_1F8_fn = fn;
}

void Slig::SetBrain2(Slig::TBrainFn fn)
{
    field_1FC_fn2 = fn;
}

bool Slig::BrainIs(Slig::TBrainFn fn)
{
    return field_1F8_fn == fn;
}

} // namespace AO
