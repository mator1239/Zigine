#pragma once
#include "engine\Zigine.h"

class Time
{
public:
	static void init();
	static void release();
	static void update();

	static float getDeltaTime();
	static float getCurrentTime();
	static sf::Time getClock();
private:
	static Time* _instance;

	float _deltaTime;
	float _time;
	sf::Clock _clock;
};