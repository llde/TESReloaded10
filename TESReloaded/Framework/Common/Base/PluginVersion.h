#pragma once

class PluginVersion {
public:
	static void CreateVersionString() {

		char FileName[MAX_PATH];
		HMODULE ModuleHandle = NULL;

		// Get game filename
		if (GetModuleFileNameA(NULL, FileName, MAX_PATH)) {
			AddVersion(FileName);
		}

		strncat(VersionString, " ", sizeof(VersionString));

		// Get DLL filename
		if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&CreateVersionString, &ModuleHandle) && GetModuleFileNameA(ModuleHandle, FileName, MAX_PATH)) {
			AddVersion(FileName);
		}
	}
	
	static void AddVersion(char* FileName) {
		
		DWORD VersionHandle = NULL;

		DWORD VersionSize = GetFileVersionInfoSizeA(FileName, &VersionHandle);
		if (VersionSize) {
			LPSTR VersionData = new char[VersionSize];
			UINT BufferSize = 0;
			void* BufferData = NULL;

			if (GetFileVersionInfoA(FileName, VersionHandle, VersionSize, VersionData)) {
				if (VerQueryValueA(VersionData, "\\StringFileInfo\\040904b0\\ProductName", &BufferData, &BufferSize)) {
					strncat(VersionString, (char*)BufferData, sizeof(VersionString));
					strncat(VersionString, " v", sizeof(VersionString));
				}
				if (VerQueryValueA(VersionData, "\\StringFileInfo\\040904b0\\ProductVersion", &BufferData, &BufferSize)) {
					strncat(VersionString, (char*)BufferData, sizeof(VersionString));
                }
			}
			delete VersionData;
		}

	}

	static char VersionString[0x80];
};
