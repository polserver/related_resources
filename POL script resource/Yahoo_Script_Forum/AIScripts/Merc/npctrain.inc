//FIXME: Optimise & bugfix this file.

Const UOBJECT_ARROW := 0xf3f;
Const UOBJECT_BOLT := 0x1bfb;
Const UOBJECT_FIREBOLT := 0x6051;
Const SFX_SHOT := 0x235;
Const SFX_ARROWHIT1 := 0x224;
Const SFX_ARROWHIT2 := 0x225;

Const GFX_ARROW_FLIGHT := 0x0f42;
Const GFX_BOLT_FLIGHT := 0x1bfe;


function Getweapon()

	local skillid := me.weapon.skillid;
	if( !skillid )
	    skillid := SKILLID_WRESTLING;
	endif
	return skillid;

endfunction


function trainonbutte(butte)

	if (!CheckLineOfSight( me, butte ))
	        Say( "I cant see that" );
        	return;
	endif

	local skillid := Getweapon();

	if (skillid != SKILLID_ARCHERY )
		say( "I need to equip a bow or crossbow." ); //make this automatic
		return;
	endif

	local skill := GetSkill(me,Getweapon());
	if(skill > 70 )
		say("I need a moving target to get any better.");
		return;
	endif

	if (!RunFromButte(Butte))
		return;
	endif

	local ammunitiontype, panim, effect;
	local trainingtime := ReadGameClock()+200+randomint(120);
	local str := me.strength - me.strength_mod, dex := me.dexterity - me.strength_mod;
	local ev;
	local flying_arrow;
	local count := 0;
	local used_ammo :=0;

	local itemtype := GetObjType( me.weapon );

	if ( itemtype = 0x13b2 ) // bow
		ammunitiontype := UOBJECT_ARROW;
		panim := ANIM_ATTACK_BOW;
        effect := GFX_ARROW_FLIGHT;		
	elseif (( itemtype = 0xf4f ) or ( itemtype = 0x13fd )) //xbow
		ammunitiontype := UOBJECT_BOLT;
		panim := ANIM_ATTACK_XBOW;
        effect := GFX_BOLT_FLIGHT;	
	elseif (( itemtype = 0x6050 )) //fire
		ammunitiontype := UOBJECT_FIREBOLT; //FIXME: make butte able to hold firearrows
		panim := ANIM_ATTACK_BOW;
        effect := GFX_ARROW_FLIGHT;	
		say ("These arrows seem to burn up upon impact.");
	else
		say ("These arrows wont work with this butte");
		return; 
	endif


	if (ammunitiontype = UOBJECT_ARROW)
		used_ammo := GetObjProperty( butte , "arrows" );
		if(!used_ammo)
			used_ammo := 0;
			SetObjProperty( butte , "arrows" , 0 );
		endif
	elseif (ammunitiontype = UOBJECT_BOLT)
		used_ammo := GetObjProperty( butte , "bolts" );
		if(!used_ammo)
			used_ammo := 0;
			SetObjProperty( butte , "bolts" , 0 );
		endif
	endif



	while ( ReadGameClock() < trainingtime )

		ev := wait_for_event( 5 );
		case (ev.type)
			EVID_ENGAGED:
			EVID_DAMAGED:
				return;
			EVID_SPEECH:
				if (!ev.source.npctemplate)
					local evtext := lower(ev.text);
					if (ev.source.serial = masterserial)
						if (evtext["stop"])
							say("Okay");
							setwarmode(0);
							turntoward(master);	
							return;
						endif
					else
						say("I am busy at the moment.");
					endif
				endif
		endcase

		flying_arrow := DrawArrow(ammunitiontype);
		
		if (!flying_arrow)
			while ( distance(butte,me)>1 )
				RunToward(butte);
				count:=count + 1;
				if (count>10)
					say("No ammo left.");
					return;
				endif
			endwhile
			count := 0;
			GrabAmmo(me, butte);
			used_ammo := 0;
			sleepms(500);
			
			flying_arrow := DrawArrow(ammunitiontype);
			
			if (!flying_arrow)
				say("Im out of ammo.");
				return;
			else
				if (!RunFromButte(Butte))
					return;
				endif
			endif
		endif

		TurnToward(butte);

		if( CheckSkill( me , SKILLID_ARCHERY , 10 , 200 ) )
			PerformAction( me, panim );
			sleepms(GetSleepDelayms());
			PlayMovingEffectXYZ( me.x, me.y, me.z+9, butte.x, butte.y, butte.z+5, effect, 10, 0, 0 );
			sleep(1);
			PlaySoundEffect( me, SFX_SHOT );
			say( "What a good shot!" );

			used_ammo := used_ammo + 1;

		else
			PerformAction( me, panim );
			sleepms(GetSleepDelayms());
			PlayMovingEffectXYZ( me.x, me.y, me.z+9, butte.x+randomInt(3), butte.y+randomInt(3), butte.z+5, effect, 10, 0, 0 );
			sleep(1);
			PlaySoundEffect( me, SFX_ARROWHIT1 );
			say( "Damnit I missed!" );
			//used_ammo := used_ammo + 1; //if we miss, we lose the arrow
		endif

			if( ammunitiontype = UOBJECT_ARROW )
			   SetObjProperty( butte , "arrows" , used_ammo);
			elseif( ammunitiontype = UOBJECT_BOLT )
			   SetObjProperty( butte , "bolts" , used_ammo);
			endif

		if (flying_arrow.amount > 1)
			local amnt := flying_arrow.amount;
			DestroyItem(flying_arrow);
			CreateItemInBackpack( me,ammunitiontype , amnt-1); //THERE MUST be a better way
		else
			DestroyItem(flying_arrow);
		endif

		check_for_gain(str,dex,skill);

	endwhile

