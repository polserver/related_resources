///////////////////////////////////////////////////////////
// MerchantNonCombat.inc
//
// Merchant non combat actions.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Purpose: Processing for NPC when not in combat.
// Params:	none
// Returns: 1	Do no more non combat processing.
//			0	Comntinue with non combat processing.
///////////////////////////////////////////////////////////
function NonCombat()
	RestockInventory();

	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Processing per mobile seen in non combat.
// Params:  mobile		Ref to mobile seen.
// Returns: 1	No more processing for this mobile.
//			0	Continue main processing for this mobile.
///////////////////////////////////////////////////////////
function NonCombatPerMobile(byref mobile)
	return 0;
endfunction