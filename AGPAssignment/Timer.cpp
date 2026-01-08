#include "Timer.h"
#include <chrono>

void Timer::Reset()
{
	elapsedTime = 0;
	deltaTime = 0.0f;
}

void Timer::Update()
{

}

Timer::Timer()
{
	Reset();
}
