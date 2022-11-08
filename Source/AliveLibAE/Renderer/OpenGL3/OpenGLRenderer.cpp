#include <algorithm>

#include "../relive_lib/data_conversion/rgb_conversion.hpp"
#include "../relive_lib/Primitives.hpp"
#include "../relive_lib/Animation.hpp"
#include "../../Compression.hpp"
#include "../../Font.hpp"
#include "../AliveLibCommon/FatalError.hpp"
#include "GLDebug.hpp"
#include "OpenGLRenderer.hpp"

#define GL_TO_IMGUI_TEX(v) *reinterpret_cast<ImTextureID*>(&v)


static bool gRenderEnable_Batching = true;

static bool gRenderEnable_SPRT = true;
static bool gRenderEnable_GAS = true;
static bool gRenderEnable_TILE = true;
static bool gRenderEnable_FT4 = true;
static bool gRenderEnable_G4 = true;
static bool gRenderEnable_G3 = true;
static bool gRenderEnable_G2 = true;
static bool gRenderEnable_F4 = true;
static bool gRenderEnable_F3 = true;
static bool gRenderEnable_F2 = true;

static const f32 pi = 3.14f;
static const f32 halfPi = 1.57f;

static GLuint Renderer_CreateTexture(GLenum interpolation = GL_NEAREST)
{
    GLuint textureId = 0;

    GL_VERIFY(glGenTextures(1, &textureId));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, textureId));

    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interpolation));
    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interpolation));

    return textureId;
}

u32 OpenGLRenderer::PreparePalette(AnimationPal& pCache)
{
    // Check we don't already have this palette
    const u32 paletteHash = HashPalette(&pCache);
    auto searchResult = mPaletteCache.find(paletteHash);

    if (searchResult != std::end(mPaletteCache))
    {
        searchResult->second.mInUse = true;
        return searchResult->second.mIndex; // Palette index
    }

    // Get an index for the new palette
    u32 nextIndex = static_cast<u32>(mPaletteCache.size());

    if (nextIndex >= GL_AVAILABLE_PALETTES)
    {
        // Look for a unused slot
        u32 unusedPaletteHash = 0;

        auto iter = mPaletteCache.begin();
        while (iter != mPaletteCache.end())
        {
            if (!iter->second.mInUse)
            {
                // Found an unused one
                unusedPaletteHash = iter->first;
                break;
            }
            iter++;
        }

        if (iter == std::end(mPaletteCache))
        {
            ALIVE_FATAL("Ran out of palettes!");
        }

        // Acquire the index we're taking over
        nextIndex = iter->second.mIndex;

        // Bin the old one
        mPaletteCache.erase(unusedPaletteHash);
    }

    mPaletteCache[paletteHash] = PalCacheEntry{nextIndex, true};

    // Write palette data
    mPaletteTexture->LoadSubImage(0, nextIndex, GL_PALETTE_DEPTH, 1, pCache.mPal);

    mStats.mPalUploadCount++;

    return nextIndex;
}

u32 OpenGLRenderer::HashPalette(const AnimationPal* pPal)
{
    // This is the 'djb2' algorithm
    u32 hash = 5381;

    for (int i = 0; i < GL_PALETTE_DEPTH; i++)
    {
        hash = ((hash << 5) + hash) + pPal->mPal[i].r;
        hash = ((hash << 5) + hash) + pPal->mPal[i].g;
        hash = ((hash << 5) + hash) + pPal->mPal[i].b;
        hash = ((hash << 5) + hash) + pPal->mPal[i].a;
    }

    return hash;
}

GLuint OpenGLRenderer::CreateCachedTexture(u32 uniqueId, u32 lifetime)
{
    CachedTexture newTex;
    const GLuint texId = Renderer_CreateTexture();

    newTex.mTextureId = texId;
    newTex.mLifetime = lifetime;

    mTextureCache[uniqueId] = newTex;

    return texId;
}

GLuint OpenGLRenderer::GetCachedTextureId(u32 uniqueId, s32 bump)
{
    auto it = mTextureCache.find(uniqueId);

    if (it == mTextureCache.end())
    {
        return 0;
    }

    if (bump > 0)
    {
        // Bump!
        CachedTexture bumpTex;

        bumpTex.mTextureId = it->second.mTextureId;
        bumpTex.mLifetime = bump;

        mTextureCache[uniqueId] = bumpTex;
    }

    return it->second.mTextureId;
}

u32 OpenGLRenderer::PrepareTextureFromAnim(Animation& anim)
{
    const AnimResource& r = anim.mAnimRes;

    u32 textureId = GetCachedTextureId(r.mUniqueId.Id(), GL_SPRITE_TEXTURE_LIFETIME);

    if (textureId == 0)
    {
        textureId = CreateCachedTexture(r.mUniqueId.Id(), GL_SPRITE_TEXTURE_LIFETIME);

        GL_VERIFY(glBindTexture(GL_TEXTURE_2D, textureId));
        GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, r.mTgaPtr->mWidth, r.mTgaPtr->mHeight, 0, GL_RED, GL_UNSIGNED_BYTE, r.mTgaPtr->mPixels.data()));

        mStats.mAnimUploadCount++;
    }

    return textureId;
}

u32 OpenGLRenderer::PrepareTextureFromPoly(Poly_FT4& poly)
{
    GLuint textureId = 0;

    if (poly.mFg1)
    {
        textureId = GetCachedTextureId(poly.mFg1->mUniqueId.Id(), GL_CAM_TEXTURE_LIFETIME);

        if (textureId == 0)
        {
            textureId = CreateCachedTexture(poly.mFg1->mUniqueId.Id(), GL_CAM_TEXTURE_LIFETIME);

            GL_VERIFY(glBindTexture(GL_TEXTURE_2D, textureId));
            GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));
            GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, poly.mFg1->mImage.mWidth, poly.mFg1->mImage.mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, poly.mFg1->mImage.mPixels->data()));

            mStats.mFg1UploadCount++;
        }
    }
    else if (poly.mCam)
    {
        textureId = GetCachedTextureId(poly.mCam->mUniqueId.Id(), GL_CAM_TEXTURE_LIFETIME);

        if (textureId == 0)
        {
            textureId = CreateCachedTexture(poly.mCam->mUniqueId.Id(), GL_CAM_TEXTURE_LIFETIME);

            GL_VERIFY(glBindTexture(GL_TEXTURE_2D, textureId));
            GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));
            GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, poly.mCam->mData.mWidth, poly.mCam->mData.mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, poly.mCam->mData.mPixels->data()));

            mStats.mCamUploadCount++;
        }
    }
    else if (poly.mAnim)
    {
        return PrepareTextureFromAnim(*poly.mAnim);
    }
    else if (poly.mFont)
    {
        textureId = GetCachedTextureId(poly.mFont->field_C_resource_id.mUniqueId.Id(), GL_SPRITE_TEXTURE_LIFETIME);

        if (textureId == 0)
        {
            std::shared_ptr<TgaData> pTga = poly.mFont->field_C_resource_id.mTgaPtr;

            textureId = CreateCachedTexture(poly.mFont->field_C_resource_id.mUniqueId.Id(), GL_SPRITE_TEXTURE_LIFETIME);

            GL_VERIFY(glBindTexture(GL_TEXTURE_2D, textureId));
            GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, pTga->mWidth, pTga->mHeight, 0, GL_RED, GL_UNSIGNED_BYTE, pTga->mPixels.data()));

            mStats.mFontUploadCount++;
        }
    }

    return textureId;
}

