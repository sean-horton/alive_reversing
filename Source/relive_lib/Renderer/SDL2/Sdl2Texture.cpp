#include "Sdl2Texture.hpp"
#include "FatalError.hpp"
#include "Renderer/PaletteCache.hpp"
#include "data_conversion/AnimationConverter.hpp"

Sdl2Texture::Sdl2Texture(Sdl2Context& context, u32 width, u32 height, SDL_PixelFormatEnum format, SDL_TextureAccess access)
    : mContext(context), mFormat(format), mHeight(height), mWidth(width)
{
    // SDL2 does not support palette textures, if we want to store indexed
    // colour we have to handle that internally (using mIndexedPixels)
    if (mFormat == SDL_PIXELFORMAT_INDEX8)
    {
        mIndexedPixels = (u8*) malloc(mWidth * mHeight);
    }
    else
    {
        mTexture = SDL_CreateTexture(mContext.GetRenderer(), mFormat, access, mWidth, mHeight);

        if (!mTexture)
        {
            ALIVE_FATAL("%s", SDL_GetError());
        }
    }
}

Sdl2Texture::~Sdl2Texture()
{
    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);
    }
}

std::shared_ptr<Sdl2Texture> Sdl2Texture::FromMask(Sdl2Context& context, std::shared_ptr<Sdl2Texture> srcTex, const u8* maskPixels)
{
    auto resultTex = std::make_shared<Sdl2Texture>(context, srcTex->mWidth, srcTex->mHeight, srcTex->mFormat, SDL_TEXTUREACCESS_TARGET);

    // Create mask texture
    u8* texPixels;
    s32 pitch;
    SDL_Texture* maskTex = SDL_CreateTexture(context.GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, srcTex->mWidth, srcTex->mHeight);

    SDL_LockTexture(maskTex, NULL, (void**) &texPixels, &pitch);

    for (s32 i = 0; i < pitch * static_cast<s32>(srcTex->mHeight); i += 4)
    {
        s32 r = i;
        s32 g = i + 1;
        s32 b = i + 2;
        s32 a = i + 3;

        // Mask out black pixels
        if (maskPixels[r] == 0 && maskPixels[g] == 0 && maskPixels[b] == 0)
        {
            texPixels[a] = 0;
        }
        else
        {
            texPixels[a] = 255;
        }
    }

    SDL_UnlockTexture(maskTex);

    // Paint result texture
    SDL_BlendMode blendMode =
        SDL_ComposeCustomBlendMode(
            SDL_BLENDFACTOR_ZERO,
            SDL_BLENDFACTOR_ONE,
            SDL_BLENDOPERATION_ADD,
            SDL_BLENDFACTOR_SRC_ALPHA,
            SDL_BLENDFACTOR_ZERO,
            SDL_BLENDOPERATION_ADD
        );

    context.SaveFramebuffer();
    context.UseTextureFramebuffer(resultTex->GetTexture());

    SDL_RenderCopy(context.GetRenderer(), srcTex->GetTexture(), NULL, NULL);

    SDL_SetTextureBlendMode(maskTex, blendMode);
    SDL_RenderCopy(context.GetRenderer(), maskTex, NULL, NULL);

    SDL_SetTextureBlendMode(resultTex->GetTexture(), SDL_BLENDMODE_BLEND);

    // Cleanup
    context.RestoreFramebuffer();
    SDL_DestroyTexture(maskTex);

    return resultTex;
}

SDL_Texture* Sdl2Texture::GetTexture()
{
    if (mFormat == SDL_PIXELFORMAT_INDEX8)
    {
        ALIVE_FATAL("%s", "SDL2 use GetTextureUsePalette with INDEX8 tex");
    }

    return mTexture;
}

