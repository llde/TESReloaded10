#pragma once

static __declspec(naked) void RenderShadowMapHook() {

	__asm {
		pushad
		mov		ecx, TheShadowManager
		call	ShadowManager::RenderShadowMaps
		popad
		jmp		kRenderShadowMapReturn
	}

}

static void AddCastShadowFlag(TESObjectREFR* Ref, TESObjectLIGH* Light, NiPointLight* LightPoint) {
	
	SettingsShadowStruct::InteriorsStruct* ShadowsInteriors = &TheSettingManager->SettingsShadows.Interiors;

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

static __declspec(naked) void AddCastShadowFlagHook() {

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
		jmp		kAddCastShadowFlagReturn
	}

}