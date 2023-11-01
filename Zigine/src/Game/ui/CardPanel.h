#ifndef _CARDPANEL_H
#define _CARDPANEL_H
#include "engine/ui/Button.h"

#define CARD_X 45
#define CARD_Y 65

#define HALFCARD_X (CARD_X * 4)
#define HALFCARD_Y (CARD_Y * 4)

class CardPanel : public Button
{
public:
	CardPanel(const std::string& name, int cost = 100);

	void Draw();

	void SetPosition(const vector2& position);
	void SetFillColor(const sf::Color& color);
	void SetFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

	void SetColor(const sf::Color& color, ButtonColorType colorType = ButtonColorType::Default);

	void SetCost(int cost);

	inline const std::string& GetName() const { return m_Name; }
	inline const sf::Texture* GetSeedTexture() const { return m_SeedTexture; }
protected:
	void OnMousePressed();
	void OnMouseHovered();
private:
	std::string m_Name;
	sf::Texture* m_SeedTexture;
	sf::RectangleShape m_Seed;
	int m_Cost;
};

#endif // !_CARDPANEL_H
