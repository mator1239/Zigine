#ifndef _ZIGINE_H
#define _ZIGINE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <list>

#include <memory>
#include <stack>

#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace Math
{
	constexpr float PI = 3.141592653589793238462643383279f;
}

#define __DISABLE_CURRENT_WARNINGS 4244 4267 4305
#pragma warning(disable: __DISABLE_CURRENT_WARNINGS)

#define DECLARE_CLASS(thisClass, baseClass)\
	typedef baseClass BaseClass;\
	typedef thisClass ThisClass;

#define DECLARE_INSTANCE_FUNCTION(className, name)\
	extern std::unique_ptr<className> __s_Instance_##className;\
	extern inline className* name();\

#define DEFINE_INSTANCE_FUNCTION(className, name)\
	std::unique_ptr<className> __s_Instance_##className = std::make_unique<className>();\
	inline className* name()\
	{\
		return __s_Instance_##className.get();\
	}

#define DEFINE_SECURE_INSTANCE_FUNCTION(className, name)\
	std::unique_ptr<className> __s_Instance_##className = nullptr;\
	inline className* name()\
	{\
		if (__s_Instance_##className == nullptr)\
			__s_Instance_##className = std::make_unique<className>();\
		return __s_Instance_##className.get();\
	}

#define SINGLETON(className)\
	static className* getInstance()\
	{\
		static className s_Instance;\
		return &s_Instance;\
	}\

enum PrintMessageType
{
	Default,
	Warning,
	Success,
	Error
};

namespace CoreLog
{
	static PrintMessageType m_Type;

	void SetConsoleTextColor(PrintMessageType type = PrintMessageType::Default);
	void PrintMessage(const std::string& functionName, const std::string& format, ...);
}

#define _T(s) s

#define LOG(type, format, ...)\
		CoreLog::SetConsoleTextColor(type);\
		CoreLog::PrintMessage(_T(__FUNCTION__), format, __VA_ARGS__);\

#define LOG_NULLPTR(ptr, rightptr, format, ...)\
		if (ptr == nullptr) {\
		LOG(PrintMessageType::Error, format, __VA_ARGS__)\
		return nullptr;\
		} else return rightptr;\

#define LOG_RETURN(condition, format, ...)\
	if (condition) {\
		LOG(PrintMessageType::Error, format, __VA_ARGS__)\
		return; }\

#define LOG_CONDITION(condition, format, ...)\
	if (!(condition)) {\
		LOG(PrintMessageType::Error, format, __VA_ARGS__)\
		return nullptr; }\

#define DEFINE_MANAGER_ARGUMENT_FUNCTION(className, functionName, makeStatic)\
	template <class _T, class... _Types>\
	makeStatic _T* functionName(_Types&&... args);\

#define SETUP_MANAGER_FUNCTION(className, baseClass, functionName)\
	template<class _T, class... _Types>\
	inline _T* className::functionName(_Types&& ...args)\
	{\
		_T* c = (new _T(std::forward<_Types>(args)...));\
		std::unique_ptr<baseClass> uPtr { c };

#define END_DECLARE_MANAGER_FUNCTION()\
		return c;\
	}\

#define INITIALIZE_MANAGER_ARRAY(arrayName)\
	arrayName.push_back(std::move(uPtr));

#define ADD_MANAGER_FUNCTION_CODE

#define interface_class class
#define abstract_class class

#ifndef ZIGINE_BUILD
	#ifdef ZIGINE_BUILD_DLL
		#define ZIGINE_API __declspec(dllexport)
	#else
		#define ZIGINE_API __declspec(dllimport)
	#endif
#endif // !ZIGINE_BUILD

#include "utils/Timer.h"
#include "utils/Math.h"

#endif // !_ZIGINE_H
