#include "EntityManager.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	_entities.clear();
}

void EntityManager::addEntity(std::shared_ptr<CBaseEntity> entity)
{
	entity->setEntityIndex(_entities.size());
	_entities.emplace_back(entity);
}

void EntityManager::removeEntity(std::shared_ptr<CBaseEntity> entity)
{
	if (_entities[entity->getEntityIndex()])
		_entities.erase(_entities.begin() + entity->getEntityIndex());
}

void EntityManager::setupEntities(std::shared_ptr<Renderer> render)
{
	for (const auto& entity : _entities)
	{
		entity->setRenderer(render);
		entity->spawn();
	}
}

void EntityManager::updateEntities()
{
	for (const auto& entity : _entities)
		entity->update();
}

void EntityManager::drawEntities()
{
	for (const auto& entity : _entities)
		entity->draw();
}