void OpenGLRenderer::Clear(u8 r, u8 g, u8 b)
{
    if (!mFrameStarted || SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MINIMIZED)
    {
        return;
    }

    GLboolean scissoring;

    GL_VERIFY(glGetBooleanv(GL_SCISSOR_TEST, &scissoring));

    // We clear the screen framebuffer here
    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    if (scissoring)
    {
        GL_VERIFY(glDisable(GL_SCISSOR_TEST));
    }

    GL_VERIFY(glClearColor((f32) r, (f32) g, (f32) b, 1.0f));
    GL_VERIFY(glClear(GL_COLOR_BUFFER_BIT));

    // Set back to the PSX framebuffer
    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, mPsxFramebufferId));

    if (scissoring)
    {
        GL_VERIFY(glEnable(GL_SCISSOR_TEST));
    }
}

bool OpenGLRenderer::Create(TWindowHandleType window)
{
    mWindow = window;

    // Find the opengl driver
    const s32 numDrivers = SDL_GetNumRenderDrivers();
    if (numDrivers < 0)
    {
        LOG_ERROR("Failed to get driver count %s", SDL_GetError());
    }

    LOG_INFO("Got %d drivers", numDrivers);

    s32 index = -1;
    for (s32 i = 0; i < numDrivers; i++)
    {
        SDL_RendererInfo info = {};
        if (SDL_GetRenderDriverInfo(i, &info) < 0)
        {
            LOG_WARNING("Failed to get render %d info %s", i, SDL_GetError());
        }
        else
        {
            LOG_INFO("%d name %s", i, info.name ? info.name : "(null)");
            if (info.name && strstr(info.name, "opengl"))
            {
                index = i;
                break;
            }
        }
    }

    if (index == -1)
    {
        LOG_WARNING("OpenGL SDL2 driver not found");
        return false;
    }


    // We should attempt to load OpenGL 3.2 first, because this is the minimum
    // required version for RenderDoc captures so we can actually debug stuff
    const char_type* glslVer150 = "#version 150";
    const char_type* glslVer140 = "#version 140";

    bool glslVer150Supported = true;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create context
    mContext = SDL_GL_CreateContext(window);

    if (mContext == NULL)
    {
        LOG_ERROR("OpenGL 3.2 context could not be created! SDL Error: %s", SDL_GetError());

        // Our ACTUAL minimum OpenGL requirement is 3.1, though we will check
        // supported extensions on the GPU in a moment
        glslVer150Supported = false;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create context
        mContext = SDL_GL_CreateContext(window);
        if (mContext == NULL)
        {
            LOG_ERROR("OpenGL 3.1 context could not be created! SDL Error: %s", SDL_GetError());
            return false;
        }
    }

    LOG_INFO("GL_VERSION = %s", glGetString(GL_VERSION));

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK)
    {
        LOG_ERROR("Error initializing GLEW! %s", glewGetErrorString(glewError));
    }

    // Use Vsync
    // FIXME: VSYNC disabled for now - remove before merge to master!
    if (SDL_GL_SetSwapInterval(0) < 0)
    {
        LOG_ERROR("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());
    }

    // Check supported extensions by the GPU
    if (!glewIsSupported("GL_ARB_vertex_array_object GL_ARB_framebuffer_object GL_ARB_explicit_attrib_location"))
    {
        ALIVE_FATAL("Your graphics device is not supported, sorry!");
    }

    ImGui::CreateContext();

    // Setup IMGUI for texture debugging
    ImGui_ImplSDL2_InitForOpenGL(mWindow, mContext);
    ImGui_ImplOpenGL3_Init(glslVer150Supported ? glslVer150 : glslVer140);

    // Create and bind the VAO, and never touch it again! Wahey.
    GL_VERIFY(glGenVertexArrays(1, &mVAO));
    GL_VERIFY(glBindVertexArray(mVAO));

    // FIXME: Temp - init palette here for now
    const static RGBA32 black[256] = {};

    mPaletteTexture = std::make_unique<GLTexture2D>(GL_PALETTE_DEPTH, GL_AVAILABLE_PALETTES, GL_RGBA, true);

    for (s32 i = 0; i < GL_AVAILABLE_PALETTES; i++)
    {
        mPaletteTexture->LoadSubImage(0, i, GL_PALETTE_DEPTH, 1, black);
    }

    // Load shaders
    mPassthruShader.LoadSource(gShader_PassthruVSH, gShader_PassthruFSH);
    mPassthruIntShader.LoadSource(gShader_PassthruIntVSH, gShader_PassthruFSH);
    mPassthruFilterShader.LoadSource(gShader_PassthruVSH, gShader_PassthruFilterFSH);
    mPsxShader.LoadSource(gShader_PsxVSH, gShader_PsxFSH);

    // ROZZA Blending
    GL_VERIFY(glEnable(GL_BLEND));
    GL_VERIFY(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Init framebuffers
    CreateFramebuffer(&mPsxFramebufferId, &mPsxFramebufferTexId, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT);
    CreateFramebuffer(&mPsxFramebufferSecondId, &mPsxFramebufferSecondTexId,GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT);
    CreateFramebuffer(&mFilterFramebufferId, &mFilterFramebufferTexId, GL_FRAMEBUFFER_FILTER_WIDTH, GL_FRAMEBUFFER_FILTER_HEIGHT);

    // Init batch vectors
    mCurFG1TextureIds.reserve(4);
    mBatchData.reserve(GL_RESERVE_QUADS * 4);
    mBatchIndicies.reserve(GL_RESERVE_QUADS * 6);
    mBatchTextureIds.reserve(GL_USE_NUM_TEXTURE_UNITS);
    mScreenWaveData.reserve(GL_RESERVE_SCREENWAVE_QUADS * 4);
    mScreenWaveIndicies.reserve(GL_RESERVE_SCREENWAVE_QUADS * 6);

    // Init array we pass to texture uniform to specify the units we're using
    // which is the number of units starting at GL_TEXTURE7
    for (int i = 0; i < GL_USE_NUM_TEXTURE_UNITS; i++)
    {
        mTextureUnits[i] = i + 7;
    }

    return true;
}

void OpenGLRenderer::CreateFramebuffer(GLuint* outFramebufferId, GLuint* outTextureId, s32 width, s32 height)
{
    static const GLenum fbTargets[1] = {GL_COLOR_ATTACHMENT0};

    // Create objects
    GL_VERIFY(glGenFramebuffers(1, outFramebufferId));
    GL_VERIFY(glGenTextures(1, outTextureId));

    // Init texture
    GL_VERIFY(glActiveTexture(GL_TEXTURE0));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, *outTextureId));

    GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));

    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    // Init framebuffer
    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, *outFramebufferId));
    GL_VERIFY(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *outTextureId, 0));

    GL_VERIFY(glDrawBuffers(1, fbTargets));
}

