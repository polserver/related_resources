//////////////////////////////////////////////////////
//sench.inc                                         //
//////////////////////////////////////////////////////
//Functions for use with the senchantedhit hitscript//
//should be part of the senchantment system soonish //
//////////////////////////////////////////////////////
//Creator:  S!tH                                    //
//Last Mod: 26/8/2001                               //
//Version:  1.0                                     //
//////////////////////////////////////////////////////

use uo;
use os;
use util;
use basic;
use cfgfile;

include "include/string";
include "include/client";
include "include/attributes";

/////////////////////////////////
//Magical Item Spawning Constants
//These only effect magic item spawning...
/////////////////////////////////
Const SMIS_SCROLL_CHANCE := 3;              //1 in 3 chance of making a scroll, regardless of item enchantability
Const SMIS_MAX_ENCHANTMENTS_PER_ITEM := 3;  //Maximum natural enchantments spawned on an item
Const SMIS_MAXLVL_DIVIDER := 1;             //Divide the NPCs "magicadjustment" by this, to get the max enchantment level.
Const SMIS_NOSOCKET_CHANCE := 6;            //1 in 6 chance of not socketing an enchanted item
Const SMIS_MAXSOCKET := 2;                  //1-2 sockets on an enchanted item


//////////////////////////////////////////////////////////////////////////////////////////////////
//Function List											//
//////////////////////////////////////////////////////////////////////////////////////////////////
//findPositionInArray( thing, arr )		Attempt to find position of "thing" in array "arr"
//getItemGroupString( igroup )			String that says what this group contains.
//isSocketable( objtype )			Is this object type listed as socketable?
//getGroupByObjtype( objtype )			What bias 'group' does this objtype belong to?
//isOfGroup( objtype, group )			Is this objtype in the bias 'group'?
//checkSpellAgainst( spellid, groupid )		Used in the magic system
//calculateMagikool( caster, cast_on, amt, spelltype ) Calculates all the spell effects of enchanted items.
//isSocketedIn( ench, item )			Checks to see if 'ench' is on a socketed item inserted in item.
//sortEnchantments( item )			Should sort enchantments so that naturals are first, followed by inserteds. For uninserted player-crafted.
//setEquipScripts( item )			Set the equip scripts of items to the SithMagicItemSystem one.
//getEnchStringArray( item, enchantment )	Returns array of descriptions. For multiple descriptions of an enchantment.
//grabEnchString( item, origString )		Returns an ItemID ready string from the original CFG string.
//isRegistered( enchantment )			Returns 0 if not registered, itemref if it is.
//registerUnique( enchantment, item )		Registers the existence of unique enchantment on item.
//hasConflicts( enchantment, item )		Returns a 1 if this ench cannot be added to this item due to conflicts.
//makeMagicScroll( container, chance, maxlvl )  Chance to make a random magic scroll
//convEnch( fromitem, item, enchantment )	Like addEnch, but converts any CProps rather than making new ones.
//getBias( enchantment )			Returns array of bias' for enchantment
//setSlots( item, amount )			Sets the items slots to amount (all empty).
//makeRandomArmour( container )			Make a random piece of armour in 'container' and return the itemref.
//makeRandomWeapon( container )			Make a random weapon in 'container' and return the itemref.
//getRandomEnchantment( level )			Returns a random enchantment string of level 'level'
//getEnchConfigProp( enchantment, propname, type ) Grabs the config property 'propname' for 'enchantment' type is "integer" or "string".
//fillEnchSlots( item, enchantment, slotsize )	Fill the slots (#=slotsize) on item for enchantment.
//getFreeEnchSlots( item )			Gets the number of free enchantment slots on item.
//getEnchSlots( item )				Gets the total number of enchantment slots on item.
//refreshEnchNames( item )			Refreshes the name based on current enchantments.
//killEnch( item, enchantment )			Kills all copies of enchantment on item, including names.
//addEnch( item, enchantment )			Add the enchantment to the item. Adds + Fixes name.
//enchFixName( item )				Apply the naming of item.
//enchAddName( item, enchantment )		Add the names for enchantment to item. Does not apply.
//////////////////////////////////////////////////////////////////////////////////////////////////

