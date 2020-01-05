var regions := array;
var regionfile;

function LoadRegionsArray()

   var elem;
   var region := struct;
   region.+name;
   region.+valid;
   
   region.valid := 1;
   
   foreach key in (regionfile.keys())
      elem := regionfile.FindElement(key);
      region.name := elem.GetProp("name");
      regions[key] := region;
   endforeach

endfunction

function GetRegionSpecs(regionnum)

   var region;
   CreateNewRegion(region);
   
   var elem := regionfile.FindElement(regionnum);
   
   region.name := elem.GetProp("name");
   region.rects := elem.GetProp("rects");
   region.groups := elem.GetProp("groups");
   region.specials := elem.GetProp("specials");
   region.enabled := elem.GetProp("enabled");
   region.serial := elem.GetProp("serial");
   if(region.serial)
      region.ref := SystemFindObjectBySerial(region.serial);
      if(!region.ref)
         Syslog("Exception detected: region #"+regionnum+" holds an invalid serial.");
         elem.SetProp("serial", 0);
      endif
   endif

   return region;

endfunction

function BuildRegionGump(region)

   if((region == 0) or EntryInUse("Region", region, 1))
      return;
   endif

   var regiontmp;
   CreateNewRegion(regiontmp);
   
   if(region > 0)
      regiontmp := GetRegionSpecs(region);
   else
      region := 0;
      repeat
         repeat
            region := region + 1;
         until(!regions[region].valid);
      until(!EntryInUse("Region", region, 1));
   endif
   
   var res, keepgoing := 1;
   var save := 0;
   
   repeat
   
      data := {
         "Name:",
         regiontmp.name,
         "Rectangles:",
         "Groups:",
         "Specials",
         "Enabled:",
         regiontmp.enabled,
         "Go to manager:",
         "Restart region:",
         "Flash Spawn region:",
         "Erase region:"
      };
      
      layout := {
         "page 0",
         "noclose",
         "nodispose",
         "resizepic 0 0 5120 320 45",
         "text 20 15 600 0",
         "text 120 15 600 1",
         "button 280 15 210 211 1 0 1",
         "resizepic 0 45 5120 320 285",
         "text 20 60 600 2",
         "button 280 60 210 211 1 0 2",
         "text 20 90 600 3",
         "button 280 90 210 211 1 0 3",
         "text 20 120 600 4",
         "button 280 120 210 211 1 0 4",
         "text 20 150 600 5",
         "text 280 150 600 6",
         "button 280 150 600 5",
         "text 20 180 600 7",
         "button 280 180 210 211 1 0 6",
         "text 20 210 600 8",
         "button 280 210 210 211 1 0 7",
         "text 20 240 600 9",
         "button 280 240 210 211 1 0 8",
         "text 20 270 600 10",
         "button 280 270 210 211 1 0 9",
         "button 240 300 239 240 1 0 10",
         "button 90 300 242 241 1 0 0"
      };
   
      res := SendDialogGump(me, layout, data);
      
      case(res[0])
      1: regiontmp.name := GetNewProp(regiontmp.name, "region name", PROPTYPE_STRING);
      2: BuildRectGump(GetElemFromArray("Region Boundaries", regiontmp.rects, OT_SELECT_AND_ADD), regiontmp.rects);
      3: BuildRegionGroupsGump(ShowRegionGroups(regiontmp.groups), regiontmp.groups, GetObjProperty(regiontmp.ref, "grouparray"));
      4: BuildSpecialsGump(GetElemFromArray("Region Specials", regiontmp.specials, OT_SELECT_AND_ADD), regiontmp.specials, GetObjProperty(regiontmp.ref, "specialarray"));
      5: regiontmp.enabled := 1 - regiontmp.enabled;
      6: GoToManager(regiontmp.ref);
      7: SendEventToManager(region, EV_CLEAR_REGION);
      8: SendEventToManager(region, EV_FLASH_SPAWN);
      9: regiontmp.valid := 0;
         save := 1;
         keepgoing := 0;
      10:if(regiontmp.rects.size() < 1)
            SendSysMessage(me, "Region must have at least one rect.");
            continue;
         endif
         regiontmp.valid := 1;
         save := 1;
         keepgoing := 0;
      default:
         keepgoing := 0;
      endcase
   
   until(!keepgoing or !me.ip);
   
   if(save)
      SaveRegionSettings(regiontmp, region);
   endif
   
   ReleaseEntry("Region", region);
   
endfunction

