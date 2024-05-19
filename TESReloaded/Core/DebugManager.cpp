#include "DebugManager.h"

DebugManager::DebugManager(const PluginInterface* intf) {
}


void DebugManager::Initialize(const PluginInterface* Interface) {
	TheDebugManager = new DebugManager(Interface);
}

void DebugManager::SaveRenderTarget(std::string& filename, IDirect3DSurface9* surface) {
	if (TheSettingManager->Config->Develop.DebugMode) {
		if (Global->OnKeyDown(0x17)) { // TODO: setting for debug key ?
			char Filename[MAX_PATH];

			time_t CurrentTime = time(NULL);
			GetCurrentDirectoryA(MAX_PATH, Filename);
			strcat(Filename, "\\Test\\");
			if (GetFileAttributesA(Filename) == INVALID_FILE_ATTRIBUTES) CreateDirectoryA(Filename, NULL);
			strcat(Filename, filename.c_str());
			D3DXSaveSurfaceToFileA(Filename, D3DXIFF_JPG, surface, NULL, NULL);
		}
	}
}