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
	void SetConsoleTextColor(LogType type = LogType::Default);
	void Msg(LogType type, const std::string& functionName, const std::string& format, ...);

	template <class _T, class... Args>
	_T Condition(_T condition, LogType type, const std::string& functionName, const std::string& format, Args... args)
	{
		if (condition)
			Msg(type, functionName, format, args...);

		return condition;
	}
}

#endif // !_LOG_H
