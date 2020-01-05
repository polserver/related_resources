Last Update: 4 - April - 2001

See the AI's killpcs and archerkillpcs as examples of the use of the new function closedistace.  
The new function is based on CheckLineofSight, if the npc doesn't have vision line for the opponent, he angers to seek a point with the smallest it distances for the enemy that he/she has vision line for both, he will go to that point and later for the enemy.  
in case he doesn't get to find that point, the function it return 2.  
  
NPC's can also walk in group, add in your npcdesc.cfg the following:  
  
groupby template  
or  
groupby graphic  
  
NPC will group with other NPC's of same graph or of same NPC template, in case the " groupby " doesn't exist in your npcdesc, the npc won't group.  
  
Obs. My shit English is thanks to it Power Trnalator Pro, hauahu

Hugo P. L.
hugo_pl@bol.com.br