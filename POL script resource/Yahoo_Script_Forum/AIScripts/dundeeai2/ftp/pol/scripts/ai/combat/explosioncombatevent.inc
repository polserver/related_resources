function process_combat_event(ev)

	ThrowPotion(ev.source);

        if (ev.type = EVID_DAMAGED)
		if ((me.hp * 100/me.maxhp) < flee_point)
			Eraseobjproperty(me,"#flees");
			flee(ev.source);
		endif
        endif

endfunction

function in_combat_event_loop(opponent, loops)

	ThrowPotion(opponent);

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

function ThrowPotion(you)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 3);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 3);

	if ( (distance(me,you)>2) and (RandomInt(2)=1) )

		var parms := {};
		parms[1] := me;
		parms[2] := you;

		start_script( ":alchemy:explosion", parms ); 

	endif

endfunction
