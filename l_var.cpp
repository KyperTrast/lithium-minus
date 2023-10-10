/*============================================================================

	This file is part of Lithium II Mod for Quake II
	Copyright (C) 1997, 1998, 1999, 2010 Matthew A. Ayres

	Lithium II Mod is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Lithium II Mod is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Lithium II Mod.  If not, see <http://www.gnu.org/licenses/>.

	Quake II is a trademark of Id Software, Inc.

	Code by Matt "WhiteFang" Ayres, matt@lithium.com

============================================================================*/

// Kyper - Lithium port
// partial import of l_var.c
// I've decided not to port over the lvar struct for now, 
// so far the only functionality that seems useful is the pointer to onchange functions

#include "g_local.h"

cvar_t *use_safety;
cvar_t *safety_time;

cvar_t *start_health;
cvar_t *start_armor;
cvar_t *start_bullets;
cvar_t *start_shells;
cvar_t *start_rockets;
cvar_t *start_grenades;
cvar_t *start_cells;
cvar_t *start_slugs;
// Kyper - Lithium port - expansion ammo
cvar_t *start_magslugs;
cvar_t *start_flechettes;
cvar_t *start_disruptorrounds;
cvar_t *start_prox;
cvar_t *start_tesla;
cvar_t *start_traps;

cvar_t *max_health;
// Kyper - Lithium port
// I've decided not to implement max_armor, seems janky - appears to only affect shards
//cvar_t *max_armor;
cvar_t *max_bullets;
cvar_t *max_shells;
cvar_t *max_rockets;
cvar_t *max_grenades;
cvar_t *max_cells;
cvar_t *max_slugs;
// Kyper - Lithium port - expansion ammo
cvar_t *max_magslugs;
cvar_t *max_flechettes;
cvar_t *max_disruptorrounds;
cvar_t *max_prox;
cvar_t *max_tesla;
cvar_t *max_traps;

// Kyper - Lithium port
// I've decided not to implement start_weapon and start_blaster
// in original, start_weapon doesn't place that weapon in your inventory
// and start_blaster 0 will only equip the blaster if you auto-switch from having no ammo in
// all other weapons, but testing this in remaster seems to crash the game
//cvar_t *start_weapon;
//cvar_t *start_blaster;
cvar_t *start_shotgun;
cvar_t *start_sshotgun;
cvar_t *start_machinegun;
cvar_t *start_chaingun;
cvar_t *start_grenadelauncher;
cvar_t *start_rocketlauncher;
cvar_t *start_hyperblaster;
cvar_t *start_railgun;
cvar_t *start_bfg;
// Kyper - Lithium port - expansion weapons
cvar_t *start_chainfist;
cvar_t *start_etfrifle;
cvar_t *start_proxlauncher;
cvar_t *start_plasmabeam;
cvar_t *start_ionripper;
cvar_t *start_phalanx;
cvar_t *start_disruptor;

// weapon vars
cvar_t *blaster_damage;
cvar_t *blaster_speed;
cvar_t *shotgun_damage;
cvar_t *shotgun_count;
cvar_t *shotgun_hspread;
cvar_t *shotgun_vspread;
cvar_t *sshotgun_damage;
cvar_t *sshotgun_count;
cvar_t *sshotgun_hspread;
cvar_t *sshotgun_vspread;
cvar_t *machinegun_damage;
cvar_t *machinegun_hspread;
cvar_t *machinegun_vspread;
cvar_t *chaingun_damage;
cvar_t *chaingun_damage_sp;
cvar_t *chaingun_hspread;
cvar_t *chaingun_vspread;
cvar_t *grenade_damage;
cvar_t *grenade_radius;
cvar_t *grenadelauncher_damage;
cvar_t *grenadelauncher_radius;
cvar_t *rocket_damage;
cvar_t *rocket_damage2;
cvar_t *rocket_rdamage;
cvar_t *rocket_radius;
cvar_t *rocket_speed;
cvar_t *rocket_knockback;
cvar_t *hyperblaster_damage;
cvar_t *hyperblaster_damage_sp;
cvar_t *hyperblaster_speed;
cvar_t *railgun_damage;
cvar_t *railgun_damage_sp;
cvar_t *bfg_damage;
cvar_t *bfg_damage_sp;
cvar_t *bfg_radius;
cvar_t *bfg_speed;
cvar_t *bfg_raydamage;
cvar_t *bfg_raydamage_sp;
cvar_t *bfg_balldamage;
cvar_t *bfg_ballradius;
// Kyper - Lithium port - expansion weapons
cvar_t *chainfist_damage;
cvar_t *chainfist_damage_sp;
cvar_t *chainfist_range;
cvar_t *etfrifle_damage;
cvar_t *etfrifle_speed;
cvar_t *proxlauncher_damage;
cvar_t *proxlauncher_radius;
cvar_t *ionripper_damage;
cvar_t *ionripper_damage_sp;
cvar_t *ionripper_speed;
cvar_t *plasmabeam_damage;
cvar_t *plasmabeam_kick;
cvar_t *plasmabeam_kick_sp;
cvar_t *phalanx_damage;
cvar_t *phalanx_damage2;
cvar_t *phalanx_rdamage;
cvar_t *phalanx_radius;
cvar_t *phalanx_rdamage2;
cvar_t *phalanx_radius2;
cvar_t *phalanx_speed;
cvar_t *disruptor_damage;
cvar_t *disruptor_damage_sp;
cvar_t *disruptor_speed;
cvar_t *disruptor_fixticks;
cvar_t *tesla_damagerate;
cvar_t *trap_triggerradius;

