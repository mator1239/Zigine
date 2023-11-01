#include "Timer.h"
#include "Time.h"

void Timer::Create(float time, std::function<void()> callback)
{
	m_RealTime = time;
	m_Time = time + Time::getCurrentTime();
	m_TimerCallback = callback;
}

void Timer::Reset(float time, bool newTime)
{
	if (time == 0.0f)
	{
		m_Time = m_RealTime + Time::getCurrentTime();
	}
	else
	{
		if (newTime)
			m_RealTime = time;

		m_Time = time + Time::getCurrentTime();
	}
}

void Timer::Update()
{
	if (m_IsStopped)
		return;

	if (m_Time < Time::getCurrentTime())
		m_TimerCallback();
}
