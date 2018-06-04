#include <stdlib.h>
#include <math.h>

#include "matrix.h"

#include "game.h"

float p = 3.14159f;

float dt = 0.003f;

void update(Game_State *game) {

    Matrix3x3f mat = {
        cos(dt), -sin(dt), 0.0,
        sin(dt),  cos(dt), 0.0,
        0.0,          0.0, 1.0,
    };

    matrix_vector_mul3f(&game->v[0], &mat, &game->v[0]);
    matrix_vector_mul3f(&game->v[1], &mat, &game->v[1]);
    matrix_vector_mul3f(&game->v[2], &mat, &game->v[2]);
}

void initialize_game(Game_State *game) {
    game->v[0].x = 0.0f;
    game->v[0].y = 1.0f;
    game->v[0].z = 5.0f;

    game->v[1].x = -1.0f;
    game->v[1].y = -1.0f;
    game->v[1].z = 5.0f;

    game->v[2].x = 1.0f;
    game->v[2].y = -1.0f;
    game->v[2].z = 5.0f;
}
