#pragma once
#include "GameState.h"
#include <vector>
#include "PlayerObject.h"

class GameplayTestState : public GameState
{
private:
public:
	GameplayTestState();
	~GameplayTestState() = default;
	void initialise(const GameInfo& _info);
	void update(const GameInfo& _info);
	void draw(const RenderInfo& _info);
	void cleanup(const GameInfo& _info);
};