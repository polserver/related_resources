function Fight( opponent )
	if ((opponent.cmdlevel) or (opponent.serial = me.serial))
        	setwarmode(0);
        	opponent := 0;
            return;
	endif

	set_priority(50);

	SetOpponent( opponent );
   	prepare_for_fight();

	local loops := 0;
   	local ev;
	local waittime := 0;

    if (me.scritp = "tamed")
        EnableEvents(SYSEVENT_SPEECH, 6);
    endif

    while ( (opponent) and !(opponent.dead or opponent.hidden or opponent.concealed))

    local closedist := CloseDistance( opponent );
	if (!closedist)         // Continua correndo para o inimigo
		loops := loops + 1;
		waittime := 0;
	elseif (closedist = 2) // Não achou caminho, abandona a luta e procura outro oponent
        post_combat();
        return;
    else
        loops := 0;
		waittime := 1;
	endif
    turntoward( opponent );

	in_combat_event_loop(opponent, loops);

	ev := wait_for_event( waittime );
	case (ev.type)
        SYSEVENT_SPEECH:
            if ((me.script = "tamed")and(ev.source = me.master))
                if (ev.text[me.name] or ev.text["todos"])
                    return ev;
                endif
            endif
        SYSEVENT_DAMAGED:
		SYSEVENT_ENGAGED:
			if (ev.source)
			  process_combat_event(ev);
			  if (RandomInt(4)=1)
				if ((!ev.source.npctemplate) or (ev.source.script = "tamed") )
					opponent := ev.source;
			  		SetOpponent( opponent );
					turntoward( opponent );
				endif
			  endif
			endif
        EVID_PEACEMADE:
            post_combat();
			return;
	endcase

    endwhile

    post_combat();
      
endfunction

function EnableCombatEvents()

    EnableEvents( SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + EVID_PEACEMADE );

endfunction

function DisableCombatEvents()

    DisableEvents( SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + EVID_PEACEMADE );

endfunction

function flee(opponent)

	if (me.script = "immobile")
		sleep(2);
		return;
	endif

	local numflees := getobjproperty(me,"#flees");

	if (numflees)
		if ( numflees > 5 )
			MoveCharacterToLocation(me,5288,1176,0,MOVECHAR_FORCELOCATION);
			SetObjProperty(me,"guardkill",1);
			damage( me, me.maxhp + 3 );
		else
			numflees := numflees + 1;
		endif
	else
		numflees := 1;
	endif

	setobjproperty(me,"#flees",numflees);

	local runs := 0;
	while ( (distance(me, opponent) < 20) and (runs < 50) )
		runawayfrom(opponent);
		runs := runs +1;
		wait_for_event(0);
	endwhile

	RestartScript( me );

endfunction

