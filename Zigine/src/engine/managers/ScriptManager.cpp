#include "ScriptManager.h"
#include "TextureManager.h"

DEFINE_SECURE_INSTANCE_FUNCTION(ScriptManager, Scripts)

bool checkLua(lua_State* state, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(state, -1);
		Log::Msg(LogType::Error, __FUNCTION__, errormsg);
		return false;
	}

	return true;
}

void ScriptManager::Init(const std::string& path)
{
	m_GamePath = path;
	m_State = luaL_newstate();
	luaL_openlibs(m_State);

	LoadStandardLibrary();

	// Clear temporary memory
	m_Libraries.clear();
	m_Functions.clear();
	m_Files.clear();
	m_Numbers.clear();
}

void ScriptManager::Load(const std::string& name, std::function<void(lua_State* state)> function)
{
	std::string path = m_GamePath + name;
	const char* filename = path.c_str();
	if (checkLua(m_State, luaL_dofile(m_State, filename)))
	{
		if (function)
			function(m_State);
	}
}

void ScriptManager::PushMetaTable(const std::string& name, const std::string& functionName, const LuaCFuntion initFunction)
{
	const char* metaTableName = name.c_str();
	const char* functionMetaName = functionName.c_str();

	lua_pushcfunction(m_State, initFunction);
	lua_setglobal(m_State, functionMetaName);
	luaL_newmetatable(m_State, metaTableName);
}

void ScriptManager::PushNumber(const std::string& name, const int number)
{
	lua_pushnumber(m_State, number);
	lua_setglobal(m_State, name.c_str());
}

void ScriptManager::RegisterLibrary(const std::string& name, const LuaCFuntion openfunction)
{
	LuaLibrary library { openfunction };
	m_Libraries.emplace(name, library);
}

void ScriptManager::RegisterFile(const std::string& file)
{
	m_Files.push_back(file);
}

void ScriptManager::RegisterNumber(const std::string& name, const int number)
{
	m_Numbers.emplace(number, name);
}

void ScriptManager::RegisterFunctions(const luaL_Reg* functions)
{
	for (const luaL_Reg* function = functions; function->func; ++function)
		m_Functions.emplace(function->name, function->func);
}

int ScriptManager::RegisterLibraryFunctions(const luaL_Reg* functions)
{
	luaL_newlib(m_State, functions);
	return 1;
}

void ScriptManager::RegisterMetaTable(const std::string& name, const std::string& functionName,
	const LuaCFuntion initFunction)
{
	LuaMetaTable metaTable { functionName, initFunction };
	m_MetaTables.emplace(name, metaTable);
}

void ScriptManager::LoadStandardLibrary()
{
	for (auto& [name, library] : m_Libraries)
	{
		luaL_requiref(m_State, name.c_str(), library.m_OpenFunction, 1);
		lua_pop(m_State, 1);
	}

	const auto include = [](lua_State* state) {
		const char* path = lua_tostring(state, 1);
		Scripts()->Load(path);
		return 0;
	};
	const auto findmetatable = [](lua_State* state) {
		const char* name = lua_tostring(state, 1);
		luaL_getmetatable(state, name);
		lua_setmetatable(state, -1);
		return 1;
	};
	const auto isstring = [](lua_State* state) {
		lua_pushboolean(state, lua_isstring(state, -1));
		return 1;
	};
	const auto isnumber = [](lua_State* state) {
		lua_pushboolean(state, lua_isnumber(state, -1));
		return 1;
	};
	const auto isbool = [](lua_State* state) {
		lua_pushboolean(state, lua_isboolean(state, -1));
		return 1;
	};

	const struct luaL_Reg enginebaselib[] =
	{
		{ "include", include },
		{ "isstring", isstring },
		{ "isnumber", isnumber },
		{ "isbool", isbool },
		{ "FindMetaTable", findmetatable },
		{ nullptr, nullptr }
	};

	RegisterFunctions(enginebaselib);

	for (auto& [name, function] : m_Functions)
		lua_register(m_State, name.c_str(), function);

	for (auto& [number, name] : m_Numbers)
		PushNumber(name, number);

	for (auto& [metaName, metaTable] : m_MetaTables)
		PushMetaTable(metaName, metaTable.m_FunctionName, metaTable.m_InitFunction);

	for (auto file : m_Files)
		LoadLuaFile(file);
}

void ScriptManager::LoadLuaFile(const std::string& name)
{
	const char* filename = name.c_str();
	checkLua(m_State, luaL_dofile(m_State, filename));
}

void ScriptManager::Release()
{
	lua_close(m_State);
}
