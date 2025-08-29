#include <stdio.h>
#include <raylib.h>

static Vector2 player = {10,10};
extern bool switchGame;
extern int selection;

void TestGame2Input(void){
    if (IsKeyDown(KEY_A)) player.x -= 1;
    if (IsKeyDown(KEY_D)) player.x += 1;
    //printf("input");
    if (IsKeyPressed(KEY_Q)){
            selection -= 1;
            switchGame = true;
        }
        else if (IsKeyPressed(KEY_W)){
            selection += 1;
            switchGame = true;
        }
}

void TestGame2Update(void){
    //printf("update");
}

void TestGame2Draw(void){
    BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(player.x,player.y,32,32,PINK);
    EndDrawing();
}