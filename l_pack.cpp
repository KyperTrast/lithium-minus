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

#include "g_local.h"

cvar_t *use_packs;

cvar_t *pack_spawn;
cvar_t *pack_life;

cvar_t *pack_health;
cvar_t *pack_armor;
cvar_t *pack_bullets;
cvar_t *pack_shells;
cvar_t *pack_rockets;
cvar_t *pack_grenades;
cvar_t *pack_cells;
cvar_t *pack_slugs;
// Kyper - Lithium port - expansion ammo
cvar_t *pack_magslugs;
cvar_t *pack_flechettes;
cvar_t *pack_disruptorrounds;
cvar_t *pack_prox;
cvar_t *pack_tesla;
cvar_t *pack_traps;

void Pack_InitGame(void)
{
	use_packs = gi.cvar("use_packs", "0", CVAR_NOFLAGS);

	pack_spawn = gi.cvar("pack_spawn", "0.03", CVAR_NOFLAGS);
	pack_life = gi.cvar("pack_life", "25", CVAR_NOFLAGS);

	pack_health = gi.cvar("pack_health", "100", CVAR_NOFLAGS);
	pack_armor = gi.cvar("pack_armor", "200", CVAR_NOFLAGS);
	pack_bullets = gi.cvar("pack_bullets", "300", CVAR_NOFLAGS);
	pack_shells = gi.cvar("pack_shells", "200", CVAR_NOFLAGS);
	pack_rockets = gi.cvar("pack_rockets", "100", CVAR_NOFLAGS);
	pack_grenades = gi.cvar("pack_grenades", "100", CVAR_NOFLAGS);
	pack_cells = gi.cvar("pack_cells", "300", CVAR_NOFLAGS);
	pack_slugs = gi.cvar("pack_slugs", "100", CVAR_NOFLAGS);
	// Kyper - Lithium port - expansion ammo
	pack_magslugs = gi.cvar("pack_magslugs", "100", CVAR_NOFLAGS);
	pack_flechettes = gi.cvar("pack_flechettes", "300", CVAR_NOFLAGS);
	pack_disruptorrounds = gi.cvar("pack_disruptorrounds", "30", CVAR_NOFLAGS);
	pack_prox = gi.cvar("pack_prox", "50", CVAR_NOFLAGS);
	pack_tesla = gi.cvar("pack_tesla", "5", CVAR_NOFLAGS);
	pack_traps = gi.cvar("pack_traps", "5", CVAR_NOFLAGS);
}

//===============================
// packs

void Pack_MaybeSpawn(vec3_t origin) {
	edict_t *pack;

	if (!use_packs->integer)
		return;

	if (frandom() > pack_spawn->value)
		return;

	pack = G_Spawn();
	if (!pack)
		return;

	pack->s.origin = origin;
	gi.setmodel(pack, "models/items/pack/tris.md2");
	pack->velocity[0] = -200 + (frandom() * 400);
	pack->velocity[1] = -200 + (frandom() * 400);
	pack->velocity[2] = 150 + (frandom() * 150);
	pack->movetype = MOVETYPE_BOUNCE;
	pack->solid = SOLID_TRIGGER;
	pack->clipmask = MASK_SOLID;
	pack->s.frame = 0;
	pack->flags = FL_NONE;
	pack->classname = "pack";
	pack->s.effects = EF_ROTATE;
	pack->s.renderfx = RF_GLOW | RF_NO_LOD | RF_IR_VISIBLE;

	pack->spawnflags = SPAWNFLAG_ITEM_DROPPED;

	pack->mins = vec3_t{ -16, -16, -4};   // Kyper - Lithium port - original 12 min/24 max on Z axis made it sink into the floor...
	pack->maxs = vec3_t{ 16, 16, 8 };

	pack->item = FindItem("pack");

	pack->touch = Pack_Touch;
	pack->think = Pack_Remove;
	pack->nextthink = level.time + gtime_t::from_sec(pack_life->integer);

	gi.linkentity(pack);
}

bool Pickup_Pack(edict_t *ent, edict_t *other);
TOUCH(Pack_Touch) (edict_t *self, edict_t *other, const trace_t &tr, bool other_touching_self) -> void
{
	gclient_t *client;

	if (strcmp(other->classname, "player"))
		return; // only players can have packs

	if (other->health < 1)
		return;

	if (level.intermissiontime)
		return;

	if (!other->client->has_pack)
	{
		client = other->client;

		other->max_health = max(other->max_health, pack_health->integer);
		//other->max_armor = max(other->max_armor, pack_armor->integer);
		client->pers.max_health = max(client->pers.max_health, pack_health->integer);
		client->pers.max_ammo[AMMO_BULLETS] = max(client->pers.max_ammo[AMMO_BULLETS], (int16_t)pack_bullets->integer);
		client->pers.max_ammo[AMMO_SHELLS] = max(client->pers.max_ammo[AMMO_SHELLS], (int16_t)pack_shells->integer);
		client->pers.max_ammo[AMMO_ROCKETS] = max(client->pers.max_ammo[AMMO_ROCKETS], (int16_t)pack_rockets->integer);
		client->pers.max_ammo[AMMO_GRENADES] = max(client->pers.max_ammo[AMMO_GRENADES], (int16_t)pack_grenades->integer);
		client->pers.max_ammo[AMMO_CELLS] = max(client->pers.max_ammo[AMMO_CELLS], (int16_t)pack_cells->integer);
		client->pers.max_ammo[AMMO_SLUGS] = max(client->pers.max_ammo[AMMO_SLUGS], (int16_t)pack_slugs->integer);
		// Kyper - Lithium port - expansion ammo
		client->pers.max_ammo[AMMO_MAGSLUG] = max(client->pers.max_ammo[AMMO_MAGSLUG], (int16_t)pack_magslugs->integer);
		client->pers.max_ammo[AMMO_FLECHETTES] = max(client->pers.max_ammo[AMMO_FLECHETTES], (int16_t)pack_flechettes->integer);
		client->pers.max_ammo[AMMO_DISRUPTOR] = max(client->pers.max_ammo[AMMO_DISRUPTOR], (int16_t)pack_disruptorrounds->integer);
		client->pers.max_ammo[AMMO_PROX] = max(client->pers.max_ammo[AMMO_PROX], (int16_t)pack_prox->integer);
		client->pers.max_ammo[AMMO_TESLA] = max(client->pers.max_ammo[AMMO_TESLA], (int16_t)pack_tesla->integer);
		client->pers.max_ammo[AMMO_TRAP] = max(client->pers.max_ammo[AMMO_TRAP], (int16_t)pack_traps->integer);

		client->has_pack = true;
	}

	Pickup_Pack(self, other);

	Pack_UpdateHUD(other);

	G_FreeEdict(self);
}

THINK(Pack_Remove) (edict_t *self) -> void
{
	G_FreeEdict(self);
}

// Kyper - Lithium port
// original didn't update HUD for Ammo Packs, let's do it for the remaster!
void Pack_UpdateHUD(edict_t *player)
{
	gi.configstring(CS_AMMOPACK, "$item_ammo_pack");
	player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex("i_pack");
	player->client->ps.stats[STAT_PICKUP_STRING] = CS_AMMOPACK;
	player->client->pickup_msg_time = level.time + 3_sec;
	gi.sound(player, CHAN_AUTO, gi.soundindex("items/pkup.wav"), 1, ATTN_NORM, 0);
}