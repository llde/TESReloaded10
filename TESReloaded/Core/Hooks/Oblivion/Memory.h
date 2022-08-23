#pragma once

static __declspec(naked) void MemReallocHook() {

	__asm {
		mov     ebp, [esp + 0x10]
		push	ebp
		push	ebx
		call	Mem.Realloc
		add		esp, 8
		jmp		Jumpers::Memory::MemReallocReturn
	}

}

static HRESULT __stdcall CreateTextureFromFileInMemory(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture) {

	return D3DXCreateTextureFromFileInMemoryEx(pDevice, pSrcData, SrcDataSize, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, ppTexture);

}


static char (__thiscall* LoadTextureFile)(NiDX9SourceTextureData*, char*, NiDX9Renderer*, UInt32*) = (char (__thiscall*)(NiDX9SourceTextureData*, char*, NiDX9Renderer*, UInt32*)) Hooks::LoadTextureData;


static  char __fastcall LoadTextureFileHook(NiDX9SourceTextureData *This, UInt32 edx, char *Src, NiDX9Renderer *a5, UInt32 *a6) {
    Logger::Log("%s", Src);
    return (*LoadTextureFile)(This, Src,a5,a6);
}

