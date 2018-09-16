#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

typedef struct Vector3fLL {
    float x, y, z;
    struct Vector3fLL *next;
} Vector3fLL;

typedef struct IndexLL {
    int i;
    struct IndexLL *next;
} IndexLL;

int main() {
    Vector3fLL *vert_head = calloc(1, sizeof(Vector3fLL));
    Vector3fLL *vert_tail = vert_head;

    IndexLL *ind_head = calloc(1, sizeof(IndexLL));
    IndexLL *ind_tail = ind_head;

    int num_verts = 0;
    int num_inds = 0;


    FILE *fp;

    char buffer[255] = {};
    char str[100] = {};

    fp = fopen("dodecahedron.obj", "r");


    // Read obj file data into linked lists
    while(fgets(buffer, sizeof(buffer), fp)) {
        if (buffer[0] == 'v') {
            float a, b, c;
            sscanf(buffer, "v %f %f %f", &a, &b, &c);

            num_verts++;
            
            vert_tail->x = a;
            vert_tail->y = b;
            vert_tail->z = c;
            vert_tail->next = calloc(1, sizeof(Vector3fLL));

            vert_tail = vert_tail->next;
        }
        if (buffer[0] == 'f') {
            int a, b, c;            

            sscanf(buffer, "f %d %d %d", &a, &b, &c);

            num_inds += 3;

            ind_tail->i = a;
            ind_tail->next = calloc(1, sizeof(IndexLL));
            ind_tail = ind_tail->next;

            ind_tail->i = b;
            ind_tail->next = calloc(1, sizeof(IndexLL));
            ind_tail = ind_tail->next;

            ind_tail->i = c;
            ind_tail->next = calloc(1, sizeof(IndexLL));
            ind_tail = ind_tail->next;
        }
    }

    fclose(fp);

    printf("-----------\n");
    printf("Verts: %d    Indices: %d\n", num_verts, num_inds);
    printf("-----------\n");

    Vector3fLL *current = vert_head;

    while (current->next) {
        printf("(%f, %f, %f)\n", current->x, current->y, current->z);
        Vector3fLL *next = current->next;
        free(current);
        current = next;
    }

    IndexLL *ind_current = ind_head;

    while(ind_current->next) {
        printf("%d, ", ind_current->i);
        IndexLL *next = ind_current->next;
        free(ind_current);
        ind_current = next;
    }

    return 0;
}
