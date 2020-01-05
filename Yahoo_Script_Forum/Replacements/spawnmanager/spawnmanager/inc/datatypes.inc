const GROUPS_DATAFILE := "groupfile";
const REGION_DATAFILE := "regionfile";

function CreateNewGroup(byref group)

   group := struct;
   group.+name;
   group.+entries;
   group.+valid;
   group.valid := 0;
   group.name := "Click to select group name:";
   group.entries := array;

endfunction

function CreateNewRegion(byref region)

   region := struct;
   region.+name;
   region.+rects;
   region.+groups;
   region.+specials;
   region.+enabled;
   region.+serial;
   region.+ref;
   region.+valid;

   region.name := "Click to select a name.";
   region.rects := array;
   region.groups := array;
   region.specials := array;
   region.enabled := 1;
   region.serial := 0;
   region.ref := 0;
   region.valid := 0;

endfunction

function CreateNewRect(byref rect)

   rect := struct;
   rect.+name;
   rect.+fromloc;
   rect.+toloc;
   rect.+valid;
   rect.name := "Click to select a name.";
   rect.valid := 1;
   rect.fromloc := struct;
   rect.fromloc.+x;
   rect.fromloc.+y;
   rect.toloc := rect.fromloc;
   
   rect.fromloc.x := me.x - 5;
   rect.fromloc.y := me.y - 5;
   rect.toloc.x := me.x + 5;
   rect.toloc.y := me.y + 5;
   
endfunction

function CreateNewRegionGroup(byref group)

   group := struct;
   group.+groupid;
   group.+restime;
   group.+total;
   
   group.groupid := 0;
   group.restime := 30;
   group.total := 5;

endfunction

function CreateNewSpecial(byref special)

   special := struct;
   special.+name;
   special.+restime;
   special.+total;
   special.+valid;
   
   special.name := "Click to select template";
   special.restime := 30;
   special.total := 1;
   special.valid := 0;

endfunction