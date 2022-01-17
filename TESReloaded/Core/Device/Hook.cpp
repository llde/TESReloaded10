#include "Hook.h"
#include "Device.h"

static HRESULT STDMETHODCALLTYPE CreateDevice(IDirect3D9Ex* D3DInterface, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9Ex** ppReturnedDeviceInterface) {
	
	HRESULT R = D3DInterface->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, (IDirect3DDevice9**)ppReturnedDeviceInterface);
	//HRESULT R = D3DInterface->CreateDeviceEx(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, NULL, ppReturnedDeviceInterface);
	*ppReturnedDeviceInterface = new TESRDirect3DDevice9(D3DInterface, *ppReturnedDeviceInterface);
	return R;
	
}

static __declspec(naked) void CreateDeviceHook()
{

	__asm
	{
		mov		eax, [ecx + 0x40]
		call	CreateDevice
		jmp		Jumpers::CreateDevice::Return
	}

}

void AttachDeviceHooks() {

	SafeWriteJump(Jumpers::CreateDevice::Hook, (UInt32)CreateDeviceHook);

}
