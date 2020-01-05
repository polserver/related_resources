
use uo;
use cfgfile;

function BrokeCon(who)

	if (who.hp < GetObjProperty(who, "#casthp"))
		return 1;
	endif

	return 0;

endfunction

function CleanUp(who)

	EraseObjProperty(who, "#casthp");

endfunction

function DoCast(who, magicid)

	if (BrokeCon(who))
		SendSysMessage(caster, "You have lost your concentration.");
		return 0;
	endif

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
			return 0;
		endif
	endif


	if (!casterops["NOSKILL"])
		if (!CheckSkill(who, SKILLID_MAGERY, diff, points))
			PlayObjectCenteredEffect(who, FX_SPELL_FAIL, 7, 7);
			PlaySoundEffect(who, SFX_5B);
			return 0;
		endif
	endif

	if (!casterops["NOREGS"])
		if (!ConsumeReagents(who,magicid))
			PlayObjectCenteredEffect(who, FX_SPELL_FAIL, 7, 7);
			PlaySoundEffect(who, SFX_5B);
			SendSysMessage(who, "Insufficient reagents.");
			return 0;
		endif
	endif

	return 1;
	
endfunction

function hasReagents(who, regs)
	var regtypes := regsToObjtypes(regs);
	var stuff := EnumerateItemsInContainer(who.backpack);
	foreach item in stuff
		if (regtypes[item.objtype])
			regtypes.erase(item.objtype);
		endif
	endforeach
	if (!((regtypes.keys()).size()))
		return 1;
	else
		return 0;
	endif
endfunction

function regsToObjtypes(components)

	var regtypes := dictionary;
	foreach regs in components
		regs := lower(regs);
		syslog(regs);
	        case (regs)
		    "batwing":         regtypes[0xF78] := 1;
		    "blackmoor":       regtypes[0xF79] := 1;
		    "blackpearl":      regtypes[0xF7A] := 1;
		    "bloodmoss":       regtypes[0xF7B] := 1;
		    "bloodspawn":      regtypes[0xF7C] := 1;
		    "vialofblood":     regtypes[0xF7D] := 1;
		    "bone":            regtypes[0xF7E] := 1;
		    "brimstone":       regtypes[0xF7F] := 1;
		    "daemonbone":      regtypes[0xF80] := 1;
		    "fertiledirt":     regtypes[0xF81] := 1;
		    "dragonsblood":    regtypes[0xF82] := 1;
		    "executionerscap": regtypes[0xF83] := 1;
		    "garlic":          regtypes[0xF84] := 1;
		    "ginseng":         regtypes[0xF85] := 1;
		    "mandrakeroot":    regtypes[0xF86] := 1;
		    "eyeofnewt":       regtypes[0xF87] := 1;
		    "nightshade":      regtypes[0xF88] := 1;
		    "obsidian":        regtypes[0xF89] := 1;
		    "pigiron":         regtypes[0xF8A] := 1;
		    "pumice":          regtypes[0xF8B] := 1;
		    "sulphurousash":   regtypes[0xF8C] := 1;
		    "spiderssilk":     regtypes[0xF8D] := 1;
		    "spidersilk":      regtypes[0xF8D] := 1;
		    "serpentsscales":  regtypes[0xF8E] := 1;
		    "serpentscales":   regtypes[0xF8E] := 1;
		    "volcanicash":     regtypes[0xF8F] := 1;
		    "deadwood":        regtypes[0xF90] := 1;
		    "wormsheart":      regtypes[0xF91] := 1;
		endcase
	endforeach
	return regtypes;
endfunction
