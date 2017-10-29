#ifndef RENDER_H
#define RENDER_H

#include "game.h"

typedef struct Render_Buffer {
    int width;
    int height;

    int *pixels;
} Render_Buffer;

Render_Buffer *create_render_buffer(int width, int height);

void free_render_buffer(Render_Buffer *buff);

void render(Render_Buffer *rbuffer, Game_State *game);

#endif
