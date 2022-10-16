#include "stdafx_ao.h"
#include "Game.hpp"
#include "Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "SwitchStates.hpp"
#include "DDCheat.hpp"
#include "Io.hpp"
#include "Psx.hpp"
#include "Sys.hpp"
#include "../relive_lib/DynamicArray.hpp"
#include "BaseAliveGameObject.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "ResourceManager.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "Map.hpp"
#include "GameSpeak.hpp"
#include "CheatController.hpp"
#include "DDCheat.hpp"
#include "MusicController.hpp"
#include "VGA.hpp"
#include "Input.hpp"
#include "Midi.hpp"
#include "PauseMenu.hpp"
#include "Abe.hpp"
#include "../relive_lib/ShadowZone.hpp"
#include "CameraSwapper.hpp"
#include "AmbientSound.hpp"
#include "PsxRender.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "../relive_lib/Error.hpp"
#include "../relive_lib/Events.hpp"
#include "Sound.hpp"
#include "../AliveLibAE/Game.hpp"
#include "AddPointer.hpp"
#include "PathDataExtensions.hpp"
#include "GameAutoPlayer.hpp"
#include "../relive_lib/Error.hpp"

namespace AO {

DynamicArrayT<BaseGameObject>* gLoadingFiles = nullptr;

DynamicArrayT<BaseGameObject>* gPlatformsArray = nullptr;

void Game_ForceLink()
{
}

s16 gbKillUnsavedMudsDone_5076CC = 0;

// TODO: Move to game ender controller for AO sync
s16 gRestartRuptureFarmsKilledMuds_5076C4 = 0;
s16 gRestartRuptureFarmsSavedMuds_5076C8 = 0;

s16 gOldKilledMuds_5076D0 = 0;
s16 gOldSavedMuds_5076D4 = 0;

s16 sBreakGameLoop_507B78 = 0;
s16 gAttract_507698 = 0;

s8 gDDCheatMode_508BF8 = 0;

s32 Game_End_Frame_4505D0(u32 bSkip)
{
    return Game_End_Frame_4950F0(bSkip);
}

static void Main_ParseCommandLineArguments()
{
    IO_Init_48E1A0(0);

    std::string windowTitle = WindowTitleAO();

    if (GetGameAutoPlayer().IsRecording())
    {
        windowTitle += " [Recording]";
    }
    else if (GetGameAutoPlayer().IsPlaying())
    {
        windowTitle += " [AutoPlay]";
    }

    Sys_WindowClass_Register("ABE_WINCLASS", windowTitle.c_str(), 32, 64, 640, 480);

    Sys_Set_Hwnd(Sys_GetWindowHandle());

    const LPSTR pCmdLine = Sys_GetCommandLine();
    if (pCmdLine)
    {
        if (_strcmpi(pCmdLine, "-it_is_me_your_father") == 0)
        {
            Input_GetCurrentKeyStates();
            if (Input_IsVKPressed(VK_SHIFT))
            {
                gDDCheatMode_508BF8 = 1;
            }
        }
        // Force DDCheat
#if FORCE_DDCHEAT
        gDDCheatMode_508BF8 = 1;
#endif
    }

    Init_VGA_AndPsxVram();

    PSX_EMU_Init_49A1D0();
    PSX_EMU_VideoAlloc_49A2B0();
    PSX_EMU_SetCallBack_499920(1, Game_End_Frame_4505D0);
}

void Init_GameStates()
{
    sKilledMudokons_5076BC = gRestartRuptureFarmsKilledMuds_5076C4;
    sRescuedMudokons_5076C0 = gRestartRuptureFarmsSavedMuds_5076C8;
    gSwitchStates = {};
    gOldKilledMuds_5076D0 = 0;
    gOldSavedMuds_5076D4 = 0;
    gbKillUnsavedMudsDone_5076CC = 0;
}


void Init_Sound_DynamicArrays_And_Others_41CD20()
{
    DebugFont_Init();

    pPauseMenu_5080E0 = nullptr;
    sActiveHero = nullptr;
    sControlledCharacter = nullptr;
    gNumCamSwappers = 0;
    sGnFrame = 0;

    gFilesPending_507714 = 0;
    bLoadingAFile_50768C = 0;

    gPlatformsArray = relive_new DynamicArrayT<BaseGameObject>(20);

    ObjList_5009E0 = relive_new DynamicArrayT<ResourceManager::ResourceManager_FileRecord>(10); // not used in AE

    ShadowZone::MakeArray();

    gBaseAliveGameObjects = relive_new DynamicArrayT<BaseAliveGameObject>(20);

    gLoadingFiles = relive_new DynamicArrayT<BaseGameObject>(20); // TODO: Leaked on purpose for now

    SND_Init_476E40();
    SND_Init_Ambiance();
    MusicController::Create();

    Init_GameStates(); // Note: inlined

    // TODO: The switch state clearing is done in Init_GameStates in AE
    // check this is not an AO bug
    SwitchStates_ClearAll();
}

void Game_Init_LoadingIcon()
{
    /*
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kLoadingAOResID, 1, 0);
    if (!ppRes)
    {
        ResourceManager::LoadResourceFile_455270("LOADING.BAN", nullptr);
        ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kLoadingAOResID, 1, 0);
    }
    ResourceManager::Set_Header_Flags_4557D0(ppRes, ResourceManager::ResourceHeaderFlags::eNeverFree);
    */
}

void Game_Free_LoadingIcon()
{
    /*
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AOResourceID::kLoadingAOResID, 0, 0);
    if (ppRes)
    {
        ResourceManager::FreeResource_455550(ppRes);
    }
    */
}


using TExitGameCB = AddPointer_t<void CC()>;

TExitGameCB sGame_OnExitCallback_9F664C = nullptr;

void Game_SetExitCallBack(TExitGameCB)
{
    
}

void Game_ExitGame()
{
    PSX_EMU_VideoDeAlloc_49A550();
}


s32 CreateTimer_48F030(s32, void*)
{
    
    return 0;
}

void Game_Shutdown()
{
    if (sGame_OnExitCallback_9F664C)
    {
        sGame_OnExitCallback_9F664C();
        sGame_OnExitCallback_9F664C = nullptr;
    }

    CreateTimer_48F030(0, nullptr); // Creates a timer that calls a call back which is always null, therefore seems like dead code?
    Input_DisableInput();
    //SND_MCI_Close_493C30(); // TODO: Seems like more dead code because the mci is never set?
    SND_SsQuit();
    IO_Stop_ASync_IO_Thread_491A80();
    VGA_Shutdown_4900E0();
    Error_ShowErrorStackToUser(true);
}


void Game_Loop()
{
    sBreakGameLoop_507B78 = 0;
    bool bPauseMenuObjectFound = false;
    while (!gBaseGameObjects->Empty())
    {
        GetGameAutoPlayer().SyncPoint(SyncPoints::MainLoopStart);

        EventsResetActive();

        // Update objects
        GetGameAutoPlayer().SyncPoint(SyncPoints::ObjectsUpdateStart);
        for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
        {
            BaseGameObject* pBaseGameObject = gBaseGameObjects->ItemAt(i);
            if (!pBaseGameObject)
            {
                break;
            }

            if (pBaseGameObject->mBaseGameObjectFlags.Get(BaseGameObject::eUpdatable_Bit2)
			    && !pBaseGameObject->mBaseGameObjectFlags.Get(BaseGameObject::eDead) 
				&& (gNumCamSwappers == 0 || pBaseGameObject->mBaseGameObjectFlags.Get(BaseGameObject::eUpdateDuringCamSwap_Bit10)))
            {
                const s32 updateDelay = pBaseGameObject->UpdateDelay();
                if (updateDelay <= 0)
                {
                    if (pBaseGameObject == pPauseMenu_5080E0)
                    {
                        bPauseMenuObjectFound = true;
                    }
                    else
                    {
                        pBaseGameObject->VUpdate();
                    }
                }
                else
                {
                    pBaseGameObject->SetUpdateDelay(updateDelay - 1);
                }
            }
        }
        GetGameAutoPlayer().SyncPoint(SyncPoints::ObjectsUpdateEnd);

        // Animate everything
        if (gNumCamSwappers <= 0)
        {
            GetGameAutoPlayer().SyncPoint(SyncPoints::AnimateAll);
            AnimationBase::AnimateAll(AnimationBase::gAnimations);
        }

        // Render objects
        PrimHeader** ppOt = gPsxDisplay.mDrawEnvs[gPsxDisplay.mBufferIndex].mOrderingTable;

        // Render objects
        GetGameAutoPlayer().SyncPoint(SyncPoints::DrawAllStart);
        for (s32 i = 0; i < gObjListDrawables->Size(); i++)
        {
            BaseGameObject* pDrawable = gObjListDrawables->ItemAt(i);
            if (!pDrawable)
            {
                break;
            }

            if (pDrawable->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
            {
                pDrawable->mBaseGameObjectFlags.Clear(BaseGameObject::eCantKill_Bit11);
            }
            else if (pDrawable->mBaseGameObjectFlags.Get(BaseGameObject::eDrawable_Bit4))
            {
                pDrawable->mBaseGameObjectFlags.Set(BaseGameObject::eCantKill_Bit11);
                pDrawable->VRender(ppOt);
            }
        }
        GetGameAutoPlayer().SyncPoint(SyncPoints::DrawAllEnd);

        DebugFont_Flush();
        pScreenManager->VRender(ppOt);
        SYS_EventsPump(); // Exit checking?

        GetGameAutoPlayer().SyncPoint(SyncPoints::RenderOT);
        gPsxDisplay.RenderOrderingTable();
        
        GetGameAutoPlayer().SyncPoint(SyncPoints::RenderStart);

        // Destroy objects with certain flags
        for (s16 i = 0; i < gBaseGameObjects->Size(); i++)
        {
            BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eDead) && pObj->mBaseGameObjectRefCount == 0)
            {
                DynamicArrayIter it;
                it.field_0_pDynamicArray = gBaseGameObjects;
                it.field_4_idx = i + 1;

                it.Remove_At_Iter();
                delete pObj;
            }
        }

        GetGameAutoPlayer().SyncPoint(SyncPoints::RenderEnd);

        if (bPauseMenuObjectFound && pPauseMenu_5080E0)
        {
            pPauseMenu_5080E0->VUpdate();
        }

        bPauseMenuObjectFound = false;

        gMap.ScreenChange();
        Input().Update(GetGameAutoPlayer());

        if (gNumCamSwappers == 0)
        {
            GetGameAutoPlayer().SyncPoint(SyncPoints::IncrementFrame);
            sGnFrame++;
        }

        if (sBreakGameLoop_507B78)
        {
            GetGameAutoPlayer().SyncPoint(SyncPoints::MainLoopExit);
            break;
        }

        GetGameAutoPlayer().ValidateObjectStates();

    } // Main loop end

