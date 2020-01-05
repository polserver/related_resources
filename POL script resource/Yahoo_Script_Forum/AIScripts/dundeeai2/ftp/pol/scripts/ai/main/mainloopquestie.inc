function main_AI_loop()

    local ev;
    local wanders := 60;
    local next_offer := readgameclock();
    local next_wander := 0;
    local evtext;
    local resetquest := 0;

    EnableMainEvents();

    while (1)

	if (readgameclock() > next_wander)
        	wander();
		next_wander := readgameclock()+2;
		wanders := wanders +1;
		if (wanders > 60)
			wanders :=0;
			if (!look_around())
			if (!ResetQuest)
				if (master.serial = me.serial)
					if (!slave)
						MoveCharacterToLocation(me,5288,1176,0,MOVECHAR_FORCELOCATION);
						SetObjProperty(me,"guardkill",1);
						damage( me, me.maxhp + 3 );
					endif
				else
					if (!master)
						MoveCharacterToLocation(me,5288 , 1176 , 0,MOVECHAR_FORCELOCATION);
						SetObjProperty(me,"guardkill",1);
						damage( me, me.maxhp + 3 );
					endif
				endif
			else
				MoveCharacterToLocation(me,5288 , 1176 , 0,MOVECHAR_FORCELOCATION);
				SetObjProperty(me,"guardkill",1);
				damage( me, me.maxhp + 3 );
			endif
			endif
			ev := sleepmode();
	    	endif
	else
		ev := os::wait_for_event( 3 );
	endif

	if (ev)
        repeat
            case (ev.type)
                EVID_SPEECH:
	    		next_wander := readgameclock()+30;
			evtext := lower(ev.text);
			if (evtext["take"])
				GiveQuestItem(ev.source);
			elseif ( next_offer < ReadGameClock() )
				next_offer := ReadGameClock()+45;
				TurnToward(ev.source);
				if (!OfferQuest())
		    			check_speech(ev.text, ev.source);
				endif
			else
		    		check_speech(ev.text, ev.source);
			endif
		EVID_ENTEREDAREA:
		    if (!ev.source.npctemplate)
		    	YellToFriend(ev.source);
		    endif
                EVID_ENGAGED:
                EVID_DAMAGED:
                    Fight( ev.source );
		EVID_ITEM_GIVEN:
		    wanders :=0;
		    next_wander := readgameclock()+30;
		    if ( GetObjproperty(ev.item,"slave") = cint(me.serial) )
			TakeQuestItem(ev.source,ev.item);
			ResetQuest := 1;
		    else
			TakeItem(ev.source,ev.item);
		   endif
            endcase
        until (! (ev := os::wait_for_event(2)) );
	endif

   endwhile      

endfunction        

function look_around()

	foreach critter in ListMobilesNearLocation( me.x,me.y,me.z, 10 );
          if (!critter.npctemplate)
		return 1;
          endif
	endforeach

	return 0;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_SPEECH, 2 );
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );
    EnableEvents( EVID_ITEM_GIVEN );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA + EVID_ITEM_GIVEN );

endfunction

function OfferQuest()

	if ( questtype < 2 )
		return OfferMailBoyQuest();
	endif

	return 0;

endfunction

function OfferMailBoyQuest()

	local item := 0;
	local slavetown;
	if (me.serial = master.serial)
		item := HasQuestItem(me, slave);
		if (item)
			slavetown := getobjproperty(me,"slavetown");
			say("I have "+ item.desc + " that I need delivered to "+slave.name+" in " + slavetown);
			sleep(1);
			say("If you will [take] it, "+ slave.name + " will pay you.");
			return 1;
		endif
	else
		if (!master)
			return 0;
		else
			item := HasQuestItem(master, me);
			slavetown := WhatTown(master);
			if ( (item) and (slavetown) )
				say(master.name + " in " + slavetown + " has " + item.desc + " for me.");
				sleep(1);
				say("If you will bring it to me, I will pay you.");
				return 1;
			endif
		endif
	endif
	return 0;

endfunction

function GiveQuestItem(you)

	local item := HasQuestItem(me, slave);
	if (item)
		local slavetown := getobjproperty(me,"slavetown");
		say("Here is "+item.desc+" for "+slave.name+" in "+slavetown);
		say("Take it to "+ slave.name + " for your payment.");
		MoveItemToContainer(item,you.backpack);
	endif

endfunction

function HasQuestItem(who, forwhom)

	foreach item in enumerateitemsincontainer(who.backpack)
		if ( getobjproperty(item,"slave") = forwhom.serial )
			return item;
		endif
	endforeach
	return 0;

endfunction

function TakeQuestItem(you, it)

	TurnToward(you);
	say("Oh this must be from "+master.name+"!  Thank you for bringing it!");
	say("And here is your pay!");
	DestroyItem(it);
	local goldamount := ((randomint(3)+2)*100)+RandomInt(100);
	CreateItemInContainer(you.backpack,"goldcoin",goldamount);

endfunction
