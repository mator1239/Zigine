#include "Engine.h"

Engine::Engine()
{
}

void Engine::create(int width, int height, const std::string &title, bool verticalSync, sf::Color background, sf::Uint32 style)
{
	_render->create(width, height, title, verticalSync, background, style);

	start();
	_entityManager->setupEntities(_render);

	while (_render->isOpen())
	{
		update(0.0f);
		_entityManager->updateEntities();

		// Render
		_render->clear();

		_entityManager->drawEntities();

		_render->display();
	}
}