void OpenGLRenderer::Destroy()
{
    ImGui_ImplSDL2_Shutdown();

    mPassthruShader.Free();
    mPsxShader.Free();

    for (auto& it : mTextureCache)
    {
        GL_VERIFY(glDeleteTextures(1, &it.second.mTextureId));
    }
    mTextureCache.clear();

    GL_VERIFY(glUseProgram(0));

    GL_VERIFY(glDeleteTextures(1, &mCurGasTextureId));

    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GL_VERIFY(glDeleteFramebuffers(1, &mPsxFramebufferId));
    GL_VERIFY(glDeleteTextures(1, &mPsxFramebufferTexId));

    if (mContext)
    {
        SDL_GL_DeleteContext(mContext);
        mContext = nullptr;
    }
}

void OpenGLRenderer::Draw(Prim_Sprt& sprt)
{
    if (!gRenderEnable_SPRT)
    {
        return;
    }

    if (sprt.mAnim == nullptr)
    {
        return;
    }

    std::shared_ptr<TgaData> pTga = sprt.mAnim->mAnimRes.mTgaPtr;

    const u32 sprtTextureId = PrepareTextureFromAnim(*sprt.mAnim);
    const u32 palIndex = PreparePalette(*sprt.mAnim->mAnimRes.mCurPal);

    u32 r = sprt.mBase.header.rgb_code.r;
    u32 g = sprt.mBase.header.rgb_code.g;
    u32 b = sprt.mBase.header.rgb_code.b;

    u32 texW = (u32) sprt.field_14_w;
    u32 texH = (u32) sprt.field_16_h;

    u32 u0 = U0(&sprt);
    u32 v0 = V0(&sprt);

    u32 u1 = U0(&sprt) + texW;
    u32 v1 = V0(&sprt) + texH;

    const bool isSemiTrans = GetPolyIsSemiTrans(&sprt);
    const bool isShaded = GetPolyIsShaded(&sprt);
    const u16 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[4] = {
        {sprt.mBase.vert.x, sprt.mBase.vert.y, r, g, b, u0, v0, texW, texH, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
        {sprt.mBase.vert.x + sprt.field_14_w, sprt.mBase.vert.y, r, g, b, u1, v0, texW, texH, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
        {sprt.mBase.vert.x, sprt.mBase.vert.y + sprt.field_16_h, r, g, b, u0, v1, texW, texH, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
        {sprt.mBase.vert.x + sprt.field_14_w, sprt.mBase.vert.y + sprt.field_16_h, r, g, b, u1, v1, texW, texH, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0}};

    PushVertexData(verts, 4, sprtTextureId);
}

void OpenGLRenderer::Draw(Prim_GasEffect& gasEffect)
{
    if (!gRenderEnable_GAS)
    {
        return;
    }

    if (mCurGasTextureId == 0)
    {
        mCurGasTextureId = Renderer_CreateTexture();
    }

    if (gasEffect.pData == nullptr)
    {
        return;
    }

    s32 gasWidth = (gasEffect.w - gasEffect.x);
    s32 gasHeight = (gasEffect.h - gasEffect.y);

    GL_VERIFY(glActiveTexture(GL_TEXTURE0));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mCurGasTextureId));
    GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, gasWidth / 4, gasHeight / 2, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, gasEffect.pData));

    u32 r = 127;
    u32 g = 127;
    u32 b = 127;

    bool isSemiTrans = true;
    bool isShaded = true;
    u32 blendMode = (u32) TPageAbr::eBlend_0;

    VertexData verts[4] = {
        {gasEffect.x, gasEffect.y, r, g, b, 0, 0, (u32) gasWidth, (u32) gasHeight, GL_PSX_DRAW_MODE_GAS, isSemiTrans, isShaded, blendMode, 0, 0},
        {gasEffect.w, gasEffect.y, r, g, b, (u32) gasWidth, 0, (u32) gasWidth, (u32) gasHeight, GL_PSX_DRAW_MODE_GAS, isSemiTrans, isShaded, blendMode, 0, 0},
        {gasEffect.x, gasEffect.h, r, g, b, 0, (u32) gasHeight, (u32) gasWidth, (u32) gasHeight, GL_PSX_DRAW_MODE_GAS, isSemiTrans, isShaded, blendMode, 0, 0},
        {gasEffect.w, gasEffect.h, r, g, b, (u32) gasWidth, (u32) gasHeight, (u32) gasWidth, (u32) gasHeight, GL_PSX_DRAW_MODE_GAS, isSemiTrans, isShaded, blendMode, 0, 0}};
    
    PushVertexData(verts, 4, mCurGasTextureId);
}

