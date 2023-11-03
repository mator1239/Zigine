#include "engine/utils/Time.h"

#include "Animation.h"

dragonBones::SFMLFactory Animation::m_Factory = {};

void Animation::Update()
{
	float deltaTime = Time::GetDeltaTime();
	m_Factory.update(deltaTime);
}

dragonBones::SFMLArmatureDisplay* Animation::Load(sf::Texture* texture, const std::string& name,
	const std::string& skeleton, const std::string& atlas)
{
	m_Factory.loadDragonBonesData(skeleton, name);
	m_Factory.loadTextureAtlasData(atlas, texture, name);

	auto armature = new dragonBones::SFMLArmatureDisplay(name);

	Log::Condition(armature->getArmatureProxy() == nullptr, "Failed to load animation texture. No animation data");

	return armature;
}
