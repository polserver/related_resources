This is an include file, which will read in destroyequip.cfg
and use it to find what layers in equipment are "covered" by
other layers. For example, if a player is wearing a shirt, 
it is protected by an armor layer, a tunic/sash layer and a
robe. So if those items are present, they must be found before
the shirt is.

The only issue that remains, is that if an item it finds, say a robe
is newbified, then it has to go back through the stack to find an
item that isnt newbified for situations where you want to use it to
destroy items, for example on Mytharria I have a clerical rite called
blade barrier that would shread equipment in order or the slimes that
spit could use this to hit gloves before they hit a ring.

To install, just place the config file in pol\config
and the include file (.inc) into yoru pol\scripts\include folder.
To use it, in a script use 

include "include/destroyequip";

At the point you want to find the top item call the function
destroyequip() and pass the mobile you want to check equipment
on. It will return the item as an item reference. 


-Austin