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
    buff->zbuffer = malloc(sizeof(float) * width * height);

    return buff;
}


void free_render_buffer(Render_Buffer *buff) {
    free(buff->pixels);
    free(buff->zbuffer);
    free(buff);
}


static inline void fill_pixel(Render_Buffer *buff, int x, int y, float z, int color) {
    if(0 <= x && buff->width > x && 0 <= y && buff->height > y && buff->zbuffer[x + y * buff->width] > z) {
        buff->pixels[x + y * buff->width] = color;
        buff->zbuffer[x + y * buff->width] = z;
    }
}


static inline float half_space(float px, float py, float x0, float y0, float x1, float y1) {
    return (px - x0) * (y1 - y0) - (py - y0) * (x1 - x0);
}


static inline int interior_point(float w0, float w1, float w2) {
    return (w0 >= 0 && w1 >= 0 && w2 >= 0);
}

static inline float interpolate_vertex_attribute(float w0, float z0, float a0,
                                                 float w1, float z1, float a1,
                                                 float w2, float z2, float a2) {

    return (w0 * a0 * z0 + w1 * a1 * z1 + w2 * a2 * z2) / (w0 * z0 + w1 * z1 + w2 * z2);
}

static void rasterize_triangle(Render_Buffer *buff,
                               const Vector3f *v,
                               const Color *colors,
                               const Vector2f *tex_coords,
                               const int indices[3],
                               const Texture *texture) {

    float origin_x = buff->width * 0.5f;
    float origin_y = buff->height * 0.5f;

    float z0 = -1.0 / v[indices[0]].z;
    float z1 = -1.0 / v[indices[1]].z;
    float z2 = -1.0 / v[indices[2]].z;

    float x0 = (1.0f - v[indices[0]].x * 2.0f * z0) * origin_x + 0.5f;
    float x1 = (1.0f - v[indices[1]].x * 2.0f * z1) * origin_x + 0.5f;
    float x2 = (1.0f - v[indices[2]].x * 2.0f * z2) * origin_x + 0.5f;

    float y0 = (1.0f + v[indices[0]].y * 2.0f * z0) * origin_y - 0.5f;
    float y1 = (1.0f + v[indices[1]].y * 2.0f * z1) * origin_y - 0.5f;
    float y2 = (1.0f + v[indices[2]].y * 2.0f * z2) * origin_y - 0.5f;

    float area = half_space(x0, y0, x1, y1, x2, y2);

    if(area < 0) // Not a CCW triangle
        return;

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
            float w0 = half_space(x, y, x1, y1, x2, y2);
            float w1 = half_space(x, y, x2, y2, x0, y0);
            float w2 = half_space(x, y, x0, y0, x1, y1);
            // When all half-space functions positive, pixel is in triangle
            if(interior_point(w0, w1, w2)) {

                int color_hex = 0xFFFFFFFF;

                if (colors) {
                    Color final_color;
    
                    final_color.red = interpolate_vertex_attribute(w0, z0, colors[indices[0]].red,
                                                                   w1, z1, colors[indices[1]].red,
                                                                   w2, z2, colors[indices[2]].red);

                    final_color.green = interpolate_vertex_attribute(w0, z0, colors[indices[0]].green,
                                                                     w1, z1, colors[indices[1]].green,
                                                                     w2, z2, colors[indices[2]].green);

                    final_color.blue = interpolate_vertex_attribute(w0, z0, colors[indices[0]].blue,
                                                                    w1, z1, colors[indices[1]].blue,
                                                                    w2, z2, colors[indices[2]].blue);

                    color_hex = color_to_rbg(&final_color);
                }

                if (texture) {
                    Vector2f final_uv;

                    final_uv.x = interpolate_vertex_attribute(w0, z0, tex_coords[indices[0]].x,
                                                              w1, z1, tex_coords[indices[1]].x,
                                                              w2, z2, tex_coords[indices[2]].x);

                    final_uv.y = interpolate_vertex_attribute(w0, z0, tex_coords[indices[0]].y,
                                                              w1, z1, tex_coords[indices[1]].y,
                                                              w2, z2, tex_coords[indices[2]].y);

                    color_hex = lookup_texel(texture, final_uv.x, final_uv.y);
                }

                float z = (w0 * z0 + w1 * z1 + w2 * z2) / (w0 + w1 + w2);

                fill_pixel(buff, x, y, z, color_hex);
            }
        }
    }
}


static void render_mesh(Render_Buffer *buff,
                        const Mesh *const mesh,
                        const Texture *const texture,
                        const Matrix3x3f *const camera_rot,
                        const Vector3f *const camera_pos) {

    // Make a temporary copy of the mesh's vertex positions to transform
    Vector3f *temp_vertices = malloc(3 * sizeof(Vector3f) * mesh->n_vertices);
    memcpy(temp_vertices, mesh->positions, 3 * sizeof(Vector3f) * mesh->n_vertices);

    // Transform the temporary copy
    transform_vectors(temp_vertices, mesh->n_vertices, camera_rot, camera_pos);

    for(int i = 0; i < mesh->n_indices; i+=3) {
        rasterize_triangle(buff, temp_vertices, mesh->colors, mesh->uv_coords, mesh->indices + i, NULL);
    }

    free(temp_vertices);
}


void render(Render_Buffer *buff, const Game_State *const game) {
    // Clear the screen
    memset(buff->pixels, 0x11, buff->width * buff->height * sizeof(int));
    memset(buff->zbuffer, 0.0f, buff->width * buff->height * sizeof(float));

    render_mesh(buff, game->mesh, game->texture, &game->camera_rot, &game->camera_pos);

    char s[100] = {};

    sprintf(s, "Current FPS: %d", game->fps);
    render_string(s, buff->pixels, 1, 1, buff->width);

    sprintf(s, "Cam: (%f, %f, %f)", game->camera_pos.x, game->camera_pos.y, game->camera_pos.z);
    render_string(s, buff->pixels, 1, 12, buff->width);
}
