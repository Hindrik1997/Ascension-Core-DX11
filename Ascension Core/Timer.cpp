//
// Created by Hindrik Stegenga on 7/28/2016.
//

#include "Timer.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Timer::Timer()
{
}


Timer::~Timer()
{
}

double Timer::FrameTimeCalculations()
{
	FrameCount++;
	if (GetTime() > 1.0f)
	{
		Fps = FrameCount;
		FrameCount = 0;
		StartTimer();
	}
	FrameTime = GetFrameTime();
	return FrameTime;
}

void Timer::StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	CountsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}

double Timer::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - CounterStart) / CountsPerSecond;
}

double Timer::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - FrameTimeOld;
	FrameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0;

	return double(tickCount) / CountsPerSecond;
}
