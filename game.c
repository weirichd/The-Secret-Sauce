#include <stdlib.h>
#include <math.h>

#include "matrix.h"

#include "game.h"

float p = 3.14159f;

float t = 0.0f;

void update(Game_State *game) {
     t += 0.017f;

    game->v[0].x = 0;
    game->v[0].z = 5.0f;

    game->v[1].x = cos(t + p);
    game->v[1].z = sin(t + p) + 5.0f;

    game->v[2].x = cos(t);
    game->v[2].z = sin(t) + 5.0f;

    if(t > 2 * p) t -= 2 * p;
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
