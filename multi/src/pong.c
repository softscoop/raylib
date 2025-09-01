#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 640;
static const int screenHeight = 480;
static Vector2 ball = {screenWidth / 2, screenHeight / 2};
static Vector2 ballVector = {-1,0};
static Vector2 playerPaddle = {20,20};
static Vector2 cpuPaddle = {(screenWidth - 20) - 20,20};
static int paddleSpeed = 5;
static int ballSpeed = 5;

void PongInput(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Pong"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        HideCursor();
    }

    if (IsKeyDown(KEY_W)) playerPaddle.y -= paddleSpeed; 
    if (IsKeyDown(KEY_S)) playerPaddle.y += paddleSpeed; 
    
}

void PongUpdate(void){
    ball.x += ballVector.x * ballSpeed;
    ball.y += ballVector.y * ballSpeed;

    if (CheckCollisionCircleRec(ball,10.0f,(Rectangle){playerPaddle.x,playerPaddle.y,20,100})){
        ballVector.x = -ballVector.x;
        ballVector.y = -ballVector.y;
    }
}

void PongDraw(void){
    BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(playerPaddle.x,playerPaddle.y,20, 100, RED);
        DrawRectangle(cpuPaddle.x,cpuPaddle.y,20, 100, RED);
        DrawCircle(ball.x,ball.y,10,RED);
    EndDrawing();
    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}