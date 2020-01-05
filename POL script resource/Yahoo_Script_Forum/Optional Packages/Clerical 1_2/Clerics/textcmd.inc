/*
Checks to see if a player has the rite.
Simply go hasrite(who, "ritename") and
it will return the script and number.
*/
use cfgfile;

const BOOK := 0xf903;

function HasRite(who, ritename)
	var config := ReadConfigFile("rites");
	var total := GetConfigMaxIntKey(config);
	
	var canonlist := FindCanons(who);
	var i;
	
	for (i:=1;i<=total;i:=i+1)
		if (lower(config[i].Name) == lower(ritename) && CheckBook(i, canonlist))
			return i;
		endif
	endfor
	return 0;
endfunction

function CheckBook(number, canonlist)
	var temp;
	foreach canon in canonlist
		temp := GetObjProperty(canon, "Rites");
		if (number in temp)
			return 1;
		endif
	endforeach
	return 0;
endfunction

function FindCanons(who)
	var canonlist := {};
	foreach item in EnumerateItemsInContainer(who.backpack.serial)
		if (item.objtype == BOOK)
			canonlist.append(item);
		endif
	endforeach
	return canonlist;
endfunction