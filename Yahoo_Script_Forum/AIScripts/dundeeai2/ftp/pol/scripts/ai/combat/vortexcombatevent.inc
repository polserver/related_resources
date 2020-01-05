function process_combat_event(ev)

	spellattack(ev.source);
        if (ev.type = EVID_DAMAGED)
		if ((me.hp * 100/me.maxhp) < flee_point)
			Eraseobjproperty(me,"#flees");
			flee(ev.source);
		endif
        endif

endfunction

function spellattack(opponent);

	if (opponent)
		if (distance(me,opponent) < 2)
			local opmagery := cint(GetSkill(opponent,SKILLID_MAGERY));
			if (opmagery)
				applyrawdamage(opponent, randomint(cint(opmagery/15)) );
			endif
		endif
	endif

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

	if ( loops > 50 )
		flee(opponent);
		return;
	endif
         
endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	sleep(1);
	look_around();

endfunction
