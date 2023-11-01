#ifndef _PANELMANAGER_H
#define _PANELMANAGER_H
#include "engine/Zigine.h"
#include "engine/ui/Panel.h"

class PanelManager
{
public:
	void Update();
	void Draw();

	void Add(Panel* panel);
	void Remove(Panel* panel);
	void Release();

	void OnWindowResized(float width, float height);

	inline Panel* GetBasePanel() const { return m_Panels[0]; }
private:
	std::vector<Panel*> m_Panels;
};

DECLARE_INSTANCE_FUNCTION(PanelManager, Panels)

#endif // !_PANELMANAGER_H
