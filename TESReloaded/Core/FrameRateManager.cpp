void FrameRateManager::Initialize() {

	Logger::Log("Starting the framerate manager...");
	TheFrameRateManager = new FrameRateManager();
	
	LARGE_INTEGER Frequency;
	LARGE_INTEGER PerformanceCounter;
	
	TheFrameRateManager->Time = 0.0;
	TheFrameRateManager->LastTime = 0.0;
	TheFrameRateManager->ElapsedTime = 0.0;
	TheFrameRateManager->LastPerformance = 0.0;
#ifdef EXPERIMENTAL_FEATURE

	TheFrameRateManager->SmartControlMPF = 1000.0 / TheSettingManager->Config->FrameRate.SmartControlFPS;
#endif
	QueryPerformanceFrequency(&Frequency); TheFrameRateManager->PerformanceFrequency = Frequency.QuadPart;
	QueryPerformanceCounter(&PerformanceCounter); TheFrameRateManager->PerformanceCounterStart = PerformanceCounter.QuadPart;

}

void FrameRateManager::UpdatePerformance() {
	
	LARGE_INTEGER PerformanceCounterEnd;
	
	QueryPerformanceCounter(&PerformanceCounterEnd);
	Time = (double)(PerformanceCounterEnd.QuadPart - PerformanceCounterStart) / (double)PerformanceFrequency;
	ElapsedTime = Time - LastTime;
	LastTime = Time;

}

double FrameRateManager::GetPerformance() {

	LARGE_INTEGER PerformanceCounterEnd;

	QueryPerformanceCounter(&PerformanceCounterEnd);
	return (double)(PerformanceCounterEnd.QuadPart - TheFrameRateManager->PerformanceCounterStart) * 1000.0 / (double)TheFrameRateManager->PerformanceFrequency;

}

void FrameRateManager::PerformSync() {

	double CurrentPerformance = GetPerformance();
	double FrameTime = CurrentPerformance - LastPerformance;
	float NMPF = 0.0f;

	*Pointers::Generic::MPF = NMPF;
	if (FrameTime < SmartControlMPF) Sleep(SmartControlMPF - FrameTime);
	LastPerformance = GetPerformance();
#ifdef EXPERIMENTAL_FEATURE
	NMPF = (float)(FrameTime + TheSettingManager->Config->FrameRate.FlowControl + (LastPerformance - CurrentPerformance));
#endif
	if (NMPF >= 10.0f && NMPF <= 120.0f) *Pointers::Generic::MPF = NMPF;
	
}