void OpenGLRenderer::Draw(Prim_Tile& tile)
{
    if (!gRenderEnable_TILE)
    {
        return;
    }

    const u32 r = tile.mBase.header.rgb_code.r;
    const u32 g = tile.mBase.header.rgb_code.g;
    const u32 b = tile.mBase.header.rgb_code.b;

    bool isSemiTrans = GetPolyIsSemiTrans(&tile);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[4] = {
        {tile.mBase.vert.x, tile.mBase.vert.y, r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {tile.mBase.vert.x + tile.field_14_w, tile.mBase.vert.y, r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {tile.mBase.vert.x, tile.mBase.vert.y + tile.field_16_h, r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {tile.mBase.vert.x + tile.field_14_w, tile.mBase.vert.y + tile.field_16_h, r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushVertexData(verts, 4);
}

void OpenGLRenderer::Draw(Line_F2& line)
{
    static const f32 lineThickness = 1;

    if (!gRenderEnable_F2)
    {
        return;
    }

    const u32 r = R0(&line);
    const u32 g = G0(&line);
    const u32 b = B0(&line);

    bool isSemiTrans = GetPolyIsSemiTrans(&line);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[2] = {
        {X0(&line), Y0(&line), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&line), Y1(&line), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushLines(verts, 2);
}

void OpenGLRenderer::Draw(Line_G2& line)
{
    if (!gRenderEnable_G2)
    {
        return;
    }

    bool isSemiTrans = GetPolyIsSemiTrans(&line);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[2] = {
        {X0(&line), Y0(&line), R0(&line), G0(&line), B0(&line), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&line), Y1(&line), R1(&line), G1(&line), B1(&line), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushLines(verts, 2);
}

void OpenGLRenderer::Draw(Line_G4& line)
{
    if (!gRenderEnable_G4)
    {
        return;
    }

    bool isSemiTrans = GetPolyIsSemiTrans(&line);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[4] = {
        {X0(&line), Y0(&line), R0(&line), G0(&line), B0(&line), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&line), Y1(&line), R1(&line), G1(&line), B1(&line), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X2(&line), Y2(&line), R2(&line), G2(&line), B2(&line), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X3(&line), Y3(&line), R3(&line), G3(&line), B3(&line), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushLines(verts, 4);
}

void OpenGLRenderer::Draw(Poly_F3& poly)
{
    if (!gRenderEnable_F3)
    {
        return;
    }

    const u32 r = R0(&poly);
    const u32 g = G0(&poly);
    const u32 b = B0(&poly);

    bool isSemiTrans = GetPolyIsSemiTrans(&poly);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[3] = {
        {X0(&poly), Y0(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&poly), Y1(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X2(&poly), Y2(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushVertexData(verts, 3);
}

void OpenGLRenderer::Draw(Poly_G3& poly)
{
    if (!gRenderEnable_G3)
    {
        return;
    }

    bool isSemiTrans = GetPolyIsSemiTrans(&poly);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[3] = {
        {X0(&poly), Y0(&poly), R0(&poly), G0(&poly), B0(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&poly), Y1(&poly), R1(&poly), G1(&poly), B1(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X2(&poly), Y2(&poly), R2(&poly), G2(&poly), B2(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushVertexData(verts, 3);
}

void OpenGLRenderer::Draw(Poly_F4& poly)
{
    if (!gRenderEnable_F4)
    {
        return;
    }

    const u32 r = R0(&poly);
    const u32 g = G0(&poly);
    const u32 b = B0(&poly);

    bool isSemiTrans = GetPolyIsSemiTrans(&poly);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[4] = {
        {X0(&poly), Y0(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&poly), Y1(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X2(&poly), Y2(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X3(&poly), Y3(&poly), r, g, b, 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushVertexData(verts, 4);
}

void OpenGLRenderer::Draw(Poly_FT4& poly)
{
    if (!gRenderEnable_FT4)
    {
        return;
    }

    const u32 textureId = PrepareTextureFromPoly(poly);

    u32 r = poly.mBase.header.rgb_code.r;
    u32 g = poly.mBase.header.rgb_code.g;
    u32 b = poly.mBase.header.rgb_code.b;

    bool isSemiTrans = GetPolyIsSemiTrans(&poly);
    bool isShaded = GetPolyIsShaded(&poly);
    u32 blendMode = GetTPageBlendMode(GetTPage(&poly));

    if (poly.mFg1)
    {
        VertexData verts[4] = {
            {poly.mBase.vert.x, poly.mBase.vert.y, r, g, b, 0, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_FG1, isSemiTrans, isShaded, blendMode, 0, 0},
            {poly.mVerts[0].mVert.x, poly.mVerts[0].mVert.y, r, g, b, GL_FRAMEBUFFER_PSX_WIDTH, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_FG1, isSemiTrans, isShaded, blendMode, 0, 0},
            {poly.mVerts[1].mVert.x, poly.mVerts[1].mVert.y, r, g, b, 0, GL_FRAMEBUFFER_PSX_HEIGHT, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_FG1, isSemiTrans, isShaded, blendMode, 0, 0},
            {poly.mVerts[2].mVert.x, poly.mVerts[2].mVert.y, r, g, b, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_FG1, isSemiTrans, isShaded, blendMode, 0, 0}};

        PushVertexData(verts, 4, textureId);
    }
    else if (poly.mCam)
    {
        VertexData verts[4] = {
            {poly.mBase.vert.x, poly.mBase.vert.y, r, g, b, 0, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_CAM, isSemiTrans, isShaded, blendMode, 0, 0},
            {poly.mVerts[0].mVert.x, poly.mVerts[0].mVert.y, r, g, b, GL_FRAMEBUFFER_PSX_WIDTH, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_CAM, isSemiTrans, isShaded, blendMode, 0, 0},
            {poly.mVerts[1].mVert.x, poly.mVerts[1].mVert.y, r, g, b, 0, GL_FRAMEBUFFER_PSX_HEIGHT, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_CAM, isSemiTrans, isShaded, blendMode, 0, 0},
            {poly.mVerts[2].mVert.x, poly.mVerts[2].mVert.y, r, g, b, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_PSX_DRAW_MODE_CAM, isSemiTrans, isShaded, blendMode, 0, 0}};

        PushVertexData(verts, 4, textureId);
    }
    else if (poly.mAnim)
    {
        const PerFrameInfo* pHeader = poly.mAnim->Get_FrameHeader(-1);
        std::shared_ptr<TgaData> pTga = poly.mAnim->mAnimRes.mTgaPtr;

        const u32 palIndex = PreparePalette(*poly.mAnim->mAnimRes.mCurPal);

        u32 u0 = pHeader->mSpriteSheetX;
        u32 v0 = pHeader->mSpriteSheetY;

        u32 u1 = u0 + pHeader->mWidth;
        u32 v1 = v0 + pHeader->mHeight;

        if (poly.mFlipX)
        {
            std::swap(u0, u1);
        }

        if (poly.mFlipY)
        {
            std::swap(v1, v0);
        }

        VertexData verts[4] = {
            {poly.mBase.vert.x, poly.mBase.vert.y, r, g, b, u0, v0, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
            {poly.mVerts[0].mVert.x, poly.mVerts[0].mVert.y, r, g, b, u1, v0, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
            {poly.mVerts[1].mVert.x, poly.mVerts[1].mVert.y, r, g, b, u0, v1, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
            {poly.mVerts[2].mVert.x, poly.mVerts[2].mVert.y, r, g, b, u1, v1, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0}};
        
        PushVertexData(verts, 4, textureId);
    }
    else if (poly.mFont)
    {
        FontResource& fontRes = poly.mFont->field_C_resource_id;
        std::shared_ptr<TgaData> pTga = fontRes.mTgaPtr;

        auto pPal = fontRes.mCurPal;
        const u32 palIndex = PreparePalette(*pPal);

        u32 u0 = U0(&poly);
        u32 v0 = V0(&poly);

        u32 u1 = U3(&poly);
        u32 v1 = V3(&poly);

        VertexData verts[4] = {
            {poly.mBase.vert.x, poly.mBase.vert.y, r, g, b, u0, v0, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
            {poly.mVerts[0].mVert.x, poly.mVerts[0].mVert.y, r, g, b, u1, v0, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
            {poly.mVerts[1].mVert.x, poly.mVerts[1].mVert.y, r, g, b, u0, v1, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0},
            {poly.mVerts[2].mVert.x, poly.mVerts[2].mVert.y, r, g, b, u1, v1, pTga->mWidth, pTga->mHeight, GL_PSX_DRAW_MODE_DEFAULT_FT4, isSemiTrans, isShaded, blendMode, palIndex, 0}};

        PushVertexData(verts, 4, textureId);
    }
    else
    {
        // ScreenWave (Bell Song framebuffer effect)

        VertexData verts[4] = {
            {X0(&poly), Y0(&poly), 0, 0, 0, U0(&poly), V0(&poly), GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0},
            {X1(&poly), Y1(&poly), 0, 0, 0, U1(&poly), V1(&poly), GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0},
            {X2(&poly), Y2(&poly), 0, 0, 0, U2(&poly), V2(&poly), GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0},
            {X3(&poly), Y3(&poly), 0, 0, 0, U3(&poly), V3(&poly), GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0}
        };

        PushScreenWaveData(verts);
    }
}

void OpenGLRenderer::Draw(Poly_G4& poly)
{
    if (!gRenderEnable_G4)
    {
        return;
    }

    bool isSemiTrans = GetPolyIsSemiTrans(&poly);
    bool isShaded = true;
    u32 blendMode = GetTPageBlendMode(mGlobalTPage);

    VertexData verts[4] = {
        {X0(&poly), Y0(&poly), R0(&poly), G0(&poly), B0(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X1(&poly), Y1(&poly), R1(&poly), G1(&poly), B1(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X2(&poly), Y2(&poly), R2(&poly), G2(&poly), B2(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0},
        {X3(&poly), Y3(&poly), R3(&poly), G3(&poly), B3(&poly), 0, 0, 0, 0, GL_PSX_DRAW_MODE_FLAT, isSemiTrans, isShaded, blendMode, 0, 0}};

    PushVertexData(verts, 4);
}

void OpenGLRenderer::EndFrame()
{
    // Ensure any remaining data is drawn
    InvalidateBatch();
    RenderScreenWave();

    // Always decrease resource lifetimes regardless of drawing to prevent
    // memory leaks
    DecreaseResourceLifetimes();

    // The rest of this method writes to the screen, we early return now
    // because:
    //     Sometimes EndFrame is called before StartFrame
    //     When minimised, rendering to the screen blows up Intel HD 2000
    if (!mFrameStarted || SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MINIMIZED)
    {
        return;
    }

    // Draw the final composed framebuffer to the screen
    SDL_Rect drawRect = GetTargetDrawRect();

    GL_VERIFY(glDisable(GL_SCISSOR_TEST));
    DrawFramebufferToScreen(
        drawRect.x,
        drawRect.y,
        drawRect.w,
        drawRect.h);

    // Do ImGui


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(mWindow);
    ImGui::NewFrame();

    DebugWindow();

    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Throw away any errors caused by ImGui - this is necessary for AMD GPUs
    // (AMD Radeon HD 7310 with driver 8.982.10.5000)
    glGetError();

    // Render end
    SDL_GL_SwapWindow(mWindow);

    mFrameStarted = false;

    // Set the framebuffer target back to the PSX framebuffer
    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, mPsxFramebufferId));
}

void OpenGLRenderer::OutputSize(s32* w, s32* h)
{
    SDL_GL_GetDrawableSize(mWindow, w, h);
}

void OpenGLRenderer::SetClip(Prim_PrimClipper& clipper)
{
    SDL_Rect rect;
    rect.x = clipper.field_C_x;
    rect.y = clipper.field_E_y;
    rect.w = clipper.mBase.header.mRect.w;
    rect.h = clipper.mBase.header.mRect.h;

    InvalidateBatch();

    if (rect.x == 0 && rect.y == 0 && rect.w == 1 && rect.h == 1)
    {
        GL_VERIFY(glDisable(GL_SCISSOR_TEST));
        return;
    }

    GL_VERIFY(glEnable(GL_SCISSOR_TEST));
    GL_VERIFY(glScissor(rect.x, GL_FRAMEBUFFER_PSX_HEIGHT - rect.y - rect.h, rect.w, rect.h));
}

void OpenGLRenderer::SetScreenOffset(Prim_ScreenOffset& offset)
{
    mOffsetX = offset.field_C_xoff;
    mOffsetY = offset.field_E_yoff;
}

void OpenGLRenderer::SetTPage(u16 tPage)
{
    mGlobalTPage = tPage;
}

void OpenGLRenderer::StartFrame(s32 xOff, s32 yOff)
{
    if (SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MINIMIZED)
    {
        return;
    }

    mStats.Reset();

    mFrameStarted = true;

    // Set offsets for the screen (this is for the screen shake effect)
    mOffsetX = xOff;
    mOffsetY = yOff;

    // Always render to PSX framebuffer
    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, mPsxFramebufferId));
    GL_VERIFY(glViewport(0, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT));

    // FIXME: Hack to push screenwave verts first... tidy later
    VertexData verts[4] = {
        {0, 0, 0, 0, 0, 0, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0},
        {GL_FRAMEBUFFER_PSX_WIDTH, 0, 0, 0, 0, GL_FRAMEBUFFER_PSX_WIDTH, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0},
        {0, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 0, 0, 0, GL_FRAMEBUFFER_PSX_HEIGHT, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0},
        {GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 0, 0, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT, 0, 1, 0, 1, 0, 0}
    };

    PushScreenWaveData(verts);
}

void OpenGLRenderer::ToggleFilterScreen()
{
    mFramebufferFilter = !mFramebufferFilter;
}

void OpenGLRenderer::ToggleKeepAspectRatio()
{
    mKeepAspectRatio = !mKeepAspectRatio;
}

// ROZZA FRAMEBUFFER STUFF

void OpenGLRenderer::DecreaseResourceLifetimes()
{
    // FIXME: This is a stupid location for this clear but it'll do for
    //        now
    mScreenWaveData.clear();
    mScreenWaveIndicies.clear();

    // Check texture lifetimes
    auto it = mTextureCache.begin();
    while (it != mTextureCache.end())
    {
        if (it->second.mLifetime-- <= 0)
        {
            GL_VERIFY(glDeleteTextures(1, &it->second.mTextureId));
            it = mTextureCache.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (auto iter = mPaletteCache.begin(); iter != mPaletteCache.end(); iter++)
    {
        // Default all palettes to unused for next draw
        iter->second.mInUse = false;
    }
}

void OpenGLRenderer::DrawFramebufferToScreen(s32 x, s32 y, s32 width, s32 height)
{
    // Ensure blend mode is back to normal alpha compositing
    GL_VERIFY(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_VERIFY(glBlendEquation(GL_FUNC_ADD));

    // Set up the texture we're going to draw...
    GLuint texId = 0;
    f32 texWidth = 0;
    f32 texHeight = 0;

    if (mFramebufferFilter)
    {
        UpdateFilterFramebuffer();

        texId = mFilterFramebufferTexId;
        texWidth = GL_FRAMEBUFFER_FILTER_WIDTH;
        texHeight = GL_FRAMEBUFFER_FILTER_HEIGHT;
    }
    else
    {
        texId = mPsxFramebufferSecondTexId;
        texWidth = GL_FRAMEBUFFER_PSX_WIDTH;
        texHeight = GL_FRAMEBUFFER_PSX_HEIGHT;
    }

    // Set up VBOs
    GLuint drawVboId = 0;
    GLuint uvVboId = 0;

    GLfloat drawVertices[] = {
        (f32) x, (f32) y,
        (f32) x, (f32) (y + height),
        (f32) (x + width), (f32) y,

        (f32) (x + width), (f32) y,
        (f32) x, (f32) (y + height),
        (f32) (x + width), (f32) (y + height)};
    GLfloat uvVertices[] = {
        0.0f, texHeight,
        0.0f, 0.0f,
        texWidth, texHeight,

        texWidth, texHeight,
        0.0f, 0.0f,
        texWidth, 0.0f};

    GL_VERIFY(glGenBuffers(1, &drawVboId));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, drawVboId));
    GL_VERIFY(
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(drawVertices),
            drawVertices,
            GL_STREAM_DRAW));

    GL_VERIFY(glGenBuffers(1, &uvVboId));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, uvVboId));
    GL_VERIFY(
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(uvVertices),
            uvVertices,
            GL_STREAM_DRAW));

    // Bind framebuffers and draw
    s32 viewportW, viewportH;

    SDL_GL_GetDrawableSize(mWindow, &viewportW, &viewportH);

    mPassthruShader.Use();

    mPassthruShader.Uniform1i("texTextureData", 0);
    mPassthruShader.UniformVec2("vsViewportSize", (f32) viewportW, (f32) viewportH);
    mPassthruShader.Uniform1i("fsFlipUV", false);
    mPassthruShader.UniformVec2("fsTexSize", texWidth, texHeight);

    GL_VERIFY(glViewport(0, 0, viewportW, viewportH));

    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    GL_VERIFY(glActiveTexture(GL_TEXTURE0));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, texId));

    GL_VERIFY(glEnableVertexAttribArray(0));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, drawVboId));
    GL_VERIFY(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));

    GL_VERIFY(glEnableVertexAttribArray(1));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, uvVboId));
    GL_VERIFY(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));

    GL_VERIFY(glDrawArrays(GL_TRIANGLES, 0, 6));

    GL_VERIFY(glDeleteBuffers(1, &drawVboId));
    GL_VERIFY(glDeleteBuffers(1, &uvVboId));

    GL_VERIFY(glDisableVertexAttribArray(0));
    GL_VERIFY(glDisableVertexAttribArray(1));

    mPassthruShader.UnUse();
}

void OpenGLRenderer::UpdateFilterFramebuffer()
{
    // Set up VBOs
    static GLuint drawVboId = 0;
    static GLuint uvVboId = 0;

    if (drawVboId == 0)
    {
        GLfloat drawVertices[] = {
            0.0f, 0.0f,
            0.0f, GL_FRAMEBUFFER_FILTER_HEIGHT,
            GL_FRAMEBUFFER_FILTER_WIDTH, 0.0,

            GL_FRAMEBUFFER_FILTER_WIDTH, 0.0f,
            0.0f, GL_FRAMEBUFFER_FILTER_HEIGHT,
            GL_FRAMEBUFFER_FILTER_WIDTH, GL_FRAMEBUFFER_FILTER_HEIGHT};

        GLfloat uvVertices[] = {
            0.0f, GL_FRAMEBUFFER_PSX_HEIGHT,
            0.0f, 0.0f,
            GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT,

            GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT,
            0.0f, 0.0f,
            GL_FRAMEBUFFER_PSX_WIDTH, 0.0f};

        GL_VERIFY(glGenBuffers(1, &drawVboId));
        GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, drawVboId));
        GL_VERIFY(
            glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(drawVertices),
                drawVertices,
                GL_STATIC_DRAW));

        GL_VERIFY(glGenBuffers(1, &uvVboId));
        GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, uvVboId));
        GL_VERIFY(
            glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(uvVertices),
                uvVertices,
                GL_STATIC_DRAW));
    }

    // Bind framebuffers and draw
    mPassthruFilterShader.Use();

    mPassthruFilterShader.Uniform1i("texTextureData", 0);
    mPassthruFilterShader.UniformVec2("vsViewportSize", GL_FRAMEBUFFER_FILTER_WIDTH, GL_FRAMEBUFFER_FILTER_HEIGHT);
    mPassthruFilterShader.UniformVec2("fsTexSize", GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT);

    GL_VERIFY(glViewport(0, 0, GL_FRAMEBUFFER_FILTER_WIDTH, GL_FRAMEBUFFER_FILTER_HEIGHT));

    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, mFilterFramebufferId));

    GL_VERIFY(glActiveTexture(GL_TEXTURE0));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mPsxFramebufferSecondTexId));

    GL_VERIFY(glEnableVertexAttribArray(0));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, drawVboId));
    GL_VERIFY(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));

    GL_VERIFY(glEnableVertexAttribArray(1));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, uvVboId));
    GL_VERIFY(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));

    GL_VERIFY(glDrawArrays(GL_TRIANGLES, 0, 6));

    GL_VERIFY(glDisableVertexAttribArray(0));
    GL_VERIFY(glDisableVertexAttribArray(1));

    mPassthruFilterShader.UnUse();
}

