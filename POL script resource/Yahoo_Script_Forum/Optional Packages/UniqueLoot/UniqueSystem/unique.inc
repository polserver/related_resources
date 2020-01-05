use os;
use uo;

include "include/objtype";

function getItemUniqueBox()
	var i := 1;
	var a := {};
	foreach item in EnumerateItemsInContainer(getUniqueBox())
		a[1] := item;
		i := i + 1;
	endforeach
	var rand := 1 + RandomInt(1);
	return a[rand];
endfunction

function toUniqueBox(item)
	MoveItemToContainer(item, getUniqueBox());
endfunction

function getUniqueBox()
	var worldbank := OpenWorldBank();
	var uniques := "uniques";
	var uniquebox := FindRootItemInStorageArea( worldbank, uniques );
	if (!uniquebox)
		uniquebox := CreateRootItemInStorageArea( worldbank, uniques, UOBJ_BANKBOX);
	endif
	return uniquebox;
endfunction

function openUniqueBox(you)
	SendOpenSpecialContainer(you, getUniqueBox());
endfunction

function OpenWorldBank()
  var bank := FindStorageArea( "World Bank" );
  if (!bank)
    bank := CreateStorageArea( "World Bank" );
  endif
  if (!bank)
    syslog( "Unable to open or create world bank!" );
  endif
  return bank;
endfunction
	




		
		
