#include "Timer.h"

void Timer::start(float _target){
    m_target = _target;
    m_paused = false;
    m_clock.restart();
}

bool Timer::check(){
    if(m_paused)
    {
        return false;
    }
    return m_clock.getElapsedTime().asSeconds()>=m_target;
}

void Timer::pause(){
    if(!m_paused){
        m_paused = true;
        m_pauseTime = m_clock.getElapsedTime().asSeconds();
    }
}

void Timer::resume(){
    if(m_paused){
        m_paused = false;
        m_target += m_clock.getElapsedTime().asSeconds() - m_pauseTime;
    }
}
