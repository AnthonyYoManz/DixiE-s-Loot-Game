#include "Game.h"
#include <cstdlib>
#include "StateManager.h"
#include "Input.h"

const float Game::m_maxDt = 0.1;

Game::Game()
{
	m_running = false;
	m_stateManager = nullptr;
	m_input = nullptr;
}

Game::~Game()
{
	m_running = false;
	cleanup();
}

//primary functions
void Game::initialise(GameState* _initialState)
{
	//Fullscreen
    //window.create(sf::VideoMode::getDesktopMode(), "Equipment Test", sf::Style::Fullscreen);
	//Windowed
	m_window.create(sf::VideoMode(640, 480), "Equipment Test", sf::Style::Default);
	m_window.setVerticalSyncEnabled(true);
	m_windowSize = m_window.getSize();
	m_clearColour = sf::Color(0, 0, 0, 255);
    srand(m_gameTimer.getElapsedTime().asMilliseconds());
	m_running = true;
	m_dt = 0;
	m_gameInfo.m_dt = 0;
	m_renderInfo.m_target = &m_window;

	m_input = new Input;
	m_gameInfo.m_input = m_input;
	m_stateManager = new StateManager;
	m_gameInfo.m_stateManager = m_stateManager;
	m_stateManager->initialise(m_gameInfo, _initialState);
	
	m_gameTimer.restart();
	m_loopTimer.restart();
}
bool Game::pollEvent(sf::Event& event)
{
    return m_window.pollEvent(event);
}
void Game::update()
{
	m_input->cleanEvents();
	m_input->handleEvents(m_window);
	m_dt = m_loopTimer.getElapsedTime().asSeconds();
	m_loopTimer.restart();
	m_gameInfo.m_dt = deltaTime();
	m_stateManager->update(m_gameInfo);

	if (m_stateManager->isEmpty())
	{
		quit();
	}
}
void Game::draw()
{
	m_window.clear(m_clearColour);
	m_stateManager->draw(m_renderInfo);
	m_window.display();
}
void Game::quit()
{
	m_running = false;
}
void Game::cleanup()
{
	if (!m_running)
	{
		m_window.close();
		if (m_stateManager)
		{
			delete m_stateManager;
			m_stateManager = nullptr;
		}
		if (m_input)
		{
			delete m_input;
			m_input = nullptr;
		}
    }
}

//setters
void Game::setClearColour(sf::Color colour)
{
	m_clearColour = colour;
}

//getters
bool Game::isRunning() const
{
    return m_running;
}
sf::Vector2u Game::getWindowSize() const
{
    return m_windowSize;
}
float Game::getGameTime() const
{
    return m_gameTimer.getElapsedTime().asSeconds();
}
float Game::deltaTime() const
{
    return m_dt<m_maxDt ? m_dt : m_maxDt;
}

