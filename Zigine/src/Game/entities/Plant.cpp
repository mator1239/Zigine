#include "engine/ui/Panel.h"

#include "Plant.h"

void Plant::SetTilePanelSettings(Panel* panel)
{
	const vector2 position = panel->GetPosition();
	const vector2 origin = panel->GetOrigin();

	SetPositon(position);
	SetOrigin(origin);
}
