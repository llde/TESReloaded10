#pragma once

class BaseScript {
public:
	BaseScript();

	virtual void	Run() = 0;

	float			ElapsedTime;
};

class LowHSoundScript : public BaseScript { // Never disposed
public:
	LowHSoundScript();

	virtual void	Run();

	TESSound*		HeartSlow;
};

class LowFSoundScript : public BaseScript { // Never disposed
public:
	LowFSoundScript();

	virtual void	Run();

	TESSound*		BreathingF;
	TESSound*		BreathingM;
	float			BreathingTime;
};

class PurgerScript : public BaseScript { // Never disposed
public:
	PurgerScript();

	virtual void	Run();
};

class GravityScript : public BaseScript { // Never disposed
public:
	GravityScript();

	virtual void	Run();
};

class EquipmentSetupScript : public BaseScript { // Never disposed
public:
	EquipmentSetupScript();

	enum StepType {
		None,
		Request,
		Choice,
		Normal,
		Combat,
		Sleeping,
		Swimming,
	};

	virtual void			Run();

	void					EquipItems(StepType From, StepType To);
	StepType				GetCurrentEquipmentType();

	std::vector<TESForm*>	Items[4];
	TESObjectWEAP*			LeftWeapon[4];
	StepType				ConfigStep;
	StepType				GameStep;
	bool					CombatState;
};

class ScriptManager { // Never disposed
public:
	ScriptManager();

	void					LoadForms();
	void					Run();

	LowHSoundScript*		LowHSound;
	LowFSoundScript*		LowFSound;
	PurgerScript*			Purger;
	GravityScript*			Gravity;
	EquipmentSetupScript*	EquipmentSetup;
};

void CreateScriptHook();