#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 480;
static const int screenHeight = 360;

static Texture2D background;

void TicInput(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Tic-Tac-Toe"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        //HideCursor();
        background = LoadTexture("./assets/tictactoe/backgrounds/map.png");
        gameFirstFrame = false;
    }
    
}

void TicUpdate(void){
}

void TicDraw(void){
    BeginDrawing();
        DrawTexture(background, 0,0, WHITE);
    EndDrawing();
    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}
