#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum class InputType
{
    NONE,
    MISC,
    JOY_AXIS,
    JOY_AXIS_DIR,
    JOY_BUTTON,
    KEY,
    MOUSE_BUTTON,
    MOUSE_WHEEL
};

struct InputDefinition{
    bool m_activated;
    bool m_active;
    InputType m_type;

    unsigned int m_joyNumber;
    sf::Event::EventType m_event;
    sf::Joystick::Axis m_joyAxis;
    bool m_joyAxisPositive;
    float m_joyAxisDeadZone;
    unsigned int m_joyButton;
    sf::Mouse::Wheel m_mouseWheel;
    bool m_mouseWheelPositive;
    sf::Mouse::Button m_mouseButton;
    sf::Keyboard::Key m_key;
};

class Input
{
protected:
	std::map< std::string, std::vector<InputDefinition> > m_inputMap;
public:
	Input();
	~Input();
	void handleEvents(sf::RenderWindow& _window);
	void cleanEvents();
	void clearMaps();

	void registerInput(std::string name, sf::Event::EventType _type);
	void registerInput(std::string name, sf::Keyboard::Key _key);
	void registerInput(std::string name, unsigned int _joyNumber, sf::Joystick::Axis _axis, bool _positive, int _deadzone = 0);
	void registerInput(std::string name, unsigned int _joyNumber, unsigned int _button);
	void registerInput(std::string name, sf::Mouse::Button _button);
	void registerInput(std::string name, sf::Mouse::Wheel _wheel, bool _positive);
	void registerAxis(std::string name, unsigned int _joyNumber, sf::Joystick::Axis _axis, int _deadzone = 0);

	float getAxisPosition(std::string _name);
	bool getInputActive(std::string _name);
	bool getInputActivated(std::string _name);
};
