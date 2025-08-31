#include <stdio.h>
#include <raylib.h>
#include <math.h>

const int screenWidth = 10;
const int screenHeight = 10;
bool gameFirstFrame = true;
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
extern void DigiPetInput(), DigiPetUpdate(), DigiPetDraw();

Game games[] = {
    {FruitClickerInput, FruitClickerUpdate, FruitClickerDraw, "Fruit Clicker"},
    {DigiPetInput, DigiPetUpdate, DigiPetDraw, "Digi Pet"}};
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
