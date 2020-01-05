///////////////////////////////////////////////////////////
// Looter.inc
//
// Main looting processing.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const NOLOOTPROP	:= "noloot";
const LOOTEDPROP	:= "#looted";

const STARTHAIR 	:= 0x2030;
const ENDHAIR 		:= 0x2060;

///////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////
var NextLoot := 0;

///////////////////////////////////////////////////////////
// Purpose: Main looting function.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function GrabLoot()
	// Am I a looter?
	if (!ai.GrabLoot)
		return 0;
	endif

	// Has enough time passed since last looting?
	var loottime := ReadGameClock();
	if (NextLoot > loottime)
		return 0;
	endif
	NextLoot := NextLoot + ai.LootFrequency;

	LookForLoot();

	if (ai.EquipLoot)
		EquipLoot();
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Looks around for loot.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function LookForLoot()
	var lootitm;

	foreach item in ListItemsNearLocation( me.x, me.y, me.z, ai.ConsiderRange);
		// Is it an item, and can I really see it?
		if (item.isa(POLCLASS_ITEM) and CheckLineOfSight(me, item)
			and !GetObjProperty(item, LOOTEDPROP))

			// Check if it is on a multi.
			var sh := GetStandingHeight(item.x, item.y, item.z);
			if (sh.multi or sh.multi.serial)
				continue;
			endif

			// Can I walk where it is?
			var info := cint(GetMapInfo(item.x , item.y).landtile);
			if ((info > cint(0x405)) and (info < cint(0x456)))
				continue;
			endif

			if (!ItemIsLootable(item))
				continue;
			endif

			// Is it locked?!  It could be...
			if (item.locked)
				continue;
			endif

			// Walk to item...
			while (item and Distance(me, item) > 1)
				MoveToward(item);
				ProcessCombatEvent(); // We could be attacked, don't ignore attacks.
			endwhile

			if (item.isa(POLCLASS_CONTAINER) and ai.LootCorpses) // Loot an item off the corpse.

				// Rifle through the corpse.
				var corpseitems := EnumerateItemsInContainer(item);

				foreach citm in corpseitems
					if (!ItemIsLootable(citm, 1))
						continue;
					endif

					lootitm := citm;
					break; // Loot this item.
				endforeach;
			else
				lootitm := item;
			endif

			// Nothing to loot?  Mark corpse looted.
			if (!lootitm)
				SetObjProperty(item, LOOTEDPROP, 1);
				return;
			endif

			// Loot item.
			SaySpeechStuff(SAYLOOT);
			Sleep(AI_LOOT_DELAY);
			MoveItemToContainer(lootitm, me.backpack, x := -1, y := -1);
			return;
		endif
	endforeach
endfunction

///////////////////////////////////////////////////////////
// Purpose: Determines if the item is lootable.
// Params:  item		Ref to item object.
//			incontainer Item is inside a container.
// Returns: 1		It is lootable.
//			0		Can't loot it.
///////////////////////////////////////////////////////////
function ItemIsLootable(byref item, incontainer := 0)
	// Can I move it?
	if (!item.movable and !item.isa(POLCLASS_CORPSE) and !incontainer)
		return 0;
	endif

	// Is it hair?
	if (item.objtype >= STARTHAIR and item.objtype <= ENDHAIR)
		return 0;
	endif

	// Is it marked noloot?
	if (GetObjProperty(item, NOLOOTPROP))
		return 0;
	endif

	return 1;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Equips anything I have in my pack.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function EquipLoot()
	foreach item in EnumerateItemsInContainer(me.backpack)
		EquipItem(me, item);
	endforeach
endfunction