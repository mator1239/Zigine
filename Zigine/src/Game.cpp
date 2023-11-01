#include "engine/Engine.h"

#include "Game/states/GameState.h"
#include "Game/states/GameMenu.h"

class Game : public Engine
{
public:
	Game(int width, int height, const std::string& title, bool verticalSync,
		sf::Color background, sf::Uint32 style = sf::Style::Default)
		: Engine(width, height, title, verticalSync, background, style)
	{
		PushLayer(new GameState());
	}

	void Init() override
	{
	}
};

int main()
{
	Game game(1024, 600, "PVZ", false, sf::Color::Black);
	game.Create();
	return 0;
}