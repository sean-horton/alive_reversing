#include "../../../relive_lib/Primitives.hpp"
#include "FatalError.hpp"
#include "Sdl2Renderer.hpp"

Sdl2Renderer::Sdl2Renderer(TWindowHandleType window)
    : IRenderer(window),
    mContext(window),
    mPsxFbTexture{
        Sdl2Texture(mContext, kPsxFramebufferWidth, kPsxFramebufferHeight, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET),
        Sdl2Texture(mContext, kPsxFramebufferWidth, kPsxFramebufferHeight, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET)
    }
{
    // Render target support is required for things like FG1 mask and
    // framebuffer textures
    if (!mContext.IsRenderTargetSupported())
    {
        ALIVE_FATAL("%s", "SDL2 renderer requires render target support.");
    }
}

Sdl2Renderer::~Sdl2Renderer()
{
}

void Sdl2Renderer::Clear(u8 r, u8 g, u8 b)
{
    LOG("%s", "SDL2: Clear viewport");

    mContext.UseScreenFramebuffer();

    SDL_SetRenderDrawColor(mContext.GetRenderer(), r, g, b, 255);
    SDL_RenderClear(mContext.GetRenderer());

    mContext.UseTextureFramebuffer(GetActiveFbTexture().GetTexture());
}

void Sdl2Renderer::Draw(const Prim_GasEffect& gasEffect)
{
    LOG("%s", "SDL2: Draw Prim_GasEffect");

    // TODO: Implement this
    const f32 x = static_cast<f32>(gasEffect.x);
    const f32 y = static_cast<f32>(gasEffect.y);
    const f32 w = static_cast<f32>(gasEffect.w);
    const f32 h = static_cast<f32>(gasEffect.h);

    //const f32 gasWidth = std::floor(static_cast<f32>(gasEffect.w - gasEffect.x) / 4);
    //const f32 gasHeight = std::floor(static_cast<f32>(gasEffect.h - gasEffect.y) / 2);

    SDL_Color c = { 255, 255, 0, 127 };

    std::vector<SDL_Vertex> gasVerts = {
        { {x, y}, c, { 0, 0 } },
        { {w, y}, c, { 0, 0 } },
        { {x, h}, c, { 0, 0 } },

        { {x, h}, c, { 0, 0 } },
        { {w, y}, c, { 0, 0 } },
        { {w, h}, c, { 0, 0 } },
    };

    ScaleVertices(gasVerts);

    SDL_RenderGeometry(mContext.GetRenderer(), NULL, gasVerts.data(), 6, NULL, 0);
}

void Sdl2Renderer::Draw(const Line_G2& line)
{
    LOG("%s", "SDL2: Draw Line_G2");

    // FIXME: Handle thickness, and colour correctly (aka use a quad)
    SDL_SetRenderDrawColor(mContext.GetRenderer(), line.R0(), line.G0(), line.B0(), 255);
    SDL_RenderDrawLine(mContext.GetRenderer(), line.X0(), line.Y0(), line.X1(), line.Y1());
}

void Sdl2Renderer::Draw(const Line_G4& line)
{
    LOG("%s", "SDL2: Draw Line_G4");

    // FIXME: Handle thickness, and colour correctly (aka use a quad)
    SDL_Point points[] = {
        { line.X0(), line.Y0() },
        { line.X1(), line.Y1() },
        { line.X2(), line.Y2() },
        { line.X3(), line.Y3() },
    };

    SDL_SetRenderDrawColor(mContext.GetRenderer(), line.R0(), line.G0(), line.B0(), 255);
    SDL_RenderDrawLines(mContext.GetRenderer(), points, 4);
}

void Sdl2Renderer::Draw(const Poly_G3& poly)
{
    LOG("%s", "SDL2: Draw Poly_G3");

    // FIXME: Obviously unfinished (no blending, etc.)
    std::vector<SDL_Vertex> vertices = {
        { { static_cast<f32>(poly.X0()), static_cast<f32>(poly.Y0()) }, { poly.R0(), poly.G0(), poly.B0(), 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X1()), static_cast<f32>(poly.Y1()) }, { poly.R1(), poly.G1(), poly.B1(), 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X2()), static_cast<f32>(poly.Y2()) }, { poly.R2(), poly.G2(), poly.B2(), 255 }, { 0, 0 } },
    };

    ScaleVertices(vertices);

    SDL_RenderGeometry(mContext.GetRenderer(), NULL, vertices.data(), 3, NULL, 0);
}

