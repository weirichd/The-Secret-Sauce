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


Mesh *load_mesh_from_obj(const char *obj_file) {
    FloatLL *pos_head = calloc(1, sizeof(FloatLL));
    FloatLL *pos_tail = pos_head;

    IntLL *ind_head = calloc(1, sizeof(FloatLL));
    IntLL *ind_tail = ind_head;

    int num_poss = 0;
    int num_inds = 0;

    FILE *fp;

    char buffer[255] = {};
    char str[100] = {};

    fp = fopen(obj_file, "r");


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

    printf("Read %d vertices and %d indices\n", num_poss / 3, num_inds);

    // Convert linked lists to normal arrays
    float positions[num_poss];
    float colors[num_poss];
    int indices[num_inds];

    FloatLL *current_pos = pos_head;
    for(int i = 0; i < num_poss; i++) {
        
        positions[i] = current_pos->x;
        colors[i] = (float)rand()/(float)(RAND_MAX);
        FloatLL *next_pos = current_pos->next;
        //free(current_pos);
        current_pos = next_pos;
    }

    printf("I got here\n");

    IntLL *current_ind = ind_head;
    for(int i = 0; i < num_poss; i++) {
       indices[i] = current_ind->i;
       IntLL *next_ind = current_ind->next;
//       free(current_ind);
       current_ind = next_ind;
    }

    Mesh *mesh = create_mesh(num_poss / 3, num_inds);

    fill_mesh(positions, colors, indices,  mesh->n_vertices, mesh->n_indices, mesh);

    printf("I got here\n");

    return mesh;
}

