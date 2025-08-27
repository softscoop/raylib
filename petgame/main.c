#include <raylib.h>
#include <stdio.h>

void PlayGame(RenderTexture2D gameRenderTexture, RenderTexture2D vectorCaseTexture);
void DrawMenu(RenderTexture2D gameRenderTexture, RenderTexture2D vectorCaseTexture);

//enums
typedef enum{
    TITLE,
    MENU,
    OPTIONS,
    GAME
} GameState;

typedef enum{
    FEED = 2,
    PLAY,
    COMFORT,
    REST
} SelectionOptions;

typedef enum{
    TIMER_IDLE,
    TIMER_RUNNING,
    TIMER_PAUSED
} TimerState;

//structs
typedef struct Timer{
    TimerState state;
    double timeStamp;
    double elapsedTime;
    double savedTime;
} Timer;

struct Pet;
typedef struct Pet{
    float health;
    float mood;
    float hunger;
    float play;
    float comfort;
    float tiredness;
    Timer healthTimer;
    Timer moodTimer;
    Timer hungerTimer;
    Timer playTimer;
    Timer comfortTimer;
    Timer tirednessTimer;
    void (*Update)(struct Pet*);
} Pet;

double TimerTime(Timer t){
    switch (t.state){
        case TIMER_RUNNING:
            return t.elapsedTime + (GetTime() - t.timeStamp);
            break;
        case TIMER_IDLE:
            return 0.0;
            break;
        case TIMER_PAUSED:
            return t.elapsedTime;
            break;
        default:
            break;
    }
};

void TimerStart(Timer* t){
    t->state = TIMER_RUNNING;
    t->elapsedTime = 0.0 + t->savedTime;
    t->savedTime = 0.0;
    t->timeStamp = GetTime();
};

void TimerPause(Timer* t){
	if (t->state == TIMER_IDLE) return;
    if (t->state == TIMER_PAUSED){
        t->state = TIMER_RUNNING;
        t->timeStamp = GetTime();
    }
    else{
        t->state = TIMER_PAUSED;
        t->elapsedTime += GetTime() - t->timeStamp;
    }
};

float ClampF(float num, float min, float max){
    if (num < min) return min;
    else if(num > max) return max;
    return num; 
}

void PetUpdate(Pet* p){
    if (TimerTime(p->healthTimer) >= 10.0){
        p->health = ClampF(p->health -= 1.f, 0.f,10.f);
        TimerStart(&p->healthTimer);
    }
    if (TimerTime(p->moodTimer) >= 10.0){
        p->mood = ClampF(p->mood -= 1.f, 0.f,10.f);
        TimerStart(&p->moodTimer);
    }
    if (TimerTime(p->hungerTimer) >= 10.0){
        p->hunger = ClampF(p->hunger -= 1.f, 0.f,10.f);
        TimerStart(&p->hungerTimer);
    }
    if (TimerTime(p->playTimer) >= 10.0){
        p->play = ClampF(p->play -= 1.f, 0.f,10.f);
        TimerStart(&p->playTimer);
    }
    if (TimerTime(p->comfortTimer) >= 10.0){
        p->comfort = ClampF(p->comfort -= 1.f, 0.f,10.f);
        TimerStart(&p->comfortTimer);
    }
    if (TimerTime(p->tirednessTimer) >= 10.0){
        p->tiredness = ClampF(p->tiredness -= 1.f, 0.f,10.f);
        TimerStart(&p->tirednessTimer);
    }
    return;
}

Pet pet = {.health = 5, .mood = 5, .hunger = 5, .play = 5, .comfort = 5, .tiredness = 5,
    .Update = &PetUpdate};
int selector = 2;
GameState gameState = GAME;
bool gameFirstFrame = true;
Texture2D statNumbers[11];
Texture2D vectorCase;
Texture2D menu;
Texture2D pixelGameBackground;
Texture2D pixelHudBackground;
Texture2D petSprite;
Texture2D selectionBorder;
Texture2D selectionHeart;
Texture2D selectionSmile;
Texture2D selectionFrown;
Texture2D selectionNeutral;
Texture2D selectionFood;
Texture2D selectionGames;
Texture2D selectionRoom;
Texture2D selectionSleep;

