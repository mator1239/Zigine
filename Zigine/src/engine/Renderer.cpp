#include "Renderer.h"

std::shared_ptr<sf::RenderWindow> Renderer::_window = nullptr;
sf::Color Renderer::_background = {};

Renderer::Renderer()
{
}

void Renderer::init(int screenWidth, int screenHeight, const std::string &title,
	bool verticalSync, sf::Color background, sf::Uint32 style)
{
	_window = std::make_shared<sf::RenderWindow>();

	_background = background;

	sf::ContextSettings settings;
	settings.depthBits = 12;
	settings.antialiasingLevel = 1;

	_window->create(sf::VideoMode(screenWidth, screenHeight), title, style, settings);
	_window->setKeyRepeatEnabled(false);
	_window->setVerticalSyncEnabled(verticalSync);
	_window->setFramerateLimit(144);
}

void Renderer::drawSprite(sf::Sprite &sprite)
{
	_window->draw(sprite);
}

void Renderer::drawPrimitive(const sf::Drawable& drawable)
{
	_window->draw(drawable);
}

void Renderer::drawPrimitive(const sf::Drawable* drawable)
{
	_window->draw(*drawable);
}

void Renderer::setView(const sf::View& view)
{
	_window->setView(view);
}

vector2 Renderer::mapPixelToCoords(const vector2i& position)
{
	const vector2 worldPosition = _window->mapPixelToCoords(position);
	return worldPosition;
}

void Renderer::clear()
{
	_window->clear(_background);
}

void Renderer::display()
{
	_window->display();
}