void Sdl2Renderer::Draw(const Poly_FT4& poly)
{
    //
    // FIXME: Obviously unfinished (no blending, etc.)
    //
    SDL_Texture* tex = NULL;

    constexpr s32 indexList[6] = { 0, 1, 2, 1, 2 , 3 };
    std::vector<SDL_Vertex> vertices = {
        { { static_cast<f32>(poly.X0()), static_cast<f32>(poly.Y0()) }, { 255, 255, 255, 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X1()), static_cast<f32>(poly.Y1()) }, { 255, 255, 255, 255 }, { 1, 0 } },
        { { static_cast<f32>(poly.X2()), static_cast<f32>(poly.Y2()) }, { 255, 255, 255, 255 }, { 0, 1 } },
        { { static_cast<f32>(poly.X3()), static_cast<f32>(poly.Y3()) }, { 255, 255, 255, 255 }, { 1, 1 } },
    };

    ScaleVertices(vertices);

    if (poly.mFg1)
    {
        LOG("%s", "SDL2: Draw Poly_FT4 (FG1)");

        tex = PrepareTextureFromPoly(poly)->GetTexture();
    }
    else if (poly.mCam)
    {
        LOG("%s", "SDL2: Draw Poly_FT4 (CAM)");

        tex = PrepareTextureFromPoly(poly)->GetTexture();
    }
    else if (poly.mAnim)
    {
        LOG("%s", "SDL2: Draw Poly_FT4 (ANIM)");

        RGBA32 shading = {
            poly.R0(),
            poly.G0(),
            poly.B0(),
            255
        };

        if (!poly.mIsShaded)
        {
            shading.a = 0;
        }

        AnimResource& animRes = poly.mAnim->mAnimRes;
        const PerFrameInfo* pHeader = poly.mAnim->Get_FrameHeader(-1);
        std::shared_ptr<PngData> pPng = animRes.mPngPtr;

        tex =
            PrepareTextureFromPoly(poly)->GetTextureUsePalette(
                poly.mAnim->mAnimRes.mPngPtr->mPal,
                shading,
                poly.mSemiTransparent,
                poly.mBlendMode
            );

        // Fiddle with UVs...
        f32 u0 = static_cast<f32>(pHeader->mSpriteSheetX) / pPng->mWidth;
        f32 v0 = static_cast<f32>(pHeader->mSpriteSheetY) / pPng->mHeight;
        f32 u1 = u0 + (static_cast<f32>(pHeader->mSpriteWidth) / pPng->mWidth);
        f32 v1 = v0 + (static_cast<f32>(pHeader->mSpriteHeight) / pPng->mHeight);

        if (poly.mFlipX)
        {
            std::swap(u0, u1);
        }

        if (poly.mFlipY)
        {
            std::swap(v0, v1);
        }

        vertices[0].tex_coord.x = u0;
        vertices[0].tex_coord.y = v0;

        vertices[1].tex_coord.x = u1;
        vertices[1].tex_coord.y = v0;

        vertices[2].tex_coord.x = u0;
        vertices[2].tex_coord.y = v1;

        vertices[3].tex_coord.x = u1;
        vertices[3].tex_coord.y = v1;
    }
    else if (poly.mFont)
    {
        LOG("%s", "SDL2: Draw Poly_FT4 (Font)");

        // TODO: Implement this
    }
    else // Assume ScreenWave!
    {
        LOG("%s", "SDL2: Draw Poly_FT4 (ScreenWave)");

        // TODO: Implement this
    }

    SDL_RenderGeometry(mContext.GetRenderer(), tex, vertices.data(), 4, indexList, 6);
}

void Sdl2Renderer::Draw(const Poly_G4& poly)
{
    LOG("%s", "SDL2: Draw Poly_G4");

    // FIXME: Obviously unfinished (no blending, etc.)
    std::vector<SDL_Vertex> vertices = {
        { { static_cast<f32>(poly.X0()), static_cast<f32>(poly.Y0()) }, { poly.R0(), poly.G0(), poly.B0(), 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X1()), static_cast<f32>(poly.Y1()) }, { poly.R1(), poly.G1(), poly.B1(), 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X2()), static_cast<f32>(poly.Y2()) }, { poly.R2(), poly.G2(), poly.B2(), 255 }, { 0, 0 } },

        { { static_cast<f32>(poly.X1()), static_cast<f32>(poly.Y1()) }, { poly.R1(), poly.G1(), poly.B1(), 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X2()), static_cast<f32>(poly.Y2()) }, { poly.R2(), poly.G2(), poly.B2(), 255 }, { 0, 0 } },
        { { static_cast<f32>(poly.X3()), static_cast<f32>(poly.Y3()) }, { poly.R3(), poly.G3(), poly.B3(), 255 }, { 0, 0 } },
    };

    ScaleVertices(vertices);

    SDL_RenderGeometry(mContext.GetRenderer(), NULL, vertices.data(), 6, NULL, 0);
}

void Sdl2Renderer::EndFrame()
{
    LOG("%s", "SDL2: End frame");

    mTextureCache.DecreaseResourceLifetimes();

    mContext.UseScreenFramebuffer();

    // FIXME: Just drawing the whole thing for now - handle this properly
    //        with screen offset + aspect ratio (centred)
    SDL_RenderCopy(mContext.GetRenderer(), GetActiveFbTexture().GetTexture(), NULL, NULL);

    mContext.Present();
}

