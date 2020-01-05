var menuCfg := ReadConfigFile( "::smenu" );
var menuData := dictionary;
var menuRestrictions := dictionary;

/////////////////////////////////////////////
//Restricting functions:
//
//AddMenuRestriction( menuname, cfg_file, prop_name, prop_minimum );
//ClearMenuRestrictions( menuname := "" );
//RemoveMenuRestriction( menuname, propname );
/////////////////////////////////////////////
//Send functions:
//
//SelectSithMenuItem( who, menuname );
/////////////////////////////////////////////
//Example:
//
//AddMenuRestriction( "carpentry", ":carpentry:carpentry", "material", GetAmount(logs) );
//AddMenuRestriction( "carpentry", ":carpentry:carpentry", "skill", GetEffectiveSkill(character,SKILLID_CARPENTRY) );
//var what := SelectSithMenuItem( character, "carpentry" );
//
//Restricts carpentry selection by skill and material count.
/////////////////////////////////////////////

/////////////////////////////////////////////
//Entire Function Listing
/////////////////////////////////////////////
//ClearMenuRestrictions( menuname := "" )
//AddMenuRestriction( menuname, cfg, prop, propmin, subs := 1 )
//RemoveMenuRestriction( menuname, propname )
//GetMenuData( menuname )
//GetMenuSubmenuNames( menuname )
//ParseSubmenuString( submenustring )
//ParseEntryString( entrystring )
//CheckRestrictionOnObjtype( objtype, cfg, prop, propmin )
//SelectSithMenuItem( who, menuname )
/////////////////////////////////////////////

////////////////////////////////////////////
//the main function
////////////////////////////////////////////
function SelectSithMenuItem( who, menuname )
    var menuElem := GetMenuData(menuname);
    ParseMenuStuff(menuname);
    var menuBuild := CreateMenu( GetConfigString(menuElem,"Title") );
    //////////////////
    //Add all the subs
    //////////////////
    foreach entry in (menuData[menuname]["subs"])
        AddMenuItem( menuBuild, cInt(entry[2]), cStr(entry[3]) );
        sleepms(2);
    endforeach
    /////////////////////
    //Add all the entries
    /////////////////////
    foreach entry in (menuData[menuname]["ents"])
      if( CheckRes(menuname,entry[1]) )
        AddMenuItem( menuBuild, cInt(entry[1]), cStr(entry[2]) );
      endif
      sleepms(2);
    endforeach
    //////////////////////////
    //Send the client the menu
    //////////////////////////
    var menuRet := SelectMenuItem2( who, menuBuild );
    if( !menuRet )
        return menuRet;
    endif
    ////////////////////////////
    //If the selection was a sub
    ////////////////////////////
    if( menuRet[3] <= len(menuData[menuname]["subs"]) )
        return SelectSithMenuItem( who, menuData[menuname]["subs"][menuret[3]][1] );
    else
    	return menuRet;
    endif
endfunction


/////////////////////////////////
//Checks against any restrictions
/////////////////////////////////
function CheckRes( menuname, objtype )
    var menuRes := menuRestrictions[menuname];
    foreach menuRestriction in menuRes
        if( !CheckRestrictionOnObjtype( objtype, menuRestriction[1], menuRestriction[2], menuRestriction[3] ) )
            return 0;
        endif
    endforeach
    return 1;
endfunction


/////////////////////////////    
//Parse menu subs and entries
/////////////////////////////
function ParseMenuStuff( menuname )
    menuData[menuname] := dictionary;
    menuData[menuname]["subs"] := {};
    menuData[menuname]["ents"] := {};
    var menuelem := GetMenuData(menuname);
    var menusubs := GetConfigStringArray( menuelem, "SubMenu" );
    var menuents := GetConfigStringArray( menuelem, "Entry" );
    foreach menusub in menusubs
        menusub := ParseSubmenuString( menusub );
        menuData[menuname]["subs"].append( menusub );
        sleepms(2);
    endforeach
    foreach menuent in menuents
        menuent := ParseEntryString( menuent );
        menuData[menuname]["ents"].append( menuent );
        sleepms(2);
    endforeach
endfunction


////////////////////////
//Nuke menu restrictions
////////////////////////
function ClearMenuRestrictions( menuname := "" )
    if( menuname )
        menuRestrictions[menuname] := {};
    else
    	menuRestrictions := dictionary;
    endif
endfunction


////////////////////////
//add a menu restriction
////////////////////////
function AddMenuRestriction( menuname, cfg, propname, reqval, subs := 1 )
    if( {cfg,propname,reqval} in menuRestrictions[menuname] )
        return;
    endif
    
    if( !menuRestrictions[menuname] )
        menuRestrictions[menuname] := {};
    endif
    
    menuRestrictions[menuname].append( {cfg,propname,reqval} );
    
    if( subs )
        foreach sub in GetMenuSubmenuNames(menuname)
            AddMenuRestriction( sub, cfg, propname, reqval, subs );
        endforeach
    endif
endfunction


///////////////////////////
//Remove a menu restriction
///////////////////////////
function RemoveMenuRestriction( menuname, propname )
    var newRes := {};
    var oldRes := menuRestrictions[menuname];
    
    foreach res in oldRes
        if( res[2] != propname )
            newRes.append( res );
        endif
    endforeach
    
    menuRestrictions[menuname] := newRes;
endfunction


////////////////////
//Return the elemref
////////////////////
function GetMenuData( menuname )
    return FindConfigElem(menuCfg,menuname);
endfunction


/////////////////////////////
//Return an array of subnames
/////////////////////////////
function GetMenuSubmenuNames( menuname )
    var menuData := GetMenuData(menuname);
    var subData := GetConfigStringArray(menuData,"SubMenu");
    var subList := {};
    
    foreach sub in subData
        subList.append( SplitWords(sub)[1] );
    endforeach
    
    return subList;
endfunction


////////////////////////////////////////
//Returns the data from a submenu string
////////////////////////////////////////
function ParseSubmenuString( subMenuString )
    var sMenuCall;
    var sObjDisplay;
    var sText := "";
    var x;
    
    subMenuString := SplitWords(subMenuString);
    
    //The first to entries are menucall, objdisplay
    sMenuCall := subMenuString[1];
    sObjDisplay := subMenuString[2];
    
    //Get the string from the remaining array entries
    if( subMenuString[3] )
        sText := subMenuString[3];
        for( x := 4; x <= len(subMenuString); x := x + 1 )
            sText := sText + " " + subMenuString[x];
        endfor
    endif
    
    return {sMenuCall,sObjDisplay,sText};
endfunction


////////////////////////////////////////
//Returns the array from an entry string
////////////////////////////////////////
function ParseEntryString( entryString )
    entryString := SplitWords(entryString);
    
    var eObjType;
    var eText := "";
    var x;
    
    eObjType := entryString[1];
    
    if( entryString[2] )
        eText := entryString[2];
        for( x := 3; x <= len(entryString); x := x + 1 )
            eText := eText + " " + entryString[x];
        endfor
    endif
    
    return {eObjType,eText};
endfunction


//////////////////////////////////
//Check restrictions on an objtype
//////////////////////////////////
function CheckRestrictionOnObjtype( objType, cfgLoc, propName, propMax )
    var rCfg := ReadConfigFile(cfgLoc);
    var rElem := FindConfigElem(rCfg,objType);
    
    if( rElem )
        if( GetConfigInt(rElem,propName) <= propMax )
            return 1;
        else
            return 0;
        endif
    else
    	return 1;
    endif
endfunction