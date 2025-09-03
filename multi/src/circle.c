#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 640;
static const int screenHeight = 480;
static Vector2 ball = {0,0};
static float ballAngle = 90.0f;
static float ballSpeed = 5.f; // 5
static int ballRad = 15;
static float radius = 130.0f;
static float randomAngle = 180;
static Vector2 targetCenter;
static int targetRad = 70;
static int clockwise = 1;
static int score = 0;
static int highScore = 0;

static Texture2D ballTex;
static Texture2D targetZone;
static Texture2D target;
static Texture2D mask;

void CircleInput(void){
    if(gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Circle"));
        SetWindowSize(screenWidth,screenHeight);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        HideCursor();
        gameFirstFrame = false;
        targetZone = LoadTexture("./assets/circle/targetarea.png");
        target = LoadTexture("./assets/circle/target.png");
        ballTex = LoadTexture("./assets/circle/ball.png");
        mask = LoadTexture("./assets/circle/mask.png");
        score = 0;
    }
    
}

void CircleUpdate(void){
    if (IsKeyPressed(KEY_SPACE)){
        if (CheckCollisionCircles(ball, ballRad, targetCenter, targetRad)){
            randomAngle = GetRandomValue(0, 359);
            clockwise = -clockwise;
            ballSpeed += 0.02f;
            score++;
        }
        else{
            randomAngle = GetRandomValue(0, 359);
            clockwise = -clockwise;
            ballSpeed = 5;
            if ( score > highScore ) highScore = score;
            score = 0;
        }
    }
    
    ballAngle += ballSpeed * clockwise;
}

void CircleDraw(void){

    ball.x = (screenWidth / 2) + (cos(ballAngle * (PI / 180)) * radius);
    ball.y = (screenHeight / 2) + (sin(ballAngle * (PI / 180)) * radius);
    targetCenter.x = (screenWidth / 2) + (cos(randomAngle * (PI / 180)) * radius);
    targetCenter.y = (screenHeight / 2) + (sin(randomAngle * (PI / 180)) * radius);

    BeginDrawing();
        ClearBackground(WHITE);

        DrawCircle(targetCenter.x,targetCenter.y, targetRad, RED);
        DrawTexture(target,0,0,WHITE);
        DrawTexture(ballTex,ball.x - ballRad,ball.y - ballRad, WHITE);
        DrawTexture(mask,0,0, WHITE);

        DrawText(TextFormat("%d", score), 20,20,60,BLACK);
        DrawText(TextFormat("%d", highScore), 20,100,20,BLACK);
    EndDrawing();

    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}