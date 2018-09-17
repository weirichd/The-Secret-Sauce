#ifndef MESH_H
#define MESH_H

#include "matrix.h"
#include "color.h"

typedef struct Mesh {
    int n_vertices;
    int n_indices;

    Vector3f *positions;
    Color *colors;
    Vector2f *uv_coords;

    int *indices;
} Mesh;

Mesh *create_mesh(int n_vertices, int n_indices);

void free_mesh(Mesh *mesh);

void fill_mesh(const float *const positions,
               const float *const colors,
               const float *const uv_coords,
               const int *const indices,
               int n_vertices,
               int n_indices,
               const Mesh *mesh);

#endif /* MESH_H */
