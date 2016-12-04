#include "Input.h"
Input::Input()
{
}

Input::~Input()
{
	clearMaps();
}

void Input::handleEvents(sf::RenderWindow& window)
{
	m_mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	sf::Event event;
	while (window.pollEvent(event))
	{
        for(auto& mapIterator : m_inputMap)
		{
            for(auto& definedIterator : mapIterator.second)
			{
                if(definedIterator.m_type == InputType::MISC)
				{
                    if(event.type == definedIterator.m_event)
					{
                        definedIterator.m_activated = true;
                    }
                }
                else if(definedIterator.m_type == InputType::KEY)
				{
                    if(event.type == sf::Event::KeyPressed)
					{
                        if(event.key.code == definedIterator.m_key)
						{
                            if(!definedIterator.m_activated)
							{
                                definedIterator.m_active = true;
                            }
                            definedIterator.m_activated = true;
                        }
                    }
                    if(event.type == sf::Event::KeyReleased)
					{
                        if(event.key.code == definedIterator.m_key)
						{
                            definedIterator.m_active = false;
                        }
                    }
                }
                else if(definedIterator.m_type == InputType::MOUSE_BUTTON)
				{
                    if(event.type == sf::Event::MouseButtonPressed)
					{
                        if(event.mouseButton.button == definedIterator.m_mouseButton)
						{
                            definedIterator.m_active = true;
                            definedIterator.m_activated = true;
                        }
                    }
                    if(event.type == sf::Event::MouseButtonReleased)
					{
                        if(event.mouseButton.button == definedIterator.m_mouseButton)
						{
                            definedIterator.m_active = false;
                        }
                    }
                }
                //MOUSE WHEEL INPUT NEEDS TESTING
                else if(definedIterator.m_type == InputType::MOUSE_WHEEL)
				{
                    if(event.type == sf::Event::MouseWheelScrolled)
					{
                        if(definedIterator.m_mouseWheelPositive)
						{
                            if(event.mouseWheelScroll.delta > 0)
							{
                                definedIterator.m_activated = true;
                            }
                        }
                        else
						{
                            if(event.mouseWheelScroll.delta < 0)
							{
                                definedIterator.m_activated = true;
                            }
                        }
                    }
                }
                else if(definedIterator.m_type == InputType::JOY_BUTTON)
				{
                    if(event.type == sf::Event::JoystickButtonPressed)
					{
                        if(event.joystickButton.button == definedIterator.m_joyButton)
						{
                            if(event.joystickButton.joystickId == definedIterator.m_joyNumber)
							{
                                definedIterator.m_active = true;
                                definedIterator.m_activated = true;
                            }
                        }
                    }
                    if(event.type == sf::Event::JoystickButtonReleased)
					{
                        if(event.joystickButton.button == definedIterator.m_joyButton)
						{
                            if(event.joystickButton.joystickId == definedIterator.m_joyNumber)
							{
                                definedIterator.m_active = false;
                            }
                        }
                    }
                }
                else if(definedIterator.m_type == InputType::JOY_AXIS_DIR)
				{
                    if(event.type == sf::Event::JoystickMoved)
					{
                        if(event.joystickMove.joystickId == definedIterator.m_joyNumber)
						{
                            if(event.joystickMove.axis == definedIterator.m_joyAxis)
							{
                                if(definedIterator.m_joyAxisPositive)
								{
                                    if(event.joystickMove.position > definedIterator.m_joyAxisDeadZone)
									{
                                        definedIterator.m_activated = true;
                                        definedIterator.m_active = true;
                                    }
                                    else
									{
                                        definedIterator.m_active = false;
                                    }
                                }
                                else
								{
                                    if(event.joystickMove.position < -definedIterator.m_joyAxisDeadZone)
									{
                                        definedIterator.m_activated = true;
                                        definedIterator.m_active = true;
                                    }
                                    else
									{
                                        definedIterator.m_active = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
		if (event.type == sf::Event::Resized)
		{
			sf::View view = window.getDefaultView();
			view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
			window.setView(view);
		}
	}
}

void Input::registerInput(std::string name, sf::Event::EventType _type){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_event = _type;
    newInput.m_type = InputType::MISC;
    m_inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, sf::Keyboard::Key _key){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_key = _key;
    newInput.m_type = InputType::KEY;
    m_inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, unsigned int joyNumber, sf::Joystick::Axis _axis, bool _positive, int _deadzone){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_joyNumber = joyNumber;
    newInput.m_joyAxis = _axis;
    newInput.m_joyAxisPositive = _positive;
    newInput.m_joyAxisDeadZone = _deadzone;
    newInput.m_type = InputType::JOY_AXIS_DIR;
    m_inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, unsigned int joyNumber, unsigned int button){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_joyNumber = joyNumber;
    newInput.m_joyButton = button;
    newInput.m_type = InputType::JOY_BUTTON;
    m_inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, sf::Mouse::Button _button){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_mouseButton = _button;
    newInput.m_type = InputType::MOUSE_BUTTON;
    m_inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, sf::Mouse::Wheel _wheel, bool positive){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_mouseWheel = _wheel;
    newInput.m_mouseWheelPositive = positive;
    newInput.m_type = InputType::MOUSE_WHEEL;
    m_inputMap[name].push_back(newInput);
}

void Input::registerAxis(std::string name, unsigned int joyNumber, sf::Joystick::Axis _axis, int _deadzone){
    InputDefinition newInput;
    newInput.m_activated = false;
    newInput.m_active = false;
    newInput.m_joyNumber = joyNumber;
    newInput.m_joyAxis = _axis;
    newInput.m_joyAxisDeadZone = _deadzone;
    newInput.m_type = InputType::JOY_AXIS;
    m_inputMap[name].push_back(newInput);
}

float Input::getAxisPosition(std::string name){
    for(auto& iterator : m_inputMap[name]){
        if(iterator.m_active && iterator.m_type == InputType::JOY_AXIS){
            float axisPosition = sf::Joystick::getAxisPosition(iterator.m_joyNumber, iterator.m_joyAxis);
            return axisPosition;
        }
    }
	return 0;
}

bool Input::getInputActive(std::string name){
    for(auto& iterator : m_inputMap[name]){
        if(iterator.m_active){
            return true;
        }
    }
	return false;
}

bool Input::getInputActivated(std::string name){
    for(auto& iterator : m_inputMap[name]){
        if(iterator.m_activated){
            return true;
        }
    }
	return false;
}

sf::Vector2f Input::getMousePosition()
{
	return m_mousePosition;
}

sf::Vector2f Input::getGlobalMousePosition()
{
	
	return sf::Vector2f(sf::Mouse::getPosition());
}

void Input::cleanEvents(){
	for (auto& mapIterator : m_inputMap){
        for (auto& definedIterator : mapIterator.second){
            definedIterator.m_activated = false;
        }
	}
}

void Input::clearMaps(){
	cleanEvents();
	for(auto& iterator : m_inputMap){
        iterator.second.clear();
	}
	m_inputMap.clear();
}
