#ifndef _PROJECTILEMANAGER_H
#define _PROJECTILEMANAGER_H
#include "engine/Entity.h"
#include "Game/entities/Projectile.h"

class ProjectileManager final
{
public:
	void Add(Projectile* projectile);
	void Remove(Projectile* projectile);
private:
	std::vector<Projectile*> m_Projectiles;
};

DECLARE_INSTANCE_FUNCTION(ProjectileManager, Projectiles)

#endif // !_PROJECTILEMANAGER_H
