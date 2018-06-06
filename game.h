#ifndef GAME_H
#define GAME_H

#include "matrix.h"

typedef struct Controller {
    int up;
    int down;
    int left;
    int right;
} Controller;

typedef struct Game_State {
    Vector3f v[3];
    Vector3f c[3];

    Matrix3x3f camera_rot;
    Vector3f camera_pos;

    Controller controller;

    int fps;
} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
