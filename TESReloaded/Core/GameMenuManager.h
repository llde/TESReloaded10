#pragma once

class GameMenuManager { // Never disposed
public:
	static void Initialize();

	void					Render();
	void					GetMidSection(char* MidSection);

	bool										Enabled;
	bool										EditingMode;
	UInt32										Pages[4];
	UInt32										SelectedPage[4];
	UInt32										Rows[4];
	UInt32										SelectedRow[4];
	UInt32										SelectedColumn;
	char										EditingValue[20];
//	SettingManager::Configuration::ConfigNode	SelectedNode;
	ID3DXFont*									FontSelected;
	ID3DXFont*									FontNormal;
	ID3DXFont*									FontStatus;
	RECT										Rect;
	RECT										RectShadow;
};