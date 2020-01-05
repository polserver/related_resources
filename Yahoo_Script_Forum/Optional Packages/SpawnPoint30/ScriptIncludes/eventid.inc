///////////////////////////////////////////////////////////
// EventId.inc
//
// Includes for custom user events.  These have to have at
// least 2 bits set, unlike systemevents that have only 1
// bit set.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

include "sysevent";

/* FIXME: these need to be renumbered, one clashes with a reserved event */
// OBSOLETE NOW with AI Package...
const EVID_SPELL_ATTACK     	:= 0x0202;
const EVID_BUDDYATTACKED     	:= 0x0204;
const EVID_PEACEMADE         	:= 0x0206;

// AI Package Grouping Messages.
const EVID_GROUP_JOIN   	 	:= 1002;
const EVID_GROUP_DEATH    		:= 1004;
const EVID_GROUP_HELP			:= 1008;

// SpawnPoint Package Messages.
const EVID_SPAWNPOINT_CREATED	:= 1010;
const EVID_SPAWNPOINT_DESTROYED := 1020;
const EVID_SPAWNPOINT_RESET		:= 1040;
const EVID_SPAWNPOINT_CHANGED	:= 1080;
const EVID_SPAWN_DEATH			:= 1100;

// AI Tamed messages.
const EVID_ALL_ATTACK_CMD   := 0x2002;
const EVID_ALL_FOLLOW_CMD   := 0x2004;
const EVID_ALL_GUARD_CMD	:= 0x2006;

// SpawnRegion Package Messages.
const EVID_SPAWNREGION_DEATH	:= 3001;
