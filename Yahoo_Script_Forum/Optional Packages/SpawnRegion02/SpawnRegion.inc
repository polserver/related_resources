///////////////////////////////////////////////////////////
// SpawnRegion.inc
//
// SpawnRegion functions.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 1-Nov-2000
// Updated: 1-Nov-2000
//
// Uses Global CProps:
//	SpawnRegions	This is a complex data struct containing
//					a dict of region names each of which contains
//					a dict of group names each of which contains
//					an array of serials spawned in that region.
//
// 	SpawnRegionsFreq	Same setup as SpawnRegions except instead of
//						SpawnRegions[region][group] holding an array
//						of serials, it holds the time for the next spawn.
//						If it is set to -1, then that group is disabled.
//
// Uses Mobile CProps:
//	#SpawnRegionManagerPID	PID of the spawn region manager script.
//	AiSerial		Set by AI script to the serial of the mobile.
//	Region			String in the format "region_name group_name".
///////////////////////////////////////////////////////////

use os;
use uo;
use cfgfile;
use basic;
use util;

include "include/createnpc";
include "include/clock";

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const MAX_SPAWN_TRIES		:= 10;	// Max number of attempts to spawn an npc.
const DEFAULT_GRP_FREQUENCY	:= 5;	// In minutes.

///////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////
var npccfg 		:= ReadConfigFile(":*:npcdesc");
var regionscfg	:= ReadConfigFile(":spawnregion:spawnregions");
var groupscfg	:= ReadConfigFile(":spawnregion:spawngroups");
var regcfg		:= dictionary;	// Regions config.
var grpcfg		:= dictionary;	// Groups config.
var regidx 		:= 0;			// Region index for SpawnAllRegions.
var MgrVerbose	:= 0;			// Whether messages are sent to console.

///////////////////////////////////////////////////////////
// GLOBAL CODE
///////////////////////////////////////////////////////////
UnloadConfigFile(":spawnregion:spawnregions");
UnloadConfigFile(":spawnregion:spawngroups");
ReadRegions();
ReadGroups();

///////////////////////////////////////////////////////////
// Purpose: Reads in the regions from cfg.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function ReadRegions()
	foreach regname in GetConfigStringKeys(regionscfg)
		var regelem := FindConfigElem(regionscfg, regname);
		if (!regelem)
			syslog("Unable to find Region: " + regname);
			continue;
		endif
		regcfg[regname] := regelem;
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Reads in the groups from cfg.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function ReadGroups()
	foreach grpname in GetConfigStringKeys(groupscfg)
		var grpelem := FindConfigElem(groupscfg, grpname);
		if (!grpelem)
			syslog("Unable to find Group: " + grpname);
			continue;
		endif
		grpcfg[grpname] := grpelem;
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Spawns a region.
// Params:  region		Name of region to spawn.
// Return:	none
///////////////////////////////////////////////////////////
function SpawnRegion(region)
	if (GetGlobalProperty("SpawnRegionOff"))
		return 0;
	endif

	var reggrps := GetConfigStringArray(regcfg[region], "Group");

	var grpdata;
	foreach grp in reggrps
		grpdata := SplitWords(grp);
		SpawnGroup(region, grpdata[1], CInt(grpdata[2]), CInt(grpdata[3]), CInt(grpdata[4]), CInt(grpdata[5]));
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Spawns a group within a region.
// Params:  region		Name of region.
//			group		Name of group.
//			max			Max number to spawn.
//			freq		Frequency of this group.
//			hrstart		HR to start spawning.
//			hrend		HR to stop spawning.
// Returns: none
///////////////////////////////////////////////////////////
function SpawnGroup(region, group, max, freq, hrstart, hrend)
	// Check if this group is disabled.
	var nextspawn := GetGroupFreq(region, group);
	if (nextspawn = -1)
		return 0;
	endif

	// Check if this group can spawn at this time, if not despawn all existing.
	if (hrstart and hrend)
		var hrnow := GetHourOfDay();
		if (!HourWithinRange(hrnow, hrstart, hrend))
			DespawnGroup(region, group);
			return 0;
		endif
	endif

	// Get current list of spawns for this region.
	var spawns := GetGroupSpawns(region, group);

	// If we are at max, then return.
	if (spawns.size() >= CInt(max))
		return 0;
	endif

	// Check if we can spawn now.
	if (!freq)
		freq := DEFAULT_GRP_FREQUENCY;
	endif

	var clock := ReadGameClock();
	if (nextspawn > clock)
		return 0;
	endif
	nextspawn := clock + (freq * 60);
	SetGroupFreq(region, group, nextspawn);

	// Check if there is anything to spawn in this group.
	if (spawns.size() >= max)
		return 0;
	endif

	// Get list of NPCs for group.
	var npcs := GetConfigStringArray(grpcfg[group], "Npc");
	if (!npcs)
		syslog("Unable to find SpawnGroup: " + group);
		return 0;
	endif
	
	// How many to spawn?
	var tospawn := max - spawns.size();

	var sp;
	var template;
	var npc;
	for (sp := 1; sp <= tospawn; sp := sp + 1)
		template := PickRandomNpc(npcs);
		npc := SpawnNpc(region, group, template);
		if (!npc)
			continue;
		endif
		spawns.append(npc.serial);
		sleepms(100); // For good measure.
	endfor
	
	SetGroupSpawns(region, group, spawns);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Picks a random NPC from a group.
