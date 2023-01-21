#include "Engine.h"
#include <chrono>

Engine::Engine()
{
}

Engine::~Engine()
{
	Time::relese();
}

void Engine::create(int width, int height, const std::string &title, bool verticalSync, sf::Color background, sf::Uint32 style)
{
	_render->create(width, height, title, verticalSync, background, style);

	start();
	_entityManager->setupEntities(_render);

	Time::init();

	while (_render->isOpen())
	{
		Time::update();

		update();
		_entityManager->updateEntities();

		_render->clear();
		_entityManager->drawEntities();
		_render->display();
	}
}

