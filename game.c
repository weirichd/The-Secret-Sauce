#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

#include "game.h"

float p = 3.14159f;
float dt = 0.003f;

void update(Game_State *game) {

    float c = cos(dt);
    float s = sin(dt);

    Matrix3x3f mat2 = {
        c, -s,0,
        s, c, 0,
        0, 0, 1,
    };

    matrix_vector_mul3f(&game->v[0], &mat2, &game->v[0]);
    matrix_vector_mul3f(&game->v[1], &mat2, &game->v[1]);
    matrix_vector_mul3f(&game->v[2], &mat2, &game->v[2]);

    // Update the camera based on controller inputs
    if(game->controller.up)
        game->camera_pos.z -= 0.01f;
    if(game->controller.down)
        game->camera_pos.z += 0.01f;
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


    // Camera position and rotation
    load_identity_matrix(&game->camera_rot);
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    game->camera_pos.z = 5.0f;

    // Controller starts w/ all buttons not pressed
    memset(&game->controller, 0, sizeof(Controller));
}
