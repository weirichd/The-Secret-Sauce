#include <string.h>
#include "render.h"

unsigned char i = 0;

static inline void draw_pixel(int *pixels, int width, int height, int x, int y, int color) {
    if(0 <= x && width >= x && 0 <= y && height >= y) {
        pixels[x + y * width] = color;
    }
}

static inline void draw_line(int *pixels, int width, int height, int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int x = x0;
    int y = y0;

    int p = 2 * dy - dx;

    while(x < x1) {
        draw_pixel(pixels, width, height, x, y, 0xFFFFFFFF);
        p += 2 * dy;

        if(p >= 0) {
            y++;
            p -= 2 * dx;
        }

        x++;
    }
}

void render(Render_Buffer *rbuffer, Game_State *game) {

    // Clear the screen
    memset(rbuffer->pixels, 0, rbuffer->width * rbuffer->height * sizeof(int));

    int origin_x = rbuffer->width / 2;
    int origin_y = rbuffer->width / 2;

    // Draw the stars
    for(int i = 0; i < STAR_LEN; i++) {

        // Transform to Clipspace
        float z = -1.0f / game->stars_z[i];

        float x = game->stars_x[i] * z;
        float y = game->stars_y[i] * z;

        // Transform to Screenspace
        int screen_x = x * rbuffer->width + origin_x;
        int screen_y = y * rbuffer->width + origin_y;

        // Clip and draw
        draw_pixel(rbuffer->pixels, rbuffer->width, rbuffer->height, screen_x, screen_y, game->stars_col[i]);
    }

    // Line stuff
    int x0 = 30;
    int y0 = 40;

    int x1 = 90;
    int y1 = 66;

    draw_line(rbuffer->pixels, rbuffer->width, rbuffer->height, x0, y0, x1, y1);
}

