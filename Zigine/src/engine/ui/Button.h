#ifndef _BUTTON_H
#define _BUTTON_H
#include <functional>
#include <unordered_map>

#include "Panel.h"
#include "Label.h"

class Button : public Label
{
public:
	using ButtonPressCallback = std::function<void(Button* button, vector2i position)>;

	enum class ButtonColorType
	{
		Default = 0,
		Pressed,
		Hovered,
	};

	virtual void Update();
	virtual void Draw();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const vector2& position);

	virtual void SetColor(const sf::Color& color, ButtonColorType colorType = ButtonColorType::Default);
	virtual void SetHoverColor(const sf::Color& color);
	virtual void SetPressedColor(const sf::Color& color);

	virtual void SetButtonCallback(ButtonPressCallback function);
protected:
	virtual void OnMousePressed();
	virtual void OnMouseHovered();

	ButtonPressCallback m_OnPressed;
	vector2 m_Min;
	vector2 m_Max;
	sf::Color m_FillColor = sf::Color(255, 255, 255, 255);
	sf::Color m_HoverColor;
	sf::Color m_OutlineColor;
	sf::Color m_PressedColor;
};

#endif // !_BUTTON_H
