#pragma once
#include <time.h>

class Clock {
private:
	clock_t m_clock;
public:
	Clock();
	void restart();
	/*Returns the time elapsed in seconds*/
	float getTime();
};
