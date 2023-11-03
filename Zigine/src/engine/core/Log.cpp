#include <Windows.h>
#include <string>

#include "Log.h"

void Log::SetConsoleTextColor(LogType type)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short byteColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	switch (type)
	{
	case LogType::Warning:
		byteColor = FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case LogType::Success:
		byteColor = FOREGROUND_GREEN;
		break;
	case LogType::Error:
		byteColor = FOREGROUND_RED;
		break;
	case LogType::Default:
	default:
		break;
	}

	SetConsoleTextAttribute(hConsole, byteColor);
}

void Log::Msg(LogType type, const std::string& format, ...)
{
	SetConsoleTextColor(type);

	const char* charFormat = format.c_str();

	va_list args;
	va_start(args, charFormat);
	vprintf(charFormat, args);
	va_end(args);

	printf("\n");

	SetConsoleTextColor();
}
