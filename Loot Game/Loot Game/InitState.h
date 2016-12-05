#pragma once
#include "GameState.h"

class InitState : public GameState
{
private:
	GameState* m_nextState;
public:
	InitState(GameState* _nextState);
	~InitState() = default;
	//Pre-load and setup in here
	void initialise(const GameInfo& _info);

	void update(const GameInfo& _info) 
	{ 
		_info.m_stateManager->swapState(m_nextState);  
	};
	//Can be used for loading screen or summin if lots is goin on in here
	void draw(const RenderInfo& _info) {};
	void cleanup(const GameInfo& _info) {};
};