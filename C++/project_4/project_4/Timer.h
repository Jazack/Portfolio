#ifndef __TIMER_H__
#define __TIMER_H__
#include <chrono>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void Start();
	void End();
	unsigned DurationInNanoSeconds();
	unsigned DurationInMicroSeconds();
	unsigned DurationInMilliSeconds();

private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
};
#endif
