function main_AI_loop()

    local ev;
    local wanders := 60;

    EnableMainEvents();

    while (1)

	wander();
	wanders := wanders +1;

	if (wanders > 60)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 3 );
	endif

	if (ev)
        repeat
	    case (ev.type)
                EVID_DAMAGED:
                    Fight( ev.source );
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
            endcase
        until (! (ev := os::wait_for_event(3)) );
	endif

   endwhile      

endfunction        

function RunLikeHell(opponent)

	local ev;
	while ( (opponent) and not 
	    (opponent.dead or opponent.hidden or opponent.concealed) and 
	    (dist(me,opponent) < 25) ) 

	    Runawayfrom( opponent );

        repeat
	    case (ev.type)
                EVID_DAMAGED:
		    if ( randomint(3)=1 )
                    	Fight( ev.source );
		    	return;
		    endif
            endcase
        until (! (ev := os::wait_for_event(1)) );

	endwhile

endfunction

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_ENTEREDAREA + EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction
