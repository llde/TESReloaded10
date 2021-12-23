#include "PluginVersion.h"

char PluginVersion::VersionString[64] = { NULL };

void PluginVersion::CreateVersionString() {

	LPSTR FileName = new char[MAX_PATH];
	HMODULE ModuleHandle = NULL;

	if (GetModuleFileNameA(ModuleHandle, FileName, MAX_PATH)) AddVersion(FileName);
	strcat(VersionString, " ");
	if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&CreateVersionString, &ModuleHandle) && GetModuleFileNameA(ModuleHandle, FileName, MAX_PATH)) AddVersion(FileName);
	delete FileName;

}

void PluginVersion::AddVersion(char* FileName) {

	DWORD VersionHandle = NULL;
	
	DWORD VersionSize = GetFileVersionInfoSizeA(FileName, &VersionHandle);
	if (VersionSize) {
		LPSTR VersionData = new char[VersionSize];
		UINT BufferSize = 0;
		void* BufferData = NULL;

		if (GetFileVersionInfoA(FileName, VersionHandle, VersionSize, VersionData)) {
			if (VerQueryValueA(VersionData, "\\StringFileInfo\\040904b0\\ProductName", &BufferData, &BufferSize)) {
				strcat(VersionString, (char*)BufferData);
				strcat(VersionString, " v");
			}
			if (VerQueryValueA(VersionData, "\\StringFileInfo\\040904b0\\ProductVersion", &BufferData, &BufferSize)) strcat(VersionString, (char*)BufferData);
		}
		delete VersionData;
	}

}