///////////////////////////////////////////////////////////
// StatMod.inc
//
// Stat modification functions.
//
// Creator: Oroborous
// Contact: mkow@sympatico.ca
//
// Created: Dec-2000
// Stat flags are set like so: CProp "#<stat>" = {expiry, amt}
///////////////////////////////////////////////////////////

use os;
use uo;
use basic;

include "include/messages";

var LegalStatMods := {"str", "dex", "int", "ar", "p"};

///////////////////////////////////////////////////////////
// Purpose:	Modifies a stat for a duration.
// Params:	who			Ref to mobile.
//			stat		Stat to modify.
//			amt			Amount to modify it by.
//			duration	Duration to mod for.
// Returns: 1/0
///////////////////////////////////////////////////////////
function ModifyStat(byref who, stat, amt, duration, logon := 0)
	stat := lower(stat);
	var prop := GetModProp(stat);
		
	if (!logon)
		if (GetObjProperty(who, prop))
			WarningMessage(who, "You are already under the influence!");
			return 0;
		endif
	endif
		
	set_critical(1);
	SetStatMod(who, stat, amt, duration);
	set_critical(0);
		
	start_script(":statmod:statmod", who);
		
	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Sets the stat mod.
// Params:	who			Ref to mobile.
//			stat		Stat to modify.
//			amt			Amount to modify it by.
//			duration	Duration to mod for. 0 = unmod.
// Returns: N/A
///////////////////////////////////////////////////////////
function SetStatMod(byref who, stat, amt, duration)
	var prop := GetModProp(stat);

	//print("Stat mod: " + who + ", " + stat + ", " + amt + ", " + duration);

	case (stat)
		"str":	who.strength_mod 	:= who.strength_mod + amt;
		"dex":	who.dexterity_mod 	:= who.dexterity_mod + amt;
		"int":	who.intelligence_mod := who.dexterity_mod + amt;
		"ar":	who.ar_mod 			:= who.ar_mod + amt;
		"p":	
			if (amt > 0)
				who.SetParalyzed(1);
			else
				who.SetParalyzed(0);
			endif
	endcase
	
	if (duration)
		var expire := ReadGameClock() + duration;
		SetObjProperty(who, prop, {expire, amt});	
	else
		EraseObjProperty(who, prop);
	endif	
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Unmodifies a stat.
// Params:	who			Ref to mobile.
//			stat		Name of stat.
//			amt			Amount to unmod.
// Returns: 1/0
///////////////////////////////////////////////////////////
function UnmodifyStat(byref who, stat, amt)
	stat := lower(stat);
	var prop := GetModProp(stat);
		
	if (!GetObjProperty(who, prop))
		return 0;
	endif
	
	set_critical(1);
	SetStatMod(who, stat, (-1 * amt), 0);
	set_critical(0);
		
	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Returns the flag for the stat.
// Params:	stat		Stat name. 
// Returns: flag		CProp flag used.
///////////////////////////////////////////////////////////
function GetModProp(stat)
	var prop := "#" + stat;
	return prop;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Returns the name of the stat from a prop.
// Params:	prop		Property name.
// Returns: stat		Stat name.
///////////////////////////////////////////////////////////
function GetStatFromModProp(prop)
	var stat := prop[2, len(prop)];
	return stat;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Checks if statmod expired yet.
// Params:	who			Ref to mobile.
//			stat		Stat to check.
// Returns: 1/0
///////////////////////////////////////////////////////////
function CheckStatModExpire(byref who, stat)
	var prop := GetModProp(stat);
	
	var statmod := GetObjProperty(who, prop);
	
	var expire := statmod[1];
	if (!expire)
		return 1;
	endif
	
	if (expire > ReadGameClock())
		return 0;
	endif
	
	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Returns a list of current stat mods.
// Params:	who			Ref to mobile.
// Returns: statmods	List of current stat mods.
///////////////////////////////////////////////////////////
function EnumerateStatMods(byref who)
	var statmods := array;
	
	var stat;
	foreach prop in GetObjPropertyNames(who)
		stat := GetStatFromModProp(prop);
		if (stat in LegalStatMods)
			statmods.append(prop);
		endif
	endforeach
	
	return statmods;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Clears all the statmods.
// Params:	who		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function ClearStatMods(byref who)
	who.strength_mod 	:= 0;
	who.dexterity_mod	:= 0;
	who.intelligence_mod := 0;
	who.ar_mod 			:= 0;
	who.SetParalyzed(0);
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Resets all the statmods.
// Params:	who			Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function ResetAllStatMods(byref who, logon := 0)
	ClearStatMods(who);
	
	var stat;
	var statmod;
	var duration;
	foreach prop in EnumerateStatMods(who)
		statmod := GetObjProperty(who, prop);	
		stat := GetStatFromModProp(prop);
		duration := statmod[1] - ReadGameClock();
		if (duration > 0)
			ModifyStat(who, stat, statmod[2], duration, 1);
		else
			EraseObjProperty(who, prop);
		endif
	endforeach
endfunction