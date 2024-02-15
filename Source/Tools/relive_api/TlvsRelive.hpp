#pragma once

#include "TlvObjectBaseRelive.hpp"
#include "TlvObjectBaseMacros.hpp"
#include "../../relive_lib/data_conversion/relive_tlvs.hpp"
#include "../../relive_lib/AnimResources.hpp"
#include <type_traits>

#define CTOR_RELIVE(editorClassName, pathClassName, tlvEnumType)\
    editorClassName() : TlvObjectBaseRelive(sizeof(relive::pathClassName), tlvEnumType, relive::pathClassName::kClassName, &mTlv)\
    {\
    }\
    \
    editorClassName(ReliveAPI::TypesCollectionBase& globalTypes, const relive::Path_TLV* pTlvSrc = nullptr) \
        : TlvObjectBaseRelive(sizeof(relive::pathClassName), globalTypes, tlvEnumType, relive::pathClassName::kClassName, &mTlv)\
    {\
        if (pTlvSrc)\
        {\
            mTlv = *static_cast<const ::relive::pathClassName*>(pTlvSrc);\
            ConvertXYPos(); \
        }\
        else\
        {\
            mPSelfTlv->mLength = static_cast<s16>(mSizeOfT);\
        }\
        AddProperties(globalTypes);\
    }\
    relive::pathClassName mTlv = {};\
    void AddProperties(ReliveAPI::TypesCollectionBase& globalTypes)

#define EMPTY_CTOR_RELIVE() (void) globalTypes

class IRefelector
{
public:
    virtual ~IRefelector() { }

    virtual void Visit(const char* fieldName, relive::reliveScale& field) = 0;

    virtual void Visit(const char* fieldName, u16& field) = 0;
    virtual void Visit(const char* fieldName, s16& field) = 0;

    virtual void Visit(const char* fieldName, u32& field) = 0;
    virtual void Visit(const char* fieldName, s32& field) = 0;

};

// TODO: Move back to the editor src
class MapObjectBase
{
public:
    MapObjectBase(relive::Path_TLV* pTlv)
     : mBaseTlv(pTlv)
    {

    }

    virtual ~MapObjectBase() { }

    relive::Path_TLV* mBaseTlv = nullptr;

    void SetXPos(s32 xpos)
    {
        mBaseTlv->mTopLeftX = xpos;
    }

    void SetYPos(s32 ypos)
    {
        mBaseTlv->mTopLeftY = ypos;
    }

    void SetWidth(s32 width)
    {
        mBaseTlv->mBottomRightX = width;
    }

    void SetHeight(s32 height)
    {
        mBaseTlv->mBottomRightY = height;
    }

    s32 XPos() const
    {
        return mBaseTlv->mTopLeftX;
    }

    s32 YPos() const
    {
        return mBaseTlv->mTopLeftY;
    }

    s32 Width() const
    {
        return mBaseTlv->Width();
    }

    s32 Height() const
    {
        return mBaseTlv->Height();
    }

    virtual void Visit(IRefelector& r)
    {
        r.Visit("top left x", mBaseTlv->mTopLeftX);
        r.Visit("top left y", mBaseTlv->mTopLeftY);
        r.Visit("bottom right x", mBaseTlv->mBottomRightX);
        r.Visit("bottom right y", mBaseTlv->mBottomRightY);
    }
};

namespace relive
{


class Editor_TimedMine final : public MapObjectBase
{
public:
    Editor_TimedMine() : MapObjectBase(&mTlv) { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Ticks Before Explosion", mTlv.mTicksUntilExplosion);
    }

    Path_TimedMine mTlv;
};

class Editor_ElectricWall final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_ElectricWall::ElectricWallStartState>("Enum_ElectricWallStartState",
        {
            {relive::Path_ElectricWall::ElectricWallStartState::eOff, "Off"},
            {relive::Path_ElectricWall::ElectricWallStartState::eOn, "On"},
        });
    }
    */
    public:
    Editor_ElectricWall()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Start State", mTlv.mStartState);
    }

    Path_ElectricWall mTlv;
};

struct Editor_Mudokon final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Mudokon::Mud_TLV_Emotion>("Enum_Mud_TLV_Emotion",
        {
            {relive::Path_Mudokon::Mud_TLV_Emotion::eNormal, "Normal"},
            {relive::Path_Mudokon::Mud_TLV_Emotion::eAngry, "Angry"},
            {relive::Path_Mudokon::Mud_TLV_Emotion::eSad, "Sad"},
            {relive::Path_Mudokon::Mud_TLV_Emotion::eWired, "Wired"},
            {relive::Path_Mudokon::Mud_TLV_Emotion::eSick, "Sick"}
        });

        types.AddEnum<relive::Path_Mudokon::MudJobs>("Enum_Mud_State",
        {
            {relive::Path_Mudokon::MudJobs::eChisle, "Chisle"},
            {relive::Path_Mudokon::MudJobs::eSitScrub, "Scrub"},
            {relive::Path_Mudokon::MudJobs::eAngryWorker, "Angry Worker"},
            {relive::Path_Mudokon::MudJobs::eDamageRingGiver, "Damage Ring Giver"},
            {relive::Path_Mudokon::MudJobs::eHealthRingGiver, "Health Ring Giver"},
        });
    }
    */

public:
    Editor_Mudokon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Job", mTlv.mJob);
        //r.Visit("Facing", mTlv.mFacing);
        r.Visit("Voice Pitch", mTlv.mVoicePitch);
        r.Visit("Rescue Switch ID", mTlv.mRescueSwitchId);
        //r.Visit("Deaf", mTlv.mDeaf);
        r.Visit("Disabled Resources", mTlv.mDisabledResources);
        //r.Visit("Persist & Reset Offscreen", mTlv.mPersistAndResetOffscreen);
        //r.Visit("Emotion", mTlv.mEmotion);
        //r.Visit("Blind", mTlv.mBlind);
        r.Visit("Angry Switch ID", mTlv.mAngrySwitchId);
        //r.Visit("Work After Turning Wheel", mTlv.mWorkAfterTurningWheel);
        //r.Visit("Gets Depressed", mTlv.mGetsDepressed);
        r.Visit("Ring Pulse Interval", mTlv.mRingPulseInterval);
        //r.Visit("Give Ring Without Password", mTlv.mGiveRingWithoutPassword);
    }

    Path_Mudokon mTlv;
};

struct Editor_BirdPortal final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_BirdPortal::PortalType>("Enum_PortalType",
        {
            {relive::Path_BirdPortal::PortalType::eAbe, "Abe"},
            {relive::Path_BirdPortal::PortalType::eWorker, "Worker"},
            {relive::Path_BirdPortal::PortalType::eShrykull, "Shrykull"},
            {relive::Path_BirdPortal::PortalType::eMudTeleport, "Mud Teleport"},
        });
    }
    */

public:
    Editor_BirdPortal()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        //r.Visit("Enter Side", mTlv.mEnterSide);
        // r.Visit("BirdPortalExit Level", mTlv.mExitLevel);
         r.Visit("BirdPortalExit Path", mTlv.mExitPath);
        r.Visit("BirdPortalExit Camera", mTlv.mExitCamera);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Movie ID", mTlv.mMovieId);
        //r.Visit("Portal Type", mTlv.mPortalType);
        r.Visit("Mudokon Amount For Shrykull", mTlv.mMudCountForShrykull);
        r.Visit("(AE) Create Portal Switch ID", mTlv.mCreatePortalSwitchId);
        r.Visit("(AE) Delete Portal Switch ID", mTlv.mDeletePortalSwitchId);
    }

    Path_BirdPortal mTlv;
};

struct Editor_LCDStatusBoard final : public MapObjectBase
{
public:
    Editor_LCDStatusBoard()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        r.Visit("(AE) Number of Mudokons", mTlv.mNumberOfMuds);
        r.Visit("(AE) Zulag Number", mTlv.mZulagNumber);
        //r.Visit("(AE) Hide Board", mTlv.mHideBoard);
    }

    Path_LCDStatusBoard mTlv;
};

struct Editor_Door final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Door::DoorStates>("Enum_DoorStates",
        {{relive::Path_Door::DoorStates::eOpen, "Open"},
        {relive::Path_Door::DoorStates::eClosed, "Closed"},
        {relive::Path_Door::DoorStates::eOpening, "Opening"},
        {relive::Path_Door::DoorStates::eClosing, "Closing"}});

        types.AddEnum<relive::Path_Door::DoorTypes>("Enum_DoorTypes",
        {{relive::Path_Door::DoorTypes::eBasicDoor, "Basic Door"},
        {relive::Path_Door::DoorTypes::eTasksDoorWithSecretMusic, "Tasks Door With Secret Music"},
        {relive::Path_Door::DoorTypes::eTasksDoor, "Tasks Door"},
        {relive::Path_Door::DoorTypes::eTrialDoor, "(AO) Trial Door"},
        {relive::Path_Door::DoorTypes::eHubDoor, "(AO) Hub Door"}});
    }
    */

public:
    Editor_Door()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        r.Visit("Next Path", mTlv.mNextPath);
        //r.Visit("Next Level", mTlv.mNextLevel);
        r.Visit("Next Camera", mTlv.mNextCamera);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Door ID", mTlv.mDoorId);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Target Door ID", mTlv.mTargetDoorId);
        //r.Visit("Door Type", mTlv.mDoorType);
        //r.Visit("(AO) Door Closed", mTlv.mDoorClosed);
        //r.Visit("(AE) Start State", mTlv.mStartState);
        r.Visit("Hub 1 ID", mTlv.mHub1);
        r.Visit("Hub 2 ID", mTlv.mHub2);
        r.Visit("Hub 3 ID", mTlv.mHub3);
        r.Visit("Hub 4 ID", mTlv.mHub4);
        r.Visit("Hub 5 ID", mTlv.mHub5);
        r.Visit("Hub 6 ID", mTlv.mHub6);
        r.Visit("Hub 7 ID", mTlv.mHub7);
        r.Visit("Hub 8 ID", mTlv.mHub8);
        //r.Visit("Wipe Effect", mTlv.mWipeEffect);
        r.Visit("Movie ID", mTlv.mMovieId);
        r.Visit("X Offset", mTlv.mDoorOffsetX);
        r.Visit("Y Offset", mTlv.mDoorOffsetY);
        //r.Visit("Abe Direction On Exit", mTlv.mExitDirection);
        //r.Visit("(AE) Close On Exit", mTlv.mCloseOnExit);
        //r.Visit("(AE) Clear Throwables", mTlv.mClearThrowables);
    }

    Path_Door mTlv;
};

