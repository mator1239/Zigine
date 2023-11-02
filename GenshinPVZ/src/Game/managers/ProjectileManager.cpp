#include "ProjectileManager.h"
#include "engine/physics/PhysicsManager.h"

DEFINE_INSTANCE_FUNCTION(ProjectileManager, Projectiles)

void ProjectileManager::Remove(Projectile* projectile)
{
	if (!projectile)
		return;

	auto it = std::find_if(m_Projectiles.begin(), m_Projectiles.end(), [&](Projectile* element) {
		return projectile->GetIndex() == element->GetIndex();
	});

	if (it != m_Projectiles.end())
	{
		m_Projectiles.erase(it);
		delete projectile;
	}
}

void ProjectileManager::Add(Projectile* projectile)
{
	m_Projectiles.push_back(projectile);
}
