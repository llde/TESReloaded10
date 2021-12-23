char	Logger::MessageBuffer[1024];
FILE*	Logger::LogFile;

void Logger::Initialize(char* FileName) {

	LogFile = _fsopen(FileName, "w", _SH_DENYWR);

}

void Logger::Log(char* Message, ...) {

	va_list Args;

	if (LogFile) {
		va_start(Args, Message);
		vsprintf_s(MessageBuffer, sizeof(MessageBuffer), Message, Args);
		va_end(Args);
		fputs(MessageBuffer, LogFile);
		fputc('\n', LogFile);
		fflush(LogFile);
	}

}