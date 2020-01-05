function process_combat_event(ev)

	spellattack(ev.source);

	case (ev.type)
        	EVID_DAMAGED:
			if ( me.hp < (me.strength/2))
				CastSpell(me,me,"gheal");
				if( cint(getobjproperty(me, "poison_level")) > 1)
					CastSpell(me,me,"cure");
					CastSpell(me,ev.source,"poison");
				endif
			endif
                        if ((me.hp * 100/me.maxhp) < flee_point)
				Eraseobjproperty(me,"#flees");
                                flee(ev.source);
                        endif
			break;
        	default: break;
	endcase

endfunction

function spellattack(opponent)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 2);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	if (RandomInt(3) != 1)
		sleep(1);
		cast_offensive_spell(me,opponent);
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 2);

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

	if ( loops > 50 )
		flee(opponent);
		return;
	endif

endfunction

function prepare_for_fight(opponent)

	if (!cint(GetObjProperty(me, "mr")))
		CastSpell(me,me,"reflect");
	endif

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	if ( me.hp < (me.strength/2))
		CastSpell(me,me,"gheal");
	endif

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	summons := 1;

	sleep(1);
	look_around();
  
endfunction
