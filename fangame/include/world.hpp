#ifndef WORLD_HPP
#define WORLD_HPP

extern "C" {
    #include <raylib.h>  
}
#include "../include/player.hpp"
#include "../include/leveldata.hpp"
#include <vector>

class Level {
    public:
        std::vector<Rectangle> colBlocks;
        std::vector<RectObj> worldObjs;
        std::vector<Rectangle> saveLocs;
        std::vector<Rectangle> warpLocs;
        std::vector<Rectangle> waterLocs;
        std::vector<Rectangle> coinLocs;
        std::vector<Triangle> spike16;
        std::vector<Triangle> spike32;
        Texture2D background;
        Texture2D foreground;
        Texture2D water;
        Music music;
        int warpTo;
        Vector2 playerStartPosition;

        void Init();
        void Update();
        void Warp();
        void Draw();
};

class Block : public StaticSprite2D{};

#endif // WORLD_HPP