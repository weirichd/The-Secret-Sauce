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

static inline int rgb(float r, float g, float b) {
    clampf(&r, 0.0f, 1.0f);
    clampf(&g, 0.0f, 1.0f);
    clampf(&b, 0.0f, 1.0f);

    unsigned int R = (unsigned int)(r * 0xFF);
    unsigned int G = (unsigned int)(g * 0xFF);
    unsigned int B = (unsigned int)(b * 0xFF);

    return 0xFF000000 + (R << 16) + (G << 8) + B;
}

static inline void fill_pixel(Render_Buffer *buff, int x, int y, int color) {
    if(0 <= x && buff->width >= x && 0 <= y && buff->height >= y) {
        buff->pixels[x + y * buff->width] = color;
    }
}

static inline void draw_line(Render_Buffer *buff, int x0, int y0, int x1, int y1, float r0, float g0, float b0, float r1, float g1, float b1) {
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
        float t = (float) i / (float) dx;
        float r  = r1 * t + (1 - t) * r0;
        float g  = g1 * t + (1 - t) * g0;
        float b  = b1 * t + (1 - t) * b0;

        fill_pixel(buff, x, y, rgb(r, g, b));
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
    float z0 = -1.0f / game->z[0];
    float x0 = game->x[0] * z0;
    float y0 = game->y[0] * z0;
    float z1 = -1.0f / game->z[1];
    float x1 = game->x[1] * z1;
    float y1 = game->y[1] * z1;
    float z2 = -1.0f / game->z[2];
    float x2 = game->x[2] * z2;
    float y2 = game->y[2] * z2;

    // Transform to Screenspace
    int screen_x0 = x0 * buff->width + origin_x;
    int screen_y0 = y0 * buff->width + origin_y;
    int screen_x1 = x1 * buff->width + origin_x;
    int screen_y1 = y1 * buff->width + origin_y;
    int screen_x2 = x2 * buff->width + origin_x;
    int screen_y2 = y2 * buff->width + origin_y;

    draw_line(buff, screen_x0, screen_y0, screen_x1, screen_y1, game->r[0], game->g[0], game->b[0], game->r[1], game->g[1], game->b[1]);
    draw_line(buff, screen_x1, screen_y1, screen_x2, screen_y2, game->r[1], game->g[1], game->b[1], game->r[2], game->g[2], game->b[2]);
    draw_line(buff, screen_x2, screen_y2, screen_x0, screen_y0, game->r[2], game->g[2], game->b[2], game->r[0], game->g[0], game->b[0]);
}

