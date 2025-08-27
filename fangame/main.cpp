#include <iostream>

extern "C" {
    #include <raylib.h>
    //#include <raymath.h>    
}
#include "./include/player.hpp"
#include "./include/boss.hpp"
#include "./include/world.hpp"
//#define DEBUG

enum keyLayout{
    WASD,
    CLASSIC
};

enum gameState{
    TITLE,
    MENU,
    OPTIONS,
    GAME
};

void debugKeys();
void debugDraw();
void SetKeys(keyLayout layout);
void switchKeys();
void WindowSize();
bool classicControls;

extern Player player;
extern Level level;
extern Boss testBoss;
extern Bullet bullet;
extern std::vector<Bullet> bullets;

const int gameWidth = 800;
const int gameHeight = 608;

void DrawMenu(Texture2D &menu, RenderTexture2D &renderTexture);
void PlayGame(RenderTexture2D &renderTexture);
gameState state = MENU;
bool menuQuit = false;
bool paused = false;
const char* title = "IWBT Christmas Demo";
Input input;
Timer gameTime;
Timer titleUpdateTimer;

int main(){
    //Raylib Init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(gameWidth, gameHeight, title);
    SetTargetFPS(50);
    InitAudioDevice();
    const char* appDir = GetApplicationDirectory();
    ChangeDirectory(appDir);
    Image icon = LoadImage("./assets/icon.png");
    SetWindowIcon(icon);
    RenderTexture2D gameRenderTexture = LoadRenderTexture(gameWidth, gameHeight);
    SetTextureFilter(gameRenderTexture.texture, TEXTURE_FILTER_POINT);
    
    //World & Player Init
    player.Init();
    level.Init();
    testBoss.Init();
    Texture2D sprMenu = LoadTexture("./assets/menu/menu.png");
    Music music = LoadMusicStream("./assets/music/calm-christmas-piano-262888.mp3");
    SetMusicVolume(music, 0.4f);
    PlayMusicStream(music);
    SetMasterVolume(0.1f);
    classicControls = true;
    SetKeys(keyLayout::WASD);
    gameTime.Start();
    titleUpdateTimer.Start();

    while (!WindowShouldClose()){
        UpdateMusicStream(music);
        if (IsKeyPressed(KEY_F)){
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            ToggleFullscreen();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        }

        if (state == MENU){
            DrawMenu(sprMenu, gameRenderTexture);
        }
        else if (state == GAME){
            PlayGame(gameRenderTexture);
        };
        if (menuQuit == true){
            CloseWindow();
            return 0;
        }
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void DrawMenu(Texture2D &menu, RenderTexture2D &renderTexture){
    static Texture2D sprButtonPlay = LoadTexture("./assets/menu/buttonPlay.png");
    static Texture2D sprButtonPlayHover = LoadTexture("./assets/menu/buttonPlay-hover.png");
    static Texture2D sprButtonQuit = LoadTexture("./assets/menu/buttonQuit.png");
    static Texture2D sprButtonQuitHover = LoadTexture("./assets/menu/buttonQuit-hover.png");
    static Rectangle playButtonRect = {((float)gameWidth / 2.0f) - ((float)sprButtonPlay.width / 2.0f),(float)gameHeight / 2.0f,(float)sprButtonPlay.width,(float)sprButtonPlay.height};
    static Rectangle quitButtonRect = {((float)gameWidth / 2.0f) - ((float)sprButtonQuit.width / 2.0f),(float)gameHeight / 2.0f + 70.0f,(float)sprButtonQuit.width,(float)sprButtonQuit.height};
    //WindowSize();
    BeginTextureMode(renderTexture);
        ClearBackground(BLACK);
        DrawTexture(menu,0,0,WHITE);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(),playButtonRect)){
            DrawTexture(sprButtonPlayHover,playButtonRect.x,playButtonRect.y,WHITE);
            state = GAME;
        }
        else if (CheckCollisionPointRec(GetMousePosition(),playButtonRect)){
            DrawTexture(sprButtonPlayHover,playButtonRect.x,playButtonRect.y,WHITE);
        }
        else{
            DrawTexture(sprButtonPlay,playButtonRect.x,playButtonRect.y,WHITE);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(),quitButtonRect)){
            DrawTexture(sprButtonQuitHover,quitButtonRect.x,quitButtonRect.y,WHITE);
            menuQuit = true;
        }
        else if (CheckCollisionPointRec(GetMousePosition(),quitButtonRect)){
            DrawTexture(sprButtonQuitHover,quitButtonRect.x,quitButtonRect.y,WHITE);
        }
        else{
            DrawTexture(sprButtonQuit,quitButtonRect.x,quitButtonRect.y,WHITE);
        }
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);
        WindowSize();
        float ratio;

        if ((float)GetScreenWidth() / (float)GetScreenHeight() < (float)gameWidth / (float)gameHeight){
            ratio = (float)GetScreenWidth() / (float)gameWidth;
        }
        else{
            ratio = (float)GetScreenHeight() / (float)gameHeight;
        }
        float scaledGamewidth = (float)gameWidth * ratio;
        float scaledGameHeight = (float)gameHeight * ratio;
        Rectangle src = {0.0f, 0.0f, 800.0f, -608.0f};
        Rectangle dest = {((float)GetScreenWidth() - ((float)gameWidth * ratio)) / 2,
            ((float)GetScreenHeight() - ((float)gameHeight * ratio)) / 2,
            (float)gameWidth * ratio, (float)gameHeight * ratio};
        DrawTexturePro(renderTexture.texture,src, dest,{0,0}, 0.0f, WHITE);
    EndDrawing();
    return;
}

