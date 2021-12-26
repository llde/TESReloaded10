#include "MemoryManagement.h"

static const UInt32 kMemReallocHook = 0x00401E66;
static const UInt32 kMemReallocReturn = 0x00401EC7;
static const UInt32 kCreateTextureFromFileInMemory = 0x007610D3;

struct Memory {
	void* (*Malloc)		(size_t Size);
	void  (*Free)		(void* Block);
	void* (*Realloc)	(void* Block, size_t Size);
};
static Memory Mem;

static __declspec(naked) void MemReallocHook() {

	__asm {
		mov     ebp, [esp + 0x10]
		push	ebp
		push	ebx
		call	Mem.Realloc
		add		esp, 8
		jmp		kMemReallocReturn
	}

}

HRESULT __stdcall CreateTextureFromFileInMemory(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture) {

	return D3DXCreateTextureFromFileInMemoryEx(pDevice, pSrcData, SrcDataSize, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, ppTexture);

}

void CreateMemoryManagementHook() {
	
	HMODULE Module = NULL;
	char Filename[MAX_PATH];

	if (TheSettingManager->SettingsMain.Main.MemoryHeapManagement) {
		GetCurrentDirectoryA(MAX_PATH, Filename);
		strcat(Filename, FastMMFile);
		Module = LoadLibraryA(Filename);
		if (Module) {
			Mem.Malloc = (void* (*)(size_t))GetProcAddress(Module, "GetMemory");
			Mem.Free = (void (*)(void*))GetProcAddress(Module, "FreeMemory");
			Mem.Realloc = (void* (*)(void*, size_t))GetProcAddress(Module, "ReallocMemory");
			Logger::Log("Fast memory manager loaded correctly.");
		}
		else {
			char Error[160];
			sprintf(Error, "CRITICAL ERROR: Cannot load the memory manager, please reinstall the package.");
			Logger::Log(Error);
			MessageBoxA(NULL, Error, PluginVersion::VersionString, MB_ICONERROR | MB_OK);
			TerminateProcess(GetCurrentProcess(), 0);
		}

		SafeWriteJump(0x009D7E40, 0x009D7E60); //Skips MemoryHeap initialization
		SafeWriteJump(0x0040E3BF, 0x0040E62A); //Skips MemoryHeap pools creation and cleanup assignment
		SafeWriteJump(0x0040B3A0, 0x0040C008); //Skips MemoryHeap stats
		SafeWriteCall(0x00401AAE, (UInt32)Mem.Malloc);
		SafeWriteCall(0x00401495, (UInt32)Mem.Free);
		SafeWriteJump(kMemReallocHook, (UInt32)MemReallocHook);
	}
	if (TheSettingManager->SettingsMain.Main.MemoryTextureManagement) SafeWriteCall(kCreateTextureFromFileInMemory, (UInt32)CreateTextureFromFileInMemory);

}