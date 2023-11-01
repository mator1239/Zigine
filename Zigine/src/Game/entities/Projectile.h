#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#include "engine/Entity.h"
#include "Game/Const.h"

class Projectile : public Entity
{
public:
	Projectile(const vector2& position, const vector2& direction, const float damage, const float speed);

	virtual void Update();

	bool TakeDamage(Entity* entity);

	inline uint32_t GetUserType() const { return PROJECTILE_TYPE; }
protected:
	vector2 m_Direction;
	float m_Damage;
	float m_Speed;
};

#endif // !_PROJECTILE_H
