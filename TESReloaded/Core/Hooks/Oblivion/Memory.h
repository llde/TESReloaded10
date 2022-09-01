#pragma once
extern char(__thiscall* LoadTextureFile)(NiDX9SourceTextureData*, char*, NiDX9Renderer*, UInt32*);
char __fastcall LoadTextureFileHook(NiDX9SourceTextureData* This, UInt32 edx, char* Src, NiDX9Renderer* a5, UInt32* a6);

HRESULT __stdcall CreateTextureFromFileInMemory(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture);

void MemReallocHook();
