#include <stdlib.h>
#include <math.h>

#include "matrix.h"

#include "game.h"

float p = 3.14159f;
float dt = 0.003f;

void update(Game_State *game) {

    float c = cos(dt);
    float s = sin(dt);

    Matrix3x3f mat1 = {
        c, 0, -s,
        0, 1, 0,
        s, 0, c
    };

    matrix_vector_mul3f(&game->v[0], &mat1, &game->v[0]);
    matrix_vector_mul3f(&game->v[1], &mat1, &game->v[1]);
    matrix_vector_mul3f(&game->v[2], &mat1, &game->v[2]);
}

void initialize_game(Game_State *game) {
    // Triangle position
    game->v[0].x = 0.0f;
    game->v[0].y = 1.0f;
    game->v[0].z = 0.0f;

    game->v[1].x = -1.0f;
    game->v[1].y = -1.0f;
    game->v[1].z = 0.0f;

    game->v[2].x = 1.0f;
    game->v[2].y = -0.5f;
    game->v[2].z = 0.0f;

    // Triangle Color
    game->c[0].x = 1.0f;
    game->c[0].y = 0.0f;
    game->c[0].z = 0.0f;

    game->c[1].x = 0.0f;
    game->c[1].y = 1.0f;
    game->c[1].z = 0.0f;

    game->c[2].x = 0.0f;
    game->c[2].y = 0.0f;
    game->c[2].z = 1.0f;

}