SDL_Texture* Sdl2Texture::GetTextureUsePalette(const std::shared_ptr<AnimationPal>& palette, const RGBA32& shading, bool isSemiTrans, relive::TBlendModes blendMode)
{
    if (mFormat != SDL_PIXELFORMAT_INDEX8)
    {
        ALIVE_FATAL("%s", "SDL2 attempt to use palette on non-indexed tex");
    }

    // (Re)create texture if necessary (palette/shading/blend changes)
    if (mTexture)
    {
        if (
            PaletteCache::HashPalette(palette.get()) == mLastPaletteHash &&
            mLastBlendMode == blendMode &&
            mLastSemiTransparent == isSemiTrans &&
            mLastShadeColor.ToU32() == shading.ToU32()
        )
        {
            LOG("%s", "SDL2 palette tex cache hit");
            return mTexture;
        }

        SDL_DestroyTexture(mTexture);
    }

    LOG("%s", "SDL2 palette tex cache miss");
    mTexture = SDL_CreateTexture(mContext.GetRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);

    // Lock target texture, all the per-pixel ops are handled here - sampling
    // from palette + shading/blending
    u8* pixelsTarget = NULL;
    s32 pitchTarget = 0;

    SDL_LockTexture(mTexture, NULL, (void**) &pixelsTarget, &pitchTarget);

    for (s32 i = 0; i < static_cast<s32>(mWidth * mHeight); i++)
    {
        s32 r = (i * 4);
        s32 g = (i * 4) + 1;
        s32 b = (i * 4) + 2;
        s32 a = (i * 4) + 3;

        RGBA32 colour = palette->mPal[mIndexedPixels[i]];

        // This logic is basically a mirror of the GLSL shader, but in
        // software - see ShaderPsx.cpp, and the blend mode stuff in
        // OpenGLRenderer.cpp::DrawBatches

        if (colour.ToU32() == 0)
        {
            pixelsTarget[r] = 0;
            pixelsTarget[g] = 0;
            pixelsTarget[b] = 0;
            pixelsTarget[a] = 255;

            continue;
        }

        if (shading.a == 255) // Shading required
        {
            colour.r = HandleShading(colour.r, shading.r);
            colour.g = HandleShading(colour.g, shading.g);
            colour.b = HandleShading(colour.b, shading.b);
        }

        if (isSemiTrans && colour.a == 255)
        {
            switch (blendMode)
            {
                case relive::TBlendModes::eBlend_0: // HALF_DST_ADD_HALF_SRC
                    pixelsTarget[r] = colour.r / 2;
                    pixelsTarget[g] = colour.g / 2;
                    pixelsTarget[b] = colour.b / 2;
                    pixelsTarget[a] = 128;
                    break;

                case relive::TBlendModes::eBlend_1: // ONE_DST_ADD_ONE_SRC
                case relive::TBlendModes::eBlend_2: // ONE_DST_SUB_ONE_SRC
                    pixelsTarget[r] = colour.r;
                    pixelsTarget[g] = colour.g;
                    pixelsTarget[b] = colour.b;
                    pixelsTarget[a] = 255;
                    break;

                case relive::TBlendModes::eBlend_3: // ONE_DST_ADD_QRT_SRC
                    pixelsTarget[r] = colour.r / 4;
                    pixelsTarget[g] = colour.g / 4;
                    pixelsTarget[b] = colour.b / 4;
                    pixelsTarget[a] = 255;
                    break;

                default:
                    ALIVE_FATAL("SDL2 Invalid blend mode %u", blendMode);
                    break;
            }
        }
        else
        {
            pixelsTarget[r] = colour.r / 2;
            pixelsTarget[g] = colour.g / 2;
            pixelsTarget[b] = colour.b / 2;
            pixelsTarget[a] = 0;
        }
    }

    SDL_UnlockTexture(mTexture);

    // Set up texture blend mode usage
    SDL_BlendMode texBlendMode;

    if (blendMode == relive::TBlendModes::eBlend_2)
    {
        texBlendMode =
            SDL_ComposeCustomBlendMode(
                SDL_BLENDFACTOR_SRC_ALPHA,
                SDL_BLENDFACTOR_ONE,
                SDL_BLENDOPERATION_REV_SUBTRACT,
                SDL_BLENDFACTOR_SRC_ALPHA,
                SDL_BLENDFACTOR_ONE,
                SDL_BLENDOPERATION_REV_SUBTRACT
            );
    }
    else
    {
        texBlendMode =
            SDL_ComposeCustomBlendMode(
                SDL_BLENDFACTOR_ONE,
                SDL_BLENDFACTOR_SRC_ALPHA,
                SDL_BLENDOPERATION_ADD,
                SDL_BLENDFACTOR_ONE,
                SDL_BLENDFACTOR_SRC_ALPHA,
                SDL_BLENDOPERATION_ADD
            );
    }

    SDL_SetTextureBlendMode(mTexture, texBlendMode);

    // Update cache state
    mLastBlendMode = blendMode;
    mLastPaletteHash = PaletteCache::HashPalette(palette.get());
    mLastSemiTransparent = isSemiTrans;
    mLastShadeColor = shading;

    return mTexture;
}

void Sdl2Texture::Update(const SDL_Rect* rect, const void* pixels)
{
    if (mFormat == SDL_PIXELFORMAT_INDEX8)
    {
        memcpy(mIndexedPixels, pixels, mWidth * mHeight);
    }
    else
    {
        u32 pitch = 0;

        switch (mFormat)
        {
            case SDL_PIXELFORMAT_RGBA32:
                pitch = mWidth * 4;
                break;

            default:
                ALIVE_FATAL("SDL2 - Unsupported texture format %d", mFormat);
                break;
        }

        SDL_UpdateTexture(mTexture, rect, pixels, pitch);
    }
}

u8 Sdl2Texture::HandleShading(const u8 src, const u8 shade)
{
    f32 result = (src * (shade / 255.0f)) / 0.5f;

    if (result > 255.0f)
    {
        return 255;
    }

    return static_cast<u8>(result);
}