#ifndef _ZOMBIE_H
#define	_ZOMBIE_H
#include "engine/AnimationEntity.h"
#include "Object.h"

enum ZombieId
{
	ZOMBIE_DEFAULT,
	ZOMBIE_FLAG,
	ZOMBIE_CONEHEAD,
	ZOMBIE_BUCKETHEAD,
	ZOMBIE_LASTID,
};

enum class ZombieState : uint32_t
{
	ZOMBIE_IDLE,
	ZOMBIE_ALIVE,
	ZOMBIE_DYING,
	ZOMBIE_ATTACK,
};

struct ZombieArmorSettings
{

};

struct lua_State;

class Zombie : public Object
{
public:
	Zombie(const vector2& position);

	virtual void Update();
	virtual void UpdateState();
	virtual bool UpdateAnimationState();

	virtual void TakeDamage(const float damage) override;

	virtual void SetEnemy(Entity* enemy);
	virtual void SetArmor(const float armor);
	virtual void SetState(ZombieState state);

	virtual inline ZombieState GetState() const { return m_State; }
	virtual inline ZombieId GetZombieId() const { return ZOMBIE_DEFAULT; }

	inline uint32_t GetUserType() const { return ZOMBIE_TYPE; }
	inline bool IsZombie() const override { return true; }
private:
	ZombieState m_State = ZombieState::ZOMBIE_IDLE;
	ZombieState m_PreviousState = ZombieState::ZOMBIE_IDLE;
	Entity* m_Enemy = nullptr;
	float m_Armor = 0.0f;

	DECLARE_CLASS(Zombie, AnimationEntity)
};

#endif // !_ZOMBIE_H
