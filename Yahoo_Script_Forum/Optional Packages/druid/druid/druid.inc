include "include/attributes";

///////////////////
//  tries to cast the specified druid spell
///////////////////

function CastDruidSpell (caster, staff, spellid)

	if (GetObjProperty (caster, "#useskill"))
		if (GetProcess (GetObjProperty (caster, "#useskill")))
			PrintTextAbovePrivate (caster, "I am already performing another action.", caster);
			return;
		endif
	endif
	
	//load the config file
	local spell_cfg_file:= ReadConfigFile ("spells");
	local current_spell := FindConfigelem (spell_cfg_file,spellid);
	local circle := FindSpellCircle (spellid);
	
	//save the player's position
	local casterx := caster.x;
	local castery := caster.y;
	caster.hidden := 0;

	//play the animations
	local animation := GetConfigStringArray (current_spell, "animation");
	foreach motion in animation
		PerformAction( caster, cint(motion));
		sleepms(1500);
		if (casterx != caster.x or castery != caster.y)
			EraseObjProperty (caster, "#castingdruidspell");
			return 0;
		endif
	endforeach

	//do a skill check
	local difficulty := GetSpellDifficulty (spellid);
	if (!CheckSkill (caster, SKILLID_MAGERY, difficulty, 0))
		return 0;
	endif

//	//make sure the caster has enough mana
//	if (!ConsumeMana (caster, spellid))
//		PrintTextAbovePrivate (caster, "*Not enough mana*", caster);
//		return 0;
//	endif

	//consume the reagents
	//the "#noreagents" prop is set if the caster was a GM and declared that they didn't need reagents
	if (!GetObjProperty(caster, "#noreagents"))
		//go through all the reagents
		local reagents := GetConfigStringArray (current_spell, "reagent");
		local reg, amt, regline;
		foreach reagent in reagents
			regline := splitwords(reagent);
			reg := cint(regline[1]);
			amt := cint(regline[2]);
			if (!ConsumeSubstanceIsBroken(caster, reg, amt))
				PrintTextAbovePrivate(caster, "Not enough reagents", caster);
				return 0;
			endif
		endforeach
	endif

	//save the property "#castingdruidspell".  This is done in order to avoid casting more than
	//one spell at a time
	SetObjProperty (caster, "#castingdruidspell", 1);

	ReduceCastersNecroSkill (caster);
	detach();
	StartSpellEffect (caster, spellid);
	return 1;
endfunction




///////////////////
//  Reduce's the caster's necro skill for casting a druid spell
//////////////////

function ReduceCastersNecroSkill (caster)
	local skillval := GetAttributeBaseValue (caster, ATTRIBUTEID_NECROMANCY);
	if (skillval)
		skillval := CINT (skillval*0.99);
		SetAttributeBaseValue (caster, ATTRIBUTEID_NECROMANCY, skillval);
	endif
endfunction




///////////////////
//  temporary function until Consume Substance is fixed
///////////////////

function ConsumeSubstanceIsBroken (caster, what, amt)
	local mystuff := HasReagents (caster, what, amt);
	if (!mystuff)
		return 0;
	else
		SubtractAmount(mystuff,amt);
		return 1;
	endif
endfunction

function HasReagents(caster, what, amt)
	foreach item in EnumerateItemsInContainer (caster.backpack)
		if ( (item.objtype = what)  and (item.amount >= amt) )
			return item;
		endif
	endforeach

	return 0;
endfunction




///////////////////
//  Put the rune ojbtype in the bag specified.  Doesn't check to make sure its a valid rune.
///////////////////

function PutRuneInBag (bag, rune_objtype)
	local rune_array := GetObjProperty (bag, "runes");
	if (!rune_array)
		rune_array := {};
	endif

	foreach rune in rune_array
		if (cint(rune) = cint(rune_objtype) )
			return 0;
		endif
	endforeach

	rune_array.append (rune_objtype);
	SetObjProperty (bag, "runes", rune_array);

	return 1;
endfunction



///////////////////
//  takes the rune objtype out of the bag.  Doesn't check to make sure its a valid rune
///////////////////

function TakeRuneOutOfBag (bag, rune_objtype)
	local rune_array := GetObjProperty (bag, "runes");
	if (!rune_array)
		return 0;
	endif

	local new_rune_array := {};

	foreach rune in rune_array
		if (rune and cint(rune) != cint (rune_objtype))
			new_rune_array.append (rune);
		endif
	endforeach

	SetObjProperty (bag, "runes", new_rune_array);
	return 1;
endfunction




///////////////////
//  checks to see if the runeobjtype is in the bag
///////////////////

function CheckForRuneInBag (bag, rune_objtype)
	local rune_array := GetObjProperty (bag, "runes");
	if (!rune_array)
		return 0;
	endif

	foreach rune in rune_array
		if ( cint(rune) = cint (rune_objtype) )
			return 1;
		endif
	endforeach

	return 0;
endfunction

//Druidry manausage

function usemana(caster, circle)
var umana, diff;
var mana := GetMana(caster);

	case(circle)
		1: umana := 10;
		2: umana := 20;
		3: umana := 30;
		4: umana := 40;
		5: umana := 50;
	endcase
	
    SetMana(caster, Cint(mana - umana));
endfunction

function checkdruidopts(caster, circle)

	var diff, spelldelay;

	case(circle)
		1: diff := 50; spelldelay := 2;
		2: diff := 60; spelldelay := 3;
		3: diff := 70; spelldelay := 4;
		4: diff := 80; spelldelay := 5;
		5: diff := 90; spelldelay := 6;
	endcase
	
	While (spelldelay > 0)
		PerformAction(caster, ANIM_CAST_DIR);
		sleep(1);
		spelldelay := spelldelay - 1;
		caster.frozen := 1;
  	endwhile
		caster.frozen := 0;
	
	var points := diff*5;
	
	  
  	if( !CheckSkill(caster, SKILLID_ANIMALLORE, diff, points))
  		PlayObjectCenteredEffect(caster, FX_SPELL_FAIL, 7, 7);
		PlaySoundEffect(caster, SFX_5B);
		return;
  	endif
  
	
endfunction

function checkstaff(caster)

	var staffequip := GetEquipmentByLayer(caster, LAYER_HAND2);

	if(staffequip.objtype != 0x700a)
		SendSysMessage(caster, "Heretic! You need your earthen staff!");
		ApplyRawDamage(caster, "2d30");
		return 0;
	else
		return 1;
	endif

endfunction