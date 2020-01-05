// Abs.inc


function Abs(x)

	if (x < 0)
		x := 0 - x;
	endif
	return x;

endfunction


///////////////////
//  trims off the extra stuff to find the basic NPCtemplate (usedful for putting NPCs in packages)
///////////////////

function TrimTemplate(npctemplate)
	if ( npctemplate[":"] )
		npctemplate[":"] := "";
		npctemplate := npctemplate[(find(npctemplate, ":", 1)+1), len(npctemplate)];
	endif
	return npctemplate;
endfunction