////////////////
//Global configs
////////////////
var eConfig := ReadConfigFile( ":sithmagicitems:senchantedhit" );
var sConfig := ReadConfigFile( ":sithmagicitems:configuration/spellgroups" );

//To remove enchantment scrolls and make ench's go straight -> runestones,
//simply chance the ID_ENCHSCROLL to the runestone value!
const ID_RUNESTONE  := 0x7900;
const ID_ENCHSCROLL := 0x79FF;

//Should the effect of any spell resisting or incrementing items,
//be divided by the amount of enchanted items being worn?
const SPELL_DMG_DIV := 1;

/////////////////////////////////////
//hasEnchantment( item, enchantment )
/////////////////////////////////////
function hasEnchantment( item, enchantment )
    foreach ench in GetObjProperty(item,"Enchantments")
        if( ench == enchantment )
            return 1;
        endif
    endforeach
endfunction

///////////////////////////////////
//findPositionInArray( thing, arr )
///////////////////////////////////
function findPositionInArray( thing, arr )
	var x;
	for( x := 1; x <= len(arr); x := x + 1 )
	    if( cStr(arr[x]) == cStr(thing) )
		return x;
	    endif
	endfor
	return error;
endfunction

//////////////////////////////
//getItemGroupString( igroup )
//////////////////////////////
function getItemGroupString( igroup )
	var igCfg := ReadConfigFile( ":sithmagicitems:configuration/itemgroups" );
	var gElem := FindConfigElem( igCfg, igroup );
	return GetConfigString( gElem, "itemidstring" );
endfunction

/////////////////////////
//isSocketable( objtype )
/////////////////////////
function isSocketable( objtype )
	var igCfg := ReadConfigFile( ":sithmagicitems:configuration/itemgroups" );
	var igElem := FindConfigElem( igCfg, "socketables" );
	var groupz := GetConfigStringArray( igElem, "igroup" );
	foreach bg in groupz
	    if( isOfGroup( objtype, bg ) )
	    	return bg;
	    endif
	endforeach
	return 0;
endfunction

//////////////////////////////
//getGroupByObjtype( objtype )
//////////////////////////////
function getGroupByObjtype( objtype )
	var igCfg := ReadConfigFile( ":sithmagicitems:configuration/itemgroups" );
	var igElem := FindConfigElem( igCfg, "allGroups" );
	var groupz := GetConfigStringArray( igElem, "igroup" );
	foreach bg in groupz
	    if( isOfGroup( objtype, bg ) )
	    	return bg;
	    endif
	endforeach
	return 0;
endfunction

/////////////////////////////
//isOfGroup( objtype, group )
/////////////////////////////
function isOfGroup( objtype, group )
	var zigCfg := ReadConfigFile( ":sithmagicitems:configuration/itemgroups" );
	var gElem := FindConfigElem( zigCfg, group );
	return GetConfigInt( gElem, hex(objtype) );
endfunction

///////////////////////////////////////
//checkSpellAgainst( spellid, groupid )
///////////////////////////////////////
function checkSpellAgainst( spellid, groupid )
	if( cStr(spellid) == cStr(groupid) )
	    return 1;
	endif
	return GetConfigInt( FindConfigElem(sConfig,groupid), spellid );
endfunction

