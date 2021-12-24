#pragma once

class CommandManager;	extern CommandManager*		TheCommandManager;
class SettingManager;	extern SettingManager*		TheSettingManager;
class ShaderManager;	extern ShaderManager*		TheShaderManager;
class TextureManager;	extern TextureManager*		TheTextureManager;
class RenderManager;	extern RenderManager*		TheRenderManager;
class FrameRateManager; extern FrameRateManager*	TheFrameRateManager;
class GameMenuManager;	extern GameMenuManager*		TheGameMenuManager;
class KeyboardManager;	extern KeyboardManager*		TheKeyboardManager;
class GameEventManager; extern GameEventManager*	TheGameEventManager;
class ShadowManager;	extern ShadowManager*		TheShadowManager;
class OcclusionManager; extern OcclusionManager*	TheOcclusionManager;
class EquipmentManager; extern EquipmentManager*	TheEquipmentManager;
class ScriptManager;	extern ScriptManager*		TheScriptManager;
class CameraManager;	extern CameraManager*		TheCameraManager;

class Main;					extern Main*					Global;
class TES;					extern TES*						Tes;
class PlayerCharacter;		extern PlayerCharacter*			Player;
class SceneGraph;			extern SceneGraph*				WorldSceneGraph;
class MasterDataHandler;	extern MasterDataHandler*		DataHandler;
class MenuInterfaceManager; extern MenuInterfaceManager*	MenuManager;
class QueuedModelLoader;	extern QueuedModelLoader*		ModelLoader;
class ShadowSceneNode;		extern ShadowSceneNode*			SceneNode;

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

void InitializeManagers();