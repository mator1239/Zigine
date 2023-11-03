#pragma once
#include "engine\Zigine.h"

class Time
{
public:
	static void Init();
	static void Release();
	static void Update();

	static float GetDeltaTime();
	static float GetTime();
	static sf::Time GetClock();
private:
	static Time* m_Instance;

	float m_DeltaTime;
	float m_Time;
	sf::Clock m_Clock;
};