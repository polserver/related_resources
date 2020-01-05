function main_AI_loop()

    local ev;
    local wanders := 60;
    local next_loot := readgameclock() + 20;

    EnableMainEvents();

    look_around();

    while (1)

	if (ReadGameClock() > next_loot)
		grabloot();
		next_loot := ReadGameClock() + 10;
	else
		wander();
	endif

	wanders := wanders +1;

	if (wanders > 60)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 2 );
	endif

	if (ev)
	  repeat
            case (ev.type)
                EVID_ENTEREDAREA:
                    if ( (!ev.source.npctemplate) or (ev.source.script = "tamed") )
			Fight( ev.source );
                    endif
		EVID_ALL_ATTACK_CMD:
		    Fight( ev.source );
                EVID_ENGAGED:
                EVID_DAMAGED:
		    if (ev.source)
		    	get_help( ev.source );
		    	fight(ev.source);
		    endif
            endcase
	  until (!(ev := os::wait_for_event(2)));
	endif

   endwhile      

endfunction       

function look_around()

	foreach npc in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
          if ( (!npc.npctemplate) or (npc.script = "tamed") )
                Fight( npc );
		return;
          endif
	endforeach

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction

function get_help( opponent )

	local inev;
	local ev Array;
	ev.+type := EVID_ALL_ATTACK_CMD;
	ev.+source := opponent;

	foreach critter in ListMobilesNearLocation( me.x, me.y, me.z, 4 )
		if ( (critter.npctemplate) and (critter.script != "tamed") and (!critter.warmode) and
		     (critter.serial != me.serial) )
			SendEvent(critter, ev);
		endif
		inev := wait_for_event(0);
		if (inev.type = EVID_ALL_ATTACK_CMD)
			return;
		endif
	endforeach

endfunction
