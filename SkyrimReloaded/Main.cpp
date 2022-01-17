#define WaitForDebugger 0
#define HookDevice 0

#include "Hooks/Skyrim/Hooks.h"
#include "Device/Hook.h"

extern "C" {

	bool SKSEPlugin_Query(const PluginInterface* Interface, PluginInfo* Info) {
		
		Info->InfoVersion = PluginInfo::kInfoVersion;
		Info->Name = "SkyrimReloaded";
		Info->Version = 5;
		return true;

	}

	bool SKSEPlugin_Load(const PluginInterface* Interface) {

#if _DEBUG
	#if WaitForDebugger
		while (!IsDebuggerPresent()) Sleep(10);
	#endif
	#if HookDevice
		AttachDeviceHooks();
	#endif
#endif

		Logger::Initialize("SkyrimReloaded.log");
		CommandManager::Initialize(Interface);

		if (!Interface->IsEditor) {
			PluginVersion::CreateVersionString();
			SettingManager::Initialize();
			if (TheSettingManager->LoadSettings(true)) {
				AttachHooks();
			}
			else {
				char Error[160];
				sprintf(Error, "CRITICAL ERROR: Cannot find the config file.");
				Logger::Log(Error);
				MessageBoxA(NULL, Error, PluginVersion::VersionString, MB_ICONERROR | MB_OK);
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}
		return true;

	}

};