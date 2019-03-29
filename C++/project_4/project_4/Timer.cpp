#include "Timer.h"
#include <chrono>


void Timer::Start()
{
	start = std::chrono::high_resolution_clock::now();
}

void Timer::End()
{
	end = std::chrono::high_resolution_clock::now();
}

unsigned Timer::DurationInNanoSeconds()
{
	using std::chrono::duration_cast;
	using std::chrono::nanoseconds;
	return duration_cast<nanoseconds>(end - start).count();
}

unsigned Timer::DurationInMicroSeconds()
{
	using std::chrono::duration_cast;
	using std::chrono::microseconds;
	return duration_cast<microseconds>(end - start).count();
}

unsigned Timer::DurationInMilliSeconds()
{
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	return duration_cast<milliseconds>(end - start).count();
}
