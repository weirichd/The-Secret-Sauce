#ifndef SQUARE_H
#define SQUARE_H

float square_positions[] = {
    1, 1, 0,
    -1, -1, 0,
    -1, 1, 0,
    1, -1, 0,
};

float square_colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};

int square_indices[] = {0, 1, 2, 1, 0, 3};

int n_square_indices = sizeof(square_indices) / sizeof(int);

int n_square_vertices = sizeof(square_positions) / (sizeof(float) * 3);

#endif
