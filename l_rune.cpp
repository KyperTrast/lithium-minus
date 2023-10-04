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

cvar_t *use_runes;
cvar_t *rune_minbound;
cvar_t *rune_life;
cvar_t *rune_perplayer;
cvar_t *rune_spawnpersecond;
cvar_t *rune_min;
cvar_t *rune_max;

cvar_t *rune_resist;
cvar_t *rune_strength;
cvar_t *rune_regen;
cvar_t *rune_regenmax;
cvar_t *rune_regencap;
cvar_t *rune_vampire;
cvar_t *rune_vampiremax;

cvar_t *rune_flags;

cvar_t *rune_strength_sound;
cvar_t *rune_resist_sound;
cvar_t *rune_haste_sound;
cvar_t *rune_regen_sound;
cvar_t *rune_vampire_sound;

int rune_count[NUM_RUNES] = { 0, 0, 0, 0, 0 };
int rune_total = 0;
int time_counter = 0;      // Kyper - Lithium port - replaces "counter" in Rune_RunFrame

static int Rune_IsInSolid(edict_t *ent); //QW//
static int Rune_IsInSolidStopped(edict_t *ent);

void UseRunesChanged(void)
{
	if (!use_runes->value)	
		Rune_RemoveAll();
	//	StatusBar_UpdateAll();
}

void Rune_InitGame(void)
{
	use_runes = gi.cvar("use_runes", "1", CVAR_NOFLAGS);
	//use_runes->func = UseRunesChanged;    // Kyper - Lithium port - no storing functions in cvars...

	rune_minbound = gi.cvar("rune_minbound", "-4", CVAR_NOFLAGS);

	rune_flags = gi.cvar("rune_flags", "31", CVAR_NOFLAGS);
	rune_perplayer = gi.cvar("rune_perplayer", "0.6", CVAR_NOFLAGS);
	rune_spawnpersecond = gi.cvar("rune_spawnpersecond", "1", CVAR_NOFLAGS);
	rune_life = gi.cvar("rune_life", "20", CVAR_NOFLAGS);
	rune_min = gi.cvar("rune_min", "3", CVAR_NOFLAGS);
	rune_max = gi.cvar("rune_max", "12", CVAR_NOFLAGS);
	rune_resist = gi.cvar("rune_resist", "2.0", CVAR_NOFLAGS);
	rune_strength = gi.cvar("rune_strength", "2.0", CVAR_NOFLAGS);
	rune_regen = gi.cvar("rune_regen", "0.25", CVAR_NOFLAGS);
	rune_regenmax = gi.cvar("rune_regenmax", "200", CVAR_NOFLAGS);
	rune_regencap = gi.cvar("rune_regencap", "3.5", CVAR_NOFLAGS);
	rune_vampire = gi.cvar("rune_vampire", "0.5", CVAR_NOFLAGS);
	rune_vampiremax = gi.cvar("rune_vampiremax", "200", CVAR_NOFLAGS);

	rune_resist_sound = gi.cvar("rune_resist_sound", "world/force2.wav", CVAR_NOFLAGS);
	rune_strength_sound = gi.cvar("rune_strength_sound", "items/damage3.wav", CVAR_NOFLAGS);
	rune_haste_sound = gi.cvar("rune_haste_sound", "world/x_light.wav", CVAR_NOFLAGS);
	rune_regen_sound = gi.cvar("rune_regen_sound", "items/s_health.wav", CVAR_NOFLAGS);
	rune_vampire_sound = gi.cvar("rune_vampire_sound", "makron/pain2.wav", CVAR_NOFLAGS);	
}

