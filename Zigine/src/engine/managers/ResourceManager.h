#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H
#include "engine/Zigine.h"

class ResourceManager
{
public:
	bool LoadModel(const std::string& key, const std::string& path);
	sf::Sound* LoadSound(const std::string& key, const std::string& path);
	sf::Texture* LoadTexture(const std::string& key, const std::string& path);

	bool GetModel(const std::string& key);
	sf::Sound* GetSound(const std::string& key);
	sf::Texture* GetTexture(const std::string& key);
private:
	std::unordered_map<std::string, sf::Sound*> m_Sounds;
	std::unordered_map<std::string, sf::Texture*> m_Textures;
};

DECLARE_INSTANCE_FUNCTION(ResourceManager, Resources)

#endif // !_RESOURCEMANAGER_H
