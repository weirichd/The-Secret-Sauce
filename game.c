#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"
#include "mesh.h"
#include "objloader.h"

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
        c, -s, 0,
        s, c, 0,
        0, 0, 0,
    };

//    transform_vectors(game->mesh->positions, game->mesh->n_vertices, &mat, NULL);
}

void initialize_game(Game_State *game) {
    game->mesh = load_mesh_from_obj("dodecahedron.obj");
//    game->mesh = load_mesh_from_obj("square.obj");

    // Camera position and rotation
    load_identity_matrix(&game->camera_rot);
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    game->camera_pos.z = 5.0f;

    // Controller starts w/ all buttons not pressed
    memset(&game->controller, 0, sizeof(Controller));
}
