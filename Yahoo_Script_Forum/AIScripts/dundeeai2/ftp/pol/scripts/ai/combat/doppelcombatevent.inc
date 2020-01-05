function process_combat_event(ev)

	spellattack(ev.source);
        case (ev.type)
                EVID_DAMAGED: 
			check_for_change();
                       	if (will_cast)
                       		if ( me.hp < (me.strength/2))
                                	CastSpell(me,me,"gheal");
					if( cint(getobjproperty(me, "poison_level")>1) )
						CastSpell(me,me,"cure");
                       			endif
                       		endif
                       	endif
                        if ((me.hp * 100/me.maxhp) < flee_point)
				Eraseobjproperty(me,"#flees");
                                flee(ev.source);
                        endif
        endcase

endfunction

function spellattack(opponent)


	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	if (RandomInt(2)=1)
		sleep(1);
		cast_offensive_spell(me,opponent);
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
	elseif ( (will_breathe) and (randomint(3) = 1) )
		breathe_meteor(me);
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);
	else
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
        endif

	check_for_change();

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

	if ( loops > 50 )
		flee(opponent);
		return;
	endif

endfunction       

function post_combat()
  
	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	summons := 1;

	sleep(1);
	look_around();

endfunction

function prepare_for_fight(opponent)

	if (GetObjProperty(me, "mr") != "1")
		setobjproperty(me, "mr", "1");
	endif

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function breathe_meteor( caster )
    local parms := array;
    

    local targets := ListMobilesInLineofSight(me, 4);
    PerformAction(me,0x0c);

    foreach mobile in targets
      
	   Local dmg := randomint((cint(70* me.hp)/me.maxhp))+5;
	   PlayMovingEffect(caster, mobile ,MOVING_EFFECT_FIREBALL, 10,1,1);
	   applydamage(mobile, dmg);          
	
    endforeach


endfunction


function check_for_change()

if (me.hp < (me.strength /5))
        if (num_changes >= len(graphics))
                return;
        else
                num_changes := num_changes + 1;
                me.hp := me.strength;
                local parm := splitwords(graphics[num_changes]);
                local form := cint(parm[1]);
                print ("graphic is " + form);
                local clr := cint(parm[2]);
                will_cast := cint(parm[4]);
                will_breathe := cint(parm[3]);
                me.graphic := form;
                me.color := clr;
                printtextabove(me, "The creature changes shape!");
       endif
endif

endfunction
