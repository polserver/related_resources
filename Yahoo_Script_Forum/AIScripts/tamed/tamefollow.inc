function Follow()

local ev,friendly;
while(followed)
	//just a dummy prop, no hurt to use it...
	friendly := Distance(me, followed);
	if( friendly > 1)
		RunToward(followed);
		if(friendly > 50)
			MoveCharacterToLocation( me, followed.x, followed.y, followed.z );
		elseif(friendly > 25)
			//probably just ran away
			followed :=0;
			return;
		endif
	else
		sleepms(250);
	endif

	ev:=wait_for_event(0);
	if(ev)
		friendly := CheckPerson(ev.source.serial);
		case(ev.type)
			EVID_SPEECH:
				if(friendly)
					Do_Command(ev,friendly);
				endif
			//should this be here? or they should never stop while following?
			EVID_ENGAGED:
			EVID_DAMAGED:
				if(ev.source)
					opponent := ev.source;
					fightqueue := {};
					followed :=0;
				endif

			EVID_DOUBLECLICKED:
				followed :=0;
				OpenMyPack(ev.source,friendly);
			EVID_ALL_ATTACK_CMD:
				followed :=0;
				opponent := ev.target;
			EVID_ALL_FOLLOW_CMD:
				followed := ev.target;

			//EVID_MASTER_DEAD:
			//EVID_BODY_TOUCHED:	
		endcase
	endif
	sleepms(100);
endwhile
endfunction