    PSX_VSync_496620(0);

    // Destroy all game objects
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObjToKill = gBaseGameObjects->ItemAt(i);
        if (!pObjToKill)
        {
            break;
        }

        if (pObjToKill->mBaseGameObjectRefCount == 0)
        {
            i = gBaseGameObjects->RemoveAt(i);
            delete pObjToKill;
        }
    }
}

void DDCheat_Allocate()
{
    relive_new DDCheat();
}

void Game_Run()
{
    // Begin start up
    SYS_EventsPump();

    gAttract_507698 = 0;

    SYS_EventsPump();

    gPsxDisplay.Init();
    Input().InitPad(1);

    gBaseGameObjects = relive_new DynamicArrayT<BaseGameObject>(90);

    BaseAnimatedWithPhysicsGameObject::MakeArray();

    AnimationBase::CreateAnimationArray();

    Init_Sound_DynamicArrays_And_Others_41CD20();
    Input_Init();

    gMap.Init(EReliveLevelIds::eMenu, 1, 10, CameraSwapEffects::eInstantChange_0, 0, 0);

    DDCheat_Allocate();

    gEventSystem = relive_new GameSpeak();

    gCheatController = relive_new CheatController();

    Game_Init_LoadingIcon();

    // Main loop start
    Game_Loop();

    // Shut down start
    Game_Free_LoadingIcon();

    DDCheat::ClearProperties();

    gMap.Shutdown();

    AnimationBase::FreeAnimationArray();
    BaseAnimatedWithPhysicsGameObject::FreeArray();
    relive_delete gBaseGameObjects;
    relive_delete gPlatformsArray;

    MusicController::Shutdown();

    SND_Reset_Ambiance();
    SND_Shutdown_476EC0();
    InputObject::Shutdown();
}


void Game_Main()
{
    GetGameAutoPlayer().ParseCommandLine(Sys_GetCommandLine());

    Main_ParseCommandLineArguments();

    Game_SetExitCallBack(Game_ExitGame);

    // Only returns once the engine is shutting down
    Game_Run();

    // TODO: AE inlined calls here (pull AE's code into another func)
    Game_Shutdown();
}

} // namespace AO
