lin:
	gcc main.c -o mousemaze-lin -I/home/jack/Documents/Raylib/include/ -L/home/jack/Documents/Raylib//lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./mousemaze-lin

win:
	gcc main.c -o mousemaze-win.exe -IC:\Raylib\include -LC:\Raylib\lib -lraylib  -lraylib -lopengl32 -lgdi32 -lwinmm -std=c99

mac:
	gcc -o mousemaze-mac main.c -framework IOKit -framework Cocoa -framework OpenGL -lraylib -std=c99 -Wall && ./mousemaze-mac