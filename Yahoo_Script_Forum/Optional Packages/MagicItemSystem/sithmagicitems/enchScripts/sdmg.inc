use uo;
use os;

include "include/attributes";

//Calculates damage OSI-Style
function doSpellDamage( caster, caston, basedmg, circle )

	var cres := cInt(GetEffectiveSkill( caston, 26 ));
	var cmag := cInt(GetEffectiveSkill( caster, 25 ));
	var ceis := cInt(GetEffectiveSkill( caster, 16 ));
	var resC;
	var sDmg := basedmg;

	local ctra := cres / 5;
	local ctrb := cres - ( ( (cmag - 20) / 5) + (circle * 5) );

	if( ctra > ctrb )
		resC := ctra;
	elseif( ctrb > ctra )
		resC := ctrb;
	else
		resC := ctra;
	endif

	AwardPoints( caston, 26, (circle * 100) );

	if( RandomInt(100) <= resC )
		//Spell was resisted
		AwardPoints( caston, 26, (circle * 100) );
		SendSysMessage( caston, "You feel yourself resist " + caster.name + "'s spell!" );
		SendSysMessage( caster, "It looks like " + caston.name + " is resisting your spell!" );
		sDmg := sDmg / 2;
	endif

	local dmgMod;

	if( cres > ceis )
		//Resistance is higher than attackers Evaluating Intelligence
		dmgMod := 1 + ( ceis - cres ) / 200;
	else
		//Evaluating Intelligence is higher than Resistance
		dmgMod := 1 + ( ceis - cres ) / 500;
	endif

	sDmg := sDmg * dmgMod;

	ApplyRawDamage( caston, sDmg );

endfunction

///////////////////////////
//Find a mobile from serial
///////////////////////////
function findThisGuy( serial )

	local who;
	who := SystemFindObjectBySerial( serial );
	if( !who || who = error )
		who := SystemFindObjectBySerial( serial, SYSFIND_SEARCH_OFFLINE_MOBILES );
	endif

	if( who )
		return who;
	else
		return 0;
	endif

endfunction