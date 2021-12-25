#define WaitForDebugger 1
#define HookDevice 0

#include "RenderHook.h"
#include "ShaderIOHook.h"
#include "FormHook.h"
#include "CameraMode.h"
#include "SleepingMode.h"
#include "FlyCam.h"
#include "PluginVersion.h"
#include "MemoryManagement.h"
#include "D3D9Hook.h"

extern "C" {

	bool NVSEPlugin_Query(const PluginInterface* Interface, PluginInfo* Info) {
		
		Info->InfoVersion = PluginInfo::kInfoVersion;
		Info->Name = "NewVegasReloaded";
		Info->Version = 4;
		return true;

	}

	bool NVSEPlugin_Load(const PluginInterface* Interface) {

#if _DEBUG
	#if WaitForDebugger
			while (!IsDebuggerPresent()) Sleep(10);
	#endif
	#if HookDevice
			CreateD3D9Hook();
	#endif
#endif
		Logger::CreateLog("NewVegasReloaded.log");
		new CommandManager();
		TheCommandManager->AddCommands(Interface);

		if (!Interface->IsEditor) {
			PluginVersion::CreateVersionString();
			new SettingManager();
			if (TheSettingManager->LoadSettings(true)) {
				CreateGameInitializationHook();
				CreateShaderIOHook();
				CreateRenderHook();
				CreateFormLoadHook();
				CreateSettingsHook();
				CreateScriptHook();
				CreateShadowsHook();
				CreateFrameRateHook();
				//if (TheSettingManager->SettingsMain.OcclusionCulling.Enabled) CreateOcclusionCullingHook();
				//if (TheSettingManager->SettingsMain.Main.MemoryManagement) CreateMemoryManagementHook();
				if (TheSettingManager->SettingsMain.CameraMode.Enabled) CreateCameraModeHook();
				if (TheSettingManager->SettingsMain.SleepingMode.Enabled) CreateSleepingModeHook();
				if (TheSettingManager->SettingsMain.FlyCam.Enabled) CreateFlyCamHook();

				SafeWrite16(0x0086A170, 0x9090);		// Avoids to pause the game when ALT-TAB
			}
		}
		return true;

	}

};