void PlayGame(RenderTexture2D &renderTexture){
    if (titleUpdateTimer.Time() >= 1){
        double stamp = gameTime.Time();
        double seconds = (int)stamp % 60;
        double minutes = (int)stamp / 60;
        double mins = (int)minutes % 60;
        double hours = (int)minutes / 60;
        SetWindowTitle(TextFormat("%s | Deaths: %d | %02.f:%02.f:%02.f", title, player.deathCount, hours, mins, seconds));
        titleUpdateTimer.Start();
    }
    static Texture2D sprWarp = LoadTexture("./assets/sprites/warp.png");
    static Texture2D sprWarpBlocked = LoadTexture("./assets/sprites/warpBlocked.png");
    static Texture2D sprSaveRed = LoadTexture("./assets/sprites/saveRed.png");
    static Texture2D sprSaveGreen = LoadTexture("./assets/sprites/saveGreen.png");
    static Texture2D sprCoin = LoadTexture("./assets/sprites/coin.png");
    if (!paused){
        level.Update();
        if (!player.dead) player.Update();

        for (auto& bullet : bullets){
            bullet.Update();
            if(CheckCollisionRecs(bullet.HitBoxRect(), testBoss.HitBoxRect())){
                testBoss.healthPoints -= 10.0f;                
            }
        }

        //testBoss.Update();
        static int i = 0;
        i = 0;
        while(i < bullets.size()){
            if(bullets[i].position.x < 0 - 4 || bullets[i].position.x > gameWidth + 4 || bullets[i].blockCol() || CheckCollisionRecs(bullets[i].HitBoxRect(),testBoss.HitBoxRect()))
                bullets.erase(bullets.begin() + i);
            else
                ++i;
        }
    }
    if (IsKeyPressed(KEY_I)){
        switchKeys();
    }
    if (IsKeyPressed(KEY_R)){
        if (!player.dead){
            player.position = player.savePosition;
        }
        else if (player.dead){
            player.dead = false;
        }
    }

    WindowSize();
    BeginTextureMode(renderTexture);
        ClearBackground(BLACK);
        level.Draw();
        static Texture2D sprDeathScreen = LoadTexture("./assets/death.png");

        for (auto& save : level.saveLocs){
            if (CheckCollisionRecs(player.HitBoxRect(), save)) DrawTexture(sprSaveGreen, save.x, save.y,WHITE);
            else DrawTexture(sprSaveRed, save.x, save.y,WHITE); 
        }
        int coinCount = level.coinLocs.size();
        for (auto& wB : level.warpLocs){
            if (player.coinsCollected != coinCount)
                DrawTexture(sprWarpBlocked, wB.x, wB.y,WHITE);
            else DrawTexture(sprWarp, wB.x, wB.y,WHITE);
        }
        for (auto& coin : level.coinLocs){
            DrawTexture(sprCoin, coin.x, coin.y,WHITE);
        }
        if (!player.dead){
            player.Draw();
        }
        else DrawTexture(sprDeathScreen,0,0,WHITE); 
        
        for (auto& bullet : bullets){
        bullet.Draw();
        }

        //testBoss.Draw();
        DrawTexture(level.water, 0, 0, WHITE);

        #ifdef DEBUG
            DrawText(TextFormat("coins collected: %d / %d", player.coinsCollected,coinCount), 0,25,20, BLACK);
            int test = bullets.size();
            DrawText(TextFormat("Bullets: %d", test), 0,50,20, BLACK);
            DrawText(TextFormat("Boss: %f", testBoss.healthPoints), 0,75,20, BLACK);
            //DrawRectangleRec(player.HitBoxRect(),PURPLE);
            debugDraw();
            if (IsKeyDown(KEY_NINE)) debugDraw();
            debugKeys();
            DrawFPS(0, 0);
        #endif
    EndTextureMode();
    BeginDrawing();
        ClearBackground(BLACK);
        WindowSize();
        float ratio;

        if ((float)GetScreenWidth() / (float)GetScreenHeight() < (float)gameWidth / (float)gameHeight){
            ratio = (float)GetScreenWidth() / (float)gameWidth;
        }
        else{
            ratio = (float)GetScreenHeight() / (float)gameHeight;
        }
        float scaledGamewidth = (float)gameWidth * ratio;
        float scaledGameHeight = (float)gameHeight * ratio;
        Rectangle src = {0.0f, 0.0f, 800.0f, -608.0f};
        Rectangle dest = {((float)GetScreenWidth() - ((float)gameWidth * ratio)) / 2,
            ((float)GetScreenHeight() - ((float)gameHeight * ratio)) / 2,
            (float)gameWidth * ratio, (float)gameHeight * ratio};
        DrawTexturePro(renderTexture.texture,src, dest,{0,0}, 0.0f, WHITE);
    EndDrawing();
    return;
}

