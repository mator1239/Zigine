#pragma once
#include "Zigine.h"
#include "Entity.h"
#include "Renderer.h"

class EntityManager
{
public:
	EntityManager();
	virtual ~EntityManager();

	void addEntity(std::shared_ptr<CBaseEntity> entity);
	void removeEntity(std::shared_ptr<CBaseEntity> entity);

	void setupEntities(std::shared_ptr<Renderer> render);
	void updateEntities();
	void drawEntities();
private:
	std::vector<std::shared_ptr<CBaseEntity>> _entities;
};