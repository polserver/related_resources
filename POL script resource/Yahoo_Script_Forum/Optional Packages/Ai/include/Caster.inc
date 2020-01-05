///////////////////////////////////////////////////////////
// Caster.inc
//
// Spell caster main processing.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use os;
use npc;
use util;
use basic;
use cfgfile;

include "include/statmod";

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const 	SPELLPKG	:= ":spells:";
const 	SPELLSCFG	:= ":spells:spells";
const 	CIRCLECFG	:= "::circles";
const	NPCSPELLCFG	:= ":ai:/npcspells/NpcSpells";

const 	OFFENSIVE	:= "Offensive";
const	DEFENSIVE	:= "Defensive";
const	OTHER		:= "Other";

const 	SPELLCIRCLEDIVISOR := 8;

///////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////
var spellscfg := ReadConfigFile(SPELLSCFG);	// NpcSpells config.
var circlecfg := ReadConfigFile(CIRCLECFG);	// Circle config.
var offensive;	// Offensive spell array.
var defensive;	// Defensive spell array.
var other;		// Other spell array/
var spellids;	// SpellID dictionary Key = SpellScript  Val = SpellID
var NextCast := ReadGameClock();	// Next time I can cast a spell.

///////////////////////////////////////////////////////////
// GLOBAL CODE - Reads in NPCs spell lists.
///////////////////////////////////////////////////////////
if (mydesc.castpct)
	offensive := array;
	defensive := array;
	other := array;
	spellids := dictionary;

	var npcspells := ReadConfigFile(NPCSPELLCFG);

	var circleelem;
	var spelldat;
	var circle;
	for (circle := 1; circle <= mydesc.castcircle; circle := circle + 1)
		circleelem := FindConfigElem(npcspells, circle);

		// Read in offensives.
		var offspells := GetConfigStringArray(circleelem, OFFENSIVE);
		foreach offsp in offspells
			spelldat := SplitWords(offsp);
			offensive.append(CInt(spelldat[2]));
			spellids[spelldat[1]] := CInt(spelldat[2]);
		endforeach

		// Read in defensives.
		var defspells := GetConfigStringArray(circleelem, DEFENSIVE);
		foreach defsp in defspells
			spelldat := SplitWords(defsp);
			defensive.append(CInt(spelldat[2]));
			spellids[spelldat[1]] := CInt(spelldat[2]);
		endforeach

		// Read in other.
		var otrspells := GetConfigStringArray(circleelem, OTHER);
		foreach otrsp in otrspells
			spelldat := SplitWords(otrsp);
			other.append(CInt(spelldat[2]));
			spellids[spelldat[1]] := CInt(spelldat[2]);
		endforeach
	endfor
endif

///////////////////////////////////////////////////////////
// Purpose: Main casting function.
// Params:  tgt		Ref to mobile target,
//					will be undef when not in combat.
// Returns: N/A
///////////////////////////////////////////////////////////
function Cast(byref tgt)
	// Am I a caster and do I have mana?
	if (!mydesc.castpct and me.mana)
		return 0;
	endif

	// Is it time to try to cast this cycle?
	var casttime := ReadGameClock();
	if (NextCast > casttime)
		return 0;
	endif
	NextCast := casttime + ai.CastFrequency;

	// Heal myself if I need it.
	if ((me.hp * 100/me.maxhp) < ai.WhenToHeal)
		CastHeal(me);
		return 1;
	endif

	// Cure myself.
	if (Poisoned(me))
		CastCure(me);
		return 1;
	endif

	// Do I cast this cycle?
	var chance := RandomInt(100);
	if (me.warmode)
		if (chance > mydesc.castpct)
			return 0;
		endif
	else // In noncombat, I cast at only half frequency.
		if (RandomInt(100) > (mydesc.castpct / 2))
			return 0;
		endif
	endif

	CastMagic(tgt);

	return 1;
endfunction



