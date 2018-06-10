#ifndef COLOR_H
#define COLOR_H

#include "mymath.h"

typedef struct Color {
    float red, green, blue;
} Color;


static inline int rgb(float r, float g, float b) {
    clampf(&r, 0.0f, 1.0f);
    clampf(&g, 0.0f, 1.0f);
    clampf(&b, 0.0f, 1.0f);

    unsigned int R = (unsigned int)(r * 0xFF);
    unsigned int G = (unsigned int)(g * 0xFF);
    unsigned int B = (unsigned int)(b * 0xFF);

    return 0xFF000000 + (R << 16) + (G << 8) + B;
}


static inline int color_to_rbg(const Color *const color) {
    return rgb(color->red, color->green, color->blue);
}

static void blend_three_colors(Color *const result,
                               const Color *const color0,
                               const Color *const color1,
                               const Color *const color2,
                               float weight0,
                               float weight1,
                               float weight2) {

    result->red = weight0 * color0->red + weight1 * color1->red + weight2 * color2->red;
    result->green = weight0 * color0->green + weight1 * color1->green + weight2 * color2->green;
    result->blue = weight0 * color0->blue + weight1 * color1->blue + weight2 * color2->blue;
}


#endif /* COLOR_H */
