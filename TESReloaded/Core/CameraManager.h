#pragma once

class CameraManager { // Never disposed
public:
	static void Initialize();

	class CameraManagerCommands { // Never disposed
	public:
		CameraManagerCommands();

		bool			IsTranslating;
		bool			IsRotating;
		bool			IsLookingAt;
		bool			IsTranslatingToPosition;
		bool			IsRotatingToPosition;
		bool			IsLookingAtPosition;
		NiPoint3		Position;
		NiPoint3		Rotation;
		NiPoint3		LookingAtOffset;
		NiPoint3		LookingAtPosition;
		TESObjectREFR*	Ref;

		void			Execute(NiAVObject* CameraNode);

	};
	
	bool					IsFirstPerson();
	bool					IsVanity();
	void					SetFirstPerson(bool FirstPerson);
	void					SetSceneGraph();
	void					ResetCamera();
	void					ExecuteCommands(NiAVObject* CameraNode);

	Actor*					DialogTarget;
	NiPoint3				From;
	NiPoint3				FromOffset;
	CameraManagerCommands*	CameraCommands;
	bool					TogglePOV;

private:
	bool					FirstPersonView;
};