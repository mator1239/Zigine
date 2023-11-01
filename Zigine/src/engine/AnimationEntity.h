#ifndef _ANIMATIONENTITY_H
#define _ANIMATIONENTITY_H
#include "Entity.h"
#include "dragonBones/SFMLArmatureDisplay.h"

using Bone = dragonBones::Bone;

class AnimationEntity : public Entity
{
public:
	virtual void Draw();

	void LoadAnimationTexture(const std::string& key, const std::string& skeleton, const std::string& atlas);
	void LoadAnimationTexture(sf::Texture* texture, const std::string& key, const std::string& skeleton, 
		const std::string& atlas);

	void PlayAnimation(const std::string& name, const int playTimes = -1);

	Bone* GetAttachment(const std::string& name);
protected:
	dragonBones::SFMLArmatureDisplay* m_Armature;
	dragonBones::Animation* m_Animation;
};

#endif // !_ANIMATIONENTITY_H
