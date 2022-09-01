#pragma once

bool (__cdecl* LoadForm)(TESForm*, UInt32) = (bool (__cdecl*)(TESForm*, UInt32))Hooks::LoadForm;
bool __cdecl LoadFormHook(TESForm* Form, UInt32 ModEntry) {
	
	bool r = LoadForm(Form, ModEntry);
	switch (Form->formType) {
		case TESForm::FormType::kFormType_Weather: {
				if (TheSettingManager->SettingsMain.WeatherMode.Enabled) {
					TESWeatherEx* Weather = (TESWeatherEx*)Form;
					memcpy(Weather->colorsb, Weather->colors, TESWeather::kNumColorTypes * TESWeather::kNumTimeOfDay * 4);
					TheSettingManager->SetSettingsWeather(Weather);
				}
			}
			break;
		case TESForm::FormType::kFormType_Water: {
				TESWaterForm* Water = (TESWaterForm*)Form;
				if (TheSettingManager->SettingsMain.Main.RemoveUnderwater) Water->RemoveUnderwaterFog();
			}
			break;
		default:
			break;
	}
	return r;

}

void SetRegionEditorName(TESRegionEx* Region, const char* Name) {

	strcpy(Region->EditorName, Name);

}

void SetWeatherEditorName(TESWeatherEx* Weather, const char* Name) {

	strcpy(Weather->EditorName, Name);

}