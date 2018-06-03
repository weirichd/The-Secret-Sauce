#ifndef GAME_H
#define GAME_H

#include "matrix.h"

typedef struct Game_State {
    Vector3f v[3];
    int fps;
} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
