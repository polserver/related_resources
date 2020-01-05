use uo;
use cfgfile;
use os;

//Special Effects
CONST CAST_ANIM := 17;
CONST CHANT_SOUND := 587;

//Meditation skill
CONST CLERIC_SKILL := 28;

//Focci
CONST POWER_FOCUS := 0xF014;
CONST SPIRIT_FOCUS := 0xF015;
CONST ARCANE_FOCUS := 0xF016;
CONST TIME_FOCUS := 0xF017;
CONST EARTH_FOCUS := 0xF018;
CONST LIFE_FOCUS := 0xF019;

//Cleric tools
CONST CLERIC_BOOK := 0xF903;
CONST HP_SYMBOL := 0x6053;

//Glyphs
CONST GLYPH_OF_WARDING := 0xDA05;
CONST SYMBOL_OF_PAIN := 0x7301;

function RiteInfo(elem) 
	// Send a number: Return the rite.
	var config := ReadConfigFile("rites");
	return config[elem];	
endfunction

function SacramentInfo(elem)
	var config := ReadConfigFile("sacraments");
	return config[elem];
endfunction

function DevotionType(what, rite)
	//Tricky function to use. (what, riteinfo(num))
	//Gets the devotion prop from what, and looks for it in the rite.
	if (!GetConfigString(rite, "Devotion") || GetObjProperty(what, "Devotion") == "Faithless")
		return 1;
	endif
	foreach devotion in GetConfigStringArray(rite, "Devotion")
		if (GetObjProperty(what, "Devotion") == devotion)
			return 1;
		endif
	endforeach
	return 0;
endfunction

function DevotionPiety(devotion, who:=0)
//Get the number of people online that are not GMs
//and the number in that cleric's faith to determine
//faith wide piety.

	var piety;
	var online := 0;
	var infaith := 0;
	//var sects := getsects(devotion);
	
	foreach player in EnumerateOnlineCharacters()
		if (player.cmdlevel < 2)
			if (GetObjProperty(player, "Devotion") == devotion)
				infaith := infaith + 1;
			endif
			online := online+1;
		endif
	endforeach
	
	piety := cdbl(infaith)/cdbl(online);
	piety := piety*10;
	
	if (piety < 1)
		piety := 1;
	endif
	
	if((piety - cint(piety)) >= 0.5)
   		piety := (cint(piety) + 1);
	else
   		piety := cint(piety);
	endif
	
	piety := piety+hpboost(who);

	return piety;
endfunction

function HPBoost(who)
	var owner, devotion;
	foreach item in listequippeditems(who)
		if (item.objtype == HP_SYMBOL)
			owner := GetObjProperty(item, "Owner");
			devotion := GetObjProperty(item, "Devotion");
			if (who.serial == owner && GetObjProperty(who, "Devotion") == devotion)
				return 1;
			endif
		endif
	endforeach
	return 0;
endfunction

function GetConcentratingClerics(who, range:=5, method := "piety", matchreligion := 0)
	// Finds all the clerics concentrating on the who cleric
	// in the defined range. Returns their combined piety.
	var piety;
	var clericlist := { };
	foreach person in listmobilesinlineofsight(who, range)
		if (!matchreligion || GetObjProperty(person, "Devotion") == GetObjProperty(who, "Devotion"))
			if(GetObjProperty(person, "#concentrating") == who.serial && person != who)
				clericlist.append(person);
				piety := piety + DevotionPiety(GetObjProperty(person, "Devotion"));
				SendSysMessage(who, person.name + " is concentrating on you.");
			endif
		endif
	endforeach
	
	if (method["piety"])
		return piety;
	else
		return clericlist;
	endif
endfunction

function ClericalTarget(byref who, byref npctarget, prompt := "Select a target", ops := TGTOPT_CHECK_LOS + TGTOPT_NEUTRAL)
	var x := who.x;
	var y := who.y;
	who.hidden := 0;
	if (npctarget)
		return npctarget;
	endif
	
	if (who.npctemplate)
		return;
	endif
	
	sendsysmessage(who, prompt);
	
	var targ := target(who, ops);
	
	if (who.x == x && who.y == y)
		return targ;
	else
		SendSysMessage(who, "You break your concentration.");
		return 0;
	endif
endfunction

function ClericalTargetCoordinates(byref who, byref params := "", prompt := "Select a target")
	var x := who.x;
	var y := who.y;
	who.hidden := 0;
	if (params[3])
		return params[3];
	endif
	if (who.npctemplate)
		return;
	endif
	sendsysmessage(who, prompt);
	var targ := targetcoordinates(who);
	
	if (who.x == x && who.y == y)
		return targ;
	else
		SendSysMessage(who, "You lose concentration");
		return 0;
	endif
endfunction

function GetFacing(who, targx, targy, targz)
	var ns_desc := "";
	var ew_desc := "";
	var thedesc;
	
	if (targy < who.y)
		ns_desc := "north";
	elseif  (targy > who.y)
		ns_desc := "south";
	endif
	
	if (targx < who.x)
		ew_desc := "west";
	elseif  (targx > who.x)
		ew_desc := "east";
	endif
	
	if (ns_desc = "" and ew_desc = "")
		thedesc := "nearby";
	else
		thedesc := ns_desc + ew_desc ;
	endif
	return thedesc;
endfunction

function IsCleric(who)
	var config := ReadConfigFile("clerics");
	if (!config)
		SendSysMessage(who, "Can not read in clerics.cfg");
	endif
	config := config["classes"];
	
	foreach class in GetConfigStringArray(config, "class")
		if (lower(class) == lower(GetObjProperty(who, "class")))
			return 1;
		endif
	endforeach
	
	return 0;
endfunction

function FocusType(word)
	// You can send this the focus name
	// it will return the objtype of it
	word := lower(word);
	
	if (word == "power focus")
		return POWER_FOCUS;
	elseif (word == "spirit focus")
		return SPIRIT_FOCUS;
	elseif (word == "arcane focus")
		return ARCANE_FOCUS;
	elseif (word == "time focus")
		return TIME_FOCUS;
	elseif (word == "earth focus")
		return EARTH_FOCUS;
	elseif (word == "life focus")
		return LIFE_FOCUS;
	endif
endfunction

function FocusName(number)
	// You can send this the focus objtype
	// it will return the name of it
	
	if (number == POWER_FOCUS)
		return "power focus";
	elseif (number == SPIRIT_FOCUS)
		return "spirit focus";
	elseif (number == ARCANE_FOCUS)
		return "arcane focus";
	elseif (number == TIME_FOCUS)
		return "time focus";
	elseif (number == EARTH_FOCUS)
		return "earth focus";
	elseif (number == LIFE_FOCUS)
		return "life focus";
	endif
endfunction

function CheckMana(who, amount)
	if (who.mana >= amount)
		who.mana := (who.mana - amount);
		return 1;
	else
		return 0;
	endif
endfunction

function DistanceCheck(who, targ, range)
	if (who.npctemplate)
		return 1;
	elseif (distance(who, targ) <= range)
		return 1;
	else
		return 0;
	endif
endfunction

function ReleaseScript(pid)
	var process := GetProcess(pid);
	process.SendEvent("done");
endfunction