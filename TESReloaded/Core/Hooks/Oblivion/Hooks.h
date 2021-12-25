#pragma once

void AttachHooks() {

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ReadSetting,				&ReadSettingHook);
	DetourAttach(&(PVOID&)WriteSetting,				&WriteSettingHook);
	DetourAttach(&(PVOID&)LoadGame,					&LoadGameHook);
	DetourAttach(&(PVOID&)NewMain,					&NewMainHook);
	DetourAttach(&(PVOID&)InitializeRenderer,		&InitializeRendererHook);
	DetourAttach(&(PVOID&)NewTES,					&NewTESHook);
	DetourAttach(&(PVOID&)NewPlayerCharacter,		&NewPlayerCharacterHook);
	DetourAttach(&(PVOID&)NewSceneGraph,			&NewSceneGraphHook);
	DetourAttach(&(PVOID&)NewMainDataHandler,		&NewMainDataHandlerHook);
	DetourAttach(&(PVOID&)NewMenuInterfaceManager,	&NewMenuInterfaceManagerHook);
	DetourAttach(&(PVOID&)NewQueuedModelLoader,		&NewQueuedModelLoaderHook);
	DetourAttach(&(PVOID&)CreateVertexShader,		&CreateVertexShaderHook);
	DetourAttach(&(PVOID&)CreatePixelShader,		&CreatePixelShaderHook);
	DetourTransactionCommit();

	SafeWrite32(0x0076BD75, sizeof(RenderManager));
	SafeWrite8(0x00801BCB,	sizeof(NiD3DVertexShaderEx));
	SafeWrite8(0x008023A1,	sizeof(NiD3DPixelShaderEx));

}

//#include <fstream>
//LPD3DXBUFFER Disasm;
//char FileNameS[MAX_PATH];
//void* ShaderPackage = *(void**)0x00B430B8;
//
//char* ShaderFunction = (char*)ThisCall(0x007DAC70, ShaderPackage, ShaderName);
//ShaderFunction = ShaderFunction + 0x104;
//D3DXDisassembleShader((const DWORD*)ShaderFunction, FALSE, NULL, &Disasm);
//strcpy(FileNameS, "C:\\Archivio\\TES\\Shaders\\OblivionShadersNew\\");
//strcat(FileNameS, ShaderName);
//strcat(FileNameS, ".dis");
//std::ofstream FileBinary(FileNameS, std::ios::out | std::ios::binary);
//FileBinary.write((char*)Disasm->GetBufferPointer(), Disasm->GetBufferSize());
//FileBinary.flush();
//FileBinary.close();