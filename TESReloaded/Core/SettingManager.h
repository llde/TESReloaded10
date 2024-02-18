#pragma once
#include <SettingStructure.h>


class SettingManager : public SettingManagerBase {
public:
	bool							GameLoading;
	ffi::Config*					Config;
	ffi::Effects*					Effects;
	ffi::Shaders*					Shaders;
	void LoadSettings();
	bool GetMenuShaderEnabled(const char* Name);
	void SetGame(ffi::Game game);
	static void Initialize();
};
