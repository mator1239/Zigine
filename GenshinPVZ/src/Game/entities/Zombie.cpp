#include "Game/managers/ZombieManager.h"
#include "engine/managers/ScriptManager.h"
#include "engine/managers/TextureManager.h"
#include "engine/physics/PhysicsManager.h"
#include "engine/dragonBones/SFMLTextureData.h"
#include "Game/states/GameState.h"

#include "Zombie.h"

Zombie::Zombie(const vector2& position)
{
	SetPositon(position);
	Zombies()->LoadConfiguration(this);
	PlayAnimation("idle");

	b2BodyDef definition;
	definition.position.Set(position.x, position.y);
	definition.type = b2_dynamicBody;
	m_Body = Physics()->Add(&definition);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(40, 70);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.filter.categoryBits = ZOMBIE_TYPE;
	fixture.filter.maskBits = MASK_ZOMBIE;

	fixture.userData.pointer = reinterpret_cast<uintptr_t>(this);

	m_Body->CreateFixture(&fixture);
}

LINK_ENTITY_TO_CLASS(zombie_default, Object)

void Zombie::Update()
{
	UpdateState();
}

void Zombie::UpdateState()
{
	UpdateAnimationState();

	switch (m_State)
	{
	case ZombieState::ZOMBIE_IDLE:
		break;
	case ZombieState::ZOMBIE_ALIVE:
		break;
	case ZombieState::ZOMBIE_DYING:
		break;
	case ZombieState::ZOMBIE_ATTACK:
		break;
	}

	m_PreviousState = m_State;
}

bool Zombie::UpdateAnimationState()
{
	if (m_PreviousState == m_State)
		return false;

	switch (m_State)
	{
	case ZombieState::ZOMBIE_IDLE:
		PlayAnimation("idle");
		break;
	case ZombieState::ZOMBIE_ALIVE:
		break;
	case ZombieState::ZOMBIE_DYING:
		break;
	case ZombieState::ZOMBIE_ATTACK:
		break;
	}

	return true;
}

void Zombie::TakeDamage(const float damage)
{
	LOG_RETURN(damage <= 0, "damage <= 0?");

	m_Health -= damage;

	if (m_Health <= 0)
		SetState(ZombieState::ZOMBIE_DYING);
}

void Zombie::SetEnemy(Entity* enemy)
{
	LOG_RETURN(enemy == nullptr, "enemy was nullptr. Wtf?");

	m_Enemy = enemy;
}

void Zombie::SetArmor(const float armor)
{
}

void Zombie::SetState(ZombieState state)
{
	m_State = state;
}
