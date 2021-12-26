#pragma once

static void RaiseEvent(Actor* Act, Actor* TargetAct, GameEventManager::EventEnum GameEvent) {
	
	if (Act) {
		switch (GameEvent) {
			case GameEventManager::OnHit:
				if (Act == Player) {
					HighProcess* Proc = (HighProcess*)Act->process;
					InventoryChanges::EntryData* WeaponData = Proc->equippedWeaponData;
					if (WeaponData) {
						TESForm* EquippedObject = WeaponData->type;
						if (EquippedObject && EquippedObject->formType == TESForm::FormType::kFormType_Weapon && ((TESObjectWEAP*)EquippedObject)->wtype <= TESObjectWEAP::kWeapType_BluntTwoHand) TheGameEventManager->OnHitByPlayer();
					}
				}
				break;
			default:
				break;
		}
	}

}

static __declspec(naked) void HitEventHook() {
	
	__asm {
		pushad
		push	1
		push	esi
		push	edi
		call	RaiseEvent
		add		esp, 12
		popad
		push	256
		jmp		kHitEventReturn
	}

}