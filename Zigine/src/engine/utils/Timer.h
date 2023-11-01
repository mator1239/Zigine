#ifndef _TIMER_H
#define _TIMER_H
#include <functional>

class Timer
{
public:
	void Create(float time, std::function<void()> callback);
	void Reset(float time = 0.0f, bool newTime = false);
	void Update();

	const inline float GetTime() const { return m_Time; }
private:
	std::function<void()> m_TimerCallback;
	float m_Time;
	float m_RealTime;
	bool m_IsStopped;
};

#endif // !_TIMER_H
