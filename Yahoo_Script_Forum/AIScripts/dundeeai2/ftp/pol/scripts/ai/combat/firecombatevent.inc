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

        cast_meteor(me);

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


function cast_meteor( caster )

	local nextbreath := GetObjProperty(me,"#lastbreath");

	if ( (nextbreath) and (nextbreath > ReadGameClock() ) )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + cint(RandomInt(10)+10) );

	local targets := ListMobilesNearLocation(me.x,me.y,me.z, 4);
	PerformAction(me,0x0c);

	local basedmg := cint(me.maxhp/3);

	foreach mobile in targets
	if ( (mobile) and (!mobile.npctemplate or mobile.script = "tamed") and (!mobile.cmdlevel))
		Local dmg := randomint((cint( basedmg * me.hp)/me.maxhp))+5;
		if (!dmg)
			dmg := 1;
		endif
		PlayMovingEffect(caster, mobile ,MOVING_EFFECT_FIREBALL, 10,1,1);
		applydamage(mobile, dmg);           
	endif
	endforeach

endfunction
