#ifndef _OBJECT_H
#define _OBJECT_H
#include "engine/AnimationEntity.h"
#include "Game/Const.h"

class Object : public AnimationEntity
{
public:
	virtual inline bool IsPlant() const { return false; }
	virtual inline bool IsZombie() const { return false; }
};

#endif // !_OBJECT_H
