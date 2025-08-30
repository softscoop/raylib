run: a.out
	./a.out

a.out: main.c
	gcc main.c -I/home/jack/Documents/Raylib/include/ -L/home/jack/Documents/Raylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

win: a.exe
	
a.exe: main.c
	gcc -fdiagnostics-color=always -g main.c -IC:/Raylib/include -LC:/Raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -std=c99