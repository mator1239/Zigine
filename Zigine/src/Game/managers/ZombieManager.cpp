#include "engine/managers/ScriptManager.h"
#include "engine/managers/FileSystem.h"
#include "engine/managers/TextureManager.h"

#include "ZombieManager.h"

DEFINE_INSTANCE_FUNCTION(ZombieManager, Zombies)

ZombieManager::ZombieManager()
{
	auto configs = filesystem()->GetFiles("scripts/configs/zombies");

	Scripts()->RegisterNumber("ZOMBIE_DEFAULT", ZOMBIE_DEFAULT);
	Scripts()->RegisterMetaTable("ZombieConfig", "ZombieConfig", ZombieConfig::CreateConfig);

	const auto zombieConfigLoad = [](lua_State* state) {
		if (lua_istable(state, -1))
		{
			ZombieConfig config = {};

			lua_pushstring(state, "Texture"); lua_gettable(state, -2);
			
			if (lua_istable(state, -1))
			{
				lua_getfield(state, -1, "Key");
				config.m_Key = lua_tostring(state, -1);
				lua_pop(state, 1);

				lua_getfield(state, -1, "Path");
				const char* path = lua_tostring(state, -1);
				lua_pop(state, 2);

				config.m_Texture = Textures()->Load(config.m_Key, path);
			}

			lua_pushstring(state, "Animation"); lua_gettable(state, -2);

			if (lua_istable(state, -1))
			{
				lua_getfield(state, -1, "Atlas");
				config.m_Atlas = "game/";
				config.m_Atlas.append(lua_tostring(state, -1));
				lua_pop(state, 1);

				lua_getfield(state, -1, "Skeleton");
				config.m_Skeleton = "game/";
				config.m_Skeleton.append(lua_tostring(state, -1));
				lua_pop(state, 2);
			}

			lua_pushstring(state, "ConfigId"); lua_gettable(state, -2);
			ZombieId configId = static_cast<ZombieId>(lua_tonumber(state, -1));
			lua_pop(state, 1);

			lua_pushstring(state, "WalkSpeed"); lua_gettable(state, -2);
			config.m_WalkSpeed = lua_tonumber(state, -1);
			lua_pop(state, 2);

			Zombies()->AddConfiguration(configId, config);
		}
		return 0;
	};

	const struct luaL_Reg zombieFunctions[] =
	{
		{ "LoadZombieConfig", zombieConfigLoad },
		{ nullptr, nullptr }
	};

	Scripts()->RegisterFunctions(zombieFunctions);

	for (auto file : configs)
		Scripts()->RegisterFile(file);
}

void ZombieManager::AddConfiguration(ZombieId id, ZombieConfig config)
{
	m_Configs.emplace(id, config);
}

void ZombieManager::LoadConfiguration(Zombie* zombie)
{
	ZombieId zombieId = zombie->GetZombieId();
	ZombieConfig zombieConfig = m_Configs[zombieId];

	zombie->LoadAnimationTexture(zombieConfig.m_Texture, zombieConfig.m_Key,
		zombieConfig.m_Skeleton, zombieConfig.m_Atlas);

	LOG(PrintMessageType::Success, "%s%d", "Load zombie config with id: ", zombieId);
}

void ZombieManager::Add(Zombie* zombie)
{
	m_Zombies.push_back(zombie);
}

void ZombieManager::Remove(Zombie* zombie)
{
	if (zombie == nullptr)
		return;

	auto it = std::find_if(m_Zombies.begin(), m_Zombies.end(), [&](Zombie* element) {
		return zombie->GetIndex() == element->GetIndex();
	});

	if (it != m_Zombies.end())
	{
		m_Zombies.erase(it);
		delete zombie;
	}
}

int ZombieConfig::CreateConfig(lua_State* state)
{
	lua_newtable(state);

	lua_pushstring(state, "WalkSpeed");
	lua_pushnumber(state, 0);
	lua_settable(state, -3);

	lua_pushstring(state, "RunSpeed");
	lua_pushnumber(state, 0);
	lua_settable(state, -3);

	lua_pushstring(state, "Texture");
	lua_pushstring(state, "");
	lua_settable(state, -3);

	luaL_getmetatable(state, "ZombieConfig");
	lua_setmetatable(state, -2);

	return 1;
}
