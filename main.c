#include <SDL2/SDL.h>
#include <stdio.h>
#include <x86intrin.h>
#include <stdlib.h>

#include "render.h"
#include "game.h"

#include "upscale.h"

#pragma intrinsic(__rdtsc)

int main(int argc, char* argv[]) {
    int width = 200;
    int height = 200;

    int upscale_factor = 4;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window;
    window = SDL_CreateWindow("The Secret Sauce",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width * upscale_factor, height * upscale_factor,
            SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    Game_State *game = malloc(sizeof(Game_State));

   int *color_buffer = malloc(sizeof(int) * width * height); 

    initialize_game(game);

    int quit = 0;

    SDL_Event event;
    unsigned long long last_cycle = __rdtsc();

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
        }

        update(game);
        render(color_buffer, game, width, height);

        upscale(color_buffer, window_surface->pixels, width, height, width * upscale_factor, height * upscale_factor);

        SDL_UpdateWindowSurface(window);

        unsigned long long this_cycle = __rdtsc();
        unsigned int delta_cycles = this_cycle - last_cycle;
        printf("%u\n", delta_cycles);
        last_cycle = this_cycle;
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    free(game);

    free(color_buffer);

    return 0;
}
