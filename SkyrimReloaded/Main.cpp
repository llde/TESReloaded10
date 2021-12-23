#define WaitForDebugger 0

#include "RenderHook.h"
#include "ShaderIOHook.h"
#include "FormHook.h"
#include "CameraMode.h"
#include "SleepingMode.h"
#include "PluginVersion.h"
#include "D3D9Hook.h"

extern "C" {

	bool SKSEPlugin_Query(const PluginInterface* Interface, PluginInfo* Info) {
		
		Info->InfoVersion = PluginInfo::kInfoVersion;
		Info->Name = "SkyrimReloaded";
		Info->Version = 4;
		return true;

	}

	bool SKSEPlugin_Load(const PluginInterface* Interface) {

#if WaitForDebugger
		while (!IsDebuggerPresent()) Sleep(10);
#endif
		Logger::CreateLog("SkyrimReloaded.log");
		new CommandManager();
		TheCommandManager->AddCommands(Interface);

		if (!Interface->IsEditor) {
			PluginVersion::CreateVersionString();
			new SettingManager();
			TheSettingManager->LoadSettings();
			PerformGameInitialization();
			CreateShaderIOHook();
			CreateRenderHook();
			CreateFormLoadHook();
			CreateSettingsHook();
			CreateGameEventHook();
			if (TheSettingManager->SettingsMain.CameraMode.Enabled) CreateCameraModeHook();
			if (TheSettingManager->SettingsMain.SleepingMode.Enabled) CreateSleepingModeHook();
			if (TheSettingManager->SettingsMain.Develop.LogShaders) CreateD3D9Hook();
		}
		return true;

	}

};