function DetectarSom()

	local noise := 0;
	case (me.graphic)

    0x01://Ogre
        case (randomint(2))
        0: noise := 0x1AC;
        1: noise := 0x1AD;
        endcase
    0x02://Ettin
    0x12:
        case (randomint(2))
        0: noise := 0x170;
        1: noise := 0x171;
        endcase
    0x03://Zombie
        case (randomint(2))
        0: noise := 0x1D8;
        1: noise := 0x1D9;
        endcase
    0x04://Gargoyle
        case (randomint(2))
        0: noise := 0x175;
        1: noise := 0x176;
        endcase
    0x05://eagle
        case (randomint(2))
        0: noise := 0x90;
        1: noise := 0x91;
        endcase
    0x06://bird
		case (randomint(12))
		0: noise := 0x18;
		1: noise := 0x19;
		2: noise := 0x1A;
		3: noise := 0x1B;
		4: noise := 0x1C;
		5: noise := 0x1D;
		6: noise := 0x1E;
		7: noise := 0x1F;
		8: noise := 0x20;
		9: noise := 0x277;
        10: noise := 0x7E;
        11: noise := 0x7F;
		endcase
    0x07://Orcs
    0x11:
    0x29:
        case (randomint(2))
        0: noise := 0x1B1;
        1: noise := 0x1B2;
        endcase
    0x09://Deamons
    0x0a:
        noise := 0x167;
    0x0C://dragons
    0x3B:
    0x3C:
    0x3D:
        noise := 0x16B;
    0x15://Serpent and Snake
    0x34:
        noise := 0xDD;
    0x16://Gazer
        case (randomint(2))
        0: noise := 0x17A;
        1: noise := 0x17B;
        endcase
    0x1a://Shade and Ghosts
    0x3ca:
        case (randomint(5))
        0: noise := 0x17F;
        1: noise := 0x180;
        2: noise := 0x181;
        3: noise := 0x182;
        4: noise := 0x185;
        endcase
    0x1c://Spider
        case (randomint(2))
        0: noise := 0x184;
        1: noise := 0x185;
        endcase
    0x1E://Harpie
        case (randomint(2))
        0: noise := 0x193;
        1: noise := 0x194;
        endcase
    0x18://Lich
        noise := 0x19D;
    0x1F://Headless One
        case (randomint(2))
        0: noise := 0x198;
        1: noise := 0x199;
        endcase
    0x21://Lizardmans
    0x23:
    0x24:
        case (randomint(2))
        0: noise := 0x1A2;
        1: noise := 0x1A3;
        endcase
    0x27://Mong Bat/Imp
        case (randomint(2))
        0: noise := 0x1A7;
        1: noise := 0x1A8;
        endcase
    0x2a://Ratmans
    0x2c:
    0x2d:
        case (randomint(2))
        0: noise := 0x1B6;
        1: noise := 0x1B7;
        endcase
    0x2f://reaper
        case (randomint(2))
        0: noise := 0x1BB;
        1: noise := 0x1BC;
        endcase
    0x30://Giant Scorpion
        case (Randomint(2))
        0: noise := 0x18E;
        1: noise := 0x18F;
        endcase
    0x32://Skeleatons
    0x38:
    0x39:
        case (randomint(2))
        0: noise := 0x1C4;
        1: noise := 0x1C5;
        endcase
    0x33://Slime
        case (randomint(2))
        0: noise := 0x1C9;
        1: noise := 0x1CA;
        endcase
    0x35://Trolls
    0x36:
    0x37:
        case (randomint(2))
        0: noise := 0x1CE;
        1: noise := 0x1CF;
        endcase
    0x3a://Wisp
        case (randomint(2))
        0: noise := 0x1D3;
        1: noise := 0x1D4;
        endcase
    0x4c://Cyclops
        case (randomint(5))
        0: noise := 0x25D;
        1: noise := 0x25E;
        2: noise := 0x25F;
        3: noise := 0x260;
        4: noise := 0x261;
        endcase
    0x96://Sea Serpent
        case (randomint(3))
        0: noise := 0x1C0;
        1: noise := 0x1C1;
        2: noise := 0x1C3;
        endcase
    0x97://Dolphin
        case (randomint(3))
        0: noise := 0x8B;
        1: noise := 0x8C;
        2: noise := 0x8D;
        endcase
    0xc9://cat
        case (randomint(2))
        0: noise := 0x6A;
        1: noise := 0x6B;
        endcase
	0xca://Aligator
        case (randomint(4))
        0: noise := 0x5B;
        1: noise := 0x5C;
        2: noise := 0x5E;
        3: noise := 0x5F;
        endcase
	0xcb://pig and Boar
    0x122:
        case (randomint(2))
        0: noise := 0xC5;
        1: noise := 0xC6;
        endcase
    0xcd://Bunny/Rabbit
        noise := 0xCA;
    0xce://Lava Lizzard
        case (randomint(2))
        0: noise := 0x28A;
        1: noise := 0x28B;
        endcase
    0xd0://Chicken
        case (randomint(3))
        0: noise := 0x6F;
        1: noise := 0x70;
        2: noise := 0x71;
        endcase
	0xd1://goat
		case (randomint(2))
		0: noise := 0x9A;
		1: noise := 0x9B;
		endcase	
    0xd6://Panther
        case (randomint(2))
        0: noise := 0xBB;
        1: noise := 0xBC;
        endcase
    0xd7://Giant Rat
        case (randomint(2))
        0: noise := 0x189;
        1: noise := 0x18A;
        endcase
	0xd9://dog
		case (randomint(2))
		0: noise := 0x86;
		1: noise := 0x87;
		endcase
    0xe9://bull
	0xe8:
        case (randomint(3))
        0: noise := 0x65;
        1: noise := 0x66;
        2: noise := 0x67;
        endcase
    0xea://Great Hart and deer
    0xed:
        noise := 0x83;
    0xe7://cow
	0xd8:
        case (randomint(2))
        0: noise := 0x79;
        1: noise := 0x7A;
        endcase
	0xe1://wolf
        case (randomint(2))
        0: noise := 0xE7;
        1: noise := 0xE8;
        endcase
    0xee://Rat
        case (randomint(2))
        0: noise := 0xCD;
        1: noise := 0xCE;
        endcase
    0xcc://horses
	0xc8:
	0xe2:
	0xe4:
		case (randomint(4))
		0: noise := 0xA9;
		1: noise := 0xAA;
		2: noise := 0xAB;
		3: noise := 0xAC;
		endcase
    0x50://toad
    0x51:
		case (randomint(4))
		0: noise := 0x267;
		1: noise := 0x268;
		2: noise := 0x26A;
		3: noise := 0x26D;
		endcase
    0xd4://Grizzly bear
		case (randomint(5))
		0: noise := 0xA4;
		1: noise := 0xA5;
		2: noise := 0xA6;
		3: noise := 0xA7;
		3: noise := 0xA8;
		endcase
    0xd3://black bear and polar
    0xd5:
		case (randomint(5))
		0: noise := 0x60;
		1: noise := 0x61;
		2: noise := 0x62;
		3: noise := 0x63;
		3: noise := 0x64;
		endcase
    0xdd://Walrus
        case (randomint(2))
        0: noise := 0xE1;
        1: noise := 0xE2;
        endcase
    0xDF://sheep
    0xCF:
		case (randomint(2))
		0: noise := 0xD7;
		1: noise := 0xD8;
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