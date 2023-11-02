#include "engine/ui/Panel.h"
#include "CardPanel.h"	

#include "SeedBankPanel.h"

SeedBankPanel::SeedBankPanel()
{
	LoadTexture("UISeedBank", "materials/ui/seedbank.png");
}

void SeedBankPanel::AddCard(CardPanel* card)
{
	vector2 position = { GetPosition().x + 85.0f + ((CARD_X + 5.0f) * m_Cards.size()), 10.0f};

	card->SetPosition(position);
	m_Cards.push_back(card);
}

void SeedBankPanel::SetPosition(const vector2& position)
{
	Panel::SetPosition(position);

	for (auto& card : m_Cards)
		card->SetPosition(position);
}
