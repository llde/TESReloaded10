#pragma once

class EquipmentManager { // Never disposed
public:
	static void Initialize();

	enum PositionRotationType {
		None,
		Shield,
		Weapon,
		TwoHandWeapon,
		Staff,
		Bow,
		Light,
	};

	void			LoadForms();
	void			SetRotationPosition(NiAVObject* Object, PositionRotationType PositionRotation, UInt8 SitSleepState);
	void			SetTorchLight(Actor* Act, NiAVObject* Torch, UInt8 Enable);
	void			SetAnimations(HighProcess* Process, UInt8 LeftWeapon);
	void			SetAnimGroup(HighProcess* Process, UInt8 AnimGroup, UInt8 AnimType, const char* Filename);
	void			ResetAnimGroup(HighProcess* Process, UInt8 AnimGroup, UInt8 AnimType);

	TESIdleForm*	OnBackAnim;
	float			LeftTime;
};

void CreateEquipmentHook();