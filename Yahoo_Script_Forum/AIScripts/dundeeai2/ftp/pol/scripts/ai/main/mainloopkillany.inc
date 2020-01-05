function main_AI_loop()

    local ev;
    local wanders := 60;
    local next_loot := readgameclock() + 20;

    EnableMainEvents();

    look_around();

    while (1)

	if ( ReadGameClock() > next_loot )
		grabloot();
		next_loot := ReadGameClock() + 5;
	else
       		wander();
	endif

	wanders := wanders +1;
	if (wanders > 60)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 1 );
	endif

	if (ev)
	repeat
	    case (ev.type)
                EVID_ENTEREDAREA:
                EVID_ENGAGED:
                EVID_DAMAGED:
		    Fight( ev.source);
	    endcase
        until (! (ev := os::wait_for_event(1)) );
	endif

   endwhile      

endfunction        

function look_around()

	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
                Fight( critter );
		return;
	endforeach
	
endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction
