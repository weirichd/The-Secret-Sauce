game: main.c render.c
	gcc -o game main.c render.c `pkg-config --libs --cflags sdl2`
