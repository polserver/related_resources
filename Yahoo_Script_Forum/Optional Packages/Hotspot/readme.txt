Hotspots!

Brian Docherty (brian@pcsys.demon.co.uk)

Hotspots are co-ordinates in the game where a predetermined event will occur.
I expect most scripters already have a similar system on their shards already.
Events inlcude, Heals, Cures, Lightning strikes, Summoning of creatures, etc.
It works really nice in graveyards, walk over a grave and skeles or a liche
appears!

The scripts are rather like those used for the system teleporters.
The 'hotspots.inc' file has all of the hotspots hard coded, hence no cfg file.

If you examine the file you will see at the top the hotspots which I have put
on my shard.  The syntax goes as follows;

{x, y, z,   "action",   "type",   amount},


X, y, z, = Obviously co-ordinates for the hotspot

"action" = One of ("firefield", "poisfield", "enerfield", "parafield",
           "stonewall", "earthquake", "lightstrk", "invisible", "clumsy",
           "feeblemind", "weaken", "agility", "cunning", "strength", "harm",
           "heal", "lightning", "poison", "summon", or "random")

"type" = Used when Action is set to 'summon' and should contain the npctemplate
         in quotes.  ie. "skeleton"
         Also used for the fields to specify direction of field compared to
         the hotspot, 'north', 'south', etc and use 'all' to surround the
         spot with the specified field.

"amount" = Number of npcs to summon (Max 8), or number of seconds that a field
           should stay in place.


Other notes:

If the action is set to "random", one of ten event will happen each time.
They are "poison", "lightning", "heal", "clumsy", "feeblemind", "weaken",
 "agility", "cunning", "strength", or "harm".

The action "lightstrk" has two functions.  Firstly if under type you specify "in",
all PCs & NPCs within the range you specifiy in 'Amount' will be hit.
Alternatively if you specify "out" as the type everything between the range set
and 15 will be hit. ie. The centre will be safe.

Currently, once a hotspot has been activated, it will not work for 3 minues.
If you want to change list, the line is commented in hotspot.src.

Hotspot 'spell' damage is calculated the same way as the std spells work, on 
the magery skills/int of the pc which triggers the hotspot.


To Install:
1) Copy hotspots.inc & abs.inc to the scripts\include folder and make the changes
   you want to the hotspots.
2) Copy the hotspot.src file to scripts\items.
3) If you have changed your start.src file, just added the 2 lines as shown
   in my file, or just overwrite with the attached version.

4) Insert the following into your \config\itemdesc.cfg file.

# System Hotspot
Item 0x6202
{
    Name            systemhotspot
    Graphic         1
    WalkOnScript    hotspot
    Movable         0
    Invisible       1
    SaveOnExit      0
# A dungeon teleporter should have these custom props:
# (set by the creationscript)
#   CProp DestX     i0
#   CProp DestY     i0
#   CProp DestZ     i0
}

5) Recompile start.src and hotspot.src and restart POL.


Lastly, I'm sure the code isn't that pretty, compared to many coders out there,
but wtf I'm trying!

Think i've covered everything.  Please let me know of any problems, enhancements
that I could add.  Happy hotspoting.


