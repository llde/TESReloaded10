static void UpdateGrass(TESObjectCELL* Cell, NiNode* GrassNode, float CameraPosX, float CameraPosY, float CameraPosZ, float CameraForwardX, float CameraForwardY, int Arg8, float StartFadingDistance, float EndDistance, float Arg11) {
	
	GridCellArray* CellArray = Tes->gridCellArray;
	UInt32 CellArraySize = CellArray->size * CellArray->size;

	for (UInt32 i = 0; i < CellArraySize; i++) {
		if (TESObjectCELL* Cell = CellArray->gridEntry[i].cell) {
			if (TheOcclusionManager->InFrustum(Cell->niNode)) Pointers::Functions::CreateGrass(Cell, GrassNode, CameraPosX, CameraPosY, CameraPosZ, CameraForwardX, CameraForwardY, Arg8, StartFadingDistance, EndDistance, Arg11);
		}
	}

}

static __declspec(naked) void UpdateGrassHook() {

	__asm {
		call	UpdateGrass
		jmp		Jumpers::UpdateGrass::Return
	}

}