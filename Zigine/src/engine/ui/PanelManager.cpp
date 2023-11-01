#include "PanelManager.h"

DEFINE_INSTANCE_FUNCTION(PanelManager, Panels)

void PanelManager::Update()
{
	for (const auto& panel : m_Panels)
		panel->Update();
}

void PanelManager::Draw()
{
	for (const auto& panel : m_Panels)
		panel->Draw();
}

void PanelManager::Add(Panel* panel)
{
	m_Panels.push_back(panel);
}

void PanelManager::Remove(Panel* panel)
{
	auto it = std::remove(m_Panels.begin(), m_Panels.end(), panel);
	m_Panels.erase(it);
}

void PanelManager::Release()
{
	for (auto& panel : m_Panels)
		delete panel;

	m_Panels.clear();
}

void PanelManager::OnWindowResized(float width, float height)
{
	for (auto& panel : m_Panels)
		panel->OnWindowResized(width, height);
}