struct Editor_Lever final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Lever::LeverSoundType>("Enum_LeverSoundType",
        {
            {relive::Path_Lever::LeverSoundType::eNone, "None"},
            {relive::Path_Lever::LeverSoundType::eWell, "Well"},
            {relive::Path_Lever::LeverSoundType::eSwitchBellHammer, "Switch Bell Hammer"},
            {relive::Path_Lever::LeverSoundType::eDoor, "Door"},
            {relive::Path_Lever::LeverSoundType::eElectricWall, "Electric Wall"},
            {relive::Path_Lever::LeverSoundType::eSecurityOrb, "Security Orb"},
            {relive::Path_Lever::LeverSoundType::eLift, "(AE) Lift"}
        });

        types.AddEnum<relive::Path_Lever::LeverSoundDirection>("Enum_LeverSoundDirection",
        {
            {relive::Path_Lever::LeverSoundDirection::eLeftAndRight, "Left And Right"},
            {relive::Path_Lever::LeverSoundDirection::eLeft, "Left"},
            {relive::Path_Lever::LeverSoundDirection::eRight, "Right"},
        });
    }
    */

public:
    Editor_Lever()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        //r.Visit("Action", mTlv.mAction);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("On Sound", mTlv.mOnSound);
        //r.Visit("Off Sound", mTlv.mOffSound);
        //r.Visit("Sound Direction", mTlv.mSoundDirection);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("(AE) Persist Offscreen", mTlv.mPersistOffscreen);
    }

    Path_Lever mTlv;
};

struct Editor_Hoist final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Hoist::Type>("Enum_HoistType",
        {
            {relive::Path_Hoist::Type::eNextFloor, "Next Floor"},
            {relive::Path_Hoist::Type::eOffScreen, "Off Screen"},
        });

        types.AddEnum<relive::Path_Hoist::GrabDirection>("Enum_HoistGrabDirection",
        {
            {relive::Path_Hoist::GrabDirection::eFacingLeft, "Facing Left"},
            {relive::Path_Hoist::GrabDirection::eFacingRight, "Facing Right"},
            {relive::Path_Hoist::GrabDirection::eFacingAnyDirection, "Facing Any Direction"},
        });
    }*/

public:
    Editor_Hoist()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        //r.Visit("Hoist Type", mTlv.mHoistType);
        //r.Visit("Grab Direction", mTlv.mGrabDirection);
        r.Visit("(AE) Scale", mTlv.mScale);
    }

    Path_Hoist mTlv;
};

struct Editor_BoomMachine final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_BoomMachine::NozzleSide>("Enum_BoomMachineNozzleSide",
        {
            {relive::Path_BoomMachine::NozzleSide::eRight, "Right"},
            {relive::Path_BoomMachine::NozzleSide::eLeft, "Left"},
        });
    }
    */

public:
    Editor_BoomMachine()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Nozzle Side", mTlv.mNozzleSide);
        r.Visit("Number Of Grenades", mTlv.mGrenadeAmount);
    }

    Path_BoomMachine mTlv;
};

struct Editor_Slig final : public MapObjectBase
{
public:
    Editor_Slig()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mData.mScale);
        //r.Visit("Start State", mTlv.mData.mStartState);
        //r.Visit("(AE) Death Mode", mTlv.mData.mDeathMode);
        //r.Visit("(AE) Can Beat", mTlv.mData.mCanBeat);
        //r.Visit("(AE) Can Z Shoot", mTlv.mData.mCanZShoot);
        r.Visit("Pause Time", mTlv.mData.mPauseTime);
        r.Visit("Pause Left Min", mTlv.mData.mPauseLeftMin);
        r.Visit("Pause Left Max", mTlv.mData.mPauseLeftMax);
        r.Visit("Pause Right Min", mTlv.mData.mPauseRightMin);
        r.Visit("Pause Right Max", mTlv.mData.mPauseRightMax);
        //r.Visit("Shoot Possessed Sligs", mTlv.mData.mShootPossessedSligs);
        r.Visit("Shoot On Sight Delay", mTlv.mData.mShootOnSightDelay);
        r.Visit("Bullet Shoot Count", mTlv.mData.mNumTimesToShoot);

        r.Visit("Code 1", mTlv.mData.mCode1);
        r.Visit("Code 2", mTlv.mData.mCode2);
        //r.Visit("Chase Abe When Spotted", mTlv.mData.mChaseAbeWhenSpotted);
        //r.Visit("Facing", mTlv.mData.mFacing);
        r.Visit("Panic Timeout", mTlv.mData.mPanicTimeout);
        r.Visit("Stop Chase Delay", mTlv.mData.mStopChaseDelay);
        r.Visit("Time To Wait Before Chase", mTlv.mData.mTimeToWaitBeforeChase);
        r.Visit("Slig Bound/Persist ID", mTlv.mData.mSligBoundId);
        r.Visit("Alerted Listen Time", mTlv.mData.mAlertedListenTime);
        r.Visit("Percent Say What", mTlv.mData.mPercentSayWhat);
        r.Visit("Percent Beat Mudokon", mTlv.mData.mPercentBeatMud);
        r.Visit("Z Shoot Delay", mTlv.mData.mZShootDelay);
        //r.Visit("Stay Awake", mTlv.mData.mStayAwake);
        r.Visit("Noise Wake Up Distance (Grids)", mTlv.mData.mNoiseWakeUpDistance);
        r.Visit("Slig Spawner Switch ID", mTlv.mData.mSligSpawnerSwitchId);
        //r.Visit("(AE) Unlimited Spawns", mTlv.mData.mUnlimitedSpawns); // HIDDEN
        r.Visit("(AO) Disabled Resources", mTlv.mData.mDisabledResourcesAO.Raw().all);
        r.Visit("(AE) Disabled Resources", mTlv.mData.mDisabledResourcesAE);
    }

    Path_Slig mTlv;
};

struct Editor_Fleech final : public MapObjectBase
{
public:
    Editor_Fleech()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Facing", mTlv.mFacing);
        //r.Visit("Asleep", mTlv.mAsleep);
        r.Visit("Attack Anger Increaser", mTlv.mAttackAngerIncreaser);
        r.Visit("Wake Up Switch ID", mTlv.mWakeUpSwitchId);
        //r.Visit("Hanging", mTlv.mHanging);
        r.Visit("Lost Target Timeout", mTlv.mLostTargetTimeout);
        //r.Visit("Goes To Sleep", mTlv.mGoesToSleep);
        r.Visit("Patrol Range (Grids)", mTlv.mPatrolRangeInGrids);
        r.Visit("Wake Up Switch Anger Value", mTlv.mWakeUpSwitchAngerValue);
        r.Visit("Can Wake Up Switch ID", mTlv.mCanWakeUpSwitchId);
        //r.Visit("Persistant", mTlv.mPersistant);
    }

    Path_Fleech mTlv;
};

struct Editor_EnemyStopper final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_EnemyStopper::StopDirection>("Enum_StopDirection",
        {
            {relive::Path_EnemyStopper::StopDirection::Left, "Left"},
            {relive::Path_EnemyStopper::StopDirection::Right, "Right"},
            {relive::Path_EnemyStopper::StopDirection::Both, "Both"},
        });
    }
    */

public:
    Editor_EnemyStopper()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Stop Direction", mTlv.mStopDirection);
        r.Visit("Switch ID", mTlv.mSwitchId);
    }

    Path_EnemyStopper mTlv;
};

struct Editor_Teleporter final : public MapObjectBase
{
public:
    Editor_Teleporter()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Teleporter Switch ID", mTlv.mTeleporterId);
        r.Visit("Other Teleporter Switch ID", mTlv.mOtherTeleporterId);
        r.Visit("Destination Camera", mTlv.mDestCamera);
        r.Visit("Destination Path", mTlv.mDestPath);
        //r.Visit("Destination Level", mTlv.mDestLevel);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Screen Change Effect", mTlv.mWipeEffect);
        r.Visit("Movie ID", mTlv.mMovieId);
        r.Visit("Electric X", mTlv.mElectricX);
        r.Visit("Electric Y", mTlv.mElectricY);
    }

    Path_Teleporter mTlv;
};

struct Editor_UXB final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_UXB::StartState>("Enum_Path_UXB_StartState",
        {
            {relive::Path_UXB::StartState::eOn, "On"},
            {relive::Path_UXB::StartState::eOff, "Off"},
        });
    }
    */
public:
    Editor_UXB()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Pattern Length (Max 4)", mTlv.mPatternLength);
        r.Visit("Pattern", mTlv.mPattern);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Start State", mTlv.mStartState);
    }

    Path_UXB mTlv;
};

struct Editor_LCDScreen final : public MapObjectBase
{
public:
    Editor_LCDScreen()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Message 1 ID", mTlv.mMessageId1);
        r.Visit("Random Message Min ID", mTlv.mMessageRandMinId);
        r.Visit("Random Message Max ID", mTlv.mMessageRandMaxId);

        r.Visit("(AE) Message 2 ID", mTlv.mMessageId2);
        r.Visit("(AE) Toggle Message Switch ID", mTlv.mToggleMessageSwitchId);
    }

    Path_LCDScreen mTlv;
};

struct Editor_Edge final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Edge::GrabDirection>("Enum_EdgeGrabDirection",
        {
            {relive::Path_Edge::GrabDirection::eFacingLeft, "Facing Left"},
            {relive::Path_Edge::GrabDirection::eFacingRight, "Facing Right"},
            {relive::Path_Edge::GrabDirection::eFacingAnyDirection, "Facing Any Direction"},
        });
    }
    */
public:
    Editor_Edge()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Grab Direction", mTlv.mGrabDirection);
        //r.Visit("Can Grab", mTlv.mCanGrab);
        r.Visit("(AE) Scale", mTlv.mScale);
    }

    Path_Edge mTlv;
};

struct Editor_StatusLight final : public MapObjectBase
{
public:
    Editor_StatusLight()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Input Switch ID", mTlv.mInputSwitchId);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Linked Status Light Switch ID 1", mTlv.mLinkedStatusLightSwitchId1);
        r.Visit("Linked Status Light Switch ID 2", mTlv.mLinkedStatusLightSwitchId2);
        r.Visit("Linked Status Light Switch ID 3", mTlv.mLinkedStatusLightSwitchId3);
        r.Visit("Linked Status Light Switch ID 4", mTlv.mLinkedStatusLightSwitchId4);
        r.Visit("Linked Status Light Switch ID 5", mTlv.mLinkedStatusLightSwitchId5);
        //r.Visit("Ignore Grid Snapping", mTlv.mIgnoreGridSnapping);
    }

    Path_StatusLight mTlv;
};

struct Editor_ShadowZone final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_ShadowZone::Scale>("Enum_ShadowZoneScale",
        {
            {relive::Path_ShadowZone::Scale::eBoth, "Both"},
            {relive::Path_ShadowZone::Scale::eHalf, "Half"},
            {relive::Path_ShadowZone::Scale::eFull, "Full"},
        });
    }
    */

public:
    Editor_ShadowZone()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("R", mTlv.mRGB.r);
        r.Visit("G", mTlv.mRGB.g);
        r.Visit("B", mTlv.mRGB.b);
        //r.Visit("Scale", mTlv.mScale);
    }

    Path_ShadowZone mTlv;
};

struct Editor_WorkWheel final : public MapObjectBase
{
public:
    Editor_WorkWheel()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Activation Time", mTlv.mActivationTime);
        r.Visit("Turn Off Time", mTlv.mTurnOffTime);
        //r.Visit("Turn Off When Stopped", mTlv.mTurnOffWhenStopped);
    }

    Path_WorkWheel mTlv;
};

struct Editor_MusicTrigger final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_MusicTrigger::MusicTriggerMusicType>("Enum_MusicTriggerMusicType",
        {
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eDrumAmbience, "Drum Ambience"},
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eDeathDrumShort, "Death Drum Short"},
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eSecretAreaLong, "Secret Area Long"},
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eSoftChase, "Soft Chase"},
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eIntenseChase, "Intense Chase"},
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eChime, "Chime"},
            {relive::Path_MusicTrigger::MusicTriggerMusicType::eSecretAreaShort, "Secret Area Short"},
        });

        types.AddEnum<relive::Path_MusicTrigger::TriggeredBy>("Enum_MusicTriggeredBy",
        {
            {relive::Path_MusicTrigger::TriggeredBy::eTimer, "Timer"},
            {relive::Path_MusicTrigger::TriggeredBy::eTouching, "Touching"},
            {relive::Path_MusicTrigger::TriggeredBy::eSwitchId, "(AO) Switch ID"},
            {relive::Path_MusicTrigger::TriggeredBy::eUnknown, "(AO) Unknown"},
        });
    }
    */
public:
    Editor_MusicTrigger()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Music Type", mTlv.mMusicType);
        //r.Visit("Triggered By", mTlv.mTriggeredBy);
        r.Visit("(AO) Switch ID", mTlv.mSwitchId);
        r.Visit("Music Delay", mTlv.mMusicDelay);
    }

    Path_MusicTrigger mTlv;
};

struct Editor_AbeStart final : public MapObjectBase
{
public:
    Editor_AbeStart()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_AbeStart mTlv;
};

struct Editor_SoftLanding final : public MapObjectBase
{
public:
    Editor_SoftLanding()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("(AE) Switch ID", mTlv.mSwitchId);
    }

    Path_SoftLanding mTlv;
};

struct Editor_WellExpress final : public MapObjectBase
{
public:
    Editor_WellExpress()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        // Path_WellBase
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("(AO) Other Well ID", mTlv.mOtherWellId);
        r.Visit("(AO) Animation ID", mTlv.mAnimId);  // leftover from AO well FG hack

        // Path_WellExpress
        r.Visit("Exit X", mTlv.mExitX);
        r.Visit("Exit Y", mTlv.mExitY);
        //r.Visit("Disabled Well Level", mTlv.mOffDestLevel);
        r.Visit("Disabled Well Path", mTlv.mOffDestPath);
        r.Visit("Disabled Well Camera", mTlv.mOffDestCamera);
        r.Visit("Disabled Well ID", mTlv.mOffOtherWellId);
        //r.Visit("Enabled Well Level", mTlv.mOnDestLevel);
        r.Visit("Enabled Well Path", mTlv.mOnDestPath);
        r.Visit("Enabled Well Camera", mTlv.mOnDestCamera);
        r.Visit("Enabled Well ID", mTlv.mOnOtherWellId);
        //r.Visit("Emit Leaves", mTlv.mEmitLeaves);
        r.Visit("Leaf X", mTlv.mLeafX);
        r.Visit("Leaf Y", mTlv.mLeafY);
        r.Visit("Movie ID", mTlv.mMovieId);
    }

    Path_WellExpress mTlv;
};

struct Editor_SlamDoor final : public MapObjectBase
{
public:
    Editor_SlamDoor()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Start Shut", mTlv.mStartClosed);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Flip On Y Axis", mTlv.mFlipY);
        //r.Visit("Delete", mTlv.mDelete);
    }

    Path_SlamDoor mTlv;
};

struct Editor_HandStone final : public MapObjectBase
{
public:
    Editor_HandStone()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Camera ID 1", mTlv.mCameraId1);
        r.Visit("Camera ID 2", mTlv.mCameraId2);
        r.Visit("Camera ID 3", mTlv.mCameraId3);
        r.Visit("(AE) Trigger Switch ID", mTlv.mTriggerSwitchId);

        //r.Visit("(AO) Level 1", mTlv.mLevel1);
        r.Visit("(AO) Path 1", mTlv.mPath1);
        //r.Visit("(AO) Level 2", mTlv.mLevel2);
        r.Visit("(AO) Path 2", mTlv.mPath2);
        //r.Visit("(AO) Level 3", mTlv.mLevel3);
        r.Visit("(AO) Path 3", mTlv.mPath3);
    }

    Path_HandStone mTlv;
};

struct Editor_LaughingGas final : public MapObjectBase
{
public:
    Editor_LaughingGas()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Is Laughing Gas", mTlv.mLaughingGas);
        r.Visit("Laughing Gas Switch ID", mTlv.mLaughingGasSwitchId);
        r.Visit("Red %", mTlv.mRedPercent);
        r.Visit("Green %", mTlv.mGreenPercent);
        r.Visit("Blue %", mTlv.mBluePercent);
    }

    Path_LaughingGas mTlv;
};

struct Editor_InvisibleSwitch final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_InvisibleSwitch::InvisibleSwitchScale>("Enum_InvisibleSwitchScale",
        {
            {relive::Path_InvisibleSwitch::InvisibleSwitchScale::eHalf, "Half"},
            {relive::Path_InvisibleSwitch::InvisibleSwitchScale::eFull, "Full"},
            {relive::Path_InvisibleSwitch::InvisibleSwitchScale::eAny, "Any"},
        });
    }*/

public:
    Editor_InvisibleSwitch()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Action", mTlv.mAction);
        r.Visit("Activation Delay", mTlv.mActivationDelay);
        //r.Visit("Set Off Alarm", mTlv.mSetOffAlarm);
        //r.Visit("Scale", mTlv.mScale);
    }

    Path_InvisibleSwitch mTlv;
};

struct Editor_Water final : public MapObjectBase
{
public:
    Editor_Water()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Max Drops", mTlv.mMaxDrops);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Splash Time", mTlv.mSplashTime);
        r.Visit("Splash X Velocity", mTlv.mSplashVelX);
        r.Visit("Water Duration", mTlv.mWaterDuration);
    }

    Path_Water mTlv;
};

struct Editor_GasEmitter final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_GasEmitter::GasColour>("Enum_GasColour",
        {
            {relive::Path_GasEmitter::GasColour::eYellow, "Yellow"},
            {relive::Path_GasEmitter::GasColour::eRed, "Red"},
            {relive::Path_GasEmitter::GasColour::eGreen, "Green"},
            {relive::Path_GasEmitter::GasColour::eBlue, "Blue"},
            {relive::Path_GasEmitter::GasColour::eWhite, "White"},
        });
    }*/

public:
    Editor_GasEmitter()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("(AE) Switch ID", mTlv.mSwitchId);
        //r.Visit("(AE) Colour", mTlv.mColour);
    }

    Path_GasEmitter mTlv;
};

struct Editor_BackgroundAnimation final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<::relive::Path_BackgroundAnimation::BgAnimSounds>("Enum_BackgroundAnimation_BgAnimSounds",
        {
            {relive::Path_BackgroundAnimation::BgAnimSounds::eNone, "None"},
            {relive::Path_BackgroundAnimation::BgAnimSounds::eFire, "Fire"},
        });

        types.AddEnum<relive::Path_BackgroundAnimation::Layer>("Enum_Layer",
        {
            {relive::Path_BackgroundAnimation::Layer::eLayer0, "Layer 0"},
            {relive::Path_BackgroundAnimation::Layer::eLayer2, "Layer 2"},
        });

        types.AddEnum<relive::TBlendModes>("Enum_relive::TBlendModes",
        {
            {relive::TBlendModes::eBlend_0, "Blend 0"},
            {relive::TBlendModes::eBlend_1, "Blend 1"},
            {relive::TBlendModes::eBlend_2, "Blend 2"},
            {relive::TBlendModes::eBlend_3, "Blend 3"},
        });
    }
    */

public:
    Editor_BackgroundAnimation()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Animation ID", mTlv.mAnimId);
        //r.Visit("Is Semi Trans", mTlv.mIsSemiTrans);
        //r.Visit("Semi Trans Mode", mTlv.mSemiTransMode);
        //r.Visit("(AO) Sound Effect", mTlv.mSoundEffect);
        //r.Visit("(AE) Layer", mTlv.mLayer);
    }

    Path_BackgroundAnimation mTlv;
};

struct Editor_LiftPoint final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_LiftPoint::LiftPointStopType>("Enum_LiftPointStopType",
        {
            {relive::Path_LiftPoint::LiftPointStopType::eTopFloor, "Top Floor"},
            {relive::Path_LiftPoint::LiftPointStopType::eBottomFloor, "Bottom Floor"},
            {relive::Path_LiftPoint::LiftPointStopType::eMiddleFloor, "Middle Floor"},
            {relive::Path_LiftPoint::LiftPointStopType::eMiddleLockFloor, "Middle Lock Floor"},
            {relive::Path_LiftPoint::LiftPointStopType::eStartPointOnly, "Start Point Only"},
        });
    }*/

public:
    Editor_LiftPoint()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Lift Point ID", mTlv.mLiftPointId);
        //r.Visit("Start Point", mTlv.mIsStartPoint);
        //r.Visit("Lift Point Stop Type", mTlv.mLiftPointStopType);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Ignore Lift Mover", mTlv.mIgnoreLiftMover);
    }

    Path_LiftPoint mTlv;
};

struct Editor_PullRingRope final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_PullRingRope::PullRingSwitchSound>("Enum_PullRingSwitchSound",
        {
            {relive::Path_PullRingRope::PullRingSwitchSound::eNone, "None"},
            {relive::Path_PullRingRope::PullRingSwitchSound::eWellExit, "Well Exit"},
            {relive::Path_PullRingRope::PullRingSwitchSound::eRingBellHammer, "Ring Unknown Trigger"},
            {relive::Path_PullRingRope::PullRingSwitchSound::eDoorEffect, "Door Effect"},
        });

        types.AddEnum<relive::Path_PullRingRope::PullRingSoundDirection>("Enum_PullRingSoundDirection",
        {
            {relive::Path_PullRingRope::PullRingSoundDirection::eLeftAndRight, "Left And Right"},
            {relive::Path_PullRingRope::PullRingSoundDirection::eLeft, "Left"},
            {relive::Path_PullRingRope::PullRingSoundDirection::eRight, "Right"},
        });
    }*/

public:
    Editor_PullRingRope()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Action", mTlv.mAction);
        r.Visit("Rope Length", mTlv.mRopeLength);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("On Sound", mTlv.mOnSound);
        //r.Visit("Off Sound", mTlv.mOffSound);
        //r.Visit("Sound Direction", mTlv.mSoundDirection);
    }

    Path_PullRingRope mTlv;
};

