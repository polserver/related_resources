function process_combat_event(ev)

	if (spellcast)
		spellattack(ev.source);
	endif

        if (ev.type = EVID_DAMAGED)
			if ( (spellcast) and ( me.hp < (me.strength/2)) )
				CastSpell(me,me,"gheal");
				if( cint(getobjproperty(me, "poison_level")) > 1)
					CastSpell(me,me,"cure");
					CastSpell(me,ev.source,"poison");
				endif
			endif
                        if ((me.hp * 100/me.maxhp) < flee_point)
				Eraseobjproperty(me,"#flees");
                                flee(ev.source);
                        endif
        endif

endfunction

function in_combat_event_loop(opponent, loops)

	if (spellcast)
		spellattack(opponent);
	endif

	if ( loops > 50 )
		flee(opponent);
		return;
	endif

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
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	if ( (spellcast) and ( me.hp < (me.strength/2)) )
		CastSpell(me,me,"gheal");
	endif

	sleep(1);
	look_around();
	me.hidden := 1;

endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	me.concealed := 1;
	local it;
 	foreach it in listequippeditems(me)
		destroyitem(it);
	endforeach
	local p := createitematlocation(me.x, me.y, me.z, 0x0e75, 1);
	equipitem(me, p);
	me.criminal := 0;
	me.graphic := opponent.graphic;
	me.color:= opponent.color;
	me.name := opponent.name;

	foreach it in listequippeditems(opponent)
		local what := createitemincontainer(me.backpack, it.objtype, 1);
		what.color := it.color;
		what.graphic := it.graphic;
		if (it.name)
			what.name := it.name;
		endif
		equipitem(me,what);
		setobjproperty(what,"#noloot",1);
	endforeach
	me.criminal := 0;
	local oldprio := set_priority(50);

	local weaponone := GetEquipmentByLayer( me,  LAYER_HAND1 );
	local weapontwo := GetEquipmentByLayer( me,  LAYER_HAND2 );
	if ( (weaponone.objtype = 0x13B2) or (weapontwo.objtype = 0x13B2) )
		runaway:=0;
		CreateItemInInventory(me.backpack,0xf3f,50);
	elseif ( (weaponone.objtype = 0x0f4f) or (weapontwo.objtype = 0x0f4f) or 
		(weaponone.objtype = 0x13fd) or (weapontwo.objtype = 0x13fd) )
		runaway:=0;
		CreateItemInInventory(me.backpack,0x1bfb,50);
	elseif ( (weaponone.objtype = 0x0f4f) or (weapontwo.objtype = 0x0f4f) )
		runaway:=0;
		CreateItemInInventory(me.backpack,0x6051,25);
	else
		RunAway := 100;	
	endif
	me.concealed := 0;
	if ( (!weaponone) and (!weapontwo) )
		spellcast := 1;
	elseif	( (!weaponone.maxhp) and (!weapontwo.maxhp) )
		spellcast := 1;
	else
		spellcast := 0;
	endif

	EnableCombatEvents();

endfunction