SDL_Rect OpenGLRenderer::GetTargetDrawRect()
{
    SDL_Rect rect = {};

    s32 wndWidth = 0;
    s32 wndHeight = 0;

    OutputSize(&wndWidth, &wndHeight);

    // Calculate the draw size, aspect ratio dealt with here 
    rect.w = wndWidth;
    rect.h = wndHeight;

    if (mKeepAspectRatio)
    {
        if (3 * wndWidth > 4 * wndHeight)
        {
            rect.w = (wndHeight * 4) / 3;
        }
        else
        {
            rect.h = (wndWidth * 3) / 4;
        }
    }

    // Calculate any screen shake
    s32 shakeX = static_cast<s32>(mOffsetX * (rect.w / 640.0f));
    s32 shakeY = static_cast<s32>(mOffsetY * (rect.h / 480.0f));

    rect.x = shakeX + ((wndWidth - rect.w) / 2);
    rect.y = shakeY + ((wndHeight - rect.h) / 2);

    return rect;
}

u16 OpenGLRenderer::GetTPageBlendMode(u16 tpage)
{
    return (tpage >> 4) & 3;
}

void OpenGLRenderer::RenderScreenWave()
{
    if (!mFrameStarted)
    {
        return;
    }

    // Ensure blend mode is back to normal alpha compositing
    GL_VERIFY(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_VERIFY(glBlendEquation(GL_FUNC_ADD));

    // Set up VBOs
    GLuint eboId, vboId;

    GL_VERIFY(glGenBuffers(1, &vboId));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, vboId));
    GL_VERIFY(glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * mScreenWaveData.size(), &mScreenWaveData.front(), GL_STREAM_DRAW));

    GL_VERIFY(glGenBuffers(1, &eboId));
    GL_VERIFY(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId));
    GL_VERIFY(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mScreenWaveIndicies.size(), &mScreenWaveIndicies.front(), GL_STREAM_DRAW));

    // Bind framebuffers and draw
    mPassthruIntShader.Use();

    mPassthruIntShader.Uniform1i("texTextureData", 0);
    mPassthruIntShader.UniformVec2("vsViewportSize", (f32) GL_FRAMEBUFFER_PSX_WIDTH, (f32) GL_FRAMEBUFFER_PSX_HEIGHT);
    mPassthruIntShader.Uniform1i("fsFlipUV", true);
    mPassthruIntShader.UniformVec2("fsTexSize", (f32) GL_FRAMEBUFFER_PSX_WIDTH, (f32) GL_FRAMEBUFFER_PSX_HEIGHT);

    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, mPsxFramebufferSecondId));

    GL_VERIFY(glActiveTexture(GL_TEXTURE0));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mPsxFramebufferTexId));

    GL_VERIFY(glEnableVertexAttribArray(0));
    GL_VERIFY(glVertexAttribIPointer(0, 2, GL_INT, sizeof(VertexData), 0));

    GL_VERIFY(glEnableVertexAttribArray(1));
    GL_VERIFY(glVertexAttribIPointer(1, 2, GL_UNSIGNED_INT, sizeof(VertexData), (void*) offsetof(VertexData, u)));

    GL_VERIFY(glDrawElements(GL_TRIANGLES, (u32) mScreenWaveIndicies.size(), GL_UNSIGNED_INT, NULL));

    GL_VERIFY(glDeleteBuffers(1, &eboId));
    GL_VERIFY(glDeleteBuffers(1, &vboId));

    GL_VERIFY(glDisableVertexAttribArray(0));
    GL_VERIFY(glDisableVertexAttribArray(1));

    mPassthruIntShader.UnUse();
    GL_VERIFY(glBindFramebuffer(GL_FRAMEBUFFER, mPsxFramebufferId));
    GL_VERIFY(glBindTexture(GL_TEXTURE_2D, 0));
}

