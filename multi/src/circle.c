#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static const int screenWidth = 640;
static const int screenHeight = 480;

static float rotation = 90.0f;
static float radius = 130.0f;
static Vector2 ball = {0,0};
static float randomAngle = 180;
static Vector2 targetCenter;
static int targetRad = 70;
static int clockwise = 1;
static float ballSpeed = 4.f; // 5
static Texture2D targetZone;
static Texture2D target;
static Texture2D ballTex;
static int score = 0;
static int highScore = 0;

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
        score = 0;
    }
    
}

void CircleUpdate(void){
    if (IsKeyPressed(KEY_SPACE)){
        if (CheckCollisionCircles(ball, 15, targetCenter, targetRad)){
            randomAngle = GetRandomValue(0, 359);
            clockwise = -clockwise;
            ballSpeed += 0.02f;
            score++;
        }
        else{
            randomAngle = GetRandomValue(0, 359);
            clockwise = -clockwise;
            ballSpeed = 4;
            if ( score > highScore ) highScore = score;
            score = 0;
        }
    }
    
    rotation += ballSpeed * clockwise;
}

void CircleDraw(void){
    BeginDrawing();
        ClearBackground(WHITE);

        //DrawCircle(screenWidth / 2, screenHeight / 2, 10, GREEN);
        ball.x = (screenWidth / 2) + (cos(rotation * (PI / 180)) * radius);
        ball.y = (screenHeight / 2) + (sin(rotation * (PI / 180)) * radius);

        targetCenter.x = (screenWidth / 2) + (cos(randomAngle * (PI / 180)) * radius);
        targetCenter.y = (screenHeight / 2) + (sin(randomAngle * (PI / 180)) * radius);

        //DrawCircle(targetCenter.x,targetCenter.y, targetRad, RED);
        //DrawTexture(targetZone, 0,0,WHITE);
        //DrawTexturePro(targetZone, (Rectangle){0,0,640,480}, (Rectangle){320,240,640,480}, (Vector2){320.f,240.f}, randomAngle, WHITE);
        DrawTexture(target,0,0,WHITE);
        //DrawCircle(screenWidth / 2,screenHeight / 2 , 175, BLACK);
        //DrawCircle(screenWidth / 2,screenHeight / 2 , radius + 15 + 5, WHITE);
        DrawCircle(targetCenter.x,targetCenter.y, targetRad, RED);
        DrawTexture(target,0,0,WHITE);
        //DrawCircle(screenWidth / 2,screenHeight / 2 , radius - 15 - 5, BLACK);
        //DrawCircle(ball.x, ball.y, 15, RED);
        DrawTexture(ballTex,ball.x - 15,ball.y - 15, WHITE);
        //DrawText(TextFormat("X:%f", cos(rotation * (PI / 180) ) ), 20,20, 20, RED);
        //DrawText(TextFormat("Y:%f", sin(rotation * (PI / 180) ) ), 20,60, 20, RED);
        DrawText(TextFormat("%d", score), 20,20,60,BLACK);
        DrawText(TextFormat("%d", highScore), 20,100,20,BLACK);
    EndDrawing();
    if (IsKeyPressed(KEY_M)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 0;
    } 
}