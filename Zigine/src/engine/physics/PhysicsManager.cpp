#include "engine/Entity.h"
#include "engine/utils/Time.h"
#include "engine/Renderer.h"

#include "PhysicsManager.h"

DEFINE_INSTANCE_FUNCTION(PhysicsManager, Physics)

template <class _T>
constexpr b2Vec2 ToBoxVector2(const _T other)
{
	return b2Vec2(other.x, other.y);
}

template <class _T>
constexpr vector2 ToSFMLVector2(const _T other)
{
	return vector2(other.x, other.y);
}

PhysicsManager::PhysicsManager()
{
	m_World = new b2World(b2Vec2_zero);
#ifdef _DEBUG
	m_Draw.SetFlags(b2Draw::e_aabbBit);
	m_World->SetDebugDraw(&m_Draw);
#endif // _DEBUG
}

PhysicsManager::~PhysicsManager()
{
	Release();
}

void PhysicsManager::Draw()
{
#ifdef _DEBUG
	m_World->DebugDraw();
#endif // _DEBUG
}

void PhysicsManager::UpdateCollision()
{
	float deltaTime = Time::getDeltaTime();
	m_World->Step(deltaTime, 0, 4);
}

void PhysicsManager::Release()
{
	delete m_World;
}

b2Body* PhysicsManager::Add(const b2BodyDef* definition)
{
	return m_World->CreateBody(definition);
}

void PhysicsManager::Remove(b2Body* body)
{
	LOG_RETURN(body != nullptr, "%s", "body was nullptr");

	m_World->DestroyBody(body);
}

void PhysicsManager::RayCast(RayCastCallback* input, const vector2& start, const vector2& end)
{
	m_World->RayCast(input, ToBoxVector2(start), ToBoxVector2(end));
}

void PhysicsManager::PhysicsDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape convexShape(vertexCount);
	for (int i = 0; i < vertexCount; i++)
		convexShape.setPoint(i, ToSFMLVector2(vertices[i]));

	convexShape.setFillColor(sf::Color::Transparent);
	convexShape.setOutlineThickness(1.0f);
	sf::Color shapeColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
	convexShape.setOutlineColor(shapeColor);

	Renderer::DrawPrimitive(convexShape);
}

void PhysicsManager::PhysicsDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape convexShape(vertexCount);
	for (int i = 0; i < vertexCount; i++)
		convexShape.setPoint(i, ToSFMLVector2(vertices[i]));

	sf::Color shapeColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
	convexShape.setFillColor(shapeColor);

	Renderer::DrawPrimitive(convexShape);
}

void PhysicsManager::PhysicsDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	sf::CircleShape shape(radius);
	shape.setOrigin(radius / 2.0f, radius / 2.0f);
	shape.setPosition(ToSFMLVector2(center));

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1.0f);
	sf::Color shapeColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
	shape.setOutlineColor(shapeColor);

	Renderer::DrawPrimitive(shape);
}

void PhysicsManager::PhysicsDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	sf::CircleShape shape(radius);
	shape.setPosition(ToSFMLVector2(center));
	shape.setOrigin(radius / 2.0f, radius / 2.0f);

	sf::Color shapeColor(color.r * 255, color.g * 255, color.b * 255, color.a * 80);
	shape.setFillColor(shapeColor);

	Renderer::DrawPrimitive(shape);

	b2Vec2 point = center + (radius * axis);
	DrawSegment(center, point, color);
}

void PhysicsManager::PhysicsDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::VertexArray vertexArray(sf::Lines, 2);
	sf::Color shapeColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255);

	vertexArray[0].position = ToSFMLVector2(p1);
	vertexArray[0].color = shapeColor;

	vertexArray[1].position = ToSFMLVector2(p2);
	vertexArray[1].color = shapeColor;

	Renderer::DrawPrimitive(vertexArray);
}

void PhysicsManager::PhysicsDraw::DrawTransform(const b2Transform& xf)
{
	b2Vec2 point = xf.p;
	b2Vec2 pointX = point + (0.5f * xf.q.GetXAxis());
	b2Vec2 pointY = point + (0.5f * xf.q.GetYAxis());

	DrawSegment(point, pointX, b2Color(1.0f, 0.0f, 1.0f));
	DrawSegment(point, pointY, b2Color(1.0f, 0.0f, 1.0f));
}

void PhysicsManager::PhysicsDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	sf::CircleShape shape(size);
	shape.setPosition(ToSFMLVector2(p));
	shape.setOrigin(size / 2.0f, size / 2.0f);

	sf::Color shapeColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
	shape.setFillColor(shapeColor);

	Renderer::DrawPrimitive(shape);
}
