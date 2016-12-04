#pragma once
#include <SFML/Graphics.hpp>

class Input;
class StateManager;
template<typename T> class AssetFactory;
class GameObject;
template<typename T> class ObjectFactory;

struct GameInfo
{
	StateManager* m_stateManager;
	Input* m_input;
	AssetFactory<sf::Texture>* m_textureFactory;
	ObjectFactory<GameObject>* m_objectFactory;
	float m_dt;
};