#ifndef PLAYER_HPP
#define PLAYER_HPP

extern "C" {
    #include <raylib.h>  
}
#include "../include/classes.hpp"
#include "../include/world.hpp"

class Player : public Sprite2D{
    public:
        enum PlayerState{
            DOUBLE_JUMP,
            FALL,
            HIT,
            IDLE,
            JUMP,
            RUN,
            WALL_JUMP
        };

        enum TextureNames{   
            SPR_IDLE,
            SPR_RUN,
            SPR_JUMP,
            SPR_FALL
        };

        int speed;
        float gravity;
        float maxFallSpeed;
        float jumpForce;
        float doubleJumpForce;
        float jumpRelease;
        bool jumping;
        bool doubleJump;
        bool onPlatform;
        Vector2 savePosition;
        Vector2 velocity;

        bool dead;
        bool shouldWarp;
        int coinsCollected;

        Sound sndJump;
        Sound sndDJump;
        Sound sndDeath;
        Sound sndShoot;
        Sound sndPickup;

        void Init();
        Rectangle HitBoxRect();
        void Update();
        void onDeath();
        bool CheckCollisionRectTriangle(Vector2 p1, Vector2 p2, Vector2 p3);
        void Animate(int state);
        void Draw();
};

class Bullet : public StaticSprite2D{
    public:
        Bullet(Vector2 pos,int direction){
            if (direction == RIGHT){
                this->position.x = (pos.x + 32) - 20;
                this->position.y = pos.y + 19;
            }
            else if (direction == LEFT){
                this->position.x = (pos.x - 4) + 20;
                this->position.y = pos.y + 19;
            }
            //this->position = pos;
            this->direction = direction;
            this->Init();
        };

        enum Movement{
            LEFT = -1,
            RIGHT = 1
        };

        void Init();
        Rectangle HitBoxRect();
        bool blockCol();
        void Update();
        void Draw();
};

#endif // PLAYER.HPP