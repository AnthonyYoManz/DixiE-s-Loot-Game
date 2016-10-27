#pragma once

#include <SFML/Graphics.hpp>

class Timer
{
private:
	sf::Clock m_clock;
	float m_target;
	float m_pauseTime;
	bool m_paused;
public:
	void pause();
	bool check();
	void start(float _target);
	void resume();
};
