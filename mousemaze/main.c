#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    // Window setup
    const int screenWidth = 640;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "MouseMaze");
    SetTargetFPS(60);
    HideCursor();

    // Load images & textures
    Image collisionMap = LoadImage("./assets/colMap.png");
    Texture2D map = LoadTexture("./assets/map.png");

    // Put all the collision pixels in a color array
    Color *colors = LoadImageColors(collisionMap);
    int index;
    Color pixel;

    // No need to have collisionMap loaded in memory
    UnloadImage(collisionMap);
    
    while (!WindowShouldClose())
    {
        index = ((int)GetMousePosition().y * collisionMap.width) + (int)GetMousePosition().x;
        pixel = colors[index];

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(map,0,0,WHITE);
            DrawCircleV(GetMousePosition(),10,BLACK);
            DrawText(TextFormat("%d", pixel.r),10,10,20,BLACK);
            DrawFPS(10,50);
        EndDrawing();
    }

    // Unload assets
    UnloadTexture(map);
    //UnloadImage(collisionMap);

    CloseWindow();

    return 0;
}