//////////////////////////////////////////////////////
//calculateMagikool( caster, cast_on, amt, spelltype )
//////////////////////////////////////////////////////
function calculateMagikool( caster, cast_on, amt, spelltype )

	var castNums := 0;
	var victNums := 0;
	if( SPELL_DMG_DIV )
	  foreach ite in ListEquippedItems( caster )
	    if( GetObjProperty( ite, "Enchantments" ) )
	    	castNums := castNums + 1;
	    endif
	  endforeach
	  foreach ite in ListEquippedItems( cast_on )
	    if( GetObjProperty( ite, "Enchantments" ) )
	    	victNums := victNums + 1;
	    endif
	  endforeach
	else
	  castNums := castNums + 1;
	  victNums := victNums + 1;
	endif
    	//Caster first...
	foreach ite in ListEquippedItems( caster )
	    if( GetObjProperty( ite, "Enchantments" ) )
	    	castNums := castNums + 1;
	    endif
	    foreach iEnch in GetObjProperty( ite, "Enchantments" )
	    	foreach mprop in getEnchConfigProp( iEnch, "spellBonus", "stringarray" )
	    	    mprop := SplitWords( mprop );
		    if( !cInt(mprop[2]) )
			mprop[2] := GetObjProperty( ite, mprop[2] );
		    endif
	    	    if( checkSpellAgainst(spelltype, mprop[1]) )
	    	    	amt := amt * ((cInt(mprop[2])/100.0)/castNums);
	    	    endif
	    	endforeach
	    endforeach
	endforeach
	//Monster's enchantments
	foreach iEnch in GetObjProperty( caster, "Enchantments" )
	    foreach mprop in getEnchConfigProp( iEnch, "spellBonus", "stringarray" )
	        mprop := SplitWords( mprop );
		if( !cInt(mprop[2]) )
		    mprop[2] := GetObjProperty( caster, mprop[2] );
		endif
	        if( checkSpellAgainst(spelltype, mprop[1]) )
	            amt := amt * ( cInt(mprop[2]) / 100.0 );
	    	endif
	    endforeach
	endforeach
	
	//Now the dead guy... err.. cast_on i mean
	foreach ite in ListEquippedItems( cast_on )
	    foreach iEnch in GetObjProperty( ite, "Enchantments" )
	    	foreach mprop in getEnchConfigProp( iEnch, "spellResist", "stringarray" )
	    	    mprop := SplitWords( mprop );
		    if( !cInt(mprop[2]) )
			mprop[2] := GetObjProperty( ite, mprop[2] );
		    endif
	    	    if( checkSpellAgainst(spelltype, mprop[1]) )
	    	    	amt := amt - ((amt*((cInt(mprop[2])/100.0)))/victNums );
	    	    endif
	    	endforeach
	    endforeach
	endforeach
	//Defending Monsters
	foreach iEnch in GetObjProperty( cast_on, "Enchantments" )
	    foreach mprop in getEnchConfigProp( iEnch, "spellResist", "stringarray" )
	    	mprop := SplitWords( mprop );
		if( !cInt(mprop[2]) )
		    mprop[2] := GetObjProperty( cast_on, mprop[2] );
		endif
	    	if( checkSpellAgainst(spelltype, mprop[1]) )
	    	    amt := amt - ( amt * (cInt(mprop[2])/100.0) );
	    	endif
	    endforeach
	endforeach
	return cInt(amt);
	
endfunction

////////////////////////////
//isSocketedIn( ench, item )
////////////////////////////
function isSocketedIn( ench, item )
  foreach eslot in GetObjProperty( item, "eSlots" )
  	if( len(eslot) && eslot[1] == ench )
  		return 1;
  	elseif( eslot == ench )
  		return 1;
  	endif
  endforeach
endfunction

//////////////////////////
//sortEnchantments( item )
//////////////////////////
function sortEnchantments( item )

	var enchantments := GetObjProperty( item, "Enchantments" );
	if( !enchantments || !len(enchantments) )
	    return;
	endif
	
	var newEnch;
	
	foreach ench in enchantments
	    if( !isSocketedIn( ench, item ) ) //Natural
	    	newEnch.append( ench );
	    	ench := 0;
	    endif
	endforeach
	foreach ench in enchantments
	    if( ench )
	    	newEnch.append( ench ); //Was not a natural
	    endif
	endforeach
	
	return SetObjProperty( item, "Enchantments", newEnch );
	
endfunction

/////////////////////////
//setEquipScripts( item )
/////////////////////////
function setEquipScripts( item )

	item.equipscript := ":sithmagicitems:smequip";
	item.unequipscript := ":sithmagicitems:smunequip";
	item.destroyscript := ":sithmagicitems:smdestroy";

endfunction

