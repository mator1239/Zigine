#include "engine/utils/Time.h"

#include "Animation.h"

dragonBones::SFMLFactory Animation::m_Factory = {};

void Animation::Update()
{
	float deltaTime = Time::getDeltaTime();
	m_Factory.update(deltaTime);
}

dragonBones::SFMLArmatureDisplay* Animation::Load(sf::Texture* texture, const std::string& name,
	const std::string& skeleton, const std::string& atlas)
{
	m_Factory.loadDragonBonesData(skeleton, name);
	m_Factory.loadTextureAtlasData(atlas, texture, name);

	auto armature = new dragonBones::SFMLArmatureDisplay(name);

	LOG_NULLPTR(armature->getArmatureProxy(), armature, 
		"Failed to load animation texture. No animation data");
}
