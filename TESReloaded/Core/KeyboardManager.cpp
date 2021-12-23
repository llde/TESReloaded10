#define KeyboardCurrentState Global->GetInputKeyboard()->CurrentKeyState
#define KeyboardPreviousState Global->GetInputKeyboard()->PreviousKeyState
#define MouseCurrentState Global->GetInputMouse()->CurrentMouseState.rgbButtons
#define MousePreviousState Global->GetInputMouse()->PreviousMouseState.rgbButtons

KeyboardManager::KeyboardManager() {

	Logger::Log("Starting the keyboard manager...");
	TheKeyboardManager = this;

}

bool KeyboardManager::OnKeyDown(UInt16 KeyCode) {

	if (KeyCode >= 256) return OnMouseDown(KeyCode - 256);
	if (KeyCode != 255 && KeyboardCurrentState[KeyCode] && !KeyboardPreviousState[KeyCode]) return true;
	return false;

}

bool KeyboardManager::OnKeyPressed(UInt16 KeyCode) {

	if (KeyCode >= 256) return OnMousePressed(KeyCode - 256);
	if (KeyCode != 255 && KeyboardCurrentState[KeyCode] && KeyboardPreviousState[KeyCode]) return true;
	return false;

}

bool KeyboardManager::OnKeyUp(UInt16 KeyCode) {

	if (KeyCode >= 256) return OnMouseUp(KeyCode - 256);
	if (KeyCode != 255 && !KeyboardCurrentState[KeyCode] && KeyboardPreviousState[KeyCode]) return true;
	return false;

}

bool KeyboardManager::OnMouseDown(UInt8 ButtonIndex) {

	if (ButtonIndex != 255 && MouseCurrentState[ButtonIndex] && !MousePreviousState[ButtonIndex]) return true;
	return false;

}

bool KeyboardManager::OnMousePressed(UInt8 ButtonIndex) {

	if (ButtonIndex != 255 && MouseCurrentState[ButtonIndex] && MousePreviousState[ButtonIndex]) return true;
	return false;

}

bool KeyboardManager::OnMouseUp(UInt8 ButtonIndex) {

	if (ButtonIndex != 255 && !MouseCurrentState[ButtonIndex] && MousePreviousState[ButtonIndex]) return true;
	return false;

}

#if defined(OBLIVION)
#define KeyboardControls Global->GetInputKeyboard()->KeyboardInputControls
#define MouseControls Global->GetInputMouse()->MouseInputControls

bool KeyboardManager::OnControlDown(UInt16 ControlID) {

	return OnKeyDown(KeyboardControls[ControlID]) + OnMouseDown(MouseControls[ControlID]);

}

bool KeyboardManager::OnControlPressed(UInt16 ControlID) {

	return OnKeyPressed(KeyboardControls[ControlID]) + OnMousePressed(MouseControls[ControlID]);

}

bool KeyboardManager::OnControlUp(UInt16 ControlID) {

	return OnKeyUp(KeyboardControls[ControlID]) + OnMouseUp(MouseControls[ControlID]);

}

void KeyboardManager::SetControlState(UInt8 ControlID, UInt8 CurrentState, UInt8 PreviousState) {

	UInt16 Source = KeyboardControls[ControlID];

	if (Source != 255) {
		KeyboardCurrentState[Source] = CurrentState;
		KeyboardPreviousState[Source] = PreviousState;
	}
	Source = MouseControls[ControlID];
	if (Source != 255) {
		MouseCurrentState[Source] = CurrentState;
		MousePreviousState[Source] = PreviousState;
	}

}
#elif defined(SKYRIM)
bool KeyboardManager::OnControlDown(UInt16 ControlID) { return false; }
bool KeyboardManager::OnControlPressed(UInt16 ControlID) { return false; }
bool KeyboardManager::OnControlUp(UInt16 ControlID) { return false; }
void KeyboardManager::SetControlState(UInt8 ControlID, UInt8 CurrentState, UInt8 PreviousState) {}
#endif