struct Editor_MultiSwitchController final : public MapObjectBase
{
public:
    Editor_MultiSwitchController()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Output Switch ID", mTlv.mOutputSwitchId);
        //r.Visit("Action", mTlv.mAction);
        r.Visit("On/Off Delay", mTlv.mOnOffDelay);
        r.Visit("Input Switch ID 1", mTlv.mInputSwitchId1);
        r.Visit("Input Switch ID 2", mTlv.mInputSwitchId2);
        r.Visit("Input Switch ID 3", mTlv.mInputSwitchId3);
        r.Visit("Input Switch ID 4", mTlv.mInputSwitchId4);
        r.Visit("Input Switch ID 5", mTlv.mInputSwitchId5);
        r.Visit("Input Switch ID 6", mTlv.mInputSwitchId6);
    }

    Path_MultiSwitchController mTlv;
};

struct Editor_SecurityOrb final : public MapObjectBase
{
public:
    Editor_SecurityOrb()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
    }

    Path_SecurityOrb mTlv;
};

struct Editor_InvisibleZone final : public MapObjectBase
{
public:
    Editor_InvisibleZone()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_InvisibleZone mTlv;
};

struct Editor_ContinuePoint final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_ContinuePoint::Scale>("Enum_ContinuePointScale",
        {
            {relive::Path_ContinuePoint::Scale::eNone, "None"},
            {relive::Path_ContinuePoint::Scale::eHalf, "Half"},
            {relive::Path_ContinuePoint::Scale::eFull, "Full"},
        });
    }*/

public:
    Editor_ContinuePoint()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("(AO) Zone Number", mTlv.mZoneNumber);
        //r.Visit("(AO) Clear From ID", mTlv.mClearFromId);
        //r.Visit("(AO) Clear To ID", mTlv.mClearToId);
        //r.Visit("(AO) Elum Restarts", mTlv.mElumRestarts);
        //r.Visit("(AO) Abe Spawn Dir", mTlv.mAbeSpawnDir);
        //r.Visit("(AE) Scale", mTlv.mScale);
        r.Visit("(AE) Save File ID", mTlv.mSaveFileId);
    }

    Path_ContinuePoint mTlv;
};

struct Editor_WheelSyncer final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_WheelSyncer::OutputRequirement>("Enum_WheelSyncerOutputRequirement",
        {
            {relive::Path_WheelSyncer::OutputRequirement::eAllOn, "All On"},
            {relive::Path_WheelSyncer::OutputRequirement::e1OnAnd2Off, "1 On And 2 Off"},
            {relive::Path_WheelSyncer::OutputRequirement::e1Or2On, "1 Or 2 On"},
            {relive::Path_WheelSyncer::OutputRequirement::e1OnOr2Off, "1 On Or 2 Off"},
        });
    }
    */

public:
    Editor_WheelSyncer()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Input Switch ID 1", mTlv.mInputSwitchId1);
        r.Visit("Input Switch ID 2", mTlv.mInputSwitchId2);
        r.Visit("Output Switch ID", mTlv.mOutputSwitchId);
        //r.Visit("Output Requirement", mTlv.mOutputRequirement);
        r.Visit("Input Switch ID 3", mTlv.mInputSwitchId3);
        r.Visit("Input Switch ID 4", mTlv.mInputSwitchId4);
        r.Visit("Input Switch ID 5", mTlv.mInputSwitchId5);
        r.Visit("Input Switch ID 6", mTlv.mInputSwitchId6);
    }

    Path_WheelSyncer mTlv;
};

struct Editor_LevelLoader final : public MapObjectBase
{
public:
    Editor_LevelLoader()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Destination Level", mTlv.mDestLevel);
        r.Visit("Destination Path", mTlv.mDestPath);
        r.Visit("Destination Camera", mTlv.mDestCamera);
        r.Visit("Movie ID", mTlv.mMovieId);
    }

    Path_LevelLoader mTlv;
};

struct Editor_Pulley final : public MapObjectBase
{
public:
    Editor_Pulley()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_Pulley mTlv;
};

struct Editor_FlyingSlig final : public MapObjectBase
{
public:
    Editor_FlyingSlig()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Spawn Delay State", mTlv.mSpawnDelayState);
        r.Visit("Spawn Move Delay", mTlv.mSpawnMoveDelay);
        r.Visit("Patrol Pause Min", mTlv.mPatrolPauseMin);
        r.Visit("Patrol Pause Max", mTlv.mPatrolPauseMax);
        //r.Visit("Start Direction", mTlv.mFacing);
        r.Visit("Panic Delay", mTlv.mPanicDelay);
        r.Visit("Give Up Chase Delay", mTlv.mGiveUpChaseDelay);
        r.Visit("Pre-chase Delay", mTlv.mPrechaseDelay);
        r.Visit("Slig Bound/Persist ID", mTlv.mSligBoundId);
        r.Visit("Alerted Listen Time", mTlv.mAlertedListenTime);
        r.Visit("Spawner Switch ID", mTlv.mSpawnerSwitchId);
        r.Visit("Grenade Delay", mTlv.mGrenadeDelay);
        r.Visit("Max Velocity", mTlv.mMaxVelocity);
        r.Visit("Launch Grenade Switch ID", mTlv.mLaunchGrenadeSwitchId);
        //r.Visit("Persistant", mTlv.mPersistant);
    }

    Path_FlyingSlig mTlv;
};

struct Editor_FlyingSligSpawner final : public MapObjectBase
{
public:
    Editor_FlyingSligSpawner()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Spawn Delay State", mTlv.mSpawnDelayState);
        r.Visit("Spawn Move Delay", mTlv.mSpawnMoveDelay);
        r.Visit("Patrol Pause Min", mTlv.mPatrolPauseMin);
        r.Visit("Patrol Pause Max", mTlv.mPatrolPauseMax);
        //r.Visit("Start Direction", mTlv.mFacing);
        r.Visit("Panic Delay", mTlv.mPanicDelay);
        r.Visit("Give Up Chase Delay", mTlv.mGiveUpChaseDelay);
        r.Visit("Pre-chase Delay", mTlv.mPrechaseDelay);
        r.Visit("Slig Bound/Persist ID", mTlv.mSligBoundId);
        r.Visit("Listen Time", mTlv.mAlertedListenTime);
        r.Visit("Spawner Switch ID", mTlv.mSpawnerSwitchId);
        r.Visit("Grenade Delay", mTlv.mGrenadeDelay);
        r.Visit("Max Velocity", mTlv.mMaxVelocity);
        r.Visit("Launch Grenade Switch ID", mTlv.mLaunchGrenadeSwitchId);
        //r.Visit("Persistant", mTlv.mPersistant);
    }

    Path_FlyingSligSpawner mTlv;
};

struct Editor_DeathDrop final : public MapObjectBase
{
public:
    Editor_DeathDrop()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_DeathDrop mTlv;
};

struct Editor_SligSpawner final : public MapObjectBase
{
public:
    Editor_SligSpawner()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mData.mScale);
        //r.Visit("Start State", mTlv.mData.mStartState);
        //r.Visit("(AE) Death Mode", mTlv.mData.mDeathMode);
        //r.Visit("(AE) Can Beat", mTlv.mData.mCanBeat);
        //r.Visit("(AE) Can Z Shoot", mTlv.mData.mCanZShoot);
        r.Visit("Pause Time", mTlv.mData.mPauseTime);
        r.Visit("Pause Left Min", mTlv.mData.mPauseLeftMin);
        r.Visit("Pause Left Max", mTlv.mData.mPauseLeftMax);
        r.Visit("Pause Right Min", mTlv.mData.mPauseRightMin);
        r.Visit("Pause Right Max", mTlv.mData.mPauseRightMax);
        //r.Visit("Shoot Possessed Sligs", mTlv.mData.mShootPossessedSligs);
        r.Visit("Shoot On Sight Delay", mTlv.mData.mShootOnSightDelay);
        r.Visit("Bullet Shoot Count", mTlv.mData.mNumTimesToShoot);

        r.Visit("Code 1", mTlv.mData.mCode1);
        r.Visit("Code 2", mTlv.mData.mCode2);
        //r.Visit("Chase Abe When Spotted", mTlv.mData.mChaseAbeWhenSpotted);
        //r.Visit("Facing", mTlv.mData.mFacing);
        r.Visit("Panic Timeout", mTlv.mData.mPanicTimeout);
        r.Visit("Stop Chase Delay", mTlv.mData.mStopChaseDelay);
        r.Visit("Time To Wait Before Chase", mTlv.mData.mTimeToWaitBeforeChase);
        r.Visit("Slig Bound/Persist ID", mTlv.mData.mSligBoundId);
        r.Visit("Alerted Listen Time", mTlv.mData.mAlertedListenTime);
        r.Visit("Percent Say What", mTlv.mData.mPercentSayWhat);
        r.Visit("Percent Beat Mudokon", mTlv.mData.mPercentBeatMud);
        r.Visit("Z Shoot Delay", mTlv.mData.mZShootDelay);
        //r.Visit("Stay Awake", mTlv.mData.mStayAwake);
        r.Visit("Noise Wake Up Distance (Grids)", mTlv.mData.mNoiseWakeUpDistance);
        r.Visit("Slig Spawner Switch ID", mTlv.mData.mSligSpawnerSwitchId);
        //r.Visit("(AE) Unlimited Spawns", mTlv.mData.mUnlimitedSpawns); // HIDDEN
        r.Visit("(AO) Disabled Resources", mTlv.mData.mDisabledResourcesAO.Raw().all);
        r.Visit("(AE) Disabled Resources", mTlv.mData.mDisabledResourcesAE);
    }

    Path_SligSpawner mTlv;
};

struct Editor_SligBoundLeft final : public MapObjectBase
{
public:
    Editor_SligBoundLeft()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_SligBoundLeft mTlv;
};

struct Editor_SligBoundRight final : public MapObjectBase
{
public:
    Editor_SligBoundRight()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_SligBoundRight mTlv;
};

struct Editor_SligPersist final : public MapObjectBase
{
public:
    Editor_SligPersist()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_SligPersist mTlv;
};

struct Editor_ZSligCover final : public MapObjectBase
{
public:
    Editor_ZSligCover()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_ZSligCover mTlv;
};

struct Editor_WellLocal final : public MapObjectBase
{
public:
    Editor_WellLocal()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        // Path_WellBase
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("(AO) Other Well ID", mTlv.mOtherWellId);     // hidden because this is only used by the well express
        r.Visit("(AO) Animation ID (Unused?)", mTlv.mAnimId); // leftover from AO well FG hack
        r.Visit("(AO) Exit X", mTlv.mExitX);
        r.Visit("(AO) Exit Y", mTlv.mExitY);

        // Path_WellLocal
        r.Visit("(AO) Disabled XPos", mTlv.mOffDestX);
        r.Visit("(AO) Disabled YPos", mTlv.mOffDestY);
        r.Visit("Enabled XPos", mTlv.mOnDestX);
        r.Visit("Enabled YPos", mTlv.mOnDestY);
        //r.Visit("Emit Leaves", mTlv.mEmitLeaves);
        r.Visit("Leaf XPos", mTlv.mLeafX);
        r.Visit("Leaf YPos", mTlv.mLeafY);
    }

    Path_WellLocal mTlv;
};

struct Editor_BrewMachine final : public MapObjectBase
{
public:
    Editor_BrewMachine()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Brew Count", mTlv.mBrewCount);
    }

    Path_BrewMachine mTlv;
};

