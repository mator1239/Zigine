--[[
	'+' - variables that have a default value and you can just do not implement them

	cards value template:
		'Name' - should be a table value

	'Name' value template:
		Texture - path to the texture (automaticly starts with 'game/')
		+Cost - cost for plant (default: 100)
		Class - entity class (should be prepared in source code or else you have got an error
			and game's crash)
--]]

cards = {
	Sunflower = { Key = "Peashooter", Texture = "materials/Peashooter.png", Cost = 100, Class = "plant_sunflower" },
}


