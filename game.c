#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

#include "game.h"

float p = 3.14159f;
float dt = 0.003f;

void update(Game_State *game) {

    // Update the camera based on controller inputs
    if(game->controller.up)
        game->camera_pos.z -= 0.01f;
    if(game->controller.down)
        game->camera_pos.z += 0.01f;
}

void initialize_game(Game_State *game) {
    game->mesh.n_vertices = 3;
    game->mesh.n_indices = 3;

    game->mesh.positions = malloc(sizeof(Vector3f) * 3);
    game->mesh.colors = malloc(sizeof(Vector3f) * 3);
    game->mesh.indices = malloc(sizeof(int) * 3);

    // Triangle position
    game->mesh.positions[0].x = 0.0f;
    game->mesh.positions[0].y = 1.0f;
    game->mesh.positions[0].z = 0.0f;

    game->mesh.positions[1].x = -1.0f;
    game->mesh.positions[1].y = -1.0f;
    game->mesh.positions[1].z = 0.0f;

    game->mesh.positions[2].x = 1.0f;
    game->mesh.positions[2].y = -0.5f;
    game->mesh.positions[2].z = 0.0f;

    // Triangle Color
    game->mesh.colors[0].x = 1.0f;
    game->mesh.colors[0].y = 0.0f;
    game->mesh.colors[0].z = 0.0f;

    game->mesh.colors[1].x = 0.0f;
    game->mesh.colors[1].y = 1.0f;
    game->mesh.colors[1].z = 0.0f;

    game->mesh.colors[2].x = 0.0f;
    game->mesh.colors[2].y = 0.0f;
    game->mesh.colors[2].z = 1.0f;

    // Mesh Indices
    game->mesh.indices[0] = 0;
    game->mesh.indices[1] = 1;
    game->mesh.indices[2] = 2;

    // Camera position and rotation
    load_identity_matrix(&game->camera_rot);
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    game->camera_pos.z = 5.0f;

    // Controller starts w/ all buttons not pressed
    memset(&game->controller, 0, sizeof(Controller));
}
