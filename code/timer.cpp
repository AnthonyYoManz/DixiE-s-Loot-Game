#include "Timer.h"

void Timer::start(float _target){
    target = _target;
    paused = false;
    clock.restart();
}

bool Timer::check(){
    if(paused)
    {
        return false;
    }
    return clock.getElapsedTime().asSeconds()>=target;
}

void Timer::pause(){
    if(!paused){
        paused = true;
        pauseTime = clock.getElapsedTime().asSeconds();
    }
}

void Timer::resume(){
    if(paused){
        paused = false;
        target += clock.getElapsedTime().asSeconds() - pauseTime;
    }
}
