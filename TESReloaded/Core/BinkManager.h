#pragma once

class BinkManager { // Never disposed
public:
	static void Initialize();
	
	void			Render(const char* MovieFilename);
	void			Close();

	HBINK			Bink;
	BINKTEXTURESET	BinkTextures;

};