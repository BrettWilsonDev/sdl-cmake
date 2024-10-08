#include <iostream>
#include "SDL3/SDL.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

static void mainLoop(void)
{
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT)
    {
        SDL_Quit();
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (!SDL_CreateWindowAndRenderer("Hello SDL", 320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    const int linked = SDL_GetVersion();
    std::cout << "SDL version: " << SDL_VERSIONNUM_MAJOR(linked) << "." << SDL_VERSIONNUM_MINOR(linked) << "." << SDL_VERSIONNUM_MICRO(linked) << std::endl;


#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    while (1)
    {
        mainLoop();
    }
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}