#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include "../molten/include/molten.h"

const int screenWidth = 10;
const int screenHeight = 10;
bool gameFirstFrame = true;
void GameSwitcher(void);

extern void MenuInput(), MenuUpdate(), MenuDraw();
extern void PongInput(), PongUpdate(), PongDraw();
extern void FruitClickerInput(), FruitClickerUpdate(), FruitClickerDraw();
extern void DigiPetInput(), DigiPetUpdate(), DigiPetDraw();
extern void CircleInput(), CircleUpdate(), CircleDraw();
extern void TicInput(), TicUpdate(), TicDraw();

MiniGame games[] = {
    {MenuInput, MenuUpdate, MenuDraw, "Menu"},
    {PongInput,PongUpdate,PongDraw, "Pong"},
    {FruitClickerInput, FruitClickerUpdate, FruitClickerDraw, "Fruit Clicker"},
    {DigiPetInput, DigiPetUpdate, DigiPetDraw, "Digi Pet"},
    {CircleInput, CircleUpdate, CircleDraw, "Circle"},
    {TicInput, TicUpdate, TicDraw, "Tic-Tac-Toe"}
};
MiniGame CurrentGame;
bool switchGame = true;
int selection = 5;
int gameCount = sizeof(games) / sizeof(games[0]);

int main(void){
    InitWindow(screenWidth, screenHeight, "Multi");
    SetTargetFPS(60);
    GameSwitcher();

    while (!WindowShouldClose()){
        if (switchGame) GameSwitcher();
        CurrentGame.Input();
        CurrentGame.Update();
        CurrentGame.Draw();
    }
    CloseWindow();
    return 0;
}

void GameSwitcher(void){
    if (selection >= 0 && selection < gameCount){
        CurrentGame = games[selection];
        switchGame = false;
    }
}
