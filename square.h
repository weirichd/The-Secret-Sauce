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

float mesh_uvs[] = {
    1, 1,
    0, 0,
    0, 1,
    1, 0,
};

int mesh_indices[] = {
    0, 2, 1,
    1, 3, 0
};

int texture_data[] = {
    0xFFFF0000, 0xFF00FF00,
    0xFF0000FF, 0xFFFFFF00,
};

int n_mesh_indices = sizeof(mesh_indices) / sizeof(int);

int n_mesh_vertices = sizeof(mesh_positions) / (sizeof(float) * 3);

#endif
