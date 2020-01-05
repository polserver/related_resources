///////////////////////////////////////////////////////////
// gumputil.inc
//
// Gump utility finctions.
//
// REQUIRES: Mythmarri's GUMPS package - v2.1
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 19-Apr-2000
// Updated: 19-Apr-2000
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// GUMP CONSTS
///////////////////////////////////////////////////////////

// Backgrounds
const BKGND_MARBLE			:= 0x0a28;

// Stretchable Dividers
const DIV_BLACK_LINE		:= 0x005d;

// Book
const G_BIGBOOK				:= 0x01fe;
const G_BIGBOOK_L_CORNER	:= 0x01ff;
const G_BIGBOOK_R_CORNER	:= 0x0200;

// Small circles with spell circle numbers 1-8.
const G_CIRCLE1				:= 0x08b1;
const G_CIRCLE2				:= 0x08b2;
const G_CIRCLE3				:= 0x08b3;
const G_CIRCLE4				:= 0x08b4;
const G_CIRCLE5				:= 0x08b5;
const G_CIRCLE6				:= 0x08b6;
const G_CIRCLE7				:= 0x08b7;
const G_CIRCLE8				:= 0x08b8;

// Diamond Buttons
const G_BLUE_DIAMOND_1		:= 0x0868;
const G_BLUE_DIAMOND_0		:= 0x086a;
const G_RED_DIAMOND_1		:= 0x09a9;
const G_RED_DIAMOND_0		:= 0x09aa;

// Octagon Skill 1-3 Buttons
const G_SKILL1				:= 0x04d8;
const G_SKILL2				:= 0x04db;
const G_SKILL3				:= 0x04de;

// Standard buttons.
const G_RED_PREV_1			:= 0x04f1;
const G_RED_PREV_0			:= 0x04f2;
const G_GREEN_CONT_1		:= 0x04f4;
const G_GREEN_CONT_0		:= 0x04f5;
const G_GREEN_DONE_1		:= 0x051a;
const G_GREEN_DONE_0		:= 0x0519;
const G_GREEN_OK_0			:= 0x0992;
const G_GREEN_OK_1			:= 0x0993;

// Oval buttons with gold border.
const G_RED_OVAL_CANCEL_1	:= 0x0818;
const G_RED_OVAL_CANCEL_0	:= 0x0817;
const G_RED_OVAL_PREV_1		:= 0x0913;
const G_RED_OVAL_PREV_0		:= 0x0912;
const G_GREEN_OVAL_OK_1		:= 0x081b;
const G_GREEN_OVAL_OK_0		:= 0x081a;
const G_YELLOW_OVAL_APPLY_1	:= 0x084b;
const G_YELLOW_OVAL_APPLY_0	:= 0x084a;

// Other Buttons
const G_SMALL_GEM_0			:= 0x04b9;
const G_SMALL_GEM_1			:= 0x04ba;
const G_TINY_GEM_0			:= 0x0837;
const G_TINY_GEM_1			:= 0x0838;

// Other.
const G_SQUARE_PLUS			:= 0x151a;
const G_SQUARE_MINUS		:= 0x1519;

// Words
const G_SKILLS				:= 0x0834;
const G_SKILL_USE			:= 0x0836;

// Stone Gumps
const G_TAB_0				:= 0x138e;
const G_TAB_1				:= 0x138f;
const G_MINUS_0				:= 0x138c;
const G_MINUS_1				:= 0x138d;
const G_STONE_SPHERE		:= 0x13a8;
const G_STONE_XBOX_0		:= 0x138a;
const G_STONE_XBOX_1		:= 0x138b;
const G_STONE_CHECK_0		:= 0x13ba;
const G_STONE_CHECK_1		:= 0x13bb;
const G_STONE_X_0			:= 0x13bc;
const G_STONE_X_1			:= 0x13bd;
const G_STONE_UP			:= 0x1458;
const G_STONE_DOWN			:= 0x1459;
const G_STONE_LEFT			:= 0x1467;
const G_STONE_RIGHT			:= 0x1468;
const G_STONE_SQUARE		:= 0x00d2;
const G_STONE_SQUARE_CHECK	:= 0x00d3;
const G_STONE_SQUARE_BLANK	:= 0x00d4;
const G_GRAY_CIRCLE_0		:= 0x00d0;
const G_GRAY_CIRCLE_1		:= 0x00d1;


// Arrows
const G_TRIANGLE_UP			:= 0x15e0;
const G_TRIANGLE_DOWN		:= 0x15e2;

// Tombstones
const G_TOMBSTONE_ROUND		:= 0x0065;
const G_TOMBSTONE_SQUARE	:= 0x0066;

// Seperators
const G_WAX_SEAL			:= 0x005c;
const G_FLAT_LINE			:= 0x005d;
const G_LEAF				:= 0x005e;

// COLOURS
const COL_YELLOW			:= 52;
const COL_RED				:= 32;
const COL_BLUE				:= 87;
const COL_DK_BLUE			:= 96;
const COL_LT_BLUE			:= 88;

// Text Entry Backgrounds
const G_TX_MARBLE_L			:= 0x0988;
const G_TX_MARBLE_S_LT		:= 0x098b;
const G_TX_MARBLE_S_DK		:= 0x098c;
const G_TX_MARBLE_M			:= 0x098d;
const G_TX_MARBLE_SQ_L		:= 0x098e;

///////////////////////////////////////////////////////////
// Purpose: Returns the index from a button group.
// Params:  arr		Array of keys in group.
//			value   Key val to compare to.
// Returns: index	Button # pressed.
///////////////////////////////////////////////////////////
function WhichIndex(arr, value)
	var index := 1;

	if (arr.size() = 0)
		return 0;
	endif

	foreach member in arr
		if (member = value)
			return index;
		else
			index := index + 1;
		endif
	endforeach

	return 0;
endfunction
