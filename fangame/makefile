run: a.out
	./a.out

a.out: main.c
	gcc main.c -I/home/jack/Documents/Raylib/include/ -L/home/jack/Documents/Raylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

win: a.exe
	
a.exe: main.cpp
	g++ main.cpp -IC:/Raylib/include -LC:/Raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -static-libstdc++ -static-libgcc -static ./src/leveldata.cpp ./src/player.cpp ./src/world.cpp