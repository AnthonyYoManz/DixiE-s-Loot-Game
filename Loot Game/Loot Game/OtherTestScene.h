#pragma once
#pragma once

#include "GameInfo.h"
#include "RenderInfo.h"
#include "Scene.h"

class OtherTestScene : public Scene {
public:
	OtherTestScene();
	void initialise(const GameInfo& _info);
	void update(const GameInfo& _info);
	void draw(const RenderInfo& _info);
	void cleanup(const GameInfo& _info);
};
