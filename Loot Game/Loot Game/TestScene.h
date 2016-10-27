#pragma once

#include "GameInfo.h"
#include "RenderInfo.h"
#include "Scene.h"

class TestScene : public Scene {
public:
	TestScene();
	void initialise(const GameInfo& _info);
	void update(const GameInfo& _info);
	void draw(const RenderInfo& _info);
	void cleanup(const GameInfo& _info);
};
