#include <stdio.h>
#include <raylib.h>
#include <math.h>

const int screenWidth = 640;
const int screenHeight = 480;

void GameSwitcher(void);

typedef void (*Input)(void);
typedef void (*Update)(void);
typedef void (*Draw)(void);

typedef struct Game{
    Input Input;
    Update Update;
    Draw Draw;
    char* name; 
} Game;

extern void FruitClickerInput(), FruitClickerUpdate(), FruitClickerDraw();
extern void TestGame2Input(), TestGame2Update(), TestGame2Draw();

Game games[] = {
    {FruitClickerInput, FruitClickerUpdate, FruitClickerDraw, "Fruit Clicker"},
    {TestGame2Input, TestGame2Update, TestGame2Draw, "TestGame2"}};
Game CurrentGame;
bool switchGame = true;
int selection = 0;
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