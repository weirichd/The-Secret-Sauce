#ifndef GAME_H
#define GAME_H

#define STAR_LEN 1500

typedef struct Game_State {

    float stars_x[STAR_LEN];
    float stars_y[STAR_LEN];
    float stars_z[STAR_LEN];
    unsigned int stars_col[STAR_LEN];

} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
