#include "D3D9Device.h"

TESRDirect3DDevice9::TESRDirect3DDevice9(IDirect3D9Ex* D3DInterface, IDirect3DDevice9Ex* D3DDevice) : IDirect3DDevice9Ex() {
	this->D3DInterface = D3DInterface;
	this->D3DDevice = D3DDevice;
}

TESRDirect3DDevice9::~TESRDirect3DDevice9() { }

STDMETHODIMP TESRDirect3DDevice9::QueryInterface(REFIID riid, void **ppvObj) {
	return D3DDevice->QueryInterface(riid, ppvObj);
}

STDMETHODIMP_(ULONG) TESRDirect3DDevice9::AddRef() {
	return D3DDevice->AddRef();
}

STDMETHODIMP_(ULONG) TESRDirect3DDevice9::Release() {
	ULONG count = D3DDevice->Release();
	if (count == 0) delete this;
	return count;
}

STDMETHODIMP TESRDirect3DDevice9::TestCooperativeLevel() {
	return D3DDevice->TestCooperativeLevel();
}

STDMETHODIMP_(UINT) TESRDirect3DDevice9::GetAvailableTextureMem() {
	return D3DDevice->GetAvailableTextureMem();
}

STDMETHODIMP TESRDirect3DDevice9::EvictManagedResources() {
	return D3DDevice->EvictManagedResources();
}

STDMETHODIMP TESRDirect3DDevice9::GetDirect3D(IDirect3D9 **ppD3D9) {
	HRESULT hr = D3DDevice->GetDirect3D(ppD3D9);
	if (SUCCEEDED(hr)) *ppD3D9 = (IDirect3D9*)D3DInterface;
	return hr;
}

STDMETHODIMP TESRDirect3DDevice9::GetDeviceCaps(D3DCAPS9 *pCaps) {
	return D3DDevice->GetDeviceCaps(pCaps);
}

STDMETHODIMP TESRDirect3DDevice9::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE *pMode) {
	return D3DDevice->GetDisplayMode(iSwapChain, pMode);
}

STDMETHODIMP TESRDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) {
	return D3DDevice->GetCreationParameters(pParameters);
}

STDMETHODIMP TESRDirect3DDevice9::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap) {
	return D3DDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

STDMETHODIMP_(void) TESRDirect3DDevice9::SetCursorPosition(int X, int Y, DWORD Flags) {
	D3DDevice->SetCursorPosition(X, Y, Flags);
}

STDMETHODIMP_(BOOL) TESRDirect3DDevice9::ShowCursor(BOOL bShow) {
	return D3DDevice->ShowCursor(bShow);
}

STDMETHODIMP TESRDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **pSwapChain) {
	return D3DDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

STDMETHODIMP TESRDirect3DDevice9::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain) {
	return D3DDevice->GetSwapChain(iSwapChain, pSwapChain);
}

COM_DECLSPEC_NOTHROW UINT STDMETHODCALLTYPE TESRDirect3DDevice9::GetNumberOfSwapChains() {
	return D3DDevice->GetNumberOfSwapChains();
}

STDMETHODIMP TESRDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS *pPresentationParameters) {
	return D3DDevice->Reset(pPresentationParameters);
}

STDMETHODIMP TESRDirect3DDevice9::Present(CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion) {
	return D3DDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

STDMETHODIMP TESRDirect3DDevice9::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 **ppBackBuffer) {
	return D3DDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

STDMETHODIMP TESRDirect3DDevice9::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus) {
	return D3DDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

STDMETHODIMP TESRDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs) {
	return D3DDevice->SetDialogBoxMode(bEnableDialogs);
}

STDMETHODIMP_(void) TESRDirect3DDevice9::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP *pRamp) {
	return D3DDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

STDMETHODIMP_(void) TESRDirect3DDevice9::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP *pRamp) {
	return D3DDevice->GetGammaRamp(iSwapChain, pRamp);
}

