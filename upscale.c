#include <string.h>

#include "upscale.h"

#include <stdio.h>

void upscale(int *src, int *dest, int src_width, int src_height, int dest_width, int dest_height) {
    int w_scale = dest_width / src_width;
    int h_scale = dest_height / src_height;

    for(int j = 0; j < src_height; j++) {
        for(int i = 0; i < src_width; i++) {
            for(int b = 0; b < h_scale; b++) {
                for(int a = 0; a < w_scale; a++) {
                    int x = i * w_scale + a;
                    int y = j * h_scale + b;
                    dest[x + y*dest_width] = src[i + j*src_width];
                }
            }
        }
    }
}
