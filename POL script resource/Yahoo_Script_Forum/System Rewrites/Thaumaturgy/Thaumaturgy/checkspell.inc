
include "include/math";

function CheckSpell(char, spellid)

	const SPELLBOOK_OBJTYPE := 0xa237;

	local magic := spellid - 108;
	local circle := 1;
	local spellnum := 0;
	
	while (!spellnum)
	    if (magic <= 8)
	         spellnum := magic;
	    else
	        circle++;
	        magic := magic-8;
	    endif
	endwhile
	
	local cancast := 0;
	foreach item in EnumerateItemsInContainer(char.backpack)
	    if (item.objtype = SPELLBOOK_OBJTYPE)
	    // it's a spellbook
	         if (char.serial = GetObjProperty(item, "ownerserial"))
	         // it's bound to me
                        local innerspells := GetObjProperty(item, "Circles");
                        local thisspell := BitOut(innerspells[circle]);
                        if (thisspell[magic])
                             cancast := 1;
                        else
                             cancast := 2;
                        endif
                  endif
            endif
        endforeach
        case (cancast)
             0:
             default:
                PrintTextAbovePrivate(char, "You do not have a spellbook to which you are bound.", char);
                return 0;
             2: 
                PrintTextAbovePrivate(char, "You do not have this spell in your spellbook.", char); 
                return 0;
             1:
                return 1;
        endcase
endfunction
