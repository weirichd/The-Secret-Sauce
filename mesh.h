#ifndef MESH_H
#define MESH_H

#include "matrix.h"

typedef struct Mesh {
    int n_vertices;
    int n_indices;

    Vector3f *positions;
    Vector3f *colors;
    int *indices;
} Mesh;



#endif /* MESH_H */
