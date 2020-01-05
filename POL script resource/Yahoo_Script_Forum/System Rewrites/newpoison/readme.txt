NewPoisons readme.txt

Installation:

put newpoisons.inc and convert.inc in your main include directory. Put everything else into a new package.

Newpoisons is a system to implement poisons, diseases, and curses. It allows for continuation after death, login and logout, and unending curses (that is, curses that don't end after a period of time). It is config-file driven.

When a character logs in, it starts a "poisonwatcher" process that is incharge of maintaining all poisons (for this package, "poisons", "curses", and "diseases" can be used interchangeably). It starts and stops individual poison packages as needed, and handles all curing and healing.

Poisonwatcher runs as long as a character is online. Other scripts send it events to let it know which poison scripts to run. It kills those scripts when they've timed out.

You can have several different types of poisons, and there's no limits on what they can do. From the poisonwatcher's point of view, all they need is a script, a timeout, and a virulence. 
	script: the script to start (String)
	timeout: the time, in seconds, that the script should run
	virulence: a measure of how powerful the poison is, per second. Curing spells and potions will subtract from this virulence.
	
	Example: a lesser poison has a virulence of 1 per second. Someone is poisoned for 30 seconds worth of lesser poison, for a total virulence of 30. They drink a cure potion that heals 15 points of virulence. That would reduce that poison timeout by 15. Their remaining virulence is 15.
	
	A moment later, the same character is hit with 20 seconds of (virulence 2) regular poison. That increases their total virulence by 40, to 55. They then drink a potion that cures 25 virulence. That stops all of the level 1 poison, and removes 10 virulence (or 5 seconds) of the other poison. The end result? He's left with 15 seconds to go on the second poison.
	
	poison resistance: poison resistance works can work different ways. First of all, the newpoisons.cfg file can specify a ResistType of A or P. Type A (all) means that the poison, if resisted, will be completely resisted -- and it won't start the script at all. Type P, for partial, means that the poison's virulence will be reduced by poison skill as a percentage.Also, individual poison scripts can check the poisonresist skill on each damage loop. 
	
	Cure Skill: if there is a CureSkill property set in the config file, any skillchecks will be done against that skillID. If not, then it'll use whatever you specify as DEFAULT_CURE_SKILL at the top of poisonwatcher.src.	
	
	Death: most poisons will cease on death. If the config file has a ContinueOnDeath property set to anything but zero, it will continue while they're dead. This is to allow for curses and the like. Please note that ContinueOnDeath poisons will still stop when an NPC dies.
	
	Non-curable poisons: any poison can be non-curable by normal means. To make a noncurable poison, put "NoCure 1" in the config file.  If this happens, then other scripts will be responsible for curing the poison.
	
	Unending poisons: If newpoisons.cfg has a NoEnd 1 property in it, then the poison will never time out on its own. This, combined with NoCure 1 and ContinueOnDeath 1, can make for a  good, long-lasting curse.
	
	Cure Scripts: You can specify a CureScript entry in the config file. This will be a script to call instead of killing the poison script itself. You can use this to do temporary stat modifying scripts. The poison listener will pass the victim, pid, virulence,and timeout of the script when it kills it.
	
	KillScripts: when a player logs out, we need to stop the poison script. If you specify a killscript, it will call this instead of killing the poison itself. Passes pid and victim.
	
	Type: If no type is entered, the entry is thought to be a poison. Type "C" is curse, and type "D" is disease. The primary difference between them is the spell/rite required to cure them. 
	
	
To create your own poison, you write a simple script that implements the poison functionality, then put an entry in newpoisons.cfg. You can then use the addpoison() function in newpoisons.inc to infect someone. The following is a simple example:

use uo;
use os;
program demopoison(parms)
local who := parms[1];

while (1)
	applyrawdamage(who, 1);
	sleep(1);
endwhile
endprogram

The following poisons/diseases/curses are included in this package:

mildtoxin, mediumtoxin, greaterpoison, deadlypoison: regular OSI-style poisons
magekiller: a poison that drains mana along with health
paralyze: a paralysis poison (shows curescripts)
squelch: a silence poison
ragecurse: sends all mobs near the afflicted an EVID_ENGAGED. dangerous!
common cold: a communicable disease. If you come close to an infected player, you'll catch it
lycanthropy: turns you into a werewolf at night (looks for a lightlevel global cprop)
impcurse: (requires an npc template called "tormenter" using the "tormenter" ai that's included): causes a really annoying imp to follow you around and insult you.
