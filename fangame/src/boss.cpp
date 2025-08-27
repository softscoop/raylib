#include "../include/boss.hpp"

#define GROUND_LEVEL 50
#define TILE_SIZE_32x32 32
#define TILE_32x32 32

Boss testBoss;
extern Player player;

void Boss::Init(){
    this->position = (Vector2){100, 608 - 64};
    this->direction = -1;
    this->animation = SPR_IDLE;
    this->animationFrame = 0;
    this->hitBoxOffset = {0,0};
    this->hitBoxSize = {32,32};
    this->sprites = {
        LoadTexture("./assets/sprites/testbosspng.png"),
        LoadTexture("./assets/sprites/sprRun.png"),
        LoadTexture("./assets/sprites/sprJump.png"),
        LoadTexture("./assets/sprites/sprFall.png"),
        LoadTexture("./assets/sprites/sprBullet.png")};
    this->state = Boss::BossState::IDLE;
}

void Boss::Update(){

    //current boss state
    switch (this->state){
        case Boss::BossState::ENGAGED:
            if(this->healthPoints <= 0){
                this->state = Boss::BossState::DEAD;
                this->position.y = 1000;
                break;
            }
            if(player.position.x + 32 < this->position.x){
                this->position.x -= 1;
                this->direction = -1;
            }
            else if(player.position.x > this->position.x + 32){
                this->position.x += 1;
                this->direction = 1;
        }
        break;
        case Boss::BossState::IDLE:
            this->healthPoints = 100;
            if (CheckCollisionRecs(player.HitBoxRect(), this->HitBoxRect())){
                this->state = Boss::BossState::ENGAGED;
            }
        break;
        
        default:
            break;
    }
}

void Boss::Draw(){
    DrawTextureRec(
            this->sprites[this->animation],
            (Rectangle){(float)this->animationFrame * 32.0f, 0.0f,
                        (float)this->direction * 32.0f, 32.0f},
            this->position, WHITE);
}

Rectangle Boss::HitBoxRect(){
    return (Rectangle){this->position.x + this->hitBoxOffset.x, this->position.y + this->hitBoxOffset.y, this->hitBoxSize.x, this->hitBoxSize.y};
}