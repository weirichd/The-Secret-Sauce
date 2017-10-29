#ifndef GAME_H
#define GAME_H

// TODO: Don't keep this here.
typedef struct Vertex {
    float x, y, z, r, g, b;
} Vertex;

typedef struct Game_State {
    Vertex v[4];
} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
