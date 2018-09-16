#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "mesh.h"


typedef struct FloatLL {
    float x;
    struct FloatLL *next;
} FloatLL;

typedef struct IntLL {
    int i;
    struct IntLL *next;
} IntLL;

int main() {
    FloatLL *pos_head = calloc(1, sizeof(FloatLL));
    FloatLL *pos_tail = pos_head;

    IntLL *ind_head = calloc(1, sizeof(FloatLL));
    IntLL *ind_tail = ind_head;

    int num_poss = 0;
    int num_inds = 0;


    FILE *fp;

    char buffer[255] = {};
    char str[100] = {};

    fp = fopen("dodecahedron.obj", "r");


    // Read obj file data into linked lists
    while(fgets(buffer, sizeof(buffer), fp)) {
        if (buffer[0] == 'v') {
            float x[3];
            sscanf(buffer, "v %f %f %f", x, x+1, x+2);

            for(int i = 0; i < 3; i++) {
                pos_tail->x = x[i];
                pos_tail->next = calloc(1, sizeof(FloatLL));
                pos_tail = pos_tail->next;
            }
            num_poss += 3;
        }

        if (buffer[0] == 'f') {
            int a[3];
            sscanf(buffer, "f %d %d %d", a, a+1, a+2);

            for(int i = 0; i < 3; i++) {
                ind_tail->i = a[i];
                ind_tail->next = calloc(1, sizeof(IntLL));
                ind_tail = ind_tail->next;
            }
            num_inds += 3;
        }
    }

    fclose(fp);

    printf("-----------\n");
    printf("READ:\n");
    printf("Verts: %d    Indices: %d\n", num_poss, num_inds);
    printf("-----------\n");

    // Convert linked lists to normal arrays

    return 0;
}
