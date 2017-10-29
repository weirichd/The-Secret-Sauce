#ifndef GAME_H
#define GAME_H

typedef struct Game_State {

    float x[3];
    float y[3];
    float z[3];

    float r[3];
    float g[3];
    float b[3];
} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
