#include <stdlib.h>
#include <math.h>

#include "game.h"

float t = 0.0f;

void update(Game_State *game) {
    t += 0.007f;

    game->stars_x[0] = cos(t + 2);
    game->stars_z[0] = sin(t + 2) + 5.0f;

    game->stars_x[1] = cos(t + 4);
    game->stars_z[1] = sin(t + 4) + 5.0f;

    game->stars_x[2] = cos(t);
    game->stars_z[2] = sin(t) + 5.0f;
}

void initialize_game(Game_State *game) {

    game->stars_x[0] = 0.0f;
    game->stars_y[0] = 1.0f;
    game->stars_z[0] = 3.0f;

    game->stars_x[1] = -1.0f;
    game->stars_y[1] = -1.0f;
    game->stars_z[1] = 3.0f;

    game->stars_x[2] = 1.0f;
    game->stars_y[2] = -1.0f;
    game->stars_z[2] = 3.0f;
}