STDMETHODIMP TESRDirect3DDevice9::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle) {
	return D3DDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle) {
	return D3DDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle) {
	return D3DDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle) {
	return D3DDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle) {
	return D3DDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle) {
	return D3DDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle) {
	return D3DDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::UpdateSurface(IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect, IDirect3DSurface9 *pDestinationSurface, CONST POINT *pDestPoint) {
	return D3DDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

STDMETHODIMP TESRDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture) {
	return D3DDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

STDMETHODIMP TESRDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface) {
	return D3DDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

STDMETHODIMP TESRDirect3DDevice9::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9 *pDestSurface) {
	return D3DDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

STDMETHODIMP TESRDirect3DDevice9::StretchRect(IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter) {
	return D3DDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

STDMETHODIMP TESRDirect3DDevice9::ColorFill(IDirect3DSurface9 *pSurface, CONST RECT *pRect, D3DCOLOR color) {
	return D3DDevice->ColorFill(pSurface, pRect, color);
}

STDMETHODIMP TESRDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle) {
	return D3DDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

STDMETHODIMP TESRDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget) {
	return D3DDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

STDMETHODIMP TESRDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget) {
	return D3DDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

STDMETHODIMP TESRDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9 *pNewZStencil) {
	return D3DDevice->SetDepthStencilSurface(pNewZStencil);
}

STDMETHODIMP TESRDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9 **ppZStencilSurface) {
	return D3DDevice->GetDepthStencilSurface(ppZStencilSurface);
}

STDMETHODIMP TESRDirect3DDevice9::BeginScene() {
	return D3DDevice->BeginScene();
}

STDMETHODIMP TESRDirect3DDevice9::EndScene() {
	return D3DDevice->EndScene();
}

STDMETHODIMP TESRDirect3DDevice9::Clear(DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) {
	return D3DDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

STDMETHODIMP TESRDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix) {
	return D3DDevice->SetTransform(State, pMatrix);
}

STDMETHODIMP TESRDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix) {
	return D3DDevice->GetTransform(State, pMatrix);
}

STDMETHODIMP TESRDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix) {
	return D3DDevice->MultiplyTransform(State, pMatrix);
}

STDMETHODIMP TESRDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9 *pViewport) {
	return D3DDevice->SetViewport(pViewport);
}

STDMETHODIMP TESRDirect3DDevice9::GetViewport(D3DVIEWPORT9 *pViewport) {
	return D3DDevice->GetViewport(pViewport);
}

STDMETHODIMP TESRDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9 *pMaterial) {
	return D3DDevice->SetMaterial(pMaterial);
}

STDMETHODIMP TESRDirect3DDevice9::GetMaterial(D3DMATERIAL9 *pMaterial) {
	return D3DDevice->GetMaterial(pMaterial);
}

STDMETHODIMP TESRDirect3DDevice9::SetLight(DWORD Index, CONST D3DLIGHT9 *pLight) {
	return D3DDevice->SetLight(Index, pLight);
}

STDMETHODIMP TESRDirect3DDevice9::GetLight(DWORD Index, D3DLIGHT9 *pLight) {
	return D3DDevice->GetLight(Index, pLight);
}

STDMETHODIMP TESRDirect3DDevice9::LightEnable(DWORD Index, BOOL Enable) {
	return D3DDevice->LightEnable(Index, Enable);
}

STDMETHODIMP TESRDirect3DDevice9::GetLightEnable(DWORD Index, BOOL *pEnable) {
	return D3DDevice->GetLightEnable(Index, pEnable);
}

STDMETHODIMP TESRDirect3DDevice9::SetClipPlane(DWORD Index, CONST float *pPlane) {
	return D3DDevice->SetClipPlane(Index, pPlane);
}

STDMETHODIMP TESRDirect3DDevice9::GetClipPlane(DWORD Index, float *pPlane) {
	return D3DDevice->GetClipPlane(Index, pPlane);
}

STDMETHODIMP TESRDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) {
	return D3DDevice->SetRenderState(State, Value);
}

STDMETHODIMP TESRDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue) {
	return D3DDevice->GetRenderState(State, pValue);
}

STDMETHODIMP TESRDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB) {
	return D3DDevice->CreateStateBlock(Type, ppSB);
}

STDMETHODIMP TESRDirect3DDevice9::BeginStateBlock() {
	return D3DDevice->BeginStateBlock();
}

STDMETHODIMP TESRDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9 **ppSB) {
	return D3DDevice->EndStateBlock(ppSB);
}

STDMETHODIMP TESRDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9 *pClipStatus) {
	return D3DDevice->SetClipStatus(pClipStatus);
}

STDMETHODIMP TESRDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9 *pClipStatus) {
	return D3DDevice->GetClipStatus(pClipStatus);
}

STDMETHODIMP TESRDirect3DDevice9::GetTexture(DWORD Sampler, IDirect3DBaseTexture9 **ppTexture) {
	return D3DDevice->GetTexture(Sampler, ppTexture);
}

STDMETHODIMP TESRDirect3DDevice9::SetTexture(DWORD Sampler, IDirect3DBaseTexture9 *pTexture) {
	return D3DDevice->SetTexture(Sampler, pTexture);
}

STDMETHODIMP TESRDirect3DDevice9::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue) {
	return D3DDevice->GetTextureStageState(Stage, Type, pValue);
}

STDMETHODIMP TESRDirect3DDevice9::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) {
	return D3DDevice->SetTextureStageState(Stage, Type, Value);
}

STDMETHODIMP TESRDirect3DDevice9::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue) {
	return D3DDevice->GetSamplerState(Sampler, Type, pValue);
}

STDMETHODIMP TESRDirect3DDevice9::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) {
	return D3DDevice->SetSamplerState(Sampler, Type, Value);
}

