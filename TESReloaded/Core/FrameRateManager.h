#pragma once

class FrameRateManager { // Never disposed
public:
	FrameRateManager();

	void			UpdatePerformance();
	double			GetPerformance();
	void			PerformSync();

	LONGLONG		PerformanceFrequency;
	LONGLONG		PerformanceCounterStart;
	double			Time;
	double			LastTime;
	double			ElapsedTime;
	double			SmartControlMPF;
	double			LastPerformance;
};

void CreateFrameRateHook();