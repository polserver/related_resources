New snooping and stealing
-------------------------
This script allows players to snoop and steal the items you define 
from the npcs that you define. Stealing from other players is imposible.
 

Which bit goes where?
---------------------

the snooping folder and the stealing folder replace existing folders in
pol\pkg\std


What do I do next?
--------------------
Next you will have to edit the stealme.cfg in the snooping folder and
make an entry for each npc that you want players to be able to snoop
and steal from. Follow the same format as the the default example npc person

once your npcs are in the stealme.cfg open up the snooping.src and edit the
function isaplayer() list your npc templates there, the return value for each 
template is the difficulty to steal from that npc. I put five npcs in there already
to get you started but you will need to edit them so that they correspond with 
the npctemplates you listed in stealme.cfg

once the npcs have been added recompile 


How do I snoop/steal?
---------------------

you need thiefgloves to try out the script make to make some type
.create 0xc53e

currently the only npc you can steal from is a person
type .createnpc person to make one and try it out

to snoop them double click gloves then target person

once pack is open click the blue button in skills menu next to stealing 
and target and item in their pack

the difficulty level of the person is 10.


Feedback, comments, questions and suggestions to
rosie@twisted-kitten.com


-=Arcadia=-