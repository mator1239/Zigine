#ifndef _IMANAGERUKNOWN_H
#define _IMANAGERUKNOWN_H
#include "engine/Zigine.h"

interface_class IManagerUnknown
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif // !_IMANAGERUKNOWN_H
