#ifndef _MENUGAMESTATE_H
#define _MENUGAMESTATE_H
#include "engine/core/Layer.h"

class GameOver : public Layer
{
public:
	GameOver() {}

	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnImguiRender();
};

#endif // !_MENUGAMESTATE_H
