zombieConfig = {
	WalkSpeed = 20,
	ConfigId = ZOMBIE_FLAG,
	Texture = { 
		Key = "FlagZombieTexture",
		Path = "materials/zombies/ZombieSkeleton_tex.png" 
	},
	Animation = {
		Atlas = "animations/zombies/ZombieSkeleton_tex.json",
		Skeleton = "animations/zombies/ZombieSkeleton_ske.json"
	}
}

LoadZombieConfig(zombieConfig)