function main_AI_loop(next_wander := 0)

    local ev;
    local wanders := 60;
    local next_loot := readgameclock() + 20;

	local configfile := ReadConfigFile("::npcdesc");

    EnableMainEvents();

    while (1)

	if (readgameclock() > next_wander)
		wander();
		next_wander := readgameclock()+3;
		wanders := wanders +1;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
    		endif
	else
		ev := os::wait_for_event( 3 );
	endif

	if (ev)
        repeat
            case (ev.type)
		EVID_ENTEREDAREA:
			if ( (ev.source.npctemplate) and (ev.source.script != "tamed") )
                		if (!configfile[ev.source.npctemplate].guardignore)
					say("Ah ha! " + ev.source.name);
                        		fight(ev.source);
                		endif
			endif
                EVID_SPEECH:
		    if (!ev.source.npctemplate)
		    	wanders :=0;
		    	next_wander := readgameclock()+30;
		    	check_speech(ev.text, ev.source);
		    endif
                EVID_ENGAGED:
                EVID_DAMAGED:
                    Fight( ev.source );
		EVID_ITEM_GIVEN:
		    next_wander := readgameclock()+60;
		    TakeItem(ev.source,ev.item);
            endcase
        until (! (ev := os::wait_for_event(3)) );
	endif

   endwhile      

endfunction        

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_ENTEREDAREA + EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );
    EnableEvents(EVID_SPEECH, 2 );
    EnableEvents(EVID_ITEM_GIVEN);

endfunction

function DisableMainEvents()

    DisableEvents( EVID_ENTEREDAREA + EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED );
    DisableEvents(EVID_ITEM_GIVEN);

endfunction
