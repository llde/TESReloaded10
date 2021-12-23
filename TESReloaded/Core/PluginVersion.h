#pragma once

class PluginVersion {

public:
	static void CreateVersionString();
	static char VersionString[64];

private:
	static void AddVersion(char* FileName);

};