struct Editor_Drill final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Drill::DrillBehavior>("Enum_DrillBehavior",
        {
            {relive::Path_Drill::DrillBehavior::eNotInteractable, "Not Interactable"},
            {relive::Path_Drill::DrillBehavior::eToggle, "Toggle"},
            {relive::Path_Drill::DrillBehavior::eUse, "Use"},
        });

        types.AddEnum<relive::Path_Drill::DrillDirection>("Enum_DrillDirection",
        {
            {relive::Path_Drill::DrillDirection::eDown, "Down"},
            {relive::Path_Drill::DrillDirection::eRight, "Right"},
            {relive::Path_Drill::DrillDirection::eLeft, "Left"},
        });
    }
    */

public:
    Editor_Drill()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Min Off Time", mTlv.mOnMinPauseTime);
        r.Visit("Max Off Time", mTlv.mOnMaxPauseTime);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Behavior", mTlv.mDrillBehavior);
        r.Visit("Speed", mTlv.mOnSpeed);
        //r.Visit("Start State On", mTlv.mStartStateOn);
        r.Visit("Off Speed", mTlv.mOffSpeed);
        r.Visit("Min Off Time Speed Change", mTlv.mOffMinPauseTime);
        r.Visit("Max Off Time Speed Change", mTlv.mOffMaxPauseTime);
        //r.Visit("Start Position Bottom", mTlv.mStartPositionBottom);
        //r.Visit("Start Direction", mTlv.mDrillDirection);
    }

    Path_Drill mTlv;
};

struct Editor_Mine final : public MapObjectBase
{
public:
    Editor_Mine()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Persist Offscreen", mTlv.mPersistOffscreen);
    }

    Path_Mine mTlv;
};

struct Editor_Slog final : public MapObjectBase
{
public:
    Editor_Slog()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Start Direction", mTlv.mFacing);
        //r.Visit("Asleep", mTlv.mAsleep);
        r.Visit("Wake Up Anger", mTlv.mWakeUpAnger);
        r.Visit("Bark Anger", mTlv.mBarkAnger);
        r.Visit("Chase Anger", mTlv.mChaseAnger);
        r.Visit("Chase Delay", mTlv.mChaseDelay);
        r.Visit("Anger Switch ID", mTlv.mAngerSwitchId);
        r.Visit("(AE) Bone Eating Time", mTlv.mBoneEatingTime);
    }

    Path_Slog mTlv;
};

struct Editor_ResetPath final : public MapObjectBase
{
public:
    Editor_ResetPath()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Clear Ids", mTlv.mClearIds);
        r.Visit("From", mTlv.mFrom);
        r.Visit("To", mTlv.mTo);
        r.Visit("Exclude", mTlv.mExclude);
        //r.Visit("Clear Objects", mTlv.mClearObjects);
        r.Visit("Path", mTlv.mPath);
        //r.Visit("(AE) Enabled", mTlv.mEnabled);
    }

    Path_ResetPath mTlv;
};

struct Editor_TrapDoor final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_TrapDoor::StartState>("Enum_TrapDoorStartState",
        {{relive::Path_TrapDoor::StartState::eOpen, "Open"},
        {relive::Path_TrapDoor::StartState::eClosed, "Closed"}});
    }
    */

public:
    Editor_TrapDoor()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Start State", mTlv.mStartState);
        //r.Visit("Self Closing", mTlv.mSelfClosing);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Direction", mTlv.mDirection);
        r.Visit("X Offset", mTlv.mXOff);
        r.Visit("(AE) Stay Open Time", mTlv.mStayOpenTime);
    }

    Path_TrapDoor mTlv;
};

struct Editor_PathTransition final : public MapObjectBase
{
public:
    Editor_PathTransition()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Next Level", mTlv.mNextLevel);
        r.Visit("Next Path", mTlv.mNextPath);
        r.Visit("Next Camera", mTlv.mNextCamera);
        r.Visit("Movie ID", mTlv.mMovieId);
        r.Visit("Wipe Effect", mTlv.mWipeEffect);
        r.Visit("Next Path Scale", mTlv.mNextPathScale);
    }

    Path_PathTransition mTlv;
};

struct Editor_LiftMover final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_LiftMover::YDirection>("Enum_LiftMoverYDirection",
        {
            {relive::Path_LiftMover::YDirection::eDown, "Down"},
            {relive::Path_LiftMover::YDirection::eUp, "Up"},
        });
    }*/

public:
    Editor_LiftMover()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Lift Mover Switch ID", mTlv.mLiftMoverSwitchId);
        r.Visit("Target Lift Point ID", mTlv.mTargetLiftPointId);
        //r.Visit("Move Direction", mTlv.mMoveDirection);
    }

    Path_LiftMover mTlv;
};

struct Editor_RockSack final : public MapObjectBase
{
public:
    Editor_RockSack()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Rock Fall Direction", mTlv.mRockFallDirection);
        r.Visit("X Velocity", mTlv.mVelX);
        r.Visit("Y Velocity", mTlv.mVelY);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Rock Amount", mTlv.mRockAmount);
    }

    Path_RockSack mTlv;
};

struct Editor_TimerTrigger final : public MapObjectBase
{
public:
    Editor_TimerTrigger()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Input Switch ID", mTlv.mInputSwitchId);
        r.Visit("Activation Delay", mTlv.mActivationDelay);
        r.Visit("Output Switch ID 1", mTlv.mOutputSwitchId1);
        r.Visit("Output Switch ID 2", mTlv.mOutputSwitchId2);
        r.Visit("Output Switch ID 3", mTlv.mOutputSwitchId3);
        r.Visit("Output Switch ID 4", mTlv.mOutputSwitchId4);
    }

    Path_TimerTrigger mTlv;
};

struct Editor_MotionDetector final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_MotionDetector::InitialMoveDirection>("Enum_InitialMoveDirection",
        {
            {relive::Path_MotionDetector::InitialMoveDirection::eRight, "Right"},
            {relive::Path_MotionDetector::InitialMoveDirection::eLeft, "Left"},
        });
    }*/

public:
    Editor_MotionDetector()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Device X", mTlv.mDeviceX);
        r.Visit("Device Y", mTlv.mDeviceY);
        r.Visit("Speed", mTlv.mSpeedx256); // Note the potential scaling factor of 256 based on field name
        //r.Visit("Initial Move Direction", mTlv.mInitialMoveDirection);
        //r.Visit("Draw Flare", mTlv.mDrawFlare);
        r.Visit("Disable Switch ID", mTlv.mDisableSwitchId);
        r.Visit("Alarm Switch ID", mTlv.mAlarmSwitchId);
        r.Visit("Alarm Duration", mTlv.mAlarmDuration);
    }

    Path_MotionDetector mTlv;
};

struct Editor_MineCar final : public MapObjectBase
{
public:
    Editor_MineCar()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
    }

    Path_MineCar mTlv;
};

struct Editor_ExplosionSet final : public MapObjectBase
{
public:
    Editor_ExplosionSet()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Start Enabled", mTlv.mStartEnabled);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Spawn Assets", mTlv.mSpawnAssets);
        r.Visit("Start Delay", mTlv.mStartDelay);
        //r.Visit("Start Direction", mTlv.mStartDirection);
        r.Visit("Asset Interval", mTlv.mAssetInterval);
        r.Visit("Grid Spacing", mTlv.mGridSpacing);
        r.Visit("Increasing Grid Spacing", mTlv.mIncreasingGridSpacing);
        r.Visit("Scale", mTlv.mScale);
    }

    Path_ExplosionSet mTlv;
};

struct Editor_ColourfulMeter final : public MapObjectBase
{
public:
    Editor_ColourfulMeter()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Number Of Meter Bars", mTlv.mNumberOfMeterBars);
        r.Visit("Mines Alarm Countdown (Seconds)", mTlv.mMinesAlarmCountdown);
        //r.Visit("Start Filled", mTlv.mStartFilled);
    }

    Path_ColourfulMeter mTlv;
};

struct Editor_Alarm final : public MapObjectBase
{
public:
    Editor_Alarm()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Duration", mTlv.mAlarmDuration);
    }

    Path_Alarm mTlv;
};

struct Editor_DemoSpawnPoint final : public MapObjectBase
{
public:
    Editor_DemoSpawnPoint()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_DemoSpawnPoint mTlv;
};

struct Editor_SlapLock final : public MapObjectBase
{
public:
    Editor_SlapLock()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Target Tomb ID 1", mTlv.mTargetTombSwitchId1);
        r.Visit("Target Tomb ID 2", mTlv.mTargetTombSwitchId2);
        //r.Visit("Has Ghost", mTlv.mHasGhost);
        //r.Visit("Give Invisibility Power-up", mTlv.mGiveInvisibilityPowerup);
        r.Visit("Invisibility Duration", mTlv.mInvisibilityDuration);
        r.Visit("Toggle Switch ID", mTlv.mSlapOutputSwitchId);
    }

    Path_SlapLock mTlv;
};

struct Editor_Slurg final : public MapObjectBase
{
public:
    Editor_Slurg()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Time Until Turning Around", mTlv.mMovingTimer);
        //r.Visit("Start Direction", mTlv.mFacing);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID (increment by 1 on death)", mTlv.mSlurgSwitchId);
    }

    Path_Slurg mTlv;
};

struct Editor_DoorBlocker final : public MapObjectBase
{
public:
    Editor_DoorBlocker()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
    }

    Path_DoorBlocker mTlv;
};

struct Editor_Dove final : public MapObjectBase
{
public:
    Editor_Dove()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Dove Count", mTlv.mDoveCount);
        //r.Visit("Pixel Perfect", mTlv.mPixelPerfect);
        r.Visit("Scale", mTlv.mScale);
    }

    Path_Dove mTlv;
};

struct Editor_BirdPortalExit final : public MapObjectBase
{
public:
    Editor_BirdPortalExit()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Exit Direction", mTlv.mExitSide);
        r.Visit("Scale", mTlv.mScale);
    }

    Path_BirdPortalExit mTlv;
};

struct Editor_DoorFlame final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_DoorFlame::Colour>("Enum_DoorFlameColour",
        {
            {relive::Path_DoorFlame::Colour::eDefault, "Default"},
            {relive::Path_DoorFlame::Colour::eRed, "Red"},
            {relive::Path_DoorFlame::Colour::eGreen, "Green"},
            {relive::Path_DoorFlame::Colour::eBlue, "Blue"},
        });
    }*/

public:
    Editor_DoorFlame()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Colour", mTlv.mColour);
    }

    Path_DoorFlame mTlv;
};

struct Editor_TrainDoor final : public MapObjectBase
{
public:
    Editor_TrainDoor()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Direction", mTlv.mDirection);
    }

    Path_TrainDoor mTlv;
};

struct Editor_Greeter final : public MapObjectBase
{
public:
    Editor_Greeter()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Motion Detector Speed", mTlv.mMotionDetectorSpeed);
        //r.Visit("Facing", mTlv.mFacing);
    }

    Path_Greeter mTlv;
};