int main(){
    
    int appWidth = 500;
    int appHeight = 500;
    int pixelGameWidth = 128;
    int pixelGameHeight = 128;
    const char* appTitle = "PetGame";
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(appWidth, appHeight, appTitle);
    SetTargetFPS(60);
    InitAudioDevice();
    const char* appDir = GetApplicationDirectory();
    ChangeDirectory(appDir);
    Image icon = LoadImage("./assets/icon.png");
    SetWindowIcon(icon);
    GetTime();

    RenderTexture2D gameRenderTexture = LoadRenderTexture(pixelGameWidth, pixelGameHeight);
    SetTextureFilter(gameRenderTexture.texture, TEXTURE_FILTER_POINT);
    RenderTexture2D vectorCaseTexture = LoadRenderTexture(appWidth, appHeight);
    SetTextureFilter(vectorCaseTexture.texture, TEXTURE_FILTER_POINT);

    statNumbers[0] = (LoadTexture("./assets/sprites/00.png"));
    statNumbers[1] = (LoadTexture("./assets/sprites/01.png"));
    statNumbers[2] = (LoadTexture("./assets/sprites/02.png"));
    statNumbers[3] = (LoadTexture("./assets/sprites/03.png"));
    statNumbers[4] = (LoadTexture("./assets/sprites/04.png"));
    statNumbers[5] = (LoadTexture("./assets/sprites/05.png"));
    statNumbers[6] = (LoadTexture("./assets/sprites/06.png"));
    statNumbers[7] = (LoadTexture("./assets/sprites/07.png"));
    statNumbers[8] = (LoadTexture("./assets/sprites/08.png"));
    statNumbers[9] = (LoadTexture("./assets/sprites/09.png"));
    statNumbers[10] = (LoadTexture("./assets/sprites/10.png"));

    vectorCase = LoadTexture("./assets/backgrounds/vectorcase.png");
    menu = LoadTexture("./assets/menu/menu.png");
    pixelGameBackground = LoadTexture("./assets/backgrounds/pixelgamebackground.png");
    pixelHudBackground = LoadTexture("./assets/backgrounds/pixelhudbackground.png");
    petSprite = LoadTexture("./assets/sprites/petsprite.png");
    selectionBorder = LoadTexture("./assets/sprites/selectionBorder.png");
    selectionHeart = LoadTexture("./assets/sprites/heart.png");
    selectionSmile = LoadTexture("./assets/sprites/smile.png");
    selectionFrown = LoadTexture("./assets/sprites/frown.png");
    selectionNeutral = LoadTexture("./assets/sprites/neutral.png");
    selectionFood = LoadTexture("./assets/sprites/food.png");
    selectionGames = LoadTexture("./assets/sprites/games.png");
    selectionRoom = LoadTexture("./assets/sprites/room.png");
    selectionSleep = LoadTexture("./assets/sprites/sleep.png");

    while (!WindowShouldClose()){
        switch (gameState)
        {
        case MENU:
            DrawMenu(gameRenderTexture, vectorCaseTexture);
            break;
        case GAME:
            PlayGame(gameRenderTexture, vectorCaseTexture);
            break;
        default:
            break;
        }
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void PlayGame(RenderTexture2D gameRenderTexture, RenderTexture2D vectorCaseTexture){

    if (gameFirstFrame){
        TimerStart(&pet.healthTimer);
        TimerStart(&pet.moodTimer);
        TimerStart(&pet.hungerTimer);
        TimerStart(&pet.playTimer);
        TimerStart(&pet.comfortTimer);
        TimerStart(&pet.tirednessTimer);
        gameFirstFrame = false;
    }

    if (IsKeyPressed(KEY_A) && selector > 2) selector -= 1;
    if (IsKeyPressed(KEY_D) && selector < 5) selector += 1;

    if (IsKeyPressed(KEY_K)){
        switch (selector){
            case FEED:
                if(IsKeyPressed(KEY_K)){
                    pet.health = ClampF(pet.health += 1.f, 0.f,10.f);
                    TimerStart(&pet.healthTimer);
                    pet.mood = ClampF(pet.mood += 1.f, 0.f,10.f);
                    TimerStart(&pet.moodTimer);
                    pet.hunger = ClampF(pet.hunger += 2.f, 0.f,10.f);
                    TimerStart(&pet.hungerTimer);
                    //pet.play = ClampF(pet.play -= 2.f, 0.f,10.f);
                    //pet.comfort = ClampF(pet.comfort -= 2.f, 0.f,10.f);
                    //pet.tiredness = ClampF(pet.tiredness -= 2.f, 0.f,10.f);
                }
            break;
            case PLAY:
                if(IsKeyPressed(KEY_K)){
                    pet.health = ClampF(pet.health += 0.5f, 0.f,10.f);
                    TimerStart(&pet.healthTimer);
                    pet.mood = ClampF(pet.mood += 1.f, 0.f,10.f);
                    TimerStart(&pet.moodTimer);
                    pet.hunger = ClampF(pet.hunger -= 0.5f, 0.f,10.f);
                    TimerStart(&pet.hungerTimer);
                    pet.play = ClampF(pet.play += 2.f, 0.f,10.f);
                    TimerStart(&pet.playTimer);
                    //pet.comfort = ClampF(pet.comfort -= 2.f, 0.f,10.f);
                    pet.tiredness = ClampF(pet.tiredness -= 0.5f, 0.f,10.f);
                    TimerStart(&pet.tirednessTimer);                                        
                }
                break;
            case COMFORT:
                if(IsKeyPressed(KEY_K)){
                    //pet.health = ClampF(pet.health += 1.f, 0.f,10.f);
                    //pet.mood = ClampF(pet.mood += 1.f, 0.f,10.f);
                    //pet.hunger = ClampF(pet.hunger -= 0.5f, 0.f,10.f);
                    //pet.play = ClampF(pet.play += 2.f, 0.f,10.f);
                    pet.comfort = ClampF(pet.comfort += 2.f, 0.f,10.f);
                    TimerStart(&pet.comfortTimer);
                    //pet.tiredness = ClampF(pet.tiredness -= 2.5f, 0.f,10.f);                                        
                    }
                break;
            case REST:
                if(IsKeyPressed(KEY_K)){
                    //pet.health = ClampF(pet.health += 1.f, 0.f,10.f);
                    //pet.mood = ClampF(pet.mood += 1.f, 0.f,10.f);
                    //pet.hunger = ClampF(pet.hunger -= 0.5f, 0.f,10.f);
                    //pet.play = ClampF(pet.play += 2.f, 0.f,10.f);
                    //pet.comfort = ClampF(pet.comfort -= 2.f, 0.f,10.f);
                    pet.tiredness = ClampF(pet.tiredness += 2.5f, 0.f,10.f);
                    TimerStart(&pet.tirednessTimer);                                        
                }
                break;
            default:
                break;
        }
    }
    
    pet.Update(&pet);
    
    // draw to pixel texture
    BeginTextureMode(gameRenderTexture);
        ClearBackground(BLACK);
        DrawTexture(pixelGameBackground,0,0,WHITE);
        DrawTexture(petSprite,32,25,WHITE);
        DrawTexture(pixelHudBackground,0,96,WHITE);
        DrawTexture(selectionHeart, 14,100,WHITE);
        if (pet.health >= 6) DrawTexture(selectionSmile, 32,100,WHITE);
        if (pet.health > 3 && pet.health < 6) DrawTexture(selectionNeutral, 32,100,WHITE);
        if (pet.health <= 3) DrawTexture(selectionFrown, 32,100,WHITE);
        DrawTexture(selectionFood, 50,100,WHITE);
        DrawTexture(selectionGames, 68,100,WHITE);
        DrawTexture(selectionRoom, 86,100,WHITE);
        DrawTexture(selectionSleep, 104,100,WHITE);
        DrawTexture(selectionBorder, 11 + ((selector * 16) + (2 * selector)), 96, WHITE);

        DrawTexture(statNumbers[(int)pet.health], 14,114,WHITE);
        DrawTexture(statNumbers[(int)pet.mood], 32,114,WHITE);
        DrawTexture(statNumbers[(int)pet.hunger], 50,114,WHITE);
        DrawTexture(statNumbers[(int)pet.play], 68,114,WHITE);
        DrawTexture(statNumbers[(int)pet.comfort], 86,114,WHITE);
        DrawTexture(statNumbers[(int)pet.tiredness], 104,114,WHITE);
    EndTextureMode();

    //draw pixel game to vector case at 2x
    BeginTextureMode(vectorCaseTexture);
        ClearBackground(BLACK);
        DrawTexture(vectorCase,0,0,WHITE);
        DrawTexturePro(gameRenderTexture.texture,(Rectangle){0,0,128,-128},(Rectangle){122,122,256,256},(Vector2){0,0},0.0f,WHITE);
    EndTextureMode();

    //draw to application screen
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(vectorCaseTexture.texture,(Rectangle){0,0,500,-500},(Rectangle){0,0,500,500},(Vector2){0,0},0.0f,WHITE);
    EndDrawing();
}

void DrawMenu(RenderTexture2D gameRenderTexture, RenderTexture2D vectorCaseTexture){
    if(IsKeyPressed(KEY_G)) gameState = GAME;
    BeginTextureMode(gameRenderTexture);
        ClearBackground(BLACK);
        DrawTexture(menu,0,0,WHITE);
    EndTextureMode();

    //draw pixel game to vector case at 2x
    BeginTextureMode(vectorCaseTexture);
        ClearBackground(BLACK);
        DrawTexture(vectorCase,0,0,WHITE);
        DrawTexturePro(gameRenderTexture.texture,(Rectangle){0,0,128,-128},(Rectangle){122,122,256,256},(Vector2){0,0},0.0f,WHITE);
    EndTextureMode();

    //draw to app screen
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(vectorCaseTexture.texture,(Rectangle){0,0,500,-500},(Rectangle){0,0,500,500},(Vector2){0,0},0.0f,WHITE);
    EndDrawing();
}