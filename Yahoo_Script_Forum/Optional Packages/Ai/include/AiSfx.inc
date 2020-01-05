///////////////////////////////////////////////////////////
// AiSfx.inc
//
// AI special effects.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use uo;

include "/include/client";

///////////////////////////////////////////////////////////
// Purpose:	Makes the mobile glow by equipping a light source.
// Params:  who		Ref to mobile
//			level	1 = candle light (small radius, dim)
//					2 = torch light (large radius, dim)
//					3 = lantern light (large radius, bright)
// Returns: 1	Success.
//			0	Failed, invalid level.
///////////////////////////////////////////////////////////
function Glow(byref who, level)
	var lightsrc;

	case (level)
		1:	lightsrc := "candle1";
		2:	lightsrc := "torch2";
		3:	lightsrc := "lantern1";
		default:
			return 0;
	endcase

	// Create the light source.
	var itm := CreateItemInBackpack(who, lightsrc, 1);
	if (!EquipItem(who, itm))
		DestroyItem(itm);
		return 0;
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Stops the glow on a mobile, by destroying light
//			source.
// Params:  who
// Returns: N/A
///////////////////////////////////////////////////////////
function NoGlow(byref who)
	var itm := GetEquipmentByLayer(who, LAYER_HAND1);
	DestroyItem(itm);
endfunction
