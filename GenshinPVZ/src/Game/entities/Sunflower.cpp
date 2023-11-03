#include "engine/managers/TextureManager.h"
#include "engine/utils/Time.h"
#include "Projectile.h"
#include "Plant.h"
#include "Game/Const.h"
#include "engine/physics/PhysicsManager.h"

#define DEFAULT_SUNDROP_TIME 4
#define NEXT_SUNDROP_TIME 24

class Sunflower : public Plant
{
public:
	Sunflower();

	void Update();
	void Draw();
private:
	Timer m_SunDropTimer;

	DECLARE_CLASS(Sunflower, Plant)
};

LINK_ENTITY_TO_CLASS(plant_sunflower, Sunflower)

Sunflower::Sunflower()
{
	m_SunDropTimer.Create(DEFAULT_SUNDROP_TIME, [&]() {
		Projectile* projectile = new Projectile(GetPosition(),
			vector2(1, 0), 10.0f, 0.1f);

		m_SunDropTimer.Reset(NEXT_SUNDROP_TIME);
		Log::Msg(LogType::Success, __FUNCTION__, "Sunflower dropped a sun");
	});

	LoadTexture("PlantWallnut", "materials/plants/Wallnut_tex.png", true);
	LoadAnimationTexture("PlantWallnut", "game/animations/plants/Wallnut_ske.json",
		"game/animations/plants/Wallnut_tex.json");
	PlayAnimation("idle");
}

void Sunflower::Update()
{
	m_SunDropTimer.Update();
}

void Sunflower::Draw()
{
	BaseClass::Draw();
}
