#include "..\include\molten.h"
#include "raylib.h"

double TimerTime(Timer t){
    switch (t.state){
        case TIMER_RUNNING:
            return t.elapsedTime + (GetTime() - t.timeStamp);
            break;
        case TIMER_IDLE:
            return 0.0;
            break;
        case TIMER_PAUSED:
            return t.elapsedTime;
            break;
        default:
            break;
    }
};

void TimerStart(Timer* t){
    t->state = TIMER_RUNNING;
    t->elapsedTime = 0.0 + t->savedTime;
    t->savedTime = 0.0;
    t->timeStamp = GetTime();
};

void TimerPause(Timer* t){
	if (t->state == TIMER_IDLE) return;
    if (t->state == TIMER_PAUSED){
        t->state = TIMER_RUNNING;
        t->timeStamp = GetTime();
    }
    else{
        t->state = TIMER_PAUSED;
        t->elapsedTime += GetTime() - t->timeStamp;
    }
};