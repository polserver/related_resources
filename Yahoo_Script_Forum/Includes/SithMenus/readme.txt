SithMenus
Version 0.1

By S1tH
sithilius@hotmail.com
ICQ #38288137

---------------------

This menus system is designed to allow (easy) restricting of the objects displayed in menus. This is for things like only showing items that the player has enough skill and materials for.

It uses a different config file for the menus, which is almost identical to the menus.cfg used by the core, so it is easy to convert. This is called smenu.cfg ( note: you did not get a default :( ).

The difference is that the "Name" property from the old menus.cfg, becomes the element key. Ie:

ItemMenu
{
        Name    Tailoring
        Title   Choose a category.
	#etc etc...
}

[Becomes...]

Menu Tailoring
{
        Title   Choose a category.
	#etc etc...
}


--------------------
Using it in a script

Drop the menus.inc into your pol\scripts\include\ folder.
In the script make sure you add 

//
"include/menus";
//

At the top of the file.
Where the old menu call would have looked like

//
var what := SelectMenuItem2( who, menuname );
//

The sith menus one should look like

//
var what := SelectSithMenuItem( who, menuname );
//


-----------------------
Adding the restrictions

Restrictions are based on config files, ie. carpentry.cfg or tinker.cfg
The config file elements must have the *EXACTLY* the same objtype as the items specified. Having

//smenu.cfg
    Entry   0x0b56 Chair

//carpentry.cfg
carpentry 0xb56
{


will NOT work!! The numbers must be exactly the same. If they are not, the item will be displayed regardless of any restrictions.

In the script, you add the restrictions before you send the gump. The command for adding them is:

//
AddMenuRestriction( menuname, cfg_file, prop_name, prop_max );


The menuname is a menu name, ie. "carpentry" or "Tailoring"
The cfg_file is a name, ie ":carpentry:carpentry"
The prop_name is a name for a property in each element in that cfg, ie. "skill" or "material"
The prop_max is the highest amount the prop can be. ie. GetSkill( who, SKILLID_CARPENTRY );

The restrictions will automatically apply to any sub-menus. If you DONT want it to apply to submenus, then use

//
AddMenuRestriction( menuname, cfg_file, prop_name, prop_max, 0 );


So, as an example (for carpentry), to restrict by skill and material, you might have:

//
AddMenuRestriction( "carpentry", ":carpentry:carpentry", "material", GetAmount(logs) );
AddMenuRestriction( "carpentry", ":carpentry:carpentry", "skill",    GetSkill(character,SKILLID_CARPENTRY) );
var what := SelectSithMenuItem( character, "carpentry" );



-----------------------------
help! Your script is screwed!

ouch :/

you can get ahold of me on ICQ #38288137
or, if your willing to wait longer, email sithilius@hotmail.com