/////////////////////////////////////////
//getEnchStringArray( item, enchantment )
/////////////////////////////////////////
function getEnchStringArray( item, enchantment )
	var zstrings := {};
	foreach zstring in getEnchConfigProp( enchantment, "idstring", "stringarray" );
	    zstring := grabEnchString( item, zstring );
	    if( zstring )
	    	zstrings.append( zstring );
	    endif
	endforeach
	return zstrings;
endfunction

/////////////////////////////////////
//grabEnchString( item, origString )
/////////////////////////////////////
function grabEnchString( item, origString )

	var sPos;
	var ePos;
	var preString;
	var sufString;
	var propName;
	var propVal;
	var tries := 0;

	while( find(origString,"$",1) && tries < 8 );
	  tries := tries + 1;
	  sPos := find( origString, "$", 1 );
	  ePos := find( origString, "#", 1 );
	  if( sPos && ePos )
	    preString := origString[1,sPos-1];
	    sufString := origString[ePos+1,len(origString)];
	    propName  := origString[sPos+1,ePos-1];
	    propName  := propName[1,ePos-sPos-1];
	    propVal   := GetObjProperty( item, propName );
	    origString := preString + cStr(propVal) + sufString;
	  endif
	endwhile

	return origString;

endfunction

/////////////////////////////
//isRegistered( enchantment )
/////////////////////////////
function isRegistered( enchantment )

	var uniques := GetGlobalProperty( "sunique" );

	if( !uniques )
	  return 0;
	endif

	var cserial;
	foreach unique in uniques
	  if( unique[1] == enchantment )
	    cserial := unique[2];
	    break;
	  endif
	endforeach

	if( !cserial )
	  return 0;
	endif

	var citem := SystemFindObjectBySerial( cserial );
	if( !citem )
	  citem := SystemFindObjectBySerial( cserial, SYSFIND_SEARCH_STORAGE_AREAS );
	  if( !citem )
	    return 0;
	  endif
	endif

	if( enchantment in GetObjProperty( citem, "Enchantments" ) )
	  return citem;
	endif
	return 0;

endfunction

/////////////////////////////////////
//registerUnique( enchantment, item )
/////////////////////////////////////
function registerUnique( enchantment, item )

	if( !enchantment || !item )
	  return;
	endif

	var uniques := GetGlobalProperty( "sunique" );

	if( !uniques || !len(uniques) )
	  uniques := {};
	endif

	var enchuniq := { enchantment, item.serial };
	uniques.append( enchuniq );

	SetGlobalProperty( "sunique", uniques );

	return 1;

endfunction

///////////////////////////////////
//hasConflicts( enchantment, item )
///////////////////////////////////
function hasConflicts( enchantment, item )

	var enchs := GetObjProperty( item, "Enchantments" );
	var conflicts := SplitWords(GetConfigString( FindConfigElem(eConfig,enchantment), "conflicts" ));

	foreach ench in enchs
	  foreach c in conflicts
	    if( c == ench )
	      return 1;
	    endif
	  endforeach
	endforeach

	return 0;

endfunction

//////////////////////////////////////////////
//makeMagicScroll( container, chance, maxlvl )
//////////////////////////////////////////////
function makeMagicScroll( container, chance, maxlvl )
	var clvl := maxlvl;
	var tlvl := 0;

        if( RandomInt(100) + 1 > chance )
          return;
        endif

	var enchantment := getRandomEnchantment( tlvl );
	
	if( !enchantment )
	  return;
	endif

	var tscroll := CreateItemInContainer( container, ID_ENCHSCROLL );

	if( tscroll )
	  if( addEnch( tscroll, enchantment ) );
	    return tscroll;
	  else
	    DestroyItem( tscroll );
	  endif
	endif

	return 0;
endfunction

