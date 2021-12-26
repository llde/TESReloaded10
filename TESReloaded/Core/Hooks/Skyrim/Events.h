#pragma once

void RaiseEvent(Actor* Act, Actor* TargetAct, GameEventManager::EventEnum GameEvent) {
	
	if (Act) {
		switch (GameEvent) {
			case GameEventManager::OnHit:
				if (Act == Player) {
#if defined(OBLIVION)
					HighProcess* Proc = (HighProcess*)Act->process;
					InventoryChanges::EntryData* WeaponData = Proc->equippedWeaponData;
					if (WeaponData) {
						TESForm* EquippedObject = WeaponData->type;
						if (EquippedObject && EquippedObject->formType == TESForm::FormType::kFormType_Weapon && ((TESObjectWEAP*)EquippedObject)->wtype <= TESObjectWEAP::kWeapType_BluntTwoHand) TheGameEventManager->OnHitByPlayer();
					}
#elif defined (SKYRIM)
					TESForm* EquippedObject = Act->GetEquippedObject(ActorProcessManager::EquippedHand::kEquippedHand_Right);
					if (EquippedObject && EquippedObject->formType == TESForm::FormType::kFormType_Weapon && ((TESObjectWEAP*)EquippedObject)->wtype <= TESObjectWEAP::WeaponType::kType_TwoHandAxe) TheGameEventManager->OnHitByPlayer();
#endif
				}
				break;
			default:
				break;
		}
	}

}

static __declspec(naked) void HitEventHook()
{
#if defined(OBLIVION)
	__asm
	{
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
#elif defined(SKYRIM)
	__asm
	{
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
#endif
}