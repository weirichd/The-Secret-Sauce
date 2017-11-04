#include "render.h"

#include "font.h"
#include "mymath.h"
#include "numbers.h"

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


static void triangle(Render_Buffer *buff, const Vertex2Di v[3])
{
    int top = 0;
    int middle = 1;
    int bottom = 2;

    // Janky as hell conditional sort
    if(v[0].y >= v[1].y && v[1].y >= v[2].y)  { top = 2; middle = 1; bottom = 0; }
    if(v[0].y >= v[2].y && v[2].y >= v[1].y)  { top = 1; middle = 2; bottom = 0; }
    if(v[1].y >= v[0].y && v[0].y >= v[2].y)  { top = 2; middle = 0; bottom = 1; }
    if(v[1].y >= v[2].y && v[2].y >= v[0].y)  { top = 0; middle = 2; bottom = 1; }
    if(v[2].y >= v[0].y && v[0].y >= v[1].y)  { top = 1; middle = 0; bottom = 2; }

    // Swap the bottom two if necessary
    if(v[middle].x >= v[bottom].x) {
        swap_int(&middle, &bottom);
    }

    int x1 = v[top].x;
    int x2 = v[middle].x;
    int x3 = v[bottom].x;

    int y1 = v[top].y;
    int y2 = v[middle].y;
    int y3 = v[bottom].y;

    // Bounding rectangle
    int minx = int_min3(x1, x2, x3);
    int maxx = int_max3(x1, x2, x3);
    int miny = int_min3(y1, y2, y3);
    int maxy = int_max3(y1, y2, y3);

    // Scan through bounding rectangle
    for(int y = miny; y < maxy; y++)
    {
        for(int x = minx; x < maxx; x++)
        {
            // When all half-space functions positive, pixel is in triangle
            if((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 &&
               (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
               (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0)
            {
                fill_pixel(buff, x, y, 0x99999999);
            }
        }
    }

    fill_pixel(buff, x1, y1, 0xFFFF0000);
    fill_pixel(buff, x2, y2, 0xFF00FF00);
    fill_pixel(buff, x3, y3, 0xFF0000FF);
}

static inline void draw_line(Render_Buffer *buff, Vertex2Di *v0, Vertex2Di *v1) {
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
}


static void transform_vertex(Vertex *dest, Vertex *src, int origin_x, int origin_y) {
   dest->z = -1.0 / src->z;
   dest->x = src->x * dest->z * 2 * origin_x + origin_x;
   dest->y = src->y * dest->z * 2 * origin_y + origin_y;

   dest->r = src->r;
   dest->g = src->g;
   dest->b = src->b;
}


static void clip_space_to_screen(Vertex *clip_verts, Vertex2Di *screen_verts, size_t count, int origin_x, int origin_y) {
    for(int i = 0; i < count; i++) {
        // TODO: Perspective divide in another step
        float z = -1.0 / clip_verts[i].z;
        screen_verts[i].x = (int)(clip_verts[i].x * z * 2 * origin_x + origin_x + 0.5f);
        screen_verts[i].y = (int)(clip_verts[i].y * z * 2 * origin_y + origin_y + 0.5f);

        screen_verts[i].r = clip_verts[i].r;
        screen_verts[i].g = clip_verts[i].g;
        screen_verts[i].b = clip_verts[i].b;
    }
}


static int num = 0;

void render(Render_Buffer *buff, Game_State *game) {

    // Clear the screen
    memset(buff->pixels, 0x22, buff->width * buff->height * sizeof(int));

    Vertex2Di temp_v[3];

    int origin_x = buff->width / 2;
    int origin_y = buff->height / 2;

    clip_space_to_screen(game->v, temp_v, 3, origin_x, origin_y);

    /*
    draw_line(buff, temp_v + 0, temp_v + 1);
    draw_line(buff, temp_v + 1, temp_v + 2);
    draw_line(buff, temp_v + 2, temp_v + 0);
    */

    triangle(buff, temp_v);

    for(unsigned char i = 0; i < 128; i++) {
        int cx = i % 32;
        int cy = i / 32; 
        render_character(i, buff->pixels, 1 + cx*4, 1 + cy*6, buff->width);
    }
}
