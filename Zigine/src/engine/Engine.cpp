#include "ui/Panel.h"
#include "engine/ui/PanelManager.h"
#include "engine/managers/ScriptManager.h"
#include "engine/animation/Animation.h"

#include "Engine.h"
#include "engine/physics/PhysicsManager.h"

#include <chrono>
#include <Windows.h>

class FPS
{
public:
	FPS() 
		: _frame(0)
		, _fps(0) 
	{}

	const unsigned int getFPS() const { return _fps; }
private:
	unsigned int _frame;
	unsigned int _fps;
	sf::Clock _clock;
public:
	void update()
	{
		if (_clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			_fps = _frame;
			_frame = 0;
			_clock.restart();
		}
		++_frame;
	}
};

Engine* Engine::m_Instance = nullptr;

Engine::Engine(int width, int height, const std::string& title, bool verticalSync,
	sf::Color background, sf::Uint32 style)
{
	Renderer::init(width, height, title, verticalSync, background, style);
	m_Instance = this;

	Panel* basePanel = new Panel();
	basePanel->SetSize(width, height);
	basePanel->SetVisible(false);

	Time::init();
	Input::init();

	Entities()->Init();
	Scripts()->Init("game/scripts/");
	Scripts()->Load("game.lua");

	m_ImguiLayer = new ImguiLayer();
	PushLayer(m_ImguiLayer);
}

Engine::~Engine()
{
	Scripts()->Release();
	Entities()->Release();
	Panels()->Release();

	Time::release();
	Input::release();
}

void Engine::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Engine::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Engine::Create()
{
	sf::RenderWindow* renderWindow = Renderer::getWindow().get();

	Init();

	FPS fps;

	while (Renderer::isOpen())
	{
		Time::update();

		sf::Event event;
		while (renderWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				renderWindow->close();
				break;
			case sf::Event::Resized:
				Panels()->OnWindowResized(event.size.width, event.size.height);
				break;
			}

			ImGui::SFML::ProcessEvent(*renderWindow, event);
		}
		Input::update(event);

		Physics()->UpdateCollision();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		Entities()->Update();
		Panels()->Update();
		Animation::Update();

		Renderer::clear();
		Entities()->Draw();
		Panels()->Draw();
		Physics()->Draw();

		m_ImguiLayer->Begin();
		{
			for (Layer* layer : m_LayerStack)
				layer->OnImguiRender();
		}
		m_ImguiLayer->End();

		Renderer::display();

		fps.update();
		std::ostringstream ss;
		ss << fps.getFPS() << " " << Time::getCurrentTime();

		renderWindow->setTitle(ss.str());

		Sleep(1);
	}
}

