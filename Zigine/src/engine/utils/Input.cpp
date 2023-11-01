#include "Input.h"

Input* Input::_instance = nullptr;

void Input::init()
{
	if (_instance)
		delete _instance;

	_instance = new Input;
}

void Input::release()
{
	delete _instance;
	_instance = nullptr;
}

void Input::update(sf::Event& event)
{
	_instance->_prevMouseStates = _instance->_mouseStates;

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Left:
			_instance->_mouseStates[sf::Mouse::Left] = true;
			break;
		case sf::Mouse::Right:
			_instance->_mouseStates[sf::Mouse::Right] = true;

			break;
		case sf::Mouse::Middle:
			_instance->_mouseStates[sf::Mouse::Middle] = true;
			break;
		}
		break;
	case sf::Event::MouseButtonReleased:
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Left:
			_instance->_mouseStates[sf::Mouse::Left] = false;
			break;
		case sf::Mouse::Right:
			_instance->_mouseStates[sf::Mouse::Right] = false;
			break;
		case sf::Mouse::Middle:
			_instance->_mouseStates[sf::Mouse::Middle] = false;
			break;
		}
		break;
	}
}