void Rune_InitLevel(void)
{
	Rune_Reset();
	time_counter = 0;    // Kyper - Lithium port - moved "counter" from Rune_RunFrame to this var

	gi.soundindex(rune_resist_sound->string);
	gi.soundindex(rune_strength_sound->string);
	gi.soundindex(rune_haste_sound->string);
	gi.soundindex(rune_regen_sound->string);
	gi.soundindex(rune_vampire_sound->string);

	// Kyper - Lithium port - loading configstrings in PreInitGame() seems to crash...
	gi.configstring(CS_RUNE1, "Resist Rune");
	gi.configstring(CS_RUNE2, "Strength Rune");
	gi.configstring(CS_RUNE3, "Haste Rune");
	gi.configstring(CS_RUNE4, "Regen Rune");
	gi.configstring(CS_RUNE5, "Vampire Rune");
	gi.configstring(CS_OBSERVING, "Lithium Minus\nlith_help for info");
	gi.configstring(CS_SAFETY, "Safety");
	gi.configstring(CS_HUDRUNE0, "None");
	gi.configstring(CS_HUDRUNE1, "Resist");
	gi.configstring(CS_HUDRUNE2, "Strength");
	gi.configstring(CS_HUDRUNE3, "Haste");
	gi.configstring(CS_HUDRUNE4, "Regen");
	gi.configstring(CS_HUDRUNE5, "Vampire");
}

void Rune_Reset(void)
{
	int i;
	for (i = 0; i < NUM_RUNES; i++)
		rune_count[i] = 0;
	rune_total = 0;
}

void Rune_RunFrame(void)
{
	edict_t *ent;
	int i, j, lowest, x;
	int playercount = 0;

	// only check once per second
	if (level.time.seconds<int>() <= time_counter)
		return;

	time_counter = level.time.seconds<int>();

	// Kyper - Lithium port
	// normally, use_runes is an lvar that has a pointer to function UseRunesChanged
	// cvars don't have that, so we'll replicate this with a global cvar and call UseRunesChanged() ourselves as needed
	// having said that, should probably just replace use_runes with g_use_runes
	gi.cvar_set("use_runes", g_use_runes->string);

	// does a rune need to be spawned?
	if (!use_runes->value)
	{
		if (rune_total)
			UseRunesChanged();

		return;
	}

	if (!rune_flags->value)
		return;
	if (rune_flags->value >= 1 << NUM_RUNES)
		return;

	// Kyper - Lithium port - there's a CountPlayers() function but it's supposedly meant for coop...
	for (auto p : active_players())
	{
		if (p->client->resp.spectator)
			continue;
		playercount++;
	}

	for (x = 0; x < rune_spawnpersecond->value; x++)
	{
		if (rune_total >= rune_max->value)
			return;
		if (rune_total >= rune_min->value && rune_total >= (int)((float)playercount * rune_perplayer->value))
			return;

		// find an entity to sprout from
		for (;;)
		{
			ent = &g_edicts[(int)(frandom() * globals.num_edicts)];

			if (!ent->inuse)
				continue;
			if (ent->client)
				continue;
			break;
		}

		// find which rune there are fewest of
		lowest = -1;
		for (i = 0; i < NUM_RUNES; i++)
			if ((int)rune_flags->value & 1 << i && (lowest == -1 || rune_count[i] < lowest))
				lowest = rune_count[i];
		
		i = j = rand() % NUM_RUNES;

		do
		{
			if ((lowest == -1 || rune_count[i] == lowest) && (int)rune_flags->value & 1 << i)
			{
				rune_count[i]++;
				rune_total++;
				Rune_Spawn(ent->s.origin, 1 << i);
				break;
			}

			i++;
			if (i == NUM_RUNES)
				i = 0;
		} while (i != j);
	}
}

