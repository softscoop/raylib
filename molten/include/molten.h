#ifndef MOLTEN_H
#define MOLTEN_H

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

double TimerTime(Timer t);
void TimerStart(Timer* t);
void TimerPause(Timer* t);

#endif // MOLTEN.H