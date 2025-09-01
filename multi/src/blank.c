#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 640;
static const int screenHeight = 480;
static Vector2 ball = {screenWidth / 2, screenHeight / 2};
static Vector2 playerPaddle = {0,0};

void PongInput(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Pong"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        HideCursor();
    }
    
}

void PongUpdate(void){
}

void PongDraw(void){
    BeginDrawing();
        DrawRectangle(0,0,20, 100, RED);
    EndDrawing();
    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}