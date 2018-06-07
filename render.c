#include "render.h"

#include "font.h"
#include "matrix.h"
#include "mymath.h"
#include "mesh.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

// NOTE: This is vulnerable to integer overflow if the screen coordinates are larger than 2^15
int half_space(int x0, int y0, int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (y0 - y1) - (y1 - y2) * (x0 - x1);
}

static void triangle(Render_Buffer *buff, const Vector3f v[3], const Vector3f colors[3])
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

    int x1 = (int)(v[top].x + 0.5f);
    int x2 = (int)(v[middle].x + 0.5f);
    int x3 = (int)(v[bottom].x + 0.5f);

    int y1 = (int)(v[top].y + 0.5f);
    int y2 = (int)(v[middle].y + 0.5f);
    int y3 = (int)(v[bottom].y + 0.5f);

    // Bounding rectangle
    int minx = int_min3(x1, x2, x3);
    int maxx = int_max3(x1, x2, x3);
    int miny = int_min3(y1, y2, y3);
    int maxy = int_max3(y1, y2, y3);

    // Scan through bounding rectangle
    for(int y = miny; y <= maxy; y++) {
        for(int x = minx; x <= maxx; x++) {
            int w0 = half_space(x, y, x1, y1, x2, y2);
            int w1 = half_space(x, y, x2, y2, x3, y3);
            int w2 = half_space(x, y, x3, y3, x1, y1);
            // When all half-space functions positive, pixel is in triangle
            if(w0 >= 0 && w1 >= 0 && w2 >= 0) {
                float denom = w0 + w1 + w2;

                float bary0 = w0 / denom;
                float bary1 = w1 / denom;
                float bary2 = w2 / denom;

                float red    = bary0 * colors[top].x + bary1 * colors[middle].x + bary2 * colors[bottom].x;
                float blue   = bary0 * colors[top].y + bary1 * colors[middle].y + bary2 * colors[bottom].y;
                float green  = bary0 * colors[top].z + bary1 * colors[middle].z + bary2 * colors[bottom].z;

                fill_pixel(buff, x, y, rgb(red, blue, green));
            }
            // Draw bounding box
            if(x == minx || x == maxx || y == miny || y == maxy) {
                fill_pixel(buff, x, y, 0xEEEEEEEE);
            }
        }
    }
}

static void clip_space_to_screen(Vector3f *screen_verts, const Vector3f *const clip_verts, size_t count, int origin_x, int origin_y) {
    for(int i = 0; i < count; i++) {
        float z = -1.0 / clip_verts[i].z;
        screen_verts[i].x = (int)(clip_verts[i].x * z * 2 * origin_x + origin_x + 0.5f);
        screen_verts[i].y = (int)(clip_verts[i].y * z * 2 * origin_y + origin_y + 0.5f);
    }
}


static void render_mesh(Render_Buffer *buff, const Mesh *const mesh, const Matrix3x3f *const camera_rot, const Vector3f *const camera_pos) {
    int origin_x = buff->width / 2;
    int origin_y = buff->height / 2;

    for(int i = 0; i < mesh->n_indices; i+=3) {
        Vector3f temp_triangle[3];
        Vector3f temp_colors[3];

        memcpy(temp_triangle, mesh->positions + mesh->indices[i], sizeof(Vector3f));
        memcpy(temp_triangle + 1, mesh->positions + mesh->indices[i + 1], sizeof(Vector3f));
        memcpy(temp_triangle + 2, mesh->positions + mesh->indices[i + 2], sizeof(Vector3f));

        memcpy(temp_colors, mesh->colors + mesh->indices[i], sizeof(Vector3f));
        memcpy(temp_colors + 1, mesh->colors + mesh->indices[i + 1], sizeof(Vector3f));
        memcpy(temp_colors + 2, mesh->colors + mesh->indices[i + 2], sizeof(Vector3f));

        transform_vectors(temp_triangle, 3, camera_rot, camera_pos);
        clip_space_to_screen(temp_triangle, temp_triangle, 3, origin_x, origin_y);

        triangle(buff, temp_triangle, temp_colors);
    }
}


void render(Render_Buffer *buff, const Game_State *const game) {
    // Clear the screen
    memset(buff->pixels, 0x22, buff->width * buff->height * sizeof(int));

    render_mesh(buff, &game->mesh, &game->camera_rot, &game->camera_pos);

    char s[100] = {};

    sprintf(s, "Current FPS: %d", game->fps);

    render_string(s, buff->pixels, 1, 1, buff->width);
}
