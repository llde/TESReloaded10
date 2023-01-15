#include "Logger.h"
//char	Logger::MessageBuffer[8192];
FILE*	Logger::LogFile;

//#define debugmode

void Logger::Initialize(char* FileName) {

	LogFile = _fsopen(FileName, "w", _SH_DENYWR);

}

void Logger::Log(char* Message, ...) {

	va_list Args;

	if (LogFile) {
		va_start(Args, Message);
		vfprintf_s(LogFile, Message, Args);
		va_end(Args);
//		fputs(MessageBuffer, LogFile);
		fputc('\n', LogFile);
		fflush(LogFile);
	}

}

void Logger::Debug(char* Message, ...) {
#ifdef debugmode
	va_list Args;
	if (LogFile) {
		va_start(Args, Message);
		vfprintf_s(LogFile, Message, Args);
		va_end(Args);
		//		fputs(MessageBuffer, LogFile);
		fputc('\n', LogFile);
		fflush(LogFile);
	}
#endif // debugmode
}
