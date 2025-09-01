#include <stdio.h>
#include <raylib.h>
#include "../../molten/include/molten.h"

extern bool switchGame;
extern int selection;
extern bool gameFirstFrame;

static int screenWidth = 500;
static int screenHeight = 500;
static int appWidth = 500;
static int appHeight = 500;
static int pixelGameWidth = 128;
static int pixelGameHeight = 128;
static int selector = 2;
static Texture2D statNumbers[11];
static Texture2D vectorCase;
static Texture2D menu;
static Texture2D pixelGameBackground;
static Texture2D pixelHudBackground;
static Texture2D petSprite;
static Texture2D selectionBorder;
static Texture2D selectionHeart;
static Texture2D selectionSmile;
static Texture2D selectionFrown;
static Texture2D selectionNeutral;
static Texture2D selectionFood;
static Texture2D selectionGames;
static Texture2D selectionRoom;
static Texture2D selectionSleep;

typedef enum{
    FEED = 2,
    PLAY,
    COMFORT,
    REST
} SelectionOptions;

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

void PetUpdate(Pet* p);

Pet pet = {.health = 5, .mood = 5, .hunger = 5, .play = 5, .comfort = 5, .tiredness = 5,
    .Update = &PetUpdate};

float ClampF(float num, float min, float max){
    if (num < min) return min;
    else if(num > max) return max;
    return num; 
}

void DigiPetInput(void){
    if (gameFirstFrame){
        SetWindowTitle(TextFormat("%s", "Digi Pet"));
        SetWindowSize(500,500);
        SetWindowPosition((1366 / 2) - (screenWidth / 2), (758 / 2) - (screenHeight / 2));
        HideCursor();
        statNumbers[0] = (LoadTexture("./assets/digipet/sprites/00.png"));
        statNumbers[1] = (LoadTexture("./assets/digipet/sprites/01.png"));
        statNumbers[2] = (LoadTexture("./assets/digipet/sprites/02.png"));
        statNumbers[3] = (LoadTexture("./assets/digipet/sprites/03.png"));
        statNumbers[4] = (LoadTexture("./assets/digipet/sprites/04.png"));
        statNumbers[5] = (LoadTexture("./assets/digipet/sprites/05.png"));
        statNumbers[6] = (LoadTexture("./assets/digipet/sprites/06.png"));
        statNumbers[7] = (LoadTexture("./assets/digipet/sprites/07.png"));
        statNumbers[8] = (LoadTexture("./assets/digipet/sprites/08.png"));
        statNumbers[9] = (LoadTexture("./assets/digipet/sprites/09.png"));
        statNumbers[10] = (LoadTexture("./assets/digipet/sprites/10.png"));

        vectorCase = LoadTexture("./assets/digipet/backgrounds/vectorcase.png");
        menu = LoadTexture("./assets/digipet/menu/menu.png");
        pixelGameBackground = LoadTexture("./assets/digipet/backgrounds/pixelgamebackground.png");
        pixelHudBackground = LoadTexture("./assets/digipet/backgrounds/pixelhudbackground.png");
        petSprite = LoadTexture("./assets/digipet/sprites/petsprite.png");
        selectionBorder = LoadTexture("./assets/digipet/sprites/selectionBorder.png");
        selectionHeart = LoadTexture("./assets/digipet/sprites/heart.png");
        selectionSmile = LoadTexture("./assets/digipet/sprites/smile.png");
        selectionFrown = LoadTexture("./assets/digipet/sprites/frown.png");
        selectionNeutral = LoadTexture("./assets/digipet/sprites/neutral.png");
        selectionFood = LoadTexture("./assets/digipet/sprites/food.png");
        selectionGames = LoadTexture("./assets/digipet/sprites/games.png");
        selectionRoom = LoadTexture("./assets/digipet/sprites/room.png");
        selectionSleep = LoadTexture("./assets/digipet/sprites/sleep.png");
        TimerStart(&pet.healthTimer);
        TimerStart(&pet.moodTimer);
        TimerStart(&pet.hungerTimer);
        TimerStart(&pet.playTimer);
        TimerStart(&pet.comfortTimer);
        TimerStart(&pet.tirednessTimer);
        //gameFirstFrame = false;
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
}

void DigiPetUpdate(void){
    pet.Update(&pet);
}

void DigiPetDraw(void){
    static RenderTexture2D gameRenderTexture;
    static RenderTexture2D vectorCaseTexture;
    if (gameFirstFrame){
        gameRenderTexture = LoadRenderTexture(pixelGameWidth, pixelGameHeight);
        SetTextureFilter(gameRenderTexture.texture, TEXTURE_FILTER_POINT);
        vectorCaseTexture = LoadRenderTexture(appWidth, appHeight);
        SetTextureFilter(vectorCaseTexture.texture, TEXTURE_FILTER_POINT);
        gameFirstFrame = false;
    }
    
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
    if (IsKeyPressed(KEY_O)){
        gameFirstFrame = true;
        switchGame = true;
        selection = 1;
    } 
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
