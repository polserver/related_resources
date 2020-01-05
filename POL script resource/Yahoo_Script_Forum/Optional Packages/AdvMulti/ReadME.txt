14/01/2001**Fusion**Fusion___@hotmail.com ICQ 86851226
The pkg include:

- Static files multi.mul and multi.idx with new multi files.

- New house system (to unzip in ..pkg/opt/NewHousing)

- Boat pkg modified in some of its parts (it's only needed to change the itemdesc and the shipdeed.src in ..pkg/std/boat if you wouldn't  change the whole pkg)

- Multis.cfg and boats.cfg to unzip in ../config

- In some multi I have left some dynamic objects also the Hitching post, I enclose a script to activate it (to unzip in ../scripts/items/)
   Add in tamed.src:
  
  elseif (evtext[mename + " go"]  or (evtext["all go"]))
                        go();
                	return;
---------------------------------------------------------





Function Go()
local tobj := TargetCoordinates(master);   
tobj :=createitematlocation(tobj.x,tobj.y,tobj.z,0x17,1);    
tobj.graphic := 1;
    local times := 0;
    while ( (distance(me, tobj) > 1) and times < 5 and CheckLineOfSight(me,tobj) )
       if( !runtoward(tobj))
          sleep(1);
          times := times + 1;
       else
          times := 0;
       endif
    endwhile
endfunction    

In the function OpenMyPack();
	

Function OpenMyPack()
       ###########################################
       #If(getobjproperty(me,"Block"))           #
       #sendsysmessage(master,"This is blocked");#
       #return;					 #
       #endif					 #
       ###########################################

ecc ecc
Every kind of bug you find, contact me and I will try to repair it. :)

Bye thank you


Il pkg comprende :
- File statici multi.mul e multi.idx con i nuovi multi.
- Nuovo house system(da decompattare in ..pkg/opt/NewHousing)
- Boat pkg modificato in alcune sue parti(e' necessario solo sostituire l'itemdesc e lo shipdeed.src in 	
					  ..pkg/std/boat se non si vuole sostituire completamente il pkg)
- Multis.cfg e boats.cfg da decompattare in ../config
- In alcuni multi ho lasciato come oggetti dinamici anche l 'hitching post allego uno script per implementarlo :)
  (da decompattare in ../scripts/items/
 Aggiungere in tamed.src:
  
  elseif (evtext[mename + " go"]  or (evtext["all go"]))
                        go();
                	return;
---------------------------------------------------------





Function Go()
local tobj := TargetCoordinates(master);   
tobj :=createitematlocation(tobj.x,tobj.y,tobj.z,0x17,1);    
tobj.graphic := 1;
    local times := 0;
    while ( (distance(me, tobj) > 1) and times < 5 and CheckLineOfSight(me,tobj) )
       if( !runtoward(tobj))
          sleep(1);
          times := times + 1;
       else
          times := 0;
       endif
    endwhile
endfunction    

Nella funzione OpenMyPack();
	

Function OpenMyPack()
       ###########################################
       #If(getobjproperty(me,"Block"))           #
       #sendsysmessage(master,"This is blocked");#
       #return;					 #
       #endif					 #
       ###########################################

ecc ecc

 Qualunque bug trovaste,contattatemi e io cerchero' di sistemarlo(ho testato tutto il piu' possibile ma 
 sicuramente qualcosa mi e' sfuggito) :)
Bye:)