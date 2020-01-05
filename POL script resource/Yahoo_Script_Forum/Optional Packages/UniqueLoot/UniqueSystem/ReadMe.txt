Description of Unique Item system.

The system works like this:
There is a global bankbox, which can be opened with .openuniques
In this bankbox you can store items that you wish to unique loot.
If a unique item decays or is removed then it will return to the uniquebox and be "recycled" if you wish to destroy an unique item completely you will have to use the .destroyunique on that specific item.
You can also make an abitrary item unique by using the .makeunique command. Then it will be treated as a unique item, and can be added to the box, if not added, it will be moved to the uniquebox on destruction.
The way players can get these unique items is getting the uniquebag, described below, as loot from monsters or what ever.

To make an item unique from a script, you will have to add to the item:

CProp unique i1
destroyscript :combat:destroy


Installation:
Move maindestroy.src to /scripts/control/
Move unique.inc to /scripts/include/
Move uniquebag.src /scripts/items/
Move the three textcommands to /scripts/textcmd/gm/

Now open destroy.src in /pkg/system/combat/
to includes add:

include "include/unique";

In the file locate

 case(type)
    "accuracy":     val := accuracy(who,item);
    "cursed":       val := cursed(who,item);
    "sight":        val := sight(who,item);
    "reflect":      val := reflect(who,item);
    "protection":   val := protection(who,item);
    "wizzohat":     val := wizzohat(who,item);
    "strength":     val := strength(who,item);
    "invisibility": val := invisibility(who, item);
    default:        val := 1;
  endcase

beneath this you shall add:

  if (GetObjProperty(item,"unique"))
    toUniqueBox(item);
    val := 0;
  endif


to your itemdesc.cfg now add this item:

item 0x7990
{
	Name	uniquebag
	color 133
	graphic             0x0E75
	desc	Strange looking bag
	Script	uniquebag
}


This item you can now just be added as loot.
When the bag created is doubleclicked, it moves a random item from the uniquecontainer to the players
backpack.

I think that is it...
Now just compile the new and edited .src files and you are ready to go.

If you have any question about the scripts feel free to mail or ICQ me.

Have fun,
Clemens

Mail: cnk@mail1.stofanet.dk
ICQ: 4409233


