#include "SleepingMode.h"

#if defined(OBLIVION)
#define kMessageBoxServeSentenceText 0x00B38B30
#define kMessageBoxButtonYes 0x00B38CF8
#define kMessageBoxButtonNo 0x00B38D00
#define kShowSleepWaitMenu 0x0057B420
#define SleepingState 9
#elif defined(SKYRIM)
#define kMessageBoxServeSentenceText 0x01B19068
#define kMessageBoxButtonYes 0x01B17FA0
#define kMessageBoxButtonNo 0x01B17FAC
#define kShowSleepWaitMenu 0x00887B20
#define SleepingState 7
#endif

static const char** MessageBoxServeSentenceText = (const char**)kMessageBoxServeSentenceText;
static const char** MessageBoxButtonYes = (const char**)kMessageBoxButtonYes;
static const char** MessageBoxButtonNo = (const char**)kMessageBoxButtonNo;
static bool Served = false;

class SleepingMode {
public:
#if defined(OBLIVION)
	int TrackServeSentence();
	bool TrackRemoveWornItems(Actor*, UInt8, int);
#elif defined(SKYRIM)
	int TrackServeSentence();
	void TrackSetFurnitureCameraState(TESFurniture*);
	int TrackProcessSleepWaitMenu(UInt32);
#endif
};

#if defined(OBLIVION)
int (__thiscall SleepingMode::* ServeSentence)();
int (__thiscall SleepingMode::* TrackServeSentence)();
int SleepingMode::TrackServeSentence() {

	TheCameraManager->ResetCamera();
	Player->unk61C = 0.0f;
	Player->Resurrect(0, 0, 0);
	return (this->*ServeSentence)();

}

bool (__thiscall SleepingMode::* RemoveWornItems)(Actor*, UInt8, int);
bool (__thiscall SleepingMode::* TrackRemoveWornItems)(Actor*, UInt8, int);
bool SleepingMode::TrackRemoveWornItems(Actor* Act, UInt8 Arg2, int Arg3) {
	
	if (Act == Player) return 1;
	return (this->*RemoveWornItems)(Act, Arg2, Arg3);

}

bool (__cdecl* ProcessSleepWaitMenu)() = (bool (__cdecl*)())0x005D7090;
bool __cdecl TrackProcessSleepWaitMenu() {

	if (Player->JailedState && Player->isSleeping) Served = true;
	return ProcessSleepWaitMenu();

}

void (__cdecl* CloseSleepWaitMenu)() = (void (__cdecl*)())0x005D6A10;
void __cdecl TrackCloseSleepWaitMenu() {

	CloseSleepWaitMenu();
	if (Served) {
		Served = false;
		InterfaceManager->ShowMessageBox(*MessageBoxServeSentenceText, (void*)0x00671600, *MessageBoxButtonYes, *MessageBoxButtonNo);
	}

}
#elif defined(SKYRIM)
int (__thiscall SleepingMode::* ServeSentence)();
int (__thiscall SleepingMode::* TrackServeSentence)();
int SleepingMode::TrackServeSentence() {

	Player->RestoreCamera();
	return (this->*ServeSentence)();

}

void (__thiscall SleepingMode::* SetFurnitureCameraState)(TESFurniture*);
void (__thiscall SleepingMode::* TrackSetFurnitureCameraState)(TESFurniture*);
void SleepingMode::TrackSetFurnitureCameraState(TESFurniture* Furniture) {

	PlayerCamera* Camera = (PlayerCamera*)this;
	UInt8 SitSleepState = Player->GetSitSleepState();

	if (SitSleepState == 7 && Camera->cameraState->stateId == TESCameraState::CameraState::kCameraState_Furniture) Player->QueueNiNodeUpdate();
	(this->*SetFurnitureCameraState)(Furniture);

}

