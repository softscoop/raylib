#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "..\molten\include\molten.h"

#define SPRITE_SIZE 64

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "Fruit Clicker");
    SetTargetFPS(60);
    HideCursor();
    Vector2 mousePos = {-40,-40};
    Vector2 fruitPos = {GetRandomValue(0, (screenWidth - 1) - SPRITE_SIZE),
        GetRandomValue(0, (screenHeight - 1) - SPRITE_SIZE)};
    int score = 0;
    int highscore = 0;
    int randFruitPick = 0;
    Timer playTimer;
    bool gameFirstFrame = true;
    Texture2D background = LoadTexture("./assets/backgrounds/background.png");
    Texture2D mouseSprite = LoadTexture("./assets/mouse.png");
    Texture2D fruitSprites[] = {
        LoadTexture("./assets/sprites/apple.png"),
        LoadTexture("./assets/sprites/blueberry.png"),
        LoadTexture("./assets/sprites/cherry.png"),
        LoadTexture("./assets/sprites/grapes.png"),
        LoadTexture("./assets/sprites/lemon.png"),
        LoadTexture("./assets/sprites/melon.png"),
        LoadTexture("./assets/sprites/strawberry.png")};
    
    FILE *fptr;
    fptr = fopen("save.txt", "r");
    char scoreString[100];
    fgets(scoreString, 100, fptr);
    highscore = atoi(scoreString);
    printf("%s", scoreString);
    fclose(fptr);

    while (!WindowShouldClose()){

        if (gameFirstFrame){
            TimerStart(&playTimer);
            gameFirstFrame = false;
        } 

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){fruitPos.x,fruitPos.y,SPRITE_SIZE,SPRITE_SIZE})){
                score += 1;
                randFruitPick = GetRandomValue(0, 7-1);
                fruitPos.x = GetRandomValue(0, screenWidth - SPRITE_SIZE);
                fruitPos.y = GetRandomValue(0, screenHeight - SPRITE_SIZE);
            }
        }

        if (TimerTime(playTimer) >= 10){
            if (score > highscore) highscore = score;
            score = 0;
            TimerStart(&playTimer);
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleV(fruitPos,(Vector2){64,64}, RED);
            DrawTexture(background,0,0,WHITE);
            DrawTexture(fruitSprites[randFruitPick], fruitPos.x,fruitPos.y,WHITE);
            DrawText(TextFormat("Score: %d/%d", score, highscore), 10,10,30, BLACK);
            DrawTexture(mouseSprite,GetMousePosition().x, GetMousePosition().y, WHITE);
        EndDrawing();
    }
    fptr = fopen("save.txt", "w");
    fprintf(fptr, TextFormat("%d", highscore));
    fclose(fptr);
    CloseWindow();

    return 0;
}