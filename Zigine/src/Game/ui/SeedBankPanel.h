#ifndef _SEEDBANKPANEL_H
#define _SEEDBANKPANEL_H

class SeedBankPanel : public Panel
{
public:
	SeedBankPanel();

	void AddCard(CardPanel* card);

	void SetPosition(const vector2& position);

	inline std::vector<CardPanel*> GetCards() const { return m_Cards; }
private:
	std::vector<CardPanel*> m_Cards;
};

#endif // !_SEEDBANKPANEL_H
