#include <iostream>
#include "SDL3/SDL.h"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <imgui.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

static void mainLoop(void)
{
    SDL_PollEvent(&event);
    ImGui_ImplSDL3_ProcessEvent(&event);
    if (event.type == SDL_EVENT_QUIT)
    {
        SDL_Quit();
    }

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // demo window
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(
        ImGui::GetDrawData(), renderer);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplSDL3_InitForSDLRenderer(
        window,
        renderer);
    ImGui_ImplSDLRenderer3_Init(
        renderer);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    while (1)
    {
        mainLoop();
    }
#endif

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}