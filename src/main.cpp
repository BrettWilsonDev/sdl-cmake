// #include <SDL3/SDL.h>
// #include <glad/glad.h> 


// int main(int argc, char *argv[])
// {
//     SDL_Window *window;
//     SDL_Renderer *renderer;
//     SDL_Event event;

//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
//         return 3;
//     }

//     if (SDL_CreateWindowAndRenderer("Hello SDL", 320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
//         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
//         return 3;
//     }

//     while (1) {
//         SDL_PollEvent(&event);
//         if (event.type == SDL_EVENT_QUIT) {
//             break;
//         }
//         SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
//         SDL_RenderClear(renderer);
//         SDL_RenderPresent(renderer);
//     }

//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);

//     SDL_Quit();

//     return 0;
// }

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_GLContext gl_context;
    SDL_Event event;
    int running = 1;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create an SDL window with OpenGL context
    window = SDL_CreateWindow("Hello SDL OpenGL", 320, 240, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }

    // Create an OpenGL context associated with the window
    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        SDL_GL_DestroyContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
                break;
            }
        }

        // Set the clear color and clear the screen
        glClearColor(0.0f, 0.5f, 1.0f, 1.0f); // Clear to a blue color
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the window buffers
        SDL_GL_SwapWindow(window);
    }

    // Clean up
    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
