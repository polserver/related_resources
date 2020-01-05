function main_AI_loop()

    local next_wander := ReadGameClock() + 10;
    local ev;
    local wanders := 120;

    look_around();

    EnableMainEvents();
 
    while (1)

	if (readgameclock() > next_wander)
		wanders := wanders +1;
		next_wander := readgameclock()+120;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
	    	endif
	else
		ev := os::wait_for_event( 120 );
	endif

        repeat
	    if (ev)
            case (ev.type)
                EVID_ENTEREDAREA:
                    if ( (!ev.source.npctemplate) or (ev.source.script = "tamed") )
			Fight( ev.source );
                    endif
                EVID_ENGAGED:
                EVID_DAMAGED:
                    Fight( ev.source );
            endcase
	    endif

        until (! (ev := os::wait_for_event(120)) );

   endwhile      

endfunction        

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction
