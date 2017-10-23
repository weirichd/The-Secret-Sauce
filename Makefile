game: main.c
	gcc -o game main.c `pkg-config --libs --cflags sdl2`
