#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;
extern MiniGame games[];

static int screenWidth = 500;
static int screenHeight = 500;

void MenuInput(void){
    if (gameFirstFrame){
        printf("%s", games[0].name);
        SetWindowTitle(TextFormat("%s", "Menu"));
        SetWindowSize(500,500);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        gameFirstFrame = false;
    }
}

void MenuUpdate(void){
}

void MenuDraw(void){
    BeginDrawing();
        DrawRectangle(2,3,32,32,RED);
    EndDrawing();
}
