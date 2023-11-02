#pragma once
#include "engine/core/Layer.h"
#include "Game/Map.h"
class Panel;
class CardPanel;
class SeedBankPanel;

class ContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);
};

class GameState : public Layer
{
public:
	GameState()
		: m_IsPlantSelected(false)
		, m_IsPlantReady(false)
		, m_SeedPanel(nullptr)
		, m_CardPanel(nullptr)
		, m_MousePlant(nullptr)
		, m_TilePlant(nullptr)
		, m_Map(nullptr)
	{}

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnImguiRender();

	void HandleInput();

	void ResetPlantShadow();
	void ResetCardPanel();
private:
	Map* m_Map;

	ContactListener m_Listener;
	bool m_IsPlantSelected;
	bool m_IsPlantReady;
	Tile m_CurrentTile;

	sf::SoundBuffer m_SoundBuffer;
	sf::Sound m_PlantSound;

	Panel* m_MousePlant;
	Panel* m_TilePlant;
	SeedBankPanel* m_SeedPanel;
	CardPanel* m_CardPanel;
};