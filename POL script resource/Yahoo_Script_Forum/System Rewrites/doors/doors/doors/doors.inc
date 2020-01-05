
include "include/client";
include "include/objtype";

function IsLocked(me,door,options := "no",closed := "no")

Const KEYSTART := 0x100E;
Const KEYEND := 0x1013;
Const KEYRING := 0x1011;

	local doorlockid;
	local keylockid;
	local insidering;

	if ((!door.locked) or ((GetObjProperty(door,"WhenOpened")) and (closed = "yes")))
		return 0;
	else
               if (((me.multi) and (options != "no")) or (GetObjProperty(door, "UseFlow")))
                    if (options = "house")
                       local params := array;
                       params[0] := me;
                       params[1] := door;
                       local innerlock := run_script_to_completion(":housing:innerlock", params);
                       if (innerlock)
                             return 0;
                       endif
                       return 1;
                    endif
                    if (((options = "yes") or ((options = "front") and (GetObjProperty(door, "Front")))) or (GetObjProperty(door, "UseFlow")))
                       case (GetObjProperty(door, "Flow"))
                           "S":
                                if (door.y < me.y)
                                     PrintTextAbovePrivate( door, "The door is locked, but you open it from the inside." , me);
                                     return 0; 
                                endif
                           "E":
                                if (door.x < me.x)
                                     PrintTextAbovePrivate( door, "The door is locked, but you open it from the inside." , me);
                                     return 0; 
                                endif
                           "W":
                                if (door.x > me.x)
                                     PrintTextAbovePrivate( door, "The door is locked, but you open it from the inside." , me);
                                     return 0; 
                                endif
                           default:
                           "N":
                                if (door.y > me.y)
                                     PrintTextAbovePrivate( door, "The door is locked, but you open it from the inside." , me);
                                     return 0; 
                                endif
                       endcase
                   endif
                endif
            
		doorlockid := GetObjProperty( door, "lockid" );
		if (!doorlockid)
			return 1;
		endif
		local MyKeys := EnumerateItemsInContainer(me.backpack);
		foreach key in MyKeys
			if ( (key.objtype >= KEYSTART ) and (key.objtype <= KEYEND) and 
			  (key.objtype != KEYRING ) )
				keylockid := GetObjProperty( key, "lockid" );
				if ( (keylockid) and (keylockid = doorlockid) )
					PrintTextAbovePrivate( door, 
					  "You quickly unlock, use and re-lock the door", me );
					return 0;
				endif
			elseif (key.objtype = KEYRING)
				insidering := FindMyPack(key.serial);
				foreach otherkey in EnumerateItemsInContainer(insidering)
					keylockid := GetObjProperty( otherkey, "lockid" );
					if (keylockid = doorlockid)
						PrintTextAbovePrivate( door, 
					  	  "You quickly unlock, use and re-lock the door", me );
						return 0;
					endif
				endforeach
			endif
		endforeach
	endif
				
	return 1;				

endfunction

function OpenTamedStorageAreas()

    local bank := FindStorageArea( "Tamed Storage" );
    if (!bank)
        bank := CreateStorageArea( "Tamed Storage" );
    endif

    return bank;

endfunction

function FindMyPack(myserial)

    local mybank := OpenTamedStorageAreas();

    local bank_obj_name := "Bankbox  " + hex(myserial);

    local bankbox := FindRootItemInStorageArea( mybank, bank_obj_name );

    if (!bankbox)
        bankbox := CreateRootItemInStorageArea(mybank, bank_obj_name, UOBJ_BANKBOX  );

    endif
    
    return bankbox;

endfunction
