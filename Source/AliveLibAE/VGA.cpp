#include "stdafx.h"
#include "VGA.hpp"
#include "Function.hpp"
#include "Sys.hpp"
#include "PsxRender.hpp"
#include "Psx.hpp"
#include "TouchController.hpp"
#include "Renderer/IRenderer.hpp"
#include "Renderer/SoftwareRenderer.hpp"
#include "Renderer/DirectX9Renderer.hpp"
#include "../AliveLibCommon/FatalError.hpp"

static bool sbRendererCreated = false;

void VGA_Shutdown()
{
    IRenderer::FreeRenderer();

    sbRendererCreated = false;
}

void VGA_EndFrame()
{
    IRenderer::GetRenderer()->Clear(0, 0, 0);
    IRenderer::GetRenderer()->EndFrame();
}

void VGA_CreateRenderer()
{
    if (sbRendererCreated)
    {
        VGA_Shutdown();
    }

    //IRenderer::CreateRenderer(IRenderer::Renderers::DirectX9);
    IRenderer::CreateRenderer(IRenderer::Renderers::OpenGL, Sys_GetHWnd());
    IRenderer::GetRenderer()->Clear(0, 0, 0);
    sbRendererCreated = true;
}
