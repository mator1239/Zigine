#include <assert.h>
#include "FileSystem.h"
#include "ScriptManager.h"
#include "TextureManager.h"

DEFINE_INSTANCE_FUNCTION(TextureManager, Textures)

TextureManager::TextureManager()
{
	const auto texture = [](lua_State* state) {
		const char* key = lua_tostring(state, 1);
		const char* path = lua_tostring(state, 1);
		Textures()->Load(key, path);

		return 0;
	};
	const struct luaL_Reg textureFunctions[] =
	{
		{ "texture", texture },
		{ nullptr, nullptr }
	};

	Scripts()->RegisterFunctions(textureFunctions);
}

sf::Texture* TextureManager::Load(const std::string& key, const std::string& filename)
{
	if (Find(key))
		return Get(key);

	std::string path = Files()->GetGamePath() + "/" + filename;

	sf::Texture* texture = new sf::Texture();
	Log::Condition(texture->loadFromFile(path) == false, LogType::Error, __FUNCTION__, 
		"Failed to load texture: %s", path);
	texture->setSmooth(true);

	m_Textures.emplace(key, texture);

	return texture;
}

bool TextureManager::Find(const std::string& key)
{
	return m_Textures.find(key) != m_Textures.end();
}

sf::Texture* TextureManager::Get(const std::string& key)
{
	return m_Textures[key];
}
