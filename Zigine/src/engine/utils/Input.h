#ifndef _INPUT_H
#define _INPUT_H
#include "engine/Zigine.h"
#include "engine/Renderer.h"
#include <unordered_map>

class Input
{
public:
	static void init();
	static void release();

	static void update(sf::Event& event);

	static bool isMouseButtonDown(sf::Mouse::Button button)
	{
		return (_instance->_mouseStates[button] &&
			_instance->_mouseStates[button] != _instance->_prevMouseStates[button]);
	}

	static bool isMouseButtonUp(sf::Mouse::Button button)
	{
		return (!_instance->_mouseStates[button] &&
			_instance->_mouseStates[button] == _instance->_prevMouseStates[button]);
	}

	static vector2i getPosition() 
	{ 
		vector2i mousePosition = sf::Mouse::getPosition(*Renderer::getWindow());
		vector2 worldPosition = Renderer::mapPixelToCoords(mousePosition);
		return { static_cast<int>(worldPosition.x), 
			static_cast<int>(worldPosition.y) };
	}
private:
	static Input* _instance;

	std::unordered_map<sf::Mouse::Button, bool> _mouseStates;
	std::unordered_map<sf::Mouse::Button, bool> _prevMouseStates;
};

#endif // !_INPUT_H
