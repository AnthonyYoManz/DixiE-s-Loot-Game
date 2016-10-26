#ifndef ANT_INPUT

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum InputType{
    INPUT_TYPE_NONE,
    INPUT_TYPE_MISC,
    INPUT_TYPE_JOY_AXIS,
    INPUT_TYPE_JOY_AXIS_DIR,
    INPUT_TYPE_JOY_BUTTON,
    INPUT_TYPE_KEY,
    INPUT_TYPE_MOUSE_BUTTON,
    INPUT_TYPE_MOUSE_WHEEL
};

struct InputDefinition{
    bool activated;
    bool active;
    InputType type;

    unsigned int joyNumber;
    sf::Event::EventType event;
    sf::Joystick::Axis joyAxis;
    bool joyAxisPositive;
    float joyAxisDeadZone;
    unsigned int joyButton;
    sf::Mouse::Wheel mouseWheel;
    bool mouseWheelPositive;
    sf::Mouse::Button mouseButton;
    sf::Keyboard::Key key;
};

class Input{
	protected:
		std::map< std::string, std::vector<InputDefinition> > inputMap;
	public:
		void handleEvents(sf::RenderWindow& window);
		void cleanEvents();
		void clearMaps();

		void registerInput(std::string name, sf::Event::EventType _type);
        void registerInput(std::string name, sf::Keyboard::Key _key);
        void registerInput(std::string name, unsigned int joyNumber, sf::Joystick::Axis _axis, bool _positive, int _deadzone = 0);
        void registerInput(std::string name, unsigned int joyNumber, unsigned int button);
        void registerInput(std::string name, sf::Mouse::Button _button);
        void registerInput(std::string name, sf::Mouse::Wheel _wheel, bool positive);
        void registerAxis(std::string name, unsigned int joyNumber, sf::Joystick::Axis _axis, int _deadzone = 0);

        float getAxisPosition(std::string name);
        bool getInputActive(std::string name);
        bool getInputActivated(std::string name);
};

#define ANT_INPUT
#endif // ANT_INPUT