function BuildRectGump(pos, byref rects)

   if(pos == 0)
      return;
   endif
   
   var res, keepgoing := 1;
   var recttmp;
   
   if(pos > 0)
      recttmp := rects[pos];
   else
      CreateNewRect(recttmp);
   endif
   
   repeat
   
      data := {
         "Name:",
         recttmp.name,
         "Top Left position:",
         recttmp.fromloc.x,
         recttmp.fromloc.y,
         "Bottom Right position:",
         recttmp.toloc.x,
         recttmp.toloc.y,
         "Erase rect"
      };
   
      layout := {
         "page 0",
         "noclose",
         "nodispose",
         "resizepic 0 0 5120 350 165",
         "text 20 15 600 0",
         "text 120 15 600 1",
         "button 320 15 210 211 1 0 1",
         "text 20 45 600 2",
         "text 220 45 600 3",
         "text 280 45 600 4",
         "button 320 45 210 211 1 0 2",
         "text 20 75 600 5",
         "text 220 75 600 6",
         "text 280 75 600 7",
         "button 320 75 210 211 1 0 3",
         "text 20 105 600 8",
         "button 320 105 210 211 1 0 4",
         "button 180 135 239 240 1 0 5",
         "button 60 135 242 241 1 0 0"
      };
      
      res := SendDialogGump(me, layout, data);
   
      case(res[0])
      1: recttmp.name := GetNewProp(recttmp.name, "rect name", PROPTYPE_STRING);
      2: var newpos := GetNewPosition("top left", recttmp.fromloc);
         recttmp.fromloc.x := newpos.x;
         recttmp.fromloc.y := newpos.y;
      3: var newpos := GetNewPosition("bottom right", recttmp.toloc);
         recttmp.toloc.x := newpos.x;
         recttmp.toloc.y := newpos.y;
      4: if(pos > 0)
            rects.erase(pos);
         endif
         keepgoing := 0;
      5: if(pos > 0)
            rects[pos] := recttmp;
         else
            rects.append(recttmp);
         endif
         keepgoing := 0;
      default:
         keepgoing := 0;
      endcase
   
   until(!keepgoing or !me.ip);
   
endfunction

function ShowRegionGroups(byref regiongroups)
   
   var res;
   var pagelocation, pagesize, pagenum, pos;
   
   data := {"Select group to edit."};
   layout := {
      "page 0",
      "noclose",
      "nodispose",
      "resizepic 0 0 5120 280 280",
      "text 20 15 600 0",
      "button 20 250 2460 2461 1 0 -1",
      "button 200 250 242 241 1 0 0",
      "page 1"
   };
   
   pagesize := 0;
   pagenum := 2; 
   pos := 1;

   foreach group in regiongroups
      pagesize := pagesize + 1;
      if(pagesize > 5)
         pagesize := 1;
         layout.append("button 230 210 5601 5605 0 " + pagenum);
         layout.append("page " + pagenum);
         layout.append("button 200 210 5603 5607 0 " + (pagenum-1));
         pagenum := pagenum + 1;
      endif			
      pagelocation := 20+(30*pagesize);
      layout.append("button 20 " + pagelocation + " 210 211 1 0 " + pos);
      data.append(GetGroupName(group.groupid));
      layout.append("text 45 " + pagelocation + " 600 " + pos);
      pos := pos + 1;
   endforeach
   
   res := SendDialogGump(me, layout, data);
   
   return res[0];

endfunction

function BuildRegionGroupsGump(pos, byref regiongroups, actual)

   if(pos == 0)
      return;
   endif
   
   var res, keepgoing := 1;
   var grouptmp;
   
   if(pos > 0)
      grouptmp := regiongroups[pos];
   else
      CreateNewRegionGroup(grouptmp);
   endif
   
   repeat
      
      data := {
         "Name:",
         GetGroupName(grouptmp.groupid),
         "Respawn time:",
         grouptmp.restime,
         "Respawn amount:",
         grouptmp.total,
         "Actual amount:",
         Cint(actual[pos]),
         "Remove group from region"
      };
      
      res := SendSpecialOrGroupGump();
      
      case(res[0])
      1: grouptmp.groupid := GetElemFromArray("group", groups);
      2: grouptmp.restime := GetNewProp(grouptmp.restime, "respawn time");
      3: grouptmp.total := GetNewProp(grouptmp.total, "respawn amount");
      4: if(pos > 0)
            regiongroups.erase(pos);
         endif
         keepgoing := 0;
      5: if(pos > 0)
            regiongroups[pos] := grouptmp;
         else
            regiongroups.append(grouptmp);
         endif
         keepgoing := 0;
      default:
         keepgoing := 0;
      endcase
      
   until(!keepgoing or !me.ip);

endfunction

