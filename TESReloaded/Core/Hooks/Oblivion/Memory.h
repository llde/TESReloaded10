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