struct Editor_ScrabBoundLeft final : public MapObjectBase
{
public:
    Editor_ScrabBoundLeft()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_ScrabBoundLeft mTlv;
};

struct Editor_ScrabBoundRight final : public MapObjectBase
{
public:
    Editor_ScrabBoundRight()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_ScrabBoundRight mTlv;
};

struct Editor_CreditsController final : public MapObjectBase
{
public:
    Editor_CreditsController()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_CreditsController mTlv;
};

struct Editor_MovieStone final : public MapObjectBase
{
public:
    Editor_MovieStone()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Movie ID", mTlv.mMovieId);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("(AE) Trigger Switch ID", mTlv.mTriggerSwitchId);
    }

    Path_MovieStone mTlv;
};

struct Editor_MovingBomb final : public MapObjectBase
{
public:
    Editor_MovingBomb()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Speed", mTlv.mSpeed);
        r.Visit("Start Moving Switch ID", mTlv.mStartMovingSwitchId);
        //r.Visit("Triggered By Alarm", mTlv.mTriggeredByAlarm);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Start Speed", mTlv.mStartSpeed);
        //r.Visit("Persist Offscreen", mTlv.mPersistOffscreen);
    }

    Path_MovingBomb mTlv;
};

struct Editor_MovingBombStopper final : public MapObjectBase
{
public:
    Editor_MovingBombStopper()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Min Stop Time", mTlv.mMinStopTime);
        r.Visit("Max Stop Time", mTlv.mMaxStopTime);
    }

    Path_MovingBombStopper mTlv;
};

struct Editor_SecurityDoor final : public MapObjectBase
{
public:
    Editor_SecurityDoor()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Code 1", mTlv.mCode1);
        r.Visit("Code 2", mTlv.mCode2);
        r.Visit("X Position", mTlv.mXPos);
        r.Visit("Y Position", mTlv.mYPos);
    }

    Path_SecurityDoor mTlv;
};

struct Editor_CrawlingSlig final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_CrawlingSlig::StartState>("Enum_CrawlingSligState",
        {
            {relive::Path_CrawlingSlig::StartState::eSleeping, "Sleeping"},
            {relive::Path_CrawlingSlig::StartState::eAwake, "Awake"},
        });

        types.AddEnum<relive::Path_CrawlingSlig::CrawlDirection>("Enum_CrawlDirection",
        {
            {relive::Path_CrawlingSlig::CrawlDirection::eLeft, "Left"},
            {relive::Path_CrawlingSlig::CrawlDirection::eRight, "Right"},
            {relive::Path_CrawlingSlig::CrawlDirection::eRandom, "Random"},
        });
    }*/

public:
    Editor_CrawlingSlig()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Start State", mTlv.mStartState);
        //r.Visit("Crawl Direction", mTlv.mCrawlDirection);
        r.Visit("Panic Switch ID", mTlv.mPanicSwitchId);
        //r.Visit("Respawn On Death", mTlv.mRespawnOnDeath);
    }

    Path_CrawlingSlig mTlv;
};

struct Editor_SligGetPants final : public MapObjectBase
{
public:
    Editor_SligGetPants()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mData.mScale);
        //r.Visit("Start State", mTlv.mData.mStartState);
        //r.Visit("(AE) Death Mode", mTlv.mData.mDeathMode);
        //r.Visit("(AE) Can Beat", mTlv.mData.mCanBeat);
        //r.Visit("(AE) Can Z Shoot", mTlv.mData.mCanZShoot);
        r.Visit("Pause Time", mTlv.mData.mPauseTime);
        r.Visit("Pause Left Min", mTlv.mData.mPauseLeftMin);
        r.Visit("Pause Left Max", mTlv.mData.mPauseLeftMax);
        r.Visit("Pause Right Min", mTlv.mData.mPauseRightMin);
        r.Visit("Pause Right Max", mTlv.mData.mPauseRightMax);
        //r.Visit("Shoot Possessed Sligs", mTlv.mData.mShootPossessedSligs);
        r.Visit("Shoot On Sight Delay", mTlv.mData.mShootOnSightDelay);
        r.Visit("Bullet Shoot Count", mTlv.mData.mNumTimesToShoot);

        r.Visit("Code 1", mTlv.mData.mCode1);
        r.Visit("Code 2", mTlv.mData.mCode2);
        //r.Visit("Chase Abe When Spotted", mTlv.mData.mChaseAbeWhenSpotted);
        //r.Visit("Facing", mTlv.mData.mFacing);
        r.Visit("Panic Timeout", mTlv.mData.mPanicTimeout);
        r.Visit("Stop Chase Delay", mTlv.mData.mStopChaseDelay);
        r.Visit("Time To Wait Before Chase", mTlv.mData.mTimeToWaitBeforeChase);
        r.Visit("Slig Bound/Persist ID", mTlv.mData.mSligBoundId);
        r.Visit("Alerted Listen Time", mTlv.mData.mAlertedListenTime);
        r.Visit("Percent Say What", mTlv.mData.mPercentSayWhat);
        r.Visit("Percent Beat Mudokon", mTlv.mData.mPercentBeatMud);
        r.Visit("Z Shoot Delay", mTlv.mData.mZShootDelay);
        //r.Visit("Stay Awake", mTlv.mData.mStayAwake);
        r.Visit("Noise Wake Up Distance (Grids)", mTlv.mData.mNoiseWakeUpDistance);
        r.Visit("Slig Spawner Switch ID", mTlv.mData.mSligSpawnerSwitchId);
        //r.Visit("(AE) Unlimited Spawns", mTlv.mData.mUnlimitedSpawns); // HIDDEN
        r.Visit("(AO) Disabled Resources", mTlv.mData.mDisabledResourcesAO.Raw().all);
        r.Visit("(AE) Disabled Resources", mTlv.mData.mDisabledResourcesAE);
    }

    Path_SligGetPants mTlv;
};

struct Editor_SligGetWings final : public MapObjectBase
{
public:
    Editor_SligGetWings()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Spawn Delay State", mTlv.mSpawnDelayState);
        r.Visit("Spawn Move Delay", mTlv.mSpawnMoveDelay);
        r.Visit("Patrol Pause Min", mTlv.mPatrolPauseMin);
        r.Visit("Patrol Pause Max", mTlv.mPatrolPauseMax);
        //r.Visit("Start Direction", mTlv.mFacing);
        r.Visit("Panic Delay", mTlv.mPanicDelay);
        r.Visit("Give Up Chase Delay", mTlv.mGiveUpChaseDelay);
        r.Visit("Pre-chase Delay", mTlv.mPrechaseDelay);
        r.Visit("Slig Bound/Persist ID", mTlv.mSligBoundId);
        r.Visit("Alerted Listen Time", mTlv.mAlertedListenTime);
        r.Visit("Spawner Switch ID", mTlv.mSpawnerSwitchId);
        r.Visit("Grenade Delay", mTlv.mGrenadeDelay);
        r.Visit("Max Velocity", mTlv.mMaxVelocity);
        r.Visit("Launch Grenade Switch ID", mTlv.mLaunchGrenadeSwitchId);
        //r.Visit("Persistant", mTlv.mPersistant);
    }

    Path_SligGetWings mTlv;
};

struct Editor_CrawlingSligButton final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        // this probably shouldn't be here since the sound/sound direction implementation is extremely scuffed
        // but maybe someone wants to use it anyway
        types.AddEnum<relive::Path_CrawlingSligButton::ButtonSounds>("Enum_CrawlingSligButtonSounds",
        {
            {relive::Path_CrawlingSligButton::ButtonSounds::None, "None"},
            {relive::Path_CrawlingSligButton::ButtonSounds::SackHit1, "Sack Hit 1"},
            {relive::Path_CrawlingSligButton::ButtonSounds::SackHit2, "Sack Hit 2"},
            {relive::Path_CrawlingSligButton::ButtonSounds::FallingItemPresence2, "Falling Item Presence 2"},
            {relive::Path_CrawlingSligButton::ButtonSounds::SecurityOrb, "Security Orb"},
            {relive::Path_CrawlingSligButton::ButtonSounds::Bullet1, "Bullet 1"},
            {relive::Path_CrawlingSligButton::ButtonSounds::AbeGenericMovement, "Abe Generic Movement"},
        });
    }
    */

public:
    Editor_CrawlingSligButton()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Action", mTlv.mAction);
        //r.Visit("On Sound", mTlv.mOnSound);
        //r.Visit("Off Sound", mTlv.mOffSound);
        //r.Visit("Sound Direction", mTlv.mSoundDirection); // HIDDEN
    }

    Path_CrawlingSligButton mTlv;
};

struct Editor_Glukkon final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Glukkon::GlukkonTypes>("Enum_GlukkonTypes",
        {
            {relive::Path_Glukkon::GlukkonTypes::eNormal, "Normal"},
            {relive::Path_Glukkon::GlukkonTypes::eStoryAslik, "Story Aslik"},
            {relive::Path_Glukkon::GlukkonTypes::eStoryDripik, "Story Dripik"},
            {relive::Path_Glukkon::GlukkonTypes::eStoryPhleg, "Story Phleg"},
        });

        types.AddEnum<relive::Path_Glukkon::Facing>("Enum_GlukkonFacing",
        {
            {relive::Path_Glukkon::Facing::eRight, "Right"},
            {relive::Path_Glukkon::Facing::eLeft, "Left"},
        });

        types.AddEnum<relive::Path_Glukkon::SpawnType>("Enum_GlukkonSpawnType",
        {
            {relive::Path_Glukkon::SpawnType::eRegularSpawn, "Regular Spawn"},
            {relive::Path_Glukkon::SpawnType::eFacingLeft, "Facing Left"},
            {relive::Path_Glukkon::SpawnType::eFacingRight, "Facing Right"},
            {relive::Path_Glukkon::SpawnType::eFullSpawnEffects, "Full Spawn Effects"},
        });

        types.AddEnum<relive::Path_Glukkon::Behavior>("Enum_GlukkonBehavior",
        {
            {relive::Path_Glukkon::Behavior::eIgnoreWalls, "Ignore Walls"},
            {relive::Path_Glukkon::Behavior::eCheckForWalls, "Check For Walls"},
        });
    }
    */

public:
    Editor_Glukkon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Starting Direction", mTlv.mFacing);
        //r.Visit("Behavior", mTlv.mBehavior);
        r.Visit("Scream Help Delay", mTlv.mScreamHelpDelay);
        r.Visit("Help Switch ID", mTlv.mHelpSwitchId);
        r.Visit("To Calm Delay", mTlv.mToCalmDelay);
        r.Visit("Spawner Switch ID", mTlv.mSpawnSwitchId);
        //r.Visit("Spawn Type", mTlv.mSpawnType);
        r.Visit("Spawn Delay", mTlv.mSpawnDelay);
        //r.Visit("Glukkon Type", mTlv.mGlukkonType);
        r.Visit("Death Switch ID", mTlv.mDeathSwitchId);
        r.Visit("Play Movie Switch ID", mTlv.mPlayMovieSwitchId);
        r.Visit("Movie To Play (FMV ID)", mTlv.mMovieId);
    }

    Path_Glukkon mTlv;
};

