///////////////////////////////////////////////////////////
// AiMain.inc
//
// This is the generic AI Main function that all AI must implement.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use os;
use npc;

include "/include/eventid";
include "AiSetup";
include "Speech";
include "Combat";
include "NonCombat";
include "Consider";
include "AiSfx";
include "Grouping";
include "Caster";
include "Looter";
include "Sounds";

///////////////////////////////////////////////////////////
// GLOBAL CODE
///////////////////////////////////////////////////////////
var mefollow 		:= 0;
var clock 			:= ReadGameClock();
var NextWander 		:= clock;
var NextNonCombat 	:= clock;
var NextSound 		:= clock;

function MainAILoop()
	SetMyAnchor();

	EnableEvents(EVID_GROUP_JOIN);
	EnableEvents(EVID_ENGAGED + EVID_DAMAGED + EVID_OPPONENT_MOVED, ai.ConsiderRange);
	EnableEvents(EVID_ENTEREDAREA, ai.ConsiderRange);
	EnableEvents(EVID_SPEECH, ai.HearDist);

	while (1)
		var ev := wait_for_event(AI_WAIT_TIME_NONCOMBAT);

		if (ev)
//			repeat
				// Check for events.
				case (ev.type)
					EVID_SPEECH:
						ProcessSpeech(ev);

					EVID_ENTEREDAREA:
						if (ConsiderCombat(ev.source))
							Fight(ev.source);
						endif

					EVID_ENGAGED:
					EVID_DAMAGED:
						SaySpeechStuff(SAYENGAGED);
						GetHelpFrom(ev.source);
						Fight(ev.source);

					EVID_OPPONENT_MOVED:
						CloseDistance(ev.source);

					EVID_PEACEMADE:
						EndFight();

					default:
						// Group events processed here...
						ProcessGroupEvent(ev);

				endcase
//			until (!(ev := wait_for_event(1))); // Process all waiting events...
		endif

		ConsumeEvents();

		// Check if we are following...
		if (mefollow and Distance(me, mefollow) > ai.FollowDist)
			MoveToward(mefollow);
		endif

		// Check if should wander or do other stuff...
		clock := ReadGameClock();
		if (NextWander < clock and ai.CanMove)
			Wander();
			NextWander := clock + ai.WanderDelay;
		endif

		// Check if I should do non combat processing.
		if (NextNonCombat < clock)
			// Do stuff while idle.
			NonCombatProcessing();
			NextNonCombat := clock + AI_NONCOMBAT_DELAY;
			Cast(me);	// Cast on myself...
			GrabLoot();	// Do some looting...
		endif

		// Check if I should make sounds.
		if (NextSound < clock)
			Sounds();
			NextSound := clock + AI_SOUND_INTERVAL;
		endif

		// Delay here if need be.
		if (ai.MoveDelay)
			sleepms(ai.MoveDelay);
		endif
	endwhile
endfunction

///////////////////////////////////////////////////////////
// Purpose: Sets my anchor point.
// 			Anchor point settings are prioritized like so:
// 				1) ai structure
// 				2) NpcTemplate
// 				3) Default setting.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function SetMyAnchor()
	// Set my anchor point.
	var dstart := ai.dstart;
	if (!dstart)
		dstart := mydesc.dstart;
		if (!dstart)
			dstart := DEF_DSTART;
		endif
	endif

	var psub := ai.psub;
	if (!psub)
		psub := mydesc.psub;
		if (!psub)
			psub := DEF_PSUB;
		endif
	endif

	SetAnchor(me.x, me.y, dstart, psub);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Closes the distance.
// Params:  opponent		Ref to mobile.
// Returns: 1		We are within reach.
//			0		Need to get closer.
///////////////////////////////////////////////////////////
function CloseDistance(byref opponent)
	if (!ai.CanMove)
		return 0;
	endif

	if (mydesc.missileweapon and opponent)
		// I'm an archer, keep the distance!
		// NOTE: Archers alwasy run away!
		if (Distance(me, opponent) < ai.KeepDist)
			RunAwayFrom(opponent);
			return 0;
		else // Distance is good, fire away till we need to move again.
			return 0;
		endif
	endif

	case Distance(me, opponent)
        1:              // the most likely, so first
        0:
        	return 1;

        default:
        	MoveToward(opponent);
        	return 0;
    endcase
endfunction

///////////////////////////////////////////////////////////
// Purpose: Makes me follow the leader.
// Params:  leader		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function Follow(byref leader)
	mefollow := leader;
	return;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Stops the NPC from following.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function StopFollowing()
	mefollow := 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Moves me towards something.
// Params:  mobile		Ref to a mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function MoveToward(byref mobile)
	if (ai.Run)
		RunToward(mobile);
	else
		WalkToward(mobile);
	endif

	if (ai.MoveDelay)
		sleepms(ai.MoveDelay);
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Moves me away from mobile.
// Params:  mobile		Ref to a mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function MoveAwayFrom(byref mobile)
	if (ai.Run)
		RunAwayFrom(mobile);
	else
		WalkAwayFrom(mobile);
	endif

	if (ai.MoveDelay)
		sleepms(ai.MoveDelay);
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Consumes remaining events.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function ConsumeEvents()
	var ev;
	repeat until (!(ev := wait_for_event(0)));
endfunction