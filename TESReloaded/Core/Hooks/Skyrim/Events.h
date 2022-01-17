#pragma once

void RaiseEvent(Actor* Act, Actor* TargetAct, GameEventManager::EventEnum GameEvent) {
	
	if (Act) {
		switch (GameEvent) {
			case GameEventManager::OnHit:
				if (Act == Player) {
					TESForm* EquippedObject = Act->GetEquippedObject(ActorProcessManager::EquippedHand::kEquippedHand_Right);
					if (EquippedObject && EquippedObject->formType == TESForm::FormType::kFormType_Weapon && ((TESObjectWEAP*)EquippedObject)->gameData.type <= TESObjectWEAP::WeaponType::kType_TwoHandAxe) TheGameEventManager->OnHitByPlayer();
				}
				break;
			default:
				break;
		}
	}

}

static __declspec(naked) void HitEventHook() {
	
	__asm {
		mov		ebp, [esp + 0x24]
		add		esp, 8
		pushad
		push	1
		push	esi
		push	ebp
		call	RaiseEvent
		add		esp, 12
		popad
		jmp		kHitEventReturn
	}

}