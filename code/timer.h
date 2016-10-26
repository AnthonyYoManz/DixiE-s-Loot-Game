#ifndef ANT_TIMER
#define ANT_TIMER

#include <SFML/Graphics.hpp>

class Timer{
    private:
        sf::Clock clock;
        float target;
        float pauseTime;
        bool paused;
    public:
        void pause();
        bool check();
        void start(float _target);
        void resume();
};


#endif // ANT_TIMER
