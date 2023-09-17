# Lithium Minus
Hook and rune features taken from the Quake 2 Lithium mod, made to work with the Q2 Remaster/Rerelease. Other features have been omitted, hence the name Lithium Minus / Lithium- .
I've only briefly tested single player but the hook and runes appear to work there.\
Go through the original mod's documentation for more info, including hook and rune vars/commands:

https://quake2lithium.github.io/

## Installing and using
From the Github page, in the Releases -> Latest section on the right-hand side, download `lithminus.zip`.
Go to your Quake 2 remaster directory ex.\
Steam: \<steam\>\steamapps\common\Quake 2\rerelease\
GOG: \<GOG\>\Quake II Enhanced\
Create a directory to store the binary and name it whatever you want ex. `lithminus`. Extract `lithminus.zip` here and you will see a .DLL file. Then, use one of the two methods listed below to load the mod.
### Load the mod manually
Load up Quake 2 and in console, type `game lithminus` (no quotes). Now, create a lobby and configure it as desired, and once you start the game Lithium Minus will be loaded.
### Run the config file
Get a copy of the "lithsetup_bots.cfg" file from the source code above, and place it into your rerelease\baseq2 folder. Load up Quake 2 and in console, type `exec lithsetup_bots.cfg` (no quotes). This will create a local game with the below:
* set `game lithminus`
* immediately load q2dm1 with `map q2dm1`
* load 4 bots with `bot_minClients 5`

If you see "Lithium Minus" in the bottom left then the mod has loaded. You can immediately quit the map and create your own lobby, and modify the config file for future use.

## Added variables
* g_use_hook 0/1 - Enables/disables hook (default: 1)
* g_use_runes 0/1 - Enables/disables runes (default: 1)
* g_hook_help 0/1 - Enables/disables displaying help text for binding hook (default: 1)
* g_hook_wave 0/1 - Enables/disables adding hook_toggle to wave command  (default: 1)
* g_rune_crouchdrop 0/1 - Ability to drop runes by opening Weapon Wheel and crouching (default: 1)
* g_dm_weapons_stay_fixdrop 0/1 - Fixes bug with players not dropping weapons on death when weapons stay is enabled, more info below (default: 1)

## New commands added for this remaster port
* lith_help - display text for instructions on binding hook and overview of runes
* lith_help_cvar - one-liners on all the cvars for configuring hook and runes
* hook_toggle - fires hook on button press, unfires hook on next button press

## Other items added for this remaster port
* Bots now have a [BOT] prefix in their name to help distinguish from real players
* g_hook_help - if enabled, this outputs 2 lines of text to inform players about the ability to use hook and drop runes, moving for a bit will hide the text so it doesn't get in the way
* g_hook_wave - if enabled, players can set a button to use the wave command (Input -> Multiplayer -> Wave) for hook_toggle, helpful for players not on PC/can't access the console
* g_rune_crouchdrop - if enabled, players can hold the Weapon Wheel button and crouch to drop their current rune, helpful for players not on PC/can't access the console

## Notable items that may differ from original
* Rune spawning behaviour is changed slightly - bounding box is smaller, added a check to keep runes from getting stuck
* Regen rune uses a magic number 0.625 I couldn't figure out, behaviour with default values will vary from original (but you can always tune the regen rate/cap...)

## g_dm_weapons_stay_fixdrop
The remaster changed the code for handling weapons dropping when g_dm_weapons_stay is enabled. There are more details in a Steam guide if you want to look that up, but the short of it is that the remaster behaviour differs from the original; if a player dies in the original game with weapons stay on, that player will drop their weapon provided they still have ammo for that weapon. In the remaster, this no longer happens due to the code change. I personally find this new implementation to be a bug as the remaster still has players drop hand grenades if they are holding them before death.\
g_dm_weapons_stay_fixdrop restores the original game behaviour (it basically uses the same code/logic). The only thing to note is that this needs to be turned on with g_dm_weapons_stay before the lobby/game is started, otherwise it won't take effect as it needs to be enabled to prevent the rerelease code from affecting weapons. This is on by default so you probably don't need to worry, but if you are tinkering with the values mid-game you may need to reload the game state with map \<mapname\>.

## Other/blog stuff
I honestly have no idea what I'm doing but somehow I bashed my keyboard hard enough and things started working...
