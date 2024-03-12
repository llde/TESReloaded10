#pragma once
#include "../Framework/Oblivion/Plugin.h"
class DebugManager {
	OBSEMessagingInterface* msg;
	UInt32 pluginHandle;
	std::list<UInt32> processedAddress;
public:
	DebugManager(const PluginInterface* intf);
	void LogException(CONTEXT* context);

	static void Initialize(const PluginInterface* Interface);
};