game: main.c render.c game.c upscale.c graphics.c
	gcc -o $@ $^ `pkg-config --libs --cflags sdl2`
