/*
Recursive equipment layer finder thingy
by Austin Heilman aheilman@home.com
written on 5-12-01
*/

use cfgfile;
use uo;
use util;

function destroyequip(mobile)
	//First, get a random item and make sure there is something there!
	if (isnude(mobile))
		return 0; // So if nothing returned, the character is naked :P
	endif
	
	var config := readconfigfile("::equiplayers");
	var slot;
	
	do
		slot := randomdiceroll("1d24");
	while(!config[slot] || !getequipmentbylayer(mobile, slot));
	
	//Now use recursion to find the item covering it.
	//Return the item reference to the script that wants it.
	return getequipmentbylayer(mobile, findtopitem(mobile, slot));

endfunction

function findtopitem(mobile, slot)
	var config := readconfigfile("::equiplayers");
	foreach protector in getconfigstringarray(config[slot], "coveredby");
		if (getequipmentbylayer(mobile, cint(protector)))
			return findtopitem(mobile, cint(protector));
		endif
	endforeach
	return slot;
endfunction

function isnude(mobile)
	var config := readconfigfile("::equiplayers");
	var i;
	for (i:=1;i<=25;i:=i+1)
		if (config[i] && getequipmentbylayer(mobile, i))
			return 0;
		endif
	endfor
	return 1;
endfunction