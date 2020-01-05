=============================================================================
Runebook v3.0	2001-01-27	Shilohen (shilohen@hotmail.com)
=============================================================================


Features
=============================================================

	OSI style runebook.
	Add runes by dragging recall rune on it.
	Recharge by dragging recall scrolls on it.
	Can store up to 16 recall runes.
	Allow rune removal and default location.
	
=============================================================


Installation
=============================================================

	This package require POL092 or better version to be used,
	older version won't allow it.
	
	
	Unzip the file in either
		/pkg/std/runebook/
		or
		/pkg/opt/runebook/
		
	If you're already using an older runebook version,
	unzip the files into the same package. The new version
	include a conversion program for the old runebooks.
	
	The runebooks are newbied presently, if you don't want this,
	remove
	
		Newbie	1
		
	from the itemdesc.cfg
	
	
	To be able to use the default location feature, you'll have
	to alter recall and gate spell scripts this way:
	
	Find either of those lines in the script:
	
		if( cast_on.objtype != UOBJ_RUNE )
		or
		if( cast_on.objtype != 0x1F14 )
		
		
		
	Replace it with either, depanding if you use objtype.inc or not :
	
		if( cast_on.objtype != UOBJ_RUNE and cast_on.objtype != 0x6100 )
		or
		if( cast_on.objtype != 0x1F14 and cast_on.objtype != 0x6100 )
		

	You're ready to go :)
	
=============================================================