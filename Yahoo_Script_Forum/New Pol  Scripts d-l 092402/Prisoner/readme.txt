Name: Prisoner AI Script
Version: 1.0
Released: 1st June 2001

Created by GM Scull
scull@wn.com.au
ICQ #15041892

File will prolly be hosted at POL-Scriptforum List (http://groups.yahoo.com/group/pol-scriptforum)

-Changes in v1.0
  Added prisonreward.cfg for rewards
  Fixed Teleporters and recaling, prisoners can now follow players through any gate or systemteleporter
  Fixed up items
  Took out virtue
  Rewrote command handeling
  Rewrote detect close monster code 
  Rewrote master code	
  Optimised 99% of the functions
  Took out some useless stuff like telling a prisoner to stop

-Changes in v0.8
  Fixed prisoners not giving items, again
  Various optimisations
  Fixed lag problems (caused by prisoners checking for monsters)
  Fixed some long sentences.
  Got rid of useless cprops

-Changes in v0.7
  Got rid of some useless code
  Prisoners giving out items now works correctly
  Prisoners now have beards and hats

-Changes in v0.6
  Players now get 1-5 virtue when they rescue a prisoner
  Fixed prisoners saying help after they get rescued
  Fixed up a few other small things.

-Released v0.5


-Info-

This is an AI script for a prisoner. The prisoner can be rescued by players taking the NPC into a town. The prisoner works sorta like a tamed animal.
Put prisoners in prison cells for da best effect =P like Wrong lvl2 is a good spot.

Back yer shard up b4 ya use this AI...
If ya make any modifications, can ya email me =)

-Instalation-
Put it in yer scripts/ai dir, and make an NPC template as below.
Put prisonreward.cfg file in your config directroy

- Stuff that can be easily changed -

SAVIORGOLD: determines the amount of gold a player gets when teh prisoner is rescued.
RANDOM_SAVIORGOLD: is the max random amount that is given ontop of SAVIORGOLD.
MONSTERAVOID: determines the radius a prisoner must be away from a monster b4 it can still walk. (0 to disable)
GIVES_ITEM: This determines the chance of a player gettin a random item as a reward. (eg 1/GIVES_ITEM chance)
DONT_WANTER_TO_MUCH: Dont wander from inital spot.

 

-Suggested Entries-

* Equipt.cfg *

Equipment Prisoner
{
   Equip 0x152e all   // short pants, brown
   Equip 0x170F brown   // shoes, brown 
   Equip 0x203c hairlist     // long hair, grey
}

* NPCDesc.cfg *

NpcTemplate  prisoner
{
    Name                <random> the Prisoner
    script              prisoner

    ObjType             0x190
    Color               33784
    TrueColor           33784
    Gender              0
    STR                 50
    INT                 40
    DEX                 90
    HITS                70
    MANA                0
    STAM                90
    
    Tactics             40
    Wrestling           60

    AttackSpeed         20
    AttackDamage        3d5
    AttackSkillId       Wrestling
    AR                  4
    guardignore         1
    dstart              10
    alignment           good
    lootgroup		3
    CProp equipt        sPrisoner
}


-Notes-
The script is pretty self explanatory, so feel free to change it ya want.

Visit mah webpage: http://www.wn.com.au/toadhall/damon/
And I do know how to spell Skull for all them grammaticly correct ppl out there.
If ive missed anythin, email me.

Q3A Owns.

-Bugs-
 None Known





