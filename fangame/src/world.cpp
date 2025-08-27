#include "../include/world.hpp"

extern int gameWidth;
extern int gameHeight;
extern Player player;
Level level;
extern std::vector<Triangle> spike16Triangles[];
extern std::vector<Triangle> spike32Triangles[];
extern std::vector<Rectangle> collisionRectangles[];
extern std::vector<RectObj> worldObjects[];
extern std::vector<Texture2D> levelForegrounds[];
extern std::vector<Texture2D> levelWater[];
extern const int levelCount;

void Level::Init(){
    loadWorldData();
    player.position = (Vector2){0.0f, (float)gameHeight - 64.0f - 32.0f};
    this->background = LoadTexture("./assets/backgrounds/background.png");
    this->warpTo = 0;
    this->Warp();
}

void Level::Update(){
    if (player.shouldWarp)
        {
            this->Warp();
            player.shouldWarp = false;
        }
}

void Level::Warp(){
    this->warpTo++;
    if (this->warpTo > levelCount || this->warpTo < 0) this->warpTo = 0;
    this->foreground = levelForegrounds[warpTo][0];
    this->water = levelWater[warpTo][0];
    this->colBlocks.clear();
    this->spike32.clear();
    this->spike16.clear();
    this->worldObjs.clear();
    this->saveLocs.clear();
    this->warpLocs.clear();
    this->waterLocs.clear();
    this->coinLocs.clear();
    player.coinsCollected = 0;
    for (int i = 0; i < collisionRectangles[this->warpTo].size(); i++){
        this->colBlocks.push_back(collisionRectangles[warpTo][i]);
    }
    for (int i = 0; i < spike32Triangles[this->warpTo].size(); i++){
        this->spike32.push_back(spike32Triangles[warpTo][i]);
    }
    for (int i = 0; i < spike16Triangles[this->warpTo].size(); i++){
        this->spike16.push_back(spike16Triangles[warpTo][i]);
    }
    for (int i = 0; i < worldObjects[this->warpTo].size(); i++){
        switch (worldObjects[this->warpTo][i].Id)
        {
        case 6:
            this->saveLocs.push_back(worldObjects[this->warpTo][i].rect);
            break;
        case 7:
            this->warpLocs.push_back(worldObjects[this->warpTo][i].rect);
            break;
        case 8:
            this->playerStartPosition = (Vector2){worldObjects[this->warpTo][i].rect.x,worldObjects[this->warpTo][i].rect.y};
            player.position = playerStartPosition;
            player.savePosition = playerStartPosition;
            break;
        case 9:
            this->waterLocs.push_back(worldObjects[this->warpTo][i].rect);
            break;
        case 10:
            this->coinLocs.push_back(worldObjects[this->warpTo][i].rect);
            break;
        default:
            break;
        }
    }
}

void Level::Draw(){
    DrawTexture(this->background, 0, 0, WHITE);
    DrawTexture(this->foreground, 0, 0, WHITE);
}