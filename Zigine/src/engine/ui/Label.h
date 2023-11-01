#ifndef _LABEL_H
#define _LABEL_H
#include "Panel.h"

class Label : public Panel
{
public:
	Label(const std::string& name = "", Panel* parent = nullptr);

	virtual void Draw();

	virtual void SetTextPosition(const vector2& position);
	virtual void SetFillColor(const sf::Color& color);
	virtual void SetCharacterSize(const unsigned int size);

	virtual void SetFont(const std::string& name);
	virtual void SetFont(const sf::Font& font);
	virtual void SetText(const std::string& text);
protected:
	sf::Text m_Text;
	sf::Font m_Font;
};

#endif // !_LABEL_H
