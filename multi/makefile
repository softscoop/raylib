lin: a.out
	./a.out

a.out: main.c
	gcc main.c -I/home/jack/Documents/Raylib/include/ -L/home/jack/Documents/Raylib/lib -L/usr/local/lib -lraylib -lGL -lm -ldl -lpthread -ldl -lrt -lX11 -I/home/jack/dev/raylib/molten/include -L/home/jack/dev/raylib/molten/src ../molten/src/timer.c ./src/digipet.c ./src/fruitclicker.c ./src/menu.c ./src/pong.c -lm

win: a.exe
	
a.exe: main.c ./src/fruitclicker.c ./src/digipet.c ./src/menu.c ./src/pong.c
	gcc -fdiagnostics-color=always -g main.c -IC:/Raylib/include -LC:/Raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -std=c99 -LC:\Users\Jack\dev\raylib\molten\src C:\Users\Jacka\dev\raylib\molten\src\timer.c C:\Users\Jacka\dev\raylib\multi\src\fruitclicker.c C:\Users\Jacka\dev\raylib\multi\src\digipet.c C:\Users\Jacka\dev\raylib\multi\src\menu.c C:\Users\Jacka\dev\raylib\multi\src\pong.c
