#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


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
        ShowCursor();
    }
}

void MenuUpdate(void){
}

void MenuDraw(void){
    BeginDrawing();
        ClearBackground(WHITE);
        if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "Fruit Clicker")){
            switchGame = true;
            selection = 1;
            gameFirstFrame = true;
        }
        if (GuiButton((Rectangle){ 24, 70, 120, 30 }, "Digi Pet")){
            switchGame = true;
            selection = 2;
            gameFirstFrame = true;
        }
    EndDrawing();
}
