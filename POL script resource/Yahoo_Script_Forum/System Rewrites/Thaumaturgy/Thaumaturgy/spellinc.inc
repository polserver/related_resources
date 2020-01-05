
use uo;
use cfgfile;

function BrokeCon(who)

	if (who.hp < GetObjProperty(who, "#casthp"))
		return 1;
	endif

	return 0;

endfunction

function CleanUp(who)

	EraseObjProperty(who, "#casting");
	EraseObjProperty(who, "#casthp");

endfunction

function DoCast(who, magicid)

	var casterops := GetObjProperty(who, "casterops");
	
	var spellcfg := ReadConfigFile("::spells");
	var elem := FindConfigElem(spellcfg, magicid);
	var circle := GetConfigInt(elem,"Circle");

	var circfg := ReadConfigFile("::circles");
	var cirelem := FindConfigElem(circfg,circle);	
	var diff := GetConfigInt(cirelem,"Difficulty");
	var points := GetConfigInt(cirelem,"PointValue");

	if (!casterops["NOMANA"])
		if (!ConsumeMana(who,magicid))
			PlayObjectCenteredEffect(who, FX_SPELL_FAIL, 7, 7);
			PlaySoundEffect(who, SFX_5B);
			SendSysMessage(who, "Insufficient mana.");
			return 1;
		endif
	endif

	if (magicID > 108)
	    if (!casterops["NOSKILL"])
		if (!CheckSkill(who, SKILLID_THAUMATURGY, diff, points))
			PlayObjectCenteredEffect(who, FX_SPELL_FAIL, 7, 7);
			PlaySoundEffect(who, SFX_5B);
			return 1;
		endif
	    endif
	endif

	if (!casterops["NOREGS"])
		if (!ConsumeReagents(who,magicid))
			PlayObjectCenteredEffect(who, FX_SPELL_FAIL, 7, 7);
			PlaySoundEffect(who, SFX_5B);
			SendSysMessage(who, "Insufficient reagents.");
			return 1;
		endif
	endif

	return 0;
	
endfunction