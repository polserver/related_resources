// ********************************************************************************
// ***
// ***	fishing.inc defines the constants that are unique to the fishing skill
// ***	It is intended to be left in the pkg folder to keep these constants with
// ***	the source files for the scripts
// ***
// ********************************************************************************


// ********************************************************************************
//	Miscellaneous constants
// ********************************************************************************
Const UACTION_FISHING := 0x9;		// the action number for the casting animation
Const SFX_SKILL_FISHING	:= 0x0240;	// sound effect for the fishing skill
Const FISHING_RANGE := 6;		// the tile radius that this skill can target
// Const FISHING_GAIN_AMOUNT := 100;	// gain 100 raw skill points per success
Const MAXMAPLEVEL := 4;			// maximum level of treasure map that can be fished up
Const GAIN_MULTIPLIER := 10;		// this is used with harvest difficulty to calculate skill gain
Const MISC_SOS_TREASURE_PCT := 75;	// this is the percentage of getting a misc treasure when fishing an SOS
Const SOS_SKILL_POINTS := 500;		// Skill points awarded for a successful SOS fishing attempt
Const SOS_SKILL_THRESHOLD := 80;	// Skill level to check SOS attempts against
Const MSG_COUNT := 4;			// the number of unique SOS messages currently supported

// ********************************************************************************
//	objectype constants
// ********************************************************************************
Const UOBJ_TREASURE_CHEST := 0x0E40;	// objectype of a treasure chest
Const UOBJ_SOS_BOTTLE := 0xA360;	// objectype of an SOS bottle
Const UOBJ_SOS_MESSAGE := 0xA363;	// objectype of an SOS message
Const UOBJ_MAGIC_FISH := 0xA368;	// objectype of first magic fish in series
Const NUM_MAGIC_FISH := 8;		// number of different magic fish

// ********************************************************************************
//	These constants define both the skill level at which a certain type of object can be
//	caught while fishing, and the percentage chance that they have to get such an item
// ********************************************************************************
Const SHOELEVEL := 60;	
Const MAGICFISHLEVEL := 80;
Const TREASUREMAPLEVEL := 90;
Const SOSLEVEL := 99;

// ********************************************************************************
//	These constants define the operation of miscellaneous SOS treasures.  Some of
//	these constants define the beginning and ending objtypes of the items that
//	will be fished up as misc items while fishing an SOS message.  The NUM_SOS_MISC
//	constant reflects the number of different misc SOS treasure categories that
//	are currently in use.  You must also alter the GetSOSTreasure function in
//	fishing.src if you want to add new misc SOS item categories.
// ********************************************************************************
Const NUM_SOS_MISC := 4;        // number of misc SOS item categories 
Const BEGINSHELL := 0x0FC4;
Const ENDSHELL := 0x0FCC;
Const BEGINART := 0x0E9F;
Const ENDART := 0x0EAF;
Const BEGINWIRE := 0x1876;
Const ENDWIRE := 0x1879;
Const BEGINPILLOW := 0x13A4;
Const ENDPILLOW := 0x13AE;

