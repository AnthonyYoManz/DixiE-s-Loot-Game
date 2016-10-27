#pragma once

#include <SFML/Graphics.hpp>
#include "GameInfo.h"
#include "RenderInfo.h"

class GameState
{
protected:
	bool m_layered;
public:
	virtual ~GameState() {};
	virtual void initialise(const GameInfo& _info) = 0;
	virtual void update(const GameInfo& _info) = 0;
	virtual void draw(const RenderInfo& _info) = 0;
	virtual void cleanup() = 0;
	virtual void pause();
	virtual void resume();
	void setLayered(bool _layered);
	bool getLayered();
};

