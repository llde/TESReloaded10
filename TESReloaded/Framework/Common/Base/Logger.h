#pragma once

class Logger {
public:
	static void Initialize(char* FileName);
	static void Log(char* Message, ...);
	static void Debug(char* Message, ...);
	
//	static char			MessageBuffer[8192];
	static FILE*		LogFile;

};
