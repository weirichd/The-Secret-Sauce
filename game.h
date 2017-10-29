#ifndef GAME_H
#define GAME_H

typedef struct Game_State {

    float stars_x[3];
    float stars_y[3];
    float stars_z[3];
    unsigned int stars_col[3];

} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
