KARMA/FAME SYSTEM

by Developer Link


// Thank yous go out to WoD for their example of this about 7 months ago, 
the karma/fame.inc file was made by me and me only, it goes in your pol/scripts/include directory

---------------------------------------------------------------------



Ok, he is a little tutorial for karma/fame

in the monster ai script fight.inc, where it gets damaged/engaged ;
after if(ev.source) add
AddToHitList(ev);

then in the bottom of that file, 

function AddToHitList (ev)
 
 if (ev.type != EVID_DAMAGED or ev.source.npctemplate)
  return;
 endif

 if (!ev.source.serial)
  return;
 endif

 local hitlist := GetObjProperty (me, "hitlist");
 if (!hitlist)
  hitlist := {};
 endif

 if (ev.source.serial in hitlist)
  return;
 endif

 hitlist.append (ev.source.serial);
 SetObjProperty (me, "hitlist", hitlist);
endfunction


----------------------------------------------------

THEN:

in the death.src you need to find MakeLoot() and place it inside the if and the else

so

If(blah)
----
      AwardKarmaFame(corpse, npctemplate);
else
       AwardKarmaFame(corpse, npctemplate);
endif

to get your npc to give karma/fame, 

in your npcdesc.cfg add 
karma #
fame #
