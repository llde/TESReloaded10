#pragma once

static __declspec(naked) void RenderShadowMapHook() {

	__asm {
		pushad
		mov		ecx, TheShadowManager
		call	ShadowManager::RenderShadowMaps
		popad
		jmp		Jumpers::Shadows::RenderShadowMapReturn
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
	else if (Ref && Ref->baseForm && Ref->baseForm->formType == TESForm::FormType::kFormType_Light) {
		LightPoint->CastShadows = !(Ref->flags & TESForm::FormFlags::kFormFlags_NotCastShadows);
		LightPoint->CanCarry = 0;
	}

}

static __declspec(naked) void AddCastShadowFlagHook() {

	__asm {
		mov     esi, [ebp + 0x008]
		pushad
		mov		ecx, [ebp - 0x164]
		push	eax
		push	ecx
		push	esi
		call	AddCastShadowFlag
		pop		esi
		pop		ecx
		pop		eax
		popad
		pop		ecx
		pop		esi
		mov     ecx, [ebp - 0x34]
		jmp		Jumpers::Shadows::AddCastShadowFlagReturn
	}

}

static void LeavesNodeName(BSTreeNode* TreeNode) {
	
	TreeNode->m_children.data[1]->SetName("Leaves");

}

static __declspec(naked) void LeavesNodeNameHook() {

	__asm {
		pushad
		push	eax 
		call	LeavesNodeName
		pop		eax
		popad
		jmp		Jumpers::Shadows::LeavesNodeNameReturn
	}

}
