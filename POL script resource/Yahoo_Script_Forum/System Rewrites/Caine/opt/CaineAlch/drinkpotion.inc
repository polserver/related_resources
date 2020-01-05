
global itemdefs := ReadConfigFile("::itemdesc");
Const POISON_SOUND := 0x247;
Const DRINK_SOUND := 0x32;
Const UOBJ_EMPTY_BOTTLE := 0x0f0e;
Const EFFECT_BLUE_SPARKLE  := 0x373a;
Const SOUND_EFFECT_CURE	:= 0x1e1; 
Const EFFECT_SPARKLE  := 0x374a;
Const HIT_ACTION := 0x148b;

Const SOUND_EFFECT_HEAL	:= 0x1f3; 

Const SKILLID_TASTEID := 36;
Const EXPLOSIONP_DELAY := 12;
Const POTIONDRINK_DELAY := 10;

function checkifcandrink(character,potion)
	
	if  ((checklineofsight(character,potion)) and (distance(character,potion) <= 1))
        if (GetObjProperty(character, "#potion"))
                if (GetObjProperty(character, "#potion") > readgameclock() )
                        SendSysmessage(character, "You must wait until you can drink another potion!");
                        return 0;
                else
                
                        eraseobjproperty(character, "#potion");
                        return 1;
               endif
        else
                SetObjProperty(character, "#potion", readgameclock() + POTIONDRINK_DELAY);
                return 1;
        endif
        else
        	sendsysmessage(character,"You can not use that from here.");
        	return 0;
	endif
endfunction

function checkusepurple(character,potion)

	if  ((checklineofsight(character,potion)) and (distance(character,potion) <= 1))
        if (GetObjProperty(character, "#exppotion"))
                if (GetObjProperty(character, "#exppotion") > readgameclock() )
                        SendSysmessage(character, "You must wait until you can use another explosion potion!");
                        return 0;
                else
                
                        eraseobjproperty(character, "#exppotion");
                        return 1;
               endif
        else
                SetObjProperty(character, "#exppotion", readgameclock() + EXPLOSIONP_DELAY);
                return 1;
        endif
        else
        	sendsysmessage(character,"You can not use that from here.");
        	return 0;
	endif
endfunction

function candrink(character)
        eraseobjproperty(character, "#potion");
endfunction

function empty_bottle(character, potion)

    PlaySoundEffect (character, DRINK_SOUND);
    CreateItemInBackpack(character, UOBJ_EMPTY_BOTTLE, 1);
    DestroyItem(potion);
    PlayObjectCenteredEffect( character, EFFECT_BLUE_SPARKLE, 10,10);  
    
endfunction

function get_potion_strength(potion)

        local potion_strength := itemdefs[potion.objtype].strength;
	return potion_strength;

endfunction

function is_poison(potion)

        local poison := itemdefs[potion.objtype].ispoison;
        if (poison)
            local poison_level := itemdefs[potion.objtype].strength;
            return poison_level;
        else
           return;
        endif

endfunction

function do_poison(character, potion)


  local potion_strength := is_poison(potion);
      
        if (checkskill(character, SKILLID_TASTEID, (potion_strength * 15),  (potion_strength * 15)))
                SendSysMessage(character, "That potion is poisonous!");
                return;
        endif
  empty_bottle(character, potion);
  PrintTextAbovePrivate (character, "You have been poisoned!", character);
  local poison_level := Cint(GetObjProperty(character, "poison_level"));

        poison_level := potion_strength;
        if (!GetPoison(character))
        	SetObjProperty (character, "poison_level",cstr(poison_level));
        endif
        
        potionpoison (character, potion_strength);

endfunction

function potionpoison (creature, potion_str)
     
    local poison_level := Cint(GetObjProperty(creature, "poison_level"));
//    print("got poison level at: " + poison_level);
    if (getpoison(creature))
//        print("already poisoned... poisoning more by: " + potion_str);
        
        SetObjProperty(creature, "poison_level", cint(poison_level) + potion_str);
 //   	print("new poison level = " + Cint(GetObjProperty(creature, "poison_level")));
    	return;
    endif
    
//    print("setting poisoned");
    setpoison(creature, 1);

//    print("creature is poisoned: " + getpoison( creature ));
    detach();
    
//Make sure that the Poison Str is correct
    poison_level := cint(GetObjProperty(creature, "poison_level")) + 1;
    SetObjProperty(creature, "poison_level", cint(poison_level));
    
    while (getpoison(creature))
        poison_level := cint(GetObjProperty(creature, "poison_level")) - 1;
//        print("after getobjprob: " + poison_level);
        
        if (poison_level >= 1)
//        print("doing poison damage at level: " + poison_level);
	        SendSysMessage(creature, 3 * poison_level + " poison damage!");
	        ApplyRawDamage(creature, 3 * poison_level);

        	PlaySoundEffect(creature, POISON_SOUND);
        	SetObjProperty(creature, "poison_level", cint(poison_level));
        	if (creature.dead)
            		SetObjProperty(creature,"poison_level", 0);
//                        print("setting unpoisoned in dead");
            		setpoison(creature, 0);
            		return;
        	endif
//        	print("time now:" + 30 / poison_level * 2);
        	sleep( 30 / poison_level * 2 );
        else
//                print("unpoision");
        	setpoison(creature, 0);
        endif
    endwhile
//    print("setting unpoisoned on way outta script");
    SendSysMessage(creature, "You feel the effects of the poison wearing off...");
//Make *double* sure creture is unpoisoned... just to be safe. ;)
    setpoison(creature, 0);
    
endfunction

// i just created these functions incase i needed to change the way poison worked...
// hehehe, apparently i needed to ;)

function SetPoison( creature, val )
    creature.poisoned := val;

endfunction

function GetPoison( creature )
    local val := creature.poisoned;
    return(val);

endfunction
