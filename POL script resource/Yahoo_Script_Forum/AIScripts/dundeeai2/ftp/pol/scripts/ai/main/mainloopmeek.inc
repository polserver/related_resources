function main_AI_loop()

    local ev;
    local wanders := 60;
    local next_loot := readgameclock() + 20;
    local next_wander := 0;

    EnableMainEvents();

    while (1)

	if ( ReadGameClock() > next_loot )
		grabloot();
		next_loot := ReadGameClock() + 10;
		ev := os::wait_for_event( 3 );
	else
		if ( ReadGameClock() > next_wander )
       			wander();
			wanders := wanders +1;
			next_wander := ReadGameClock()+4;
			if (wanders > 60)
				wanders :=0;
				ev := sleepmode();
			else
				ev := os::wait_for_event( 3 );
			endif
		else
			ev := os::wait_for_event( 3 );
		endif
	endif

	if (ev)
        repeat
            case (ev.type)
                EVID_SPEECH:
		    if (!ev.source.npctemplate)
		    	next_wander := readgameclock()+30;
		    	check_speech(ev.text, ev.source);
		    endif
                EVID_DAMAGED:
                EVID_ENGAGED:
                    Run( ev.source );
		EVID_ITEM_GIVEN:
		    next_wander := readgameclock()+60;
		    TakeItem(ev.source,ev.item);
            endcase
        until (! (ev := os::wait_for_event(1)) );
	endif

   endwhile      

endfunction        

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );
    EnableEvents(EVID_ITEM_GIVEN);

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED );
    DisableEvents(EVID_ITEM_GIVEN);

endfunction
