function main_AI_loop()

    local ev;
    local wanders := 60;
    local next_wander := readgameclock();
    EnableMainEvents();
    while (1)

	if (readgameclock() > next_wander)
		SpoutTheNews();
		wanders := wanders +1;
		next_wander := readgameclock()+60;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
    		endif
	else
		ev := os::wait_for_event( 60 );
	endif

	if (ev)
        repeat
            case (ev.type)
                EVID_SPEECH:
		    if (!ev.source.npctemplate)
		    	if (lower(ev.text) = "news")
				wanders :=0;
		    		next_wander := readgameclock()+60;
		    		SpoutTheNews();
		    	endif
		    endif
                EVID_ENGAGED:
                EVID_DAMAGED:
                    Fight( ev.source );
		    ReturnHome();
            endcase

        until (! (ev := os::wait_for_event(60)) );
	endif

   endwhile      

endfunction        

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );
    EnableEvents( EVID_SPEECH, 3 );
    DisableEvents(EVID_ITEM_GIVEN);

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED );
    DisableEvents(EVID_ITEM_GIVEN);

endfunction

function SpoutTheNews()

	local news := GetGlobalProperty("news");
	if (!news)
		Say("No news is good news.");
		return;
	endif

	local i;
	for (i := 1; i <= len(news); i := i + 1)
		Say(news[i]);
		sleep(2);
	endfor

endfunction

function ReturnHome()

	local myhome := GetObjProperty(me,"myhome");
	MoveCharacterToLocation(me,myhome[1],myhome[2],myhome[3],MOVECHAR_FORCELOCATION);

endfunction