endfunction

function DrawArrow(ammunitiontype)
	foreach item in EnumerateItemsInContainerOfObjType(me.backpack, ammunitiontype )
		return item;
	endforeach
	return 0;
endfunction


function GrabAmmo( who , butte);

    CreateItemInBackpack( who , UOBJECT_ARROW , GetObjProperty( butte , "arrows") / 2 );
    CreateItemInBackpack( who , UOBJECT_BOLT , GetObjProperty( butte , "bolts") / 2 );

    //say( "I grab " + used_arrows + " arrows and " + used_bolts + " bolts from the butte." );

    SetObjProperty( butte , "arrows" , 0 );
    SetObjProperty( butte , "bolts" , 0 );

endfunction


function RunFromButte(butte)
	local count := 0;
	while(Distance(me, Butte) > 6)
		RunToward(butte);
		count:=count + 1;
		if (count>10)
			say ("I cant find a good spot to shoot from.");
			return 0;
		endif
	endwhile
	count := 0;
	while ( distance(butte,me)<3 )
		RunAwayfrom(butte);
		count:=count + 1;
		if (count>10)
			say ("I cant find a good spot to shoot from.");
			return 0;
		endif
	endwhile

	return 1;
endfunction



function trainondummy(dummy)

	local skillid := Getweapon();

	if( GetSkill(me,skillid) > 60 )
		say("I cannot learn anymore with this weapon on this dummy.");
	endif

    case (skillid)
    	SKILLID_MACEFIGHTING: 
			say("Im training macefighting skills");
			CheckSwing( me , skillid , ANIM_ATTACK_1HAND_DOWN , dummy );
    	SKILLID_FENCING: 
			say("Im training my fencing skills");
			CheckSwing( me , skillid , ANIM_ATTACK_1HAND_JAB , dummy );
    	SKILLID_SWORDSMANSHIP: 
			say("Im training my swordfighting skills");
			CheckSwing( me , skillid , ANIM_ATTACK_1HAND_WIDE , dummy );
    	SKILLID_WRESTLING: 
			say("Im training my wrestling skills");
			CheckSwing( me , skillid , 0x9 , dummy );
    	default: 
		    say("I cannot train.");
    endcase

endfunction

