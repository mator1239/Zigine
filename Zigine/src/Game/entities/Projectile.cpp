#include "Projectile.h"
#include "Game/managers/ProjectileManager.h"
#include "engine/managers/TextureManager.h"
#include "Game/states/GameState.h"

#include "Object.h"

float Length(const vector2& vec)
{
	return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
}

vector2 Normalize(const vector2& vec)
{
	float len = Length(vec);
	return { vec.x / len, vec.y / len };
}

float Product(const vector2& a, const vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

Projectile::Projectile(const vector2& position, const vector2& direction, const float damage, const float speed)
	: m_Direction(direction)
	, m_Damage(damage)
	, m_Speed(speed)
{
	LoadTexture("bullet", "materials/bullet.png", true);
	const vector2 size = GetSize();

	SetPositon(position);
	SetOrigin(vector2(size.x / 2 - 2, size.y / 2 - 2));
	Projectiles()->Add(this);

	b2BodyDef definition;
	definition.position.Set(position.x, position.y);
	definition.type = b2_dynamicBody;
	m_Body = Physics()->Add(&definition);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	//fixture.filter.categoryBits = PROJECTILE_TYPE;
	//fixture.filter.maskBits = MASK_PROJECTILE;

	//ContactCallback callback { this, PROJECTILE_TYPE };
	fixture.userData.pointer = reinterpret_cast<uintptr_t>(this);

	m_Body->CreateFixture(&fixture);
}

void Projectile::Update()
{
	Move(m_Direction * m_Speed);

	m_Body->SetTransform(ToBoxVector2(GetPosition()), 0);
}

bool Projectile::TakeDamage(Entity* entity)
{
	// Tasty hack...
	Object* object = static_cast<Object*>(entity);
	object->TakeDamage(m_Damage);

	return true;
}
