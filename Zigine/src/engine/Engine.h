#pragma once
#include "Renderer.h"
#include "managers/EntityManager.h"

#include "utils/Time.h"
#include "utils/Input.h"

#include "core/LayerStack.h"
#include "core/ImguiLayer.h"

class Engine
{
public:
	Engine(int width = 1024, int height = 768, const std::string& title = "Default", bool verticalSync = true,
		sf::Color background = sf::Color::Black, sf::Uint32 style = sf::Style::Default);
	virtual ~Engine();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	void Create();

	ImguiLayer* GetImguiLayer() { return m_ImguiLayer; }

	static Engine* GetInstance() { return m_Instance; }
protected:
	virtual void Init() {}

	LayerStack m_LayerStack;
	ImguiLayer* m_ImguiLayer;
private:
	static Engine* m_Instance;
};