cvar_t *no_shotgun;
cvar_t *no_sshotgun;
cvar_t *no_machinegun;
cvar_t *no_chaingun;
cvar_t *no_grenadelauncher;
cvar_t *no_rocketlauncher;
cvar_t *no_hyperblaster;
cvar_t *no_railgun;
cvar_t *no_bfg;
// Kyper - Lithium port - expansion weapons
cvar_t *no_chainfist;
cvar_t *no_etfrifle;
cvar_t *no_proxlauncher;
cvar_t *no_plasmabeam;
cvar_t *no_ionripper;
cvar_t *no_phalanx;
cvar_t *no_disruptor;
cvar_t *no_tesla;
cvar_t *no_traps;

cvar_t *no_pent;
cvar_t *no_quad;

cvar_t *knockback_adjust;
cvar_t *knockback_self;
cvar_t *fall_damagemod;

void Var_InitGame(void)
{
	// Kyper - Lithium port - originally contained in lithium.c
	use_safety = gi.cvar("use_safety", "0", CVAR_NOFLAGS);
	safety_time = gi.cvar("safety_time", "4.0", CVAR_NOFLAGS);

	// ammo vars
	start_health = gi.cvar("start_health", "100", CVAR_NOFLAGS);
	start_armor = gi.cvar("start_armor", "0", CVAR_NOFLAGS);
	start_bullets = gi.cvar("start_bullets", "0", CVAR_NOFLAGS);
	start_shells = gi.cvar("start_shells", "0", CVAR_NOFLAGS);
	start_rockets = gi.cvar("start_rockets", "0", CVAR_NOFLAGS);
	start_grenades = gi.cvar("start_grenades", "0", CVAR_NOFLAGS);
	start_cells = gi.cvar("start_cells", "0", CVAR_NOFLAGS);
	start_slugs = gi.cvar("start_slugs", "0", CVAR_NOFLAGS);
	// Kyper - Lithium port - expansion ammo
	start_magslugs = gi.cvar("start_magslugs", "0", CVAR_NOFLAGS);
	start_flechettes = gi.cvar("start_flechettes", "0", CVAR_NOFLAGS);
	start_disruptorrounds = gi.cvar("start_disruptorrounds", "0", CVAR_NOFLAGS);
	start_prox = gi.cvar("start_prox", "0", CVAR_NOFLAGS);
	start_tesla = gi.cvar("start_tesla", "0", CVAR_NOFLAGS);
	start_traps = gi.cvar("start_traps", "0", CVAR_NOFLAGS);

	max_health = gi.cvar("max_health", "100", CVAR_NOFLAGS);
	//max_armor = gi.cvar("max_armor", "200", CVAR_NOFLAGS);
	max_bullets = gi.cvar("max_bullets", "200", CVAR_NOFLAGS);
	max_shells = gi.cvar("max_shells", "100", CVAR_NOFLAGS);
	max_rockets = gi.cvar("max_rockets", "50", CVAR_NOFLAGS);
	max_grenades = gi.cvar("max_grenades", "50", CVAR_NOFLAGS);
	max_cells = gi.cvar("max_cells", "200", CVAR_NOFLAGS);
	max_slugs = gi.cvar("max_slugs", "50", CVAR_NOFLAGS);
	// Kyper - Lithium port - expansion ammo
	max_magslugs = gi.cvar("max_magslugs", "50", CVAR_NOFLAGS);
	max_flechettes = gi.cvar("max_flechettes", "200", CVAR_NOFLAGS);
	max_disruptorrounds = gi.cvar("max_disruptorrounds", "12", CVAR_NOFLAGS);
	max_prox = gi.cvar("max_prox", "50", CVAR_NOFLAGS);
	max_tesla = gi.cvar("max_tesla", "5", CVAR_NOFLAGS);
	max_traps = gi.cvar("max_traps", "5", CVAR_NOFLAGS);

	// weapon vars
	start_shotgun = gi.cvar("start_shotgun", "0", CVAR_NOFLAGS);
	start_sshotgun = gi.cvar("start_sshotgun", "0", CVAR_NOFLAGS);
	start_machinegun = gi.cvar("start_machinegun", "0", CVAR_NOFLAGS);
	start_chaingun = gi.cvar("start_chaingun", "0", CVAR_NOFLAGS);
	start_grenadelauncher = gi.cvar("start_grenadelauncher", "0", CVAR_NOFLAGS);
	start_rocketlauncher = gi.cvar("start_rocketlauncher", "0", CVAR_NOFLAGS);
	start_hyperblaster = gi.cvar("start_hyperblaster", "0", CVAR_NOFLAGS);
	start_railgun = gi.cvar("start_railgun", "0", CVAR_NOFLAGS);
	start_bfg = gi.cvar("start_bfg", "0", CVAR_NOFLAGS);
	// Kyper - Lithium port - expansion weapons
	start_chainfist = gi.cvar("start_chainfist", "0", CVAR_NOFLAGS);
	start_etfrifle = gi.cvar("start_etfrifle", "0", CVAR_NOFLAGS);
	start_proxlauncher = gi.cvar("start_proxlauncher", "0", CVAR_NOFLAGS);
	start_plasmabeam = gi.cvar("start_plasmabeam", "0", CVAR_NOFLAGS);
	start_ionripper = gi.cvar("start_ionripper", "0", CVAR_NOFLAGS);
	start_phalanx = gi.cvar("start_phalanx", "0", CVAR_NOFLAGS);
	start_disruptor = gi.cvar("start_disruptor", "0", CVAR_NOFLAGS);

	blaster_damage = gi.cvar("blaster_damage", "15", CVAR_NOFLAGS);
	blaster_speed = gi.cvar("blaster_speed", "1500", CVAR_NOFLAGS);

	shotgun_damage = gi.cvar("shotgun_damage", "4", CVAR_NOFLAGS);
	shotgun_count = gi.cvar("shotgun_count", "12", CVAR_NOFLAGS);
	shotgun_hspread = gi.cvar("shotgun_hspread", "500", CVAR_NOFLAGS);
	shotgun_vspread = gi.cvar("shotgun_vspread", "500", CVAR_NOFLAGS);

	sshotgun_damage = gi.cvar("sshotgun_damage", "6", CVAR_NOFLAGS);
	sshotgun_count = gi.cvar("sshotgun_count", "20", CVAR_NOFLAGS);
	sshotgun_hspread = gi.cvar("sshotgun_hspread", "1000", CVAR_NOFLAGS);
	sshotgun_vspread = gi.cvar("sshotgun_vspread", "500", CVAR_NOFLAGS);

	machinegun_damage = gi.cvar("machinegun_damage", "8", CVAR_NOFLAGS);
	machinegun_hspread = gi.cvar("machinegun_hspread", "300", CVAR_NOFLAGS);
	machinegun_vspread = gi.cvar("machinegun_vspread", "500", CVAR_NOFLAGS);

	chaingun_damage = gi.cvar("chaingun_damage", "6", CVAR_NOFLAGS);
	chaingun_damage_sp = gi.cvar("chaingun_damage_sp", "8", CVAR_NOFLAGS);
	chaingun_hspread = gi.cvar("chaingun_hspread", "300", CVAR_NOFLAGS);
	chaingun_vspread = gi.cvar("chaingun_vspread", "500", CVAR_NOFLAGS);

	grenade_damage = gi.cvar("grenade_damage", "125", CVAR_NOFLAGS);
	grenade_radius = gi.cvar("grenade_radius", "165", CVAR_NOFLAGS);

	grenadelauncher_damage = gi.cvar("grenadelauncher_damage", "120", CVAR_NOFLAGS);
	grenadelauncher_radius = gi.cvar("grenadelauncher_radius", "160", CVAR_NOFLAGS);

	rocket_damage = gi.cvar("rocket_damage", "100", CVAR_NOFLAGS);
	rocket_damage2 = gi.cvar("rocket_damage2", "20", CVAR_NOFLAGS);
	rocket_rdamage = gi.cvar("rocket_rdamage", "120", CVAR_NOFLAGS);
	rocket_radius = gi.cvar("rocket_radius", "120", CVAR_NOFLAGS);
	rocket_speed = gi.cvar("rocket_speed", "650", CVAR_NOFLAGS);
	rocket_knockback = gi.cvar("rocket_knockback", "0", CVAR_NOFLAGS);

	hyperblaster_damage = gi.cvar("hyperblaster_damage", "15", CVAR_NOFLAGS);
	hyperblaster_damage_sp = gi.cvar("hyperblaster_damage_sp", "20", CVAR_NOFLAGS);
	hyperblaster_speed = gi.cvar("hyperblaster_speed", "1000", CVAR_NOFLAGS);

	railgun_damage = gi.cvar("railgun_damage", "100", CVAR_NOFLAGS);
	railgun_damage_sp = gi.cvar("railgun_damage_sp", "125", CVAR_NOFLAGS);

	bfg_damage = gi.cvar("bfg_damage", "200", CVAR_NOFLAGS);
	bfg_damage_sp = gi.cvar("bfg_damage_sp", "500", CVAR_NOFLAGS);
	bfg_radius = gi.cvar("bfg_radius", "1000", CVAR_NOFLAGS);
	bfg_speed = gi.cvar("bfg_speed", "400", CVAR_NOFLAGS);
	bfg_raydamage = gi.cvar("bfg_raydamage", "5", CVAR_NOFLAGS);
	bfg_raydamage_sp = gi.cvar("bfg_raydamage_sp", "10", CVAR_NOFLAGS);
	bfg_balldamage = gi.cvar("bfg_balldamage", "200", CVAR_NOFLAGS);
	bfg_ballradius = gi.cvar("bfg_ballradius", "100", CVAR_NOFLAGS);

	// Kyper - Lithium port - expansion weapons
	chainfist_damage = gi.cvar("chainfist_damage", "15", CVAR_NOFLAGS);
	chainfist_damage_sp = gi.cvar("chainfist_damage_sp", "7", CVAR_NOFLAGS);
	chainfist_range = gi.cvar("chainfist_range", "24", CVAR_NOFLAGS);

	etfrifle_damage = gi.cvar("etfrifle_damage", "10", CVAR_NOFLAGS);
	etfrifle_speed = gi.cvar("etfrifle_speed", "1150", CVAR_NOFLAGS);

	proxlauncher_damage = gi.cvar("proxlauncher_damage", "90", CVAR_NOFLAGS);
	proxlauncher_radius = gi.cvar("proxlauncher_radius", "192.0", CVAR_NOFLAGS);

	plasmabeam_damage = gi.cvar("plasmabeam_damage", "15", CVAR_NOFLAGS);
	plasmabeam_kick = gi.cvar("plasmabeam_kick", "75", CVAR_NOFLAGS);
	plasmabeam_kick_sp = gi.cvar("plasmabeam_kick_sp", "30", CVAR_NOFLAGS);

	ionripper_damage = gi.cvar("ionripper_damage", "30", CVAR_NOFLAGS);
	ionripper_damage_sp = gi.cvar("ionripper_damage_sp", "50", CVAR_NOFLAGS);
	ionripper_speed = gi.cvar("ionripper_speed", "500", CVAR_NOFLAGS);

	phalanx_damage = gi.cvar("phalanx_damage", "70", CVAR_NOFLAGS);
	phalanx_damage2 = gi.cvar("phalanx_damage2", "10", CVAR_NOFLAGS);
	phalanx_rdamage = gi.cvar("phalanx_rdamage", "120", CVAR_NOFLAGS);
	phalanx_radius = gi.cvar("phalanx_radius", "120", CVAR_NOFLAGS);
	phalanx_rdamage2 = gi.cvar("phalanx_rdamage2", "120", CVAR_NOFLAGS);
	phalanx_radius2 = gi.cvar("phalanx_radius2", "30", CVAR_NOFLAGS);
	phalanx_speed = gi.cvar("phalanx_speed", "725", CVAR_NOFLAGS);

	disruptor_damage = gi.cvar("disruptor_damage", "45", CVAR_NOFLAGS);
	disruptor_damage_sp = gi.cvar("disruptor_damage_sp", "135", CVAR_NOFLAGS);
	disruptor_speed = gi.cvar("disruptor_speed", "1000", CVAR_NOFLAGS);
	disruptor_fixticks = gi.cvar("disruptor_fixticks", "0", CVAR_NOFLAGS);

	tesla_damagerate = gi.cvar("tesla_damagerate", "3", CVAR_NOFLAGS);

	trap_triggerradius = gi.cvar("trap_triggerradius", "48", CVAR_NOFLAGS);
	
	no_shotgun = gi.cvar("no_shotgun", "0", CVAR_NOFLAGS);
	no_sshotgun = gi.cvar("no_sshotgun", "0", CVAR_NOFLAGS);
	no_machinegun = gi.cvar("no_machinegun", "0", CVAR_NOFLAGS);
	no_chaingun = gi.cvar("no_chaingun", "0", CVAR_NOFLAGS);
	no_grenadelauncher = gi.cvar("no_grenadelauncher", "0", CVAR_NOFLAGS);
	no_rocketlauncher = gi.cvar("no_rocketlauncher", "0", CVAR_NOFLAGS);
	no_hyperblaster = gi.cvar("no_hyperblaster", "0", CVAR_NOFLAGS);
	no_railgun = gi.cvar("no_railgun", "0", CVAR_NOFLAGS);
	no_bfg = gi.cvar("no_bfg", "0", CVAR_NOFLAGS);
	// Kyper - Lithium port - expansion weapons
	no_chainfist = gi.cvar("no_chainfist", "0", CVAR_NOFLAGS);
	no_etfrifle = gi.cvar("no_etfrifle", "0", CVAR_NOFLAGS);
	no_proxlauncher = gi.cvar("no_proxlauncher", "0", CVAR_NOFLAGS);
	no_plasmabeam = gi.cvar("no_plasmabeam", "0", CVAR_NOFLAGS);
	no_ionripper = gi.cvar("no_ionripper", "0", CVAR_NOFLAGS);
	no_phalanx = gi.cvar("no_phalanx", "0", CVAR_NOFLAGS);
	no_disruptor = gi.cvar("no_disruptor", "0", CVAR_NOFLAGS);
	no_tesla = gi.cvar("no_tesla", "0", CVAR_NOFLAGS);
	no_traps = gi.cvar("no_traps", "0", CVAR_NOFLAGS);

	no_pent = gi.cvar("no_pent", "0", CVAR_NOFLAGS);
	no_quad = gi.cvar("no_quad", "0", CVAR_NOFLAGS);

	knockback_adjust = gi.cvar("knockback_adjust", "1.0", CVAR_NOFLAGS);
	knockback_self = gi.cvar("knockback_self", "3.2", CVAR_NOFLAGS);
	fall_damagemod = gi.cvar("fall_damagemod", "1.0", CVAR_NOFLAGS);
}

