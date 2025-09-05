#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 480;
static const int screenHeight = 360;
static const Vector2 centerPoint = {screenWidth / 2, screenHeight / 2};
static const int centerX = 240 - 40;
static const int centerY = 180 - 40;
static bool player1 = true;
static Font myFont;

static Texture2D background;
static char choices[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
static Rectangle gridBoxes[3][3] = {
    {{centerX - 104,centerY - 104,80,80}, {centerX,centerY - 104,80,80}, {centerX + 104,centerY - 104,80,80}},
    {{centerX - 104,centerY,80,80}, {centerX,centerY,80,80}, {centerX + 104,centerY,80,80}},
    {{centerX - 104,centerY + 104,80,80}, {centerX,centerY + 104,80,80}, {centerX + 104,centerY + 104,80,80}} };

void TicInput(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Tic-Tac-Toe"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        //HideCursor();
        background = LoadTexture("./assets/tictactoe/backgrounds/map.png");
        myFont = LoadFontEx("./assets/tictactoe/fonts/Edges.ttf", 80, NULL,0);
        gameFirstFrame = false;
    }

    if (IsKeyPressed(KEY_R)){
        for (int i = 0; i < 3; i++){
            for (int e = 0; e < 3; e++){
                choices[i][e] = ' ';
                player1 = true;
            }
        }
    }
    
}

void TicUpdate(void){

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        for (int i = 0; i < 3; i++){
            for (int e = 0; e < 3; e++){
                if (CheckCollisionPointRec(GetMousePosition(), gridBoxes[i][e])){
                    if (choices[i][e] == ' '){
                        if (player1 && (choices[i][e] != 'X' || choices[i][e] != 'X')){
                            choices[i][e] = 'X';
                            player1 = !player1;
                        }
                        else if (!player1 && (choices[i][e] != 'X' || choices[i][e] != 'X')){
                            choices[i][e] = 'O';
                            player1 = !player1;
                        }
                    }
                }
            }
        }
    }
}

void TicDraw(void){
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0,0, WHITE);
        for (int i = 0; i < 3; i++){
            for (int e = 0; e < 3; e++){
                if (choices[i][e] == 'X') DrawTextEx(myFont, TextFormat("%c", choices[i][e]), (Vector2){gridBoxes[i][e].x + 5, gridBoxes[i][e].y},
                80,0,BLACK);
                else DrawTextEx(myFont, TextFormat("%c", choices[i][e]), (Vector2){gridBoxes[i][e].x + 5, gridBoxes[i][e].y},
                80,0, BLACK);
            }
        }
    EndDrawing();

    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}