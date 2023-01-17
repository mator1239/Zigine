#pragma once
#include "Renderer.h"
#include "EntityManager.h"

class Engine
{
public:
	Engine();
	virtual ~Engine() = default;

	void create(int width, int height, const std::string& title, bool verticalSync,
		sf::Color background, sf::Uint32 style = sf::Style::Default);
protected:
	virtual void start() {}
	virtual void update(float dt) {}

	const std::shared_ptr<Renderer> _render = std::make_shared<Renderer>();
	const std::shared_ptr<EntityManager> _entityManager = std::make_shared<EntityManager>();
};