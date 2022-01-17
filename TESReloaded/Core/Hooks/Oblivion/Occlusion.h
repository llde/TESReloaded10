#pragma once

static __declspec(naked) void New1CollisionObjectHook() {

	__asm {
		mov     edi, eax
		add     esp, 4
		mov		dword ptr [edi + bhkCollisionObjectEx::GeoNode], 0
		jmp		Jumpers::Occlusion::New1CollisionObjectReturn
	}

}

static __declspec(naked) void New2CollisionObjectHook() {

	__asm {
		mov     esi, eax
		add     esp, 4
		mov		dword ptr [esi + bhkCollisionObjectEx::GeoNode], 0
		jmp		Jumpers::Occlusion::New2CollisionObjectReturn
	}

}

static __declspec(naked) void New3CollisionObjectHook() {

	__asm {
		mov     esi, eax
		add     esp, 4
		mov		dword ptr [esi + bhkCollisionObjectEx::GeoNode], 0
		jmp		Jumpers::Occlusion::New3CollisionObjectReturn
	}

}

static void DisposeCollisionObject(bhkCollisionObjectEx* bCollisionObject) {
	
	void* VFT = *(void**)bCollisionObject;
	
	if (VFT == Pointers::VirtualTables::bhkCollisionObject) {
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
		jmp		Jumpers::Occlusion::DisposeCollisionObjectReturn
	}

}

static __declspec(naked) void MaterialPropertyHook() {

	__asm {
		test    word ptr [esi + 0x18], 0x400
		jnz     short loc_return
		test    edi, edi
		fldz
		fst		[esp + 0x18]
		jmp		Jumpers::Occlusion::MaterialPropertyReturn1
	loc_return:
		jmp		Jumpers::Occlusion::MaterialPropertyReturn2
	}

}

static __declspec(naked) void CoordinateJackHook() {

	__asm {
		test    word ptr [eax + 0x18], 0x400
		jnz     short loc_return
		mov     esi, eax
		jmp		Jumpers::Occlusion::CoordinateJackReturn1
	loc_return:
		jmp		Jumpers::Occlusion::CoordinateJackReturn2
	}

}

static __declspec(naked) void ObjectCullHook() {

	__asm {
		test    word ptr [ecx + 0x18], 0x200
		jnz     short loc_return
		mov     eax, [esp + 0x04]
		mov     edx, [eax]
		jmp		Jumpers::Occlusion::ObjectCullReturn1
	loc_return:
		jmp		Jumpers::Occlusion::ObjectCullReturn2
	}

}