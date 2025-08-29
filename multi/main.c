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

Game CurrentGame;
bool switchGame = true;
int selection = 0;

int main(void){
    const int screenWidth = 640;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "Multi");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        if (switchGame) GameSwitcher();
        //debug function
        if (IsKeyPressed(KEY_Q)){
            selection -= 1;
            switchGame = true;
        }
        else if (IsKeyPressed(KEY_W)){
            selection += 1;
            switchGame = true;
        }
        CurrentGame.Input();
        CurrentGame.Update();
        CurrentGame.Draw();
    }
    CloseWindow();
    return 0;
}

extern void TestGame1Input();
extern void TestGame1Update();
extern void TestGame1Draw();

extern void TestGame2Input();
extern void TestGame2Update();
extern void TestGame2Draw();

void GameSwitcher(void){
    switch (selection){
        case 0:
            CurrentGame.Input = TestGame1Input;
            CurrentGame.Update = TestGame1Update;
            CurrentGame.Draw = TestGame1Draw;
            switchGame = false;
            break;
        case 1:
            CurrentGame.Input = TestGame2Input;
            CurrentGame.Update = TestGame2Update;
            CurrentGame.Draw = TestGame2Draw;
            switchGame = false;
            break;
        default:
            break;
    }
}