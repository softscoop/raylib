#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

#define SPRITE_SIZE 64

extern bool switchGame;
extern int selection;
static int screenWidth = 640;
static int screenHeight = 480;

static Vector2 mousePos = {-40,-40};
static Vector2 fruitPos;
static int score = 0;
static int highscore = 0;
static int randFruitPick = 0;
static Timer playTimer;
static bool gameFirstFrame = true;
static Texture2D background;
static Texture2D mouseSprite;
static Texture2D fruitSprites[7];

void FruitClickerInput(void){
    if (IsKeyPressed(KEY_P)){
        switchGame = true;
        selection = 1;
    } 
    if (gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Fruit Clicker"));
        SetWindowSize(640,480);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        HideCursor();
        Vector2 fruitPos = {GetRandomValue(0, (screenWidth - 1) - SPRITE_SIZE),
        GetRandomValue(0, (screenHeight - 1) - SPRITE_SIZE)};
        background = LoadTexture("./assets/fruitclicker/backgrounds/background.png");
        mouseSprite = LoadTexture("./assets/fruitclicker/mouse.png");
        fruitSprites[0] = LoadTexture("./assets/fruitclicker/sprites/apple.png");
        fruitSprites[1] = LoadTexture("./assets/fruitclicker/sprites/blueberry.png");
        fruitSprites[2] = LoadTexture("./assets/fruitclicker/sprites/cherry.png");
        fruitSprites[3] = LoadTexture("./assets/fruitclicker/sprites/grapes.png");
        fruitSprites[4] = LoadTexture("./assets/fruitclicker/sprites/lemon.png");
        fruitSprites[5] = LoadTexture("./assets/fruitclicker/sprites/melon.png");
        fruitSprites[6] = LoadTexture("./assets/fruitclicker/sprites/strawberry.png");
        TimerStart(&playTimer);
        gameFirstFrame = false;
    }
    return;
}

void FruitClickerUpdate(void){
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
    return;
}

void FruitClickerDraw(void){
    BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleV(fruitPos,(Vector2){64,64}, RED);
        DrawTexture(background,0,0,WHITE);
        DrawTexture(fruitSprites[randFruitPick], fruitPos.x,fruitPos.y,WHITE);
        DrawText(TextFormat("Score: %d/%d", score, highscore), 10,10,30, BLACK);
        DrawTexture(mouseSprite,GetMousePosition().x, GetMousePosition().y, WHITE);
    EndDrawing();
    return;
}