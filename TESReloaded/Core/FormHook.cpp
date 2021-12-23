#include "FormHook.h"

#if defined(OBLIVION)
#define kLoadForm 0x00447050
static const UInt32 kSetRegionEditorName = 0x004A32A6;
static const UInt32 kSetRegionEditorNameReturn = 0x004A33A6;
static const UInt32 kSetWeatherEditorName = 0x004EE04E;
static const UInt32 kSetWeatherEditorNameReturn = 0x004EE0EA;
#elif defined(SKYRIM)
#define kLoadForm 0x0043B4A0
static const UInt32 kSetRegionEditorName = 0x0048BEE4;
static const UInt32 kSetRegionEditorNameReturn = 0x0048BEEA;
static const UInt32 kSetWeatherEditorName = 0x004EF358;
static const UInt32 kSetWeatherEditorNameReturn = 0x004EF35E;
#endif

bool (__cdecl* LoadForm)(TESForm*, UInt32) = (bool (__cdecl*)(TESForm*, UInt32))kLoadForm;
bool __cdecl TrackLoadForm(TESForm* Form, UInt32 ModEntry) {
	
	bool r = LoadForm(Form, ModEntry);
	switch (Form->formType) {
		case TESForm::FormType::kFormType_Weather: {
				if (TheSettingManager->SettingsMain.WeatherMode.Enabled) {
					TESWeatherEx* Weather = (TESWeatherEx*)Form;
					memcpy(Weather->colorsb, Weather->colors, WeatherColorsSize);
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

static __declspec(naked) void SetRegionEditorNameHook() {

	__asm
	{
		push	ecx
		call	SetRegionEditorName
		add		esp, 8
#if defined(OBLIVION)
		xor		esi, esi
#elif defined(SKYRIM)
		lea     ecx, [esp+0x20]
#endif
		jmp		kSetRegionEditorNameReturn
	}

}

void SetWeatherEditorName(TESWeatherEx* Weather, const char* Name) {

	strcpy(Weather->EditorName, Name);

}

static __declspec(naked) void SetWeatherEditorNameHook() {

	__asm
	{
		push	ecx
		call	SetWeatherEditorName
		add		esp, 8
#if defined(SKYRIM)
		lea     ecx, [esp + 0x20]
#endif
		jmp		kSetWeatherEditorNameReturn
	}

}

void CreateFormLoadHook() {
	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)LoadForm,		&TrackLoadForm);
	DetourTransactionCommit();

#if defined(OBLIVION)
	SafeWrite8(0x00448843, sizeof(TESRegionEx));
	SafeWrite8(0x004A2EFF, sizeof(TESRegionEx));
	SafeWrite32(0x004486ED, sizeof(TESWeatherEx));
	SafeWrite32(0x0044CBE3, sizeof(TESWeatherEx));
#elif defined(SKYRIM)
	SafeWrite8(0x0048BC15, sizeof(TESRegionEx));
	SafeWrite32(0x00442B22, sizeof(TESWeatherEx));
	SafeWrite32(0x004EF7F5, sizeof(TESWeatherEx));
#endif
	SafeWriteJump(kSetRegionEditorName, (UInt32)SetRegionEditorNameHook);
	SafeWriteJump(kSetWeatherEditorName, (UInt32)SetWeatherEditorNameHook);

}