function BuildSpecialsGump(pos, byref specials, actual)

   if(pos == 0)
      return;
   endif
   
   var res, keepgoing := 1;
   var specialtmp;
   
   if(pos > 0)
      specialtmp := specials[pos];
   else
      CreateNewSpecial(specialtmp);
   endif

   repeat
      
      data := {
         "Template:",
         specialtmp.name,
         "Respawn time:",
         specialtmp.restime,
         "Respawn amount:",
         specialtmp.total,
         "Actual amount:",
         CInt(actual[pos]),
         "Remove special from region"
      };
      
      res := SendSpecialOrGroupGump();
      
      case(res[0])
      1: specialtmp.name := GetNewProp(specialtmp.name, "template", PROPTYPE_STRING);
      2: specialtmp.restime := GetNewProp(specialtmp.restime, "respawn time");
      3: specialtmp.total := GetNewProp(specialtmp.total, "respawn amount");
      4: if(pos > 0)
            specials.erase(pos);
         endif
         keepgoing := 0;
      5: specialtmp.valid := 1;
         if(pos > 0)
            specials[pos] := specialtmp;
         else
            specials.append(specialtmp);
         endif
         keepgoing := 0;
      default:
         keepgoing := 0;
      endcase
      
   until(!keepgoing or !me.ip);

endfunction

function SendSpecialOrGroupGump()

   layout := {
      "page 0",
      "noclose",
      "nodispose",
      "resizepic 0 0 5120 280 210",
      "text 20 30 600 0",
      "text 150 30 600 1",
      "button 250 30 210 211 1 0 1",
      "text 20 60 600 2",
      "text 150 60 600 3",
      "button 250 60 210 211 1 0 2",
      "text 20 90 600 4",
      "text 150 90 600 5",
      "button 250 90 210 211 1 0 3",
      "text 20 120 600 6",
      "text 150 120 600 7",
      "text 20 150 600 8",
      "button 250 150 210 211 1 0 4",
      "button 150 180 239 240 1 0 5",
      "button 60 180 242 241 1 0 0" 
   };
   
   return SendDialogGump(me, layout, data);
   
endfunction

function SaveRegionSettings(region, num)

   var elem, unload := 0;
   elem := regionfile.FindElement(num);
   
   if(region.valid)
      if(!elem)
         elem := regionfile.CreateElement(num);
      endif
      elem.SetProp("name", region.name);
      elem.SetProp("rects", region.rects);
      elem.SetProp("groups", region.groups);
      elem.SetProp("specials", region.specials);
      elem.SetProp("enabled", region.enabled);
      if(!region.ref)
         BuildRegionManager(region);
      endif
      elem.SetProp("serial", region.serial);
      SetObjProperty(region.ref, "num", num);
      unload := 1;
   else
      regions[num].valid := 0;
      if(elem)
         if(region.ref)
            DestroyItem(region.ref);
         endif
         regionfile.DeleteElement(num);
         unload := 1;
      endif
   endif

   if(!unload)
      return;
   endif
   
   UnloadDataFile(REGION_DATAFILE);
   var regionmanager := Cint(GetGlobalProperty("#regiondefs"+region));
   regionmanager := GetProcess(regionmanager);
   var ev := struct;
   ev.+type;
   ev.type := EV_REGION_UPDATED;
   regionmanager.SendEvent(ev);

endfunction

function BuildRegionManager(byref region)

   var rndx, rndy;
   var newx, newy, newz;
   var num;
   
   repeat
      num := Cint(RandomInt(region.rects.size()))+1;
      rndx := region.rects[num].toloc.x - region.rects[num].fromloc.x + 1;
      rndy := region.rects[num].toloc.y - region.rects[num].fromloc.y + 1;
      newx := region.rects[num].fromloc.x + Cint(RandomInt(rndx));
      newy := region.rects[num].fromloc.y + Cint(RandomInt(rndy));
      newz := GetWorldHeight(newx, newy);
      region.ref := CreateItemAtLocation(newx, newy, newz, 0xa348, 1);
   until(region.ref);
   
   region.serial := region.ref.serial;
   
endfunction

function GoToManager(manager)

   if(!manager)
      SendSysMessage(me, "Region manager does not exist.");
      return;
   endif
   
   var newx, newy, newz;
   
   repeat
      newx := manager.x - 3 + RandomInt(7);
      newy := manager.y - 3 + RandomInt(7);
      newz := GetWorldHeight(newx, newy);
   until(MoveCharacterToLocation(me, newx, newy, newz, 0));

endfunction

function SendEventToManager(region, evtype)

   var regproc := GetGlobalProperty("#regionmanager"+region);
   if(regproc)
      regproc := GetProcess(regproc);
   else
      SendSysMessage(me, "Could not send event.");
   endif
   
   var ev := struct;
   ev.+type;
   ev.type := evtype;
   
   if(regproc.SendEvent(ev))
      SendSysMessage(me, "Event succesfully sent");
   else
      SendSysMessage(me, "Could not send event.");
   endif

endfunction
