// mount.inc
// By Austin Heilman
//
// Created 4/24/2002 4:45PM
// Updated 4/24/2002 4:45PM
//
// Functions for mounting, and unmounting stuff on a mobile.
//

use uo;
use os;

include "include/uo_extend";
include "client/layers";

//Arbitrary objtype in the core.
const MOUNT_OBJTYPE := 0xF021;

// * Mount(who, mobile)
//
// 'who' is the mobile that the mount piece will be put on.
// 'mobile' is the horse, ostard, etc. that will be equipped on the
// 'who'. This modifies the mobile in no way.
//
// Return value is the mount piece that was equipped.
//
function Mount(who, mobile)
	Set_Critical(1);
	var mount_piece := CreateItemAtLocation(who.x, who.y, who.z, MOUNT_OBJTYPE, 1);
	mount_piece.graphic := GetMountGraphic(mobile);
	EquipItem(who, mount_piece);
	Set_Critical(0);
	
	return mount_piece;
endfunction

// * Unmount(who)
//
// 'who' is the mobile that is going to get Unmounted.
// This will get the npc type that the mount piece represents
// and recreate it, then destroy the mount piece.
//
// Returns an npc reference if one is created.
//
function Unmount(who)
	var mount_piece := GetEquipmentByLayer(who, LAYER_MOUNT);

	if ( !mount_piece )
		return 0;
	endif

	return RestoreAnimal(who, mount_piece);
endfunction

// * DeathUnmount(who, corpse)
//
// Function for creating the creature that was mounted when a mobile dies.
// It searches the corpse container for any mount pieces and recreates the
// npc.
//
// Returns an npc reference if one is created.
//
function DeathUnmount(ghost, corpse)
	var mount_piece;
	foreach item in EnumerateItemsInContainer(corpse)
		if ( item.objtype == MOUNT_OBJTYPE )
			mount_piece := item;
			break;
		endif
	endforeach
	
	return RestoreAnimal(ghost, mount_piece);
endfunction

// * RestoreAnimal(who, mount_piece)
//
// Passes the person and the mount piece.
// The mount piece is then used to determine what npc will be created.
// It makes the animal face the same direction as 'who', the 
// color based on the mount piece's color and sets the animal up to
// be under the control of 'who'.
//
// Returns the npc that was created.
//
function RestoreAnimal(who, mount_piece)
	var template := GetMountTemplate(mount_piece);
	var animal := CreateNpcFromTemplate(template, who.x, who.y, who.z);
	
	animal.facing := who.facing;
	animal.color := mount_piece.color;
	animal.name := GetObjProperty(mount_piece, "petname");
	if( who.acctname )
		SetObjProperty(animal, "master", who.serial);
		RestartScript (animal);
	endif
	DestroyItem(mount_piece);
	
	return animal;
endfunction


// * GetMountGraphic(mobile)
//
// Returns the graphic of the mount piece that represents the
// mobile passed based on its graphic.
//
function GetMountGraphic(mobile)
	var mount_piece := 0;
	case(mobile.graphic)
		0xCC: mount_piece := 0x3EA2;
		0xC8: mount_piece := 0x3E9F;
		0xE2: mount_piece := 0x3EA0;
		0xE4: mount_piece := 0x3EA1;
		0xDC: mount_piece := 0x3EA6;
		0xD2: mount_piece := 0x3EA3;
		0xDA: mount_piece := 0x3EA4;
		0xDB: mount_piece := 0x3EA5;
		
		default: return 0x3EA2;
	endcase
endfunction

// * GetMountTemplate(mount_piece)
//
// Gets the npctemplate the mount piece represents.
// It will first check the mount piece for a cprop called "template"
// if there is no such cprop, it will set the template based on the
// graphic of the mount piece.
//
// Return value is an npc template
//
function GetMountTemplate(mount_piece)
	var template := GetObjProperty(mount_piece, "template");

	if ( !template )
		case (mount_piece.graphic)
			0x3EA2: template := "horse";
			0x3E9F: template := "horse2";
			0x3EA0: template := "horse3";
			0x3EA1: template := "horse4";
			0x3EA6: template := "llama";
			0x3EA3: template := "desertostard";
			0x3EA4: template := "frenziedostard";
			0x3EA5: template := "forestostard";
			//If we dont know what it is, give them a rat :)
			default: template := "rat";
		endcase
	endif
	template := lower(template);
	return template;
endfunction
