#include "EntityManager.h"
#include "engine/physics/PhysicsManager.h"

DEFINE_SECURE_INSTANCE_FUNCTION(EntityManager, Entities)

EntityManager::EntityManager()
{
}

void EntityManager::Add(Entity* entity)
{
	m_Entities.push_back(entity);
}

void EntityManager::Add(const std::string& name, EntityRegistry factory)
{
	m_Factories.emplace(name, factory);
}

void EntityManager::Remove(Entity* entity)
{
	if (entity == nullptr)
		return;

	auto it = std::find(m_Entities.begin(), m_Entities.end(), entity);
	FreeEntity(it);
}

void EntityManager::Remove(int index)
{
	if (index > m_Entities.size())
		return;

	auto it = (m_Entities.begin() + index);
	FreeEntity(it);
}

Entity* EntityManager::Create(const std::string& name)
{
	if (m_Factories.find(name) == m_Factories.end())
		return nullptr;

	EntityRegistry factory = m_Factories[name];
	EntityRegistry::FactoryFunction function = factory.m_Function;
	
	return function();
}

void* EntityManager::Create(const size_t size)
{
	void* data = malloc(size);
	Entity* entity = static_cast<Entity*>(data);
	Add(entity);

	return data;
}

void EntityManager::FreeEntity(std::vector<Entity*>::iterator it)
{
	if (it == m_Entities.end()) 
		return;

	Entity* entity = *it;

	free(entity);
	m_Entities.erase(it);
}

void EntityManager::Init()
{
}

void EntityManager::Release()
{
	for (Entity* entity : m_Entities)
		free(entity);

	m_Entities.clear();
}

void EntityManager::Update()
{
	for (int index = 0; index < m_Entities.size(); index++)
	{
		Entity* entity = m_Entities[index];
		entity->Update();
	}
}

void EntityManager::Draw()
{
	/*ImGui::Begin("Scene");

	if (ImGui::CollapsingHeader("Entities Hierarchy"))
	{
		for (const auto entity : _entities)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Bullet;
			bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity.get(), flags, "Entity");
			if (ImGui::IsItemClicked())
				_selectionContext = entity;

			if (opened)
				ImGui::TreePop();

			if (opened)
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
				bool opened = ImGui::TreeNodeEx((void*)9812739, flags, "Entity");
				if (opened)
					ImGui::TreePop();
				ImGui::TreePop();
			}
		}
	}

	ImGui::End();*/

	for (int index = 0; index < m_Entities.size(); index++)
	{
		Entity* entity = m_Entities[index];
		entity->Draw();
	}

	/*ImGui::Begin("Entity Settings");
	if (_selectionContext)
	{
		vector2 position = _selectionContext->getPosition();
		float changePosition[2] = { position.x, position.y };
		ImGui::InputFloat2("Position", changePosition);
		_selectionContext->setLocalPosition({ changePosition[0], changePosition[1] });

		float angle = _selectionContext->getRotation() * 180.0f / Math::PI;
		ImGui::SliderAngle("Angle", &angle);
		_selectionContext->setRotation(angle * Math::PI / 180.0f);
	}
	ImGui::End();*/
}
