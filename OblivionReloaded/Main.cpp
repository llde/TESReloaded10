#define WaitForDebugger 0
#define HookDevice 0
#undef EXPERIMENTAL_FEATURE

#include "Hooks/Oblivion/Hooks.h"
#include "Device/Hook.h"

extern "C" {

	bool OBSEPlugin_Query(const PluginInterface* Interface, PluginInfo* Info) {

		Info->InfoVersion = PluginInfo::kInfoVersion;
		Info->Name = "OblivionReloaded";
		Info->Version = 11;
		return true;

	}

	bool OBSEPlugin_Load(const PluginInterface* Interface) {

#if _DEBUG
	#if WaitForDebugger
		while (!IsDebuggerPresent()) Sleep(10);
	#endif
#endif
#if HookDevice
		AttachDeviceHooks();
#endif

		Logger::Initialize("OblivionReloaded.log");
		CommandManager::Initialize(Interface);

		if (!Interface->IsEditor) {
			PluginVersion::CreateVersionString();
			SettingManager::Initialize();
			TheSettingManager->SetGame(ffi::Game::Oblivion);
			TheSettingManager->LoadSettings();
			DebugManager::Initialize(Interface);
			AttachHooks();
		}
		else {
			AttachEditorHooks();
		}
		return true;

	}

};