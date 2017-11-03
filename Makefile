game: main.c render.c game.c upscale.c numbers.c
	gcc -O3 -o $@ $^ `pkg-config --libs --cflags sdl2`
