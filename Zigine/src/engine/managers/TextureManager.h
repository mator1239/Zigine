#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H
#include "engine/Zigine.h"

class TextureManager final
{
public:
	TextureManager();

	sf::Texture* Load(const std::string& key, const std::string& filename);
	bool Find(const std::string& key);
	sf::Texture* Get(const std::string& key);
private:
	std::unordered_map<std::string, sf::Texture*> m_Textures;
};

DECLARE_INSTANCE_FUNCTION(TextureManager, Textures)

#endif // !_TEXTUREMANAGER_H
