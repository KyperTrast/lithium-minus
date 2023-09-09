/*
* Kyper - Lithium port
* 
* A few functions that aim to provide some sort of help text to players.
* The Inventory menu is kind of clunky, but I don't think this is any better...

*/
#include "g_local.h"

// Some help info, basically spit out some text in console
void Help_Lithium(edict_t* ent, const char* htext)
{
	const char* generic_help[] = { "\nSetting up hook:\n",
								  "================\n",
								  "Hold button down (change mouse2 to desired key):\n",
								  "alias +hook hook ; alias -hook unhook ; bind mouse2 +hook\n",
								  "\n",
								  "Toggle (change mouse2 to desired key):\n",
								  "bind mouse2 hook_toggle\n",
								  "\n",
								  "Runes Overview:\n",
								  "================\n",
								  "Runes spawn randomly on the map, touch one to pick it up.\n",
								  "You can only hold one at a time.\n",
								  "Your held rune is displayed in the bottom right corner.\n",
								  "Drop runes with drop_rune\n",
								  "\n",
								  "Resist: Blue, cuts damage by 50%\n",
								  "Strength: Red, deals double damage\n",
								  "Haste: Yellow, doubles firing rate%\n",
								  "Regen: Green, regenerates health, faster when lower\n",
								  "Vampire: Pink, heals you for 50% of damage dealt\n",
								  "\n",
								  "Other commands:\n",
								  "================\n",
								  "lith_help_cvar: lists summary of each cvar.\n",
								  "set lith_hide_help 1 u   : hides bottom help text\n",
								  nullptr
	};

	const char* cvars_help[] = { "Runes:\n",
								  "================\n",
								  "use_runes: use g_use_runes instead. Default: 1\n",
								  "rune_minbound: Used in a calcuation for bounding box. Default: -4\n",
								  "rune_life: Number of seconds before a rune respawns. Default: 20\n",
								  "rune_perplayer: Used in a calculation to spawn runes based on player count. Default: 0.6\n",
								  "rune_spawnpersecond: Number of runes to spawn per second. Default: 1\n",
								  "rune_min: Used in a calculation to only spawn runes to a limit. Default: 3\n",
								  "rune_max: Used in a calculation to only spawn runes to a limit. Default: 12\n",
								  "rune_resist: Divides damage by this when holding Resist. Default: 2.0\n",
								  "rune_strength: Multiplies damage by this when holding Strength. Default: 2.0\n",
								  "rune_regen: Used in a calculation for health regen rate. Default: 0.25\n",
								  "rune_regenmax: Maximum health limit that Regen will heal to. Default: 200\n",
								  "rune_regencap: Used in a calculation to limit health regen rate. Default: 3.5\n",
								  "rune_vampire: Percentage of damage returned as health with Vampire. Default: 0.5\n",
								  "rune_vampiremax: Maximum health limit that Vampire can heal to. Default: 200\n",
								  "rune_flags: Bit field that controls which runes to use in game. Default: 31 (all runes)\n",
								  "rune_strength_sound: Probably shouldn't be a cvar. Default: items/damage3.wav\n",
								  "rune_resist_sound: Probably shouldn't be a cvar. Default: world/force2.wav\n",
								  "rune_haste_sound: Probably shouldn't be a cvar. Default: world/x_light.wav\n",
								  "rune_regen_sound: Probably shouldn't be a cvar. Default: items/s_health.wav\n",
								  "rune_vampire_sound: Probably shouldn't be a cvar. Default: makron/pain2.wav\n",
								  "\n",
								  "Hook:\n",
								  "================\n",
								  "hook_speed: Hook speed. Default: 900\n",
								  "hook_pullspeed: Player pull speed after hooking a target. Default: 700\n",
								  "hook_sky: Enables/disables ability to hook the sky. Default: 0\n",
								  "hook_maxtime: Number of seconds your hook will stay attached. Default: 5\n",
								  "hook_damage: Damage dealt per 100ms(?) while hooked on a target.  Default: 1\n",
								  "hook_initdamage: Initial damage dealt when hooking a target. Default: 10\n",
								  "hook_maxdamage: Maximum limit of hook damage.  Default: 20\n",
								  "hook_delay: Number of seconds before player can refire hook. Default: 0.2\n",
								  "\n",
								  "Other:\n",
								  "================\n",
								  "g_use_hook: Enables/disables use of off-hand hook. Default: 1\n",
								  "g_use_runes: Enables/disables runes. Default: 1\n",
								  "g_hook_help: Enables/disables showing help text for everyone. Default: 0\n",
								  "g_hook_wave: Adds hook_toggle to wave 3 command - console friendly! Default: 0\n",
								  nullptr
	};

	const char** helptext = generic_help;

	if (Q_strcasecmp(htext, "lith_help_cvar") == 0)
		helptext = cvars_help;

	while (*helptext != nullptr)
	{
		gi.LocClient_Print(ent, PRINT_HIGH, "{}", *helptext);
		helptext++;
	}
}

// only display the help HUD text if we haven't moved for a while
// you gain a bit of velocity when you spawn, so this calculation factors in a "buffer"
void Help_LithHUDText(edict_t *player)
{
	if (player->velocity != vec3_origin)
	{
		player->client->help_idle_time += 100_ms;

		if (level.time - player->client->help_idle_time < -2000_ms)
			player->client->help_idle_time = level.time + 2000_ms;
		else if (level.time - player->client->help_idle_time > 2000_ms)
			player->client->help_idle_time = level.time - 2000_ms;
	}
}