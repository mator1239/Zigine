#include "GameMenu.h"
#include "Game/entities/Projectile.h"
#include "Game/managers/ProjectileManager.h"

void GameMenu::OnAttach()
{
	Projectile* projectile = new Projectile(vector2(100, 100), vector2(1, 0), 10, 10);
}

void GameMenu::OnDetach()
{
}

void GameMenu::OnUpdate()
{
}

void GameMenu::OnImguiRender()
{
	bool open = true;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar;

	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &(open), windowFlags);
	ImGui::PopStyleVar();


	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		ImGui::Begin("Entity Browser");


		ImGui::End();
		ImGui::EndMenuBar();
	}

	ImGui::End();
}
