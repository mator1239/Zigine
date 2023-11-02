#pragma once
#include "engine/Zigine.h"
#include "engine/Entity.h"
#include "engine/Renderer.h"

class EntityManager final
{
public:
	EntityManager();

	void Init();
	void Release();

	void Update();
	void Draw();

	void Add(Entity* entity);
	void Add(const std::string& name, EntityRegistry factory);

	void Remove(Entity* entity);
	void Remove(int index);

	Entity* Create(const std::string& name);
	void* Create(const size_t size);
private:
	void FreeEntity(std::vector<Entity*>::iterator it);
	std::unordered_map<std::string, EntityRegistry> m_Factories;
	std::vector<Entity*> m_Entities;
};

DECLARE_INSTANCE_FUNCTION(EntityManager, Entities)
