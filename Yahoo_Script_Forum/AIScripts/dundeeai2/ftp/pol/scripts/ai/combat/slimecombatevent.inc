function process_combat_event(ev)

	do_damage(ev.source);

        case (ev.type)
                EVID_DAMAGED: 
			if (randomint(10) = 1)
			    if ( (!cint(getobjproperty(me, "guardkill"))) and
			       (!cint(GetObjProperty(me,"killme"))) )
				local it := createnpcfromtemplate(me.npctemplate, me.x , me.y -1, me.z);
        			if (!it.errortext)
                			printtextabove(me, "The slime splits when struck!");
					SetObjProperty(it,"killme",1);
        			endif
        		    endif
			endif
                        if ((me.hp * 100/me.maxhp) < flee_point)
				Eraseobjproperty(me,"#flees");
                                flee(ev.source);
                        endif
        endcase

endfunction

function in_combat_event_loop(opponent, loops)

	do_damage(opponent);

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

function do_damage(evsource)

	if ( (distance(me, evsource) < 3 ) and (randomint(40) = 1) )
	  PrintTextAbovePrivate(me , "The slime spits acid at you!", evsource);
	  if (!HasShield(evsource))
		local dmg := randomint(5) + 1;
		local things := ListEquippedItems( evsource );

		local thing := things[ cint(randomint(len(things))+1) ];

		if ( CanEat(evsource, thing) )
		  PrintTextAbovePrivate(evsource, "The corrosive liquid damages "+ thing.desc, evsource);
		  if (dmg > thing.hp)
			dmg := thing.hp;
		  endif
		  thing.hp := thing.hp - dmg;
		  if ( (thing.hp <= 0) or (thing.hp > thing.maxhp) )
			PrintTextAbovePrivate(evsource, thing.desc + " is destroyed!", evsource);
			destroyitem(thing);
		  endif
		endif
	  endif
	endif

endfunction

function CanEat(character, item)

	if ( ( item.objtype >= 0x2030 ) and (item.objtype <= 0x2060) )
		return 0;
	endif
	if ( (item.objtype = 0x0E75) or (item.objtype = 0xF021 ) )
		return 0;
	endif

	if (!item.maxhp)
		return 0;
	endif

	return 1;

endfunction

function HasShield(you)

	local shield := GetEquipmentByLayer( you, LAYER_HAND2 );
	if ( (shield.objtype = 0x1bc3) or (shield.objtype = 0x1bc4) )
		PrintTextAbovePrivate(you,"Your shield blocks the acid!",you);
		return 1;
	endif

	return 0;

endfunction
