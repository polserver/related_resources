include "include/objtype";

function OpenTamedStorageAreas()
    local bank := FindStorageArea( "Tamed Storage" );
    if (!bank)
        bank := CreateStorageArea( "Tamed Storage" );
    endif

    if (!bank)
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

function FindExistingPack(myserial)
    local mybank := OpenTamedStorageAreas();

    local bank_obj_name := "Bankbox  " + hex(myserial);

    local bankbox := FindRootItemInStorageArea( mybank, bank_obj_name );

    if (!bankbox)
    	return 0;
    endif
    
    return bankbox;

endfunction

function MoveBackpackToCorpse(container)
        
	local myserial := GetObjProperty(container, "serial");

	if (!myserial)
		return;
	endif
   
        local mypack := FindExistingPack(myserial);
        if (!mypack)
                return 0;
        endif
         if( GetObjProperty( container , "summoned" ) )
                foreach thingie in EnumerateItemsInContainer(mypack)
			if (distance(thingie,container) != 0)
			        moveitemtolocation(thingie, container.x, container.y, container.z,0);
			endif
                endforeach
                return 0;
        else
                foreach thingie in EnumerateItemsInContainer(mypack)
			if (distance(thingie,container) != 0)
				moveitemtocontainer(thingie, container);
			endif
                endforeach
                return 1;
        endif
endfunction
