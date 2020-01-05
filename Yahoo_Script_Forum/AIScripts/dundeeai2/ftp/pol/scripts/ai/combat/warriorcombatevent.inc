function process_combat_event(ev)

        if (ev.type = EVID_DAMAGED)
		if ((me.hp * 100/me.maxhp) < flee_point)
			Eraseobjproperty(me,"#flees");
			flee(ev.source);
		elseif (me.hp < me.maxhp/2)
			ApplyHealing();
		endif
	endif

endfunction

function in_combat_event_loop(opponent, loops)

	if ( loops > 50 )
		flee(opponent);
		return;
	endif

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	sleep(1);
	look_around();

endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function ApplyHealing()

	if ( GetObjProperty(me,"#lasthealed") > ReadGameClock())
		me.hp := me.hp + (RandomInt(me.maxhp - me.hp)+1);
		SetObjProperty(me,"#lasthealed", ReadGameClock()+20);
	endif

endfunction
