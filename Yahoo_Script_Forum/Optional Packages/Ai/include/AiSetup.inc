///////////////////////////////////////////////////////////
// AiSetup.inc
//
// Setup include for NPC AI scripts.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use uo;
use npc;
use cfgfile;

include "/include/randname";
include "/include/vetement";

///////////////////////////////////////////////////////////
// CONFIGURABLE AI SETTINGS
///////////////////////////////////////////////////////////
// This is the setup structure.  It can be changed in the AI script to
// change the AI defaults.
var ai := struct;

// General distance and speech.
ai.+HearDist		:= 4;	// How far does it hear?
ai.+ConsiderRange 	:= 8;	// How far before it notices something approach/leave?
ai.+NameRespond		:= 1; 	// Does my name have to be said for me to respond?

// Movement.
ai.+Run				:= 0;	// BOOL When moving in combat, do I run or walk?
ai.+CanMove			:= 1;	// Can this NPC move, or is it rooted in one place?
ai.+MoveDelay		:= 0;	// Delay (milliseconds) in movement.  Some monsters are slow...
ai.+WanderDelay		:= 0;	// How often does it wander?
ai.+ChaseDist  		:= 25;	// How far can before I give up chase or stop running?
ai.+KeepDist		:= 4;	// For npcs with missileweapon.

// Combat.
ai.+MaxCombatLoops 	:= 100; // How long before I get tired of combat?
ai.+FleePoint		:= 10;	// Percent HP left before I flee?
ai.+MakePeace		:= 1;	// BOOL Determines if I should fight when opponent stopped.

// Consider.  These affect only 'evil' critters, as nonevil critters never attack first.
ai.+AttackNpc		:= 0;	// Do I attack other NPCs?  Only matters for 'alignment evil' NPCs.
ai.+AttackStaff		:= 0;	// Does it attack staff?  Only matters for 'alignment evil' NPCs.
ai.+Bravery			:= 0;	// How much togher is he (STR+DEX+INT) than me in percent?
							// I will attack if he is this much tougher.
							// -1 is insane. I attack anything, no matter its toughness.
							// 0 means that I only attack those equal or lesser in stats.
							// 40 means I will attack up to things up to 40% tougher than me.

// Spell Casting.
ai.+CastFrequency 	:= 5;	// How many seconds before I can test for casting again?
ai.+SpeakWords		:= 1;	// Do I speak the power words of spells?
ai.+WhenToHeal		:= 50;	// At what percent of HP do I cast heal at (myself and group members).

// Looting.
ai.+GrabLoot		:= 0;	// Do I grab loot on the ground?
ai.+LootCorpses		:= 0;	// Do I loot corpses I find?
ai.+LootFrequency	:= 5;	// How often (seconds) do I look for things to loot?
ai.+EquipLoot		:= 1;	// Do I equip the loot I find?

// Grouping.
ai.+FollowDist		:= 4;	// What distance should I keep between me and my leader?

// Misc.
ai.+psub			:= 10;	// How far can I range freely from anchor.
ai.+dstart			:= 20;  // Pct chance per step past dstart that Wander() fails.

///////////////////////////////////////////////////////////
// AI CORE CONFIGURATION CONSTS
///////////////////////////////////////////////////////////
// Defaults if not specified in NpcTemplate.
const DEF_DSTART			:= 10;	// Default dtart.
const DEF_PSUB				:= 20;	// Default psub.
const DEF_AMMO				:= 30; 	// Amount of ammo to create if none specified.

// Setup.
const AI_SETUP_PRIORITY		:= 100;	// Setup priority for dressing them.

// Combat.
const AI_MAX_COMBAT_LOOPS 	:= 100; // If fight takes that long, just run away.
const AI_WAIT_TIME_COMBAT	:= 1;	// How long to wait for events in combat.
const AI_COMBAT_PRIORITY 	:= 50; 	// Script priority in combat.
const AI_SWITCH_OPPONENT_CHANCE := 6; // 1 in ? chance of switching opponents in combat.

