#include "Time.h"

Time* Time::_instance = nullptr;

void Time::init()
{
	if (_instance)
		delete _instance;

	_instance = new Time();

	_instance->_deltaTime = 0.0f;
	_instance->_time = 0.0f;
}

void Time::release()
{
	delete _instance;
}

float Time::getDeltaTime()
{
	return _instance->_deltaTime;
}

float Time::getCurrentTime()
{
	return _instance->_time;
}

sf::Time Time::getClock()
{
	return _instance->_clock.getElapsedTime();
}

void Time::update()
{
	sf::Time time = _instance->_clock.restart();
	_instance->_time += time.asSeconds();
	_instance->_deltaTime = time.asSeconds();
}