edict_t *Rune_Spawn(vec3_t origin, int type)
{
	edict_t *rune;

	// Kyper - Lithium port - shrunk the bounding boxes by 10 (5 on each axis except for min z) to keep runes from sticking into walls
	// If you hug a wall and drop a rune with the original values, they would get stuck...
	vec3_t	mins = { -15, -15, rune_minbound->value};
	vec3_t	maxs = { 15, 15, rune_minbound->value + 35 };

	if (!use_runes->value)
		return NULL;
	
	rune = G_Spawn();
	if (!rune)
		return NULL;

	rune->s.origin = origin;
	gi.setmodel(rune, "models/items/keys/pyramid/tris.md2");
	rune->velocity[0] = -200 + (frandom() * 400);
	rune->velocity[1] = -200 + (frandom() * 400);
	rune->velocity[2] = 150 + (frandom() * 150);
	rune->movetype = MOVETYPE_BOUNCE;
	rune->solid = SOLID_TRIGGER;
	rune->clipmask = MASK_SOLID;
	rune->s.frame = 0;
	rune->flags = FL_NONE;
	rune->classname = "rune";
	rune->s.effects = EF_ROTATE | EF_COLOR_SHELL;

	rune->mins = mins;
	rune->maxs = maxs;
	
	if (type & RUNE_RESIST)
		rune->s.renderfx = RF_SHELL_BLUE;
	else if (type & RUNE_STRENGTH)
		rune->s.renderfx = RF_SHELL_RED;
	else if (type & RUNE_HASTE)
	{
		rune->s.renderfx = RF_SHELL_DOUBLE;
//		if (qver >= 3.19f)
//			rune->s.renderfx = RF_SHELL_DOUBLE;
//		else
//			rune->s.renderfx = RF_SHELL_RED | RF_SHELL_GREEN;
	}
	else if (type & RUNE_REGEN)
		rune->s.renderfx = RF_SHELL_GREEN;
	else if (type & RUNE_VAMPIRE)
		rune->s.renderfx = RF_SHELL_RED | RF_SHELL_BLUE;

	rune->touch = Rune_Touch;
	rune->think = Rune_Remove;
	rune->nextthink = level.time + gtime_t::from_sec(rune_life->value);
	
	rune->rune = type;

	gi.linkentity(rune);

	//	gi.dprintf("Rune 0x%x type %i spawned, time %.1f\n", rune, rune->rune, level.time);	

		//QW// if rune is in solid, remove it on next think
	
	//if (Rune_IsInSolid(rune))
	//	rune->nextthink = level.time + 0.1f;
	
	// Kyper - Lithium port
	// In the original, if runes spawn inside walls they would somehow clip through and be pushed out
	// I can't seem to figure out if the changes in g_phys.c are doing this so I've implemented an alternate method
	// sometimes a rune can pass the Rune_IsInSolid check as it only checks the origin point
	// but the rune's bounding box can still get stuck
	// first try to move it with SV_Physics_Toss - this will set velocity to 0 if it's really stuck
	// then grant the rune temporary MOVETYPE_PUSH to give it a chance to escape
	if (Rune_IsInSolidStopped(rune))
	{
		rune->velocity[0] = -200 + (frandom() * 400);
		rune->velocity[1] = -200 + (frandom() * 400);
		rune->velocity[2] = 150 + (frandom() * 150);
		rune->nextthink = level.time + 100_ms;
		rune->movetype = MOVETYPE_PUSH;
	}

	return rune;
}

TOUCH(Rune_Touch) (edict_t *self, edict_t *other, const trace_t &tr, bool other_touching_self) -> void
{
	int i;

	// this can be NULL somehow, if +set deathmatch 1 and no map specified
	if (!other->classname)
		return;

	// only players can have runes
	if (strcmp(other->classname, "player"))
		return;

	if (other->health < 1)
		return;

	if (level.intermissiontime)
		return;

	// don't pick up a rune the player just dropped
	if (self == other->client->drop_rune && other->client->drop_rune_time > level.time)
		return;

	// prevent player from touching a rune TOO much, if they already have one
	if (other->rune)
	{
		if (self == other->client->last_rune && other->client->last_rune_time > level.time)
			return;

		other->client->last_rune = self;
		other->client->last_rune_time = level.time + 3_sec;
		return;
	}

	other->rune = self->rune;
	other->client->regen_remainder = 0;	

	Rune_UpdateHUD(other);  // Kyper - Lithium port - moved to function shared with Rune_Give

	//LNet_Rune(other, other->rune);    // Kyper - Lithium Port - must've been cool back then...

	G_FreeEdict(self);
}

THINK(Rune_Remove) (edict_t *self) -> void
{
	// Kyper - Lithium port
	// MOVETYPE_PUSH was granted in Rune_Spawn if it was either stuck or initial velocity became 0 after a single physics call
	if (self->movetype != MOVETYPE_BOUNCE)
	{
		self->movetype = MOVETYPE_BOUNCE;

		if (!Rune_IsInSolid(self))
		{
			self->nextthink = level.time + gtime_t::from_sec(rune_life->value);
			return;
		}
	}
	int i;
	
	for (i = 0; i < NUM_RUNES; i++)
	{
		if (self->rune & 1 << i)
		{
			rune_count[i]--;
			rune_total--;
		}
	}
	//	gi.dprintf("Rune 0x%x type %i removed, time %.1f\n", self, self->rune, level.time);
	G_FreeEdict(self);
}

