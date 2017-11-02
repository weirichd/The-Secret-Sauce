#ifndef GAME_H
#define GAME_H

// TODO: Don't keep this here.
typedef struct Vertex {
    float x, y, z, r, g, b;
} Vertex;

typedef struct Vertex2Di {
    int x, y;
    unsigned char r, g, b;
} Vertex2Di;

typedef struct Game_State {
    Vertex v[3];
} Game_State;

void initialize_game(Game_State *game);
void update(Game_State *game);

#endif
