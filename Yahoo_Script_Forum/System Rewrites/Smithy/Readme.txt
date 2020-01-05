This is based on the original blacksmithing code from pol091, I just added a lil bit here and there :)

You must enter your coloured ingots into colours.cfg
The current colours.cfg is setup for my shard
Unfortunately i couldnt get ExtraAR to be for the full suit (only ar_mod is read-write), so it is per-peice... which means you cant get it very fine but oh well :(

I also changed exceptional items, so you might want to change that back to normal...
I changed the code that checks if the object is a useable ingot (it now reads from the CFG)

CFG stuff:
----------
Name = Name to go at the start of item:
Name "Bronze" = Bronze Platemail Gauntlets
------------------------------------------
SkillReqAddition = Extra skill difficulty to craft an item...
Dont put this too high, else they will fail all the time :/
-------------------------------------------------------------
MinSkill = Minimum skill to use the ingot, not related to above
---------------------------------------------------------------
Color = Color for the item made out of the ingot,
can be different to ingot colour, if its 0, will use ingot colour.
------------------------------------------------------------------
ExtraHP = Extra HP for that item
--------------------------------
ExtraAR = Extra AR for armour, (value is extra for EACH PEICE)
-------------------------------------------------------------
ExtraDamage = Extra damage for weapon to deal,
requires this in mainhitscript (pkg\combat):

	if ( GetObjProperty(weapon, "SCXDmg") )
		rawdamage := rawdamage + GetObjProperty(weapon, "SCXDmg");
	endif

@ the top will do fine... :)
----------------------------
Enchantment... sets CProps "SENCHANTED 1" and "[Enchantment entry] 1", if Enchantment is set to 0 it wont set any CProps
-------------------------------------------------------------------

Questions about what i stuffed up can be sent to sith@equalibrium.org or asked via ICQ (preffered) 38288137