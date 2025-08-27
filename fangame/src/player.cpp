#include "../include/player.hpp"
#include "../include/classes.hpp"

#define GROUND_LEVEL 50
#define TILE_SIZE_32x32 32
#define TILE_32x32 32

int gameWidth = 800;
int gameHeight = 608;
Player player;
extern Level level;
extern const char* title;
std::vector<Bullet> bullets;
extern std::vector<Rectangle> colBlocks;
extern std::vector<RectObj> worldObjects[];
extern Input input;

void Player::Init()
{
    this->position = (Vector2){100, 100 - GROUND_LEVEL};
    this->savePosition = (Vector2){0.0f, (float)gameHeight - 64.0f - 32.0f};
    this->animation = SPR_IDLE;
    this->animationSpeed = 20;
    this->animationFrame = 0;
    this->animationFrameCount = 12;
    this->frameCounter = 0;
    this->animationStart = true;
    this->state = RUN;
    this->direction = 1;
    this->shouldWarp = false;
    this->hitBoxOffset = {12,11};
    this->hitBoxSize = {11,21};
    this->dead = false;
    
    this->velocity = {0, 0};
    this->speed = 3;
    this->gravity = 0.4;
    this->maxFallSpeed = 9;
    this->jumpForce = 8.5;
    this->doubleJumpForce = 7;
    this->jumpRelease = 0.45;
    this->jumping = false;
    this->doubleJump = false;

    this->sndJump = LoadSound("./assets/sounds/sndJump.wav");
    this->sndDJump = LoadSound("./assets/sounds/sndDJump.wav");
    this->sndDeath = LoadSound("./assets/sounds/sndDeath.mp3");
    this->sndShoot = LoadSound("./assets/sounds/sndShoot.wav");
    this->sndPickup = LoadSound("./assets/sounds/sndPickup.mp3");


    this->sprites = {
        LoadTexture("./assets/sprites/sprIdle.png"),
        LoadTexture("./assets/sprites/sprRun.png"),
        LoadTexture("./assets/sprites/sprJump.png"),
        LoadTexture("./assets/sprites/sprFall.png"),
        LoadTexture("./assets/sprites/sprBullet.png")};
}

Rectangle Player::HitBoxRect(){
    return (Rectangle){this->position.x + this->hitBoxOffset.x, this->position.y + this->hitBoxOffset.y, this->hitBoxSize.x, this->hitBoxSize.y};
}

void Player::Update()
{

    this->oldPlayerPosition = {this->position.x, this->position.y};

    this->movingUp = false;
    this->movingDown = false;
    this->movingRight = false;
    this->movingLeft = false;

    // player input
    if (IsKeyDown(input.left)){
        this->position.x -= this->speed;
        this->direction = -1;
        this->hitBoxOffset = {9,11};
    }
    if (IsKeyDown(input.right)){
        this->position.x += this->speed;
        this->direction = 1;
        this->hitBoxOffset = {12,11};
    }
    if (IsKeyPressed(input.jump)){
        if (this->jumping && this->doubleJump && !this->onPlatform){
            this->Animate(DOUBLE_JUMP);
            this->velocity.y = -this->doubleJumpForce;
            this->doubleJump = false;
            PlaySound(this->sndDJump);
        }
        if (!this->jumping || this->onPlatform){
            this->Animate(JUMP);
            this->velocity.y = -this->jumpForce;
            this->jumping = true;
            this->doubleJump = true;
            PlaySound(this->sndJump);
        }
    }
    if (IsKeyReleased(input.jump) && this->velocity.y < 0){
        this->velocity.y *= this->jumpRelease;
    }

    if (this->position.x > this->oldPlayerPosition.x) this->movingRight = true;
    if (this->position.x < this->oldPlayerPosition.x) this->movingLeft = true;
    if (!this->movingLeft && !this->movingRight && !this->jumping) this->Animate(IDLE);
    else if ((this->movingLeft || this->movingRight) && !this->jumping) this->Animate(RUN);

    if (IsKeyPressed(input.shoot)){
        if (bullets.size() < 4){
            bullets.emplace_back(this->position,this->direction);
            PlaySound(this->sndShoot);
        }
    }

    for (auto block : level.colBlocks){
        if (CheckCollisionRecs(this->HitBoxRect(),block)){
            if (this->movingLeft)
                this->position.x = block.x + block.width - this->hitBoxOffset.x;
            else if (this->movingRight)
                this->position.x = block.x - TILE_32x32 + 9;
        }
    }

    this->velocity.y += this->gravity;

    for (auto& waterblock : level.waterLocs){
        if (CheckCollisionRecs(player.HitBoxRect(),waterblock)){
            if (this->velocity.y > 2) this->velocity.y = 2;
            this->doubleJump = true;
            break;        
        }
    }
    
    if (this->velocity.y > this->maxFallSpeed)
        this->velocity.y = this->maxFallSpeed;

    this->position.y += this->velocity.y;

    if (this->position.y > this->oldPlayerPosition.y) this->movingDown = true;
    if (this->position.y < this->oldPlayerPosition.y) this->movingUp = true;
    
    this->onPlatform = false;
    this->jumping = true;

    for (auto& block : level.colBlocks){
        if (CheckCollisionRecs(this->HitBoxRect(),block)){
            if (this->movingDown){
                this->position.y = block.y - TILE_32x32;
                this->velocity.y = 0;
                this->jumping = false;
                this->doubleJump = true;
                this->onPlatform = true;
            }
            else if (this->movingUp){
                this->position.y = block.y + TILE_32x32 - this->hitBoxOffset.y;
                this->velocity.y = 0;
            }
        }
    }

    if (this->position.y > gameHeight - 32){
        this->position.y = gameHeight - 32;
        this->velocity.y = 0;
        this->jumping = false;
    }

    if (this->jumping && this->movingDown) this->Animate(FALL);

    // Check for collision with spikes
    for (auto& s16 : level.spike16){
        if (CheckCollisionRectTriangle(s16.p1, s16.p2, s16.p3)){
            this->onDeath();
            break;
        }
    }

    for (auto& s32 : level.spike32){
        if (CheckCollisionRectTriangle(s32.p1, s32.p2, s32.p3)){
            this->onDeath();
            break;
        }
    }

    for (auto& warp : level.warpLocs){
        if (CheckCollisionRecs(this->HitBoxRect(), (Rectangle){warp.x + 8, warp.y + 8, 16,16}) && coinsCollected == level.coinLocs.size()){
            player.position = savePosition;
            player.shouldWarp = true;
        };
    }

    for (auto& save : level.saveLocs){
        if (CheckCollisionRecs(this->HitBoxRect(), save)){
            savePosition = (Vector2){save.x, save.y};
        };
    }

    for (auto& coin : level.coinLocs){
        if (CheckCollisionRecs(this->HitBoxRect(), (Rectangle){coin.x + 5, coin.y + 10, 21,22})){
            this->coinsCollected++;
            PlaySound(this->sndPickup);
            savePosition = (Vector2){coin.x, coin.y};
            coin.y = 1000;
        };
    }

    this->frameCounter++;
        if (this->frameCounter >= 4){
            this->animationFrame++;
            this->frameCounter = 0;
        }
}

