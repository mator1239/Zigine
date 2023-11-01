#include "engine/utils/Input.h"
#include "Button.h"

void Button::Update()
{
	vector2i position { Input::getPosition() };

	if (position.x >= m_Min.x && position.x <= m_Max.x
		&& position.y >= m_Min.y && position.y <= m_Max.y)
	{
		OnMouseHovered();

		if (Input::isMouseButtonDown(sf::Mouse::Left))
		{
			OnMousePressed();

			if (m_OnPressed)
				m_OnPressed(this, position);
		}
	}
}

void Button::Draw()
{
	Label::Draw();
}

void Button::SetPosition(float x, float y)
{
	vector2 position = { x, y };
	SetPosition(position);
}

void Button::SetPosition(const vector2& position)
{
	Panel::SetPosition(position);

	const vector2 currentPosition = GetPosition();
	m_Min = currentPosition;
	m_Max = currentPosition + GetSize();
}

void Button::SetColor(const sf::Color& color, ButtonColorType colorType)
{
	switch (colorType)
	{
	case Button::ButtonColorType::Default:
		m_FillColor = color;
		Panel::SetFillColor(m_FillColor);
		break;
	case Button::ButtonColorType::Pressed:
		m_PressedColor = color;
		break;
	case Button::ButtonColorType::Hovered:
		m_HoverColor = color;
		break;
	}
}

void Button::SetHoverColor(const sf::Color& color)
{
	m_HoverColor = color;
}

void Button::SetPressedColor(const sf::Color& color)
{
	m_PressedColor = color;
}

void Button::SetButtonCallback(ButtonPressCallback function)
{
	m_OnPressed = function;
}

void Button::OnMousePressed()
{
	if (m_PressedColor != sf::Color::Black)
		Panel::SetFillColor(m_PressedColor);
}

void Button::OnMouseHovered()
{
	if (m_HoverColor != sf::Color::Black)
		Panel::SetFillColor(m_HoverColor);
}
