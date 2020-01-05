///////////////////////////////////////////////////////////
// SpawnPoint.inc
//
// Spawn Point related functions.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
// Global CProps used:
//	SpawnPoints		Array of spawn points.
//
// Item CProps used:
//	Type		Type of spawn.
//	Template	NPC or object template to spawn.
//	Max			Max number to spawn.
//	Num			Number currently spawned.
//	Range		How far can they wander (NPCs).
//	Frequency	Minimum amount of time before can respawn, 0 = no time delay.
// 	Expire		How long since creation (in mins) until point is destroyed?
// 	ExpireNum	How many spawns before point is destroyed?
//	Note		Notes on this spawn rune.
//	Spawns		Array of serials of objects spawned.
//  NextSpawn	Time before next spawn can be created.
//	Disabled	If this prop exists, the spawn point is disabled.
//	Despawn		If this is set, all spawns are destroyed on spawn point destruction.
// 	CreateTime	Time rune was created.
//  Group		If this is set, Spawn all NPC together, otherwise stagger 1 per cycle.
//	NextValidate Time of next validation as per VALIDATE_INTERVAL.
///////////////////////////////////////////////////////////

use os;
use uo;
use cfgfile;

include "include/CreateNpc";
include "include/clock";

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const VALIDATE_INTERVAL		:= 60 * 5; // 5 minutes.

///////////////////////////////////////////////////////////
// Purpose: Add the point's serial to the global list.
// Params:  serial		Serial of the spawn point.
// Returns: N/A
///////////////////////////////////////////////////////////
function AddSpawnPoint(serial)
	set_critical(1);

	var spawnpoint := GetGlobalProperty("SpawnPoints");
	if (!spawnpoint)
		spawnpoint := array;
	endif

	spawnpoint.append(serial);
	SetGlobalProperty("SpawnPoints", spawnpoint);

	set_critical(0);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Remove the point's serial from the global list.
// Params:  serial		Serial of spawn point.
// Returns: N/A
///////////////////////////////////////////////////////////
function RemoveSpawnPoint(serial)
	set_critical(1);

	var spawnpoint := GetGlobalProperty("SpawnPoints");
	if (!spawnpoint)
		return;
	endif

	var num;
	for (num := 1; num <= spawnpoint.size(); num := num + 1)
		if (spawnpoint[num] = serial)
			spawnpoint.erase(num);
		endif
	endfor

	SetGlobalProperty("SpawnPoints", spawnpoint);

	set_critical(0);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Sends a death event to the manager when npc dies.
//			**Call this from death.src.
// Params:	corpse		Ref to corpse object.
// Returns: N/A
///////////////////////////////////////////////////////////
function SpawnPointDeath(corpse);
	var pointserial := GetObjProperty(corpse, "SpawnPoint");
	if (!pointserial)
		return;
	endif

	var npcserial := GetObjProperty(corpse, "AiSerial");

	var ev := struct;
	ev.+type := EVID_SPAWN_DEATH;
	ev.+source := corpse;
	ev.+npcserial := npcserial;
	ev.+pointserial := pointserial;

	var pid := GetGlobalProperty("#SpawnPointManagerPID");
	var manager := GetProcess(pid);
	manager.sendevent(ev);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Removes the serial from the point's list.
// Params:  point		Ref to point object.
//			npcserial	Serial of NPC being removed.
// Returns: N/A
///////////////////////////////////////////////////////////
function RemoveSerialFromPoint(byref point, npcserial)
	var serials := GetObjProperty(point, "Serials");
	var num;
	for (num := 1; num <= serials.size(); num := num + 1)
		if (serials[num] = npcserial)
			serials.erase(num);
			break;
		endif
	endfor

	SetObjProperty(point, "Serials", serials);

	// Now set NextSpawn.
	var freq := CInt(GetObjproperty(point, "Frequency"));
	var nextspawn := ReadGameClock() + (freq * 60);
	SetObjProperty(point, "NextSpawn", nextspawn);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Attempt to spawn something.
