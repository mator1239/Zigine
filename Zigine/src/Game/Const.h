#ifndef _CONST_H
#define _CONST_H

#define ZOMBIE_COLLISION_GROUP (1 << 1)
#define PROJECTILE_COLLISION_GROUP (1 << 2)
#define PLANT_COLLISION_GROUP (1 << 3)

#define ZOMBIE_TYPE 0x0001
#define PLANT_TYPE 0x0002
#define PROJECTILE_TYPE 0x0002

#define MASK_ZOMBIE (PLANT_TYPE | PROJECTILE_TYPE)
#define MASK_PLANT (ZOMBIE_TYPE | PROJECTILE_TYPE)
#define MASK_PROJECTILE (ZOMBIE_TYPE)

#endif // !_CONST_H