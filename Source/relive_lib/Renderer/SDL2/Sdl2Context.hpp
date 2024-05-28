#pragma once

#include <SDL.h>

class Sdl2Context final
{
public:
    Sdl2Context(SDL_Window* window);
    ~Sdl2Context();

    SDL_Renderer* GetRenderer();
    bool IsRenderTargetSupported();
    void Present();
    void RestoreFramebuffer();
    void SaveFramebuffer();
    void UseScreenFramebuffer();
    void UseTextureFramebuffer(SDL_Texture* texture);

private:
    SDL_Renderer* mRenderer;
    SDL_Texture* mLastFramebuffer;
    SDL_Window* mWindow;
};