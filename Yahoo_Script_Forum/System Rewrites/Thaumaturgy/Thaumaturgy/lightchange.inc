
use uo;

function switch_light(who, item)


    local change   := GetObjProperty (item, "change");
    local current  := cint(item.graphic);
    local original := GetObjProperty (item, "original");

    if ((original="") or (!original))
	original := cint(item.graphic);
	SetObjProperty (item, "original", original);
    endif
	
    local sound;

    if(current=original)
      sound := GetObjProperty (item, "changesnd");
	if (sound)
		PlaySoundEffect(who , sound );
	endif
      item.graphic := change;

    elseif(current=change)

      sound := GetObjProperty (item, "originsnd");
	if (sound)
		PlaySoundEffect(who , sound );
	endif
      item.graphic := original;

    endif

endfunction
