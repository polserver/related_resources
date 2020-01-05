  use uo;
  use cfgfile;
  include "include/canAccess";
  include "include/attributes";
  var success, fail;
  
  function playmusic(who, item, what)
  
    case(item.graphic)
     	0x0eb1:  success := 0x44;  fail := 0x45;
  		0x0eb2:  success := 0x46;  fail := 0x47;
  		0x0eb3:  success := 0x4d;  fail := 0x4e;
  		0x0eb4:  success := 0x4d;  fail := 0x4e;
  		0x0e9c:  success := 0x39;  fail := 0x3a;
  		0x0e9d:  success := 0x53;  fail := 0x54;
  		0x0e9e:  success := 0x53;  fail := 0x54;
    endcase
    if(what == success)
    	PlaySoundEffect(who, success);
  	else
  		PlaySoundEffect(who, fail);
  	endif
    return;
  	
  endfunction
  
  function skillcheck(who, songnumber)
  
     var cfgfile := ReadConfigFile(":musicianship:songs");
     var getsong := FindConfigElem(cfgfile, songnumber);
     var diff    := GetConfigInt(getsong, "Difficulty");
     var points  := diff*5;
  
     if(CheckSkill(who, SKILLID_MUSICIANSHIP, diff, points))
        return 1;
     else
     playsoundeffect(who, fail);
     endif
  
  endfunction
  
  function checkifcansing(who, type)
  
    if(type != "music")
      if(GetObjProperty(who, type))
        if(GetObjProperty(who, type) > ReadGameClock())
          SendSysMessage(who, "You must wait until you can play this song!");
          return 0;
        else
          SetObjProperty(who, type, ReadGameClock() + 20);
          return 1;
        endif
      else
        SetObjProperty(who, type, ReadGameClock() + 10);
         return 1;
      endif
    else
      return 1;
    endif
  
  endfunction
  
  function findinstrument(who)
    var instruments := {0x0eb1, 0x0eb2, 0x0eb3, 0x0eb4, 0x0e9c, 0x0e9d, 0x0e9e};
    foreach item in EnumerateItemsInContainer(who.backpack)
      if(item.graphic in instruments)
        return item;
      endif
    endforeach
  endfunction


	////////////////
	// Just Play	//
  ////////////////

  function just_play(who)
  
  var startx := who.x;
  var starty := who.y;
  var startz := who.z;
  var item := findinstrument(who);
  
  if (!item)
  	SendSysmessage(who, "You don't have an instrument to play!");
    return;
  endif
  
  var nearby := listmobilesnearlocation(who.x, who.y, who.z, 3);
  var diff := len(nearby) * 5;
  var exitit := 0;
  var mob;
  
  while (!exitit)
  	playmusic(who, item, success);
  
  	if(CheckSkill(who, SKILLID_MUSICIANSHIP, diff, -1))
  		setobjproperty(who, "#singing", 1);
    		foreach mob in nearby
      		if (distance(who, mob) <= 3)
        		var parms := {};
          	if (getobjproperty(who, "#bardsing") != who.serial)
          		setobjproperty(mob, "#bardsing", who.serial);
            	parms[1] := mob;
            	parms[2] := who;
            	SendSysMessage (mob, "You hear a wonderful tune playing",3,90);
          	endif
       	 	endif
      	endforeach
    	nearby := listmobilesnearlocation(who.x, who.y, who.z, 3);
  	else
    	exitit := 1;
    	sendsysmessage(who, "You miss a note, and your song ends");
 		endif
  
  	sleep(1);
  
  	if ((who.x = startx and who.y = starty and who.z = startz)&&(who.graphic = 400 or who.graphic = 401 or who.graphic = 987))
  		nearby := listmobilesnearlocation(who.x, who.y, who.z, 3);
    	diff := len(nearby) * 5;
  	else
    	exitit := 1;
  	endif
  
  endwhile
  
	endfunction
  
  function tell(who, msg)
  if (who.cmdlevel)
        sendsysmessage(who, msg);
  endif
  endfunction

  function staminasong(who)
  	var item := findinstrument(who);
  	var critter := POLCLASS_MOBILE;
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  
  	if (!item)
          	SendSysmessage(who, "You don't have an instrument to play!");
          	return;
  	endif
  
    if(!checkifcansing(who, "regular"))
    	return;
    endif
  
  	if(skillcheck(who, 5))
  	 var length := GetEffectiveSkill(who, SKILLID_MUSICIANSHIP)/RandomDiceRoll("4d5");
  	 var hamount := GetEffectiveSkill(who, SKILLID_PEACEMAKING)/RandomDiceRoll("4d3");
  
  	 while (length > 0)
  		if (who.x = startx and who.y = starty and who.z = startz and who.graphic = 400 or who.graphic = 401)
  			playmusic(who, item, success);
  	  	foreach critter in ListMobilesNearLocation(who.x, who.y, who.z, 5)
  		  	local oldstamina := GetStamina(critter);
  	      SendSysMessage(critter, "Your backpack feels lighter while listening to the music",3,90);
  	      SetStamina(critter, oldstamina+hamount);
  		 	endforeach
  		 	length := length - 1;
  		 	sleep(8);
  		else
  		  SendSysMessage(who, "you stop playing");
  		  return 0;
  		endif
  	 endwhile
   	 return 0;
  	endif
  	 SendSysMessage(who, "You fail to play well");
  	 PlayMusic(who, item, fail);
  endfunction
  
  function play_resurrect( who )
  	
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  	var item := findinstrument(who);
  
    if(!checkifcansing(who, "regular"))
     		return;
    endif
  
  	var use_on := Target (who, TGTOPT_HELPFUL + TGTOPT_CHECK_LOS);
  	var instrument := findinstrument(who);
  
  	if(!skillcheck(who, 7))
  		playmusic(who, item, fail);
  		return 0;
  	else
  		playmusic(who, item, success);
  	endif
  
  	if (!use_on)
  		return 0;
  	endif
  	
  	if(!use_on.dead)
  		sendsysmessage(who, "Thats not dead");
  		return 0;
  	endif
  
   	resurrect(use_on);
  	sendsysmessage(use_on, "The tune brought you back from the dead");
  
  endfunction
  
  function manasong(who)
  	var item := findinstrument(who);
  	var critter := POLCLASS_MOBILE;
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  
    if(!checkifcansing(who, "regular"))
    	return;
    endif
  
  	if (!item)
    	SendSysmessage(who, "You don't have an instrument to play!");
     	return;
  	endif
  
  	if(skillcheck(who, 4))
  	 var length := GetEffectiveSkill(who, SKILLID_MUSICIANSHIP)/RandomDiceRoll("4d5");
  	 var hamount := GetEffectiveSkill(who, SKILLID_PEACEMAKING)/RandomDiceRoll("4d5");
  
  	 while (length > 0)
  		if (who.x = startx and who.y = starty and who.z = startz and who.graphic = 400 or who.graphic = 401)
  			if(!skillcheck(who, 4))
  				SendSysMessage(who, "You miss a note and your song ends");
  				PlayMusic(who, item, fail);
  				return 0;
  			endif
  		 playmusic(who, item, success);
  	   foreach critter in ListMobilesNearLocation(who.x, who.y, who.z, 5)
  		 	local oldmana := GetMana(critter);
  	    SendSysMessage(critter, "The song seems to calm you.",3,90);
  	    SetMana(critter, oldmana+hamount);
  		 endforeach
  		 length := length - 1;
  		 sleep(8);
  		else
  		  SendSysMessage(who, "you stop playing");
  		  return 0;
  		endif
  	 endwhile
   	 return 0;
  	endif
  	
  	SendSysMessage(who, "You fail to play well");
  	PlayMusic(who, item, fail);
  endfunction
  
  function group_reflect(who)
  	var item := findinstrument(who);
  	var critter := POLCLASS_MOBILE;
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  
  	if(GetObjProperty(who, "reflect") > ReadGameClock())
  		SendSysMessage(who, "You cant play this song yet");
  		return;
  	endif
  
  	if(GetObjProperty(who, "regular") > ReadGameClock())
  		SendSysMessage(who, "You cant play this song yet");
  		return;
  	endif
  
  	if (!item)
    	SendSysmessage(who, "You don't have an instrument to play!");
      return 0;
  	endif
  
  	if(skillcheck(who, 3))
  
  		playmusic(who, item, 1);
  		sleepms(10);
  		foreach critter in ListMobilesNearLocation(who.x, who.y, who.z, 5)
   			var cfg  := ReadConfigFile("::npcdesc");
   		  var elem := cfg[critter.npctemplate].elemental;
  	    SendSysMessage(critter, "You suddenly feel magically protected.",3,90);
  	    PlaySoundEffect(critter, 0x1ea);
  		  PlayObjectCenteredEffect( critter, FX_SPARK_EFFECT, 10,10);
  		  SetObjProperty(critter, "mr","1");
  		endforeach
      SetObjProperty(who, "reflect", ReadGameClock() + 60);
   	 	return 0;
   	 	
  	endif
  
  SendSysMessage(who, "You fail to play well");
  PlayMusic(who, item, fail);
  
  endfunction
  
  function group_sight(who)
  	var item := findinstrument(who);
  	var critter := POLCLASS_MOBILE;
  	var duration := GetEffectiveSkill(who, SKILLID_MUSICIANSHIP);
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  
    if(!checkifcansing(who, "regular"))
      return;
    endif
  
  	if (!item)
    	SendSysmessage(who, "You don't have an instrument to play!");
      return 0;
  	endif
  
  	if(skillcheck(who, 6))
  
  	  foreach critter in ListMobilesNearLocation(who.x, who.y, who.z, 5)
  	  	playmusic(who, item, success);
   		  var cfg  := ReadConfigFile("::npcdesc");
   		  var elem := cfg[critter.npctemplate].elemental;
    	  PlaySoundEffect(critter, SFX_SPELL_NIGHT_SIGHT );
  		  PlayObjectCenteredEffect( critter, FX_BLESS_EFFECT, 10,10);
  			critter.setlightlevel( 0, duration * 60 );
  		endforeach
   	 	return 0;
  	endif
  
  SendSysMessage(who, "You fail to play well");
  PlayMusic(who, item, success);
  
  endfunction
  
  function g_resurrect( who )
  
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  	var item := findinstrument(who);
  	var ghosts := ListGhostsNearLocation(who.x, who.y, who.z, 10);
  	
  	broadcast(ghosts);
  
  	if(!checkifcansing(who, "regular"))
    	return;
    endif
  
  	var instrument := findinstrument(who);
  
  	if(!skillcheck(who, 8))
  		playmusic(who, item, fail);
  		broadcast("failed");
  		sleep(1);
  		return 0;
  	else
  		playmusic(who, item, success);
  		sleep(1);
  		broadcast("success");
  	endif
  
  	foreach mobile in ghosts
  		if(!mobile.graphic == 402)
  			BroadCast("not dead, error");
  		else
  			var dice := randomdiceroll("d3");
  			if(dice == 1)
  				resurrect(mobile);
  				sendsysmessage(mobile, "The tune brought you back from the dead");
  			endif
  		endif
  	endforeach
  
  endfunction
  
  
  function group_healing(who)
  
  	var critter := POLCLASS_MOBILE;
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  	var item   := findinstrument(who);

    if(!checkifcansing(who, "regular"))
      return;
    endif
  
  	if (!item)
     	SendSysmessage(who, "You don't have an instrument to play!");
     	return;
  	endif
  	
  	if(!skillcheck(who, 1))
  		SendSysMessage(who, "You fail to play well");
  		PlayMusic(who, item, fail);
  		sleep(1);
  	else
  		Playmusic(who, item, success);
  	endif
  	 	var length := GetEffectiveSkill(who, SKILLID_MUSICIANSHIP)/RandomDiceRoll("4d5");
  	 	var hamount := GetEffectiveSkill(who, SKILLID_PEACEMAKING)/RandomDiceRoll("4d5");
  
  	 	while (length > 0)
  			if(who.graphic = 400 or who.graphic = 401 or who.graphic = 987)
  				if (who.x = startx and who.y = starty and who.z = startz)
  		 			playmusic(who, item, success);
  		 			ReserveItem( item );
  	        	foreach critter in ListMobilesNearLocation(who.x, who.y, who.z, 5)
  		  				var cfg  := ReadConfigFile("::npcdesc");
   		  				var elem := cfg[critter.npctemplate].elemental;
  		  				if(!elem)
  	        			SendSysMessage(critter, "The song fills you heart with hope.",3,90);
  	          		HealDamage(critter, hamount + 10);
  		  				endif
  		  				if(elem == "undead")
  		    				Damage(critter, hamount + 10);
  		    				PlayLightningBoltEffect(critter);
  		  				endif
  		 				endforeach
  		 			length := length - 1;
  		 			sleep(8);
  				else
  		  		SendSysMessage(who, "you stop playing");
  		  		return 0;
  				endif
  			else 
  		  	SendSysMessage(who, "you stop playing");
  		  	return 0;
  			endif
  	 	endwhile
  endfunction
  
  function play_mez( who )
  	var startx := who.x;
  	var starty := who.y;
  	var startz := who.z;
  
    if(!checkifcansing(who, "regular"))
    	return;
    endif
  
  	var use_on := Target (who, TGTOPT_HARMFUL + TGTOPT_CHECK_LOS);
  	var item := findinstrument(who);
  
  	if(!skillcheck(who, 2))
  		playmusic(who, item, fail);
  		return 0;
  	else
  		playmusic(who, item, success);
  	endif
  
  	if (!use_on)
  		return 0;
  	endif
  
  	var time := 2 + CInt(GetEffectiveSkill(who,SKILLID_PROVOCATION))/RandomDiceRoll("2d5");
  
  	while(time > 0)
  
      if(who.x = startx and who.y = starty and who.z = startz)
  			if(!skillcheck(who, 2))
  				playmusic(who, item, fail);
  				sendsysmessage(who,  "You miss a note, and your song ends");
  				return 0;
  			endif
  		playmusic(who, item, success);
  		use_on.frozen := 1;
  		time := time -1;
  		sleep(8);
      else
  		sendsysmessage(who, "You stop playing");
  		use_on.frozen := 0;
  		sleep(5);
  		return;
  		endif
  
  	endwhile
  
  	use_on.frozen := 0;
  	sendsysmessage(who, "You stop playing");
  	sleep(5);
  
  endfunction
