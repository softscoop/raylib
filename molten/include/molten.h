#ifndef MOLTEN_H
#define MOLTEN_H

typedef void (*MiniGameInput)(void);
typedef void (*MiniGameUpdate)(void);
typedef void (*MiniGameDraw)(void);

typedef struct MiniGame{
    MiniGameInput Input;
    MiniGameUpdate Update;
    MiniGameDraw Draw;
    char* name; 
} MiniGame;

typedef enum{
    TIMER_IDLE,
    TIMER_RUNNING,
    TIMER_PAUSED
} TimerState;

typedef struct Timer{
    TimerState state;
    double timeStamp;
    double elapsedTime;
    double savedTime;
} Timer;

double TimerTime(Timer t);
void TimerStart(Timer* t);
void TimerPause(Timer* t);

#endif // MOLTEN.H