
function unmount(who)
	var mount := GetEquipmentByLayer(who, 25);
	if (!mount)
		return;
	endif

	var CritterName := lower(GetObjProperty(mount, "template"));
	
	if (!CritterName)
		OldUnmount(who);
		return;
	elseif (CritterName["pack"])
		CritterName := "horse2";
	endif
	
	var animal := CreateNpcFromTemplate(CritterName, who.x, who.y, who.z);
	if (!animal)
		OldUnmount(who);
		return;
	endif
	
	animal.facing := who.facing;
	animal.color := mount.color;
	animal.name := GetObjProperty(mount, "petname");
	if(who.acctname)
		SetObjProperty(animal, "master", who.serial);
		SetObjProperty(animal, "prevtamed", 1);
		animal.script := "tamed";
		RestartScript (animal);
	endif
	DestroyItem(mount);
	
	return 1;
endfunction

function oldunmount(who)
	SendSysMessage(who, "Using old unmount function", SSM_INFO_DEBUG);
	local mount := GetEquipmentByLayer(who, 25 );

	local critter := "";
	case (mount.graphic)
		0x3ea2: critter := "horse";
		0x3e9f: critter := "horse2";
		0x3ea0: critter := "horse3";
		0x3ea1: critter := "horse4";
		0x3ea6:critter := "llama";
		0x3ea3:critter := "desertostard";
		0x3ea4:critter := "frenziedostard";
		0x3ea5:critter := "forestostard";
	endcase

	local animal := createnpcfromtemplate(critter, who.x, who.y, who.z);
	animal.facing := who.facing;
	animal.color := mount.color;
	animal.name := getobjproperty(mount, "petname");
	SetObjProperty (animal, "master", who.serial);
	SetObjProperty (animal, "prevtamed", 1);
	animal.script := "tamed";
	RestartScript (animal);
	
	DestroyItem( mount );

endfunction

function deathunmount(ghost, corpse)
	foreach mount in enumerateitemsincontainer(corpse.serial)
		var critter := "";
		if (mount.objtype == 0xF021)
			critter := getobjproperty(mount, "template");
			if (!critter)
				destroyitem(mount);
			endif
			var animal := createnpcfromtemplate(critter, ghost.x, ghost.y, ghost.z);
			if (!animal)
				PrintTextAbove(ghost, "Oh dear where could my horsey be.");
				printtextabove(ghost, "Please take note of this error message: " + animal.errortext);
				
				return;
			endif
			animal.facing := ghost.facing;
			animal.color := mount.color;
			animal.name := GetObjProperty (mount, "petname");
			SetObjProperty (animal, "master", ghost.serial);
			SetObjProperty (animal, "prevtamed", 1);
			animal.script := "tamed";
			RestartScript (animal);
			DestroyItem(mount);
		endif
	endforeach
endfunction