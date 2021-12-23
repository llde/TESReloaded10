#pragma once

class SettingManager;
static SettingManager* TheSettingManager = NULL;

#include "SettingManager.h"
#include "EquipmentManager.h"
#include "ScriptManager.h"
#include "CommandManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "RenderManager.h"
#include "FrameRateManager.h"
#include "GameEventManager.h"
#include "GameMenuManager.h"
#include "KeyboardManager.h"
#include "ShadowManager.h"
#include "OcclusionManager.h"
#include "CameraManager.h"

extern CommandManager*		TheCommandManager;
extern TextureManager*		TheTextureManager;
extern ShaderManager*		TheShaderManager;
extern RenderManager*		TheRenderManager;
extern FrameRateManager*	TheFrameRateManager;
extern GameMenuManager*		TheGameMenuManager;
extern KeyboardManager*		TheKeyboardManager;
extern GameEventManager*	TheGameEventManager;
extern ShadowManager*		TheShadowManager;
extern OcclusionManager*	TheOcclusionManager;
extern EquipmentManager*	TheEquipmentManager;
extern ScriptManager*		TheScriptManager;
extern CameraManager*		TheCameraManager;

void InitializeManagers();