void OpenGLRenderer::InvalidateBatch()
{
    if (!mFrameStarted || mBatchData.size() == 0)
    {
        return;
    }

    mPsxShader.Use();

    GLuint eboId, vboId;

    // Set our new vectors
    GL_VERIFY(glGenBuffers(1, &vboId));
    GL_VERIFY(glBindBuffer(GL_ARRAY_BUFFER, vboId));
    GL_VERIFY(glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * mBatchData.size(), &mBatchData.front(), GL_STREAM_DRAW));

    GL_VERIFY(glGenBuffers(1, &eboId));
    GL_VERIFY(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId));
    GL_VERIFY(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mBatchIndicies.size(), &mBatchIndicies.front(), GL_STREAM_DRAW));

    // Set up vertex attributes
    GL_VERIFY(glEnableVertexAttribArray(0));
    GL_VERIFY(glVertexAttribIPointer(0, 2, GL_INT, sizeof(VertexData), 0));
    GL_VERIFY(glEnableVertexAttribArray(1));
    GL_VERIFY(glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, sizeof(VertexData), (void*) offsetof(VertexData, r)));
    GL_VERIFY(glEnableVertexAttribArray(2));
    GL_VERIFY(glVertexAttribIPointer(2, 4, GL_UNSIGNED_INT, sizeof(VertexData), (void*) offsetof(VertexData, u)));
    GL_VERIFY(glEnableVertexAttribArray(3));
    GL_VERIFY(glVertexAttribIPointer(3, 4, GL_UNSIGNED_INT, sizeof(VertexData), (void*) offsetof(VertexData, drawType)));
    GL_VERIFY(glEnableVertexAttribArray(4));
    GL_VERIFY(glVertexAttribIPointer(4, 2, GL_UNSIGNED_INT, sizeof(VertexData), (void*) offsetof(VertexData, paletteIndex)));

    // Inform our internal resolution
    mPsxShader.UniformVec2("vsViewportSize", GL_FRAMEBUFFER_PSX_WIDTH, GL_FRAMEBUFFER_PSX_HEIGHT);

    // Bind palette texture
    mPaletteTexture->BindTo(GL_TEXTURE0);
    mPsxShader.Uniform1i("texPalette", 0);

    // Bind gas
    if (mCurGasTextureId)
    {
        GL_VERIFY(glActiveTexture(GL_TEXTURE1));
        GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mCurGasTextureId));

        mPsxShader.Uniform1i("texGas", 1);
    }

    // Bind camera (if needed)
    if (mCurCamTextureId)
    {
        GL_VERIFY(glActiveTexture(GL_TEXTURE2));
        GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mCurCamTextureId));

        mPsxShader.Uniform1i("texCamera", 2);
    }

    // Bind FG1 layers (if needed)
    s32 numLayers = (s32) mCurFG1TextureIds.size();

    for (int i = 0; i < numLayers; i++)
    {
        GL_VERIFY(glActiveTexture(GL_TEXTURE3 + i));
        GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mCurFG1TextureIds[i]));
    }

    mPsxShader.Uniform1iv("texFG1Masks", 4, mFG1Units);

    // Bind sprite sheets
    s32 numTextures = (s32) mBatchTextureIds.size();

    for (int i = 0; i < numTextures; i++)
    {
        GL_VERIFY(glActiveTexture(GL_TEXTURE7 + i));
        GL_VERIFY(glBindTexture(GL_TEXTURE_2D, mBatchTextureIds[i]));
    }

    mPsxShader.Uniform1iv("texSpriteSheets", GL_USE_NUM_TEXTURE_UNITS, mTextureUnits);

    // Assign blend mode
    if (mBatchBlendMode <= (u32) TPageAbr::eBlend_3)
    {
        SetupBlendMode((u16) mBatchBlendMode);
    }

    // Set index data and render
    GL_VERIFY(glDrawElements(GL_TRIANGLES, (u32) mBatchIndicies.size(), GL_UNSIGNED_INT, NULL));

    // Tear down
    GL_VERIFY(glDeleteBuffers(1, &vboId));
    GL_VERIFY(glDeleteBuffers(1, &eboId));

    GL_VERIFY(glDisableVertexAttribArray(0));
    GL_VERIFY(glDisableVertexAttribArray(1));
    GL_VERIFY(glDisableVertexAttribArray(2));
    GL_VERIFY(glDisableVertexAttribArray(3));
    GL_VERIFY(glDisableVertexAttribArray(4));

    mPsxShader.UnUse();

    // Do not clear gas here - it's released later
    mCurFG1TextureIds.clear();

    mBatchBlendMode = BATCH_VALUE_UNSET;
    mBatchData.clear();
    mBatchIndicies.clear();
    mBatchTextureIds.clear();
    mStats.mInvalidationsCount++;
}

