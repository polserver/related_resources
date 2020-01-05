const EVID_ADDPOISON 	:= 78;
const EVID_CUREPOISON 	:= 79;
const EVID_DEAD 	:= 80;
const EVID_LOGOFF 	:= 81;
const EVID_CUREDISEASE := 82;
const EVID_REMOVECURSE := 83;
const EVID_CURETRUE := 84;

function died(who)
	local proc := getPoisonScript(who);
	if (!proc)
		return;
	endif
	local ev := struct;
	ev.+type;
	ev.type := EVID_DEAD;
	proc.sendevent(ev);

endfunction

function CureTrue(who, type)
	local ev := struct;
	ev.+type;
	ev.+poisontype;
	ev.type := EVID_CURETRUE ;
	ev.poisontype := type;
	local proc := getPoisonScript(who);
		if (!proc)
			return;
		endif
	proc.sendevent(ev);
endfunction
	


function getPoisonScript(who)
	local poisonpid := getobjproperty(who, "poisonscript");
	if (!poisonpid)
		return;
	endif
	return getprocess(cint(poisonpid));
endfunction

function getPoisons(who)
local poisons := getobjproperty(who, "poisons");
//returns a list of poisons with their virulence
local e := struct;
e.+name;
e.+type;
e.+virulence;
local ret := {};
local p;

local k := poisons.keys();
foreach p in k
	local t := poisons[p];
	if (!t.type || t.type = "P")
		e.name := t.name;
		e.type := p;
		e.virulence := t.virulence;
		ret.append(e);
	endif
endforeach
return ret;
endfunction

function getDiseases(who)
local poisons := getobjproperty(who, "poisons");
//returns a list of poisons with their virulence
local e := struct;
e.+name;
e.+type;
e.+virulence;
local ret := {};
local p;

local k := poisons.keys();
foreach p in k
	local t := poisons[p];
	if ( t.type = "D")
		e.name := t.name;
		e.type := p;
		e.virulence := t.virulence;
		ret.append(e);
	endif
endforeach
return ret;
endfunction

function getCurses(who)
local poisons := getobjproperty(who, "poisons");
//returns a list of poisons with their virulence
local e := struct;
e.+name;
e.+type;
e.+virulence;
local ret := {};
local p;

local k := poisons.keys();
foreach p in k
	local t := poisons[p];
	if ( t.type = "C")
		e.name := t.name;
		e.type := p;
		e.virulence := t.virulence;
		ret.append(e);
	endif
endforeach
return ret;
endfunction


function addpoison(who, poisontype, duration)
	
	var cfg := readconfigfile(":*:newpoison");
	if (!cfg)
		syslog("Gah! Couldn't read newpoison.cfg!");
		return;
	endif
	
	var elem := cfg[poisontype];
	if (!elem)
		syslog("Wahh! I was told to poison with " + poisontype + " but didn't find it in the file");
		return;
	endif
	
	var pid := getprocess(cint(getobjproperty(who, "poisonscript")));
	
	if (!pid)
		pid := start_script(":newpoison:poisonwatcher", {who});
	endif
	
	if (!pid)
		syslog("Damn, couldn't find pid");
	endif
	
	var ev := struct;
	ev.+poisontype;
	ev.+duration;
	ev.+virulence;
	ev.+type;
	ev.+death;
	ev.+nocure;
	ev.+noend;
	ev.+cureskill;
	ev.+curetype;
	ev.+curescript;
	ev.+killscript;
	ev.+ttype;
	ev.+name;
	ev.type := EVID_ADDPOISON;
	ev.duration := duration;
	ev.virulence := elem.virulence;
	ev.poisontype := elem.script;
	ev.curetype := elem.CureType;
	ev.cureskill := elem.CureSkill;
	ev.death := cint(elem.ContinueOnDeath);
	ev.nocure := cint(elem.NoCure);
	ev.noend := cint(elem.NoEnd);
	ev.ttype := elem.Type;
	ev.curescript :=  elem.CureScript ;
	ev.killscript :=  elem.KillScript ;
	ev.name := elem.name;
	 
	pid.sendevent(ev);
	return duration;
endfunction

function logoff(who)
var proc := getPoisonScript(who);
var ev := struct;
ev.+type;
ev.type := EVID_LOGOFF;

proc.sendevent(ev);
endfunction


function curepoison(who, amount)

	local ev := struct;
	ev.+type;
	ev.+virulence;
	ev.type := EVID_CUREPOISON;
	ev.virulence := cint(amount);

	var spid := getpoisonscript(who);
	local ret := spid.sendevent(ev);
	
endfunction


function curedisease(who, amount)

	local ev := struct;
	ev.+type;
	ev.+virulence;
	ev.type := EVID_CUREDISEASE
	ev.virulence := cint(amount);

	var spid := getpoisonscript(who);
	local ret := spid.sendevent(ev);
	
endfunction


function removecurse(who, amount)

	local ev := struct;
	ev.+type;
	ev.+virulence;
	ev.type := EVID_REMOVECURSE;
	ev.virulence := cint(amount);

	var spid := getpoisonscript(who);
	local ret := spid.sendevent(ev);
	
endfunction

function getVirulence(who)
local p := getobjproperty(who, "poisons");
if (!p)
	return 0;
endif
var total := 0;
var tpo;
var k := p.keys();
foreach tpo in k
	local thispoison := p[tpo];
	total := total + ((p.timeout - readgameclock()) * p.virulence);
endforeach 
return total;

endfunction