// Kyper - Lithium port
// originally called from PutClientInServer, InitClientPersistant seems more suitable
void Var_PutClientInServer(edict_t *ent)
{
	ent->client->pers.inventory[IT_AMMO_BULLETS] = start_bullets->integer;
	ent->client->pers.inventory[IT_AMMO_SHELLS] = start_shells->integer;
	ent->client->pers.inventory[IT_AMMO_ROCKETS] = start_rockets->integer;
	ent->client->pers.inventory[IT_AMMO_GRENADES] = start_grenades->integer;
	ent->client->pers.inventory[IT_AMMO_CELLS] = start_cells->integer;
	ent->client->pers.inventory[IT_AMMO_SLUGS] = start_slugs->integer;
	// Kyper - Lithium port - expansion ammo
	ent->client->pers.inventory[IT_AMMO_MAGSLUG] = start_magslugs->integer;
	ent->client->pers.inventory[IT_AMMO_FLECHETTES] = start_flechettes->integer;
	ent->client->pers.inventory[IT_AMMO_ROUNDS] = start_disruptorrounds->integer;
	ent->client->pers.inventory[IT_AMMO_PROX] = start_prox->integer;
	ent->client->pers.inventory[IT_AMMO_TESLA] = start_tesla->integer;
	ent->client->pers.inventory[IT_AMMO_TRAP] = start_traps->integer;

	ent->client->pers.inventory[IT_WEAPON_SHOTGUN] = start_shotgun->integer;
	ent->client->pers.inventory[IT_WEAPON_SSHOTGUN] = start_sshotgun->integer;
	ent->client->pers.inventory[IT_WEAPON_MACHINEGUN] = start_machinegun->integer;
	ent->client->pers.inventory[IT_WEAPON_CHAINGUN] = start_chaingun->integer;
	ent->client->pers.inventory[IT_WEAPON_GLAUNCHER] = start_grenadelauncher->integer;
	ent->client->pers.inventory[IT_WEAPON_RLAUNCHER] = start_rocketlauncher->integer;
	ent->client->pers.inventory[IT_WEAPON_HYPERBLASTER] = start_hyperblaster->integer;
	ent->client->pers.inventory[IT_WEAPON_PLASMABEAM] = start_plasmabeam->integer;   // Kyper - Lithium port - expansion weapon
	ent->client->pers.inventory[IT_WEAPON_RAILGUN] = start_railgun->integer;
	ent->client->pers.inventory[IT_WEAPON_BFG] = start_bfg->integer;
	// Kyper - Lithium port - expansion weapons
	ent->client->pers.inventory[IT_WEAPON_CHAINFIST] = start_chainfist->integer;	
	ent->client->pers.inventory[IT_WEAPON_ETF_RIFLE] = start_etfrifle->integer;
	ent->client->pers.inventory[IT_WEAPON_PROXLAUNCHER] = start_proxlauncher->integer;
	ent->client->pers.inventory[IT_WEAPON_PLASMABEAM] = start_plasmabeam->integer;
	ent->client->pers.inventory[IT_WEAPON_IONRIPPER] = start_ionripper->integer;
	ent->client->pers.inventory[IT_WEAPON_PHALANX] = start_phalanx->integer;
	ent->client->pers.inventory[IT_WEAPON_DISRUPTOR] = start_disruptor->integer;

	ent->client->pers.inventory[IT_ARMOR_JACKET] = start_armor->integer;
}

