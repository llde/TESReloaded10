#pragma once

__declspec(naked) void SetRegionEditorNameHook() {

	__asm {
		push	ecx
		call	SetRegionEditorName
		add		esp, 8
		lea     ecx, [esp+0x20]
		jmp		Jumpers::SetRegionEditorName::Return
	}

}



__declspec(naked) void SetWeatherEditorNameHook() {

	__asm {
		push	ecx
		call	SetWeatherEditorName
		add		esp, 8
		lea     ecx, [esp + 0x20]
		jmp		Jumpers::SetWeatherEditorName::Return
	}

}