#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ObjectFactory.h"
#include "GameObject.h"
#include "AssetFactory.h"
#include "GameInfo.h"
#include "RenderInfo.h"
#include "Debugger.h"


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
	Debugger m_debug;

	void initialiseFactories();
public:
	sf::RenderWindow m_window;
	
	Game();
	~Game();
	//Initialise the game
	void initialise(GameState* _initialState);

	//Poll for an event
	bool pollEvent(sf::Event& event);

	//Update/Tick
	void update();

	//Render step
	void draw();

	//Queue game closure
	void quit();

	//Deinitialise the game
	void cleanup();

	//Set screen background colour
	void setClearColour(sf::Color _colour);
	
	//Returns whether or not the game is running
	bool isRunning() const;

	//Returns window size
	sf::Vector2u getWindowSize() const;

	//Returns duration game has been active in seconds
	float getGameTime() const;
	
	//Returns time since last frame in seconds
	float deltaTime() const;
};
