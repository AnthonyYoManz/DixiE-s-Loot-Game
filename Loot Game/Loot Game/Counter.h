#pragma once

class Counter
{
private:
	unsigned int m_count;
	unsigned int m_target;
	bool m_paused;
public:
	Counter();
	void add(unsigned int _amount = 1);
	void setTarget(unsigned int _target);
	void pause();
	void resume();
	void restart();
	void restart(unsigned int _target);
	unsigned int getCount();
	unsigned int getTarget();
	bool check();
	bool isPaused();
};