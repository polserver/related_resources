
include "include/math";

function CheckSpell(char, spellid)

	const SPELLBOOK_OBJTYPE := 0xa237;

	var magic := spellid;
	var circle := 1;
	var spellnum := 0;
	var cancast := 0;
	
	while (!spellnum)
	    if (magic <= 8)
        	 spellnum := magic;
	    else
	        circle := circle + 1;
        	magic := magic-8;
	    endif
	endwhile

	var hand := GetEquipmentByLayer(char, 1);
	if (hand.objtype = SPELLBOOK_OBJTYPE)
	// it's a spellbook
		var innerspells := GetObjProperty(hand, "Circles");
		var thisspell := BitOut(innerspells[circle]);
		if (thisspell[magic])
			cancast := 1;
		else
			cancast := 2;
		endif
	endif

	if (cancast = 0)
		foreach item in EnumerateItemsInContainer(char.backpack)
		    if (item.objtype = SPELLBOOK_OBJTYPE)
		    // it's a spellbook
       	                  var innerspells := GetObjProperty(item, "Circles");
       	      	          var thisspell := BitOut(innerspells[circle]);
               		  if (thisspell[magic])
                             cancast := 1;
       	           	  else
               	             cancast := 2;
       	                  endif
        	    endif
       		endforeach
	endif

        case (cancast)
             0:
             2: 
	     default:
                PrintTextAbovePrivate(char, "You do not have this spell in your spellbook.", char); 
                return 0;
             1:
                return 1;
        endcase
endfunction


