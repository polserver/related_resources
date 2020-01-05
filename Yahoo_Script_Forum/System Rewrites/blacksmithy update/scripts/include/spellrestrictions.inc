use uo;
use os;
use cfgfile;
use util;
include "include/shaitan";


function can_cast( me, circle)

	//if (!getglobalproperty("restrictarmor")) // commented this out else mage's armor is pointless
        //	return 1;
	//endif

//the following allows for mage's armor
	local chance:= randomint(100);
	local MATotal:= MageArmorTotal(me);
	if ((MATotal > 5) && (chance < 75)) //need all of the magical armor else it wont work. Has a 75% chance of working	    
		SendSysMessage(me, "Your malachite armor enables you to cast that spell");
		return 1;
	endif

	
	local cfg := readconfigfile(":combat:itemdesc");
	local item;

	foreach item in ListEquippedItems(me)
      		if ((cfg[item.objtype].blockcircle) && 
		(cfg[item.objtype].blockcircle <= 1)  // change this 1 to circle, if you wish to have the itemdesc.cfg in pkg/std/combat decide what types of armour make which circles fail.
		&& !cfg[item.objtype].errortext) 
			SendSysmessage(me, "Your equipment prevents you from casting this spell!");
                	return 0;
		endif
	endforeach
return 1;

endfunction

function CanTargetSpell(caster, circle, TargOpt := TGTOPT_CHECK_LOS)

	if (!can_cast(caster, circle))
        	return 0;
	endif

	local cx := caster.x;
	local cy := caster.y;

	local cast_on := Target( caster, TargOpt );
	if(!cast_on  or !cast_on.strength)
		return;
	endif

	if (cx != caster.x or cy != caster.y)
		SendSysMessage(caster,"You've lost your concentration.");
		return 0;
	endif

	return cast_on;	

endfunction

function CanTargetArea(caster, circle)

	if (!can_cast(caster, circle))
        	return 0;
	endif

	local cx := caster.x;
	local cy := caster.y;

	local cast_loc := TargetCoordinates( caster );
	if (!cast_loc.x)
		return 0;
	endif

	if (cx != caster.x or cy != caster.y)
		SendSysMessage(caster,"You've lost your concentration.");
		return 0;
	endif

	if (!CheckLosAt( caster, cast_loc.x, cast_loc.y, cast_loc.z ))
        	SendSysMessage( caster, "You can't see that." );
		return 0;
	endif

	return cast_loc;	

endfunction

function Reflected(cast_on)

	if (GetObjProperty(cast_on, "mr") =  "1")
		sleepms(500);
		PlaySoundEffect(cast_on, SFX_SPELL_MAGIC_REFLECTION);
		PlayObjectCenteredEffect( cast_on, FX_CURSE_EFFECT, 10,10);
		SendSysMessage(cast_on, "Your magic reflect spell saved you!");
		EraseObjProperty(cast_on, "mr");
		return 1;
	endif

// Following will take into account reflective armor
 
	local chance:= randomint(100);
	local MRTotal:= ReflectiveArmorTotal(cast_on);
	if ((MRTotal > 6) && (chance < 65)) //need all of the magical armor else it wont work. Has a 65% chance of reflecting	    
		sleepms(500);
		PlaySoundEffect(cast_on, SFX_SPELL_MAGIC_REFLECTION);
		PlayObjectCenteredEffect( cast_on, FX_CURSE_EFFECT, 10,10);
		SendSysMessage(cast_on, "Your azurite armor saved you!");
		return 1;
	endif
	return 0;

endfunction

function Resisted(circle, caster, cast_on, amt)

	local magery := Cint(GetSkill(caster, SKILLID_MAGERY));
	local evalint := Cint(GetSkill(caster, SKILLID_EVALINT));
	local halfamt := amt/2;
	local rezamt := Cint(( (RandomInt((halfamt))+1) * evalint ) / 100);
	local diff := (circle * 10)+15;
	local points := (diff * 10);

	if (checkskill(cast_on,SKILLID_MAGICRESISTANCE, diff, points))
		SendSysMessage(cast_on, "You feel yourself resisting magical energy!");
		PlaySoundEffect(cast_on, SFX_SPELL_WEAKEN);
		PlayObjectCenteredEffect( cast_on, FX_CURSE_EFFECT, 5,5);
		if (evalint > 0)
			amt := rezamt + halfamt;
		else
			amt := halfamt;
		endif
		return amt;
	else
		return amt;
	endif

endfunction

function CalcSpellDamage(circle, caster, cast_on)

        local die_string := cstr(circle * 2) +"d3";
	local dmg := RandomDiceRoll( die_string ) ;
	dmg := dmg + Cint( GetSkill(caster, SKILLID_MAGERY)/10);
        if ( dmg > (circle * 6) )
                dmg := circle * 6;
	endif

	if (!cast_on.npctemplate)
		dmg := (dmg/3)*2;
	endif		

	return dmg;

endfunction

function CanTargetThing(caster, circle, TargOpt := TGTOPT_CHECK_LOS)

	local cx := caster.x;
	local cy := caster.y;

	if (!can_cast(caster, circle))
        	return 0;
	endif

	local cast_on := Target( caster, TargOpt );
	if(!cast_on)
		return;
	endif

	if (cx != caster.x and cy != caster.y)
		SendSysMessage(caster,"You've lost your concentration.");
		return 0;
	endif

	return cast_on;	

endfunction

