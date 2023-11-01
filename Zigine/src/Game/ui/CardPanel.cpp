#include "engine/ui/Panel.h"
#include "engine/managers/TextureManager.h"
#include "engine/utils/Input.h"

#include "CardPanel.h"

CardPanel::CardPanel(const std::string& name, int cost)
	: m_Name(name)
{
	LoadTexture("UISeeds", "materials/ui/seeds.png");
	m_Font.loadFromFile("game/materials/fonts/arial_bold.ttf");
	m_SeedTexture = Textures()->Load("UIPeashooter", "materials/Peashooter.png");
	vector2u seedSize = m_SeedTexture->getSize();
	vector2 size = GetSize();
	vector2 scaleSeed = { seedSize.x / size.x - 0.9f, seedSize.y / size.y - 0.6f };

	m_Seed.setTexture(m_SeedTexture);
	m_Seed.setSize(vector2(seedSize.x, seedSize.y));

	m_Seed.setScale(scaleSeed);
	m_Seed.setPosition(6.0f, 12.0f);

	SetFont(m_Font);
	SetCharacterSize(14);
	m_Text.setFillColor(sf::Color(0, 0, 0, 255));
	SetCost(cost);
}

void CardPanel::Draw()
{
	Renderer::drawPrimitive(m_Shape);
	Renderer::drawPrimitive(m_Seed);
	Renderer::drawPrimitive(m_Text);

#if _DEBUG
	const vector2 position = GetPosition();
	vector2 min = position;
	vector2 max = position + GetSize();

	sf::CircleShape minShape(3.0f);
	minShape.setFillColor(sf::Color(0, 0, 255));
	minShape.setPosition(min);

	sf::CircleShape maxShape(3.0f);
	maxShape.setFillColor(sf::Color(0, 0, 255));
	maxShape.setPosition(max);

	Renderer::drawPrimitive(minShape);
	Renderer::drawPrimitive(maxShape);
#endif // _DEBUG
}

void CardPanel::SetPosition(const vector2& position)
{
	Button::SetPosition(GetPosition() + position);

	m_Seed.setPosition(m_Seed.getPosition() + position);
	m_Text.setPosition(m_Text.getPosition() + position);
}

void CardPanel::SetFillColor(const sf::Color& color)
{
	Button::SetFillColor(color);

	m_Seed.setFillColor(color);
}

void CardPanel::SetFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	Button::SetFillColor({ r, g, b, a });
}

void CardPanel::SetColor(const sf::Color& color, ButtonColorType colorType)
{
	switch (colorType)
	{
	case Button::ButtonColorType::Default:
		m_FillColor = color;
		m_Shape.setFillColor(m_FillColor);
		m_Seed.setFillColor(m_FillColor);
		break;
	case Button::ButtonColorType::Pressed:
		m_PressedColor = color;
		break;
	case Button::ButtonColorType::Hovered:
		m_HoverColor = color;
		break;
	}
}

void CardPanel::SetCost(int cost)
{
	std::string text = std::to_string(cost);
	SetText(text);

	vector2 position = { 5.0f, 48.0f };
	SetTextPosition(position);
}

void CardPanel::OnMousePressed()
{
	if (m_PressedColor != sf::Color::Black)
		SetColor(m_PressedColor);
}

void CardPanel::OnMouseHovered()
{
	if (m_HoverColor != sf::Color::Black)
		SetColor(m_HoverColor);
}