void Player::onDeath(){
    player.position = savePosition;
    player.velocity = (Vector2){0,0};
    PlaySound(this->sndDeath);
    player.dead = true;
    this->deathCount++;
    //SetWindowTitle(TextFormat("%s | Deaths: %d", title, this->deathCount));
}

bool Player::CheckCollisionRectTriangle(Vector2 p1, Vector2 p2, Vector2 p3)
{
    Vector2 topL = (Vector2){this->HitBoxRect().x, this->HitBoxRect().y};
    Vector2 topR = (Vector2){this->HitBoxRect().x + this->hitBoxSize.x - 1, this->HitBoxRect().y};
    Vector2 botL = (Vector2){this->HitBoxRect().x, this->HitBoxRect().y + this->hitBoxSize.y - 1};
    Vector2 botR = (Vector2){this->HitBoxRect().x + this->hitBoxSize.x - 1, this->HitBoxRect().y + this->hitBoxSize.y - 1};

    if (CheckCollisionPointTriangle(topL, p1, p2, p3))
        return true;
    if (CheckCollisionPointTriangle(topR, p1, p2, p3))
        return true;
    if (CheckCollisionPointTriangle(botL, p1, p2, p3))
        return true;
    if (CheckCollisionPointTriangle(botR, p1, p2, p3))
        return true;

    if (CheckCollisionPointRec(p1, this->HitBoxRect()))
        return true;
    if (CheckCollisionPointRec(p2, this->HitBoxRect()))
        return true;
    if (CheckCollisionPointRec(p3, this->HitBoxRect()))
        return true;
    return false;
}

void Player::Animate(int state)
{
    switch (state)
    {
    case DOUBLE_JUMP:
        this->animation = SPR_JUMP;
        this->animationSpeed = 20;
        this->animationFrameCount = 6;
        this->animationStart = true;
        break;
    case FALL:
        this->animation = SPR_FALL;
        this->animationSpeed = 20;
        this->animationFrameCount = 1;
        this->animationStart = true;
        break;
    case IDLE:
        this->animation = SPR_IDLE;
        this->animationSpeed = 20;
        this->animationFrameCount = 4;
        this->animationStart = true;
        break;
    case JUMP:
        this->animation = SPR_JUMP;
        this->animationSpeed = 20;
        this->animationFrameCount = 1;
        this->animationStart = true;
        break;
    case RUN:
        this->animation = SPR_RUN;
        this->animationSpeed = 20;
        this->animationFrameCount = 12;
        this->animationStart = true;
        break;
    default:
        break;
    }
}

void Player::Draw(){
    DrawTextureRec(
            this->sprites[this->animation],
            (Rectangle){(float)this->animationFrame * 32.0f, 0.0f,
                        (float)this->direction * 32.0f, 32.0f},
            this->position, WHITE);
}

void Bullet::Init(){
    //this->sprites = {LoadTexture("./assets/sprites/sprBullet.png")};
    this->hitBoxSize = {4,4};
    this->hitBoxOffset = {0,0};
}

Rectangle Bullet::HitBoxRect(){
    return (Rectangle){this->position.x + this->hitBoxOffset.x, this->position.y + this->hitBoxOffset.y, this->hitBoxSize.x, this->hitBoxSize.y};
}

bool Bullet::blockCol(){
    for (auto& block : level.colBlocks){
        if (CheckCollisionRecs(this->HitBoxRect(),block)){
            return true;
        }
    }
    return false;    
}

void Bullet::Update(){
    this->position.x += 20 * this->direction;
}

void Bullet::Draw(){
    DrawTextureRec(player.sprites[4], (Rectangle){0, 0,4, 4}, this->position, WHITE);
}