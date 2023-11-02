#ifndef _SCRIPTMANAGER_H
#define _SCRIPTMANAGER_H
#include "engine/Zigine.h"

extern "C"
{
	#include <lua/lua.h>
	#include <lua/lauxlib.h>
	#include <lua/lualib.h>
}

using LuaCFuntion = lua_CFunction;

struct LuaLibrary
{
	LuaCFuntion m_OpenFunction;
};

struct LuaMetaTable
{
	std::string m_FunctionName;
	LuaCFuntion m_InitFunction;
};

class ScriptManager final
{
public:
	void Init(const std::string& path = "");
	void Release();

	void Load(const std::string& name, std::function<void(lua_State* state)> function = {});

	void PushMetaTable(const std::string& name, const std::string& functionName, const LuaCFuntion initFunction);
	void PushNumber(const std::string& name, const int number);

	// USE THOSE METHODS ONLY IN CONSTRUCTORS OF YOUR CLASS
	void RegisterLibrary(const std::string& name, const LuaCFuntion openfunction);
	int RegisterLibraryFunctions(const luaL_Reg* functions);
	void RegisterMetaTable(const std::string& name, const std::string& functionName, const LuaCFuntion initFunction);
	void RegisterFile(const std::string& file);
	void RegisterNumber(const std::string& name, const int number);
	void RegisterFunctions(const luaL_Reg* functions);
private:
	void LoadStandardLibrary();
	void LoadLuaFile(const std::string& name);

	std::unordered_map<std::string, LuaLibrary> m_Libraries;
	std::unordered_map<std::string, LuaCFuntion> m_Functions;
	std::unordered_map<int, std::string> m_Numbers;
	std::unordered_map<std::string, LuaMetaTable> m_MetaTables;
	std::vector<std::string> m_Files;
private:
	std::string m_GamePath;
	lua_State* m_State;
};

DECLARE_INSTANCE_FUNCTION(ScriptManager, Scripts)

#endif // !_SCRIPTMANAGER_H
