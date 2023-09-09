/* Kyper - Lithium port
* 
* AKA Lithium Minus as it only uses the hook and runes. Although the other features are nice, as the website's description puts it,
* "Lithium II is well known for it's red-laser style off-hand grappling hook and runes."
* 
* Maybe I'll look at adding the other stuff, but for now I think there's lots of fun to be had in remaster lobbies with the hook and runes
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
	CS_LITHIUM_END
};

static_assert(CS_LITHIUM_END < CS_PLAYERSKINS, "spilling into CS_PLAYERSKINS");

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

void Help_Lithium(edict_t *ent, const char *htext);
void Help_LithHUDText(edict_t *player);