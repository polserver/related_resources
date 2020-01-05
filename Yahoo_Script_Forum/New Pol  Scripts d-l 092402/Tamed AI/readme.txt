Modified Tamed AI:
MuadDib (sroyalty@rcsi-usa.com)

Required Core: Pol 94

Notes:

	What this does is simple. Any npc creature with the cprop
"rideable" it will allow transfers of. It still requires the taming 
and lore skill to command them, but allows them to be transferred to
be rideable at the most. It also adds in a check of the tamed 
Happiness at lvl 12. If they have the rideable cprop, it checks to see
if the happiness is 12 or lower and launches the AutoFeed function
I added in. This will feed a mounted creature IF they have the right
food in the pcs backpack.

Installation:

1) replace the tamed.src in /scripts/ai

2) Add the following to every "mountable" creature in npcdesc..
   CProp    rideable      i1


Todo: 

Anyone willing to help fix these problems are welcome to it : )
Any bug reports email me.