/////////////////////////////////////////
//convEnch( fromitem, item, enchantment )
/////////////////////////////////////////
function convEnch( fromitem, item, enchantment )

	if( !fromitem || !item || !enchantment )
	    return;
	endif

	if( GetObjProperty(item,"a_equipped") && (!item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC)) )
	  return "You must unequip the item to add enchantments to it.";
	endif

	if( hasConflicts( enchantment, item ) )
	  return "This enchantment conflicts one already existing on the item.";
	endif

        //Disable bias for NPC enchantments
	if( !getEnchConfigProp(enchantment,"npc","integer") )
	    if( !item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC) )
		var checkBias := getBias( enchantment );
		var checkType := getGroupByObjtype( hex(item.objtype) );
		if( checkType in checkBias || "all" in checkBias || hex(item.objtype) in checkBias )
		  //We're allowed to continue
		elseif( item.objtype != ID_RUNESTONE && item.objtype != ID_ENCHSCROLL )
		  return "You cannot add this enchantment to this item.";
		endif
            else
            	return "You cant put item enchantments on an NPC.";
            endif
	endif

	var onhit := GetObjProperty(item,"Enchantments");
	if( !onhit || !len(onhit) )
	    if( !item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC) )
	        SetObjProperty( item, "trueName", TruncateArticle(item.desc) );
	        SetObjProperty( item, "unnamedsench", 1 );
	        SetName( item, "a magic " + TruncateArticle(item.desc) );
	    endif
	    onhit := {};
	endif
        if( enchantment in onhit )
	  return "This item already has this enchantment.";
        endif

	//Check for uniques here...
	if( getEnchConfigProp( enchantment, "unique", "integer" ) )
	  if( isRegistered( enchantment ) && isRegistered( enchantment ) != fromitem )
	    return "There is already an item with that enchantment.";
	  else
	    registerUnique( enchantment, item );
	  endif
	endif

	onhit.append (enchantment);
	SetObjProperty (item, "Enchantments", onhit);

	var ranProps := getEnchConfigProp( enchantment, "AddRanProp", "stringarray" );
	if( ranProps )
         foreach ranProp in ranProps
	  ranProp := SplitWords( ranProp );
	  SetObjProperty( item, ranProp[1], GetObjProperty(fromitem,ranProp[1]) );
	 endforeach
	endif

	//Around here, spose we should check for equip + unequip scripts eh? :)
	if( len(getEnchConfigProp(enchantment,"toSkill","stringarray")) || len(getEnchConfigProp(enchantment,"toStat","stringarray")) )
	  setEquipScripts( item );
	endif

	var arMod := getEnchConfigProp( enchantment, "ocArmourMod", "integer" );
	if( arMod )
	  item.ar_mod := item.ar_mod + arMod;
	endif

	var toCol := GetObjProperty( item, "origColour" );
	if( !toCol )
	  toCol := getEnchConfigProp( enchantment, "toColour", "integer" );
	  if( toCol )
	    SetObjProperty( item, "origColour", item.color );
	    item.color := toCol;
	  endif
	endif
	
	enchAddName( item, enchantment );
	refreshEnchNames( item );

	return 420;

endfunction

////////////////////////
//getBias( enchantment )
////////////////////////
function getBias( enchantment )

	var elevel := GetConfigInt( FindConfigElem(eConfig,enchantment), "level" );
	var zElem := FindConfigElem( eConfig, "level" + cStr(elevel) );
	var bias := {};
	if( !zElem )
	  return 0;
	endif

	var enchs := GetConfigStringArray( zElem, "Enchantment" );
	foreach ench in enchs
	  ench := SplitWords( ench );
	  if( ench[1] == enchantment )
	    //We have our ench
	    foreach zbias in ench
	      if( zbias != ench[1] )
	        bias.append( zbias );
	      endif
	    endforeach
	    break;
	  endif
	endforeach

	if( bias )
	  return bias;
	endif

endfunction

//////////////////////////
//setSlots( item, amount )
//////////////////////////
function setSlots( item, amount )

	var sArray := {};
	if( !amount )
	  return;
	endif

	while( len(sArray) < amount )
	  sArray.append(0);
	endwhile

	SetObjProperty( item, "eSlots", sArray );

	return;

endfunction

///////////////////////////////
//makeRandomArmour( container )
///////////////////////////////
function makeRandomArmour( container )

	var magicWeps := ReadConfigFile( ":sithmagicitems:magicarmor" );
	var mwElem := FindConfigElem( magicWeps, "encharma" );

	var theWeps := GetConfigStringArray( mwElem, "arm" );
	var iType := cInt( theWeps[ RandomInt( len(theWeps) ) + 1 ] );

	return CreateItemInContainer( container, iType );