// Params:  npcs		Array of NPC templates.
// Returns: template	Template of NPC chosen.
///////////////////////////////////////////////////////////
function PickRandomNpc(byref npcs)
	var idx := RandomInt(npcs.size()) + 1;
	return npcs[idx];
endfunction

///////////////////////////////////////////////////////////
// Purpose: Spawns an npc in a region.
//			CREDIT: Code stolen from RegionalSpawner.
// Params:  region		Name of region.
//			group		Name of group.
//			template	NpcTemplate to spawn.
// Returns: npc			Ref to mobile object spawned.
//			0			Failed to spawn.
///////////////////////////////////////////////////////////
function SpawnNpc(region, group, template)
	// Get the coords of region.
	var coords := SplitWords(regcfg[region].rect);
	var x1 := cint(coords[1]);
	var y1 := cint(coords[2]);
	var x2 := cint(coords[3]);
	var y2 := cint(coords[4]);

	var x, y, z;
	var tries := 0;
	var sh;
	var info;
	var npc;
	var prop;

	repeat
		// Randomly choose point to spawn at.
		x := RandomInt(x2-x1)+x1;
		y := RandomInt(y2-y1)+y1;
		z := GetMapInfo(x, y).z;
		tries := tries + 1;

		// Never spawn on multis!
		sh := GetStandingHeight(x, y, z);
		if (sh.multi or sh.multi.serial)
			npc := 0;
		else
			info := hex(GetMapInfo(x , y).landtile);
			if ((info < 0x406) or (info > 0x455))
				npc := CreateNpc(template, x, y, z);
				if (npc)
					prop := region + " " + group;
					SetObjProperty(npc, "SpawnRegion", prop);
					return npc;
				endif
			endif
		endif
	until (tries > MAX_SPAWN_TRIES);

	if (tries > MAX_SPAWN_TRIES)
		syslog("Exceeded max tries. Region = " + region + ", npc = " + template);
	endif

	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Handles spawn death.
//			**NOTE: Call this from death.src.
// Params:	corpse		Ref to corpse object.
// Returns: N/A
///////////////////////////////////////////////////////////
function SpawnRegionDeath(byref corpse)
	var regdata := SplitWords(GetObjProperty(corpse, "SpawnRegion"));
	RemoveSerialFromGroup(regdata[1], regdata[2], CInt(GetObjProperty(corpse, "AiSerial")));
endfunction

///////////////////////////////////////////////////////////
// Purpose: Removes spawn from group.
// Params:	region		Name of region.
//			group		Name of group.
//			serial		Serial to remove.
// Returns: N/A
///////////////////////////////////////////////////////////
function RemoveSerialFromGroup(region, group, serial)
	set_critical(1);

	var spawns := GetGroupSpawns(region, group);

	var idx;
	for (idx := 1; idx <= spawns.size(); idx := idx + 1)
		if (spawns[idx] = serial)
			spawns.erase(idx);
		endif
	endfor
	
	SetGroupSpawns(region, group, spawns);
	
	set_critical(0);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Despawns a region
