#include <string.h>
#include "render.h"

unsigned char i = 0;

static inline void draw_pixel(int *pixels, int width, int x, int y, int color) {
    pixels[x + y * width] = color;
}

static inline void draw_line(int *pixels, int width, int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int x = x0;
    int y = y0;

    int p = 2 * dy - dx;

    while(x < x1) {
        draw_pixel(pixels, width, x, y, 0xFFFFFFFF);
        p += 2 * dy;

        if(p >= 0) {
            y++;
            p -= 2 * dx;
        }

        x++;
    }
}

void render(int *pixels, Game_State *game, int width, int height) {

    // Clear the screen
    memset(pixels, 0, width * height * sizeof(int));

    int origin_x = width / 2;
    int origin_y = width / 2;

    // Draw the stars
    for(int i = 0; i < STAR_LEN; i++) {

        // Transform to Clipspace
        float z = -1.0f / game->stars_z[i];

        float x = game->stars_x[i] * z;
        float y = game->stars_y[i] * z;

        // Transform to Screenspace
        int screen_x = x * width + origin_x;
        int screen_y = y * width + origin_y;

        // Clip and draw
        if(0 <= screen_x && width >= screen_x && 0 <= screen_y && height >= screen_y) {
            draw_pixel(pixels, width, screen_x, screen_y, game->stars_col[i]);
        }
    }

    // Line stuff
    int x0 = 30;
    int y0 = 40;

    int x1 = 90;
    int y1 = 66;

    draw_line(pixels, width, x0, y0, x1, y1);
}