int (__thiscall SleepingMode::* ProcessSleepWaitMenu)(UInt32);
int (__thiscall SleepingMode::* TrackProcessSleepWaitMenu)(UInt32);
int SleepingMode::TrackProcessSleepWaitMenu(UInt32 Arg1) {
	
	bool IsPlayerSleeping = Player->flags725 & 4;

	if (Player->JailedState && IsPlayerSleeping) Served = true;
	bool r = (this->*ProcessSleepWaitMenu)(Arg1);
	if (Served && !IsPlayerSleeping) {
		Served = false;
		MenuManager->ShowMessageBox(*MessageBoxServeSentenceText, (void*)0x00499D70, *MessageBoxButtonYes, *MessageBoxButtonNo);
	}
	return r;

}
#endif

void (__cdecl * ShowSleepWaitMenu)(bool) = (void (__cdecl *)(bool))kShowSleepWaitMenu;
void __cdecl TrackShowSleepWaitMenu(bool IsSleeping) {
	
	bool Rest = false;
	UInt8 SitSleepState = Player->GetSitSleepState();
	UInt8 Mode = TheSettingManager->SettingsMain.SleepingMode.Mode;

	if (SitSleepState == 0 && Mode == 0)
		Rest = true;
	else if (SitSleepState == 4 && (Mode == 0 || Mode == 2 || Mode == 3))
		Rest = true;
	else if (SitSleepState == 9 && (Mode == 0 || Mode == 1 || Mode == 3))
		Rest = true;
	if (Rest)
		ShowSleepWaitMenu(SitSleepState == SleepingState);
	else
		InterfaceManager->ShowMessage("You cannot rest now.");

}

void CreateSleepingModeHook() {

	if (TheSettingManager->SettingsMain.SleepingMode.Enabled) {
#if defined(OBLIVION)
		*((int *)&RemoveWornItems)				= 0x0064BAC0;
		TrackRemoveWornItems					= &SleepingMode::TrackRemoveWornItems;
		*((int *)&ServeSentence)				= 0x00670700;
		TrackServeSentence						= &SleepingMode::TrackServeSentence;
#elif defined (SKYRIM)
		*((int *)&SetFurnitureCameraState)		= 0x0083D6E0;
		TrackSetFurnitureCameraState			= &SleepingMode::TrackSetFurnitureCameraState;
		*((int *)&ProcessSleepWaitMenu)			= 0x00887F90;
		TrackProcessSleepWaitMenu				= &SleepingMode::TrackProcessSleepWaitMenu;
		*((int *)&ServeSentence)				= 0x0074B7E0;
		TrackServeSentence						= &SleepingMode::TrackServeSentence;
#endif

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
#if defined(OBLIVION)
		DetourAttach(&(PVOID&)RemoveWornItems,			*((PVOID *)&TrackRemoveWornItems));
		DetourAttach(&(PVOID&)ServeSentence,			*((PVOID *)&TrackServeSentence));
		DetourAttach(&(PVOID&)ProcessSleepWaitMenu,				   &TrackProcessSleepWaitMenu);
		DetourAttach(&(PVOID&)CloseSleepWaitMenu,				   &TrackCloseSleepWaitMenu);
#elif defined(SKYRIM)
		DetourAttach(&(PVOID&)SetFurnitureCameraState,	*((PVOID *)&TrackSetFurnitureCameraState));
		DetourAttach(&(PVOID&)ProcessSleepWaitMenu,		*((PVOID *)&TrackProcessSleepWaitMenu));
		DetourAttach(&(PVOID&)ServeSentence,			*((PVOID *)&TrackServeSentence));
#endif
		DetourAttach(&(PVOID&)ShowSleepWaitMenu,				   &TrackShowSleepWaitMenu);
		DetourTransactionCommit();

#if defined(OBLIVION)
		SafeWriteJump(0x004AEA1C, 0x004AEAEE); // Enables the Player to get into the bed
		SafeWriteJump(0x004AE961, 0x004AEAEE); // Enables the Player to get into the bed when in prison
		SafeWriteJump(0x00672BFF, 0x00672C18); // Enables the rest key when in prison
#elif defined(SKYRIM)
		SafeWriteJump(0x0049A351, 0x0049A367); // Enables the Player to get into the bed
		SafeWriteJump(0x0049A30F, 0x0049A367); // Enables the Player to get into the bed when in prison
#endif
	}

}