#ifndef _RENDERER_H
#define _RENDERER_H
#include "Zigine.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer() = default;

	static void Init(int screenWidth, int screenHeight, const std::string &title,
		bool verticalSync, sf::Color background, sf::Uint32 style);

	static void DrawSprite(sf::Sprite& sprite, const sf::RenderStates& states = sf::RenderStates::Default);
	static void DrawPrimitive(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	static void DrawPrimitive(const sf::Drawable* drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	static void SetView(const sf::View& view);

	static vector2 MapPixelToCoords(const vector2i& position);

	static void Clear();
	static void Display();

	static bool IsOpen() { return m_Window->isOpen(); }
	static vector2u GetSize() { return m_Window->getSize(); }
	static std::shared_ptr<sf::RenderWindow> GetWindow() { return m_Window; }
private:
	static sf::Color m_Background;
	static std::shared_ptr<sf::RenderWindow> m_Window;
};

#endif // !_RENDERER_H
