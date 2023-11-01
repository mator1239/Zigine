zombieConfig = {
	WalkSpeed = 10,
	ConfigId = ZOMBIE_DEFAULT,
	Texture = { 
		Key = "ZombieDefault",
		Path = "materials/zombies/ZombieSkeleton_tex.png" 
	},
	Animation = {
		Atlas = "animations/zombies/ZombieSkeleton_tex.json",
		Skeleton = "animations/zombies/ZombieSkeleton_ske.json"
	}
}

LoadZombieConfig(zombieConfig)