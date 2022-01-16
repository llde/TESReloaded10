#pragma once

class CommandManager: public CommandManagerBase { // Never disposed
public:
	class PluginCommands {
	public:
		void IsThirdPerson(double* result);
		void GetVersion(double* result);
		void GetLocationName(double* result);
		void SetExtraEffectEnabled(double* result, const char* Name, bool Value);
		void SetCustomConstant(double* result, const char* Name, D3DXVECTOR4* Value);
		void GetWeatherName(double* result);
		void GetSetting(double* result, const char* Section, const char* Key);
		void SetSetting(double* result, const char* Section, const char* Key, float Value);
		void CameraTranslate(double* result, TESObjectREFR* Ref, NiPoint3* Value);
		void CameraRotate(double* result, TESObjectREFR* Ref, NiPoint3* Value);
		void CameraTranslateToPosition(double* result, NiPoint3* Value);
		void CameraRotateToPosition(double* result, NiPoint3* Value);
		void CameraLookAt(double* result, TESObjectREFR* Ref, NiPoint3* Value);
		void CameraLookAtPosition(double* result, NiPoint3* Value);
		void CameraReset(double* result);
	};

	static void			Initialize(const PluginInterface* Interface);

	PluginCommands		Commands;
};