STDMETHODIMP TESRDirect3DDevice9::ValidateDevice(DWORD *pNumPasses) {
	return D3DDevice->ValidateDevice(pNumPasses);
}

STDMETHODIMP TESRDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY *pEntries) {
	return D3DDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP TESRDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries) {
	return D3DDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP TESRDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber) {
	return D3DDevice->SetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP TESRDirect3DDevice9::GetCurrentTexturePalette(UINT *PaletteNumber) {
	return D3DDevice->GetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP TESRDirect3DDevice9::SetScissorRect(CONST RECT *pRect) {
	return D3DDevice->SetScissorRect(pRect);
}

STDMETHODIMP TESRDirect3DDevice9::GetScissorRect(RECT *pRect) {
	return D3DDevice->GetScissorRect(pRect);
}

STDMETHODIMP TESRDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware) {
	return D3DDevice->SetSoftwareVertexProcessing(bSoftware);
}

COM_DECLSPEC_NOTHROW BOOL STDMETHODCALLTYPE TESRDirect3DDevice9::GetSoftwareVertexProcessing() {
	return D3DDevice->GetSoftwareVertexProcessing();
}

STDMETHODIMP TESRDirect3DDevice9::SetNPatchMode(float nSegments) {
	return D3DDevice->SetNPatchMode(nSegments);
}

COM_DECLSPEC_NOTHROW float STDMETHODCALLTYPE TESRDirect3DDevice9::GetNPatchMode() {
	return D3DDevice->GetNPatchMode();
}

STDMETHODIMP TESRDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) {
	return D3DDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

STDMETHODIMP TESRDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) {
	return D3DDevice->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

STDMETHODIMP TESRDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) {
	return D3DDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP TESRDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void *pIndexData, D3DFORMAT IndexDataFormat, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) {
	return D3DDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP TESRDirect3DDevice9::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9 *pDestBuffer, IDirect3DVertexDeclaration9 *pVertexDecl, DWORD Flags) {
	return D3DDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

STDMETHODIMP TESRDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9 **ppDecl) {
	return D3DDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
}

STDMETHODIMP TESRDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9 *pDecl) {
	return D3DDevice->SetVertexDeclaration(pDecl);
}

STDMETHODIMP TESRDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9 **ppDecl) {
	return D3DDevice->GetVertexDeclaration(ppDecl);
}

STDMETHODIMP TESRDirect3DDevice9::SetFVF(DWORD FVF) {
	return D3DDevice->SetFVF(FVF);
}

STDMETHODIMP TESRDirect3DDevice9::GetFVF(DWORD *pFVF) {
	return D3DDevice->GetFVF(pFVF);
}

STDMETHODIMP TESRDirect3DDevice9::CreateVertexShader(CONST DWORD *pFunction, IDirect3DVertexShader9 **ppShader) {
	return D3DDevice->CreateVertexShader(pFunction, ppShader);
}

STDMETHODIMP TESRDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9 *pShader) {
	return D3DDevice->SetVertexShader(pShader);
}

STDMETHODIMP TESRDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9 **ppShader) {
	return D3DDevice->GetVertexShader(ppShader);
}

STDMETHODIMP TESRDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister, CONST float *pConstantData, UINT Vector4fCount) {
	return D3DDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP TESRDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount) {
	return D3DDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP TESRDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount) {
	return D3DDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP TESRDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4iCount) {
	return D3DDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP TESRDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount) {
	return D3DDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP TESRDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT BoolCount) {
	return D3DDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP TESRDirect3DDevice9::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes, UINT Stride) {
	return D3DDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

STDMETHODIMP TESRDirect3DDevice9::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData, UINT *pOffsetInBytes, UINT *pStride) {
	return D3DDevice->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

STDMETHODIMP TESRDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber, UINT Setting) {
	return D3DDevice->SetStreamSourceFreq(StreamNumber, Setting);
}

STDMETHODIMP TESRDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber, UINT *pSetting) {
	return D3DDevice->GetStreamSourceFreq(StreamNumber, pSetting);
}

STDMETHODIMP TESRDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9 *pIndexData) {
	return D3DDevice->SetIndices(pIndexData);
}

STDMETHODIMP TESRDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9 **ppIndexData) {
	return D3DDevice->GetIndices(ppIndexData);
}

STDMETHODIMP TESRDirect3DDevice9::CreatePixelShader(CONST DWORD *pFunction, IDirect3DPixelShader9 **ppShader) {
	return D3DDevice->CreatePixelShader(pFunction, ppShader);
}

STDMETHODIMP TESRDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9 *pShader) {
	return D3DDevice->SetPixelShader(pShader);
}

STDMETHODIMP TESRDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9 **ppShader) {
	return D3DDevice->GetPixelShader(ppShader);
}

