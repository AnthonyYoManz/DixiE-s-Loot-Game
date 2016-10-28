#pragma once

#include "GameInfo.h"
#include "RenderInfo.h"
#include "GameState.h"

class TestState : public GameState {
public:
	TestState();
	void initialise(const GameInfo& _info);
	void update(const GameInfo& _info);
	void draw(const RenderInfo& _info);
	void cleanup(const GameInfo& _info);
};
