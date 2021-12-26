#pragma once

static __declspec(naked) void New1CollisionObjectHook() {

	__asm {
		mov     edi, eax
		add     esp, 4
		mov		dword ptr [edi + bhkCollisionObjectEx::GeoNode], 0
		jmp		kNew1CollisionObjectReturn
	}

}

static __declspec(naked) void New2CollisionObjectHook() {

	__asm {
		mov     esi, eax
		add     esp, 4
		mov		dword ptr [esi + bhkCollisionObjectEx::GeoNode], 0
		jmp		kNew2CollisionObjectReturn
	}

}

static __declspec(naked) void New3CollisionObjectHook() {

	__asm {
		mov     esi, eax
		add     esp, 4
		mov		dword ptr [esi + bhkCollisionObjectEx::GeoNode], 0
		jmp		kNew3CollisionObjectReturn
	}

}

static void DisposeCollisionObject(bhkCollisionObjectEx* bCollisionObject) {
	
	void* VFT = *(void**)bCollisionObject;
	
	if (VFT == VFTbhkCollisionObject) {
		if (NiNode* GeoNode = bCollisionObject->GeoNode) {
			GeoNode->Destructor(1);
			bCollisionObject->GeoNode = NULL;
		}
	}

}

static __declspec(naked) void DisposeCollisionObjectHook() {

	__asm {
		pushad
		push	ecx
		call	DisposeCollisionObject
		pop		ecx
		popad
		mov     esi, ecx
		mov		eax, 0x00897B00
		call	eax
		jmp		kDisposeCollisionObjectReturn
	}

}

static __declspec(naked) void MaterialPropertyHook() {

	__asm {
		test    word ptr [esi + 0x18], 0x400
		jnz     short loc_return
		test    edi, edi
		fldz
		fst		[esp + 0x18]
		jmp		kMaterialPropertyReturn1
	loc_return:
		jmp		kMaterialPropertyReturn2
	}

}

static __declspec(naked) void CoordinateJackHook() {

	__asm {
		test    word ptr [eax + 0x18], 0x400
		jnz     short loc_return
		mov     esi, eax
		jmp		kCoordinateJackReturn1
	loc_return:
		jmp		kCoordinateJackReturn2
	}

}

static __declspec(naked) void ObjectCullHook() {

	__asm {
		test    word ptr [ecx + 0x18], 0x200
		jnz     short loc_return
		mov     eax, [esp + 0x04]
		mov     edx, [eax]
		jmp		kObjectCullReturn1
	loc_return:
		jmp		kObjectCullReturn2
	}

}