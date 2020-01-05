///////////////////////////////////////////////////////////
// OrcConsider.inc
//
// Orc consider processing.
//
//
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Purpose: Something entered my area.
// Params:  opponent	Mobile I spotted.
// Returns: 0		Continue with consider processing.
//			1		Attack immediately!!!
//					**No more consider code will be processed.
///////////////////////////////////////////////////////////
function Consider(byref opponent)
	// Kill Virdd on sight!
	var race := GetObjProperty(opponent, "Race");
	if (race = "Virdd")
		Say("Me keel you stoopid Virdd!");
		return 1;
	endif
	return 0;
endfunction
