#pragma once

enum LootMode : int
{
	WEAPONS = 1 << 0,
	AMMO = 1 << 1,
	MEDIC = 1 << 2,
	EQUIPMENT = 1 << 3,
	ATTACHMENTS = 1 << 4,
	ALL = WEAPONS | AMMO | MEDIC | EQUIPMENT | ATTACHMENTS
};


namespace settings
{
	namespace esp
	{
		extern bool player;
		extern bool boxes;
		extern bool skeleton;
		extern int distance;
		extern bool loot;
		extern int loot_mode;
		extern bool vehicle;
	}

	namespace aimbot
	{
		extern int fov;
		extern bool draw_fov;
		extern bool on_mouse4;
		extern float smooth;
		extern bool norecoil;
		extern bool nospread;
		extern bool fullauto;
		extern bool nosway;
	}

	extern float player_speed;
}
