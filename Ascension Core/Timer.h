//
// Created by Hindrik Stegenga on 7/28/2016.
//

#ifndef ASCENSION_CORE_TIMER_H
#define ASCENSION_CORE_TIMER_H

class Timer
{
public:
	Timer();
	~Timer();

	double CountsPerSecond = 0.0;
	__int64 CounterStart = 0;
	int FrameCount = 0;
	int Fps = 0;

	__int64 FrameTimeOld = 0;
	double FrameTime;

	double FrameTimeCalculations();
	void StartTimer();
	double GetTime();
	double GetFrameTime();
};

#endif