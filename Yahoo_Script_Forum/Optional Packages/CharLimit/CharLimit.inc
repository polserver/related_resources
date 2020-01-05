///////////////////////////////////////////////////////////
// CharLimit.inc
//
// Character Limit functions.
//
// Creator: Oroborous
// Contact: mkow@sympatico.ca
//
// Created: Dec-2000
///////////////////////////////////////////////////////////

use uo;

include "include/cmdlevel";

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const MAX_CHAR_IDX		:= 2;
const MIN_CHAR_SWITCH_DELAY	:= 60 * 5;//* 60 * 2; // 2hr.

///////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////
var DenyMsg := "";		// Deny message.

//////////////////////////////////////////////////////////
// Purpose:	Returns the index of the char.
// Params:	who			Ref to mobile.
// Returns: idx			Index (1 to 5)
//			0			Not found!
///////////////////////////////////////////////////////////
function GetCharIdx(byref who)
	var chr;
	var idx;
	for (idx := 1; idx <= 5; idx := idx + 1)
		chr := (who.acct).GetCharacter(idx);
		if (who.serial = chr.serial)
			return idx;
		endif
	endfor

	return 0;
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Returns true if can logon with that char.
// Params:	who			Ref to mobile.
//			idx			Index.
// Returns: 1/0
///////////////////////////////////////////////////////////
function CanLogonWithChar(byref who, idx)
	// Check that char is not in an invalid slot.
	if (idx > MAX_CHAR_IDX)
		DenyMsg := "You may only use the first " + MAX_CHAR_IDX + " character slots.";
		return 0;
	endif
	
	// Staff can have more than 1 char!
	if (who.cmdlevel > CMD_PLAYER)
		return 1;
	endif
	
	// Delete the failed login if it's there.
	EraseObjProperty(who, "FailedLogin");
	
	// Check the last login on the char.
	var lastinfo := GetLastOnlineInfo(who);
		
	if (lastinfo[1] = idx)	// Same char logging in.
		return 1;
	else	// Different char logging in.
		// Check the last char logon.
		var timepassed := ReadGameClock() - lastinfo[2];
		if (timepassed > 0 and timepassed < MIN_CHAR_SWITCH_DELAY)
			var timeleft := MIN_CHAR_SWITCH_DELAY - timepassed;
			var minutes := timeleft / 60;
										
			DenyMsg := "You may not login with this character for another " + minutes + " minutes.";
			SetObjProperty(who, "FailedLogin", 1); // Mark it for logoff script so it knows it failed...
			return 0;
		endif
	endif

	return 1;		
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Get/Set last online info on account.
// Params:	who			Ref to mobile.
// Returns: lastinfo	Charindex from account.
//						Array {idx, lastonlinetime}
///////////////////////////////////////////////////////////
function GetLastOnlineInfo(byref who)
	var lastinfo := (who.acct).GetProp("LastOnlineInfo");
	if (!lastinfo)
		lastinfo := {0, 0};
	endif
	
	return lastinfo;
endfunction

function SetLastOnlineInfo(byref who, idx)
	var onlineinfo := array;
	onlineinfo.append(idx);
	onlineinfo.append(ReadGameClock());

	(who.acct).SetProp("LastOnlineInfo", onlineinfo);
endfunction

///////////////////////////////////////////////////////////
// Purpose:	Shows the deny login gump.
// Params:	who		Ref to mobile.
// Returns: N/A
///////////////////////////////////////////////////////////
function ShowDenyLoginGump(byref who)
	var onlineinfo := GetLastOnlineInfo(who);
	var nextlogin := ReadGameClock() - onlineinfo[2];
	
	GFInitGump(0, 0);
	GFResizePic(0, 0, BKGND_MARBLE, 640, 480);
	GFNoDispose();
	GFNoMove();
	GFNoClose();
	GFTextMid(0, 240, 640, COLOR_RED, DenyMsg);
	GFButtonID(300, 440, G_GREEN_OVAL_OK_0, G_GREEN_OVAL_OK_1, 1);
	
	GFSendGump(who);
endfunction