#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct Render_Buffer {
    int width;
    int height;

    int *pixels;
} Render_Buffer;

Render_Buffer *create_render_buffer(int width, int height);

void free_render_buffer(Render_Buffer *buff);

#endif
