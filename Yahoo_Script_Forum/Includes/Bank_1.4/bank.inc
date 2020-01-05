// Bank.inc
// By Austin Heilman
//
// Created 10/22/2001 11:31PM
// Updated 10/24/2003 5:13PM
//
// Somewhere, define a container for banks with the item name
// "BankBox" so you dont need to deal with object type numbers here
// plus making a custom container makes it easy to change the bank box
// graphic, container gump and item limits.
//

use uo;
use os;
use polsys;

//Set the 'box_type' variable to the object name of the container type
//you want to be used for bank boxes. Example 'pouch' 'metalchest' etc.
//This is only used when a new bank box is created. It can be changed on
//the fly inside of a script for when you want to use specific container
//types for special storage areas. Ideally, you should make a object type
//with the name 'BankBox' to better control the number of items that can
//be put in the storage container.
var box_type		:= "BankBox";

//Toggles the bank related debug messages on and off.
var storage_debug_mode	:= 1;

// * GetBox(mobile, string)
//
// Returns the bank box of 'who' for the bank_name passed.
// bank_name defaults to  "Global"
//
// When a new bank box is made, its stored in a global
// property called "banks" through the RegisterBank() function
//
// Use SendOpenSpecialContainer(who, GetBox(who, bank_name));
// to show someone their bank box.
function GetBox(who, bank_name)

	if ( (!bank_name) || (bank_name == error) )
		bank_name := "Global";
	endif

	RegisterBank(bank_name);

	var bank := FindStorageArea(bank_name);
	if ( !bank )
		CreateStorageArea(bank_name);
		bank := FindStorageArea(bank_name);
	endif

	//Find a box by serial because a mobile's name can change
	//but a serial never does :)
	var box_name := "Bankbox for " + hex(who.serial);

	var bank_box := FindRootItemInStorageArea(bank, box_name);
	if ( !bank_box )
		set_critical(1);
		var new_box := CreateRootItemInStorageArea(bank, box_name, box_type);
		if ( new_box.errortext )
			return new_box;
		endif
		
		bank_box := FindRootItemInStorageArea(bank, box_name);

		//Makes the storage file a little easier to read by storing
		//a person's account name and character name on the box.
		var temp := dictionary;
		temp["Name"] := who.name;
		temp["Account"] := who.acctname;
		SetObjProperty(bank_box, "Info", temp);
		set_critical(0);
	endif

	return bank_box;

endfunction

// *DestroyBox(mobile, string)
//
// Used to remove a mobile's bank box and everything inside of it.
// When someone deletes a character, pol does not do this automatically
// so you may want to use this function with GetBankNames() to clear them.
//
function DestroyBox(who, bank_name)
	if ( (!bank_name) || (bank_name == error) )
		bank_name := "Global";
	endif

	var bank := FindStorageArea(bank_name);
	var box_name := "Bankbox for " + hex(who.serial);

	DestroyRootItemInStorageArea(bank, box_name);

	BankDbgMsg("Removed bank box [" + bank_name + "] for [" + who.name + "]");
endfunction

// * RegisterBank(string)
//
// Registers the bank name in a global property called "banks".
// Used to keep track of what banks exist in the world.
//
// This is only run the first time a storage area is used.
//
function RegisterBank(bank_name)
	return;
	
	if ( (!bank_name) || (bank_name == error) )
		return 0;
	endif

	set_critical(1);
	var all_banks := GetBankNames();
	if ( !(bank_name in all_banks) )
		BankDbgMsg("Registering bank " + bank_name);
		all_banks.append(bank_name);
		SetGlobalProperty("banks", all_banks);
	endif
	set_critical(0);
endfunction

// * GetBankNames()
//
// Returns an array of all storage area names.
//
function GetBankNames()
	/*
	var all_banks := GetGlobalProperty("banks");
	if (!all_banks)
		all_banks := array;
		SetGlobalProperty("banks", all_banks);
	endif
	return all_banks;
	*/
	// Note... for now I am having it use the StorageAreas()
	// function in polsys.em. It works kind of funny though.
	// It returns an array of the region names, but if you do
	// TypeOf() on the region name, you get <RegionName> like,
	// <Global> <Britain> <Minoc> etc. back. For now I convert them
	// to a string which works. I am not really sure what Syzygy has
	// planned for this function, but if its changed to work as I have
	// a feeling it was intended to work, this foreach will still work.
	// You can uncomment the global property usage above, and comment
	// the loop below though if any problems arise. Until I am certain
	// as to how Syzygy wants to make this function work, I am leaving
	// the global property tracking of bank region names in.
	var temp := array;
	foreach key in StorageAreas()
		temp.append(Cstr(key));
		sleepms(2);
	endforeach
	
	return temp;
endfunction

function BankDbgMsg(text)
	if ( storage_debug_mode )
		SysLog(text);
	endif
endfunction