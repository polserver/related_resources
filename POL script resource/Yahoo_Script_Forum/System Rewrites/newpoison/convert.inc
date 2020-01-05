use cfgfile;
use util;
use basic;

/*
include "include/convert";
getSkill(who, SKILLID_WHATEVER): newGetSkill(who, SKILLID_WHATEVER)

who.strength : getStr(who) setStr(who, amount)
who.intelligence: getInt(who) strInt(who, amount)
who.dexterity: getDex(who) setDex(who, amount)

who.int_mod: getIntMod(who) setIntMod(who, amount)
who.str_mod: getStrMod(who) setStrMod(who, amount)
who.dex_mod: getDexMod(who) setDexMod(who, amount)

who.hp: getHP(who) setHp(who, amount)
who.maxhp: getMaxHp(who) 

who.stamina: getStam(who) setStam(who, amount)
who.maxstamina: getMaxStam(who)

who.mana: getMana(who) setMana(who, amount)
who.maxmana: getMaxMana(who)

who.hp_regen_rate : getOldHpRegenRate(who)           setOldHpRegenRate(who, amount)
who.stamina_regen_rate : getOldStaminaRegenRate(who) setOldStaminaRegenRate(who, amount)
who.mana_regen_rate : getOldManaRegenRate(who)       setOldManaRegenRate(who, amount)

helper functions: 
	getAttributeForSkillId: returns the attribute name (ie "Magery") for a skill ID

*/

use uo;

function getnewSkillIdForAttribute(attribute)
var cf := readconfigfile(":*:attributes");
return cf[attribute].skillid;
endfunction

function incstrmod(who, amt)
	setstrmod(who, getstrmod(who) + amt);
endfunction
function incdexmod(who, amt)
	setdexmod(who, getdexmod(who) + amt);
endfunction
function incintmod(who, amt)
	setintmod(who, getintmod(who) + amt);
endfunction

function newSetRawSkill(who, skillid, value)
local at := GetAttributeForSkillIdd(skillid);
local v := rawskilltobaseskill(value);
setattributebasevalue(who, at, v);

endfunction



function LowerStam(who, amount := 1)
	syslog(who.name + " has " + getstam(who) + " amount is " + amount);
	local hisstam := getstam(who);
	hisstam := hisstam - amount;
	if (hisstam < 0)
		setstam(who, 0);
	else
		
		setstam(who, hisstam);
	endif
	return getstam(who);
endfunction

function Lowermana(who, amount := 1)
	if ((getmana(who) - amount) < 0)
		setmana(who, 0);
	else
		setmana(who, getmana(who) - amount);
	endif
	return getmana(who);
endfunction



function Lowerhp(who, amount := 1)
	if ((gethp(who) - amount) < 0)
		sethp(who, 0);
	else
		sethp(who, gethp(who) - amount);
	endif
	return gethp(who);
endfunction

function incmana(who, amt)
	local m := getmana(who);
	local newm := m + amt;
	if (newm < 0)
		setmana(who, 0);
		return;
	endif
	if (newm > getmaxmana(who))
		setmana(who, getmaxmana(who));
		return;
	endif
	setmana(who, newm);
endfunction

function NewGetSkill(who, skillid)
	return getAttributebasevalue(who, getAttributeForSkillIdd(skillid))/10.0;
endfunction

function setOldHpRegenRate(who, amt)
	return setVitalRegenRate(who, "Life", amt * 12);
endfunction

function setOldStaminaRegenRate(who, amt)
	return setVitalRegenRate(who, "Stamina", amt * 12);
endfunction

function setOldManaRegenRate(who, amt)
	return setVitalRegenRate(who, "Mana", amt * 12);
endfunction

function getOldHpRegenRate(who)
	return GetVitalRegenRate( who,"Life" ) / 12;
endfunction

function getOldStaminaRegenRate(who)
	return GetVitalRegenRate( who,"Stamina" ) / 12;
endfunction

function getOldManaRegenRate(who)
	return GetVitalRegenRate( who,"Mana" ) / 12;
endfunction

function getMaxHp(who)
	return GetVitalMaximumValue( who, "Life" )/100.0 ;
endfunction

function getMaxStam(who)
	return GetVitalMaximumValue( who, "Stamina" )/100.0  ;
endfunction

function getMaxMana(who)
	return GetVitalMaximumValue( who, "Mana" ) /100.0 ;
endfunction

function setMana(who, amount)
	if (who.name["stin"])
		syslog("Mana is now " + getmana(who) + " trying to set it to " + amount);
	endif
	SetVital( who, "Mana", cint(amount * 100.0) );
	if (who.name["stin"])
		syslog("After change mana is now " + getmana(who) );
	endif
endfunction

function setHP(who, amount)
	SetVital( who, "Life", amount * 100 );
endfunction

function setStam(who, amount )
	local ret := SetVital( who, "Stamina", amount* 100);
	return ret; 
endfunction

function GetHp(who)
	return getVital(who, "Life")/100.0 ;
endfunction

function getMana(who)
	return getVital(who, "Mana")/100.0 ;
endfunction

function getStam(who)
	return getVital(who, "Stamina")/100.0 ;
endfunction

function GetAttributeForSkillIdd(skilld)
	local s := readconfigfile(":*:skills");
	return s[skilld].attribute;
endfunction

function setStrMod(who, amount)
	tell(who, "Setting str mod to " + amount);
	return setAttributeTemporaryMod(who, "Strength", amount /10  );
endfunction

function setIntMod(who, amount)
	return setAttributeTemporaryMod(who, "Intelligence", amount /10  );
endfunction

function setDexMod(who, amount)
	return setAttributeTemporaryMod(who, "Dexterity", amount/10  );
endfunction


function getIntMod(who)
	return GetAttributeTemporaryMod( who, "Intelligence" ) ;
endfunction

function getDexMod(who)
	return GetAttributeTemporaryMod( who, "Dexterity" )  ;
endfunction

function getStrMod(who)
	return GetAttributeTemporaryMod( who, "Strength" )  ;
endfunction


function getStr(who)
	return getAttribute(who, "Strength");
endfunction

function getInt(who)
	return getAttribute(who, "Intelligence");
endfunction

function getDex(who)
	return getAttribute(who, "Dexterity");
endfunction

function setStr(who, amount)
	return setattributebasevalue(who,"Strength",  amount*10);
endfunction

function setInt(who, amount)
	return setattributebasevalue(who,"Intelligence", amount*10);
endfunction

function setDex(who, amount)
	return setattributebasevalue(who,"Dexterity",  amount*10);
endfunction


function tell(who, msg)
	if (who.cmdlevel)
		sendsysmessage(who, msg);
	endif
endfunction