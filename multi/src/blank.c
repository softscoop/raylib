#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 640;
static const int screenHeight = 480;

void Input(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Name"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        HideCursor();
    }
    
}

void Update(void){
}

void Draw(void){
    BeginDrawing();
        DrawRectangle(0,0,20, 100, RED);
    EndDrawing();
    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}