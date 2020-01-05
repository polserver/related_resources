function do_poison_effect( who, dmg, str )
	
	//print("firing off the damage"); //debug
	applyrawdamage(who, dmg);
	PlaySoundEffect(who, SFX_SPELL_POISON);
	local level := cint(getobjproperty(who, str));
	level := level - 1;
	if ( (level <= 0) or (who.dead) )
		eraseobjproperty(who, str);
		who.SetPoisoned(0);
	else
		setobjproperty(who, str, level);
		who.setpoisoned(1);
		
	endif
	return(1);
endfunction