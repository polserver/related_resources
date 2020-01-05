///////////////////////////////////////////////////////////
// Combat.inc
//
// Main combat processing.  DO NOT CUSTOMIZE HERE!!!
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use os;

///////////////////////////////////////////////////////////
// Purpose: Main fight function.
// Params:  opponent		Ref to mobile.
///////////////////////////////////////////////////////////
function Fight(byref opponent)
	// Dont' fight myself, staff if I'm not supposed to.
	if (opponent = me.serial or (opponent.cmdlevel and !ai.AttackStaff))
		SetWarMode(0);
		return 0;
	endif

	set_priority(AI_COMBAT_PRIORITY);

	PreFight(opponent);

	SetWarMode(1);
	SetOpponent(opponent);
	TurnToward(opponent);

	CloseDistance(opponent);

	FightLoop(opponent);

	EndFight();
	postFight(opponent);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Ends the fight.
// Params:  opponent		Ref to mobile.
///////////////////////////////////////////////////////////
function EndFight()
	// Check if I am the make up type.
	if (!me.MakePeace)
		return 0;
	endif

	SetWarMode(0);
	SetOpponent(0);

	set_priority(AI_NONCOMBAT_PRIORITY);
endfunction

///////////////////////////////////////////////////////////
// Purpose: The fight loop.
// Params:  opponent		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
function FightLoop(byref opponent)
	var combatloops := 0;
	var sayflee := 1;

	while (opponent and !(opponent.dead or opponent.hidden or opponent.concealed)
			and Distance(me, opponent) < ai.ChaseDist and me.warmode)

		// Check if combat is taking too long.
		if (combatloops > ai.MaxCombatLoops or ShouldFlee())
			if (sayflee)
				SaySpeechStuff(SAYFLEE);
				sayflee := 0;
			endif
			Flee(opponent);
		else
			if (CloseDistance(opponent))
				combatloops := 0;
			endif
			sayflee := 1;
		endif

		combatloops := combatloops + 1;

		ProcessCombatEvent();
		Cast(opponent);

		// Custom hook.
		if (!DuringCombat(opponent))
			return;
		endif
	endwhile

	set_priority(AI_NONCOMBAT_PRIORITY);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Processes combat events.
///////////////////////////////////////////////////////////
function ProcessCombatEvent()
	var ev := wait_for_event(AI_WAIT_TIME_COMBAT);

	if (ev)
//		repeat
			case (ev.type)
				EVID_SPEECH:
					ProcessSpeech(ev, 1);

//				EVID_ENGAGED:
				EVID_DAMAGED:
					if (!me.warmode)
						Fight(ev.source);
						return 1;
					endif

					// Switch opponents now and then.
					if (RandomInt(AI_SWITCH_OPPONENT_CHANCE) = 1)
						TurnToward(ev.source);
						SetOpponent(ev.source);
						return 1;
					endif

				EVID_PEACEMADE:
					EndFight();

				EVID_OPPONENT_MOVED:
					if (!ShouldFlee())
						CloseDistance(ev.source);
						return 1;
					endif

				default:
					ProcessGroupEvent(ev);
					return;
			endcase
//		until (!(ev := wait_for_event(1)));
	endif

	ConsumeEvents();
endfunction

///////////////////////////////////////////////////////////
// Purpose: Run away! Run away!
// Params:  opponent		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function Flee(byref opponent)
	MoveAwayFrom(opponent);
	DuringFlee(opponent);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Should I flee?
// Params:  none
// Returns: 1		Yes, flee!
//			0		Fight, fight, fight!
///////////////////////////////////////////////////////////
function ShouldFlee()
	// Immobiles cannot flee!
	if (!me.CanMove)
		return 0;
	endif

	// Check my HP vs. Flee Point.
	if ((me.hp * 100/me.maxhp) < ai.FleePoint)
    	return 1;
    endif

	return 0;
endfunction
