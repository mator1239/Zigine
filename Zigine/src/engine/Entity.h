#pragma once
#include "Zigine.h"
#include "Renderer.h"
#include "physics/PhysicsManager.h"

class Entity
{
public:
	explicit Entity(const vector2& size = vector2(0, 0));

	virtual void Spawn() {}
	virtual void Update() {}
	virtual void Draw();

	static Entity* Create(const std::string& name);

	virtual void TakeDamage(const float damage) {};

	virtual void LoadTexture(sf::Texture* texture, bool isSmooth = false);
	virtual void LoadTexture(const std::string& key, bool isSmooth = false);
	virtual void LoadTexture(const std::string& key, const std::string& path, bool isSmooth = false);

	virtual void SetZ(const int coordinate);
	virtual void SetHealth(const float health);
	virtual void SetPositon(const vector2& position);
	virtual void SetOrigin(const vector2& origin);
	virtual void SetRotation(const float angle);

	virtual void Move(const vector2& offset);
	virtual void Rotate(const float angle);

	void* operator new(std::size_t size);
	void operator delete(void* memory);

	inline float GetHealth() const { return m_Health; }
	inline int GetZ() const { return m_ZCoordinate; }
	inline int GetIndex() const { return m_Index; }
	inline vector2 GetPosition() const { return m_Shape.getPosition(); }
	inline vector2 GetOrigin() const { return m_Shape.getOrigin(); }
	inline float GetRotation() const { return m_Shape.getRotation(); }

	inline uint32_t GetUserType() const { return 0; }

	// God dammit... SDL3 > SFML
	inline vector2 GetSize() const { return vector2(GetTexture()->getSize()); }
	const inline sf::Texture* GetTexture() const { return m_Shape.getTexture(); }
	inline sf::Texture* GetTexture() { return (sf::Texture*)m_Shape.getTexture(); }
	const inline std::string& GetClassName() const { return m_ClassName; }

	b2Body* m_Body;
protected:
	float m_Health;
	int m_Index;
	std::string m_ClassName;
	sf::RectangleShape m_Shape;
	int m_ZCoordinate = 0;

	friend class PhysicsManager;
private:
	void Setup();
};

template <class _T, class _Ky = Entity>
class EntityGeneric : public _Ky
{
public:
	static _T* Create(const std::string& name)
	{
		return static_cast<_T*>(_Ky::Create(name));
	}
};

class EntityRegistry
{
public:
	typedef Entity* (*FactoryFunction)();

	EntityRegistry() = default;
	EntityRegistry(const std::string& name, FactoryFunction function);

	FactoryFunction m_Function;
};

#define LINK_ENTITY_TO_CLASS(className, dllClassName)\
	static Entity* __Create##className()\
	{\
		return new dllClassName();\
	}\
	static EntityRegistry __g_##className##EntityRegistry(#className, __Create##className);