struct Editor_GlukkonSwitch final : public MapObjectBase
{
public:
    Editor_GlukkonSwitch()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("OK Switch ID", mTlv.mOkSwitchId);
        r.Visit("Fail Switch ID", mTlv.mFailSwitchId);
        r.Visit("X Position", mTlv.mXPos);
        r.Visit("Y Position", mTlv.mYPos);
    }

    Path_GlukkonSwitch mTlv;
};

struct Editor_GasCountDown final : public MapObjectBase
{
public:
    Editor_GasCountDown()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Start Timer Switch ID", mTlv.mStartTimerSwitchId);
        r.Visit("(AE) Gas Countdown Time", mTlv.mGasCountdownTimer);
        r.Visit("(AE) Stop Timer Switch ID", mTlv.mStopTimerSwitchId);
    }

    Path_GasCountDown mTlv;
};

struct Editor_FallingItem final : public MapObjectBase
{
public:
    Editor_FallingItem()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Fall Interval", mTlv.mFallInterval);
        r.Visit("Maximum Falling Items", mTlv.mMaxFallingItems);
        //r.Visit("Reset Switch ID After Use", mTlv.mResetSwitchIdAfterUse);
    }

    Path_FallingItem mTlv;
};

struct Editor_BoneBag final : public MapObjectBase
{
public:
    Editor_BoneBag()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Bone Fall Direction", mTlv.mBoneFallDirection);
        r.Visit("X Velocity", mTlv.mVelX);
        r.Visit("Y Velocity", mTlv.mVelY);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Bone Amount", mTlv.mBoneAmount);
    }

    Path_BoneBag mTlv;
};

struct Editor_SecurityClaw final : public MapObjectBase
{
public:
    Editor_SecurityClaw()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Alarm Switch ID", mTlv.mAlarmSwitchId);
        r.Visit("Alarm Duration", mTlv.mAlarmDuration);
    }

    Path_SecurityClaw mTlv;
};

struct Editor_FootSwitch final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_FootSwitch::FootSwitchTriggerBy>("Enum_FootSwitchTriggeredBy",
        {
            {relive::Path_FootSwitch::FootSwitchTriggerBy::eAbe, "Abe"},
            {relive::Path_FootSwitch::FootSwitchTriggerBy::eAnyone, "Anyone"},
        });
    }*/

public:
    Editor_FootSwitch()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Action", mTlv.mAction);
        //r.Visit("Triggered By", mTlv.mTriggeredBy);
    }

    Path_FootSwitch mTlv;
};

struct Editor_ZzzSpawner final : public MapObjectBase
{
public:
    Editor_ZzzSpawner()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Zzz Interval", mTlv.mZzzInterval);
    }

    Path_ZzzSpawner mTlv;
};

struct Editor_SlogSpawner final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_SlogSpawner::StartDirection>("Enum_SlogSpawnerStartDirection",
        {
            {relive::Path_SlogSpawner::StartDirection::eRight, "Right"},
            {relive::Path_SlogSpawner::StartDirection::eLeft, "Left"},
        });
    }*/

public:
    Editor_SlogSpawner()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Max Slogs", mTlv.mMaxSlogs);
        r.Visit("Max Slogs At A Time", mTlv.mMaxSlogsAtATime);
        //r.Visit("Start Direction", mTlv.mStartDirection);
        r.Visit("Slog Spawn Interval", mTlv.mSlogSpawnInterval);
        r.Visit("Spawner Switch ID", mTlv.mSpawnerSwitchId);
        //r.Visit("(AE) Listen To Sligs", mTlv.mListenToSligs);
        r.Visit("(AE) Chase Delay", mTlv.mChaseDelay);
    }

    Path_SlogSpawner mTlv;
};

struct Editor_MainMenuController final : public MapObjectBase
{
public:
    Editor_MainMenuController()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_MainMenuController mTlv;
};

struct Editor_Scrab final : public MapObjectBase
{
public:
    Editor_Scrab()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Attack Delay", mTlv.mAttackDelay);
        r.Visit("(AE) Patrol Type Run Or Walk Chance (6 Max)", mTlv.mPatrolTypeRunOrWalkChance);
        //r.Visit("(AO) Patrol Type", mTlv.mPatrolType);
        r.Visit("Left Min Delay", mTlv.mPauseLeftMin);
        r.Visit("Left Max Delay", mTlv.mPauseLeftMax);
        r.Visit("Right Min Delay", mTlv.mPauseRightMin);
        r.Visit("Right Max Delay", mTlv.mPauseRightMax);
        r.Visit("Pause After Chase Delay", mTlv.mPauseAfterChaseTime);
        r.Visit("Spotting Abe Delay", mTlv.mSpottingAbeDelay);
        //r.Visit("Roar Randomly", mTlv.mRoarRandomly);
        //r.Visit("(AE) Persistant", mTlv.mPersistant);
        r.Visit("(AE) Possessed Max Whirl Attack Duration", mTlv.mPossessedMaxWhirlAttackDuration);
        //r.Visit("(AE) Kill Enemy", mTlv.mKillEnemy);
    }

    Path_Scrab mTlv;
};

struct Editor_ScrabSpawner final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_ScrabSpawner::SpawnDirection>("Enum_ScrabSpawnDirection",
        {
            {relive::Path_ScrabSpawner::SpawnDirection::eNone, "None"},
            {relive::Path_ScrabSpawner::SpawnDirection::eLeft, "Left"},
            {relive::Path_ScrabSpawner::SpawnDirection::eRight, "Right"},
        });
    }*/

public:
    Editor_ScrabSpawner()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        // Scrab properties
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Attack Delay", mTlv.mAttackDelay);
        r.Visit("(AE) Patrol Type Run Or Walk Chance (6 Max)", mTlv.mPatrolTypeRunOrWalkChance);
        //r.Visit("(AO) Patrol Type", mTlv.mPatrolType);
        r.Visit("Left Min Delay", mTlv.mPauseLeftMin);
        r.Visit("Left Max Delay", mTlv.mPauseLeftMax);
        r.Visit("Right Min Delay", mTlv.mPauseRightMin);
        r.Visit("Right Max Delay", mTlv.mPauseRightMax);
        r.Visit("Pause After Chase Delay", mTlv.mPauseAfterChaseTime);
        r.Visit("Spotting Abe Delay", mTlv.mSpottingAbeDelay);
        //r.Visit("Roar Randomly", mTlv.mRoarRandomly);
        //r.Visit("(AE) Persistant", mTlv.mPersistant);
        r.Visit("(AE) Possessed Max Whirl Attack Duration", mTlv.mPossessedMaxWhirlAttackDuration);
        //r.Visit("(AE) Kill Enemy", mTlv.mKillEnemy);

        // Spawner properties
        r.Visit("Spawner Switch ID", mTlv.mSpawnerSwitchId);
        //r.Visit("Facing", mTlv.mFacing);
    }

    Path_ScrabSpawner mTlv;
};

struct Editor_SlurgSpawner final : public MapObjectBase
{
public:
    Editor_SlurgSpawner()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        // Slurg properties
        r.Visit("Time Until Turning Around", mTlv.mMovingTimer);
        //r.Visit("Facing", mTlv.mFacing);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID (increment by 1 on death)", mTlv.mSlurgSwitchId);

        // Spawner properties
        r.Visit("Spawn Interval", mTlv.mSpawnInterval);
        r.Visit("Max Slurgs", mTlv.mMaxSlurgs);
        r.Visit("Spawner Switch ID", mTlv.mSpawnerSwitchId);
    }

    Path_SlurgSpawner mTlv;
};

struct Editor_Paramite final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_Paramite::EntranceType>("Enum_ParamiteEntranceType",
        {
            {relive::Path_Paramite::EntranceType::ePatrol, "Patrol"},
            {relive::Path_Paramite::EntranceType::eSurpriseWeb, "Surprise Web"},
            {relive::Path_Paramite::EntranceType::eSlightlyHigherSpawnSurpriseWeb, "Slightly Higher Spawn Surprise Web"},
        });
    }*/

public:
    Editor_Paramite()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Entrance Type", mTlv.mEntranceType);
        r.Visit("Alone - Chase Delay", mTlv.mAloneChaseDelay);
        r.Visit("Surprise Web Delay", mTlv.mSurpriseWebDelayTimer);
        r.Visit("Meat Eating Time", mTlv.mMeatEatingTime);
        r.Visit("Group - Chase Delay", mTlv.mGroupChaseDelay);
        r.Visit("Surprise Web Switch ID", mTlv.mSurpriseWebSwitchId);
        //r.Visit("Hiss Before Attacking", mTlv.mHissBeforeAttack);
        //r.Visit("Delete When Out Of Sight", mTlv.mDeleteWhenOutOfSight);
        //r.Visit("(AE) Attack Fleeches", mTlv.mAttackFleeches);
    }

    Path_Paramite mTlv;
};

struct Editor_ParamiteWebLine final : public MapObjectBase
{
public:
    Editor_ParamiteWebLine()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
    }

    Path_ParamiteWebLine mTlv;
};

struct Editor_MeatSack final : public MapObjectBase
{
public:
    Editor_MeatSack()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Meat Fall Direction", mTlv.mMeatFallDirection);
        r.Visit("X Velocity", mTlv.mVelX);
        r.Visit("Y Velocity", mTlv.mVelY);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Amount Of Meat", mTlv.mMeatAmount);
    }

    Path_MeatSack mTlv;
};

struct Editor_TorturedMudokon final : public MapObjectBase
{
public:
    Editor_TorturedMudokon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Kill Switch ID", mTlv.mKillSwitchId);
        r.Visit("Release Switch ID", mTlv.mReleaseSwitchId);
    }

    Path_TorturedMudokon mTlv;
};

struct Editor_KillUnsavedMuds final : public MapObjectBase
{
public:
    Editor_KillUnsavedMuds()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_KillUnsavedMuds mTlv;
};

struct Editor_BackgroundGlukkon final : public MapObjectBase
{
public:
    Editor_BackgroundGlukkon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale Percent", mTlv.mScalePercent);
        r.Visit("Pal ID", mTlv.mPalId);
    }

    Path_BackgroundGlukkon mTlv;
};

struct Editor_BellsongStone final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_BellsongStone::BellsongTypes>("Enum_BellsongTypes",
        {
            {relive::Path_BellsongStone::BellsongTypes::eWhistle, "Whistle"},
            {relive::Path_BellsongStone::BellsongTypes::eChimes, "Chimes"},
        });
    }
    */
public:
    Editor_BellsongStone()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Type", mTlv.mType);
        r.Visit("Code 1", mTlv.mCode1);
        r.Visit("Code 2", mTlv.mCode2);
        r.Visit("Switch ID", mTlv.mSwitchId);
    }

    Path_BellsongStone mTlv;
};

