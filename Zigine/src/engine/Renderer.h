#pragma once
#include "Zigine.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer() = default;

	static void init(int screenWidth, int screenHeight, const std::string &title,
		bool verticalSync, sf::Color background, sf::Uint32 style);

	static void drawSprite(sf::Sprite& sprite);
	static void drawPrimitive(const sf::Drawable& drawable);
	static void drawPrimitive(const sf::Drawable* drawable);

	static void setView(const sf::View& view);

	static vector2 mapPixelToCoords(const vector2i& position);

	static void clear();
	static void display();

	static bool isOpen() { return _window->isOpen(); }
	static vector2u getSize() { return _window->getSize(); }
	static std::shared_ptr<sf::RenderWindow> getWindow() { return _window; }
private:
	static sf::Color _background;

	static std::shared_ptr<sf::RenderWindow> _window;
};