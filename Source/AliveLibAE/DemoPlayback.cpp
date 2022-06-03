#include "stdafx.h"
#include "DemoPlayback.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Events.hpp"
#include "Map.hpp"
#include "PathData.hpp"
#include "stdlib.hpp"
#include "Function.hpp"

ALIVE_VAR(1, 0x5D1E20, DemoPlayback*, sDemoObj_dword_5D1E20, nullptr);

DemoPlayback::DemoPlayback()
    : BaseGameObject(TRUE, 0)
{
    if (sDemoObj_dword_5D1E20)
    {
        mFlags.Set(BaseGameObject::eDead);
    }
    else
    {
        sDemoObj_dword_5D1E20 = this;
        mFlags.Set(BaseGameObject::eSurviveDeathReset_Bit9);

        u32** ppRes = reinterpret_cast<u32**>(Add_Resource(ResourceManager::Resource_Demo, AEResourceID::kDemoResID));
        SetUpdateDelay(1);
        sInputObject_5BD4E0.SetDemoResource_45F1E0(ppRes);
        SetType(AETypes::eDemoPlayback_98);
    }
}

void DemoPlayback::VUpdate()
{
    vUpdate_4978E0();
}

void DemoPlayback::VScreenChanged()
{
    // Keep alive
}

DemoPlayback::~DemoPlayback()
{
    if (sDemoObj_dword_5D1E20 == this)
    {
        sDemoObj_dword_5D1E20 = nullptr;
    }
}

void DemoPlayback::vUpdate_4978E0()
{
    if (Event_Get_422C00(kEventDeathReset))
    {
        sInputObject_5BD4E0.UnsetDemoPlaying_45F240();
    }

    if (!sInputObject_5BD4E0.Is_Demo_Playing_45F220())
    {
        // demo finished playing, go back to the appropriate menu
        if (gIsDemoStartedManually_5C1B9C)
        {
            // go back to the demo selection menu
            gMap.SetActiveCam(LevelIds::eMenu_0, 1, 30, CameraSwapEffects::eInstantChange_0, 0, 0);
        }
        else
        {
            // go back to the main screen
            gMap.SetActiveCam(LevelIds::eMenu_0, 1, 1, CameraSwapEffects::eInstantChange_0, 0, 0);
        }

        gMap.field_CE_free_all_anim_and_palts = 1;
        mFlags.Set(BaseGameObject::eDead);
    }
}
