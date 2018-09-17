#ifndef TEXTURE_H
#define TEXTURE_H

#include "matrix.h"

typedef struct Texture {
    int width;
    int height;
    int *texels;
} Texture;

Texture *create_texture(int width, int height);

void fill_texture_with_data(Texture *texture, int *texels, int width, int height);

void free_texture(Texture *texture);

int lookup_texel(const Texture * const texture, float u, float v);


static inline void blend_three_texture_coords(Vector2f *const result,
                                       const Vector2f *const uv0,
                                       const Vector2f *const uv1,
                                       const Vector2f *const uv2,
                                       float weight0,
                                       float weight1,
                                       float weight2) {
    result->x = weight0 * uv0->x + weight1 * uv1->x + weight2 * uv2->x;
    result->y = weight0 * uv0->y + weight1 * uv1->y + weight2 * uv2->y;
}

#endif
