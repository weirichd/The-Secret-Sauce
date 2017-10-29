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
    float z0 = -1.0f / game->v[0].z;
    float x0 = game->v[0].x * z0;
    float y0 = game->v[0].y * z0;

    float z1 = -1.0f / game->v[1].z;
    float x1 = game->v[1].x * z1;
    float y1 = game->v[1].y * z1;

    float z2 = -1.0f / game->v[2].z;
    float x2 = game->v[2].x * z2;
    float y2 = game->v[2].y * z2;

    float z3 = -1.0f / game->v[3].z;
    float x3 = game->v[3].x * z2;
    float y3 = game->v[3].y * z2;

    // Transform to Screenspace
    int screen_x0 = x0 * buff->width + origin_x;
    int screen_y0 = y0 * buff->width + origin_y;
    int screen_x1 = x1 * buff->width + origin_x;
    int screen_y1 = y1 * buff->width + origin_y;
    int screen_x2 = x2 * buff->width + origin_x;
    int screen_y2 = y2 * buff->width + origin_y;
    int screen_x3 = x3 * buff->width + origin_x;
    int screen_y3 = y3 * buff->width + origin_y;

    draw_line(buff, screen_x0, screen_y0, screen_x1, screen_y1, game->v[0].r, game->v[0].g, game->v[0].b, game->v[1].r, game->v[1].g, game->v[1].b);
    draw_line(buff, screen_x1, screen_y1, screen_x2, screen_y2, game->v[1].r, game->v[1].g, game->v[1].b, game->v[2].r, game->v[2].g, game->v[2].b);
    draw_line(buff, screen_x2, screen_y2, screen_x0, screen_y0, game->v[2].r, game->v[2].g, game->v[2].b, game->v[0].r, game->v[0].g, game->v[0].b);
    draw_line(buff, screen_x2, screen_y2, screen_x3, screen_y3, game->v[2].r, game->v[2].g, game->v[2].b, game->v[3].r, game->v[3].g, game->v[3].b);
}

