// Example program:
// Using SDL2 to create an application window

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int width = 640;
    int height = 480;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;
    window = SDL_CreateWindow("The Secret Sauce", 
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    int a = 0xFFFFFFFF;

    memcpy(surface->pixels + 8000, &a, sizeof(int));

    int quit = 0;

    SDL_Event event;

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
        }

        SDL_BlitSurface(surface, NULL, window_surface, NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
