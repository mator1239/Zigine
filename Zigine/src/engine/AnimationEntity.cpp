#include "AnimationEntity.h"
#include "managers/TextureManager.h"
#include "animation/Animation.h"

void AnimationEntity::Draw()
{
	m_Armature->setPosition(GetPosition());

	Renderer::drawPrimitive(m_Armature);
}

void AnimationEntity::LoadAnimationTexture(const std::string& key, const std::string& skeleton, const std::string& atlas)
{
	sf::Texture* texture = Textures()->Get(key);
	LoadAnimationTexture(texture, key, skeleton, atlas);
}

void AnimationEntity::LoadAnimationTexture(sf::Texture* texture, const std::string& key, const std::string& skeleton, const std::string& atlas)
{
	LoadTexture(texture, true);

	m_Armature = Animation::Load(GetTexture(), key, skeleton, atlas);
	m_Animation = m_Armature->getAnimation();
}

void AnimationEntity::PlayAnimation(const std::string& name, const int playTimes)
{
	if (m_Animation)
		m_Animation->play(name, playTimes);
}

Bone* AnimationEntity::GetAttachment(const std::string& name)
{
	Bone* bone = m_Armature->getArmature()->getBone(name);
	
	LOG_NULLPTR(bone, bone, "%s%s", "Failed to find bone with name: ", name.c_str());
}
