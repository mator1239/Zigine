#include "Renderer.h"

std::shared_ptr<sf::RenderWindow> Renderer::m_Window = nullptr;
sf::Color Renderer::m_Background = {};

Renderer::Renderer()
{
}

void Renderer::Init(int screenWidth, int screenHeight, const std::string &title,
	bool verticalSync, sf::Color background, sf::Uint32 style)
{
	m_Window = std::make_shared<sf::RenderWindow>();

	m_Background = background;

	sf::ContextSettings settings;
	settings.depthBits = 12;
	settings.antialiasingLevel = 1;

	m_Window->create(sf::VideoMode(screenWidth, screenHeight), title, style, settings);
	m_Window->setKeyRepeatEnabled(false);
	m_Window->setVerticalSyncEnabled(verticalSync);
	m_Window->setFramerateLimit(144);
}

void Renderer::DrawSprite(sf::Sprite &sprite)
{
	m_Window->draw(sprite);
}

void Renderer::DrawPrimitive(const sf::Drawable& drawable)
{
	m_Window->draw(drawable);
}

void Renderer::DrawPrimitive(const sf::Drawable* drawable)
{
	m_Window->draw(*drawable);
}

void Renderer::SetView(const sf::View& view)
{
	m_Window->setView(view);
}

vector2 Renderer::MapPixelToCoords(const vector2i& position)
{
	const vector2 worldPosition = m_Window->mapPixelToCoords(position);
	return worldPosition;
}

void Renderer::Clear()
{
	m_Window->clear(m_Background);
}

void Renderer::Display()
{
	m_Window->display();
}
