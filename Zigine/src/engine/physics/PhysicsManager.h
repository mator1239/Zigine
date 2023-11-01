#ifndef _PHYSICSMANAGER_H
#define _PHYSICSMANAGER_H
#include "engine/Zigine.h"
#include "engine/box2d/box2d.h"

using RayCastCallback = b2RayCastCallback;

class PhysicsManager final
{
public:
	PhysicsManager();
	~PhysicsManager();

	void Draw();
	void UpdateCollision();
	void Release();

	b2Body* Add(const b2BodyDef* definition);
	void Remove(b2Body* body);

	void RayCast(RayCastCallback* input, const vector2& start, const vector2& end);

	inline b2World* GetWorld() { return m_World; }
private:
	b2World* m_World;

	class PhysicsDraw : public b2Draw
	{
	public:
		PhysicsDraw() = default;

		// Унаследовано через b2Draw
		virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
		virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
		virtual void DrawTransform(const b2Transform& xf) override;
		virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
	};

	PhysicsDraw m_Draw;
};

template <class _T>
constexpr b2Vec2 ToBoxVector2(const _T other);

template <class _T>
constexpr vector2 ToSFMLVector2(const _T other);

#endif // !_PHYSICSMANAGER_H

DECLARE_INSTANCE_FUNCTION(PhysicsManager, Physics)

/*#define BEGIN_NAMESPACE_MANAGER(className, nameSpaceName)\
	extern std::unique_ptr<className> __s_Instance_##className;\
	namespace nameSpaceName {
		
#define MANAGER_FUNCTION(functionName, ...)\
	static void functionName(__VA_ARGS__) 

#define MANAGER_ARGS(className, functionName, ...)\
	__s_Instance_##className->functionName(__VA_ARGS__);

#define END_NAMESPACE_MANAGER() }

BEGIN_NAMESPACE_MANAGER(PhysicsManager, Phys)
MANAGER_FUNCTION(Add, Entity* entity, Collider::ColliderType colliderType)
{
	MANAGER_ARGS(PhysicsManager, Add, entity, colliderType)
}
MANAGER_FUNCTION(Remove, Entity* entity)
{
	MANAGER_ARGS(PhysicsManager, Remove, entity)
}
END_NAMESPACE_MANAGER()*/