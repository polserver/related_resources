function sleepmode()

	foreach critter in ListMobilesNearLocation( me.x,me.y,me.z, 10 );
          if (!critter.npctemplate)
		return 0;
          endif
	endforeach

	if (GetObjProperty(me,"killme"))
		ApplyRawDamage(me,me.hp+1);
	endif

	Eraseobjproperty(me,"#flees");

	DisableMainEvents();
	if (/*GetAttribute( me, "Hiding" )*/ GetSkill( me, 21) > 0 )
                me.hidden := 1;
		EnableEvents(SYSEVENT_ENTEREDAREA,4);
	else
		EnableEvents(SYSEVENT_ENTEREDAREA,18);
	endif

	EnableEvents(SYSEVENT_ENGAGED);
	EnableEvents(SYSEVENT_DAMAGED);

	local ev;

	while (1)
		ev := os::wait_for_event( 120 );

		repeat

		case (ev.type)
            SYSEVENT_ENGAGED:
			SYSEVENT_DAMAGED:
			EVID_ALL_ATTACK_CMD:
				if (me.hidden)
					me.hidden := 0;
					say("*" + me.name + " sai de seu esconderijo!*");
				endif
				EnableMainEvents();
				return ev;
			SYSEVENT_ENTEREDAREA:
				if ( (!ev.source.npctemplate) or (ev.source.script = "tamed") )
					if (me.hidden)
                        // Gráficos dos elementais e Corpser
                        if ((me.graphic = 0x0f)or(me.graphic = 0x10)or(me.graphic = 0x0e)or(me.graphic = 0x0d)or(me.graphic = 0x08))
                            // Efeitos especiais
                            case (me.graphic)
                                0x0D://Air elemental
                                    PlaySoundEffect(me, 0x108);
                                0x0E://Earth elemental
                                    PlaySoundEffect(me, 0x10D);
                                0x0F://Fire elemental
                                    PlaySoundEffect(me, 0x116);
                                0x10://Water elemental
                                    PlaySoundEffect(me, 0x118);
                                0x08://Corpser
                                    case (randomint(2))
                                        0: PlaySoundEffect(me, 0x162);
                                        1: PlaySoundEffect(me, 0x163);
                                    endcase
                            endcase
                            var grafico := me.graphic;
                            me.graphic := 0x0; // grafico de nada (antibug, se não não aparece animaçao)
                            me.hidden := 0;
                            sleepms(200);
                            me.graphic := grafico;
                            Performaction( me, 0x000c);
                            sleep(5);
                        else
                            me.hidden := 0;
    						say("*" + me.name + " sai de seu esconderijo!*");
                        endif
    					EnableMainEvents(); // Se for um com hid, ele retorna o evento.
    					return ev;
					endif
					EnableMainEvents();     // Se nao for, ele apenas sai de sleepmode
                    return;
				endif
		endcase

		until (! (ev := os::wait_for_event(120)) );

	endwhile      

endfunction       
