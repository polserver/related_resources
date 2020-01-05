
function Fight()

DisableEvents( EVID_DOUBLECLICKED );
DisableEvents( EVID_ITEM_GIVEN );

TurnToward( opponent );
SetOpponent( opponent );

local waittime,friendly,ev;
outer:
while (opponent and !opponent.dead)
	waittime := CloseDistance( opponent ) * 15;
	ev := wait_for_event( waittime );
        if(ev)
		friendly := CheckPerson(ev.source.serial);
        	case (ev.type)
			EVID_SPEECH:
		               	if(friendly)
					Do_Command(ev,friendly);
				endif
			EVID_ENGAGED:
			EVID_DAMAGED:
				if (ev.source.serial != opponent.serial)
					TurnToward( ev.source );
					fightqueue.append(ev.source.serial);
					sleepms(200);
					TurnToward( opponent );
				endif
			EVID_DISENGAGED:
			EVID_PEACEMADE:
				if(ev.source.serial = opponent.serial)
					opponent :=0;
				endif
			EVID_ALL_ATTACK_CMD:
				opponent := ev.target;
				fightqueue := {};
				TurnToward(opponent);
				SetOpponent(opponent);
			EVID_ALL_FOLLOW_CMD:
				SetWarMode(0);
				opponent :=0;
				fightqueue := {};
				followed := ev.target;

			//EVID_MASTER_DEAD:
			//EVID_BODY_TOUCHED:	
	        endcase
		if (caster and opponent)
			if (count_casts)
				if (num_casts > 0)
					if (randomint(100) <= cast_pct)
						Sleep(1);
						cast_offensive_spell(me,opponent);
						num_casts := num_casts - 1;
					endif
				endif
			else
				if (randomint(100) <= cast_pct)
					sleep(1);
					cast_offensive_spell(me,opponent);
					num_casts := num_casts - 1;   
				endif   
			endif
		endif
	endif

	if(!opponent)
		opponent := GetOpponent();
	endif
endwhile

SetWarMode( 0 );
opponent :=0;
fightqueue :={};
EnableEvents( EVID_DOUBLECLICKED );
EnableEvents( EVID_ITEM_GIVEN );
endfunction




function WaitFight()
    
TurnToward( opponent );
SetOpponent( opponent );

local waittime;

while (opponent and !opponent.dead)
	waittime := CloseDistance( opponent ) * 15;
	local ev := wait_for_event( waittime );
	if(ev)
		case (ev.type)
			EVID_DISENGAGED:
			EVID_PEACEMADE:
				if(ev.source.serial = opponent.serial)
					opponent :=0;
				endif

			EVID_ENGAGED:
			EVID_DAMAGED:
				if (ev.source.serial != opponent.serial)
					TurnToward( ev.source );
					fightqueue.append(ev.source.serial);
					sleepms(200);
					TurnToward( opponent );
				endif
     		endcase
		if(caster and opponent)
			if(count_casts)
				if(num_casts > 0)
					if (randomint(100) <= cast_pct)
						sleep(1);
						cast_offensive_spell(me,opponent);
						num_casts := num_casts - 1;
					endif
				endif
			else
				if(randomint(100) <= cast_pct)
					sleep(1);
					cast_offensive_spell(me,opponent);
					num_casts := num_casts - 1;   
				endif   
			endif
		endif
	endif

	if(!opponent)
		opponent := GetOpponent();
	endif

endwhile

opponent :=0;
fightqueue :={};
SetWarMode( 0 );
endfunction