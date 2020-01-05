const GFX_UNSHORN_SHEEP := 0xcf;
const GFX_SHORN_SHEEP := 0xdf;

function main_AI_loop()

    local ev;
    local wanders := 60;
    local next_wander := 0;
    local next_regrow := readgameclock() + 1800;
    local nextbark := readgameclock() + 30;

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
        until (! (ev := os::wait_for_event(1)) );
	endif

	if (readgameclock() > next_regrow)
		next_regrow := readgameclock()+cint(1800+RandomInt(300));
		if ( me.graphic = GFX_SHORN_SHEEP )
			me.graphic := GFX_UNSHORN_SHEEP;
		endif
		if ( RandomInt(1000)=1 )
			damage( me, me.maxhp + 3 );
		endif
	endif

	if ( readgameclock() > nextbark )
		nextbark := readgameclock() + ( (randomint(5)+1) * 60 );
		case (randomint(2))
		0: PlaySoundEffect(me,0xD7);
		1: PlaySoundEffect(me,0xD8);
		endcase
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
		    if ( randomint(3) = 1 )
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

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED);

endfunction
