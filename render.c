#include <string.h>
#include "render.h"

unsigned char i = 0;

void render(int *pixels, Game_State *game, int width, int height) {

    // Clear the screen
    memset(pixels, 0, width * height * sizeof(int));

    int origin_x = width / 2;
    int origin_y = width / 2;

    // Draw the stars
    for(i = 0; i < STAR_LEN; i++) {

        // Transform to Clipspace
        float z = -1.0f / game->stars_z[i];

        float x = game->stars_x[i] * z;
        float y = game->stars_y[i] * z;

        // Transform to Screenspace
        int screen_x = x * width + origin_x;
        int screen_y = y * width + origin_y;

        // Clip and draw
        if(0 <= screen_x && width >= screen_x && 0 <= screen_y && height >= screen_y) {
            pixels[width * screen_y + screen_x] = 0xFFFFFFFF;
        }
    }
}

