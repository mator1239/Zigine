#pragma once
#include "Zigine.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer() = default;

	void create(int screenWidth, int screenHeight, const std::string &title,
		bool verticalSync, sf::Color background, sf::Uint32 style);

	void drawSprite(sf::Sprite& sprite);

	void clear();
	void display();

	bool isOpen() { return _window->isOpen(); }

	std::shared_ptr<sf::RenderWindow> renderWindow() { return _window; }
private:
	sf::Color _background;

	const std::shared_ptr<sf::RenderWindow> _window = std::make_shared<sf::RenderWindow>();
};