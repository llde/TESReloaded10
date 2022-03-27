#pragma once

class BinkManager { // Never disposed
public:
	
	struct BINKFRAMETEXTURES {
		UInt32 Ysize;
		UInt32 cRsize;
		UInt32 cBsize;
		UInt32 Asize;
		IDirect3DTexture9* Y;
		IDirect3DTexture9* cR;
		IDirect3DTexture9* cB;
		IDirect3DTexture9* A;
	};

	struct BINKTEXTURESET {
		BINKFRAMEBUFFERS Buffers;
		BINKFRAMETEXTURES Textures[BINKMAXFRAMEBUFFERS];
		BINKFRAMETEXTURES DrawingTextures;
	};
	
	struct POS_TC_VERTEX {
		float sx, sy, sz, rhw;
		float tu, tv;
	};

	static void		Initialize();

private:
	void			CreateTextures();
	void			LockTextures();
	void			UnlockTextures();
	void			FreeTextures();
	void			Draw();

public:
	void			Render(const char* MovieFilename);
	void			Close();

	D3DVERTEXELEMENT9				VertexDefinition[3];
	IDirect3DVertexDeclaration9*	VertexShaderDeclaration;
	ShaderRecordPixel*				Pixel;
	HBINK							Bink;
	BINKTEXTURESET					Textures;

};