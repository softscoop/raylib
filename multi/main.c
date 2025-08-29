#include <stdio.h>
#include "raylib.h"
#include <math.h>

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

extern void TestGame1Input(), TestGame1Update(), TestGame1Draw();
extern void TestGame2Input(), TestGame2Update(), TestGame2Draw();

Game games[] = {
    {TestGame1Input, TestGame1Update, TestGame1Draw, "TestGame1"},
    {TestGame2Input, TestGame2Update, TestGame2Draw, "TestGame2"}};
Game CurrentGame;
bool switchGame = true;
int selection = 0;
int gameCount = sizeof(games) / sizeof(games[0]);

int main(void){
    const int screenWidth = 640;
    const int screenHeight = 480;
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