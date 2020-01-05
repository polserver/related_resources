function GetProps()

   reqev.+group;
   reqev.+groupid;
   reqev.+template;
   reqev.+source;
   reqev.+type;
   
   reqev.source := GetPid();
   reqev.type := EV_REQUEST_TEMPLATE;
      
   repeat
      sleepms(10);
      groupmanager := GetGlobalProperty("#groupmanagerpid");
   until(groupmanager);
   groupmanager := GetProcess(groupmanager);
   
   var num;
   repeat
      sleepms(10);
      num := GetObjProperty(manager, "num");
   until(num);

   prop.+regnum;
   prop.+type;
   prop.+num;
   prop.regnum := num;

   load_region_data();
   
endfunction

function SetProps()

   SetGlobalProperty("#regionmanager"+prop.regnum, reqev.source);
   SetObjProperty(manager, "#mypid", reqev.source);

endfunction

function load_region_data()

   Syslog("[Region Manager#"+prop.regnum+"] Reading definitions...");
   var regionelem := OpenDataFile(REGION_DATAFILE).FindElement(prop.regnum);
   
   if(!regionelem)
      Syslog("[Region Manager#"+prop.regnum+"]Exception detected: no element defines region #"+prop.regnum);
      DestroyItem(manager);
      exit;
   endif

   var regiontmp;
   CreateNewRegion(regiontmp);
   
   regiontmp.name := regionelem.GetProp("name");
   regiontmp.rects := regionelem.GetProp("rects");
   regiontmp.groups := regionelem.GetProp("groups");
   regiontmp.specials := regionelem.GetProp("specials");
   regiontmp.enabled := regionelem.GetProp("enabled");
   regiontmp.serial := regionelem.GetProp("serial");
   
   enabled := regiontmp.enabled;
   
   if(regiontmp.serial <> manager.serial)
      Syslog("[Region Manager#"+prop.regnum+"]Exception detected: regionfile holds an invalid serial. Fixing...");
      regionelem.SetProp("serial", manager.serial);
   endif

   groups := regiontmp.groups;
   BuildGroupsQueue();
   
   specials := regiontmp.specials;
   BuildSpecialsQueue();
   
   rects := regiontmp.rects;
   
   SetName(manager, regiontmp.name + " manager");
   Syslog("[Region Manager#"+prop.regnum+"] Done reading definitions.");
   
   reload := 0;
   
endfunction

function MoveManager()

   var rndx, rndy, newx, newy, newz, num;
   manager.movable := 1;
   repeat
      num := Cint(RandomInt(rects.size()))+1;
      rndx := rects[num].toloc.x - rects[num].fromloc.x + 1;
      rndy := rects[num].toloc.y - rects[num].fromloc.y + 1;
      newx := rects[num].fromloc.x + Cint(RandomInt(rndx));
      newy := rects[num].fromloc.y + Cint(RandomInt(rndy));
      newz := GetWorldHeight(newx, newy);
   until(MoveItemToLocation(manager, newx, newy, newz, 0) or !manager);
   manager.movable := 0;

endfunction

function SetGroupsArray()

   var grouparray := array;
   foreach group in groups
      grouparray.append(Cint(group.total - group.resqueue.size()));
   endforeach
   
   SetObjProperty(manager, "grouparray", grouparray);

endfunction

function SetSpecialsArray()

   var specialarray := array;
   foreach special in specials
      specialarray.append(Cint(special.total - special.resqueue.size()));
   endforeach
   
   SetObjProperty(manager, "specialarray", specialarray);

endfunction

function ClearRegionSpawn()

   var maxdist;
   var center := struct;
   center.+x;
   center.+y;
   center.+z;
   var npcprop;
   var npcs;
   
   foreach rect in rects
   
      maxdist := Max(rect.toloc.x - rect.fromloc.x, rect.toloc.y - rect.fromloc.y) + 100;
      center.x := CInt((rect.fromloc.x + rect.toloc.x)/2);
      center.y := CInt((rect.fromloc.y + rect.toloc.y)/2);
      center.z := GetWorldHeight(center.x, center.y);
      
      npcs := ListMobilesNearLocationEx(center.x, center.y, center.z, maxdist, 0x3);
      foreach npc in npcs
         npcprop := GetObjProperty(npc, "spmanager");
         if(npcprop.regnum == prop.regnum)
            EraseObjProperty(npc, "spmanager");
            SetObjProperty(npc, "guardkill", 1);
            ApplyRawDamage(npc, GetHp(npc)+5);
         endif
      endforeach
   
   endforeach

   if(ev.type == EV_CLEAR_REGION)
      SetObjProperty(manager, "grouparray", 0);
      SetObjProperty(manager, "specialarray", 0);
      BuildGroupsQueue();
      BuildSpecialsQueue();
   endif

endfunction

function BuildGroupsQueue()

   var clock := ReadGameClock();
   var timer;
   
   var res_array := GetObjProperty(manager, "grouparray");
   for i := 1 to groups.size()
      if(groups[i].resqueue == error)
         groups[i].+resqueue;
      endif
      groups[i].resqueue := array;
      groups[i].restime := groups[i].restime*60;
      timer := clock;
      for j := 1 to (groups[i].total - CInt(res_array[i]))
         timer := timer + groups[i].restime;
         groups[i].resqueue.append(timer);
      endfor
   endfor

endfunction

function BuildSpecialsQueue()

   var clock := ReadGameClock();
   var timer;
   
   var res_array := GetObjProperty(manager, "specialarray");
   for i := 1 to specials.size()
      if(specials[i].resqueue == error)
         specials[i].+resqueue;
      endif
      specials[i].resqueue := array;
      specials[i].restime := specials[i].restime*60;
      timer := clock;
      for j := 1 to Cint(specials[i].total - CInt(res_array[i]))
         timer := timer + specials[i].restime;
         specials[i].resqueue.append(timer);
      endfor
   endfor

endfunction

function Max(x, y)

   if(x > y)
      return x;
   endif
   return y;

endfunction

function FlashSpawnQueues()

   for i := 1 to groups.size()
      for j := 1 to (groups[i].resqueue.size())
         groups[i].resqueue[j] := 1;
      endfor
   endfor
      
   for i := 1 to specials.size()
      for j := 1 to (specials[i].resqueue.size())
         specials[i].resqueue[j] := 1;
      endfor
   endfor

endfunction