function CheckSwing( who , skillid , action , dummy )

	local trainingtime := ReadGameClock()+200+randomint(120);
	local ev;
	local str := me.strength;
	local dex := me.dexterity;
	local skill := GetSkill(me,Getweapon());

	local count;
	while ( distance(dummy,me)>1 )
		RunToward(dummy);
		count:=count + 1;
		if (count>10)
			say ("I cant get there");
			return;
		endif
	endwhile

	while ((distance(dummy,me)<2) and (ReadGameClock() < trainingtime) )

		TurnToward(dummy);

		ev := wait_for_event( 5 );
		case (ev.type)
			EVID_ENGAGED:
			EVID_DAMAGED:
				return;
			EVID_SPEECH:
				if (!ev.source.npctemplate)
					local evtext := lower(ev.text);
					local mename := lower(me.name);
					if (ev.source.serial = masterserial)
						if ( evtext["stop"] )
							say("Okay");
							setwarmode(0);
							turntoward(master);	
							sleep(1);
							return;
						endif
					else
						say("I am busy at the moment.");
					endif
				endif
		endcase

	   PerformAction( who , action );
	   Sleepms(GetSleepDelayms());

	   if( CheckSkill( who , skillid , 10 , 200 ) )


		   PlaySoundEffect( who , SFX_13C ); // hit sound

		   if ( dummy.objtype = UOBJ_DUMMYFREEZE_NS )
				dummy.graphic := UOBJ_DUMMYSWING_NS; // dummy swing
				sleepms(3600); // show animation for (x) ms
				dummy.graphic := UOBJ_DUMMYFREEZE_NS; // dummy freeze

		   elseif ( dummy.objtype = UOBJ_DUMMYFREEZE_EW )
				dummy.graphic := UOBJ_DUMMYSWING_EW; // dummy swing
				sleepms(3600); // show animation for (x) ms
				dummy.graphic := UOBJ_DUMMYFREEZE_EW; // dummy freeze
		   endif

			check_for_gain(str,dex,skill);

		else

		   PlaySoundEffect( who , SFX_239 ); // missing sound
		   Sleepms(GetSleepDelayms()*2);
		endif

	endwhile

	say("I tire of this activity.");

endfunction


function check_for_gain(byref str, byref dex, byref skill)

	if (me.strength - me.strength_mod>str)
		if (!npc_statcap())
			say("I am gaining strength!");
		endif
		str := me.strength - me.strength_mod;
	endif
	if (me.dexterity - me.dexterity_mod>dex)
		if (!npc_statcap())
			say("I am gaining stamina!");
		endif
		dex := me.dexterity - me.dexterity_mod;
	endif
	if (GetSkill(me,Getweapon())>skill)
		say("I feel more skillfull!");
		skill := GetSkill(me,Getweapon());
	endif

endfunction


function anatomy( )
 
 local str := me.strength - me.strength_mod;
 local dex := me.dexterity - me.dexterity_mod;
 local dexdesc;
 local strdesc;
 
 // Strength Description
 if (str <= 9)
  strdesc := "would have trouble lifting small objects" ;
 elseif (str >= 10 and str <= 19)
  strdesc :=  "am rather feeble";
 elseif (str >= 20 and str <= 29)
  strdesc :=  "am somewhat weak"; 
 elseif (str >= 30 and str <= 39)
  strdesc := "am of normal strength";
 elseif (str >= 40 and str <= 49)
  strdesc := "am somewhat strong";
 elseif (str >= 50 and str <= 59)
  strdesc := "am very strong";
 elseif (str >= 60 and str <= 69)
  strdesc := "am extremely strong";
 elseif (str >= 70 and str <= 79)
  strdesc := "am extraordinarily strong"; 
 elseif (str >= 80 and str <= 89)
  strdesc := "am strong as an ox";
 elseif (str >= 90 and str <= 99)
  strdesc := "am one of the strongest people you have ever seen";
 elseif (str >= 100)
  strdesc := "am superhumanly strong";
 endif  

 // Dexterity Description

 if (dex <= 9)
  dexdesc := "can barely manage to stay standing";
 elseif (dex >= 10 and dex <= 19)
  dexdesc := "very clumsy";
 elseif (dex >= 20 and dex <= 29)
  dexdesc := "somewhat uncoordinated";
 elseif (dex >= 30 and dex <= 39)
  dexdesc := "moderately dextrous";
 elseif (dex >= 40 and dex <= 44)
  dexdesc := "somewhat agile";
 elseif (dex >= 45 and dex <= 49)
  dexdesc := "quite agile";
 elseif (dex >= 50 and dex <= 59)
  dexdesc := "very agile";
 elseif (dex >= 60 and dex <= 69)
  dexdesc := "extremely agile";
 elseif (dex >= 70 and dex <= 79)
  dexdesc := "extraordinarily agile";
 elseif (dex >= 80 and dex <= 89)
  dexdesc := "can move like quicksilver";
 elseif (dex >= 90 and dex <= 99)
  dexdesc := "im one of the fastest people you have ever seen";
 elseif (dex >= 100)
  dexdesc := "superhumanly agile";
 endif

  return ("I " +strdesc + " and "+ dexdesc +".");     

endfunction

function GetSleepDelayms()

	local sleepdelay := 300 - (CInt(me.dexterity) * 1.5);
	if (sleepdelay < 0) sleepdelay := 0; endif
	return sleepdelay;

endfunction