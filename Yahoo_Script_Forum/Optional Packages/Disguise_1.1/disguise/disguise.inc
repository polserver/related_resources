include "include/client";

function RemoveDisguise(who)
	if (GetObjProperty(who, "$disguised"))
		var orig_look := GetObjProperty(who, "$disguised");
		
		if (orig_look.name)
			who.name := orig_look.name;
		endif
		
		if (orig_look.gender)
			who.graphic := orig_look.gender;
		endif

		if (orig_look.skincolor)
			who.color := orig_look.skincolor;
		endif
	
		if (orig_look.hairstyle)
			if (!GetEquipmentByLayer(who, 11))
				var hair := CreateItemInBackPack(who, orig_look.hairstyle);
				EquipItem(who, hair);
			else
				GetEquipmentByLayer(who, 11).graphic := orig_look.hairstyle;
			endif
			
			if (orig_look.haircolor)
				GetEquipmentByLayer(who, 11).color := orig_look.haircolor;
			endif
		else
			DestroyItem(GetEquipmentByLayer(who, 11));
		endif
	
		if (orig_look.facialhair)
			if (!GetEquipmentByLayer(who, 16))
				var hair := CreateItemInBackPack(who, orig_look.facialhair);
				EquipItem(who, hair);
			else
				GetEquipmentByLayer(who, 16).graphic := orig_look.facialhair;
			endif
			
			if (orig_look.haircolor)
				GetEquipmentByLayer(who, 16).color := orig_look.facialhaircolor;
			endif
		else
			DestroyItem(GetEquipmentByLayer(who, 16));
		endif
		
		EraseObjProperty(who, "$disguised");
		return 1;
	endif

	return 0;
endfunction
