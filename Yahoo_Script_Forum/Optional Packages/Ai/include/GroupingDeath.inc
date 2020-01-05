///////////////////////////////////////////////////////////
// GroupingDeath.inc
//
// Functions to be used from scripts/misc/death.src
// when the NPC dies.
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

include "/include/eventid";

const AIGROUP	:= "AiGroup";
const AISERIAL	:= "AiSerial";
const AILEADER	:= "AiLeader";

function AiGroupingDeath(byref corpse)
	var group := GetObjProperty(corpse, AIGROUP);

	var ev := struct;
	ev.+type	:= EVID_GROUP_DEATH;
	ev.+source := GetObjProperty(corpse, AISERIAL);

	// Send to each bud, and to leader.
	var bud;
	foreach buddy in group
		bud := SystemFindObjectBySerial(buddy);
		if (bud)
			SendEvent(bud, ev);
		endif
	endforeach

	SendEvent(GetObjProperty(corpse, AILEADER), ev);
endfunction