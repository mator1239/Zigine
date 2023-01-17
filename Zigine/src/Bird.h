#pragma once
#include "engine/Entity.h"

class CBird : public CBaseEntity
{
public:
	virtual void spawn();
	virtual void update();
	virtual void draw();
private:
};