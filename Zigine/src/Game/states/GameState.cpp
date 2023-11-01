#include "engine/Entity.h"
#include "Game/entities/Zombie.h"

#include "engine/managers/EntityManager.h"
#include "engine/managers/TextureManager.h"
#include "engine/managers/ScriptManager.h"
#include "Game/managers/ProjectileManager.h"

#include "engine/utils/Base.h"
#include "engine/ui/Base.h"
#include "Game/ui/Base.h"

#include "Game/entities/Plant.h"

#include "GameState.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//ContactCallback* callbackA = reinterpret_cast<ContactCallback*>(fixtureA->GetUserData().pointer);
	//ContactCallback* callbackB = reinterpret_cast<ContactCallback*>(fixtureB->GetUserData().pointer);

	Entity* entityA = reinterpret_cast<Entity*>(fixtureA->GetUserData().pointer);
	Entity* entityB = reinterpret_cast<Entity*>(fixtureB->GetUserData().pointer);

	uint32_t entityTypeA = entityA->GetUserType();
	uint32_t entityTypeB = entityB->GetUserType();

	switch (entityTypeA)
	{
	case PROJECTILE_TYPE:
		{
			Projectile* projectile = static_cast<Projectile*>(entityA);
			projectile->TakeDamage(entityB);
		}
		break;
	case ZOMBIE_TYPE:

		break;
	}
}

void GameState::OnAttach()
{
	m_Map = new Map();
	m_Map->Spawn();

	b2World* world = Physics()->GetWorld();
	world->SetContactListener(&m_Listener);

	m_SoundBuffer.loadFromFile("game/sounds/plant.ogg");
	m_PlantSound.setBuffer(m_SoundBuffer);

	Textures()->Load("Zombie", "materials/zombies/ZombieSkeleton_tex.png");

	Zombie* zombie = new Zombie(vector2(537, 222));

	m_SeedPanel = new SeedBankPanel();
	m_SeedPanel->AddCard(new CardPanel("plant_sunflower"));
	m_SeedPanel->AddCard(new CardPanel("plant_sunflower"));
	m_SeedPanel->SetPosition(vector2(DEFAULT_TILE_START_POSITION_X - TILE_SIZE_X, 0.0f));

	for (auto& card : m_SeedPanel->GetCards())
	{
		card->SetPressedColor({ 128, 128, 128, 255 });
		card->SetButtonCallback([&](Button* button, vector2i position) {
			CardPanel* panel = static_cast<CardPanel*>(button);
			if (m_CardPanel == panel)
			{
				ResetCardPanel();
				ResetPlantShadow();
			}
			else if (!m_CardPanel)
			{
				vector2 size = panel->GetSize();
				const sf::Texture* texture = panel->GetSeedTexture();
					
				m_TilePlant->LoadTexture(texture);
				m_TilePlant->SetOrigin(size.x / 2 + 5.0f, size.y / 2);
				m_MousePlant->LoadTexture(texture);
				m_MousePlant->SetOrigin(size.x / 2, size.y - 5.0f);

				m_CardPanel = panel;
				m_IsPlantSelected = true;
			}
		});
	}

	m_TilePlant = new Panel();
	m_MousePlant = new Panel();
	m_TilePlant->SetFillColor(255, 255, 255, 128);
	m_MousePlant->SetFillColor(255, 255, 255, 255);

	ResetPlantShadow();
}

void GameState::HandleInput()
{
	if (Input::isMouseButtonDown(sf::Mouse::Left))
	{
		if (m_IsPlantSelected)
		{
			if (m_CurrentTile.IsValid() && !m_CurrentTile.GetPlant())
			{
				m_IsPlantReady = true;
				m_IsPlantSelected = false;
			}
			else
			{
				ResetCardPanel();
				ResetPlantShadow();
			}
		}
	}
}

void GameState::OnUpdate()
{
	HandleInput();

	if (m_IsPlantReady)
	{
		//m_PlantSound.play();
		m_IsPlantReady = false;
		m_IsPlantSelected = false;

		Plant* plant = static_cast<Plant*>(Entity::Create(m_CardPanel->GetName()));
		plant->SetPositon(m_TilePlant->GetPosition());
		plant->SetOrigin(m_TilePlant->GetOrigin());

		const uint32_t tileId = m_CurrentTile.GetId();
		Tile& tile = m_Map->GetTile(tileId);
		tile.SetPlant(plant);

		ResetCardPanel();
		ResetPlantShadow();

		LOG(PrintMessageType::Default, "[GameState::OnUpdate] Plant spawned");
	}

	if (m_IsPlantSelected)
	{
		vector2 position { Input::getPosition() };

		if (m_Map->GetTile(position, m_CurrentTile) 
			&& !m_CurrentTile.GetPlant())
		{
			m_TilePlant->SetVisible(true);
			m_TilePlant->SetPosition(m_CurrentTile.GetCenter());
		}
		else
		{
			m_TilePlant->SetVisible(false);
		}

		m_MousePlant->SetVisible(true);
		m_MousePlant->SetPosition(position);
	}
}

void GameState::OnImguiRender()
{
	ImGui::Begin("Scene entities");

	ImGui::End();
}

void GameState::OnDetach()
{
}

void GameState::ResetPlantShadow()
{
	m_MousePlant->SetVisible(false);
	m_TilePlant->SetVisible(false);
}

void GameState::ResetCardPanel()
{
	m_CardPanel->SetColor({ 255, 255, 255, 255 });
	m_IsPlantSelected = false;
	m_CardPanel = nullptr;
}