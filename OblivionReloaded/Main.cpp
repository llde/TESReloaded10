#define WaitForDebugger 0
#define HookDevice 0

#include "Hooks/Oblivion/Hooks.h"
#include "D3D9/Hook.h"

extern "C" {

	bool OBSEPlugin_Query(const PluginInterface* Interface, PluginInfo* Info) {

		Info->InfoVersion = PluginInfo::kInfoVersion;
		Info->Name = "OblivionReloaded";
		Info->Version = 10;
		return true;

	}

	bool OBSEPlugin_Load(const PluginInterface* Interface) {

#if _DEBUG
	#if WaitForDebugger
		while (!IsDebuggerPresent()) Sleep(10);
	#endif
	#if HookDevice
		CreateD3D9Hook();
	#endif
#endif

		Logger::Initialize("OblivionReloaded.log");
		CommandManager::Initialize(Interface);

		if (!Interface->IsEditor) {
			PluginVersion::CreateVersionString();
			SettingManager::Initialize();
			if (TheSettingManager->LoadSettings(true)) {
				AttachHooks();
			}
			else {

			}
		}
		else {
			CreateEditorShadowsHook();
		}
		return true;

	}

};