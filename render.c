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

static inline void draw_line(Render_Buffer *buff, Vertex *v0, Vertex *v1) {
    int dx = int_abs(v1->x - v0->x);
    int dy = int_abs(v1->y - v0->y);
    int signx = int_signum(v1->x - v0->x);
    int signy = int_signum(v1->y - v0->y);

    int x = v0->x;
    int y = v0->y;

    int swapped = 0;

    if(dy > dx) {
        swap_int(&dx, &dy);
        swapped = 1;
    }

    int e = 2 * dy - dx;

    for(int i = 0; i < dx; i++) {
        float t = (float) i / (float) dx;
        float r  = v1->r * t + (1 - t) * v0->r;
        float g  = v1->g * t + (1 - t) * v0->g;
        float b  = v1->b * t + (1 - t) * v0->b;

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

    fill_pixel(buff, v1->x, v1->y, rgb(v1->r, v1->g, v1->b));
}

static void transform_vertex(Vertex *dest, Vertex *src, int origin_x, int origin_y) {
   dest->z = -1.0 / src->z; 
   dest->x = src->x * dest->z * 2 * origin_x + origin_x;
   dest->y = src->y * dest->z * 2 * origin_y + origin_y;

   dest->r = src->r;
   dest->g = src->g;
   dest->b = src->b;
}

void render(Render_Buffer *buff, Game_State *game) {

    // Clear the screen
    memset(buff->pixels, 0x22, buff->width * buff->height * sizeof(int));

    Vertex temp_v[3];

    int origin_x = buff->width / 2;
    int origin_y = buff->height / 2;

    for(int i = 0; i < 3; i++) {
        transform_vertex(temp_v + i, &game->v[i], origin_x, origin_y);
    }

    draw_line(buff, temp_v + 0, temp_v + 1);
    draw_line(buff, temp_v + 1, temp_v + 2);
    draw_line(buff, temp_v + 2, temp_v + 0);
}