// Movement.
const AI_WANDER_DELAY		:= 5;	// What is the delay on wandering around?

// NonCombat.
const AI_NONCOMBAT_DELAY 	:= 10;	// How often do I do noncombat stuff?
const AI_WAIT_TIME_NONCOMBAT := 5;	// How long to wait for events in noncombat.
const AI_NONCOMBAT_PRIORITY	:= 5;  	// Scrip priority in noncombat.

// Looting.
const AI_LOOT_DELAY			:= 2;	// How long does it take me to pick something up.

// Sleep related.
const AI_SLEEP_RANGE		:= 10;	// How close must a PC come before I wake up?
const AI_SLEEP_TIME			:= 60*5;// How long to wait (seconds) for an event to wake me up for?
const AI_SLEEP_INTERVAL		:= 60;// How long between checks for sleep time?

// Sounds.
const AI_SOUND_INTERVAL		:= 60;	// How often do I make random sounds?

///////////////////////////////////////////////////////////
// OTHER CONSTS
///////////////////////////////////////////////////////////
const UOBJ_MOUNT	:= 0xf021;

///////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////
var me 			:= self();
var npccfg 		:= ReadConfigFile(":*:npcdesc");
var mydesc 		:= npccfg[me.npctemplate];

///////////////////////////////////////////////////////////
// GLOBAL CODE - Generic for all AIs.
///////////////////////////////////////////////////////////
set_priority(AI_SETUP_PRIORITY);
InitialAISetup();
SetAiParameters();
InitialEquipment();
set_priority(AI_NONCOMBAT_PRIORITY);

///////////////////////////////////////////////////////////
// Purpose: Does the initial setup of the NPC.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function InitialAISetup()
	// Set up my gender if human model.
	if ((me.graphic = 400) or (me.graphic = 401))
		me.graphic := 400 + RandomInt(1);
		if(me.graphic = 401)
			me.gender := 1;
		endif
	endif

	// Set my name.
	if (me.name["<random>"])
		me.name := RandomName(me);
	endif

	// Set my colour randomly if I have a range specified.
	if (mydesc.colorrange)
		var parms := SplitWords(npccfg[me.npctemplate].colorrange);
		me.color := RandomInt(cint(parms[2]) - cint(parms[1])) + cint(parms[1]);
	endif

	// Dress me.
	if (mydesc.equip)
		Habille(me, mydesc.equip);
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Gives me my initial equipment.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function InitialEquipment()
	// Gimme a backpack if I need one.
	if (!me.backpack)
		var bpack := CreateItemAtLocation(me.x, me.y, me.z, "Backpack", 1);
		EquipItem(me, bpack);
	endif

	// Create my ammo if I use ranged weapons.
	if (mydesc.missileweapon)
		EquipFromTemplate(me, mydesc.missileweapon);
		var amount := mydesc.ammoamount;
		if (!amount)
			amount := DEF_AMMO;
		endif
		CreateItemInBackpack(me, mydesc.ammotype, amount);
	endif

	// Create my mount if I have one, and mount it.
	if (mydesc.mount and npccfg[mydesc.mount].graphic)
		var mount := CreateItemAtLocation(0, 0, 0, UOBJ_MOUNT, 1);
		mount.graphic := npccfg[mydesc.mount].graphic;
		mount.color := npccfg[mydesc.mount].color;
		EquipItem(me, mount);
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Sets the initial AI parameters from the Template.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function SetAiParameters()
	if (mydesc.flee_point)
		ai.FleePoint := mydesc.flee_point;
	endif

	if (mydesc.immobile)
		ai.CanMove := 0;
	endif

	if (mydesc.dstart)
		ai.dstart := mydesc.dstart;
	endif

	if (mydesc.psub)
		ai.psub := mydesc.psub;
	endif

	if (mydesc.move_delay)
		ai.MoveDelay := mydesc.move_delay;
	endif
endfunction

