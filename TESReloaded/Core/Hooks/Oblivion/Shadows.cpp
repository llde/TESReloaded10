#pragma once

__declspec(naked) void RenderShadowMapHook() {

	__asm {
		pushad
		mov		ecx, TheShadowManager
		call	ShadowManager::RenderShadowMaps
		test al,al
		jnz exec
		popad
		mov ecx, edi
		call    Jumpers::Shadows::OriginalRenderShadowPass
		jmp		Jumpers::Shadows::RenderShadowMapReturn

		exec:
		popad
		jmp		Jumpers::Shadows::RenderShadowMapReturn
	}

}

NiTexture::FormatPrefs FP = { NiRenderedTexture::PixelLayout::kPixelLayout_TrueColor32, NiRenderedTexture::AlphaFormat::kAlpha_Smooth, NiRenderedTexture::MipMapFlag::kMipMap_Default };

int(__fastcall* RenderCanopyMap)(GridCellArray*) = (int(__fastcall*)(GridCellArray*))0x004826F0;
int __fastcall RenderCanopyMapHook(GridCellArray* This) {
	NiRenderedTexture* ni = *(NiRenderedTexture**)0x00B4310C;
	if (!TheShadowManager->StubCanopyMap) {
		TheShadowManager->StubCanopyMap = Pointers::Functions::CreateNiRenderedTexture(1, 1, TheRenderManager, &FP);
		LONG u = InterlockedIncrement(&TheShadowManager->StubCanopyMap->m_uiRefCount);
		Logger::Log("Intialized Empty Canopy ShadowMap, refs %lu", u );
	}
	if (ni == nullptr || !TheSettingManager->Config->ShadowsExterior.Enabled) {
		return RenderCanopyMap(This);
	}
	return 0;
}

static void AddCastShadowFlag(TESObjectREFR* Ref, TESObjectLIGH* Light, NiPointLight* LightPoint) {
	
	ffi::ShadowsInteriorStruct *ShadowsInteriors = &TheSettingManager->Config->ShadowsInterior;

	if (Light->lightFlags & TESObjectLIGH::LightFlags::kLightFlags_CanCarry) {
		LightPoint->CastShadows = ShadowsInteriors->TorchesCastShadows;
		LightPoint->CanCarry = 1;
		if (Ref == Player) {
			if (Player->isThirdPerson) {
				if (Player->firstPersonSkinInfo->LightForm == Light) LightPoint->CastShadows = 0;
			}
			else {
				if (Player->ActorSkinInfo->LightForm == NULL && Player->firstPersonSkinInfo->LightForm == Light) LightPoint->CastShadows = 0;
			}
			LightPoint->CanCarry = 2;
		}
	}		
	else if (Ref->baseForm->formType == TESForm::FormType::kFormType_Light) {
		LightPoint->CastShadows = !(Ref->flags & TESForm::FormFlags::kFormFlags_NotCastShadows);
		LightPoint->CanCarry = 0;
	}

}

__declspec(naked) void AddCastShadowFlagHook() {

	__asm {
		mov     ecx, [esp + 0x158]
		pushad
		push	esi
		push	edi
		push	ecx
		call	AddCastShadowFlag
		pop		ecx
		pop		edi
		pop		esi
		popad
		pop		ecx
		pop		edi
		pop		esi
		pop		ebp
		pop		ebx
		jmp		Jumpers::Shadows::AddCastShadowFlagReturn
	}

}

static void EditorCastShadowFlag(HWND Window, TESForm* Form) {

	if (Window && Form) {
		SetDlgItemTextA(Window, 0x697, "Does Not Cast Shadows");
		SetWindowPos(GetDlgItem(Window, 0x697), HWND_BOTTOM, 0, 0, 140, 15, SWP_NOMOVE | SWP_NOZORDER);
	}

}

__declspec(naked) void EditorCastShadowFlagHook() {

	__asm {
		pushad
		push	eax
		push	edi
		call	EditorCastShadowFlag
		pop		edi
		pop		eax
		popad
		jmp		Jumpers::Shadows::EditorCastShadowFlagReturn
	}

}