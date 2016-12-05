#include "InitState.h"
#include <time.h>
#include "PlayerObject.h"
#include "TestGunObject.h"
#include "TestBulletObject.h"

InitState::InitState(GameState * _nextState)
{
	m_name = "Init State";
	m_nextState = _nextState;
}

void InitState::initialise(const GameInfo & _info)
{
	srand(time(NULL));

	_info.m_textureFactory->setLoaderFunc(
		[](std::string _file)
		{
			sf::Texture* tex = new sf::Texture;
			tex->loadFromFile("res/" + _file + ".png");
			tex->setSmooth(false);
			return tex;
		}
	);
	_info.m_textureFactory->setDeleterFunc(
		[](sf::Texture* _asset)
		{
			delete _asset;
		}
	);

	_info.m_input->registerInput("exit", sf::Event::Closed);
	_info.m_input->registerInput("exit", sf::Keyboard::Escape);

	_info.m_input->registerInput("leftClick", sf::Mouse::Left);
	_info.m_input->registerInput("rightClick", sf::Mouse::Right);

	_info.m_input->registerInput("p1right", sf::Keyboard::D);
	_info.m_input->registerInput("p1left", sf::Keyboard::A);
	_info.m_input->registerInput("p1up", sf::Keyboard::W);
	_info.m_input->registerInput("p1down", sf::Keyboard::S);
	_info.m_input->registerInput("p1l1", sf::Mouse::Left);
	_info.m_input->registerInput("p1l2", sf::Keyboard::Q);
	_info.m_input->registerInput("p1r1", sf::Mouse::Right);
	_info.m_input->registerInput("p1r2", sf::Keyboard::E);
	

	_info.m_objectFactory->addCreator("player", 
		[]()
		{
			return (GameObject*)(new PlayerObject);
		}
	);
	_info.m_objectFactory->addCreator("TestGunObject",
		[]()
		{
			return (GameObject*)(new TestGunObject);
		}
	);
	_info.m_objectFactory->addCreator("TestBulletObject",
		[]()
		{
			return (GameObject*)(new TestBulletObject);
		}
	);
}
