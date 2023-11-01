#ifndef _MENUGAMESTATE_H
#define _MENUGAMESTATE_H
#include "engine/core/Layer.h"

class GameMenu : public Layer
{
public:
	GameMenu() {}

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnImguiRender();
};

#endif // !_MENUGAMESTATE_H
