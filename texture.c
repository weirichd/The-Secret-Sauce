#include "texture.h"

#include <stdlib.h>
#include <string.h>

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
    // TODO: What to to when u, v outside [0, 1] range...

    int x = (int)(u * texture->width);
    int y = (int)(v * texture->height);

    int i = y * texture->width + x;

    return texture->texels[i];
}
