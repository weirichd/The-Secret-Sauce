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
    0xff15b01a, 0xff0343df, 0xffe50000,
    0xffff028d, 0xff7e1e9c, 0xfff97306,
    0xffff474c, 0xff069af3, 0xff929591,
};

int n_mesh_indices = sizeof(mesh_indices) / sizeof(int);

int n_mesh_vertices = sizeof(mesh_positions) / (sizeof(float) * 3);

#endif
