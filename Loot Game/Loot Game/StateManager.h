#pragma once
#include <vector>
#include "RenderInfo.h"

struct GameInfo;
class GameState;

class StateManager
{
private:
	//Current states on stack
	std::vector<GameState*> m_states;
	//States that will be added to stack on next update's start
	std::vector<GameState*> m_upcomingStates;
	//If not null, stacks will be cleared and this state will be the only one remaining
	GameState* m_newState;
	//If true then states will pop at next update's start
	bool m_popState;

	void mergeStates(const GameInfo& _info);
	void cleanStates(const GameInfo& _info);
	void linkListToFactory(const GameInfo& _info);
public:
	StateManager();
	~StateManager();
	void initialise(const GameInfo& _info, GameState* _initialState);
	void update(const GameInfo& _info);
	void draw(const RenderInfo& _info);

	//Pushes state to m_upcomingStates
	void pushState(GameState* _newState);
	//Cleans and pops top state from m_states
	void popState();
	//Fills in m_newState
	void swapState(GameState* _newState);
	
	bool isEmpty();
};