STDMETHODIMP TESRDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister, CONST float *pConstantData, UINT Vector4fCount) {
	return D3DDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP TESRDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount) {
	return D3DDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP TESRDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount) {
	return D3DDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP TESRDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4iCount) {
	return D3DDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP TESRDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, UINT  BoolCount) {
	return D3DDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP TESRDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT BoolCount) {
	return D3DDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP TESRDirect3DDevice9::DrawRectPatch(UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo) {
	return D3DDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

STDMETHODIMP TESRDirect3DDevice9::DrawTriPatch(UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo) {
	return D3DDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

STDMETHODIMP TESRDirect3DDevice9::DeletePatch(UINT Handle) {
	return D3DDevice->DeletePatch(Handle);
}

STDMETHODIMP TESRDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery) {
	return D3DDevice->CreateQuery(Type, ppQuery);
}

STDMETHODIMP TESRDirect3DDevice9::SetConvolutionMonoKernel(UINT width, UINT height, float * rows, float * columns) {
	return D3DDevice->SetConvolutionMonoKernel(width, height, rows, columns);
}

STDMETHODIMP TESRDirect3DDevice9::ComposeRects(IDirect3DSurface9 * pSrc, IDirect3DSurface9 * pDst, IDirect3DVertexBuffer9 * pSrcRectDescs, UINT NumRects, IDirect3DVertexBuffer9 * pDstRectDescs, D3DCOMPOSERECTSOP Operation, int Xoffset, int Yoffset) {
	return D3DDevice->ComposeRects(pSrc, pDst, pSrcRectDescs, NumRects, pDstRectDescs, Operation, Xoffset, Yoffset);
}

STDMETHODIMP TESRDirect3DDevice9::PresentEx(CONST RECT * pSourceRect, CONST RECT * pDestRect, HWND hDestWindowOverride, CONST RGNDATA * pDirtyRegion, DWORD dwFlags) {
	return D3DDevice->PresentEx(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

STDMETHODIMP TESRDirect3DDevice9::GetGPUThreadPriority(INT * pPriority) {
	return D3DDevice->GetGPUThreadPriority(pPriority);
}

STDMETHODIMP TESRDirect3DDevice9::SetGPUThreadPriority(INT Priority) {
	return D3DDevice->SetGPUThreadPriority(Priority);
}

STDMETHODIMP TESRDirect3DDevice9::WaitForVBlank(UINT iSwapChain) {
	return D3DDevice->WaitForVBlank(iSwapChain);
}

STDMETHODIMP TESRDirect3DDevice9::CheckResourceResidency(IDirect3DResource9 ** pResourceArray, UINT32 NumResources) {
	return D3DDevice->CheckResourceResidency(pResourceArray, NumResources);
}

STDMETHODIMP TESRDirect3DDevice9::SetMaximumFrameLatency(UINT MaxLatency) {
	return D3DDevice->SetMaximumFrameLatency(MaxLatency);
}

STDMETHODIMP TESRDirect3DDevice9::GetMaximumFrameLatency(UINT * pMaxLatency) {
	return D3DDevice->GetMaximumFrameLatency(pMaxLatency);
}

STDMETHODIMP TESRDirect3DDevice9::CheckDeviceState(HWND hDestinationWindow) {
	return D3DDevice->CheckDeviceState(hDestinationWindow);
}

STDMETHODIMP TESRDirect3DDevice9::CreateRenderTargetEx(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 ** ppSurface, HANDLE * pSharedHandle, DWORD Usage) {
	return D3DDevice->CreateRenderTargetEx(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle, Usage);
}

STDMETHODIMP TESRDirect3DDevice9::CreateOffscreenPlainSurfaceEx(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 ** ppSurface, HANDLE * pSharedHandle, DWORD Usage) {
	return D3DDevice->CreateOffscreenPlainSurfaceEx(Width, Height, Format, Pool, ppSurface, pSharedHandle, Usage);
}

STDMETHODIMP TESRDirect3DDevice9::CreateDepthStencilSurfaceEx(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 ** ppSurface, HANDLE * pSharedHandle, DWORD Usage) {
	return D3DDevice->CreateDepthStencilSurfaceEx(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle, Usage);
}

STDMETHODIMP TESRDirect3DDevice9::ResetEx(D3DPRESENT_PARAMETERS * pPresentationParameters, D3DDISPLAYMODEEX * pFullscreenDisplayMode) {
	return D3DDevice->ResetEx(pPresentationParameters, pFullscreenDisplayMode);
}

STDMETHODIMP TESRDirect3DDevice9::GetDisplayModeEx(UINT iSwapChain, D3DDISPLAYMODEEX * pMode, D3DDISPLAYROTATION * pRotation) {
	return D3DDevice->GetDisplayModeEx(iSwapChain, pMode, pRotation);
}
