#include <stdlib.h>

#include "game.h"

void update(Game_State *game) {

    for(int i = 0; i < STAR_LEN; i++) {
        game->stars_z[i] -= 0.06;

        if(game->stars_z[i] < 0.0f) {
            game->stars_z[i] = 25.00;
        }
    }
}

void initialize_game(Game_State *game) {

    // Set each x and y to between -10 and 10, set z to between 0 and 25
    for(int i = 0; i < STAR_LEN; i++) {
        game->stars_x[i] = (float)rand()/(float)(RAND_MAX) * 20.0f - 10.0f;
        game->stars_y[i] = (float)rand()/(float)(RAND_MAX) * 20.0f - 10.0f;
        game->stars_z[i] = (float)rand()/(float)(RAND_MAX) * 25.0f;
    }

}
