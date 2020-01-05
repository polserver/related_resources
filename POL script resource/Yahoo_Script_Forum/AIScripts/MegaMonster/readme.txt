////////////////
// MegaMonster
////////////////

Now with Expand_Stats(animalNPC) u're able to use stats up to 32977. This fix is
only a fix because it's impossible to hold stat values on server shutdown.
That's why u've to call the function not only on creation...

U can use this function for every NPC type. I've included a sample for drakes etc.

Stat ranges:
  1 <= HITS <= STR <= 32977
  1 <= MANA <= INT <= 32977
  1 <= STAM <= DEX <= 32977

Shini