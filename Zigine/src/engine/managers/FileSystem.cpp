#include <filesystem>

#include "ScriptManager.h"
#include "FileSystem.h"

DEFINE_SECURE_INSTANCE_FUNCTION(FileSystem, Files)

int FileSystemLuaLoad(lua_State* state)
{
	const auto gameDirectory = [](lua_State* state) {
		const char* path = lua_tostring(state, 1);
		Files()->SetGameDirectory(path);

		return 0;
	};
	const auto isDirectory = [](lua_State* state) {
		const char* path = lua_tostring(state, 1);
		bool isDirectoryExists = Files()->IsDirectory(path);

		lua_pushboolean(state, isDirectoryExists);
		return 1;
	};
	const auto exists = [](lua_State* state) {
		const char* file = lua_tostring(state, 1);
		const char* path = lua_tostring(state, 2);
		bool isExists = Files()->Exists(file, path);

		lua_pushboolean(state, isExists);
		return 1;
	};
	const auto size = [](lua_State* state) {
		const char* file = lua_tostring(state, 1);
		const char* path = lua_tostring(state, 2);
		int fileSize = Files()->GetFileSize(file, path);

		lua_pushinteger(state, fileSize);
		return 1;
	};
	const auto createDirectory = [](lua_State* state) {
		const char* path = lua_tostring(state, 1);
		Files()->CreateDirectory(path);

		return 0;
	};

	const struct luaL_Reg libraryFunctions[] =
	{
		{ "SetGameDir", gameDirectory },
		{ "CreateDir", createDirectory },
		{ "IsDir", isDirectory },
		{ "Exists", exists },
		{ "Size", size },
		{ nullptr, nullptr },
	};

	return Scripts()->RegisterLibraryFunctions(libraryFunctions);
}

FileSystem::FileSystem()
{
	m_GamePath = "game/"; // default game path

	Scripts()->RegisterLibrary("file", FileSystemLuaLoad);
}

std::vector<std::string> FileSystem::GetFiles(const std::string& path)
{
	std::vector<std::string> files {};

	std::string fullPath = m_GamePath + path;
	if (!std::filesystem::exists(fullPath))
		return files;

	for (const auto& entry : std::filesystem::directory_iterator(fullPath))
	{
		std::string filePath = entry.path().string();
		files.push_back(filePath);
	}

	return files;
}

void FileSystem::CreateDirectory(const std::string& name)
{
	std::string path = m_GamePath + name;
	std::filesystem::create_directory(path);
}

void FileSystem::SetGameDirectory(const std::string& path)
{
	m_GamePath = path;
}

bool FileSystem::IsDirectory(const std::string& path)
{
	return std::filesystem::is_directory(m_GamePath + path);
}

bool FileSystem::Exists(const std::string& file, const std::string& path)
{
	std::string fullPath = m_GamePath + path + "/" + file;
	return std::filesystem::exists(fullPath);
}

int FileSystem::GetFileSize(const std::string& file, const std::string& path)
{
	return std::filesystem::file_size(path + "/" + file);
}
