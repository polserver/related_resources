std Traps Package Upgrade (POL092)
===================================
1. Replace std\traps\traps.src with the new version & compile
2. Place the new traps.cfg into std\traps\

Setting:
========
In traps.cfg set 'trapoption' as follows:-

	0 :Trap always goes Off.
	1 :If PC has correct key (ie has Cprop with same lockid as the trap)
	    if REMOVETRAP skill test is successful trap is removed
	    else Trap goes off. 
	2 :If PC has correct key then they automatically disarmed
	    else Trap goes off.
	3 :If PC has correct key then they always notice the trap but do not disarm it
	    else Trap goes off.
Note:
=====
  Not POL094 compliant (see traps.src)

Dougall (dougalloogle@yahoo.com)