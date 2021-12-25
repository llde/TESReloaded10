#pragma once
#pragma warning (disable: 4244) //disable warning for possible loss of data in implicit cast between int, float and double

#define DETOURS_INTERNAL
#define assert(a) static_assert(a, "Assertion failed")

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <d3d9.h>
#include <d3dx9math.h>
#include <dinput.h>
#include <dsound.h>
#include "../Common/Lib/Detours/detours.h"
#include "../Common/Lib/Nvidia/nvapi.h"
#include "../Common/Base/Logger.h"
#include "../Common/Base/Types.h"
#include "../Common/Base/SafeWrite.h"
#include "Plugin.h"
#include "Game.h"
#include "Defines.h"
#include "Papyrus.h"
#include "Base.h"
#include "../Common/Managers.h"
#include "../Core/Hooks/Settings.h"
#include "../Core/Hooks/Game.h"
#include "../Core/Hooks/Skyrim/Settings.h"
#include "../Core/Hooks/Skyrim/Game.h"
#include "../Core/Hooks/Skyrim/ShaderIO.h"