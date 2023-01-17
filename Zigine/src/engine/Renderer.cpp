#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::create(int screenWidth, int screenHeight, const std::string &title,
	bool verticalSync, sf::Color background, sf::Uint32 style)
{
	_background = background;

	sf::ContextSettings settings;
	settings.depthBits = 12;
	settings.antialiasingLevel = 1;

	_window->create(sf::VideoMode(screenWidth, screenHeight), title, style, settings);
	_window->setVerticalSyncEnabled(verticalSync);
}

void Renderer::drawSprite(sf::Sprite &sprite)
{
	_window->draw(sprite);
}

void Renderer::clear()
{
	_window->clear(_background);
}

void Renderer::display()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
	}

	_window->display();
}
