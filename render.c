#include <string.h>

unsigned char i = 0;

void render(int *pixels) {
    
    // Clear the screen 
    memset(pixels, i++, 640*480*sizeof(int));
}


