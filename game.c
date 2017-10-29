#include <stdlib.h>
#include <math.h>

#include "game.h"

float t = 0.0f;

void update(Game_State *game) {
    t += 0.007f;

    game->v[0].x = cos(t + 2);
    game->v[0].z = sin(t + 2) + 5.0f;

    game->v[1].x = cos(t + 4);
    game->v[1].z = sin(t + 4) + 5.0f;

    game->v[2].x = cos(t);
    game->v[2].z = sin(t) + 5.0f;

    game->v[3].x = cos(t - 1);
    game->v[3].z = sin(t - 1) + 5.0f;
}

void initialize_game(Game_State *game) {

    game->v[0].x = 0.0f; game->v[0].y = 1.0f; game->v[0].z = 3.0f;
    game->v[0].r = 1.0f; game->v[0].g = 0.0f; game->v[0].b = 0.0f;

    game->v[1].x = -1.0f; game->v[1].y = -1.0f; game->v[1].z = 3.0f;
    game->v[1].r = 0.0f; game->v[1].g = 1.0f; game->v[1].b = 0.0f;

    game->v[2].x = 1.0f; game->v[2].y = -1.0f; game->v[2].z = 3.0f;
    game->v[2].r = 0.0f; game->v[2].g = 0.0f; game->v[2].b = 1.0f;

    game->v[3].x = 1.0f; game->v[3].y = 1.0f; game->v[3].z = 3.0f;
    game->v[3].r = 0.5f; game->v[3].g = 0.5f; game->v[3].b = 0.5f;
}