void Rune_Drop(edict_t *player)
{
	edict_t *rune;

	if (!player->rune)
		return;

	rune = Rune_Spawn(player->s.origin, player->rune);

	player->client->drop_rune = rune;
	player->client->drop_rune_time = level.time + 2_sec;

	player->rune = 0;

	//LNet_Rune(player, player->rune);    Kyper - Lithium port
}

int Rune_AdjustDamage(edict_t *targ, edict_t *attacker, int damage) {
	if (targ->rune & RUNE_RESIST)
		damage /= rune_resist->value;
	if (attacker->rune & RUNE_STRENGTH)
		damage *= rune_strength->value;
	return damage;
}

void body_die(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, const vec3_t &point, const mod_t &mod);

void Rune_TDamage(edict_t *targ, edict_t *attacker, int damage)
{
	if (targ == attacker || !(targ->client || targ->die == body_die))
		return;

	if (level.time > targ->last_sound_time)
	{
		if (targ->rune & RUNE_RESIST && !targ->deadflag)
			gi.sound(targ, CHAN_ITEM, gi.soundindex(rune_resist_sound->string), 1, ATTN_NORM, 0);
		if (attacker->rune & RUNE_VAMPIRE)
			gi.sound(targ, CHAN_ITEM, gi.soundindex(rune_vampire_sound->string), 1, ATTN_NORM, 0);
		targ->last_sound_time = level.time;
	}

	if (attacker->rune & RUNE_VAMPIRE)
	{
		int add, vdamage;

		if (attacker->health > rune_vampiremax->value)
			return;

		vdamage = damage;
		if (targ->health < -40)
			vdamage -= -40 - targ->health;

		add = (int)((float)vdamage * rune_vampire->value + 0.5);

		if (add > 0) {
			attacker->health += add;
			if (attacker->health > rune_vampiremax->value)
				attacker->health = rune_vampiremax->value;
		}
	}
}

void Rune_ClientFrame(edict_t *player)
{
	if (level.intermissiontime)
		return;

	Help_LithHUDText(player);		// Kyper - Lithium port - borrowing the MOTD / delayed HUD idea for help text
	
	// take away a rune that has been turned off
	if (player->rune && !(player->rune & (int)rune_flags->value)) {
		player->rune = 0;		
		gi.LocClient_Print(player, PRINT_HIGH, "Admin has disabled the rune you have.\n");
	}

	// Kyper - Lithium port - maybe rework the calculations so that it's time based?
	// Rune_ClientFrame/ClientBeginServerFrame appears to be called every 25 ms
	// no idea what 0.625 represents, I've divided it by 4 due to the 10 -> 40 tick rate
	if (player->rune & RUNE_REGEN && player->health < rune_regenmax->value) 
	{		
		float health = player->health + player->client->regen_remainder;
		float newhealth = rune_regenmax->value / health;
		if (newhealth > rune_regencap->value)
			newhealth = rune_regencap->value;
		//newhealth *= rune_regen->value * 0.625;
		newhealth *= rune_regen->value * .15625;
		health += newhealth;
		player->health = (int)health;
		player->client->regen_remainder = health - (float)player->health;

		if (level.time > player->client->regen_sound_time)   // Kyper - Lithium port - replaced "framenum % 25" with stored value
		{
			player->client->regen_sound_time = level.time + 2_sec;
			gi.sound(player, CHAN_AUTO, gi.soundindex(rune_regen_sound->string), 1, ATTN_NORM, 0);
		}
	}
}

//QW//
static int Rune_IsInSolid(edict_t *ent) {
	//if (gi.pointcontents(ent->s.origin) & CONTENTS_SOLID)
	//	gi.dprintf("Rune 0x%x type %i is in solid, time %.1f\n", ent, ent->rune, level.time);
	return gi.pointcontents(ent->s.origin) & CONTENTS_SOLID;
}
//QW//

