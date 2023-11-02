#include "ui/Panel.h"
#include "engine/ui/PanelManager.h"
#include "engine/managers/ScriptManager.h"
#include "engine/animation/Animation.h"

#include "Engine.h"
#include "engine/physics/PhysicsManager.h"

#include <chrono>
#include <Windows.h>

class FPS final
{
public:
	FPS() 
		: m_Frame(0)
		, m_Fps(0)
	{}

	void Update()
	{
		if (m_Clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			m_Fps = m_Frame;
			m_Frame = 0;
			m_Clock.restart();
		}
		m_Frame++;
	}

	const unsigned int GetFps() const { return m_Fps; }
private:
	unsigned int m_Frame;
	unsigned int m_Fps;
	sf::Clock m_Clock;
};

Engine* Engine::m_Instance = nullptr;

Engine::Engine(int width, int height, const std::string& title, bool verticalSync,
	sf::Color background, sf::Uint32 style)
{
	Renderer::Init(width, height, title, verticalSync, background, style);
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
	sf::RenderWindow* renderWindow = Renderer::GetWindow().get();

	Init();

	FPS fps;

	while (Renderer::IsOpen())
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

		Renderer::Clear();
		Entities()->Draw();
		Panels()->Draw();
		Physics()->Draw();

		m_ImguiLayer->Begin();
		{
			for (Layer* layer : m_LayerStack)
				layer->OnImguiRender();
		}
		m_ImguiLayer->End();

		Renderer::Display();

		fps.Update();
		std::ostringstream ss;
		ss << fps.GetFps() << " " << Time::getCurrentTime();

		renderWindow->setTitle(ss.str());

		Sleep(1);
	}
}

