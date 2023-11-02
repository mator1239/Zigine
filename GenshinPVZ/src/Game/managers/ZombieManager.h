#ifndef _ZOMBIEMANAGER_H
#define _ZOMBIEMANAGER_H
#include "engine/Zigine.h"
#include "Game/entities/Zombie.h"

struct ZombieConfig
{
	static int CreateConfig(lua_State* state);

	float m_WalkSpeed;
	sf::Texture* m_Texture;
	std::string m_Key;
	std::string m_Atlas;
	std::string m_Skeleton;
};

class ZombieManager final
{
public:
	ZombieManager();

	void Update();

	void AddConfiguration(ZombieId id, ZombieConfig config);
	void LoadConfiguration(Zombie* zombie);

	void Add(Zombie* zombie);
	void Remove(Zombie* zombie);

	inline std::vector<Zombie*> GetZombies() const { return m_Zombies; }
private:
	std::vector<Zombie*> m_Zombies;
	std::unordered_map<ZombieId, ZombieConfig> m_Configs;
};

DECLARE_INSTANCE_FUNCTION(ZombieManager, Zombies)

#endif // !_ZOMBIEMANAGER_H