endfunction

///////////////////////////////
//makeRandomWeapon( container )
///////////////////////////////
function makeRandomWeapon( container )

	var itemCfg := ReadConfigFile( ":sithmagicitems:itemdesc" );
	var magicWeps := ReadConfigFile( ":sithmagicitems:magicweaps" );
	var mwElem := FindConfigElem( magicWeps, "enchweps" );

	var theWeps := GetConfigStringArray( mwElem, "wep" );
	var iType := cInt( theWeps[ RandomInt( len(theWeps) ) + 1 ] );

	return CreateItemInContainer( container, iType );

endfunction

///////////////////////////////
//getRandomEnchantment( level )
///////////////////////////////
function getRandomEnchantment( level, bias := 0, npc := 0 )
	if( bias )
	  bias := SplitWords( bias );
	endif
	var zElem := FindConfigElem( eConfig, "level" + cStr(level) );
	if( zElem )
	  var enchantments := GetConfigStringArray( zElem, "Enchantment" );
	  if( !enchantments )
	    return 0;
	  endif
	  if( !bias )
		return SplitWords(enchantments[ RandomInt(len(enchantments))+1 ])[1];
	  else
		var ench := SplitWords(enchantments[ RandomInt(len(enchantments))+1 ]);
		var zc := 0;
		var tench, biass;
		while( zc < len(ench) )
		  if( zc == 1 )
		    tench := ench[zc];
		  else
		    biass.append( ench[zc] );
		  endif
		  zc := zc + 1;
		endwhile
		zc := 0;
		foreach x in bias
		  if( x in biass )
		    zc := zc + 1;
		  endif
		endforeach
		if( "all" in biass )
		  if( npc || !getEnchConfigProp(tench,"npc","integer") )
		    return tench;
		  endif
		elseif( zc != len(biass) )
		  return 0;
		else
		  if( npc || !getEnchConfigProp(tench,"npc","integer") )
		    return tench;
		  endif
		endif
	   endif
	endif
	return 0;
endfunction

//////////////////////////////////////////////////
//getEnchConfigProp( enchantment, propname, type )
//////////////////////////////////////////////////
function getEnchConfigProp( enchantment, propname, type )
	case( type )
		"integer": return GetConfigInt( FindConfigElem(eConfig,enchantment), propname );
		"string":  return GetConfigString( FindConfigElem(eConfig,enchantment), propname );
		"stringarray": return GetConfigStringArray( FindConfigElem(eConfig,enchantment), propname );
	endcase
endfunction

//////////////////////////////////////////////
//fillEnchSlots( item, enchantment, slotsize )
//////////////////////////////////////////////
function fillEnchSlots( item, enchantment, slotsize, fromItem := 0 )

	var slots := GetObjProperty( item, "eSlots" );
	if( !len(slots) )
	    return;
	endif

	var sLeft := slotsize;
	foreach s in slots
	  if( sLeft )
	    if( !s )
		if( sLeft == slotsize )
		    sLeft := sLeft - 1;
		    if( fromItem )
		        s := { enchantment, TruncateArticle(fromItem.desc), cInt(fromItem.graphic), hex(fromItem.objtype) };
		    else
		    	s := { enchantment, "dwarven runestone", 6249, ID_RUNESTONE };
		    endif
		else
		    sLeft := sLeft - 1;
		    s := 1;
		endif
	    endif
	  endif
	endforeach

	SetObjProperty( item, "eSlots", slots );

endfunction

//////////////////////////
//getFreeEnchSlots( item )
//////////////////////////
function getFreeEnchSlots( item )

	var slots := GetObjProperty( item, "eSlots" );
	if( !slots || !len(slots) )
	    return;
	endif

	var numFree := 0;
	foreach s in slots
	    if( !s && !len(s) )
		numFree := numFree + 1;
	    endif
	endforeach

	return numFree;

endfunction

