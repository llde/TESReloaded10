#include "GrassMode.h"

static const UInt32 kGrassHook = 0x004EBF87;
static const UInt32 kGrassReturn = 0x004EC4E8;

void UpdateGrass(TESObjectCELL* Cell, NiNode* GrassNode, float CameraPosX, float CameraPosY, float CameraPosZ, float CameraForwardX, float CameraForwardY, int Arg8, float StartFadingDistance, float EndDistance, float Arg11) {
	
	GridCellArray* CellArray = Tes->gridCellArray;
	UInt32 CellArraySize = CellArray->size * CellArray->size;

	for (UInt32 i = 0; i < CellArraySize; i++) {
		if (TESObjectCELL* Cell = CellArray->gridEntry[i].cell) {
			if (TheOcclusionManager->InFrustum(Cell->niNode)) CreateGrass(Cell, GrassNode, CameraPosX, CameraPosY, CameraPosZ, CameraForwardX, CameraForwardY, Arg8, StartFadingDistance, EndDistance, Arg11);
		}
	}

}

static __declspec(naked) void GrassHook() {

	__asm {
		call	UpdateGrass
		jmp		kGrassReturn
	}

}

void CreateGrassHook() {
	
	if (TheSettingManager->SettingsMain.GrassMode.Enabled) SafeWriteJump(kGrassHook, (UInt32)GrassHook);

}