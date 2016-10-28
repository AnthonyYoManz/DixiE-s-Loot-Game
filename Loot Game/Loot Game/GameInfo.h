#pragma once
#include <SFML/Graphics.hpp>

class Input;
class StateManager;
template<typename T> class AssetFactory;

struct GameInfo
{
	StateManager* m_stateManager;
	Input* m_input;
	AssetFactory<sf::Texture>* m_textureFactory;
	float m_dt;
};