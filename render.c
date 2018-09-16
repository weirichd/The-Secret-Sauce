#include "render.h"

#include "font.h"
#include "matrix.h"
#include "mymath.h"
#include "mesh.h"
#include "color.h"

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


static inline void fill_pixel(Render_Buffer *buff, int x, int y, int color) {
    if(0 <= x && buff->width > x && 0 <= y && buff->height > y) {
        buff->pixels[x + y * buff->width] = color;
    }
}


// NOTE: This is vulnerable to integer overflow if the screen coordinates are larger than 2^15
static inline int half_space(int px, int py, int x0, int y0, int x1, int y1) {
    return (px - x0) * (y1 - y0) - (py - y0) * (x1 - x0);
}


static inline int interior_point(int *w0, int *w1, int *w2) {
    // Render both CW and CCW triangles for the time being!
    if (*w0 <= 0 && *w1 <= 0 && *w2 <= 0) {
        *w0 = *w0 * -1;
        *w1 = *w1 * -1;
        *w2 = *w2 * -1;
    }

    return *w0 >= 0 && *w1 >= 0 && *w2 >= 0;
}


static void rasterize_triangle(Render_Buffer *buff, const Vector3f v[3], const Color colors[3], const int indices[3]) {
    // TODO: Less janky snapping to pixels
    int x0 = (int)(v[indices[0]].x + 0.5f);
    int x1 = (int)(v[indices[1]].x + 0.5f);
    int x2 = (int)(v[indices[2]].x + 0.5f);

    int y0 = (int)(v[indices[0]].y + 0.5f);
    int y1 = (int)(v[indices[1]].y + 0.5f);
    int y2 = (int)(v[indices[2]].y + 0.5f);

    // Bounding rectangle
    int minx = int_min3(x0, x1, x2);
    int maxx = int_max3(x0, x1, x2);
    int miny = int_min3(y0, y1, y2);
    int maxy = int_max3(y0, y1, y2);

    clampi(&minx, 0, buff->width);
    clampi(&maxx, 0, buff->width);
    clampi(&miny, 0, buff->height);
    clampi(&maxy, 0, buff->height);

    // Scan through bounding rectangle
    for(int y = miny; y <= maxy; y++) {
        for(int x = minx; x <= maxx; x++) {
            int w0 = half_space(x, y, x1, y1, x2, y2);
            int w1 = half_space(x, y, x2, y2, x0, y0);
            int w2 = half_space(x, y, x0, y0, x1, y1);
            // When all half-space functions positive, pixel is in triangle
            if(interior_point(&w0, &w1, &w2)) {
                float denom = w0 + w1 + w2;

                float bary0 = w0 / denom;
                float bary1 = w1 / denom;
                float bary2 = w2 / denom;

                Color final_color;
                blend_three_colors(&final_color, &colors[indices[0]], &colors[indices[1]], &colors[indices[2]], bary0, bary1, bary2);
                int color_hex = color_to_rbg(&final_color);

                fill_pixel(buff, x, y, color_hex);
            }
        }
    }
}


static void clip_space_to_screen(Vector3f *verts, size_t count, int origin_x, int origin_y) {
    for(int i = 0; i < count; i++) {
        float z = -1.0 / verts[i].z;
        verts[i].x = (int)(-verts[i].x * z * 2 * origin_x + origin_x + 0.5f);
        verts[i].y = (int)(verts[i].y * z * 2 * origin_y + origin_y + 0.5f);
    }
}


static void orthographic_projection(Vector3f *verts, size_t count, int screen_w, int screen_h) {
    for(int i = 0; i < count; i++) {
        verts[i].x = (int)((verts[i].x *  0.5f + 0.5f) * screen_w + 0.5f);
        verts[i].y = (int)((verts[i].y * -0.5f + 0.5f) * screen_h + 0.5f); // Buffer y goes + -> down
    }
}


static void render_mesh(Render_Buffer *buff, const Mesh *const mesh, const Matrix3x3f *const camera_rot, const Vector3f *const camera_pos) {
    int origin_x = buff->width / 2;
    int origin_y = buff->height / 2;

    // Make a temporary copy of the mesh's vertex positions to transform
    Vector3f *temp_vertices = malloc(3 * sizeof(Vector3f) * mesh->n_vertices);
    memcpy(temp_vertices, mesh->positions, 3 * sizeof(Vector3f) * mesh->n_vertices);

    // Transform the temporary copy
    transform_vectors(temp_vertices, mesh->n_vertices, camera_rot, camera_pos);
    clip_space_to_screen(temp_vertices, mesh->n_vertices, origin_x, origin_y);
    //orthographic_projection(temp_vertices, mesh->n_vertices, buff->width, buff->height);

    for(int i = 0; i < mesh->n_indices; i+=3) {
        rasterize_triangle(buff, temp_vertices, mesh->colors, mesh->indices + i);
    }

    free(temp_vertices);
}


void render(Render_Buffer *buff, const Game_State *const game) {
    // Clear the screen
    memset(buff->pixels, 0x11, buff->width * buff->height * sizeof(int));

    render_mesh(buff, game->mesh, &game->camera_rot, &game->camera_pos);

    char s[100] = {};

    sprintf(s, "Current FPS: %d", game->fps);
    render_string(s, buff->pixels, 1, 1, buff->width);

    sprintf(s, "Cam: (%f, %f, %f)", game->camera_pos.x, game->camera_pos.y, game->camera_pos.z);
    render_string(s, buff->pixels, 1, 12, buff->width);
}
