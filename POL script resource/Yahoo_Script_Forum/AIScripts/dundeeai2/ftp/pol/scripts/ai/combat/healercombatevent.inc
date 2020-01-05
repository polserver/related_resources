function process_combat_event(ev)

	spellattack(ev.source);

	case (ev.type)
		EVID_DAMAGED:
			if ( me.hp < (me.strength/2))
				CastSpell(me,me,"gheal");
				if(cint(getobjproperty(me, "poison_level")) >1 )
					CastSpell(me,me,"cure");
				endif
			endif
                        if ((me.hp * 100/me.maxhp) < flee_point)
				Eraseobjproperty(me,"#flees");
                                flee(ev.source);
                        endif
	endcase

endfunction

function spellattack(opponent)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	if (RandomInt(2)=1)
		sleep(1);
		cast_offensive_spell(me,opponent);
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);

	foreach myfriend in listmobilesnearlocation(me.x, me.y, me.z, HALT_THRESHOLD)
		if (myfriend.npctemplate and myfriend.script != "tamed" )
			healerstuff(myfriend);
		endif
	endforeach

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

	if ( loops > 50 )
		flee(opponent);
		return;
	endif

endfunction       

function prepare_for_fight(opponent)

	if (GetObjProperty(me, "mr") != "1")
		CastSpell(me,me,"reflect");
	endif

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	num_casts := 2;

	sleep(1);
	look_around();

endfunction


function HealerStuff(mobile)

if (!mobile.npctemplate or mobile.npctemplate["guard"] or mobile.script = "tamed")
        return;
endif
   
	//Say (mobile.name);
	local poison_level := Cint(GetObjProperty(mobile, "poison_level"));
	if( poison_level > 0 and CheckLineOfSight(me,mobile) )
		TurnToward(mobile);
		CastSpell(me,mobile,"cure");
	elseif( (mobile.hp < (mobile.maxhp/2)) and (CheckLineOfSight(me,mobile))  )
		TurnToward(mobile);
		CastSpell(me,mobile,"gheal");
	endif
    
endfunction
