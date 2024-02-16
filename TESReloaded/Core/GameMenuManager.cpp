using namespace ffi;
#define TextColorNormal D3DCOLOR_XRGB(MenuSettings->TextColorNormal[0], MenuSettings->TextColorNormal[1], MenuSettings->TextColorNormal[2])
#define TextShadowColorNormal D3DCOLOR_XRGB(MenuSettings->TextShadowColorNormal[0], MenuSettings->TextShadowColorNormal[1], MenuSettings->TextShadowColorNormal[2])
#define TextColorSelected D3DCOLOR_XRGB(MenuSettings->TextColorSelected[0], MenuSettings->TextColorSelected[1], MenuSettings->TextColorSelected[2])
#define TextShadowColorSelected D3DCOLOR_XRGB(MenuSettings->TextShadowColorSelected[0], MenuSettings->TextShadowColorSelected[1], MenuSettings->TextShadowColorSelected[2])
#define TextColorEditing D3DCOLOR_XRGB(MenuSettings->TextColorEditing[0], MenuSettings->TextColorEditing[1], MenuSettings->TextColorEditing[2])
#define TextShadowColorEditing D3DCOLOR_XRGB(MenuSettings->TextShadowColorEditing[0], MenuSettings->TextShadowColorEditing[1], MenuSettings->TextShadowColorEditing[2])
#define TextColorEnabled D3DCOLOR_XRGB(MenuSettings->TextColorEnabled[0], MenuSettings->TextColorEnabled[1], MenuSettings->TextColorEnabled[2])
#define TextShadowColorEnabled D3DCOLOR_XRGB(MenuSettings->TextShadowColorEnabled[0], MenuSettings->TextShadowColorEnabled[1], MenuSettings->TextShadowColorEnabled[2])
#define PositionX MenuSettings->PositionX
#define PositionY MenuSettings->PositionY
#define TitleColumnSize MenuSettings->TitleColumnSize
#define MainItemColumnSize MenuSettings->MainItemColumnSize
#define ItemColumnSize MenuSettings->ItemColumnSize
#define RowSpace MenuSettings->RowSpace
#define RowsPerPage MenuSettings->RowsPerPage

void GameMenuManager::Initialize() {

	Logger::Log("Starting the menu manager...");
	TheGameMenuManager = new GameMenuManager();
	CreateFontRenderer(TheRenderManager->device);
//	ffi::MenuStruct* MenuSettings = &TheSettingManager->Config->Menu;

//	D3DXCreateFontA(TheRenderManager->device, MenuSettings->TextSize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, MenuSettings->TextFont.data, &TheGameMenuManager->FontNormal);
//	D3DXCreateFontA(TheRenderManager->device, MenuSettings->TextSize, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, MenuSettings->TextFont.data, &TheGameMenuManager->FontSelected);
//	D3DXCreateFontA(TheRenderManager->device, MenuSettings->TextSizeStatus, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, MenuSettings->TextFontStatus.data, &TheGameMenuManager->FontStatus);

}

static bool isEnabled = false;

extern "C" void SwitchEnabled(const char* shader) {
	TheShaderManager->SwitchShaderStatus(shader);
}


void GameMenuManager::Render() {

	ffi::MenuStruct* MenuSettings = &TheSettingManager->Config->Menu;

	if (InterfaceManager->IsActive(Menu::MenuType::kMenuType_Main)) {
		ffi::WriteVersionString(TheRenderManager->width, TheRenderManager->height, (const int8_t*)PluginVersion::VersionString);
	}
	else {
		if (Global->OnKeyDown(MenuSettings->KeyEnable)) {
			isEnabled = !isEnabled;
		}
		if (isEnabled) {
			if (Global->OnKeyDown(MenuSettings->KeyDown)) {
				ffi::MoveActiveNode(ffi::MoveCursor::Down);
			}
			else if (Global->OnKeyDown(MenuSettings->KeyUp)) {
				ffi::MoveActiveNode(ffi::MoveCursor::Up);
			}
			else if (Global->OnKeyDown(MenuSettings->KeyLeft)) {
				ffi::MoveActiveNode(ffi::MoveCursor::Left);
			}
			else if (Global->OnKeyDown(MenuSettings->KeyRight)) {
				ffi::MoveActiveNode(ffi::MoveCursor::Right);
			}
			else if (Global->OnKeyDown(MenuSettings->KeyAdd)) {
				ffi::EditActiveSetting(OperationSetting::Add, &SwitchEnabled);
			}
			else if (Global->OnKeyDown(MenuSettings->KeySubtract)) {
				ffi::EditActiveSetting(OperationSetting::Sub, &SwitchEnabled);
			}
			else if (Global->OnKeyDown(MenuSettings->KeySave)) {
				ffi::SaveConfigurations();
				InterfaceManager->ShowMessage("Settings Saved");
			}
			else if (Global->OnKeyDown(MenuSettings->KeyEditing)) {
				
			}
			ffi::RenderConfigurationMenu(TheRenderManager->width, TheRenderManager->height);
		}
	}
}
