TownRaid Script, GM Scull - v0.7c
ICQ# 15041892
Email: Scull@wn.com.au
Last update: July 14th
Raid any location with hundreds of monsters, v0.7c (now with gumps, player rewards and multiple raids)


thx to Dundee for regionspawner - the base code of this package
thx go to S!th for helpin out wif the gump

If u use this script, back everything up.
if u got any ideas/suggestions/bugs/raidquests that can be addded to this package, plz icq or email me

I havent tested this package on a shard with a large playerbase, so if you do, tell me how it goes =)
The raiddefenders are pretty weak, they are mainly just for looks

If a raid goes haywire, use 'Wipe data' in the raid menu, that will wipe all global data to do with raids and 
stop all raids in one go

Note:
Some options like provoke and raidwars are still in testing, and may not work

- Usage -
.raid - brings up a menu with a heap of info on current raids
.raidtown - brings up options to raid a town


- Installation -
 Extract this zip to /pkg/opt/
 Copy the contents of Deathmod.src into scripts/misc/death.src & compile (Do this if ur upgrading from v0.6 or less)
 Copy contents of townraid/ai into scripts/ai directory
 Copy raid.ecl and raidtown.ecl into scripts/txtcmd/seers dir
 Type .unloadall
 And away ya go
 
 To compile stuff, u need to 
 copy raidconsts.inc into scripts/include
 copy ai/mainloopraider.inc into scripts/ai/main
 copy ai/raiderfight.inc & raidcombatevent into scripts/ai/combat


 If you wanna use the RaidDefenders:
 -Add to equip.cfg:
 Equipment RaidDefender
 {
    Armor NoseHelm
    Armor RingMailTunic
    Armor RingMailGloves
    Equip 0x1539 brown    // long pants
    Equip 0x1711        // thigh boots
    Armor PlatemailArms
    Armor Platemailgorget
    Armor KiteShield
    Weapon LongSword
 }

  -Add to NPCdesc.cfg:
  NpcTemplate  raiddefender
  {
    Name                <random>
    script              raiddefendpcs
    ObjType             0x190
    Color               33784
    TrueColor           33784
    Gender              0
    STR                 90
    INT                 50
    DEX                 80
    HITS                90
    MANA                70
    STAM                90
    Tactics             80
    Swordsmanship       70
    Parry		60
    MagicResistance     180
    AttackSpeed         25
    AttackDamage        3d6
    AttackSkillId       Swordsmanship
    AttackHitSound      0x23D
    AttackMissSound     0x239
    AR                  15
    guardignore         1
    alignment           good
    CProp Equipt        sRaidDefender
    cprop guardkill	i1
  }


- Version History -

v0.7c
 Fixed a reward bug where the players were gettin the amount of gold left calced b4 the endguys died.
 Optimised AI cprop code
 Cleaned up a heap of code
 Changed the global props a bit
 More customisable strings in config.cfg
 Raider type now stated in raid gump
 Cleaned up startraid gump
 Added Provoke mode, monster will only attack players if they are provoked or attacked first
 Added MonsterWar mode, monsters will attack opposing raid monsters (only if provoke mode is off)(doesent work)
 Fixed bug where while a raid was stoping, newly started raids would go all weird

v0.7b
 Fixed bug with monsters not marking players

v0.7a
 Temporary fix to reward system

v0.7 (Note, u will need to change death.src again)
 Multiple raids now happenin
 Added refreshable townraid gump, no more txtcmds =)
 Added raid menu, heaps less spam
 Added a reward system, now if a player attacks a raider, the raider marks him with a cprop.
     At the end of the raid, if the player has the cprop, he gets a share of the remaining $$$
 Added more player orientated messages.
 Playerfailmessage works now
 I prolly shouldent write so much shit in this readme.

v0.6
 No longer in Testing
 Fixed DeathBug, now raiders can be be nuked/killed in large numbers
 Added CritterHealer template
 Added more CFG entries
 Moved Checkcfg to its own script
 Fixed a few small cfg reading bugs
 Fixed .stopraid not working if townraid was waiting for monsters to die
 Fixed gold not being reported after a .stopraid had been issued
 Fixed Defender/raidarcher ai
 Found a bug in distro with npc mounts staying alive when sending them to the jail to die, this kinda needs to be fixed
 AI now smashes summoned walls properly

v0.5
 Added some more cfg entries, try northvesperbank =)
 Fixed a really stupid bug with teh amount of spawning monsters
 Toned down all the cfg entrys, they were a little to difficult and ongoing
 Slowed down monsters, now configurable in mainloopraider.inc (SLEEP_TIME)
 Added txtcmd parm - the raid can now stop if all the gold is taken
 Fixed Monsters not attacking ppl much
 Monsters can now knock down and Disspell walls
 Added const RandomSpawns, randomly spawns monsters from group untill total is reached 
 Added SpawnChance per spawn factor to groups cfg, determins the chance of an npc spawning 
  (note this is backwards, 0 - definate spawn/10 - no chance)
 Added makeraider cmd (not tested)

v0.4
 Readded spawndelay
 Optimised AI some more
 Added yoinkammount
 Got rid Ai`s event full console spamming on .stopraid
 Ai now attack players alot more on there way to the gold
 Added basic cfg waypoints for raiders
 Added covefort template, now u can get a horde of orcs walking all the way from their fort
 Added cfgfile checking, turn it off for faster startup time if everything works ok
 Better AI pathfinding
 AI can open doors now

v0.3
 Difficulty now in its own cfg
 Rewrote alot of the main spawning code
 Added PlayerEndMessage in cfg
 Added RaidDefendPCs Ai - weak defender (set in locations.cfg)
 Ai rarly fills event cue up when running towards target
 Ai nolonger loots gold if they have the cprop NoLoot
 Fixed a few AI related bugs

v0.2
 Rewrote AI to use inc files
 2 new ai types - spellcasting & archer raiders
 Moved goldpile to Difficulty in cfg
 Moved the density from the txtcmd to the spawndelay in the cfg
 Added PlayerMessage in cfg
 Added cfg gfx to goldpiles
 Added some more cfg entries & tweaked existing
 Fixed a few typos
 Optimised some stuff

v0.1
 Initial release


- Stuff planned for the next release -
 Inteligent monsters and defenders
 New reward code
 Make the end part of the raid a different script, so when a raid is stoped, the spawner script is killed

- Stuff Yet to be done -
 regroup waypoint (monsters wait a bit untill they gruop up, then
 charge dialog!
 New TownRun scenerio, this is where the monsters run through a town and if 25% of em make it, the players 'lose'
 RaidMaster, evil dude who is 'master' to all monsters, so they all go red, this dude could also be killed
 PlayerRankings needs cleaning up
 make it so if a player is too far away from chest, he donesent get a reward 

- Bugs -
 When 2 raids have the same goal, 2 chests get put ontop of each other
 Blue Raider NPCS stay blue when attacking
 When Provoke mode is on, monster wars dont work