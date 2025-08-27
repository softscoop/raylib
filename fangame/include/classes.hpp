#ifndef CLASSES_HPP
#define CLASSES_HPP

extern "C" {
    #include <raylib.h>   
}
#include <vector>

typedef struct Input{
    int up;
    int down;
    int left;
    int right;
    int jump;
    int shoot;
} Input;

typedef struct Triangle{
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
} Triangle;

typedef struct RectObj{
    int Id;
    Rectangle rect;
} RectObj;

// Has Movement / Animations
class Sprite2D {
    public:
        Vector2 position;
        std::vector<Texture2D> sprites;
        Vector2 hitBoxOffset;
        Vector2 hitBoxSize;
        Vector2 oldPlayerPosition;
        bool movingUp;
        bool movingDown;
        bool movingRight;
        bool movingLeft;

        int animation;
        int animationSpeed;
        unsigned char animationFrame;
        int animationFrameCount;
        int frameCounter;
        bool animationStart;
        int state;
        int direction;
        int deathCount;
};

// Static sprite with no animations but a hitbox
class StaticSprite2D {
    public:
        Vector2 position;
        std::vector<Texture2D> sprites;
        Vector2 hitBoxOffset;
        Vector2 hitBoxSize;
        int direction;
};

class Timer{
    public:
        enum state{
            IDLE,
            RUNNING,
            PAUSED
        };

        int state = this->IDLE;
        double timeStamp = 0.0;
        double elapsedTime = 0.0;
        double savedTime = 0.0;

        double Time(){
            switch (this->state)
            {
            case this->RUNNING:
                return this->elapsedTime + (GetTime() - this->timeStamp);
                break;
            case this->IDLE:
                return 0.0;
                break;
            case this->PAUSED:
                return this->elapsedTime;
                break;
            default:
                break;
            }
            return this->timeStamp;
        };

        void Start(){
            this->state = this->RUNNING;
			this->elapsedTime = 0.0 + this->savedTime;
            this->savedTime = 0.0;
            this->timeStamp = GetTime();
        };

        void Pause(){
			if (this->state == this->IDLE) return;
            if (this->state == this->PAUSED){
                this->state = this->RUNNING;
                this->timeStamp = GetTime();
            }
            else{
                this->state = this->PAUSED;
                this->elapsedTime += GetTime() - this->timeStamp;
            }
        };
};

#endif // CLASSES_HPP