use uo;
use os;
use cfgfile;
use util;
include "include/client";


//calculates total number of reflective armor pieces
function ReflectiveArmorTotal(me)

	local item;
	local MRTotal:= 0;	

		foreach item in ListEquippedItems(me)
		if (GetObjProperty(item, "mr") = 1)
		MRTotal:= MRTotal + 1;
		endif
		endforeach

	Return MRTotal;

endfunction

//calculates total number of  Mage's armor pieces
function MageArmorTotal(me)

	local item;
	local MATotal:= 0;
	
		foreach item in ListEquippedItems(me)
		if (GetObjProperty(item, "ma") = 1)
		MATotal:= MATotal + 1;
		endif
		endforeach
		
	Return MATotal;

endfunction

//following allows for malachite armor meditation
function MageArmorMed(me)

	local hp := me.hp;
	local x := me.x;
	local y := me.y;
	local mana := me.mana;
	local diff := me.maxmana - me.mana;
	local points := 100;
	if (diff < 200)
		local points := diff;
	endif

	SendSysMessage(me,"You begin to meditate...");
	PlaySoundEffect(me,0xf8);
	sleep(5);

	if ( (me.x != x) or (me.y !=y) or (me.hp != hp) or (me.mana >= me.maxmana) or (me.mana < mana) )
			SendSysMessage(me,"You are unable to concentrate.");
			PlaySoundEffect(me,0xf6);
			return;
	endif
	
	if ( checkskill(me,SKILLID_MEDITATION,diff,points) )
		me.mana := me.mana + 3;			//2 less mana points than normal
		if (me.mana > me.maxmana)
			me.mana := me.maxmana;
			SendSysMessage(me,"You stop meditating");
			PlaySoundEffect(me,0xf6);
			return;
		endif
		PlaySoundEffect(me,0xfa);
		
		repeat
			me.mana := me.mana + 1;
			sleep(2); 			//meditates half as fast as normal
		until 	( (me.x != x) or (me.y !=y) or 
		 	(me.hp != hp) or (me.mana >= me.maxmana)
			or (me.mana < mana) );
		
		SendSysMessage(me,"You stop meditating");
		PlaySoundEffect(me,0xf6);
	else
		SendSysMessage(me,"You are unable to concentrate.");
	endif
	return;
endfunction