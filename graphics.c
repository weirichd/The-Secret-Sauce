#include "graphics.h"

#include <stdlib.h>

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
