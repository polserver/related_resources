function process_combat_event(ev)

	DoPoison(ev.source);

        if (ev.type = EVID_DAMAGED)
		if ((me.hp * 100/me.maxhp) < flee_point)
			Eraseobjproperty(me,"#flees");
			flee(ev.source);
		endif
        endif

endfunction

function in_combat_event_loop(opponent, loops)

	DoPoison(opponent);

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

function DoPoison(you)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);

	if ( (distance(me,you)<2) and (RandomInt(4)=1) )

	local p_level := cint(me.maxhp/10);
	local poison_level := Cint(GetObjProperty(you, "poison_level"));

	if (p_level < poison_level)
		p_level := poison_level;
	else
		SendSysmessage (you, "You have been poisoned by " + me.name +"!");
		SetObjProperty(you, "poison_level",cstr(p_level));
	endif

	start_script( ":spells:poisondamage", you ); 

	endif

endfunction
