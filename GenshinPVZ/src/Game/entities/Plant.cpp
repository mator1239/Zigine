#include "engine/ui/Panel.h"

#include "Plant.h"

LINK_ENTITY_TO_CLASS(default_plant, Plant)

void Plant::SetTilePanelSettings(Panel* panel)
{
	const vector2 position = panel->GetPosition();
	const vector2 origin = panel->GetOrigin();

	SetPositon(position);
	SetOrigin(origin);
}