void Var_InitClientPersistant(gclient_t *client)
{
	client->pers.health = start_health->integer;
	client->pers.max_health = max_health->integer;
	client->pers.max_ammo[AMMO_BULLETS] = max_bullets->integer;
	client->pers.max_ammo[AMMO_SHELLS] = max_shells->integer;
	client->pers.max_ammo[AMMO_ROCKETS] = max_rockets->integer;
	client->pers.max_ammo[AMMO_GRENADES] = max_grenades->integer;
	client->pers.max_ammo[AMMO_CELLS] = max_cells->integer;
	client->pers.max_ammo[AMMO_SLUGS] = max_slugs->integer;
	// Kyper - Lithium port - expansion ammo
	client->pers.max_ammo[AMMO_MAGSLUG] = max_magslugs->integer;
	client->pers.max_ammo[AMMO_FLECHETTES] = max_flechettes->integer;
	client->pers.max_ammo[AMMO_DISRUPTOR] = max_disruptorrounds->integer;
	client->pers.max_ammo[AMMO_PROX] = max_prox->integer;
	client->pers.max_ammo[AMMO_TESLA] = max_tesla->integer;
	client->pers.max_ammo[AMMO_TRAP] = max_traps->integer;
}

bool Var_SpawnEntity(edict_t *ent)
{
	if (use_packs->integer && !Q_strcasecmp(ent->classname, "item_pack"))  // Kyper - Lithium port - only remove map ammo packs if using the Lithium packs
		return false;
	if (no_shotgun->integer && !Q_strcasecmp(ent->classname, "weapon_shotgun"))
		return false;
	if (no_sshotgun->integer && !Q_strcasecmp(ent->classname, "weapon_supershotgun"))
		return false;
	if (no_shotgun->integer && no_sshotgun->integer && !Q_strcasecmp(ent->classname, "ammo_shells"))
		return false;

	if (no_machinegun->integer && !Q_strcasecmp(ent->classname, "weapon_machinegun"))
		return false;
	if (no_chaingun->integer && !Q_strcasecmp(ent->classname, "weapon_chaingun"))
		return false;
	if (no_machinegun->integer && no_chaingun->integer && !Q_strcasecmp(ent->classname, "ammo_bullets"))
		return false;

	if (no_grenadelauncher->integer && !Q_strcasecmp(ent->classname, "weapon_grenadelauncher"))
		return false;
	//if (no_grenadelauncher->integer && !Q_strcasecmp(ent->classname, "ammo_grenades")) return false;   // Kyper - Lithium port - grenades can still be used on their own...

	if (no_rocketlauncher->integer && !Q_strcasecmp(ent->classname, "weapon_rocketlauncher"))
		return false;
	if (no_rocketlauncher->integer && !Q_strcasecmp(ent->classname, "ammo_rockets"))
		return false;

	if (no_hyperblaster->integer && !Q_strcasecmp(ent->classname, "weapon_hyperblaster"))
		return false;
	if (no_bfg->integer && !Q_strcasecmp(ent->classname, "weapon_bfg"))
		return false;
	//if (no_hyperblaster->integer && no_bfg->integer && !Q_strcasecmp(ent->classname, "ammo_cells")) return false;  // Kyper - Lithium port - expansion weapons use cells...

	if (no_railgun->integer && !Q_strcasecmp(ent->classname, "weapon_railgun"))
		return false;
	if (no_railgun->integer && !Q_strcasecmp(ent->classname, "ammo_slugs"))    // Kyper - Lithium port - slugs weren't removed in original for some reason
		return false;

	// Kyper - Lithium port - expansion weapons and ammo
	if (no_chainfist->integer && !Q_strcasecmp(ent->classname, "weapon_chainfist"))
		return false;

	if (no_etfrifle->integer && !Q_strcasecmp(ent->classname, "weapon_etf_rifle"))
		return false;
	if (no_etfrifle->integer && !Q_strcasecmp(ent->classname, "ammo_flechettes"))
		return false;

	if (no_proxlauncher->integer && !Q_strcasecmp(ent->classname, "weapon_proxlauncher"))
		return false;
	if (no_proxlauncher->integer && !Q_strcasecmp(ent->classname, "ammo_prox"))
		return false;

	if (no_plasmabeam->integer && !Q_strcasecmp(ent->classname, "weapon_plasmabeam"))
		return false;
	if (no_ionripper->integer && !Q_strcasecmp(ent->classname, "weapon_boomer"))
		return false;
	if (no_hyperblaster->integer && no_bfg->integer && no_plasmabeam->integer && no_ionripper->integer
		&& !Q_strcasecmp(ent->classname, "ammo_cells")) 
		return false;  // Kyper - Lithium port - hope there's no power shield on the map!

	if (no_phalanx->integer && !Q_strcasecmp(ent->classname, "weapon_phalanx"))
		return false;
	if (no_phalanx->integer && !Q_strcasecmp(ent->classname, "ammo_magslug"))
		return false;

	if (no_disruptor->integer && !Q_strcasecmp(ent->classname, "weapon_disintegrator"))
		return false;
	if (no_disruptor->integer && !Q_strcasecmp(ent->classname, "ammo_disruptor"))
		return false;

	if (no_tesla->integer && !Q_strcasecmp(ent->classname, "ammo_tesla"))
		return false;

	if (no_traps->integer && !Q_strcasecmp(ent->classname, "ammo_trap"))
		return false;

	if (no_quad->integer && !Q_strcasecmp(ent->classname, "item_quad"))
		return false;
	if (no_pent->integer && !Q_strcasecmp(ent->classname, "item_invulnerability"))
		return false;

	return true;
}