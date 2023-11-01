#ifndef _PLANT_H
#define _PLANT_H
#include "engine/Zigine.h"
#include "engine/AnimationEntity.h"
#include "Object.h"

class Plant : public Object
{
public:
	virtual void TakeDamage(const float damage) override {};

	inline uint32_t GetUserType() const { return PLANT_TYPE; }
	inline bool IsPlant() const override { return true; } 
private:
	DECLARE_CLASS(Plant, AnimationEntity)
};

#endif // !_PLANT_H
