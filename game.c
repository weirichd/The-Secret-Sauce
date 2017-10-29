#include <stdlib.h>
#include <math.h>

#include "game.h"

float t = 0.0f;

void update(Game_State *game) {
    t += 0.007f;

    game->x[0] = cos(t + 2);
    game->z[0] = sin(t + 2) + 5.0f;

    game->x[1] = cos(t + 4);
    game->z[1] = sin(t + 4) + 5.0f;

    game->x[2] = cos(t);
    game->z[2] = sin(t) + 5.0f;
}

void initialize_game(Game_State *game) {

    game->x[0] = 0.0f; game->y[0] = 1.0f; game->z[0] = 3.0f;
    game->r[0] = 1.0f; game->g[0] = 0.0f; game->b[0] = 0.0f;

    game->x[1] = -1.0f; game->y[1] = -1.0f; game->z[1] = 3.0f;
    game->r[1] = 0.0f; game->g[1] = 1.0f; game->b[1] = 0.0f;

    game->x[2] = 1.0f; game->y[2] = -1.0f; game->z[2] = 3.0f;
    game->r[2] = 0.0f; game->g[2] = 0.0f; game->b[2] = 1.0f;
}
