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
								  "Drop runes with drop_rune or Weapon Wheel+crouch (if enabled).\n",
								  "\n",
								  "Resist: Blue, cuts damage by 50%\n",
								  "Strength: Red, deals double damage\n",
								  "Haste: Yellow, doubles firing rate%\n",
								  "Regen: Green, regenerates health, faster when lower\n",
								  "Vampire: Pink, heals you for 50% of damage dealt\n",
								  "\n",
								  "Other commands:\n",
								  "================\n",
								  "lith_help_cvar: lists one-liners of hook/rune/misc cvars.\n",
								  "lith_help_cvarpack: lists one-liners of Ammo Pack cvars.\n",
								  "lith_help_cvarstartmax: lists one-liners of starting items/max capacity of ammo and health.\n",
								  "lith_help_cvarbaseweapon: lists one-liners of base weapon properties.\n",
								  "lith_help_cvarexpweapon: lists one-liners of expansion weapon properties.\n",
								  "lith_help_cvardisable: lists one-liners to disable weapon/power-up spawns.\n",
								  "\n",
								  "Currently maintained at:\n",
								  "https://github.com/KyperTrast/lithium-minus\n",
								  " \n",
								  nullptr
	};

	const char* cvars_help[] = { "Runes:\n",
								  "================\n",
								  "g_use_runes: Enables/disables runes. Default: 1\n",
								  "g_rune_crouchdrop: Ability to drop runes by opening Weapon Wheel+crouching. Default: 1\n",
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
								  "rune_strength_sound: Sound for the Stength rune. Default: items/damage3.wav\n",
								  "rune_resist_sound: Sound for the Resist rune. Default: world/force2.wav\n",
								  "rune_haste_sound: Sound for the Haste rune. Default: world/x_light.wav\n",
								  "rune_regen_sound: Sound for the Regen rune. Default: items/s_health.wav\n",
								  "rune_vampire_sound: Sound for the Vampire rune. Default: makron/pain2.wav\n",
								  "\n",
								  "Hook:\n",
								  "================\n",
								  "g_use_hook: Enables/disables use of off-hand hook. Default: 1\n",
								  "g_hook_help: Enables/disables showing help text for everyone. Default: 1\n",
								  "g_hook_wave: Adds hook_toggle to wave 3 command - console friendly! Default: 1\n",
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
								  "use_safety: Grants temporary invincibility after spawning. Default: 0\n",
								  "safety_time: Controls duration of invincibility after spawning. Default: 4.0\n",
								  "knockback_adjust: Multiplier for adjusting knockback of all weapons. Default: 1.0\n",
								  "knockback_self: Multiplier for adjusting knockback to self damage. Default: 3.2\n",
								  "fall_damagemod: Multiplier for adjusting fall damage. Default: 1.0\n",
								  nullptr
	};

	const char *cvars_pack[] =  { "Ammo Pack:\n",
								  "================\n",
								  "use_packs: Replaces map Ammo Packs with randomly spawning ones. Default: 0\n",
								  "pack_spawn: Chance of Ammo Pack spawning per item. Default: 0.03\n",
								  "pack_life: Number of seconds Ammo Pack will stay before despawning. Default: 25\n",
								  "pack_health: New max health limit after picking up an Ammo Pack.  Default: 100\n",
								  "pack_armor: Not implemented. Default: 200\n",
								  "pack_bullets: New max bullet capacity after picking up an Ammo Pack. Default: 300\n",
								  "pack_shells: New max shell capacity after picking up an Ammo Pack. Default: 200\n",
								  "pack_rockets: New max rocket capacity after picking up an Ammo Pack. Default: 100\n",
								  "pack_grenades: New max grenade capacity after picking up an Ammo Pack. Default: 100\n",
								  "pack_cells: New max cell capacity after picking up an Ammo Pack. Default: 300\n",
								  "pack_slugs: New max slug capacity after picking up an Ammo Pack. Default: 100\n",
								  "pack_magslugs: New max mag slug capacity after picking up an Ammo Pack.  Default: 100\n",
								  "pack_flechettes: New max flechette capacity after picking up an Ammo Pack. Default: 300\n",
								  "pack_disruptorrounds: New max rounds capacity after picking up an Ammo Pack. Default: 30\n",
								  "pack_prox: New max prox capacity after picking up an Ammo Pack. Default: 50\n",
								  "pack_tesla: New max tesla capacity after picking up an Ammo Pack. Default: 5\n",
								  "pack_traps: New max trap capacity after picking up an Ammo Pack. Default: 5\n",
								  nullptr
	};

	const char *cvars_startmax[] = { "Starting Inventory and Max Capacity:\n"
								  "================\n",
								  "start_health: Starting health after spawning. Default: 100\n",
								  "start_armor: Starting jacket armor after spawning. Default: 0\n",
								  "start_bullets: Bullets given after spawning. Default: 0\n",
								  "start_shells: Shells given after spawning. Default: 0\n",
								  "start_rockets: Rockets given after spawning. Default: 0\n",
								  "start_grenades: Grenades given after spawning. Default: 0\n",
								  "start_cells: Cells given after spawning. Default: 0\n",
								  "start_slugs: Slugs given after spawning. Default: 0\n",
								  "start_magslugs: Mag Slugs given after spawning. Default: 0\n",
								  "start_flechettes: Flechettes given after spawning. Default: 0\n",
								  "start_disruptorrounds: Rounds given after spawning. Default: 0\n",
								  "start_prox: Prox given after spawning. Default: 0\n",
								  "start_tesla: Tesla given after spawning. Default: 0\n",
								  "start_traps: Traps given after spawning. Default: 0\n",
								  "max_health: Maximum health capacity. Default: 100\n",
								  "max_bullets: Maximum bullet capacity. Default: 200\n",
								  "max_shells: Maximum shells capacity. Default: 100\n",
								  "max_rockets: Maximum rockets capacity. Default: 50\n",
								  "max_grenades: Maximum grenades capacity. Default: 50\n",
								  "max_cells: Maximum cells capacity. Default: 200\n",
								  "max_slugs: Maximum slugs capacity. Default: 50\n",
								  "max_magslugs: Maximum mag slugs capacity. Default: 50\n",
								  "max_flechettes: Maximum flechettes capacity. Default: 200\n",
								  "max_disruptorrounds: Maximum rounds capacity. Default: 12\n",
								  "max_prox: Maximum prox capacity. Default: 50\n",
								  "max_tesla: Maximum tesla capacity. Default: 5\n",
								  "max_traps: Maximum traps capacity. Default: 5\n",
								  "start_shotgun: Spawn with a Shotgun. Default: 0\n",
								  "start_sshotgun: Spawn with a Super Shotgun. Default: 0\n",
								  "start_machinegun: Spawn with a Machinegun. Default: 0\n",
								  "start_chaingun: Spawn with a Chaingun. Default: 0\n",
								  "start_grenadelauncher: Spawn with a Grenade Launcher. Default: 0\n",
								  "start_rocketlauncher: Spawn with a Rocket Launcher. Default: 0\n",
								  "start_hyperblaster: Spawn with a Hyperblaster. Default: 0\n",
								  "start_railgun: Spawn with a Railgun. Default: 0\n",
								  "start_bfg: Spawn with a BFG. Default: 0\n",
								  "start_chainfist: Spawn with a Chainfist. Default: 0\n",
								  "start_etfrifle: Spawn with an ETF Rifle. Default: 0\n",
								  "start_proxlauncher: Spawn with a Prox Launcher. Default: 0\n",
								  "start_plasmabeam: Spawn with a Plasma Beam. Default: 0\n",
								  "start_ionripper: Spawn with an Ionripper. Default: 0\n",
								  "start_phalanx: Spawn with a Phalanx. Default: 0\n",
								  "start_disruptor: Spawn with a Disruptor. Default: 0\n",
								  nullptr
	};

	const char *cvars_baseweapon[] = { "Base weapon properties:\n"
								  "================\n",
								  "blaster_damage: Sets damage of Blaster projectile. Default: 15\n",
								  "blaster_speed: Sets speed of Blaster projectile. Default: 1500\n",
								  "shotgun_damage: Sets damage of single SG pellet. Default: 4\n",
								  "shotgun_count: Sets how many pellets are fired from SG. Default: 12\n",
								  "shotgun_hspread: Sets horizontal spread of SG. Default: 500\n",
								  "shotgun_vspread: Sets vertical spread of SG. Default: 500\n",
								  "sshotgun_damage: Sets damage of single SSG pellet. Default: 6\n",
								  "sshotgun_count: Sets how many pellets are fired from SSG. Default: 20\n",
								  "sshotgun_hspread: Sets horizontal spread of SSG. Default: 1000\n",
								  "sshotgun_vspread: Sets vertical spread of SSG. Default: 500\n",
								  "machinegun_damage: Sets damage of MG bullet. Default: 8\n",
								  "machinegun_hspread: Sets horizontal spread of MG. Default: 300\n",
								  "machinegun_vspread: Sets vertical spread of MG. Default: 500\n",
								  "chaingun_damage: Sets damage of CG bullet. Default: 6\n",
								  "chaingun_damage_sp: Single player damage of CG bullet. Default: 8\n",
								  "chaingun_hspread: Sets horizontal spread of CG. Default: 300\n",
								  "chaingun_vspread: Sets vertical spread of CG. Default: 500\n",
								  "grenade_damage: Sets damage of hand grenade. Default: 125\n",
								  "grenade_radius: Sets explosion radius of hand grenade. Default: 165\n",
								  "grenadelauncher_damage: Sets damage of GL projectile. Default: 120\n",
								  "grenadelauncher_radius: Sets explosion radius of GL. Default: 160\n",
								  "rocket_damage: Sets damage of RL. Default: 100\n",
								  "rocket_damage2: Sets extra random damage of RL. Default: 20\n",
								  "rocket_rdamage: Sets radius damage of RL. Default: 120\n",
								  "rocket_radius: Sets explosion radius of RL. Default: 120\n",
								  "rocket_speed: Sets speed of RL projectile. Default: 650\n",
								  "rocket_knockback: Sets knockback of RL. Default: 0\n",
								  "hyperblaster_damage: Sets damage of HB. Default: 15\n",
								  "hyperblaster_damage_sp: Single player damage of HB. Default: 20\n",
								  "hyperblaster_speed: Sets speed of HB projectile. Default: 1000\n",
								  "railgun_damage: Sets damage of RG. Default: 100\n",
								  "railgun_damage_sp: Single player damage of RG. Default: 125\n",
								  "bfg_damage: Sets damage of BFG. Default: 200\n",
								  "bfg_damage_sp: Single player damage of BFG. Default: 500\n",
								  "bfg_radius: Sets explosion radius of BFG. Default: 1000\n",
								  "bfg_speed: Sets speed of BFG. Default: 400\n",
								  "bfg_raydamage: Sets damage of BFG rays. Default: 5\n",
								  "bfg_raydamage_sp: Single player damage of BFG rays. Default: 10\n",
								  "bfg_balldamage: Sets damage of BFG ball. Default: 200\n",
								  "bfg_ballradius: Sets explosion radius of BFG ball. Default: 100\n",
								  nullptr
	};

	const char *cvars_expweapon[] = { "Expansion weapon properties:\n"
								  "================\n",
								  "chainfist_damage: Sets damage of Chainfist. Default: 15\n",
								  "chainfist_damage_sp: Single player damage of Chainfist. Default: 7\n",
								  "chainfist_range: Sets Chainfist range. Default: 24\n",
								  "etfrifle_damage: Sets damage of ETF Rifle projectile. Default: 10\n",
								  "etfrifle_speed: Sets speed of ETF Rifle projectile. Default: 1150\n",
								  "proxlauncher_damage: Sets damage of Prox Launcher. Default: 90\n",
								  "proxlauncher_radius: Sets radius of Prox Launcher. Default: 192.0\n",
								  "plasmabeam_damage: Sets damage of Plasma Beam. Default: 15\n",
								  "plasmabeam_kick: Sets knockback of Plasma Beam. Default: 75\n",
								  "plasmabeam_kick_sp: Single player knockback of Plasma Beam. Default: 30\n",
								  "ionripper_damage: Sets damage of Ionripper. Default: 30\n",
								  "ionripper_damage_sp: Single player damage of Ionripper. Default: 50\n",
								  "ionripper_speed: Sets speed of Ionripper projectile. Default: 500\n",
								  "phalanx_damage: Sets damage of Phalanx projectile. Default: 70\n",
								  "phalanx_damage2: Sets extra random damage of Phalanx. Default: 10\n",
								  "phalanx_rdamage: Sets radius damage of Phalanx projectile. Default: 120\n",
								  "phalanx_radius: Sets radius of Phalanx projectile. Default: 120\n",
								  "phalanx_rdamage2: Sets radius damage of Phalanx 2nd shot. Default: 120\n",
								  "phalanx_radius2: Sets radius of Phalanx 2nd shot. Default: 30\n",
								  "phalanx_speed: Sets speed of Phalanx projectile. Default: 725\n",
								  "disruptor_damage: Sets damage of Disruptor. Default: 45\n",
								  "disruptor_damage_sp: Single player damage of Disruptor. Default: 135\n",
								  "disruptor_speed: Sets speed of Disruptor projectile. Default: 1000\n",
								  "disruptor_fixticks: Disruptor always hits for 5 ticks, never 6. Default: 0\n",
								  "tesla_damagerate: Sets damage of Tesla. Default: 3\n",
								  "trap_triggerradius: Sets radius of Trap. Default: 48\n",
								  nullptr
	};

	const char *cvars_disable[] = { "Disable weapon/power-up spawns:\n"
								  "================\n",
								  "no_shotgun: Prevents SG from spawning. Default: 0\n",
								  "no_sshotgun: Prevents SSG from spawning. Default: 0\n",
								  "no_machinegun: Prevents MG from spawning. Default: 0\n",
								  "no_chaingun: Prevents CG from spawning. Default: 0\n",
								  "no_grenadelauncher: Prevents GL from spawning. Default: 0\n",
								  "no_rocketlauncher: Prevents RL from spawning. Default: 0\n",
								  "no_hyperblaster: Prevents HB from spawning. Default: 0\n",
								  "no_railgun: Prevents RG from spawning. Default: 0\n",
								  "no_bfg: Prevents BFG from spawning. Default: 0\n",
								  "no_chainfist: Prevents Chainfist from spawning. Default: 0\n",
								  "no_etfrifle: Prevents ETF Rifle from spawning. Default: 0\n",
								  "no_proxlauncher: Prevents Prox Launcher from spawning. Default: 0\n",
								  "no_plasmabeam: Prevents Plasma Beam from spawning. Default: 0\n",
								  "no_ionripper: Prevents Ionripper from spawning. Default: 0\n",
								  "no_phalanx: Prevents Phalanx from spawning. Default: 0\n",
								  "no_disruptor: Prevents Disruptor from spawning. Default: 0\n",
								  "no_tesla: Prevents Tesla from spawning. Default: 0\n",
								  "no_traps: Prevents Traps from spawning. Default: 0\n",
								  "no_pent: Prevents Invulnerability from spawning. Default: 0\n",
								  "no_quad: Prevents Quad from spawning. Default: 0\n",
								  nullptr
	};

	const char** helptext = generic_help;

	if (Q_strcasecmp(htext, "lith_help_cvar") == 0)
		helptext = cvars_help;
	else if (Q_strcasecmp(htext, "lith_help_cvarpack") == 0)
		helptext = cvars_pack;
	else if (Q_strcasecmp(htext, "lith_help_cvarstartmax") == 0)
		helptext = cvars_startmax;
	else if (Q_strcasecmp(htext, "lith_help_cvarbaseweapon") == 0)
		helptext = cvars_baseweapon;
	else if (Q_strcasecmp(htext, "lith_help_cvarexpweapon") == 0)
		helptext = cvars_expweapon;
	else if (Q_strcasecmp(htext, "lith_help_cvardisable") == 0)
		helptext = cvars_disable;

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
		else if (level.time - player->client->help_idle_time > 2500_ms)
			player->client->help_idle_time = level.time - 2500_ms;
	}
}