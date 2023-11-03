#include "Time.h"

Time* Time::m_Instance = nullptr;

void Time::Init()
{
	if (m_Instance)
		delete m_Instance;

	m_Instance = new Time();

	m_Instance->m_DeltaTime = 0.0f;
	m_Instance->m_Time = 0.0f;
}

void Time::Release()
{
	delete m_Instance;
}

float Time::GetDeltaTime()
{
	return m_Instance->m_DeltaTime;
}

float Time::GetTime()
{
	return m_Instance->m_Time;
}

sf::Time Time::GetClock()
{
	return m_Instance->m_Clock.getElapsedTime();
}

void Time::Update()
{
	sf::Time time = m_Instance->m_Clock.restart();
	m_Instance->m_Time += time.asSeconds();
	m_Instance->m_DeltaTime = time.asSeconds();
}
