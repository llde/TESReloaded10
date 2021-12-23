void SafeWrite8(UInt32 addr, UInt32 data) {

	UInt32	oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt8*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);

}

void SafeWrite16(UInt32 addr, UInt32 data) {

	UInt32	oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt16*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);

}

void SafeWrite32(UInt32 addr, UInt32 data) {

	UInt32	oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt32*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);

}

void SafeWriteJump(UInt32 jumpSrc, UInt32 jumpTgt) {

	SafeWrite8(jumpSrc, 0xE9);
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);

}

void SafeWriteCall(UInt32 jumpSrc, UInt32 jumpTgt) {

	SafeWrite8(jumpSrc, 0xE8);
	SafeWrite32(jumpSrc + 1, jumpTgt - jumpSrc - 1 - 4);

}