///////////////////////////////////////////////////////////
// Purpose: Cast a spell.  Offensives  and Defensives will
//			be cast when warmode is set, Defensive and Other
//			when not in	warmode.
// Params:  tgt		Ref to mobile target if needed.
// Returns: N/A
///////////////////////////////////////////////////////////
function CastMagic(byref tgt)
	var type := RandomInt(10);
	var spells;

	// Determine type of spell to cast.
	if (me.warmode)
		case (type)
			0: 1: 2: 3: 4: 5: 6: 7: 8:
				spells := offensive;

			default:
				spells := defensive;
		endcase
	else
		case (type)
			0: 1: 2: 3: 4: 5: 6: 7: 8:
				spells := defensive;

				// If grouped, chance of casting spell on groupmember.
				if (mygroup.size() > 0 and RandomInt(3) = 1)
					var bud := mygroup[RandomInt(mygroup.size() - 1) + 1];
					tgt := SystemFindObjectBySerial(bud);
				endif

			default:
				spells := other;
		endcase
	endif

	// In case there are no spells of that type available to this NPC.
	if (spells.size() = 0)
		return;
	endif

	// Choose a specific spell and cast it.
	var spelltocast := spells[RandomInt(spells.size() - 1) + 1];
	if (!spelltocast)
		return 0;
	endif

	CastMagicSpell(me, tgt, spelltocast);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Casts a magic spell
// Params:  caster		Ref to mobile caster.
//			tgt			Ref to mobile target.
//			spellid		Ref to the spellid being cast.
// Returns: N/A
///////////////////////////////////////////////////////////
function CastMagicSpell(byref caster, byref tgt, spellid)
	if (!spellid)
		return 0;
	endif

	var delay := GetDelayAndDeductMana(spellid);
	if (!delay)
		return 0;
	endif

	var params := array;
	params[1] := "#MOB";
	params[2] := me;
	params[3] := tgt;

	if (ai.SpeakWords)
		Say(spellscfg[spellid].PowerWords);
	endif

	sleepms(delay);

	start_script(SPELLPKG + spellscfg[spellid].Script, params);

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Casts a heal spell on the mobile.
// Params:  mobile		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function CastHeal(byref mobile)
	if ((mobile.hp * 100 / mobile.maxhp < ai.WhenToHeal) and CanCast("gheal"))
		CastMagicSpell(me, mobile, spellids["gheal"]);
		return 1;
	endif

	if (CanCast("heal")) // Try casting heal...
		CastMagicSpell(me, mobile, spellids["heal"]);
	endif

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Cures a mobile
// Params:  mobile		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function CastCure(byref mobile)
	if (CanCast("cure"))
		CastMagicSpell(me, mobile, spellids["cure"]);
	endif

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Checks if I can cast that spell.
// Params:  spellname		Name of the spell script.
// Returns: 0		Can't cast it.
//			1		Can cast it.
///////////////////////////////////////////////////////////
function CanCast(spellname)
	if (spellids.exists(spellname))
		return 1;
	endif

	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Tells if poisoned.
// Params:  mobile		Ref to mobile
// Returns: 1		Poisoned.
//			0		not poisoned.
///////////////////////////////////////////////////////////
function Poisoned(byref mobile)
	if (GetObjProperty(mobile, "poison_level") or mobile.poisoned)
		return 1;
	endif
	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Deducts mana for the casting of the spell and
//			returns the delay of the spell.
// Params:  spellid		SpellID being cast.
// Returns: delay	Delay for the spell.
//			0		Not enough mana!
//////////////////////////////////////////////////////////
function GetDelayAndDeductMana(spellid)
	var circle := spellid / SPELLCIRCLEDIVISOR;
	if (circle < 1)
		circle := 1;
	endif

	var manacost := circlecfg[circle].Mana;

	if (me.mana <= manacost)
		return 0;
	endif

	me.mana := me.mana - manacost;

	return circlecfg[circle].Delay;
endfunction