void OpenGLRenderer::PushLines(const VertexData* vertices, int count)
{
    static const f32 halfThickness = 0.5f;

    const int numLines = count - 1;

    for (int i = 0; i < numLines; i++)
    {
        VertexData vertA = vertices[i];
        VertexData vertB = vertices[i + 1];

        f32 x0 = (f32) vertA.x;
        f32 y0 = (f32) vertA.y;

        f32 x1 = (f32) vertB.x;
        f32 y1 = (f32) vertB.y;

        f32 dx = x1 - x0;
        f32 dy = y1 - y0;

        f32 normal = halfPi - std::atan(dy / dx);

        f32 dxTarget = halfThickness * std::cos(normal);
        f32 dyTarget = halfThickness * std::sin(normal);

        s16 finalX0 = (s16) std::ceil(x0 + dxTarget);
        s16 finalY0 = (s16) std::ceil(y0 - dyTarget);

        s16 finalX1 = (s16) std::ceil(x0 - dxTarget);
        s16 finalY1 = (s16) std::ceil(y0 + dyTarget);

        s16 finalX2 = (s16) std::ceil(x1 + dxTarget);
        s16 finalY2 = (s16) std::ceil(y1 - dyTarget);

        s16 finalX3 = (s16) std::ceil(x1 - dxTarget);
        s16 finalY3 = (s16) std::ceil(y1 + dyTarget);

        VertexData triangleVerts[4] = {
            {finalX0, finalY0, vertA.r, vertA.g, vertA.b, 0, 0, 0, 0, vertA.drawType, vertA.isSemiTrans, vertA.isShaded, vertA.blendMode, 0, 0},
            {finalX1, finalY1, vertA.r, vertA.g, vertA.b, 0, 0, 0, 0, vertA.drawType, vertA.isSemiTrans, vertA.isShaded, vertA.blendMode, 0, 0},
            {finalX2, finalY2, vertB.r, vertB.g, vertB.b, 0, 0, 0, 0, vertB.drawType, vertB.isSemiTrans, vertB.isShaded, vertB.blendMode, 0, 0},
            {finalX3, finalY3, vertB.r, vertB.g, vertB.b, 0, 0, 0, 0, vertB.drawType, vertB.isSemiTrans, vertB.isShaded, vertB.blendMode, 0, 0}};

        PushVertexData(triangleVerts, 4);
    }
}

