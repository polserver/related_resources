New Crafting System (By Dream Weaver and Hammerstorm)

When we redid MR we wanted to make a cool crafting system, where multiple skills, tools,  and materials could be used to make a complex item. We also wanted to have the menu reference skill needs, and only display the items you can make. Here's what we have so far (known bugs to follow)

Crafting.src replaces tinkering, tailoring, blacksmithy, and a coupla other skills that escape me now. The crafting.cfg file contains everything you need. Here's the entries:

menu 0x13e3+0x1bf2      //using a hammer on (the graphic of) ingots, show the menu
{
	showmenu blacksmithing:hammeroningots
}


Note: multiple entries snipped -- check the file for details. Eventually you come to:

craftitem 0x156a           //the objtype of the item you want to make
{
Name Decorative Weapons
skill 7/75/600            //skill 7 is checked for 75 difficulty, and yields 600 raw points
skill 37/50/250
skill 11/40/150
material 0x1bf2/50       // you need 50 of objtype 0x1bf2 (ingots, I think)
material 0x1bdd/6 
material 0x1bd7/5 
exceptional 1            // this item can be exceptional
sound 0x2b/3             //play sound 0x2b 3 times
sound 0x242/2 
sound 0x23e/1 
tool 0xfaf/Select an anvil to use        // you need an anvil, and you're prompted for one if it can't see it
area forge                               // you have a forge item in the area (see areatools.cfg( 
tool 0x1035/Select the saw you wish to use to make the rack.      
tool 0x1ebc/Select the tinker's tools you will wire the display together with.
}


Please note that there is significant overlap between the itemdesc.cfg in this distro and the default POL distro. It'll take some tuning to get it in!

Known Bugs:

Material use is screwy as hell: the 3rd + materials aren't consumed correctly on failure, and sometimes the whole stack is taken

Failure messages are screwy.

If you have a question or fix, post to the board.