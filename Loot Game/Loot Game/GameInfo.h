#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "StateManager.h"
#include "AssetFactory.h"
#include "GameObject.h"
#include "ObjectFactory.h"

struct GameInfo
{
	StateManager* m_stateManager;
	Input* m_input;
	AssetFactory<sf::Texture>* m_textureFactory;
	ObjectFactory<GameObject>* m_objectFactory;
	float m_dt;
};