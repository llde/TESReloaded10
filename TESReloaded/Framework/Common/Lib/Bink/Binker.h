#pragma once

class Binker {
public:
	static void Render(IDirect3DDevice9* Device, const char* MovieFilename, unsigned int Width, unsigned int Height);
	static void Close(IDirect3DDevice9* Device);

};