#include "DebugManager.h"

DebugManager::DebugManager(const PluginInterface* intf) {
	this->msg = (OBSEMessagingInterface*)intf->QueryInterface(PluginInterface::Interface::kInterface_Messaging);
	this->pluginHandle = intf->GetPluginHandle();
	if (this->msg == nullptr) Logger::Log("No Message Interface initialized");
}

void DebugManager::LogException(CONTEXT* context) {
	if (std::find(processedAddress.begin(), processedAddress.end(), context->Eip) != processedAddress.end()) return;
	EXCEPTION_POINTERS* excptr = new EXCEPTION_POINTERS();
	excptr->ContextRecord = context;
	excptr->ExceptionRecord = new EXCEPTION_RECORD();
	excptr->ExceptionRecord->ExceptionCode = 0x666;
	excptr->ExceptionRecord->ExceptionAddress = (void*)excptr->ContextRecord->Eip;
	excptr->ExceptionRecord->ExceptionRecord = nullptr;
	if (this->msg->Dispatch(this->pluginHandle, 'LOGG', excptr, 1, nullptr)) {
		processedAddress.push_back(context->Eip);

	}
}

void DebugManager::Initialize(const PluginInterface* Interface) {
	TheDebugManager = new DebugManager(Interface);
}