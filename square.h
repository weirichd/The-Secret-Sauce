#ifndef SQUARE_H
#define SQUARE_H

float mesh_positions[] = {
    1, 1, 0,
    -1, -1, 0,
    -1, 1, 0,
    1, -1, 0,
};

float mesh_colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};

int mesh_indices[] = {
  0, 2, 1,
  1, 3, 0
};

int n_mesh_indices = sizeof(mesh_indices) / sizeof(int);

int n_mesh_vertices = sizeof(mesh_positions) / (sizeof(float) * 3);

#endif
