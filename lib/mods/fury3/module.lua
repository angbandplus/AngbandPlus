add_module
{
	["name"]    = "FuryBand G",
	["version"] = { 1, 1, 0 },
	["author"]  = { "The Fury", "thefury@furytech.net" },
	["desc"] = {
		"A much harder version of T. All monsters are double the player level.",
		},

	["rand_quest"] = FALSE,
	["C_quest"] = FALSE,

	["base_dungeon"] = 4,
	["death_dungeon"] = 28,

	 ["astral_dungeon"] = 4,
        ["astral_wild_x"] = 1,
        ["astral_wild_y"] = 1,

	["random_artifact_weapon_chance"] = 33,
	["random_artifact_armor_chance"] = 33,
	["random_artifact_jewelry_chance"] = 34,

	["max_plev"] = 75,
	["max_skill_overage"] = 5,
	
	["mod_savefiles"]=
	{
		"FuryBand G",
	},
	["layout"] = 
	{ 
	["apex"] = "fury3", 
	["core"] = "fury3",
	["data"] = "fury3", 
	["dngn"] = "fury3",
	["edit"] = "fury3", 
	["file"] = "fury3",
	["help"] = "fury3",
	["note"] = "fury3",
	["save"] = "fury3",
	["scpt"] = "fury3",
	["user"] = "fury3",
	["pref"] = "fury3",
	}, 
}