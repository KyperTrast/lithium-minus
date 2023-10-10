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
/* Kyper - Lithium port
* 
* AKA Lithium Minus as it only uses the hook and runes. Although the other features are nice, as the website's description puts it,
* "Lithium II is well known for it's red-laser style off-hand grappling hook and runes."
* 
* Maybe I'll look at adding the other stuff, but for now I think there's lots of fun to be had in remaster lobbies with the hook and runes
* ...is what I said when I started porting the mod to remaster, now I've added almost everything that isn't admin/menu/hud related!
* 
* Derived from Lithium - lithium.h
*/
#pragma once

#define RUNE_RESIST 1
#define	RUNE_STRENGTH 2
#define RUNE_HASTE 4
#define RUNE_REGEN 8
#define RUNE_VAMPIRE 16

#define NUM_RUNES 5

enum
{
	// Kyper - Lithium port
	// Adding new configstring values past MAX_CONFIGSTRINGS seems to crash with an index error
	// Not sure if this is the proper way to do things...
	CS_LITHIUM = (CS_ITEMS + MAX_ITEMS - 20),
	CS_RUNE1,
	CS_RUNE2,
	CS_RUNE3,
	CS_RUNE4,
	CS_RUNE5,
	CS_OBSERVING,
	CS_CHASING,
	CS_SAFETY,
	CS_HUDRUNE0,
	CS_HUDRUNE1,
	CS_HUDRUNE2,
	CS_HUDRUNE3,
	CS_HUDRUNE4,
	CS_HUDRUNE5,
	CS_AMMOPACK,     // Kyper - added for remaster
	CS_LITHIUM_END
};

static_assert(CS_LITHIUM_END < CS_PLAYERSKINS, "spilling into CS_PLAYERSKINS");

// Kyper - Lithium port
// use_safety/safety_time moved out from original implementation in lithium.c
extern cvar_t *use_safety;
extern cvar_t *safety_time;

extern cvar_t *use_packs;

// weapon vars
extern cvar_t *blaster_damage;
extern cvar_t *blaster_speed;
extern cvar_t *shotgun_damage;
extern cvar_t *shotgun_count;
extern cvar_t *shotgun_hspread;
extern cvar_t *shotgun_vspread;
extern cvar_t *sshotgun_damage;
extern cvar_t *sshotgun_count;
extern cvar_t *sshotgun_hspread;
extern cvar_t *sshotgun_vspread;
extern cvar_t *machinegun_damage;
extern cvar_t *machinegun_hspread;
extern cvar_t *machinegun_vspread;
extern cvar_t *chaingun_damage;
extern cvar_t *chaingun_damage_sp;
extern cvar_t *chaingun_hspread;
extern cvar_t *chaingun_vspread;
extern cvar_t *grenade_damage;
extern cvar_t *grenade_radius;
extern cvar_t *grenadelauncher_damage;
extern cvar_t *grenadelauncher_radius;
extern cvar_t *rocket_damage;
extern cvar_t *rocket_damage2;
extern cvar_t *rocket_rdamage;
extern cvar_t *rocket_radius;
extern cvar_t *rocket_speed;
extern cvar_t *rocket_knockback;
extern cvar_t *hyperblaster_damage;
extern cvar_t *hyperblaster_damage_sp;
extern cvar_t *hyperblaster_speed;
extern cvar_t *railgun_damage;
extern cvar_t *railgun_damage_sp;
extern cvar_t *bfg_damage;
extern cvar_t *bfg_damage_sp;
extern cvar_t *bfg_radius;
extern cvar_t *bfg_speed;
extern cvar_t *bfg_raydamage;
extern cvar_t *bfg_raydamage_sp;
extern cvar_t *bfg_balldamage;
extern cvar_t *bfg_ballradius;
// Kyper - Lithium port - expansion weapons
extern cvar_t *chainfist_damage;
extern cvar_t *chainfist_damage_sp;
extern cvar_t *chainfist_range;
extern cvar_t *etfrifle_damage;
extern cvar_t *etfrifle_speed;
extern cvar_t *proxlauncher_damage;
extern cvar_t *proxlauncher_radius;
extern cvar_t *ionripper_damage;
extern cvar_t *ionripper_damage_sp;
extern cvar_t *ionripper_speed;
extern cvar_t *plasmabeam_damage;
extern cvar_t *plasmabeam_kick;
extern cvar_t *plasmabeam_kick_sp;
extern cvar_t *phalanx_damage;
extern cvar_t *phalanx_damage2;
extern cvar_t *phalanx_rdamage;
extern cvar_t *phalanx_radius;
extern cvar_t *phalanx_rdamage2;
extern cvar_t *phalanx_radius2;
extern cvar_t *phalanx_speed;
extern cvar_t *disruptor_damage;
extern cvar_t *disruptor_damage_sp;
extern cvar_t *disruptor_speed;
extern cvar_t *disruptor_fixticks;
extern cvar_t *tesla_damagerate;
extern cvar_t *trap_triggerradius;

extern cvar_t *knockback_adjust;
extern cvar_t *knockback_self;
extern cvar_t *fall_damagemod;


// l_hook.cpp
void Hook_InitGame(void);
void Hook_PlayerDie(edict_t *attacker, edict_t *self);
void Hook_Think(edict_t *self);
edict_t* Hook_Start(edict_t *ent);
void Hook_Reset(edict_t *rhook);
bool Hook_Check(edict_t *self);
void Hook_Service(edict_t *self);
void Hook_Track(edict_t *self);
void Hook_Touch(edict_t *self, edict_t *other, const trace_t &tr, bool other_touching_self);
void Hook_Fire(edict_t *owner, vec3_t start, vec3_t forward);
void Weapon_Hook_Fire(edict_t *ent);
void Weapon_Hook(edict_t *ent);

// l_rune.cpp
void Rune_InitGame(void);
void Rune_InitLevel(void);
void Rune_RunFrame(void);
void Rune_Reset(void);
edict_t *Rune_Spawn(vec3_t origin, int type);
void Rune_Touch(edict_t *self, edict_t *other, const trace_t &tr, bool other_touching_self);
void Rune_Remove(edict_t *self);
void Rune_Drop(edict_t *player);
int Rune_AdjustDamage(edict_t *targ, edict_t *attacker, int damage);
void Rune_TDamage(edict_t *targ, edict_t *attacker, int damage);
void Rune_ClientFrame(edict_t *player);
int Rune_HasHaste(edict_t *player);
int Rune_HasRegen(edict_t *player);
void Rune_RemoveAll(void);
void Rune_FireSound(edict_t *ent);
bool Rune_Give(edict_t *ent, const char *name);
void Rune_UpdateHUD(edict_t* player);

// l_var.cpp
void Var_InitGame(void);
void Var_PutClientInServer(edict_t *ent);
void Var_InitClientPersistant(gclient_t *client);
bool Var_SpawnEntity(edict_t *ent);

// l_pack.cpp
void Pack_InitGame(void);
void Pack_MaybeSpawn(vec3_t origin);
void Pack_Touch(edict_t *self, edict_t *other, const trace_t &tr, bool other_touching_self);
void Pack_Remove(edict_t *self);
void Pack_UpdateHUD(edict_t *player);

// lm_help.cpp
void Help_Lithium(edict_t *ent, const char *htext);
void Help_LithHUDText(edict_t *player);