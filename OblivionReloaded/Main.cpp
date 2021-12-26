#define WaitForDebugger 0
#define HookDevice 0

#include "GrassMode.h"
#include "MountedCombat.h"
#include "SleepingMode.h"
#include "Animation.h"
#include "Dodge.h"
#include "FlyCam.h"
#include "MemoryManagement.h"
#include "D3D9Hook.h"
#include "Hooks/Oblivion/Hooks.h"

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
				CreateAnimationHook();
				CreateShadowsHook();
				CreateFrameRateHook();
				CreateTextureHook();
				CreateOcclusionCullingHook();
				CreateMemoryManagementHook();
				CreateGrassHook();
				CreateCameraModeHook();
				if (TheSettingManager->SettingsMain.EquipmentMode.Enabled) {
					CreateEquipmentHook();
					if (TheSettingManager->SettingsMain.MountedCombat.Enabled) CreateMountedCombatHook();
				}
				CreateSleepingModeHook();
				CreateDodgeHook();
				CreateFlyCamHook();

				SafeWriteJump(0x0049849A, 0x004984A0); // Skips antialiasing deactivation if HDR is enabled on the D3DDevice
				SafeWriteJump(0x004984BD, 0x004984CD); // Skips antialiasing deactivation if AllowScreenshot is enabled
				SafeWriteJump(0x005DEE60, 0x005DEE68); // Skips antialiasing deactivation if HDR is enabled on loading the video menu
				SafeWriteJump(0x005DF69E, 0x005DF755); // Skips HDR deactivation changing antialising (video menu)
				SafeWriteJump(0x00497D5A, 0x00497D63); // Unlocks antialising bar if HDR is enabled (video menu)
				SafeWriteJump(0x005DF8E9, 0x005DF983); // Skips antialising deactivation changing HDR (video menu)
				SafeWriteJump(0x006738B1, 0x00673935); // Cancels the fPlayerDeathReloadTime
			}
		}
		else {
			CreateEditorShadowsHook();
		}
		return true;

	}

};