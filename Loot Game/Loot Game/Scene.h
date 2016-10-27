#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"
#include "GameInfo.h"
#include "RenderInfo.h"

class SceneObject;

class Scene : public GameState
{
protected:
	std::vector<SceneObject*> m_objectList;
	std::vector<unsigned int> m_removalList;
	std::vector<unsigned int> m_uncleanRemovalList;
	sf::Vector2f m_cameraPosition;
	sf::Vector2f m_cameraOffset;
	unsigned int m_currentHandle;

	void processRemovalList();
	void processUncleanRemovalList();
	void removeObjectFromList(unsigned int handle);
public:
	virtual ~Scene() {}
	virtual void initialise(const GameInfo& _info) = 0;
	virtual void update(const GameInfo& _info) = 0;
	virtual void draw(const RenderInfo& _info) = 0;
	virtual void cleanup(const GameInfo& _info) = 0;

	void addObject(SceneObject* _object, sf::Vector2f position = sf::Vector2f(0, 0));
	void removeObject(unsigned int handle);
	void uncleanRemoveObject(unsigned int handle);
	void moveCamera(float x, float y);
	void offsetCamera(float x, float y);

	sf::Vector2f getCameraPosition();
	unsigned int getObjectCount();
	SceneObject* getObjectByID(unsigned int objectID);
	SceneObject* getObjectByHandle(unsigned int handle);
};
