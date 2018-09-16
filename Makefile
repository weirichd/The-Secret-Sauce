sauce: main.o render.o game.o upscale.o mesh.o objloader.o
	gcc -O3 -o $@ $^ `pkg-config --libs --cflags sdl2`

%.o: %.c %.h
	gcc -O3 -c -o $@ $<

render.o: font.h

objloader.o: mesh.h

clean:
	rm *.o sauce
