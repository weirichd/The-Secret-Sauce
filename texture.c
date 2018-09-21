#include "texture.h"

#include "mymath.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Texture *create_texture(int width, int height) {
    Texture *texture = malloc(sizeof(Texture));
    texture->width = width;
    texture->height = height;
    texture->texels = malloc(sizeof(int) * width * height);

    return texture;
}

void fill_texture_with_data(Texture *texture, int *texels, int width, int height) {
    memcpy(texture->texels, texels, sizeof(int) * width * height);
}


void free_texture(Texture *texture) {
    free(texture->texels);
    free(texture);
}


int lookup_texel(const Texture * const texture, float u, float v) {

    float epsilon_width = 1.0f / ((float) (2.0f * texture->width));
    float epsilon_height = 1.0f / ((float) (2.0f * texture->height));

    clampf(&u, epsilon_width, 1.0f - epsilon_width);
    clampf(&v, epsilon_height, 1.0f - epsilon_height);

    int x = (int)(u * texture->width);
    int y = (int)(v * texture->height);

    int i = y * texture->width + x;

    int value = texture->texels[i];

    return value;
}
