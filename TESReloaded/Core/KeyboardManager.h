#pragma once

class KeyboardManager { // Never disposed
public:
	KeyboardManager();

	bool	OnKeyDown(UInt16 KeyCode);
	bool	OnKeyPressed(UInt16 KeyCode);
	bool	OnKeyUp(UInt16 KeyCode);
	bool	OnMouseDown(UInt8 ButtonIndex);
	bool	OnMousePressed(UInt8 ButtonIndex);
	bool	OnMouseUp(UInt8 ButtonIndex);
	bool	OnControlDown(UInt16 ControlID);
	bool	OnControlPressed(UInt16 ControlID);
	bool	OnControlUp(UInt16 ControlID);
	void	SetControlState(UInt8 ControlID, UInt8 CurrentState, UInt8 PreviousState);

};