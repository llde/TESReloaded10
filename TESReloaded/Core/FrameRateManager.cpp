#include "FrameRateManager.h"

#if defined(OBLIVION)
static const UInt32 TimeInfoUpdate = 0x0047D170;
static const UInt32 kUpdateTimeInfoHook = 0x0040D8AB;
static const UInt32 kUpdateTimeInfoReturn = 0x0040D8B0;
static float* MPF = (float*)0x00B33E94;
#endif

FrameRateManager::FrameRateManager() {

	Logger::Log("Starting the framerate manager...");
	TheFrameRateManager = this;
	
	LARGE_INTEGER Frequency;
	LARGE_INTEGER PerformanceCounter;
	
	Time = 0.0;
	LastTime = 0.0;
	ElapsedTime = 0.0;
	LastPerformance = 0.0;
	SmartControlMPF = 1000.0 / TheSettingManager->SettingsMain.FrameRate.SmartControlFPS;
	QueryPerformanceFrequency(&Frequency); PerformanceFrequency = Frequency.QuadPart;
	QueryPerformanceCounter(&PerformanceCounter); PerformanceCounterStart = PerformanceCounter.QuadPart;

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

	*MPF = NMPF;
	if (FrameTime < SmartControlMPF) Sleep(SmartControlMPF - FrameTime);
	LastPerformance = GetPerformance();
	NMPF = (float)(FrameTime + TheSettingManager->SettingsMain.FrameRate.FlowControl + (LastPerformance - CurrentPerformance));
	if (NMPF >= 10.0f && NMPF <= 120.0f) *MPF = NMPF;
	
}

static __declspec(naked) void UpdateTimeInfoHook() {

	__asm {
		pushad
		mov		ecx, TheFrameRateManager
		call	FrameRateManager::PerformSync
		popad
		call	TimeInfoUpdate
		jmp		kUpdateTimeInfoReturn
	}

}

void EndProcess() {
	
	void* SettingCollection = (void*)0x00B07BF0;
	char* SettingName = (char*)0x00B07BF4;

	ThisCall(0x0040C180, SettingCollection, SettingName);
	TerminateProcess(GetCurrentProcess(), 0);

}

void CreateFrameRateHook() {
	
	SettingsMainStruct::FrameRateStruct* FrameRate = &TheSettingManager->SettingsMain.FrameRate;
	
	if (FrameRate->SmartControl) SafeWriteJump(kUpdateTimeInfoHook,	(UInt32)UpdateTimeInfoHook);
	if (FrameRate->SmartBackgroundProcess) {
		SafeWriteJump(0x00701739, 0x00701748); // Skips init	 SourceDataCriticalSection (NiRenderer::New)
		SafeWriteJump(0x00763565, 0x0076357F); // Skips entering SourceDataCriticalSection (NiRenderer::CreateSourceTextureRendererData)
		SafeWriteJump(0x00763596, 0x007635AA); // Skips leaving	 SourceDataCriticalSection (NiRenderer::CreateSourceTextureRendererData)
		SafeWriteJump(0x007635C4, 0x007635DE); // Skips entering SourceDataCriticalSection (NiRenderer::CreateSourceCubeMapRendererData)
		SafeWriteJump(0x007635FB, 0x0076360F); // Skips leaving	 SourceDataCriticalSection (NiRenderer::CreateSourceCubeMapRendererData)
		SafeWrite8(0x007635F9, 0x8B); // Patches the NiRenderer::CreateSourceCubeMapRendererData
		SafeWrite8(0x007635FA, 0xF8); // Patches the NiRenderer::CreateSourceCubeMapRendererData
		SafeWriteJump(0x0077ACBF, 0x0077ACD9); // Skips entering SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AD08, 0x0077AD1C); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AD52, 0x0077AD66); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrepareTextureForRendering)
		SafeWriteJump(0x0077AE2A, 0x0077AE44); // Skips entering SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
		SafeWriteJump(0x0077AE6C, 0x0077AE80); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
		SafeWriteJump(0x0077AEAF, 0x0077AEC3); // Skips leaving	 SourceDataCriticalSection (NiDX9TextureManager::PrecacheTexture)
	}

	SafeWriteJump(0x0040F488, (UInt32)EndProcess);

}