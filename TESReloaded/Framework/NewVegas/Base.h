#pragma once

class Hooks {
public:

};

class Jumpers {
public:
	struct CreateDevice {
		static const UInt32 Hook	= 0x00E731FF;
		static const UInt32 Return	= 0x00E73204;
	};
};

class CommandManagerBase {
public:
	
	void RegisterCommands(const PluginInterface* Interface, void** CommandExecuters, CommandInfo** CommandInfos, int CommandInfoSize, void** PapyrusCommands) {

		Interface->SetOpcodeBase(0x3000);
		for (int i = 0; i < CommandInfoSize; i++) {
			Interface->RegisterCommand(CommandInfos[i]);
		}

	}

};

class SettingManagerBase {
public:

	bool IsMatching(char* Versioning) {

		return Versioning[2] == '1';

	}

};

class RenderManagerBase : public NiDX9Renderer {
public:

	IDirect3DSurface9* CreateHDRRenderTarget() {

		return NULL;

	}

};

class ShaderManagerBase {
public:

};

class ShadowManagerBase {
public:

	enum ShadowMapTypeEnum {
		MapNear = 0,
		MapFar = 1,
		MapOrtho = 2,
	};

};