#pragma once

class FrameRateManager { // Never disposed
public:

	static void		Initialize();

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