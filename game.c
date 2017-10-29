#include <stdlib.h>
#include <time.h>

#include "game.h"

void update(Game_State *game) {

    for(int i = 0; i < STAR_LEN; i++) {
        game->stars_z[i] -= 0.1;

        if(game->stars_z[i] < 0.0f) {
            game->stars_x[i] = (float)rand()/(float)(RAND_MAX) * 20.0f - 10.0f;
            game->stars_y[i] = (float)rand()/(float)(RAND_MAX) * 20.0f - 10.0f;
            game->stars_z[i] = 25.00;
        }
    }
}

void initialize_game(Game_State *game) {

    int seed = time(NULL);
    srand(seed);

    // Set each x and y to between -10 and 10, set z to between 0 and 25
    for(int i = 0; i < STAR_LEN; i++) {
        game->stars_x[i] = (float)rand()/(float)(RAND_MAX) * 20.0f - 10.0f;
        game->stars_y[i] = (float)rand()/(float)(RAND_MAX) * 20.0f - 10.0f;
        game->stars_z[i] = (float)rand()/(float)(RAND_MAX) * 25.0f;
        game->stars_col[i] = rand() | 0xFF;
    }
}
