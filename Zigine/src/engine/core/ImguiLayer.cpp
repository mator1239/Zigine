#include "engine/Zigine.h"
#include "engine/Renderer.h"
#include "engine/utils/Time.h"
#include "ImguiLayer.h"

ImguiLayer::ImguiLayer()
	: Layer("ImguiLayer")
{
	m_Window = Renderer::getWindow().get();
}

void ImguiLayer::OnAttach()
{
	ImGui::SFML::Init(*m_Window);

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;       // Enable Keyboard Controls
	io.BackendFlags |= ImGuiWindowFlags_MenuBar;
}

void ImguiLayer::OnDetach()
{
	ImGui::SFML::Shutdown();
}

void ImguiLayer::Begin()
{
	ImGui::SFML::Update(*m_Window, Time::getClock());
}

void ImguiLayer::End()
{
	ImGui::SFML::Render(*m_Window);
}
