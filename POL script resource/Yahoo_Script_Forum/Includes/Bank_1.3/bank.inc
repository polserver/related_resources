// Bank.inc
// By Austin Heilman
//
// Created 10/22/01 11:31PM
// Updated 4/14/2002 10:21AM
//
// Somewhere, define a container for banks with the item name
// "BankBox" so you dont need to deal with object type numbers here
// plus making a custom container makes it easy to change the bank box
// graphic, container gump and item limits.
//

use uo;
use os;

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
	
	var bank := FindStorageArea( bank_name );
	if (!bank)
		CreateStorageArea( bank_name );
		bank := FindStorageArea( bank_name );
	endif
	
	//Find a box by serial because a mobile's name can change
	//but a serial never does :)
	var box_name := "Bankbox for " + hex(who.serial);
	
	var bank_box := FindRootItemInStorageArea( bank, box_name );
	if (!bank_box)
		CreateRootItemInStorageArea( bank, box_name, "BankBox" );
		bank_box := FindRootItemInStorageArea( bank, box_name );
		
		//Makes the storage file a little easier to read by storing
		//a person's account name and character name on the box.
		var temp := dictionary;
		temp["Name"] := who.name;
		temp["Account"] := who.acctname;
		SetObjProperty(bank_box, "Info", temp);
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
	
	SysLog("Removed bank box [" + bank_name + "] for [" + who.name + "]");
	
endfunction

// * RegisterBank(string)
//
// Registers the bank name in a global property called "banks".
// Used to keep track of what banks exist in the world.
//
// This is only run the first time a storage area is used.
//

function RegisterBank(bank_name)
	
	if ( (!bank_name) || (bank_name == error) )
		return 0;
	endif
	
	set_critical(1);
		var all_banks := GetBankNames();
				
		if ( !(bank_name in all_banks) )
			SysLog("Registering bank " + bank_name);
			all_banks.append(bank_name);
			SetGlobalProperty("banks", all_banks);
		endif
	set_critical(0);
endfunction

// * GetBankNames()
//
// Reads in the global property "banks" and returns an
// array of strings which are the names of banks in the world.
//

function GetBankNames()
	var all_banks := GetGlobalProperty("banks");
	if (!all_banks)
		all_banks := array;
		SetGlobalProperty("banks", all_banks);
	endif
	
	return all_banks;
endfunction
