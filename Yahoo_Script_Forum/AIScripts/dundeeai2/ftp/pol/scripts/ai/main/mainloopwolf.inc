function main_AI_loop()

    local ev;
    local wanders := 60;
    local hatelist := "animal cat barker tamed chicken sheep bird";

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
		EVID_LEFTAREA:
			if ( ( me.npctemplate = "dog" ) and (!ev.source.npctemplate) )
				case (randomint(2))
				0: PlaySoundEffect(me,0x86);
				1: PlaySoundEffect(me,0x87);
				endcase
			elseif ( (ev.source.script) and ( hatelist[ev.source.script] ) )
			    get_help( ev.source );
	                    Fight( ev.source );
			elseif ( ev.source.npctemplate = me.npctemplate)
				WalkToward(ev.source);
				sleepms(500);
				WalkToward(ev.source);
			endif
                EVID_DAMAGED:
                EVID_ENGAGED:
		    if (ev.source)
		    	get_help( ev.source );
                    	Fight( ev.source );
		    endif
		EVID_ALL_ATTACK_CMD:
                    Fight( ev.source );
            endcase
        until (! (ev := os::wait_for_event(1)) );
	endif

   endwhile      

endfunction        

function look_around()

	local hatelist := "animal cat barker tamed chicken sheep bird";
	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
		if ( (critter.script) and ( hatelist[critter.script] ) )
			Fight( critter );
			return;
		endif
	endforeach

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA + EVID_LEFTAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA + EVID_LEFTAREA);

endfunction

function get_help( opponent )

	local ev Array;
	ev.+type := EVID_ALL_ATTACK_CMD;
	ev.+source := opponent;

	foreach critter in ListMobilesNearLocation( me.x, me.y, me.z, HALT_THRESHOLD )
		if ( (critter.npctemplate = me.npctemplate) and (critter.script != "tamed") and (!critter.warmode) )
			SendEvent(critter, ev);
		endif
	endforeach

endfunction
