
Begging Notes
-------------

Installation, thats simple:  

Extract the zip into pkg/std/begging (or pkg/opt/begging)

Edit config/skills.cfg and remove the begging entry

Recompile scripts (not necessary, but suggested)

Unload the skills.cfg if that works, or restart the shard



Now for the possible pains
--------------------------

In order to beg successfully, begging first does a generic skills check, so you may want to edit
that function if you've added any more AI (I could have just checked the npc's graphic for humans, but there
are some npc's on my shard that I don't want to respond to begging.  I can just see players enticing evil humans
and begging them for money (even though it doesn't make much sense).

After you have made the proper changes, you need to make sure that your npc's have money!  Stock pol doesn't do
this, some replacement merchant packages do, but that leaves a whole lot of npcs without.  So whichever way you
like, either just when server starts, or at certain intervals, just create some gold in their backpacks.

Thats it, simple and sweet, comments and complaints to claywar@core.ods.org

