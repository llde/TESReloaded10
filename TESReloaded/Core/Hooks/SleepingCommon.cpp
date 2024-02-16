#pragma once

bool Served = false;

void (__cdecl * ShowSleepWaitMenu)(bool) = (void (__cdecl *)(bool))Hooks::ShowSleepWaitMenu;
void __cdecl ShowSleepWaitMenuHook(bool IsSleeping) {
	
	bool Rest = false;
	UInt8 SitSleepState = Player->GetSitSleepState();
	UInt8 Mode = TheSettingManager->Config->SleepingMode.Mode;

	if (SitSleepState == HighProcess::SitSleep::kSitSleep_None && Mode == 0)
		Rest = true;
	else if (SitSleepState == HighProcess::SitSleep::kSitSleep_Sitting && (Mode == 0 || Mode == 2 || Mode == 3))
		Rest = true;
	else if (SitSleepState == HighProcess::SitSleep::kSitSleep_Sleeping && (Mode == 0 || Mode == 1 || Mode == 3))
		Rest = true;
	if (Rest)
		ShowSleepWaitMenu(SitSleepState == HighProcess::SitSleep::kSitSleep_Sleeping);
	else
		InterfaceManager->ShowMessage("You cannot rest now.");

}