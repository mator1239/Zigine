#include "Time.h"

Time* Time::_instance = nullptr;

void Time::init()
{
	if (_instance)
		delete _instance;

	_instance = new Time;
}

void Time::relese()
{
	delete _instance;
	_instance = nullptr;
}

float Time::getDeltaTime()
{
	return _instance->_deltaTime;
}

float Time::getCurrentTime()
{
	return _instance->_time;
}

void Time::update()
{
	sf::Time time = _instance->_clock.restart();
	_instance->_deltaTime = time.asSeconds();
}
