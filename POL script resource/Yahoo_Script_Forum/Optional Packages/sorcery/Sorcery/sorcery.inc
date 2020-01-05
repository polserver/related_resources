use uo;
use os;
use cfgfile;
use util;

include "include/attributes";

function SpellDamage(circle, caster, cast_on)
  var die_string := circle+"d8";
  var dmg := RandomDiceRoll(die_string);
  dmg := dmg + CInt(GetEffectiveSkill(caster, SKILLID_MAGERY)/10) + CInt(GetEffectiveSkill(caster, SKILLID_EVALINT)/10);
  if(cast_on.npctemplate)
      var adjust := GetObjProperty(cast_on, "str");
      	if(adjust <= 100);
	    dmg := dmg * 4;
	    ApplyRawDamage(cast_on, dmg);
	    return;
	endif
      dmg := dmg * 2;
  endif
  ApplyRawDamage(cast_on, dmg);
endfunction

function sorcopts(circle, caster)

  var umana, diff, spelldelay;
  var mana := GetMana(caster);
  
  case(circle)
  
  	1: umana := 10; diff := 60; spelldelay := 1;
  	2: umana := 20; diff := 70; spelldelay := 2;
  	3: umana := 30; diff := 80; spelldelay := 3;
  	4: umana := 40; diff := 90; spelldelay := 4;
  	5: umana := 50; diff := 100; spelldelay := 5;
  
  endcase
  
  While (spelldelay > 0)
	PerformAction(caster, ANIM_CAST_DIR);
	sleep(1);
	spelldelay := spelldelay - 1;
	caster.frozen := 1;
  endwhile
  	caster.frozen := 0;
  	
  var points := diff*5;
  
  if( !CheckSkill(caster, SKILLID_MAGERY, diff, points))
  	PlayObjectCenteredEffect(caster, FX_SPELL_FAIL, 7, 7);
	PlaySoundEffect(caster, SFX_5B);
	return 0;
  else
  	SetMana(caster, Cint(mana - umana));
  	return 1;
  endif
  
endfunction
  
  