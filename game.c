#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"
#include "mesh.h"

#include "game.h"

float p = 3.14159f;
float dt = 0.003f;

void update(Game_State *game) {

    // Update the camera based on controller inputs
    if(game->controller.up)
        game->camera_pos.z -= 0.003f;
    if(game->controller.down)
        game->camera_pos.z += 0.003f;

    if(game->controller.left)
        game->camera_pos.x -= 0.003;
    if(game->controller.right)
        game->camera_pos.x += 0.003;

    float c = cos(0.004f);
    float s = sin(0.004f);

    Matrix3x3f mat = {
        c, 0, -s,
        0, 1, 0,
        s, 0, c,
    };

    transform_vectors(game->mesh->positions, game->mesh->n_vertices, &mat, NULL);
}

void initialize_game(Game_State *game) {
    float positions[] = {
        1, 1, 0,
        -1, -1, 0,
        -1, 1, 0,
        1, -1, 0,
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.1f, 0.1f, 0.2f,
        0.0f, 0.0f, 1.0f,
        0.2f, 0.1f, 0.1f,
    };

    int indices[] = {0, 1, 2, 1, 0, 3};

    game->mesh = create_mesh(4, 6);
    fill_mesh(positions, colors, indices, 4, 6, game->mesh);

    // Camera position and rotation
    load_identity_matrix(&game->camera_rot);
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    game->camera_pos.z = 5.0f;

    // Controller starts w/ all buttons not pressed
    memset(&game->controller, 0, sizeof(Controller));
}