void OpenGLRenderer::PushScreenWaveData(const VertexData *vertices)
{
    if (!mFrameStarted)
    {
        return;
    }

    u32 nextIndex = (u32) mScreenWaveData.size();

    mScreenWaveIndicies.push_back(nextIndex + 1);
    mScreenWaveIndicies.push_back(nextIndex);
    mScreenWaveIndicies.push_back(nextIndex + 3);

    mScreenWaveIndicies.push_back(nextIndex + 3);
    mScreenWaveIndicies.push_back(nextIndex);
    mScreenWaveIndicies.push_back(nextIndex + 2);

    for (int i = 0; i < 4; i++)
    {
        mScreenWaveData.push_back(vertices[i]);
    }
}

void OpenGLRenderer::PushVertexData(VertexData* pVertData, int count, GLuint textureId)
{
    if (!mFrameStarted)
    {
        return;
    }

    u32 blendMode = pVertData[0].blendMode;
    u32 drawType = pVertData[0].drawType;

    // Check if we need to invalidate the existing batched data
    //
    // The only reason we need to invalidate here is if the blend mode switches
    // to/from subtractive blending
    if (
        mBatchBlendMode != blendMode &&
        mBatchBlendMode != BATCH_VALUE_UNSET &&
        (mBatchBlendMode == 2 || blendMode == 2))
    {
        InvalidateBatch();
    }

    // Set up texture ... if it's a textured poly then we need to make sure we
    // have texture units leftover if it's not already assigned
    u32 targetTexUnit = 0;

    switch (drawType)
    {
        case GL_PSX_DRAW_MODE_DEFAULT_FT4:
        {
            auto iter = std::find(mBatchTextureIds.begin(), mBatchTextureIds.end(), textureId);

            if (iter == mBatchTextureIds.end())
            {
                if (mBatchTextureIds.size() == GL_USE_NUM_TEXTURE_UNITS)
                {
                    InvalidateBatch();
                }

                targetTexUnit = (u32) mBatchTextureIds.size();
                mBatchTextureIds.push_back(textureId);
            }
            else
            {
                targetTexUnit = (u32) std::distance(mBatchTextureIds.begin(), iter);
            }

            break;
        }

        case GL_PSX_DRAW_MODE_CAM:
        {
            mCurCamTextureId = textureId;
            break;
        }

        case GL_PSX_DRAW_MODE_FG1:
        {
            targetTexUnit = static_cast<u32>(mCurFG1TextureIds.size());

            if (targetTexUnit == 4)
            {
                ALIVE_FATAL("Out of texture units for FG1 layers.");
            }

            mCurFG1TextureIds.push_back(textureId);

            break;
        }

        case GL_PSX_DRAW_MODE_GAS:
        {
            mCurGasTextureId = textureId;
            break;
        }
    }

    mBatchBlendMode = blendMode;

    // Push indicies for this data
    u32 nextIndex = (u32) mBatchData.size();
    s32 numTriangles = count - 2;

    if (numTriangles == 1)
    {
        mBatchIndicies.push_back(nextIndex);
        mBatchIndicies.push_back(nextIndex + 1);
        mBatchIndicies.push_back(nextIndex + 2);
    }
    else if (numTriangles == 2)
    {
        mBatchIndicies.push_back(nextIndex + 1);
        mBatchIndicies.push_back(nextIndex);
        mBatchIndicies.push_back(nextIndex + 3);

        mBatchIndicies.push_back(nextIndex + 3);
        mBatchIndicies.push_back(nextIndex);
        mBatchIndicies.push_back(nextIndex + 2);
    }

    // Push vertex data
    for (int i = 0; i < count; i++)
    {
        pVertData[i].textureUnitIndex = targetTexUnit;
        mBatchData.push_back(pVertData[i]);
    }

    // DEBUGGING: If batching is disabled we invalidate immediately
    if (!gRenderEnable_Batching)
    {
        InvalidateBatch();
    }
}

void OpenGLRenderer::SetupBlendMode(u16 blendMode)
{
    if ((TPageAbr)blendMode == TPageAbr::eBlend_2)
    {
        GL_VERIFY(glBlendFunc(GL_SRC_ALPHA, GL_ONE));
        GL_VERIFY(glBlendEquation(GL_FUNC_REVERSE_SUBTRACT));
    }
    else
    {
        GL_VERIFY(glBlendFunc(GL_ONE, GL_SRC_ALPHA));
        GL_VERIFY(glBlendEquation(GL_FUNC_ADD));
    }
}

// END ROZZA FRAMEBUFFER STUFF


void OpenGLRenderer::DebugWindow()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Developer"))
        {
            if (ImGui::BeginMenu("Renderer Debug"))
            {
                ImGui::MenuItem("Batching Enabled", nullptr, &gRenderEnable_Batching);

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Render Elements"))
            {
                ImGui::MenuItem("SPRT", nullptr, &gRenderEnable_SPRT);
                ImGui::MenuItem("TILE", nullptr, &gRenderEnable_TILE);
                ImGui::MenuItem("GAS", nullptr, &gRenderEnable_GAS);
                ImGui::MenuItem("FT4", nullptr, &gRenderEnable_FT4);
                ImGui::MenuItem("G4", nullptr, &gRenderEnable_G4);
                ImGui::MenuItem("G3", nullptr, &gRenderEnable_G3);
                ImGui::MenuItem("G2", nullptr, &gRenderEnable_G2);
                ImGui::MenuItem("F4", nullptr, &gRenderEnable_F4);
                ImGui::MenuItem("F3", nullptr, &gRenderEnable_F3);
                ImGui::MenuItem("F2", nullptr, &gRenderEnable_F2);

                #if GL_DEBUG > 0
                ImGui::MenuItem("gl_debug", nullptr, &gGlDebug);
                #endif

                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (ImGui::Begin("Render stats"))
    {
        ImGui::Text("Cams %d", mStats.mCamUploadCount);
        ImGui::Text("Fg1s %d", mStats.mFg1UploadCount);
        ImGui::Text("Anims %d", mStats.mAnimUploadCount);
        ImGui::Text("Pals %d", mStats.mPalUploadCount);
        ImGui::Text("Fonts %d", mStats.mFontUploadCount);
        ImGui::Text("Invalidations %d", mStats.mInvalidationsCount);
    }
    ImGui::End();
}