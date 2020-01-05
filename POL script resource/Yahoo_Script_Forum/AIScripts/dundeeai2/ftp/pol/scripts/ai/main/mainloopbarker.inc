function main_AI_loop()

    local ev;
    local wanders := 60;
    local mynoise := bark();

    EnableMainEvents();

    while (1)

	wander();
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
		    if (!ev.source.npctemplate)
		    	PlaySoundEffect(me, mynoise);
		    endif
                EVID_DAMAGED:
                    Fight( ev.source );
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
            endcase
        until (! (ev := os::wait_for_event(2)) );
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

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction

function Bark()

	local noise := 0;
	case (me.graphic)
	0x06://bird
		case (randomint(3))
		0: noise := 0x1B;
		1: noise := 0x18;
		2: noise := 0x277;
		endcase
	0xc9://cat	
		noise := 0x6B;
	0xe7:
	0xe9:
	0xe8:
	0xd8://cow
		noise := 0x7A;
	0xd9://dog
		case (randomint(2))
		0: noise := 0x86;
		1: noise := 0x87;
		endcase
	0xd1://goat
		case (randomint(2))
		0: noise := 0x9A;
		1: noise := 0x9B;
		endcase	
	0xcb://pig
		noise := 0xC6;
	0xcc:
	0xc8:
	0xe2:
	0xe4://horses
		case (randomint(4))
		0: noise := 0xA9;
		1: noise := 0xAA;
		2: noise := 0xAB;
		3: noise := 0xAC;
		endcase
	0x51://toad
		case (randomint(4))
		0: noise := 0x267;
		1: noise := 0x268;
		2: noise := 0x26A;
		3: noise := 0x26D;
		endcase
	0xd3://bears
		case (randomint(5))
		0: noise := 0xA4;
		1: noise := 0xA5;
		2: noise := 0xA6;
		3: noise := 0xA7;
		3: noise := 0xA8;
		endcase
	0x1d://gorilla
		case (randomint(3))
		0: noise := 0x9F;
		1: noise := 0xA0;
		2: noise := 0xA2;
		endcase
	endcase

	return noise;

endfunction
