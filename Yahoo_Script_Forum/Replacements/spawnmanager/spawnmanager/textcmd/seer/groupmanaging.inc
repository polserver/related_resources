var groupfile;
var groups := array;

function LoadGroupsArray()

   var elem;
   var group := struct;
   group.+name;
   group.+valid;
   group.valid := 1;

   foreach key in (groupfile.keys())
      elem := groupfile.FindElement(key);
      group.name := elem.GetProp("name");
      groups[key] := group;
   endforeach
   
endfunction

function GetGroupSpecs(groupnum)

   var group;
   CreateNewGroup(group);
   
   var elem := groupfile.FindElement(groupnum);
   group.name := elem.GetProp("name");
   group.entries := elem.GetProp("entries");
   
   return group;

endfunction

function BuildGroupGump(group)

   if((group == 0) or EntryInUse("Group", group, 1))
      return;
   endif
   
   var pagelocation, pagesize, pagenum, entrynum, res;
   var keepgoing := 1;
   var save := 0;
   
   var grouptmp;
   CreateNewGroup(grouptmp);
   
   if(group > 0)
      grouptmp := GetGroupSpecs(group);
   else
      group := 0;
      repeat
         repeat
            group := group + 1;
         until(!groups[group].valid);
      until(!EntryInUse("Group", group));
   endif
   
   repeat
      
      data := {grouptmp.name,"Select entry to edit.","Erase group."};
      layout := {
         "page 0",
         "noclose",
         "nodispose",
         "resizepic 0 0 5120 280 45",
         "text 20 15 600 0",
         "button 250 15 210 211 1 0 1",
         "resizepic 0 45 5120 280 265",
         "text 20 60 600 1",
         "text 20 250 600 2",
         "button 30 280 2460 2461 1 0 2",
         "button 150 250 210 211 1 0 3",
         "button 210 280 239 240 1 0 4",
         "button 120 280 242 241 1 0 0",
         "page 1"
      };
      
      pagesize := 0;
      pagenum := 2;
      entrynum := 0;
      
      foreach entry in (grouptmp.entries)
         pagesize := pagesize + 1;
         entrynum := entrynum + 1;
         if(pagesize > 5)
            pagesize := 1;
            layout.append("button 230 250 5601 5605 0 " + pagenum);
            layout.append("page " + pagenum);
            layout.append("button 200 250 5603 5607 0 " + (pagenum-1));
            pagenum := pagenum + 1;
         endif			
         
         pagelocation := 65+(30*pagesize);
         layout.append("text 45 " + pagelocation + " 600 " + (entrynum+2));
         layout.append("button 20 " + pagelocation + " 210 211 1 0 " + (entrynum+4));
         data.append(entry);
      endforeach
      
      res := SendDialogGump(me, layout, data);
      case(res[0])
      0: keepgoing := 0;
      1: grouptmp.name := GetNewProp(grouptmp.name, "name", PROPTYPE_STRING);
      2: AddTemplateToGroup(grouptmp.entries);
      3: grouptmp.valid := 0;
         keepgoing := 0;
         save := 1;
      4: grouptmp.valid := 1;
         keepgoing := 0;
         save := 1;
      default:
         grouptmp.entries.erase(res[0]-4);
      endcase
      
   until(!keepgoing or !me.ip);
   
   if(save)
      SaveGroupSettings(grouptmp, group);
   endif

   ReleaseEntry("Group", group);

endfunction

function AddTemplateToGroup(byref entries)

   var template := SendTextEntryGump(me, "Enter new template.",TE_CANCEL_ENABLE,TE_STYLE_NORMAL, 50, "");
   if(template)
      entries.append(template);
   endif
   
endfunction

function SaveGroupSettings(group, num)

   var elem, unload := 0;
   elem := groupfile.FindElement(num);
   if(group.valid)
      if(!elem)
         elem := groupfile.CreateElement(num);
      endif
      elem.SetProp("name", group.name);
      elem.SetProp("entries", group.entries);
      unload := 1;
   else
      groups[num].valid := 0;
      if(elem)
         groupfile.DeleteElement(num);
         unload := 1;
      endif
   endif 
      
   if(!unload)   
      return;
   endif   
   
   UnloadDataFile(GROUPS_DATAFILE);
   var groupmanager := Cint(GetGlobalProperty("#groupmanagerpid"));
   groupmanager := GetProcess(groupmanager);
   var ev := struct;
   ev.+type;
   ev.type := EV_GROUPS_UPDATED;
   groupmanager.SendEvent(ev);
   
endfunction

function GetGroupName(group)
   
   if((group < 1) or (!group) or (!groups[group].valid))
      return ("Invalid group.");
   endif
   
   return (groups[group].name);
   
endfunction

