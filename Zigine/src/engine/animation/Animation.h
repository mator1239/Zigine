#ifndef _ANIMATION_H
#define _ANIMATION_H
#include "../dragonBones/SFMLArmatureDisplay.h"
#include "../dragonBones/SFMLFactory.h"

class Animation
{
public:
	static void Update();

	static dragonBones::SFMLArmatureDisplay* Load(sf::Texture* texture, const std::string& name,
		const std::string& skeleton, const std::string& atlas);
private:
	static dragonBones::SFMLFactory m_Factory;
};

#endif // !_ANIMATION_H
