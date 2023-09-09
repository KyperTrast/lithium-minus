# Lithium Minus
Hook and rune features taken from the Quake 2 Lithium mod, made to work with the Q2 Remaster/Rerelease. Other features have been omitted, hence the name Lithium Minus / Lithium- .
Go through the original mod's documentation for more info, including hook and rune vars/commands:

https://quake2lithium.github.io/

## Global variables
* g_use_hook 0/1 - Enables/disables hook (default: 1)
* g_use_runes 0/1 - Enables/disables runes (default: 1)
* g_hook_help 0/1 - Enables/disables displaying help text for binding hook (default: 0)
* g_hook_wave 0/1 - Enables/disables adding hook_toggle to wave command  (default: 0)

## Added commands
* lith_help - display text for instructions on binding hook and overview of runes
* lith_help_cvar - one-liners on all the cvars for configuring hook and runes
* hook_toggle - fires hook on button press, unfires hook on next button press

## Notable items that may differ from original
* Added hook_toggle - can now use one button to fire/unfire hook in addition to original alias/hold method
* Rune spawning behaviour is changed slightly - bounding box is smaller, added a check to keep runes from getting stuck
* Regen rune uses a magic number 0.625 I couldn't figure out, behaviour with default values will vary from original (but you can always tune the regen rate/cap...)
* Regen doesn't prevent megahealth decay, even if you are below rune_regenmax health

\
I honestly have no idea what I'm doing but somehow I bashed my keyboard hard enough and things started working...
