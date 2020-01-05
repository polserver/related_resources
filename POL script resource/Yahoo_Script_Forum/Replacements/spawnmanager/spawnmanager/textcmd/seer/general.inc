const PROPTYPE_INTEGER := 0;
const PROPTYPE_STRING := 1;
const OT_SELECT := 0;
const OT_SELECT_AND_ADD := 1;

function OpenFile(filespec)

   var file := OpenDataFile(filespec);
   if(!file)
      file := CreateDataFile(filespec, DF_KEYTYPE_INTEGER);
   endif
   
   return file;

endfunction

function GetNewProp(oldpropval, propname, proptype := PROPTYPE_INTEGER)

   var newprop;
   case (proptype)
   PROPTYPE_INTEGER:
      newprop := Cint(SendTextEntryGump(me, "Enter new "+propname+".",TE_CANCEL_ENABLE,TE_STYLE_NUMERICAL, 360, "Old value was "+oldpropval));
   PROPTYPE_STRING:
      newprop := CStr(SendTextEntryGump(me, "Enter new "+propname+".",TE_CANCEL_ENABLE,TE_STYLE_NORMAL, 50, "Old value was "+oldpropval));
   endcase
   
   if(!newprop)
      return oldpropval;
   else
      return newprop;
   endif

endfunction

function GetElemFromArray(name, byref elems, option := OT_SELECT)
   
   data := { "Select the "+name+":" };
   layout := {
      "page 0",
      "noclose",
      "nodispose",
      "resizepic 0 0 5120 280 280",
      "text 20 15 600 0",
      "button 120 250 242 241 1 0 0"
   };
   
   if(option)
      layout.append("button 20 250 2460 2461 1 0 -1");
   endif
   
   layout.append("page 1");
   
   var pagesize := 0;
   var pagenum := 2; 
   var num := 0;
   var invalidnum := 0;
   var pagelocation;
   
   foreach elem in elems
      num := num + 1;
      if(elem.valid)
         pagesize := pagesize + 1;
      else
         invalidnum := invalidnum + 1;
         continue;
      endif
      if(pagesize > 5)
         pagesize := 1;
         layout.append("button 230 210 5601 5605 0 " + pagenum);
         layout.append("page " + pagenum);
         layout.append("button 200 210 5603 5607 0 " + (pagenum-1));
         pagenum := pagenum + 1;
      endif			
      pagelocation := 20+(30*pagesize);
      layout.append("button 20 " + pagelocation + " 210 211 1 0 " + num);
      data.append(elem.name);
      layout.append("text 45 " + pagelocation + " 600 " + (num-invalidnum));
   endforeach
   
   var res := SendDialogGump(me, layout, data);
   
   return(res[0]);
   
endfunction

function GetNewPosition(posname, oldpos)
   
   SendSysMessage(me, "Target the "+posname+" position.");
   var newpos := TargetCoordinates(me);
   
   if(!newpos)
      return oldpos;
   endif
   
   return newpos;

endfunction
