#include "render.h"

#include "mymath.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

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

#include <stdio.h>

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

static int X0 = 70;
static int Y0 = 10;
static int X1 = 50;
static int Y1 = 50;

static int DX0 = 1;
static int DX1 = 1;
static int DY0 = 1;
static int DY1 = -1;

void render(Render_Buffer *buff, Game_State *game) {

    // Clear the screen
    memset(buff->pixels, 0x22, buff->width * buff->height * sizeof(int));

    int origin_x = buff->width / 2;
    int origin_y = buff->width / 2;

    // Draw the stars
    for(int i = 0; i < STAR_LEN; i++) {

        // Transform to Clipspace
        float z = -1.0f / game->stars_z[i];

        float x = game->stars_x[i] * z;
        float y = game->stars_y[i] * z;

        // Transform to Screenspace
        int screen_x = x * buff->width + origin_x;
        int screen_y = y * buff->width + origin_y;

        // Clip and draw
        fill_pixel(buff, screen_x, screen_y, game->stars_col[i]);
    }

    draw_line(buff, X0, Y0, X1, Y1);

    X0 += DX0;
    X1 += DX1;
    Y0 += DY0;
    Y1 += DY1;
    
    if(X0 < 0 || X0 > buff->width)
        DX0 = -DX0;

    if(Y0 < 0 || Y0 > buff->height)
        DY0 = -DY0;

    if(X1 < 0 || X1 > buff->width)
        DX1 = -DX1;

    if(Y1 < 0 || Y1 > buff->height)
        DY1 = -DY1;
}

