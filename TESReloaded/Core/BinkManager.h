#pragma once

class BinkManager { // Never disposed
public:
	static void Initialize();
	
	void			Open(const char* MovieFilename);
	void			Render();
	void			Close();

	HBINK			Bink;
	BINKTEXTURESET	BinkTextures;

};