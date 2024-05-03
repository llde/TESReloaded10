#include "DebugManager.h"

DebugManager::DebugManager(const PluginInterface* intf) {
}


void DebugManager::Initialize(const PluginInterface* Interface) {
	TheDebugManager = new DebugManager(Interface);
}