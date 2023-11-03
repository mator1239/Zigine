#include "Label.h"

Label::Label(const std::string& name, Panel* parent)
	: Panel(parent)	
{
}

void Label::Draw()
{
	Renderer::DrawPrimitive(m_Text);
}

void Label::SetTextPosition(const vector2& position)
{
	m_Text.setPosition(position);
}

void Label::SetFillColor(const sf::Color& color)
{
	Panel::SetFillColor(color);

	m_Text.setFillColor(color);
}

void Label::SetCharacterSize(const unsigned int size)
{
	m_Text.setCharacterSize(size);
}

void Label::SetFont(const std::string& name)
{
	m_Font.loadFromFile(name);
	m_Text.setFont(m_Font);
}

void Label::SetFont(const sf::Font& font)
{
	m_Font = font;
	m_Text.setFont(m_Font);
}

void Label::SetText(const std::string& text)
{
	m_Text.setString(text);
}