//////////////////////////
//getEnchSlots( item )
//////////////////////////
function getEnchSlots( item )

	var slots := GetObjProperty( item, "eSlots" );
	if( !slots || !len(slots) )
	    return;
	else
	    return len(slots);
	endif

endfunction

//////////////////////////
//refreshEnchNames( item )
//////////////////////////
function refreshEnchNames( item )

	var tName := GetObjProperty( item, "trueName" );
	if( !tName )
	    tName := GetObjProperty( item, "tname" );
	endif
	if( !tName )
	    return; //Cant be any enchantments!
	elseif( !GetObjProperty(item,"unnamedsench") )
	    Setname( item, AddArticle(tName) );
	endif

	EraseObjProperty( item, "enchPrefix" );
	EraseObjProperty( item, "enchSuffix" );

	foreach ench in GetObjProperty( item, "Enchantments" )
	    enchAddName( item, ench );
	endforeach
	
	if( !GetObjProperty(item,"unnamedsench") )
	    enchFixName( item );
	endif

endfunction

///////////////////////////////
//killEnch( item, enchantment )
///////////////////////////////
function killEnch( item, enchantment )

	var onhit := getobjproperty(item,"Enchantments");
	if(!onhit or !len(onhit))
		return;
	endif

	var arMod;
	var ranProps;

	var newonhit := {};

	foreach thing in onhit
		if ( thing != enchantment )
			newonhit.append (thing);
		else
			//Attempt to reverse some of the enchantment effects.
			//ar_mod
			arMod := getEnchConfigProp( enchantment, "ocArmourMod", "integer" );
			if( arMod )
			  item.ar_mod := item.ar_mod - arMod;
			endif
			//Free up memory from the CProps
			ranProps := getEnchConfigProp( enchantment, "AddRanProp", "stringarray" );
			if( ranProps )
			  foreach rprop in ranProps
			    rprop := SplitWords(rprop);
			    EraseObjProperty( item, rprop[1] );
			  endforeach
			endif
		endif
	endforeach

	SetObjProperty (item, "Enchantments", newonhit);
	refreshEnchNames( item );

endfunction

//////////////////////////////////////
//addEnch( item, enchantment )
//////////////////////////////////////
function addEnch( item, enchantment )

	if( !item || !enchantment )
	    return;
	endif

	if( GetObjProperty(item,"a_equipped") && (!item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC)) )
	  return "You must unequip the item to add enchantments to it.";
	endif

	if( hasConflicts( enchantment, item ) )
	  return "This enchantment conflicts one already existing on the item.";
	endif

        //Disable bias for NPC enchantments
	if( !getEnchConfigProp(enchantment,"npc","integer") )
	    if( !item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC) )
		var checkBias := getBias( enchantment );
		var checkType := getGroupByObjtype( hex(item.objtype) );
		if( checkType in checkBias || "all" in checkBias || hex(item.objtype) in checkBias )
		  //We're allowed to continue
		elseif( item.objtype != ID_RUNESTONE && item.objtype != ID_ENCHSCROLL )
		  return "You cannot add this enchantment to this item.";
		endif
            else
            	return "You cant put item enchantments on an NPC.";
            endif
	endif

	var onhit := GetObjProperty(item,"Enchantments");
	if( !onhit || !len(onhit) )
	    if( !item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC) )
	        SetObjProperty( item, "trueName", TruncateArticle(item.desc) );
	        SetObjProperty( item, "unnamedsench", 1 );
	        SetName( item, "a magic " + TruncateArticle(item.desc) );
	    endif
	    onhit := {};
	endif
        if( enchantment in onhit )
	  return "This item already has this enchantment.";
        endif

	//Check for uniques here...
	if( getEnchConfigProp( enchantment, "unique", "integer" ) )
	  if( isRegistered( enchantment ) )
	    return "There is already an item with that enchantment.";
	  else
	    registerUnique( enchantment, item );
	  endif
	endif

	onhit.append(enchantment);
	SetObjProperty (item, "Enchantments", onhit);

	var ranProps := getEnchConfigProp( enchantment, "AddRanProp", "stringarray" );
	if( ranProps )
         foreach ranProp in ranProps
	  ranProp := SplitWords( ranProp );
	  if( len(ranProp) = 2 )
	    SetObjProperty( item, ranProp[1], RandomInt(cInt(ranProp[2]))+1);
	  elseif( len(ranProp) = 3 )
	    SetObjProperty( item, ranProp[1], (cInt(ranProp[2])+RandomInt(ranProp[3]-ranProp[2])+1) );
	  endif
         endforeach
	endif

	//Around here, spose we should check for equip + unequip scripts eh? :)
	if( len(getEnchConfigProp(enchantment,"toSkill","stringarray")) || len(getEnchConfigProp(enchantment,"toStat","stringarray")) )
	  setEquipScripts( item );
	endif

	var arMod := getEnchConfigProp( enchantment, "ocArmourMod", "integer" );
	if( arMod )
	  item.ar_mod := item.ar_mod + arMod;
	endif

	var toCol := GetObjProperty( item, "origColour" );
	if( !toCol )
	  toCol := getEnchConfigProp( enchantment, "toColour", "integer" );
	  if( toCol )
	    SetObjProperty( item, "origColour", item.color );
	    item.color := toCol;
	  endif
	endif
	
	if( !item.IsA(POLCLASS_MOBILE) && !item.IsA(POLCLASS_NPC) )
	    enchAddName( item, enchantment );
	    refreshEnchNames( item );
	    if( !GetObjProperty(item,"unnamedsench") )
	        enchFixName(item);
	    endif
	endif

	return 420;
