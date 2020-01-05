include "include/speech";
function main_AI_loop()

    local ev;
    local wanders := 120;
    local next_loot := readgameclock() + 20;

    EnableMainEvents();

    while (1)

    look_around();
    Agrupar();

    if (ReadGameClock() > next_loot)
		grabloot();
		next_loot := ReadGameClock() + 10;
	else
		wander();
	endif

	wanders := wanders +1;

	if (wanders > 120)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 2 );
	endif

	if (ev)
	  repeat
            case (ev.type)
                SYSEVENT_SPEECH:
                    RespondToSpeech(ev.source, ev.text);
               		wanders :=0;
                SYSEVENT_ENTEREDAREA:
                    PlaysoundEffect(me, DetectarSom());
                    if ( (!ev.source.npctemplate) or (ev.source.script = "tamed") )
        		    	get_help( ev.source );
            			Fight( ev.source );
                   		wanders :=0;
                    endif
        		EVID_ALL_ATTACK_CMD:
        		    Fight( ev.source );
               		wanders :=0;
                SYSEVENT_ENGAGED:
                SYSEVENT_DAMAGED:
        		    get_help( ev.source );
        		    fight(ev.source);
               		wanders :=0;
            endcase
	  until (!(ev := os::wait_for_event(2)));
	endif

   endwhile      

endfunction       

function look_around()

	foreach npc in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
          if ( ((!npc.npctemplate) or (npc.script = "tamed")) and !(npc.cmdlevel))
                Fight( npc );
        		return;
          endif
	endforeach

endfunction

function EnableMainEvents()

    DisableEvents( SYSEVENT_LEFTAREA + SYSEVENT_DISENGAGED + SYSEVENT_OPPONENT_MOVED );
    EnableEvents( SYSEVENT_SPEECH + SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + SYSEVENT_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( SYSEVENT_SPEECH + SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + SYSEVENT_ENTEREDAREA);

endfunction

function get_help( opponent )

	local inev;
	local ev := array;
	ev.+type := EVID_ALL_ATTACK_CMD;
	ev.+source := opponent;

	set_critical(1);
	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
		if ( (critter.graphic = me.graphic) and (critter.script != "tamed") and (!critter.warmode) )
			SendEvent(critter, ev);
		endif
		inev := wait_for_event(0);
		if (inev = EVID_ALL_ATTACK_CMD)
			set_critical(0);
			return;
		endif
	endforeach
	set_critical(0);

endfunction
