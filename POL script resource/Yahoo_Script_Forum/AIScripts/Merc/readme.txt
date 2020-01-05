Name: Mercenary NPC
Version: 0.6a
Released: 1st June 2001

Created by GM Scull
  scull@wn.com.au
  ICQ #15041892

File will prolly be hosted at POL-Scriptforum List (http://groups.yahoo.com/group/pol-scriptforum)
 Use this script at ur own risk, aint my fault if it screws something.
 Read this very long file b4 ya use da mercs.
 ICQ me if ya want anything added/removed/customised or whatever, or if ya find a bug


-Version History-

0.6a
 Forgot to add latest soruce in last release =P
 Fixed a typo
0.6
 Optimised a heap of stuff
 Moved dress funtions to misc dir for smaller script
 Fixed a few text commands not working
0.5 - Non beta Release
 Fixed some looting issues
 Optimised a bit
 Fixed MAX_MERCS bug, turns out the yes/no dialog that was causing the problem =P
 Added INVUL_WHILE_NOT_HIRED
 Changed NPC template
0.4e
 New talk code
 Fixed stupid loot bug
0.4c
 Mercs now equip properly with the distro scripts (i dident realise they were naked b4 =P)
 Can now compile under distro scripts
 Minor tweaks to merc fighting
 Added autoloot cmd
 Mercs now use archery buttes properly (like they get their arrows that they have used from the butte)
0.4c
 Fixed mercs not drinking potions
 Added ThrowPot command, this will get the merc to throw an explode pot if it has one
 Fixed all the 'all' cmd stuff
 mercs can now hear 'all heal'
0.4b
 Fixed some misc stuff
 Mercs can now be spawned with a horse
 Fixed some walkhome stuff
0.4a
 Fixes some more fighting stuff
0.4
 Fixed speech problem
 Fixed Bug with mercs not retreating from battle if master is too far away
 Fixed a heap of ev stuff
 Optimised a bit
0.3
 Initial release


-Stuff yet to be done-
 * Res ability (Players generally want to res mercs, it takes lotsa effort to get these fellas stats up)
 * Spellcasting (mmm)
 * Moodsetter (aggressive/defence)
 * Skillcap (not statcap)
 * Make the file a bit smaller, I dunno, but i rekon 64kb is a bit to much for an ai.
 * A few textcmds, so players can find and manage their mercs
 * Mercs should re-equip if they are fired
 * change help book to be compatible with distro book package

-Stuff yet to be fixed-
 - Mercs can carve corpses when they have no knife
 - format helpbook
 - Cant wash bandages in ocean


-Info-
This script is basicly a full on modification of the warrior.src script, thx whoever wrote it =)
This NPC is a mercenary. Players can basicly hire and fire em.
Mercs are able to gain stats sorta like a normal player, so they can be trained till they hit the statcap. They can equipt anything and can be set up just like a players character. Kinda like human pets. Sofar, These Mercs cannot be exploited by players (IE hire em, get em to drop their stuff, release em).


- Varibles meant to be changed depending on your shard-

HIRE_GP: Base price of merc to be hired (weapons and armour are added to this val) (2000) 
MAX_FRIENDS: Max ppl on a mercs friend list (5)
MAX_ENEMYS: Max ppl on a mercs enemy list (3)
MAX_MERCS_PER_PLAYER: Max alive mercs that can be hired per player (3)
INVUL_WHILE_NOT_HIRED: If enabled, mercs are invunrable whenever they do not have a master (0)
STATCAP: Ur shards statcap, mercs will not go above this (250)
CREATE_HELPBOOK: Creates a helpbook in mercs backpack (U must be running Shinigami's Book-Package v1.01) (0)
BUILD: Used by me to determine a mercs build numba.


- Big ol list of stuff mercs can do -
 Mercs have a big list of commands, they r listed below.
 Mercs use all default potions (explode, heal, cure, str, etc)
 Mercs can use training dummys (just tell em to attack and they go at it for about 5 mins b4 gettin bored)
 Mercs can use archery ranges
 Mercs Gain skills and stats depending on master and opponent
 Mercs can loot and carve stuff on command or automaticly
 Mercs will not attack their master and will run if their master attacks them
 Mercs can wash their bandages

 Mercs can come equipted with a book o commands, though u need this book package to use it.
 ** Requires Shinigami's Book-Package v1.01 to be installed **

 When spawned, mercs randomly equip themselves, and modify their price to go with their skill/equip.
 Dont use Spawnnet to spawn mercs, I dun think it would be overly compatible. not sure really

-Commands-
  Note: Using 'all' infront of some commands will command all mercs within 12 squares. (ie, All attack)
        Using 'me' at the end of some commands will make mercs do something to u. (ie, Bob heal me)        
 	If 'all' isent used, mercs names must be used infront of commands. (ie, Bob attack)
	some commands dont requite the all or name to be used. (ie RUN)
	
 * GM commands
	version:  merc sez current build of script its using
 * Player commands
	Hire: Hires unhired merc
	skill: Merc reports current skill status

	kill/attack/fight: Merc will attack selected NPC or player.
	stop: Merc will stop whatever its doin
	heal: Merc will use bandages to heal selected NPC or player
        throwpot: Merc throws an explosion potion if it has one
	help/ahh: mercs scan for and fight anything near you
	run: Merc runs like hell, nomatter what

	guard: Merc will stay within 9 squares and defend a selected NPC or player.
	camp: Merc will set up camp in current spot*
	come: Merc will run towards you.
	follow: Merc will follow selected NPC or player

	drop: Merc will drop all its stuff on da ground
	undress: merc puts all equipted items in its backpack
	dismount: Merc will get off what its riding
	ride/mount: Merc will ride selected NPC
	rearm: Merc will switch currently equipted weapons with weapons in backpack


	report: merc reports current ar, and lists ppl on lists
	freind: Adds selected Player to freindly list**
	enemy: Adds selected Player to enemy list***
	removeall: removes everyone from list
	remove: removes typed in player from list
	quote: Lets u type in a sentence that the merc will recite when a player comes nearby
	battlecry: Lets u type in Mercs Battlecry

	loot: Merc autoloots nearest corpse
	autoloot: merc automaticly loots stuff when he kills it
	carve: Merc carves up nearest corpse
	wash: Merc washes bandages in nearest water(not ocean)

	release: Fires merc

	Double click on a merc to open its backpack

 * Mercs camp when master goes offline. When a merc is camped, it will walk back to its camping spot if it moves 	away. Good for defending houses and stuff
 ** People on a mercs freind list get complimented when they walk near the camped merc
 ** People on a mercs enemy list get attacked when they walk near the camped merc



-Instalation-
Put it in yer scripts/ai dir, and make an NPC template as below.
Copy mercdress.ecl to the scripts/misc dir


-Suggested Entries-

* NPCDesc.cfg *

NpcTemplate merc
{
    Name        <random>
    script      hireling

    ObjType     0x190
    Color       33784
    TrueColor   33784
    Gender      0
    STR         60
    INT         60
    DEX         60
    HITS        60
    MANA        0
    STAM        100

    guardignore 1
    alignment   good
}


-Notes-
Do not use .tame on mercs, it screws around with their little brains.

Visit mah webpage: http://www.wn.com.au/toadhall/damon/
And I do know how to spell Skull for all them grammaticly correct ppl out there.
If ive missed anythin, email me.

Q3A Owns CS.


