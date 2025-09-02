#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
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
static int paddleSpeed = 7;
static int ballSpeed = 2;
static int ballRadius = 20;
static bool allowCollision = true;
static Vector2 prevBallPos[10];
static int prevBallPosSize = sizeof(prevBallPos) / sizeof(prevBallPos[0]);

void PongInput(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Pong"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        int ballAngle = GetRandomValue(135, 225);
        ballVector.y = sin(ballAngle * (PI / 180));
        HideCursor();
        gameFirstFrame = false;
    }

    if (IsKeyDown(KEY_W)) playerPaddle.y -= paddleSpeed; 
    if (IsKeyDown(KEY_S)) playerPaddle.y += paddleSpeed; 
    if (IsKeyPressed(KEY_O)) ballSpeed++; 
    if (IsKeyPressed(KEY_I)) ballSpeed--; 
    
}

void PongUpdate(void){
    ball.x += ballVector.x * ballSpeed;
    ball.y += ballVector.y * ballSpeed;
    if (prevBallPos[prevBallPosSize -1].y > cpuPaddle.y + 50) cpuPaddle.y += paddleSpeed;
    else if (prevBallPos[prevBallPosSize -1].y < cpuPaddle.y + 50) cpuPaddle.y -= paddleSpeed;

    if (playerPaddle.y < 0) playerPaddle.y = 0;
    if (playerPaddle.y >= screenHeight - 100) playerPaddle.y = screenHeight - 100;

    if (cpuPaddle.y < 0) cpuPaddle.y = 0;
    if (cpuPaddle.y >= screenHeight - 100) cpuPaddle.y = screenHeight - 100;

    if ((CheckCollisionCircleRec(ball,ballRadius,(Rectangle){playerPaddle.x,playerPaddle.y,20,100}) ||
        CheckCollisionCircleRec(ball,ballRadius,(Rectangle){cpuPaddle.x,cpuPaddle.y,20,100}))
        && allowCollision == true){            
        ballVector.x = -ballVector.x;
        //ballVector.y = -ballVector.y;
        allowCollision = false;
    }
    if (ball.x >= screenWidth - ballRadius) ballVector.x = -ballVector.x;
    if (ball.x < 0 + ballRadius) ballVector.x = -ballVector.x;
    if (ball.y >= screenHeight - ballRadius) ballVector.y = -ballVector.y;
    if (ball.y < 0 + ballRadius) ballVector.y = -ballVector.y;

    if (ball.x >= 100 && ball.y < screenWidth - 100) allowCollision = true;
    //shuffle array and add final position
    for (int i = (sizeof(prevBallPos) / sizeof(prevBallPos[0]) - 2); i >= 0; i--){
        prevBallPos[i+1] = prevBallPos[i];
    }
    prevBallPos[0] = ball;
}

void PongDraw(void){
    BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(playerPaddle.x,playerPaddle.y,20, 100, RED);
        DrawRectangle(cpuPaddle.x,cpuPaddle.y,20, 100, RED);
        DrawCircle(ball.x,ball.y,ballRadius,RED);
        DrawLine(ball.x,ball.y, prevBallPos[prevBallPosSize - 1].x, prevBallPos[prevBallPosSize -1].y, GREEN);
        DrawCircle(prevBallPos[prevBallPosSize - 1].x,prevBallPos[prevBallPosSize -1].y,ballRadius,BLUE);
    EndDrawing();
    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}