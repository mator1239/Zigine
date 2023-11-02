#include "managers/EntityManager.h"
#include "managers/TextureManager.h"
#include "animation/Animation.h"

#include "Entity.h"

static int m_GlobalEntityIndex = 0;

Entity::Entity(const vector2& size)
{
	Setup();
}

void Entity::Draw()
{
	Renderer::DrawPrimitive(m_Shape);
}

Entity* Entity::Create(const std::string& name)
{
	return Entities()->Create(name);
}

void Entity::LoadTexture(sf::Texture* texture, bool isSmooth)
{
	vector2 newSize = (vector2)texture->getSize();
	texture->setSmooth(isSmooth);

	m_Shape.setTexture(texture);
	m_Shape.setSize(newSize);
}

void Entity::LoadTexture(const std::string& key, bool isSmooth)
{
	sf::Texture* texture = Textures()->Get(key);
	LoadTexture(texture, isSmooth);
}

void Entity::LoadTexture(const std::string& key, const std::string& path, bool isSmooth)
{
	sf::Texture* texture = Textures()->Load(key, path);
	LoadTexture(texture, isSmooth);
}

void Entity::SetZ(const int coordinate)
{
	m_ZCoordinate = coordinate;
}

void Entity::SetHealth(const float health)
{
	m_Health = health;
}

void Entity::SetPositon(const vector2& position)
{
	m_Shape.setPosition(position);
}

void Entity::SetOrigin(const vector2& origin)
{
	m_Shape.setOrigin(origin);
}

void Entity::SetRotation(const float angle)
{
	m_Shape.setRotation(angle);
}

void Entity::Move(const vector2& offset)
{
	m_Shape.move(offset);
}

void Entity::Rotate(const float angle)
{
	m_Shape.rotate(angle);
}

void* Entity::operator new(std::size_t size)
{
	return Entities()->Create(size);
}

void Entity::operator delete(void* memory)
{
	Entity* entity = static_cast<Entity*>(memory);
	Entities()->Remove(entity);
}

void Entity::Setup()
{
	m_Index = m_GlobalEntityIndex;
	m_GlobalEntityIndex++;
}

EntityRegistry::EntityRegistry(const std::string& name, FactoryFunction function)
{
	m_Function = function;

	Entities()->Add(name, *this);
}