endfunction

//////////////////////////////////////
//enchFixName( item )
//////////////////////////////////////
//Adds the name of the enchantments on
//to the "tname"...
//////////////////////////////////////
function enchFixName( item )

        if( item.IsA(POLCLASS_MOBILE) || item.IsA(POLCLASS_NPC) )
            return;
        endif

	var theName := GetObjProperty( item, "trueName" );
	if( !theName )
	    theName := GetObjProperty( item, "tname" );
	    if( !theName )
	        theName := TruncateArticle( item.desc );
	    endif
	endif

	var prefix, suffix;
	prefix := GetObjProperty( item, "enchPrefix" );
	suffix := GetObjProperty( item, "enchSuffix" );

	if( prefix )
	    foreach p in prefix
		theName := p + " " + theName;
	    endforeach
	endif
	if( suffix )
	    var doneFirst := 0;
	    foreach s in suffix
		if( !doneFirst )
		    doneFirst := 1;
		    theName := theName + " of " + s;
		else
		    theName := theName + " and " + s;
		endif
	    endforeach
	endif

	theName := AddArticle( theName );
	SetName(item,theName);

	return 1;
endfunction

//////////////////////////////////////
//enchAddName( item, enchName )
//////////////////////////////////////
//The 'enchName' taken here isnt the
//name to add, but the name of the
//enchantment whos name to add
//////////////////////////////////////
function enchAddName( item, enchName )

        if( item.IsA(POLCLASS_MOBILE) || item.IsA(POLCLASS_NPC) )
            return;
        endif

	var zCfg, zElem;
	zCfg := ReadConfigFile( ":sithmagicitems:senchantedhit" );
	zElem := FindConfigElem( zCfg, enchName );

	if( !zElem )
	    return zElem; //For debugging?
	endif

	//Enchantments prefixes + suffixes
	var zPre, zSuf;
	zPre := GetConfigString( zElem, "Prefix" );
	zSuf := GetConfigString( zElem, "Suffix" );

	//Prefixes + Suffixes already on the weapon
	var xPre, xSuf;
	xPre := GetObjProperty( item, "enchPrefix" );
	xSuf := GetObjProperty( item, "enchSuffix" );

	if( !xPre )
	    xPre := {};
	endif
	if( !xSuf )
	    xSuf := {};
	endif

	if( zPre )
	    xPre.append( zPre );
	endif
	if( zSuf )
	    xSuf.append( zSuf );
	endif

	//Dont be a silly kent
	SetObjProperty( item, "enchPrefix", xPre );
	SetObjProperty( item, "enchSuffix", xSuf );

	return 1;

endfunction