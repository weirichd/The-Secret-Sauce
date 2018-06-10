#include "mesh.h"

#include <stdio.h>

Mesh *create_mesh(int n_vertices, int n_indices) {
    Mesh *mesh = malloc(sizeof(Mesh));    

    mesh->n_vertices = n_vertices;
    mesh->n_indices = n_indices;

    mesh->positions = malloc(sizeof(Vector3f) * n_vertices);
    mesh->colors = malloc(sizeof(Vector3f) * n_vertices);
    mesh->indices = malloc(sizeof(int) * n_indices);
    
    return mesh;
}

void free_mesh(Mesh *mesh) {
    free(mesh->positions);
    free(mesh->colors);
    free(mesh->indices);
    free(mesh);
}

void fill_mesh(const float *const positions, const float *const colors, const int *const indices, int n_vertices, int n_indices, const Mesh *mesh) {
    memcpy(mesh->positions, positions, 3 * sizeof(float) * n_vertices);
    memcpy(mesh->colors, colors, 3 * sizeof(float) * n_vertices);
    memcpy(mesh->indices, indices, sizeof(int) * n_indices);
}

