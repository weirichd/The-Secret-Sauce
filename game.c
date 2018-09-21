#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "mesh.h"

#include "game.h"

#include "square.h"

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

    Matrix3x3f mat = {
        9.99989355e-01,  -2.29997957e-03,  -3.99998933e-03,
        2.29999797e-03,   9.99997355e-01,   0.00000000e+00,
        3.99997875e-03,  -9.19996736e-06,   9.99992000e-01
    };


    transform_vectors(game->mesh->positions, game->mesh->n_vertices, &mat, NULL);
}

void initialize_game(Game_State *game) {
    game->mesh = create_mesh(n_mesh_vertices, n_mesh_indices);
    fill_mesh(mesh_positions,
              mesh_colors,
              mesh_uvs,
              mesh_indices,
              n_mesh_vertices,
              n_mesh_indices,
              game->mesh);

    game->texture = create_texture(3, 3);
    fill_texture_with_data(game->texture, texture_data, 3, 3);

    // Camera position and rotation
    load_identity_matrix(&game->camera_rot);
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    game->camera_pos.z = 5.0f;

    // Controller starts w/ all buttons not pressed
    memset(&game->controller, 0, sizeof(Controller));
}
