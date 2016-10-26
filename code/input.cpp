#include "Input.h"
void Input::handleEvents(sf::RenderWindow& window){
	sf::Event event;
	while (window.pollEvent(event)){
        for(auto& mapIterator : inputMap){
            for(auto& definedIterator : mapIterator.second){
                if(definedIterator.type == INPUT_TYPE_MISC){
                    if(event.type == definedIterator.event){
                        definedIterator.activated = true;
                    }
                }
                else if(definedIterator.type == INPUT_TYPE_KEY){
                    if(event.type == sf::Event::KeyPressed){
                        if(event.key.code == definedIterator.key){
                            if(!definedIterator.activated){
                                definedIterator.active = true;
                            }
                            definedIterator.activated = true;
                        }
                    }
                    if(event.type == sf::Event::KeyReleased){
                        if(event.key.code == definedIterator.key){
                            definedIterator.active = false;
                        }
                    }
                }
                else if(definedIterator.type == INPUT_TYPE_MOUSE_BUTTON){
                    if(event.type == sf::Event::MouseButtonPressed){
                        if(event.mouseButton.button == definedIterator.mouseButton){
                            definedIterator.active = true;
                            definedIterator.activated = true;
                        }
                    }
                    if(event.type == sf::Event::MouseButtonReleased){
                        if(event.mouseButton.button == definedIterator.mouseButton){
                            definedIterator.active = false;
                        }
                    }
                }
                //MOUSE WHEEL INPUT NEEDS TESTING
                else if(definedIterator.type == INPUT_TYPE_MOUSE_WHEEL){
                    if(event.type == sf::Event::MouseWheelScrolled){
                        if(definedIterator.mouseWheelPositive){
                            if(event.mouseWheelScroll.delta > 0){
                                definedIterator.activated = true;
                            }
                        }
                        else{
                            if(event.mouseWheelScroll.delta < 0){
                                definedIterator.activated = true;
                            }
                        }
                    }
                }
                else if(definedIterator.type == INPUT_TYPE_JOY_BUTTON){
                    if(event.type == sf::Event::JoystickButtonPressed){
                        if(event.joystickButton.button == definedIterator.joyButton){
                            if(event.joystickButton.joystickId == definedIterator.joyNumber){
                                definedIterator.active = true;
                                definedIterator.activated = true;
                            }
                        }
                    }
                    if(event.type == sf::Event::JoystickButtonReleased){
                        if(event.joystickButton.button == definedIterator.joyButton){
                            if(event.joystickButton.joystickId == definedIterator.joyNumber){
                                definedIterator.active = false;
                            }
                        }
                    }
                }
                else if(definedIterator.type == INPUT_TYPE_JOY_AXIS_DIR){
                    if(event.type == sf::Event::JoystickMoved){
                        if(event.joystickMove.joystickId == definedIterator.joyNumber){
                            if(event.joystickMove.axis == definedIterator.joyAxis){
                                if(definedIterator.joyAxisPositive){
                                    if(event.joystickMove.position > definedIterator.joyAxisDeadZone){
                                        definedIterator.activated = true;
                                        definedIterator.active = true;
                                    }
                                    else{
                                        definedIterator.active = false;
                                    }
                                }
                                else{
                                    if(event.joystickMove.position < -definedIterator.joyAxisDeadZone){
                                        definedIterator.activated = true;
                                        definedIterator.active = true;
                                    }
                                    else{
                                        definedIterator.active = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
	}
}

void Input::registerInput(std::string name, sf::Event::EventType _type){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.event = _type;
    newInput.type = INPUT_TYPE_MISC;
    inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, sf::Keyboard::Key _key){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.key = _key;
    newInput.type = INPUT_TYPE_KEY;
    inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, unsigned int joyNumber, sf::Joystick::Axis _axis, bool _positive, int _deadzone){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.joyNumber = joyNumber;
    newInput.joyAxis = _axis;
    newInput.joyAxisPositive = _positive;
    newInput.joyAxisDeadZone = _deadzone;
    newInput.type = INPUT_TYPE_JOY_AXIS_DIR;
    inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, unsigned int joyNumber, unsigned int button){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.joyNumber = joyNumber;
    newInput.joyButton = button;
    newInput.type = INPUT_TYPE_JOY_BUTTON;
    inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, sf::Mouse::Button _button){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.mouseButton = _button;
    newInput.type = INPUT_TYPE_MOUSE_BUTTON;
    inputMap[name].push_back(newInput);
}

void Input::registerInput(std::string name, sf::Mouse::Wheel _wheel, bool positive){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.mouseWheel = _wheel;
    newInput.mouseWheelPositive = positive;
    newInput.type = INPUT_TYPE_MOUSE_WHEEL;
    inputMap[name].push_back(newInput);
}

void Input::registerAxis(std::string name, unsigned int joyNumber, sf::Joystick::Axis _axis, int _deadzone){
    InputDefinition newInput;
    newInput.activated = false;
    newInput.active = false;
    newInput.joyNumber = joyNumber;
    newInput.joyAxis = _axis;
    newInput.joyAxisDeadZone = _deadzone;
    newInput.type = INPUT_TYPE_JOY_AXIS;
    inputMap[name].push_back(newInput);
}

float Input::getAxisPosition(std::string name){
    for(auto& iterator : inputMap[name]){
        if(iterator.active && iterator.type == INPUT_TYPE_JOY_AXIS){
            float axisPosition = sf::Joystick::getAxisPosition(iterator.joyNumber, iterator.joyAxis);
            return axisPosition;
        }
    }
	return 0;
}

bool Input::getInputActive(std::string name){
    for(auto& iterator : inputMap[name]){
        if(iterator.active){
            return true;
        }
    }
	return false;
}

bool Input::getInputActivated(std::string name){
    for(auto& iterator : inputMap[name]){
        if(iterator.activated){
            return true;
        }
    }
	return false;
}

void Input::cleanEvents(){
	for (auto& mapIterator : inputMap){
        for (auto& definedIterator : mapIterator.second){
            definedIterator.activated = false;
        }
	}
}

void Input::clearMaps(){
	cleanEvents();
	for(auto& iterator : inputMap){
        iterator.second.clear();
	}
	inputMap.clear();
}
