game: main.c render.c game.c upscale.c
	gcc -O3 -o $@ $^ `pkg-config --libs --cflags sdl2`
