#include "engine/ui/Panel.h"
#include "engine/managers/TextureManager.h"
#include "engine/utils/Input.h"
#include "engine/utils/Time.h"

#include "CardPanel.h"

CardPanel::CardPanel(const std::string& classname, int cost)
	: m_ClassName(classname)
	, m_IsRecharged(false)
	, m_TimeRecharge(5)
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

	m_RechargeShape.setFillColor(sf::Color(128, 128, 128, 48));
	m_RechargeShape.setSize(vector2(size.x, 0));
}

void CardPanel::Draw()
{
	Renderer::DrawPrimitive(m_Shape);
	Renderer::DrawPrimitive(m_Seed);
	Renderer::DrawPrimitive(m_Text);

	if (m_IsRecharged)
		Renderer::DrawPrimitive(m_RechargeShape);
}

void CardPanel::Update()
{
	if (m_IsRecharged)
	{
		if (m_NextRecharge < Time::GetTime())
		{
			m_IsRecharged = false;
			const vector2 rechargeSize = m_RechargeShape.getSize();
			m_RechargeShape.setSize(vector2(rechargeSize.x, 0));
			SetColor(sf::Color(255, 255, 255, 255));
			const vector2 size = GetSize();
			std::cout << size.x << " " << size.y << std::endl;
			std::cout << rechargeSize.x << " " << rechargeSize.y << std::endl;
		}
		else
		{
			const vector2 rechargeSize = m_RechargeShape.getSize();
			const vector2 size = GetSize();
			const float segment = (1.0f / m_TimeRecharge) * Time::GetDeltaTime();
			const float delta = size.y * segment;

			m_RechargeShape.setSize(vector2(rechargeSize.x, rechargeSize.y - delta));
		}
	}

	vector2i position{ Input::GetPosition() };

	if (position.x >= m_Min.x && position.x <= m_Max.x
		&& position.y >= m_Min.y && position.y <= m_Max.y)
	{
		//OnMouseHovered();

		if (Input::IsMouseButtonDown(sf::Mouse::Left))
		{
			if (!m_IsRecharged)
			{
				OnMousePressed();

				if (m_OnPressed)
					m_OnPressed(this, position);
			}
		}
	}
}

void CardPanel::Recharge()
{
	m_IsRecharged = true;

	m_NextRecharge = Time::GetTime() + m_TimeRecharge;

	SetColor(m_PressedColor);
}

void CardPanel::SetPosition(const vector2& position)
{
	Button::SetPosition(GetPosition() + position);

	m_Seed.setPosition(m_Seed.getPosition() + position);
	m_Text.setPosition(m_Text.getPosition() + position);
	m_RechargeShape.setPosition(GetPosition() + vector2(0, GetSize().y));
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
