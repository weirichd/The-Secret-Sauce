game: main.c render.c game.c
	gcc -o $@ $^ `pkg-config --libs --cflags sdl2`
