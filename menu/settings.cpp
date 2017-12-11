#include "settings.hpp"

namespace settings
{
	namespace esp
	{
		bool player = false;
		bool boxes = true;
		bool skeleton = true;
		int distance = 400;
		bool loot = true;
		int loot_mode = WEAPONS;
		bool vehicle = false;
	}

	namespace aimbot
	{
		int fov = 2;
		bool draw_fov = true;
		bool on_mouse4 = false;
		float smooth = 1.f;
		bool norecoil = true;
		bool nospread = true;
		bool fullauto = true;
		bool nosway = true;
	}

	float player_speed = 1.f;
}
