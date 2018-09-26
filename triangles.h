#ifndef SQUARE_H
#define SQUARE_H

float mesh_positions[] = {
    1, 1, 0,
    0, 1, 0,
    0.75, -1.2, -0.5,

    -1, 1, 0,
    -1, 0, 0,
     1.2, 0.75, -0.5,

    -1, -1, 0,
    0, -1, 0,
    -0.75, 1.2, -0.5,

    1, -1, 0,
    1, 0, 0,
    -1.2, -0.75, -0.5,
};

float mesh_colors[] = {
    1.0f, 0.5f, 0.5f,
    1.0f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,

    0.5f, 1.0f, 0.5f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f,

    0.5f, 0.5f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.5f,

    1.0f, 1.0f, 0.5f,
    1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,
};

float mesh_uvs[] = {
    1, 1,
    0, 0,
    0, 1,
    1, 0,
};

int mesh_indices[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11
};

int texture_data[] = {
    0xff15b01a, 0xff0343df, 0xffe50000, 0xffffffff,
    0xffff028d, 0xff7e1e9c, 0xfff97306, 0xff000000,
    0xffff474c, 0xff069af3, 0xff929591, 0xffffffff,
    0xffffffff, 0xff000000, 0xffffffff, 0xff000000
};

int n_mesh_indices = sizeof(mesh_indices) / sizeof(int);

int n_mesh_vertices = sizeof(mesh_positions) / (sizeof(float) * 3);

#endif
