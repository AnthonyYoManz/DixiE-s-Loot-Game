#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ObjectFactory.h"
#include "GameObject.h"
#include "AssetFactory.h"
#include "GameInfo.h"
#include "RenderInfo.h"


class Input;
class StateManager;
class GameState;

class Game
{
private:
	bool m_running;
	sf::Vector2u m_windowSize;
	sf::Clock m_gameTimer;
	sf::Clock m_loopTimer;
	static const float m_maxDt;
	float m_dt;
	sf::Color m_clearColour;
	GameInfo m_gameInfo;
	RenderInfo m_renderInfo;
	StateManager* m_stateManager;
	Input* m_input;
	ObjectFactory<GameObject> m_objectFactory;
	AssetFactory<sf::Texture> m_textureFactory;
	void initialiseFactories();
public:
	sf::RenderWindow m_window;
	
	Game();
	~Game();
	//primary functions
	void initialise(GameState* initialState);
	bool pollEvent(sf::Event& event);
	void update();
	void draw();
	void quit();
	void cleanup();

	//setters
	void setClearColour(sf::Color colour);
	//getters
	bool isRunning() const;
	sf::Vector2u getWindowSize() const;
	float getGameTime() const;
	float deltaTime() const;
};
