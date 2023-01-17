#include "engine/Engine.h"

#include "Bird.h"

class Game : public Engine
{
private:
	std::shared_ptr<CBird> bird = std::make_shared<CBird>();
public:
	virtual void start()
	{
		_entityManager->addEntity(bird);
		bird->setPostion(sf::Vector2f(40, 50));
	}
	virtual void update(float dt)
	{
	}
};

int main()
{
	Game game;
	game.create(800, 600, "Territory", true, sf::Color::Black);
	return 0;
}