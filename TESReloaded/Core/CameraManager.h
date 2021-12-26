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
	
	void					ResetCamera();
	void					SetSceneGraph();
	bool					IsVanityView();
	void					ExecuteCommands(NiAVObject* CameraNode);

	Actor*					DialogTarget;
	NiPoint3				From;
	NiPoint3				FromOffset;
	CameraManagerCommands*	CameraCommands;
	bool					FirstPersonView;
};

void CreateCameraModeHook();