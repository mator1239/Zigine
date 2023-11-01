#ifndef _IMEMORYALLOCATOR_H
#define _IMEMORYALLOCATOR_H
#include "engine/Zigine.h"

interface_class IMemoryAllocator
{
public:
	virtual void allocate(size_t size) = 0;
};
#endif // !_IMEMORYALLOCATOR_H
