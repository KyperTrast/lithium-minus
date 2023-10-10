# Lithium Minus
A port of the Lithium mod, made to work with the Quake 2 Remaster/Rerelease. A number of server/map administration and hud/GUI features have been omitted, hence the name Lithium Minus / Lithium- .

Originally just taking the hook and rune features from Lithium, this mod now has weapon/ammo spawn starting values, max ammo/health capacity, and weapon properties settings such as damage and projectile speed. Settings have also been added for the Ground Zero/Reckoning expansion weapons. I've only briefly tested single player but the settings appear to work there.

Go through the config-remaster.txt file to see the settings that you can configure. You can use stock.cfg as a base for your config and enable/alter only the settings that you want.

You can also go through the original mod's documentation for more info:
https://quake2lithium.github.io/

## Installing and using the mod
From the Github page, in the Releases -> Latest section on the right-hand side, download `lithminus.zip`.
Go to your Quake 2 remaster directory ex.\
Steam: \<steam\>\steamapps\common\Quake 2\rerelease\
GOG: \<GOG\>\Quake II Enhanced\
Create a directory to store the binary and name it `lithminus`. Extract `lithminus.zip` here and you will see a .DLL file. Then, use one of the two methods listed below to load the mod.
### Load the mod manually
Load up Quake 2 and then press the tilde key (~) to open the console. In here, type `game lithminus` (no quotes). Now, create a lobby and configure it as desired, and once you start the game Lithium Minus will be loaded.
### Run the config file
Get a copy of the "lithsetup_bots.cfg" file from the source code above, and place it into your rerelease\baseq2 folder. Load up Quake 2 and then press the tilde key (~) to open the console. In here, type `exec lithsetup_bots.cfg` (no quotes). This will create a local game with the below:
* set `game lithminus`
* immediately load q2dm1 with `map q2dm1`
* load 4 bots with `bot_minClients 5`

If you see "Lithium Minus" in the bottom left then the mod has loaded. You can immediately quit the map and create your own lobby, and modify the config file for future use.

## Using the hook and runes
You can use the original hold button down method or the new toggle method. Run one of the below in console (tilde key ~):\
Hold button (change mouse2 to desired key): `alias +hook hook ; alias -hook unhook ; bind mouse2 +hook`\
Toggle (change mouse2 to desired key): `bind mouse2 hook_toggle`\
Alternatively, if g_hook_wave is enabled you can use the Escape menu to map the Wave key: Input -> Multiplayer section -> Wave

Runes spawn randomly on the map, touch one to pick it up. Your held rune is displayed in the bottom right corner. Drop a rune by binding a key to drop_rune ex. (change x to desired key): `bind x drop_rune`. Alternatively, if g_rune_crouchdrop is enabled, you can open your Weapon Wheel and Crouch to drop your rune.

## Added variables
* g_use_hook 0/1 - Enables/disables hook (default: 1)
* g_use_runes 0/1 - Enables/disables runes (default: 1)
* g_hook_help 0/1 - Enables/disables displaying help text for binding hook (default: 1)
* g_hook_wave 0/1 - Enables/disables adding hook_toggle to wave command  (default: 1)
* g_rune_crouchdrop 0/1 - Ability to drop runes by opening Weapon Wheel and crouching (default: 1)

## New commands added for this remaster port
* hook_toggle - fires hook on button press, unfires hook on next button press
* lith_help - display text for instructions on binding hook and overview of runes
* lith_help_cvar - one-liners on all the cvars for configuring hook/rune/misc settings
* lith_help_cvarpack - one-liners of Ammo Pack cvars
* lith_help_cvarstartmax - one-liners of cvars for starting items/max capacity of ammo and health
* lith_help_cvarbaseweapon - one-liners of base weapon property cvars
* lith_help_cvarexpweapon - one-liners of expansion weapon property cvars
* lith_help_cvardisable - one-liners on cvars to disable weapon/power-up spawns

## Other items added for this remaster port
* Bots now have a [BOT] prefix in their name to help distinguish from real players
* g_hook_help - if enabled, this outputs 2 lines of text to inform players about the ability to use hook and drop runes, moving for a bit will hide the text so it doesn't get in the way
* g_hook_wave - if enabled, players can set a button to use the wave command (Input -> Multiplayer -> Wave) for hook_toggle, helpful for players not on PC/can't access the console
* g_rune_crouchdrop - if enabled, players can hold the Weapon Wheel button and crouch to drop their current rune, helpful for players not on PC/can't access the console

## Notable items that may differ from original
* Rune spawning behaviour is changed slightly - bounding box is smaller, added a check to keep runes from getting stuck
* Safety still shows health icon
* Added separate \*_damage_sp cvars for weapons that have varying damage between multiplayer and single player (ex. railgun)
* omitted start_weapon and start_blaster - start_weapon can give you a weapon without adding to inventory, start_blaster 1 can crash the game in remaster
* not implemented (yet...?): armor customization, max_armor cap, armor_shard value, small_health value, mega_rot

## Other/blog stuff
I honestly have no idea what I'm doing but somehow I bashed my keyboard hard enough and things started working...