struct Editor_LightEffect final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_LightEffect::Type>("Enum_LightType",
        {
            {relive::Path_LightEffect::Type::Star, "Star"},
            {relive::Path_LightEffect::Type::GoldGlow, "Gold Glow"},
            {relive::Path_LightEffect::Type::GreenGlow, "Green Glow"},
            {relive::Path_LightEffect::Type::FlintGlow, "Flint Glow"},
            {relive::Path_LightEffect::Type::Switchable_RedGreenDoorLights, "RedGreen Door Light"},
            {relive::Path_LightEffect::Type::Switchable_RedGreenHubLight, "RedGreen Hub Light"},
        });
    }
    */
public:
    Editor_LightEffect()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Type", mTlv.mType);
        r.Visit("Size", mTlv.mSize);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Direction", mTlv.mDirection);
    }

    Path_LightEffect mTlv;
};

struct Editor_StartController final : public MapObjectBase
{
public:
    Editor_StartController()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_StartController mTlv;
};

struct Editor_HintFly final : public MapObjectBase
{
public:
    Editor_HintFly()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Message ID", mTlv.mMessageId);
    }

    Path_HintFly mTlv;
};

struct Editor_Bat final : public MapObjectBase
{
public:
    Editor_Bat()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Time Before Moving", mTlv.mTimeBeforeMoving);
        r.Visit("Speed", mTlv.mSpeed);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Attack Duration", mTlv.mAttackDuration);
    }

    Path_Bat mTlv;
};

struct Editor_BellHammer final : public MapObjectBase
{
public:
    Editor_BellHammer()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Action", mTlv.mAction);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Direction", mTlv.mDirection);
    }

    Path_BellHammer mTlv;
};

struct Editor_ElumPathTrans final : public MapObjectBase
{
public:
    Editor_ElumPathTrans()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Next Level", mTlv.mNextLevel);
        r.Visit("Next Path", mTlv.mNextPath);
        r.Visit("Next Camera", mTlv.mNextCamera);
    }

    Path_ElumPathTrans mTlv;
};

struct Editor_ElumStart final : public MapObjectBase
{
public:
    Editor_ElumStart()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_ElumStart mTlv;
};

struct Editor_ElumWall final : public MapObjectBase
{
public:
    Editor_ElumWall()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_ElumWall mTlv;
};

struct Editor_RingMudokon final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_RingMudokon::MustFaceMud>("Enum_RingMudokon_MustFaceMud",
        {
            {relive::Path_RingMudokon::MustFaceMud::eYes, "Yes"},
            {relive::Path_RingMudokon::MustFaceMud::eNo, "No"},
        });
    }*/

public:
    Editor_RingMudokon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Facing", mTlv.mFacing);
        //r.Visit("Abe Must Face Mudokon", mTlv.mAbeMustFaceMud);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Give Password", mTlv.mGivePassword);
        r.Visit("Code 1", mTlv.mCode1);
        r.Visit("Code 2", mTlv.mCode2);
        //r.Visit("Action", mTlv.mAction);
        r.Visit("Ring And Angry Mudokon Timeout", mTlv.mRingTimeout);
        //r.Visit("Give Ring Without Password", mTlv.mGiveRingWithoutPassword);
    }

    Path_RingMudokon mTlv;
};

struct Editor_RingCancel final : public MapObjectBase
{
public:
    Editor_RingCancel()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_RingCancel mTlv;
};

struct Editor_MeatSaw final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_MeatSaw::Type>("Enum_MeatSawType",
        {
            {relive::Path_MeatSaw::Type::eAutomaticPersistOffscreen, "Automatic Persist Offscreen"},
            {relive::Path_MeatSaw::Type::eAutomatic, "Automatic"},
            {relive::Path_MeatSaw::Type::eSwitchId, "Switch ID"},
        });

        types.AddEnum<relive::Path_MeatSaw::StartState>("Enum_MeatSawStartState",
        {
            {relive::Path_MeatSaw::StartState::eOff, "Off"},
            {relive::Path_MeatSaw::StartState::eOn, "On"},
        });
    }
    */
public:
    Editor_MeatSaw()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch Min Time Off", mTlv.mSwitchMinTimeOff);
        r.Visit("Switch Max Time Off", mTlv.mSwitchMaxTimeOff);
        r.Visit("Y Travel Distance", mTlv.mYTravelDistance);
        r.Visit("Switch ID", mTlv.mSwitchId);
        //r.Visit("Type", mTlv.mType);
        r.Visit("Switch Speed", mTlv.mSwitchSpeed);
        //r.Visit("Start State", mTlv.mStartState);
        r.Visit("Automatic Speed", mTlv.mAutomaticSpeed);
        r.Visit("Automatic Min Time Off", mTlv.mAutomaticMinTimeOff);
        r.Visit("Automatic Max Time Off", mTlv.mAutomaticMaxTimeOff);
        r.Visit("Start At Bottom", mTlv.mStartAtBottom);
    }

    Path_MeatSaw mTlv;
};

struct Editor_ChimeLock final : public MapObjectBase
{
public:
    Editor_ChimeLock()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Solve Switch ID", mTlv.mSolveSwitchId);
        r.Visit("Code 1", mTlv.mCode1);
        r.Visit("Code 2", mTlv.mCode2);
        r.Visit("Password Switch ID", mTlv.mPasswordSwitchId);
    }

    Path_ChimeLock mTlv;
};

struct Editor_FlintLockFire final : public MapObjectBase
{
public:
    Editor_FlintLockFire()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        r.Visit("Switch ID", mTlv.mSwitchId);
    }

    Path_FlintLockFire mTlv;
};

struct Editor_MudokonPathTrans final : public MapObjectBase
{
public:
    Editor_MudokonPathTrans()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Next Level", mTlv.mNextLevel);
        r.Visit("Next Path", mTlv.mNextPath);
        r.Visit("Next Camera", mTlv.mNextCamera);
    }

    Path_MudokonPathTrans mTlv;
};

struct Editor_ScrabNoFall final : public MapObjectBase
{
public:
    Editor_ScrabNoFall()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_ScrabNoFall mTlv;
};

struct Editor_LiftMudokon final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_LiftMudokon::Direction>("Enum_LiftMudokonDirection",
        {
            {relive::Path_LiftMudokon::Direction::eRight, "Right"},
            {relive::Path_LiftMudokon::Direction::eLeft, "Left"},
        });
    }
    */
public:
    Editor_LiftMudokon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("How Far To Walk", mTlv.mHowFarToWalk);
        r.Visit("Lift Switch ID", mTlv.mLiftSwitchId);
        //r.Visit("Facing", mTlv.mFacing);
        //r.Visit("Give Password", mTlv.mGivePassword);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Code 1", mTlv.mCode1);
        r.Visit("Code 2", mTlv.mCode2);
    }

    Path_LiftMudokon mTlv;
};

struct Editor_HoneySack final : public MapObjectBase
{
public:
    Editor_HoneySack()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Chase Time", mTlv.mChaseTime);
        r.Visit("Scale", mTlv.mScale);
    }

    Path_HoneySack mTlv;
};

struct Editor_SlingMudokon final : public MapObjectBase
{
public:
    Editor_SlingMudokon()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Don't Whistle Password", mTlv.mDontWhistlePassword);
        r.Visit("Code 1", mTlv.mCode1);
        r.Visit("Code 2", mTlv.mCode2);
    }

    Path_SlingMudokon mTlv;
};

struct Editor_BeeSwarmHole final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_BeeSwarmHole::MovementType>("Enum_BeeSwarmHoleMovementType",
        {
            {relive::Path_BeeSwarmHole::MovementType::eHover, "Hover"},
            {relive::Path_BeeSwarmHole::MovementType::eAttack, "Attack"},
            {relive::Path_BeeSwarmHole::MovementType::eFollowPath, "Follow Path"},
        });
    }
    */
public:
    Editor_BeeSwarmHole()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Start Interval", mTlv.mStartInterval);
        //r.Visit("Movement Type", mTlv.mMovementType);
        r.Visit("Bees Amount", mTlv.mBeesAmount);
        r.Visit("Chase Time", mTlv.mChaseTime);
        r.Visit("Speed", mTlv.mSpeed);
    }

    Path_BeeSwarmHole mTlv;
};

struct Editor_RollingBall final : public MapObjectBase
{
public:
    Editor_RollingBall()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Roll Direction", mTlv.mRollDirection);
        r.Visit("Release Switch ID", mTlv.mReleaseSwitchId);
        r.Visit("Max Speed", mTlv.mMaxSpeed);
        r.Visit("Acceleration", mTlv.mAcceleration);
    }

    Path_RollingBall mTlv;
};

struct Editor_RollingBallStopper final : public MapObjectBase
{
public:
    Editor_RollingBallStopper()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Stopper Switch ID", mTlv.mStopperSwitchId);
        r.Visit("Scale", mTlv.mScale);
        r.Visit("Ball Switch ID", mTlv.mBallSwitchId);
        //r.Visit("Stop Direction", mTlv.mStopDirection);
    }

    Path_RollingBallStopper mTlv;
};

struct Editor_BeeNest final : public MapObjectBase
{
public:
    Editor_BeeNest()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        r.Visit("Switch ID", mTlv.mSwitchId);
        r.Visit("Swarm Size", mTlv.mSwarmSize);
        r.Visit("Chase Time", mTlv.mChaseTime);
        r.Visit("Speed", mTlv.mSpeed);
        r.Visit("Amount Of Bees", mTlv.mBeesAmount);
    }

    Path_BeeNest mTlv;
};

struct Editor_ZBall final : public MapObjectBase
{
    /*
    void AddTypes(ReliveAPI::TypesCollectionBase& types) override
    {
        types.AddEnum<relive::Path_ZBall::StartPos>("Enum_ZBallStartPos",
        {
            {relive::Path_ZBall::StartPos::eCenter, "Center"},
            {relive::Path_ZBall::StartPos::eOut, "Out"},
            {relive::Path_ZBall::StartPos::eIn, "In"},
        });

        types.AddEnum<relive::Path_ZBall::Speed>("Enum_ZBallSpeed",
        {
            {relive::Path_ZBall::Speed::eNormal, "Normal"},
            {relive::Path_ZBall::Speed::eFast, "Fast"},
            {relive::Path_ZBall::Speed::eSlow, "Slow"},
        });
    }
    */
public:
    Editor_ZBall()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);

        //r.Visit("Start Position", mTlv.mStartPos);
        r.Visit("Scale", mTlv.mScale);
        //r.Visit("Speed", mTlv.mSpeed);
    }

    Path_ZBall mTlv;
};

struct Editor_Honey final : public MapObjectBase
{
public:
    Editor_Honey()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_Honey mTlv;
};

struct Editor_HoneyDripTarget final : public MapObjectBase
{
public:
    Editor_HoneyDripTarget()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_HoneyDripTarget mTlv;
};

struct Editor_Elum final : public MapObjectBase
{
public:
    Editor_Elum()
        : MapObjectBase(&mTlv)
    { }

    void Visit(IRefelector& r) override
    {
        MapObjectBase::Visit(r);
    }

    Path_Elum mTlv;
};
} // namespace relive

#undef EMPTY_CTOR_RELIVE
#undef CTOR_RELIVE