void debugKeys()
{
    if (IsKeyPressed(KEY_F11))
        ToggleFullscreen();
    if (IsKeyPressed(KEY_ONE))
        SetTargetFPS(10);
    if (IsKeyPressed(KEY_TWO))
        SetTargetFPS(50);
    if (IsKeyPressed(KEY_THREE))
        SetTargetFPS(10000);        
    if (IsKeyPressed(KEY_P))
        paused = !paused;
    if (IsKeyPressed(KEY_MINUS)){
        level.warpTo -= 2;
        player.shouldWarp = true;
    }
    if (IsKeyPressed(KEY_EQUAL))
        player.shouldWarp = true;
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        state = MENU;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        player.position = GetMousePosition();
}

void debugDraw(){
    for (auto& s16 : level.spike16){
            DrawTriangleLines(s16.p1, s16.p2, s16.p3,BLACK);
    }
    for (auto& s32 : level.spike32){
            DrawTriangleLines(s32.p1, s32.p2, s32.p3,BLACK);
    }
    for (auto& bl : level.colBlocks){
            DrawRectangleRec(bl,BLACK);
    }
    for (auto& wB : level.warpLocs){
            DrawRectangleRec(wB,WHITE);
    }
}

void SetKeys(keyLayout layout){
    switch (layout)
    {
    case keyLayout::WASD:
        input.up = KEY_W;
        input.down = KEY_S;
        input.left = KEY_A;
        input.right = KEY_D;
        input.jump = KEY_K;
        input.shoot = KEY_J;
        classicControls = !classicControls;
        break;
     case keyLayout::CLASSIC:
        input.up = KEY_UP;
        input.down = KEY_DOWN;
        input.left = KEY_LEFT;
        input.right = KEY_RIGHT;
        input.jump = KEY_LEFT_SHIFT;
        input.shoot = KEY_Z;
        classicControls = !classicControls;
        break;
    default:
        break;
    }
}

void switchKeys(){
    if (classicControls){
            input.up = KEY_W;
            input.down = KEY_S;
            input.left = KEY_A;
            input.right = KEY_D;
            input.jump = KEY_K;
            input.shoot = KEY_J;
            classicControls = !classicControls;
        }
        else {
            input.up = KEY_UP;
            input.down = KEY_DOWN;
            input.left = KEY_LEFT;
            input.right = KEY_RIGHT;
            input.jump = KEY_LEFT_SHIFT;
            input.shoot = KEY_Z;
            classicControls = !classicControls;
        }
}

void WindowSize(){
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    if (width < gameWidth || height < gameHeight) {
        SetWindowSize(
            width < gameWidth ? gameWidth : width,
            height < gameHeight ? gameHeight : height
        );
    }
}