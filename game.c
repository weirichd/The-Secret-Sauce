#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"
#include "mesh.h"

#include "game.h"

#include "triangles.h"

void update(Game_State *game) {

    // Update the camera based on controller inputs
    if(game->controller.up)
        game->camera_pos.z -= 0.03f;
    if(game->controller.down)
        game->camera_pos.z += 0.03f;

    if(game->controller.left)
        game->camera_pos.x -= 0.03;
    if(game->controller.right)
        game->camera_pos.x += 0.03;

    float t = 0.03f;
    float s = 0.02f;

    Matrix3x3f mat1 = {
        cosf(t), -sinf(t), 0.,
        sinf(t),  cosf(t), 0.,
        0.     ,  0.     , 1.
    };

    Matrix3x3f mat = {
        cosf(s), 0, -sinf(s),
        0.     ,  1.     , 0.,
        sinf(s),  0, cosf(s)
    };

    transform_vectors(game->mesh->positions, game->mesh->n_vertices, &mat1, NULL);
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

    game->texture = create_texture(4, 4);
    fill_texture_with_data(game->texture, texture_data, 4, 4);

    // Camera position and rotation
    load_identity_matrix(&game->camera_rot);
    game->camera_pos.x = 0.0f;
    game->camera_pos.y = 0.0f;
    game->camera_pos.z = 5.0f;

    // Controller starts w/ all buttons not pressed
    memset(&game->controller, 0, sizeof(Controller));
}
