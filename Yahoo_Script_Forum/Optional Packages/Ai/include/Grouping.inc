///////////////////////////////////////////////////////////
// Grouping.inc
//
// Main Processing for grouping critters.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
// These grouping functions utilize these CProps on NPCs:
//	#AiLeader		Serial of leader of the group.
//	#AiGroup		Array of Serials of buddies.
//	#AiMaxGroup		Max number that I can group with.
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const AILEADER		:= "AiLeader";
const AIGROUP		:= "AiGroup";
const AIMAXGROUP	:= "AiMaxGroup";
const AISERIAL		:= "AiSerial";

///////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////
var myleader := 0;		// Ref to my leader.
var mygroup  := 0; 		// Array of PIDs of buddies.

///////////////////////////////////////////////////////////
// GLOBAL CODE
///////////////////////////////////////////////////////////
EraseObjProperty(me, AILEADER);
EraseObjProperty(me, AIGROUP);

// Make mygroup an array only if we can group, saves memory.
if (mydesc.group)
	mygroup := array;
endif

// Store my serial.
SetObjProperty(me, AISERIAL, me.serial);

///////////////////////////////////////////////////////////
// Purpose: Form a group. Call this function to try to
//			group with something.
// Params:  mobile		Ref to mobile.
// Returns: 1	He's friendly.
//			0	I can't group with it.
///////////////////////////////////////////////////////////
function FormGroup(byref mobile)
	// Check if it's ok to group with this mobile.
	if (!CanGroupWith(mobile))
		return 0;
	endif

	if (GroupedWith(mobile))
		return 1;
	endif

	TurnToward(mobile);

	if (MeBeLeader(mobile))
		// I am the leader!!!  Let him know to join up.
		SetLeader(me);
		mygroup.append(mobile.serial);

		SaySpeechStuff(SAYINVITE);

		var gev := struct;
		gev.+type := EVID_GROUP_JOIN;
		gev.+source := me;
		SendEvent(mobile, gev);
	else
		return 1;
	endif

	SetObjProperty(me, AIGROUP, mygroup);

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Accept invitation to group.
// Params:  leader		Ref to mobile who is my new leader.
// Returns: N/A
///////////////////////////////////////////////////////////
function GroupWith(byref leader)
	SaySpeechStuff(SAYACCEPT);
	mygroup.append(leader.serial);
	SetLeader(leader);
	SetObjProperty(me, AIGROUP, mygroup);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Processing for when a group member dies.
// Params:  serial		Serial of dead buddy.
// Returns: N/A
///////////////////////////////////////////////////////////
function GroupDeath(serial)
	// If leader died, no more group!
	if (serial = GetObjProperty(me, AILEADER))
		EraseObjProperty(me, AILEADER);
		EraseObjProperty(me, AIGROUP);
		NoLeader();
		return;
	endif

	// A regular member of the group died.
	var num;
	for (num := 1; num <= mygroup.size(); num := num + 1)
		if (mygroup[num] = serial)
			mygroup.erase(num);
			if (mygroup.size() > 0)
				SetObjProperty(me, AIGROUP, mygroup);
			else
				EraseObjProperty(me, AIGROUP);
			endif
			return;
		endif
	endfor

	// If I am leader and no more groupmembers...
	if (!mygroup.size())
		EraseObjProperty(me, AILEADER);
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Checks if an NPC and I can group.
// Params:  mobile		Ref to mobile.
// Returns: 1	 	Let's team up!
//			0		Nope.
///////////////////////////////////////////////////////////
function CanGroupWith(byref mobile)
	var groups := SplitWords(mydesc.group);
	var hisgrp := npccfg[mobile.npctemplate].group;

	foreach group in groups
		if (group = hisgrp)
			return 1;
		endif
	endforeach

	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Am I grouped with this mobile?
// Params:  mobile		Ref to mobile.
// Returns: 1		Yes, we are grouped.
//			0		No, we are not grouped.
///////////////////////////////////////////////////////////
function GroupedWith(byref mobile)
	foreach serial in mygroup
		if (serial = mobile.serial)
			return 1;
		endif
	endforeach
	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Sets the leader of the group.
// Params:  leader		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function SetLeader(byref leader)
	myleader := leader;
	SetObjProperty(me, AILEADER, myleader.serial);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Frees me from my leader.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function NoLeader()
	myleader := 0;
	EraseObjProperty(me, AILEADER);
	StopFollowing();
endfunction

///////////////////////////////////////////////////////////
// Purpose: Am I the leader?
// Params:  mobile		Ref to a mobile.
// Returns: 1		I am new leader.
//			0		I can't be the leader.
///////////////////////////////////////////////////////////
function MeBeLeader(byref mobile)
	// Am I the leader type?
	if (!mydesc.groupleader)
		return 0;
	endif

	// Am I at my group max?
	if (mydesc.groupmax and mygroup.size() > mydesc.groupmax)
		return 0;
	endif

	// if I have a leader.
	if (myleader and myleader.serial != me.serial)
		return 0;
	endif

	// If he is already a leader or has one, then I can't be...
	var hisleader := GetObjProperty(mobile, AILEADER);
	if (hisleader)
		return 0;
	endif

	// If I am already leader, then he must join me.
	if (myleader.serial = me.serial)
		return 1;
	endif

	// Leader is determined by adding up all the stats
	// the one with the highest stats always wins.
	var mystats := me.strength + me.dexterity + me.intelligence;
	var hisstats := mobile.strength + mobile.dexterity + mobile.intelligence;

	if (mystats > hisstats)
		return 1;
	elseif (mystats < hisstats)
		return 0;
	else // We has same stats, I'm first to ask, so I'm leader!
		return 1;
	endif

	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Signal group members.
// Params:  ev			Ref to event struct.
// Returns: N/A
///////////////////////////////////////////////////////////
function SignalGroup(byref ev)
	var bud;
	foreach buddy in mygroup
		bud := SystemFindObjectBySerial(buddy);
		SendEvent(bud, ev);
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Gets help from buddies.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function GetHelpFrom(byref opponent)
	if (!mygroup.size())
		return 0;
	endif

	SaySpeechStuff(SAYHELP);

	var ev := struct;
	ev.+type := EVID_GROUP_HELP;
	ev.+source := me;
	ev.+opponent := opponent;

	SignalGroup(ev);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Leader tells all to attack
// Params:  opponent	Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function GroupAllAttack(byref opponent)
	var ev := struct;
	ev.+type := EVID_GROUP_HELP;
	ev.+source := me;
	ev.+opponent := opponent;

	SignalGroup(ev);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Does processing of Group related events.
// Params:  ev			Ref to event structure.
// Returns: N/A
///////////////////////////////////////////////////////////
function ProcessGroupEvent(byref ev)
	case (ev.type)

		EVID_GROUP_JOIN:
			GroupWith(ev.source);
			Follow(ev.source);

		EVID_GROUP_DEATH:
			GroupDeath(ev.source);

		EVID_GROUP_HELP:
			// if he is poisoned, ignore him.
			if (ev.source.poisoned)
				return 1;
			endif

			SaySpeechStuff(SAYAID);
			// If I am leader, tell the group!
			if (myleader.serial = me.serial)
				SaySpeechStuff(SAYATTACK);
				GroupAllAttack(ev.opponent);
			endif

			if (!me.warmode)
				Fight(ev.opponent);
			endif
	endcase
endfunction