#include <stdio.h>
#include <stdarg.h>
#include "Zigine.h"

#include <Windows.h>

void CoreLog::SetConsoleTextColor(PrintMessageType type)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short byteColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	switch (type)
	{
	case Warning:
		byteColor = FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case Success:
		byteColor = FOREGROUND_GREEN;
		break;
	case Error:
		byteColor = FOREGROUND_RED;
		break;
	case Default:
	default:
		break;
	}

	SetConsoleTextAttribute(hConsole, byteColor);
}

void CoreLog::PrintMessage(const std::string& format, ...)
{
	const char* charFormat = format.c_str();

	va_list args;
	va_start(args, charFormat);
	vprintf(charFormat, args);
	va_end(args);

	printf("\n");

	SetConsoleTextColor();
}
