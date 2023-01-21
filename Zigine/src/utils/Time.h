#pragma once
#include "..\engine\Zigine.h"

class Time
{
public:
	static void init();
	static void relese();

	static float getDeltaTime();
	static float getCurrentTime();

	static void update();
private:
	static Time* _instance;

	float _deltaTime;
	float _time;
	sf::Clock _clock;
};