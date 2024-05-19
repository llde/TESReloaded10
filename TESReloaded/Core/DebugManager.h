#pragma once
class DebugManager {
public:
	DebugManager(const PluginInterface* intf);

	void SaveRenderTarget(std::string& filename, IDirect3DSurface9* surface);
	static void Initialize(const PluginInterface* Interface);
};