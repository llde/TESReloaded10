#include "bink.h"
#include "binktextures.h"
#include "Binker.h"

static HBINK Bink = NULL;
static BINKTEXTURESET BinkTextures = { NULL };
static bool IsInitialized = false;

void Binker::Render(IDirect3DDevice9* Device, const char* MovieFilename, unsigned int Width, unsigned int Height) {
	
	IDirect3DBaseTexture9* Texture0 = NULL;
	IDirect3DBaseTexture9* Texture1 = NULL;
	IDirect3DBaseTexture9* Texture2 = NULL;
	bool NewFrame = 0;
	char Filename[MAX_PATH];
	
	if (!IsInitialized) {
		Create_Bink_shaders(Device);
		IsInitialized = true;
	}
	if (!Bink) {
		GetCurrentDirectoryA(MAX_PATH, Filename);
		strcat(Filename, MovieFilename);
		Bink = BinkOpen(Filename, BINKNOFRAMEBUFFERS);
		if (Bink) {
			BinkSetVolume(Bink, 0, 0);
			BinkGetFrameBuffersInfo(Bink, &BinkTextures.bink_buffers);
			Create_Bink_textures(Device, &BinkTextures);
		}
	}
	if (Bink) {
		if (!BinkWait(Bink)) NewFrame = 1;
		if (NewFrame) {
			Lock_Bink_textures(&BinkTextures);
			BinkRegisterFrameBuffers(Bink, &BinkTextures.bink_buffers);
			BinkDoFrame(Bink);
			Unlock_Bink_textures(Device, &BinkTextures, Bink);
		}
		if (Bink->FrameNum != Bink->Frames) {
			Device->GetTexture(0, &Texture0);
			Device->GetTexture(1, &Texture1);
			Device->GetTexture(2, &Texture2);
			Draw_Bink_textures(Device, &BinkTextures, Width, Height, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
			Device->SetTexture(0, Texture0);
			Device->SetTexture(1, Texture1);
			Device->SetTexture(2, Texture2);
		}
		if (NewFrame) BinkNextFrame(Bink);
	}

}

void Binker::Close(IDirect3DDevice9* Device) {
	
	if (Bink) {
		Free_Bink_textures(Device, &BinkTextures);
		BinkClose(Bink);
		Bink = NULL;
	}

}