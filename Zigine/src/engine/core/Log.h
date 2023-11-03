#ifndef _LOG_H
#define _LOG_H

enum class LogType
{
	Default,
	Warning,
	Success,
	Error
};

namespace Log
{
#ifdef _DEBUG
	void SetConsoleTextColor(LogType type = LogType::Default);
	void Msg(LogType type, const std::string& format, ...);

	template <class _T, class... Args>
	_T Condition(_T condition, const std::string& format, Args... args)
	{
		if (condition)
			Msg(LogType::Error, format, args...);

		return condition;
	}
#else
	void SetConsoleTextColor(LogType type = LogType::Default) {}
	void Msg(LogType type, const std::string& format, ...) {}

	template <class _T, class... Args>
	_T Condition(_T condition, LogType type, const std::string& format, Args... args) {}
#endif // _DEBUG
}

#endif // !_LOG_H
