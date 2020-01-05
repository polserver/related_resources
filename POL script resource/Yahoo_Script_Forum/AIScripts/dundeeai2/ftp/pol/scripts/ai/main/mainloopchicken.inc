const GFX_UNSHORN_SHEEP := 0xcf;
const GFX_SHORN_SHEEP := 0xdf;

function main_AI_loop()

    local ev;
    local wanders := 60;
    local nextlay := cint(readgameclock() + 3600);
    local nextbark := readgameclock() + 30;
    local next_wander := 0;

    EnableMainEvents();

    while (1)

	if (readgameclock() > next_wander)
		wander();
		next_wander := readgameclock()+5;
		wanders := wanders +1;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
	    	endif
	else
		ev := os::wait_for_event( 5 );
	endif

	if (ev)
        repeat
	    case (ev.type)
                EVID_DAMAGED:
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
            endcase
        until (! (ev := os::wait_for_event(5)) );
	endif

	if (readgameclock() > nextlay)
		nextlay := readgameclock()+ 2600 + cint(3800*RandomInt(2));
		createitematlocation(me.x, me.y, me.z,"egg",1);
	endif

	if ( readgameclock() > nextbark )
		nextbark := readgameclock() + ( (randomint(5)+1) * 60 );
		PlaySoundEffect(me,0x70);
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
        until (! (ev := os::wait_for_event(1)) );

	endwhile

endfunction

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED + EVID_ENTEREDAREA);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction
