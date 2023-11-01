#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <list>
#include <unordered_map>
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

#define DECLARE_INSTANCE(className)\
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
	void PrintMessage(const std::string& format, ...);
}

#define ASSERT_CONDITION(condition) if (!(condition))
#define ASSERT_MESSAGE(format, ...) CoreLog::PrintMessage(format, __VA_ARGS__);
#define ASSERT(condition, format, ...)\
	ASSERT_CONDITION(condition)\
	{\
		CoreLog::SetConsoleTextColor(PrintMessageType::Error);\
		ASSERT_MESSAGE(format, __VA_ARGS__)\
	}\

#define ASSERT_BOOLEAN(condition, format, ...)\
	ASSERT_CONDITION(condition)\
	{\
		CoreLog::SetConsoleTextColor(PrintMessageType::Error);\
		ASSERT_MESSAGE(format, __VA_ARGS__)\
		return false;\
	}\

#define LOG(type, format, ...)\
		CoreLog::SetConsoleTextColor(type);\
		CoreLog::PrintMessage(format, __VA_ARGS__);\

#define LOG_NULLPTR(ptr, rightptr, format, ...)\
		if (ptr == nullptr) {\
		LOG(PrintMessageType::Error, format, __VA_ARGS__)\
		return nullptr;\
		} else return rightptr;\

#define LOG_RETURN(condition, format, ...)\
	if (condition) {\
		LOG(PrintMessageType::Error, format, __VA_ARGS__)\
		return; }\

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

typedef sf::Vector2f vector2;
typedef sf::Vector2i vector2i;
typedef sf::Vector2u vector2u;

static vector2 vector2_origin(0.0f, 0.0f);

template <class T>
inline float LengthSqr(const sf::Vector2<T> vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

#include "utils/Timer.h"
