function castspell( caster, cast_on, spellname )

	case (spellname)
	"summonskel":
		if ( summons > 0 )
			SummonSkel(caster,cast_on);
			summons := summons -1;
		endif
	
	default:
		local SpellID := GetSpellID(spellname);
		if (!spellID)
			return;
		endif

		If (!PrepareToCast(caster,cast_on,spellid))
			return;
		endif

		local parms :={};
		parms[1] := "#MOB";
		parms[2] := caster;
		parms[3] := cast_on;

		detach();

		start_script( ":spells:"+spellname, parms ); 
	endcase

endfunction

function SummonSkel(me, onwho)

	local utterance := randomint(4);

	case (utterance)
        	0: say("Awake, my children! Come forth and take your rightful place!");
        	1: say("Come forth my minions!");
        	2: say("I call upon the forces of darkness to attend me!");
        	3: say("Mortal, you shall soon be my slave!");
	endcase

	local c1 := createnpcfromtemplate("skeleton", me.x, me.y -2, me.z, 0);
	SetObjProperty(c1,"summoned",1);
	EraseObjProperty(c1,"looter");

	local c2 := createnpcfromtemplate("zombie", onwho.x, onwho.y - 1, onwho.z, 0);
	SetObjProperty(c2,"summoned",1);
	EraseObjProperty(c2,"looter");

	local c3 := createnpcfromtemplate("skeleton", me.x, me.y + 1, me.z, 0);
	SetObjProperty(c3,"summoned",1);
	EraseObjProperty(c3,"looter");

endfunction

Function GetSpellID(spellname)

	local spellid := 0;

	case (spellname)
	"clumsy"	: spellid := 1;
	"feeblemind"	: spellid := 3;
	"heal"		: spellid := 4;
	"magicarrow"	: spellid := 5;
	"nightsight"	: spellid := 6;
	"reactivearmor"	: spellid := 7;
	"weaken"	: spellid := 8;
	"agility"	: spellid := 9;
	"cunning"	: spellid := 10;
	"cure"		: spellid := 11;
	"harm"		: spellid := 12;
	"protection"	: spellid := 15;
	"strength"	: spellid := 16;
	"bless"		: spellid := 17;
	"fireball"	: spellid := 18;
	"poison"	: spellid := 20;
	"teleport"	: spellid := 22;
	"wallofstone"	: spellid := 24;
	"archcure"	: spellid := 25;
	"archprot"	: spellid := 26;
	"curse"		: spellid := 27;
	"firefield"	: spellid := 28;
	"gheal"		: spellid := 29;
	"lightning"	: spellid := 30;
	"manadrain"	: spellid := 31;
	"blade_spirit"	: spellid := 33;
	"dispel_field"	: spellid := 34;
	"reflect"	: spellid := 36;
	"mindblast"	: spellid := 37;
	"paralyze"	: spellid := 38;
	"poisonfield"	: spellid := 39;
	"summon_creature": spellid := 40;
	"dispel"	: spellid := 41;
	"ebolt"		: spellid := 42;
	"explosion"	: spellid := 43;
	"invisibility"	: spellid := 44;
	"masscurse"	: spellid := 46;
	"parafield"	: spellid := 47;
	"reveal"	: spellid := 48;
	"chain_lightning": spellid := 49;
	"energy_field"	: spellid := 50;
	"fstrike"	: spellid := 51;
	"manavamp"	: spellid := 53;
	"massdispel"	: spellid := 54;
	"meteor_swarm"	: spellid := 55;
	"polymorph"	: spellid := 56;
	"earthquake"	: spellid := 57;
	"vortex"	: spellid := 58;
	"resurrect"	: spellid := 59;
	"summon_air"	: spellid := 60;
	"summon_daemon"	: spellid := 61;
	"summon_earth"	: spellid := 62;
	"summon_fire"	: spellid := 63;
	"summon_water"	: spellid := 64;
	endcase

	return spellid;
	
endfunction

function PrepareToCast(caster, cast_on, spellid)

	if (!CheckLineOfSight( caster, cast_on ))
		return 0;
	endif
	if (! ConsumeMana( caster, spellid ))
		return 0;
	endif
	if (saywords)
		SpeakPowerWords( me, spellid);
		PerformAction(caster,ANIM_CAST_DIR);
		sleep(1);
	endif

	if (GetSkill(caster, SKILLID_MAGERY))
		if (!CheckSkill(caster, SKILLID_MAGERY, GetSpellDifficulty( spellid ), 0 ))
			PlaySoundEffect(caster,0x005d);
			PlayObjectCenteredEffect(caster, 0x3735,0x0a, 0x1e);
			return 0;
		endif
	endif

	return 1;

endfunction

function cast_offensive_spell(caster, cast_on)

	local thespell;

	if (GetObjProperty(cast_on, "summoned"))
		thespell := "dispel";
		syslog("cast_offensive sysfind: "+pack(cint(getobjproperty(cast_on, "master"))));
		local nexttarget := SystemFindObjectBySerial(cint(getobjproperty(cast_on, "master")));
		CastSpell(caster, cast_on, thespell);
		if(nexttarget)
			fightqueue.append(nexttarget.serial);
		endif
		return;
	endif

	thespell := spells[randomint( len(spells) +1 )];
	CastSpell(caster, cast_on, thespell);

endfunction