// Params:  region		Name of region.
// Returns: N/A
///////////////////////////////////////////////////////////
function DespawnRegion(region)
	var spawnregions := GetGlobalProperty("SpawnRegions");
	if (!spawnregions)
		spawnregions := dictionary;
	endif

	// Get the groups in the region (a dict of groups).
	var rgroups := spawnregions[region];
	if (!rgroups)
		return 0;
	endif

	foreach grp in (rgroups.keys())
		DespawnGroup(region, grp);
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Despawns a group.
// Params:  region		Name of region.
//			group		Name of group.
// Returns: N/A
///////////////////////////////////////////////////////////
function DespawnGroup(region, group)
	var spawns := GetGroupSpawns(region, group);

	foreach spawn in spawns
		Despawn(spawn);
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Despawns an npc.
// Params:  serial		Serial of npc to despawn.
// Returns: N/A
///////////////////////////////////////////////////////////
function Despawn(serial)
	var npc := SystemFindObjectBySerial(serial);
	if (!npc)
		return 0;
	endif

	SetObjProperty(npc, "guardkill", 1);
	SetObjProperty(npc, "NoSound", 1);
	ApplyRawDamage(npc, npc.maxhp * 2);
	Sleepms(100); // For good measure in case a lot of npcs are despawned at once.
endfunction

///////////////////////////////////////////////////////////
// Purpose: Get list of spawns for a group in a region.
//			This also allocates the space in the dict for
//			this region if it is new.
// Params:  region		Region name.
//			group		Group name.
// Returns: spawns		Array of spawns in that group.
///////////////////////////////////////////////////////////
function GetGroupSpawns(region, group)
	var spawnregions := GetGlobalProperty("SpawnRegions");
	if (!spawnregions)
		spawnregions := dictionary;
	endif

	// Alloc dictionary if region does not exist.
	if (!spawnregions.exists(region))
		spawnregions[region] := dictionary;
	endif

	var spawns := spawnregions[region][group];
	if (!spawns)
		return array; // Return empty array.
	endif

	return spawns;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Set list of spawns for a group in a region.
//			**NOTE: You must call GetSgroupSpawns() before
//			calling this, use the value returned from there
//			as the spawns param here.
// Params:  region		Region name.
//			group		Group name.
//			spawns		Array of spawns to set.
// Returns: N/A
///////////////////////////////////////////////////////////
function SetGroupSpawns(region, group, byref spawns)
	set_critical(1);
	
	var spawnregions := GetGlobalProperty("SpawnRegions");
	if (!spawnregions)
		spawnregions := dictionary;
	endif

	// Alloc dictionary if region does not exist.
	if (!spawnregions.exists(region))
		spawnregions[region] := dictionary;
	endif

	spawnregions[region][group] := spawns;
	SetGlobalProperty("SpawnRegions", spawnregions);
	
	set_critical(0);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Spawns all regions, but does it one region per
//			cycle.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function SpawnAllRegions()
	if (GetGlobalProperty("SpawnRegionOff"))
		return 0;
	endif

	var regions := GetConfigStringKeys(regionscfg);
	
	foreach reg in regions
		start_script(":spawnregion:spawnregion", reg);
	endforeach

endfunction

///////////////////////////////////////////////////////////
// Purpose: Enables a spawn region.
// Params:  region		Name of region.
// Returns: N/A
///////////////////////////////////////////////////////////
function EnableRegion(region)
	var spawnregfreq := GetGlobalProperty("SpawnRegionsFreq");
	if (!spawnregfreq)
		spawnregfreq := dictionary;
	endif

	foreach grp in (spawnregfreq[region].keys())
		EnableGroup(region, grp);
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Disables a region.
// Params:  region		Name of region.
// Returns: N/A
///////////////////////////////////////////////////////////
function DisableRegion(region)
	var spawnregfreq := GetGlobalProperty("SpawnRegionsFreq");
	if (!spawnregfreq)
		spawnregfreq := dictionary;
	endif

	foreach grp in (spawnregfreq[region].keys())
		DisableGroup(region, grp);
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Enables a group.
// Params:  region		Name of region.
//			group		Name of group.
// Returns: N/A
///////////////////////////////////////////////////////////
function EnableGroup(region, group)
	var freq := GetGroupFreq(region, group);
	if (freq != -1)
		return 0;
	endif

	SetGroupFreq(region, group, 1);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Disables a group.
// Params:  region		Name of region.
//			group		Name of group.
// Returns: N/A
///////////////////////////////////////////////////////////
function DisableGroup(region, group)
	SetGroupFreq(region, group, -1);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Get list of frequencies for a group in a region.
