#include "Clock.h"

Clock::Clock() {
	m_clock = clock();
}

void Clock::restart() {
	m_clock = clock();
}

float Clock::getTime() {
	clock_t ticks = clock() - m_clock;
	return (static_cast<float>(ticks) / CLOCKS_PER_SEC);
}