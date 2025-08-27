#ifndef BOSS_HPP
#define BOSS_HPP

extern "C" {
    #include <raylib.h>  
}
#include "../include/classes.hpp"
#include "../include/world.hpp"

class Boss : public Sprite2D{
    public:
        enum BossState{
            IDLE,
            ENGAGED,
            DEAD,
            DOUBLE_JUMP,
            FALL,
            HIT,
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

        int state;
        float healthPoints;

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

#endif // BOSS.HPP