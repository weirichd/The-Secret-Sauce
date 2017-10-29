#include "render.h"

#include "mymath.h"

#include <stdlib.h>
#include <string.h>

Render_Buffer *create_render_buffer(int width, int height) {
    Render_Buffer *buff = malloc(sizeof(Render_Buffer));
    buff->width = width;
    buff->height = height;
    buff->pixels = malloc(sizeof(int) * width * height);

    return buff;
}

void free_render_buffer(Render_Buffer *buff) {
    free(buff->pixels);
    free(buff);
}

static inline void fill_pixel(Render_Buffer *buff, int x, int y, int color) {
    if(0 <= x && buff->width >= x && 0 <= y && buff->height >= y) {
        buff->pixels[x + y * buff->width] = color;
    }
}

static inline void draw_line(Render_Buffer *buff, int x0, int y0, int x1, int y1) {
    int dx = int_abs(x1 - x0);
    int dy = int_abs(y1 - y0);
    int signx = int_signum(x1 - x0);
    int signy = int_signum(y1 - y0);

    int x = x0;
    int y = y0;

    int swapped = 0;

    if(dy > dx) {
        swap_int(&dx, &dy);
        swapped = 1;
    }

    int e = 2 * dy - dx;

    for(int i = 0; i < dx; i++) {
        fill_pixel(buff, x, y, 0xFFFFFFFF);
        while(e >= 0) {
            if(swapped)
                x += signx;
            else
                y += signy;
            e -= 2 * dx;
        }
        if(swapped)
            y += signy;
        else
            x += signx;
        e += 2 * dy;
    }
}

void render(Render_Buffer *buff, Game_State *game) {

    // Clear the screen
    memset(buff->pixels, 0x22, buff->width * buff->height * sizeof(int));

    int origin_x = buff->width / 2;
    int origin_y = buff->width / 2;

    // Transform to Clipspace
    float z0 = -1.0f / game->stars_z[0];
    float x0 = game->stars_x[0] * z0;
    float y0 = game->stars_y[0] * z0;
    float z1 = -1.0f / game->stars_z[1];
    float x1 = game->stars_x[1] * z1;
    float y1 = game->stars_y[1] * z1;
    float z2 = -1.0f / game->stars_z[2];
    float x2 = game->stars_x[2] * z2;
    float y2 = game->stars_y[2] * z2;

    // Transform to Screenspace
    int screen_x0 = x0 * buff->width + origin_x;
    int screen_y0 = y0 * buff->width + origin_y;
    int screen_x1 = x1 * buff->width + origin_x;
    int screen_y1 = y1 * buff->width + origin_y;
    int screen_x2 = x2 * buff->width + origin_x;
    int screen_y2 = y2 * buff->width + origin_y;

    // Clip and draw

    draw_line(buff, screen_x0, screen_y0, screen_x1, screen_y1);
    draw_line(buff, screen_x1, screen_y1, screen_x2, screen_y2);
    draw_line(buff, screen_x2, screen_y2, screen_x0, screen_y0);

    fill_pixel(buff, screen_x0, screen_y0, 0xFF0000FF);
    fill_pixel(buff, screen_x1, screen_y1, 0xFFFF0000);
    fill_pixel(buff, screen_x2, screen_y2, 0xFF00FF00);
}