// Kyper - Lithium port - additional check for velocity if origin isn't in a solid object but bounding box prevents movement
static int Rune_IsInSolidStopped(edict_t *ent)
{
	void SV_Physics_Toss(edict_t *ent);
	SV_Physics_Toss(ent);

	return (gi.pointcontents(ent->s.origin) & CONTENTS_SOLID) || ent->velocity == vec3_origin;
}

int Rune_HasHaste(edict_t *player)
{
	return player->rune & RUNE_HASTE;
}

int Rune_HasRegen(edict_t *player)
{
	return player->rune & RUNE_REGEN;
}

void Rune_RemoveAll(void)
{
	edict_t* ent;

	while ((ent = G_FindByString<&edict_t::classname>(nullptr, "rune")))
		G_FreeEdict(ent);

	// Kyper - Lithium port - could use Rune_Remove() above, but let's be absolutely sure...
	Rune_Reset();

	//ent = NULL;	
	//while ((ent = G_Find(ent, FOFS(classname), "player")))

	//while ((ent = G_FindByString<&edict_t::classname>(nullptr, "player")))
	//	ent->rune = 0;

	// Kyper - Lithium port
	// Attempting to use remaster equivalent of remove runes from players crashes
	// I have no idea what it does, so I'll just use an alternate check...
	for (auto player : active_players())
	{
		player->rune = 0;
	}
}

void Rune_FireSound(edict_t *ent)
{
	if (ent->rune == RUNE_STRENGTH)
		gi.sound(ent, CHAN_ITEM, gi.soundindex(rune_strength_sound->string), 1, ATTN_NORM, 0);
	if (ent->rune == RUNE_HASTE)
		gi.sound(ent, CHAN_ITEM, gi.soundindex(rune_haste_sound->string), 1, ATTN_NORM, 0);
}

bool Rune_Give(edict_t *ent, const char *name)
{
	if (!Q_strcasecmp(name, "resist"))
		ent->rune = RUNE_RESIST;
	else if (!Q_strcasecmp(name, "strength"))
		ent->rune = RUNE_STRENGTH;
	else if (!Q_strcasecmp(name, "haste"))
		ent->rune = RUNE_HASTE;
	else if (!Q_strcasecmp(name, "regen"))
		ent->rune = RUNE_REGEN;
	else if (!Q_strcasecmp(name, "vampire"))
		ent->rune = RUNE_VAMPIRE;
	else
		return false;

	// Kyper - Lithium port - update HUD with the rune we were given
	Rune_UpdateHUD(ent);

	return true;
}

// Kyper - Lithium port
// Text macros with % got ripped out of the remaster, so this function is unused...
void CTFSay_Team_Rune(edict_t* who, char* buf, unsigned int buflen)
{
	if (who->rune & RUNE_RESIST)
		Q_strlcpy(buf, "the Resist rune", buflen);
	else if (who->rune & RUNE_STRENGTH)
		Q_strlcpy(buf, "the Strength rune", buflen);
	else if (who->rune & RUNE_HASTE)
		Q_strlcpy(buf, "the Haste rune", buflen);
	else if (who->rune & RUNE_REGEN)
		Q_strlcpy(buf, "the Regen rune", buflen);
	else if (who->rune & RUNE_VAMPIRE)
		Q_strlcpy(buf, "the Vampire rune", buflen);
	else
		Q_strlcpy(buf, "no rune", buflen);
}

// Kyper - Lithium port
// Used by Rune_Give and Rune_Touch
void Rune_UpdateHUD(edict_t* player)
{
	player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex("k_pyramid");
	for (int i = 0; i < NUM_RUNES; i++)
	{
		if (player->rune & 1 << i)
		{
			player->client->ps.stats[STAT_PICKUP_STRING] = CS_RUNE1 + i;
			player->client->ps.stats[STAT_RUNE_TEXT] = CS_RUNE1 + i;
			player->client->ps.stats[STAT_RUNE_PIC] = gi.imageindex("k_pyramid");
		}
	}

	player->client->pickup_msg_time = level.time + 3_sec;
	gi.sound(player, CHAN_AUTO, gi.soundindex("items/pkup.wav"), 1, ATTN_NORM, 0);
}