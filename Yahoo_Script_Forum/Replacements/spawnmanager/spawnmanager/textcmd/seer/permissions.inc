function EntryInUse(entryname, entry, warn := 0)

   if(entry < 1)
      return 0;
   endif
   
   var monitor := "#"+entryname+"mon"+CStr(entry);
   var retval := 1;
   
   set_critical(1);
   if(!GetGlobalProperty(monitor))
      SetGlobalProperty(monitor, 1);
      retval := 0;
   endif
   set_critical(0);
   
   if(retval and warn)
      SendSysMessage(me, entryname+" #"+entry+" is already in use.");
   endif
   
   return retval;

endfunction

function ReleaseEntry(entryname, entry)

   var monitor := "#"+entryname+"mon"+CStr(entry);
   EraseGlobalProperty(monitor);

endfunction