//			This also allocates the space in the dict for
//			this region if it is new.
// Params:  region		Region name.
//			group		Group name.
// Returns: freq		Array of frequency data.
///////////////////////////////////////////////////////////
function GetGroupFreq(region, group)
	var spawnregions := GetGlobalProperty("SpawnRegionsFreq");
	if (!spawnregions)
		spawnregions := dictionary;
	endif

	// Alloc dictionary if region does not exist.
	if (!spawnregions.exists(region))
		spawnregions[region] := dictionary;
	endif

	var freq := spawnregions[region][group];
	return freq;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Set list of group frequencies for a region
//			**NOTE: You must call GetSgroupSpawns() before
//			calling this, use the value returned from there
//			as the spawns param here.
// Params:  region		Region name.
//			group		Group name.
//			freq		Array of frequencies to set.
// Returns: N/A
///////////////////////////////////////////////////////////
function SetGroupFreq(region, group, byref freq)
	set_critical(1);

	var spawnregions := GetGlobalProperty("SpawnRegionsFreq");
	if (!spawnregions)
		spawnregions := dictionary;
	endif

	// Alloc dictionary if region does not exist.
	if (!spawnregions.exists(region))
		spawnregions[region] := dictionary;
	endif

	spawnregions[region][group] := freq;
	SetGlobalProperty("SpawnRegionsFreq", spawnregions);
	
	set_critical(0);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Validates the SpawnRegions and SpawnRegionsFreqstructure
//			vs. the	config file.  Basically cleans up garbage.
// Params:  none
// Returns: none
///////////////////////////////////////////////////////////
function ValidateSpawnRegions()
	LogMsg("[SPAWNREGIONMGR]: Validating SpawnRegions.");
	
	var spawnregions := GetGlobalProperty("SpawnRegions");
	if (!spawnregions)
		spawnregions := dictionary;
	endif

	var spawnfreq := GetGlobalProperty("SpawnRegionsFreq");
	if (!spawnfreq)
		spawnfreq := dictionary;
	endif

	var cfggroups;
	var ingrpcfg;
	var spawns;
	var obj;
	var num;

	foreach regname in (spawnregions.keys())
		// Check if region still exists.
		if (!regcfg.exists(regname)) // Not in config!
			LogMsg("[SPAWNREGIONMGR]: Region " + regname + " removed.");
			DespawnRegion(regname);
			spawnregions.erase(regname); // Remove whole region.
			spawnfreq.erase(regname);
			continue;
		endif

		// Check if a group has been removed from the regions config.
		foreach grpname in (spawnregions[regname].keys())
			ingrpcfg := 0;
			foreach cgrp in GetConfigStringArray(regcfg[regname], "Group")
				cgrp := SplitWords(cgrp);
				if (cgrp[1] = grpname)
					ingrpcfg := 1;
				endif
			endforeach

			// Group is not in config, remove it and despawn it as well.
			if (!ingrpcfg)
				LogMsg("[SPAWNREGIONMGR]: " + regname + " - " + grpname + " removed.");
				DespawnGroup(regname, grpname);
				(spawnregions[regname]).erase(grpname);
				(spawnfreq[regname]).erase(grpname);
				continue;
			endif

			// Check all the spawns that they are valid, remove invalid ones.
			var serial;
			for (num := 1; num <= (spawnregions[regname][grpname]).size(); num := num + 1)
				serial := spawnregions[regname][grpname][num];
				obj := SystemFindObjectBySerial(serial);
				if (!obj)
					LogMsg("[SPAWNREGIONMGR]: " + regname + " - " + grpname + " - " + serial + " removed.");
					(spawnregions[regname][grpname]).erase(num);
				endif
			endfor
			sleepms(10);	// Avoid runaway.
		endforeach
		sleepms(10);	// Avoid runaway.
	endforeach

	SetGlobalProperty("SpawnRegions", spawnregions);
	SetGlobalProperty("SpawnRegionsFreq", spawnfreq);
	

	LogMsg("[SPAWNREGIONMGR]: Validation Completed.");
endfunction

///////////////////////////////////////////////////////////
// Purpose: Logs messages to console if verbose is specified.
// Params:	msg		Message to print to console.
// Returns: N/A
///////////////////////////////////////////////////////////
function LogMsg(msg)
	if (MgrVerbose)
		print(msg);
	endif
endfunction