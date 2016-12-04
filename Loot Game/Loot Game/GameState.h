#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameInfo.h"
#include "StateInfo.h"
#include "RenderInfo.h"

class GameObject;

class GameState
{
protected:
	std::string m_name;
	std::vector<GameObject*> m_objects;
	bool m_layered;
	StateInfo m_stateInfo;
public:
	virtual ~GameState() {};
	
	//Initialise the state
	virtual void initialise(const GameInfo& _info) = 0;

	//Update/tick
	virtual void update(const GameInfo& _info) = 0;

	//Render step
	virtual void draw(const RenderInfo& _info) = 0;

	//Deinitialise the state
	virtual void cleanup(const GameInfo& _info) = 0;

	//Optionally overloadable pause (when the state is left but still exists)
	virtual void pause();

	//Optionally overloadable resume (when the state is returned to)
	virtual void resume();

	//Set the state to count as a 'layered' state
	void setLayered(bool _layered);

	//Returns whether or not the state is layered
	bool getLayered();

	//Returns state name
	std::string getName();

	//Returns pointer to m_objects
	std::vector<GameObject*>* getObjectList();
};