void Sdl2Renderer::SetClip(const Prim_ScissorRect& clipper)
{
    LOG("%s", "SDL2: Set viewport clip");

    // FIXME: Implement this
    SDL_Rect rect;

    rect.x = clipper.mRect.x;
    rect.y = clipper.mRect.y;
    rect.w = clipper.mRect.w;
    rect.h = clipper.mRect.h;

    SDL_SetClipRect(SDL_GetWindowSurface(mWindow), &rect);
}

void Sdl2Renderer::StartFrame()
{
    LOG("%s", "SDL2: Start frame");

    IRenderer::StartFrame();

    mOffsetX = 0;
    mOffsetY = 0;

    // FIXME: Need to check if framebuffer textures require resizing here!

    // Default back to render target
    mContext.UseTextureFramebuffer(mPsxFbTexture[0].GetTexture());
}

Sdl2Texture& Sdl2Renderer::GetActiveFbTexture()
{
    return mPsxFbTexture[mActiveFbTexture];
}

std::shared_ptr<Sdl2Texture> Sdl2Renderer::PrepareTextureFromPoly(const Poly_FT4& poly)
{
    static u32 lastTouchedCamId = 0;

    std::shared_ptr<Sdl2Texture> texture;

    if (poly.mFg1)
    {
        // TODO: Implement this
        // FIXME: kCamLifetime should be in IRenderer ?
        texture = mTextureCache.GetCachedTexture(poly.mFg1->mUniqueId.Id(), 1);

        if (!texture)
        {
            std::shared_ptr<Sdl2Texture> camRefTex = mTextureCache.GetCachedTexture(lastTouchedCamId, 1);
            std::shared_ptr<Sdl2Texture> fg1Tex = Sdl2Texture::FromMask(mContext, camRefTex, poly.mFg1->mImage.mPixels->data());

            texture =
                mTextureCache.Add(
                    poly.mFg1->mUniqueId.Id(),
                    1,
                    fg1Tex
                );

            LOG("SDL2 FG1 cache miss %u", poly.mFg1->mUniqueId.Id());
        }
    }
    else if (poly.mCam)
    {
        lastTouchedCamId = poly.mCam->mUniqueId.Id();

        // FIXME: kCamLifetime should be in IRenderer ?
        texture = mTextureCache.GetCachedTexture(poly.mCam->mUniqueId.Id(), 1);

        if (!texture)
        {
            auto camTex =
                std::make_shared<Sdl2Texture>(
                    mContext,
                    poly.mCam->mData.mWidth,
                    poly.mCam->mData.mHeight,
                    SDL_PIXELFORMAT_RGBA32,
                    SDL_TEXTUREACCESS_STATIC
                );

            camTex->Update(NULL, poly.mCam->mData.mPixels->data());

            texture =
                mTextureCache.Add(
                    poly.mCam->mUniqueId.Id(),
                    1,
                    camTex
                );

            LOG("SDL2 CAM cache miss %u", poly.mCam->mUniqueId.Id());
        }
    }
    else if (poly.mAnim)
    {
        // FIXME: Temp bump amount
        texture = mTextureCache.GetCachedTexture(poly.mAnim->mAnimRes.mUniqueId.Id(), 255);

        if (!texture)
        {
            auto animTex =
                std::make_shared<Sdl2Texture>(
                    mContext,
                    poly.mAnim->mAnimRes.mPngPtr->mWidth,
                    poly.mAnim->mAnimRes.mPngPtr->mHeight,
                    SDL_PIXELFORMAT_INDEX8,
                    SDL_TEXTUREACCESS_STREAMING
                );

            animTex->Update(NULL, poly.mAnim->mAnimRes.mPngPtr->mPixels.data());

            texture =
                mTextureCache.Add(
                    poly.mAnim->mAnimRes.mUniqueId.Id(),
                    255,
                    animTex
                );
        }
    }
    else if (poly.mFont)
    {
        // TODO: Implement this
    }

    return texture;
}

SDL_FPoint Sdl2Renderer::PointToViewport(const SDL_FPoint& point)
{
    if (mUseOriginalResolution)
    {
        return point;
    }

    SDL_Rect   wndRect     = GetTargetDrawRect();
    SDL_FPoint scaledPoint = {
        point.x * (wndRect.w / kPsxFramebufferWidth),
        point.y * (wndRect.h / kPsxFramebufferHeight)
    };

    return scaledPoint;
}

void Sdl2Renderer::ScaleVertices(std::vector<SDL_Vertex>& vertices)
{
    for (u8 i = 0; i < vertices.size(); i++)
    {
        vertices[i].position = PointToViewport(vertices[i].position);
    }
}