// Params:  point		Spawn point to spawn for.
// Returns: 1		Something was spawned.
//			0		Nothing was spawned.
///////////////////////////////////////////////////////////
function Spawn(byref point)
	// NOTE: Disabled runes never expire either!
	if (GetObjProperty(point, "Disabled"))
		return 0;
	endif

	// Done periodically.
	ValidatePointSpawns(point);

	var type := GetObjProperty(point, "Type");
	var template := GetObjProperty(point, "Template");

	var serials := GetObjProperty(point, "Serials");
	if (!serials)
		serials := array;
	endif

	var max := CInt(GetObjProperty(point, "Max"));
	var obj;

	// Check for expiry based on time.
	var expiretime := CInt(GetObjProperty(point, "Expire")) * 60; // In mins.
	if (expiretime > 0)
		// Calculate how much time left.
		var whenexpire := CInt(GetObjProperty(point, "CreateTime")) + expiretime;
		var minsleft := (whenexpire - ReadGameClock()) / 60;
		if (minsleft <= 0)
			DeletePoint(point);
		endif
		SetObjProperty(point, "Expire", minsleft);
	endif

	// Anything to spawn?
	if (template = "<NONE>" or !CanSpawn(point))
		return 0;
	endif

	// How many to spawn?
	var numtospawn := max - serials.size();
	if (numtospawn <= 0)
		return 0;
	endif

	// Check for expiry based on number.
	var deleterune := 0;
	var expirenum := GetObjProperty(point, "ExpireNum");
	if (expirenum > 0)
		var expireleft := expirenum - numtospawn;
		if (expireleft <= 0)
			numtospawn := expireleft;
		endif

		// Write back expireleft.
		SetObjProperty(point, "ExpireNum", expireleft);

		// Now check if after this spawn the rune should be deleted.
		if (expireleft <= 0)
			deleterune := 1;
		endif
	endif

	var anchor := array;
	anchor.append(point.x);
	anchor.append(point.y);
	anchor.append(GetObjProperty(point, "Range"));
	anchor.append(100);

	// Check if grouping, otherwise stagger.
	if (!GetObjProperty(point, "Group"))
		numtospawn := 1;
	endif

	var num;
	for (num := 0; num < numtospawn; num := num + 1)
		case (type)
			"NPC":
				obj := CreateNpc(template, point.x, point.y, point.z);
				if (!obj)
					syslog("Failed to create " + template + ", error = " + obj.errortext);
					return 0;
				endif

			"Item":

			"Container":

			default:
				syslog("Unknown SpawnPoint type: " + type);
				return 0;
		endcase

		serials.append(obj.serial);
		SetObjProperty(obj, "SpawnPoint", point.serial);
		SetObjProperty(obj, "Anchor", anchor);
		RestartScript(obj);
		sleep(2);
	endfor

	SetObjProperty(point, "Serials", serials);

	if (deleterune)
		DeletePoint(point);
	endif

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Checks if it is time to spawn also despawns
//			any existing spawns if we can't spawn right now!
// Params:  point
// Returns: 1		Time to spawn.
//			0		Can't spawn yet.
///////////////////////////////////////////////////////////
function CanSpawn(byref point)
	var freq := GetObjProperty(point, "Frequency");
	var nextspawn := GetObjProperty(point, "NextSpawn");
	if (!nextspawn)
		nextspawn := 0;
	endif

	var clock := ReadGameClock();

	if (nextspawn > clock)
		return 0;
	endif

	// Check if it right time to spawn.
	var starthr := CInt(GetObjProperty(point, "HrStart"));
	var endhr := CInt(GetObjProperty(point, "HrEnd"));

	if ((starthr != 0 and endhr != 0))
		var hrnow := GetHourOfDay();
		if (!HourWithinRange(hrnow, starthr, endhr))
			DespawnAll(point); // Despawn all, can't spawn now.
			return 0;
		endif
	endif

	nextspawn := clock + (freq * 60);
	SetObjProperty(point, "NextSpawn", nextspawn);

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Spawns all points.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function SpawnAllPoints()
	var point;
	var spawnpoints := GetGlobalProperty("SpawnPoints");

	// This also does cleanup if there are problems.
	var num := 1;
	foreach serial in spawnpoints
		point := SystemFindObjectBySerial(serial);
		if (!point)
			spawnpoints.erase(num);
			continue;
		endif

		Spawn(point);
		num := num + 1;
		sleep(2);
	endforeach

	SetGlobalProperty("SpawnPoints", spawnpoints);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Kills/destroys all spawns.
// Params:  point		Ref to spawn point object.
// Returns: N/A
///////////////////////////////////////////////////////////
function DespawnAll(byref point)
	var ptobj;
	var spawno;
	var type := GetObjProperty(point, "Type");

	foreach spawnsr in GetObjProperty(point, "Serials")
		spawno := SystemFindObjectBySerial(spawnsr);
		case (type)
			"NPC":
				// Kill all NPCs.
				SetObjProperty(spawno, "guardkill", 1);
				SetObjProperty(spawno, "NoSound", 1);
				ApplyRawDamage(spawno, spawno.maxhp * 2);

			"Container":
				// Destroy the container, all within will be destroyed too.

			"Item":
				// Destroy only spawned items on the ground.

		endcase
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Destroys the spawn point.
// Params:  point		Ref tospawn point obj.
// Returns: N/A
///////////////////////////////////////////////////////////
function DeletePoint(byref point)
	var type := GetObjProperty(point, "Type");
	var template := GetObjProperty(point, "Template");
	var max := CInt(GetObjProperty(point, "Max"));
	var despawn := GetObjProperty(point, "Despawn");
	var dtxt := "";
	if (despawn)
		dtxt := "Despawning all spawns.";
		DespawnAll(point);
	endif
	syslog("SpawnPoint (" + type + ": " + max + " " + template + ") expired. " + dtxt);
	DestroyItem(point);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Validates a point's serials list, and removes
//			invalid entries.
// Params:  point		Ref to point to validate.
// Returns: N/A
///////////////////////////////////////////////////////////
function ValidatePointSpawns(byref point)
	var nextval := CInt(GetObjProperty(point, "NextValidate"));
	if (!nextval)
		nextval := 0;
	endif

	// Check if time to validate again.
	var clock := ReadGameClock();
	if (nextval > clock)
		return 0;
	endif
	nextval := clock + VALIDATE_INTERVAL;
	SetObjProperty(point, "NextValidate", nextval);

	var serials := GetObjProperty(point, "Serials");
	if (serials.size() <= 0)
		return 0;
	endif

	var obj;
	var idx;
	for (idx := 1; idx <= serials.size(); idx := idx + 1)
		obj := SystemFindObjectBySerial(serials[idx]);
		if (!obj)
			serials.erase(idx);
		endif
	endfor

	SetObjProperty(point, "Serials", serials);
endfunction

