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
#include "core/Log.h"

#endif // !_ZIGINE_H
