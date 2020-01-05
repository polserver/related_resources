set_critical(0);
global me := self();

global flee_point;

drop_anchor();

flee_point := 10;

if (!me.backpack)
	local newbackpack := CreateItemAtLocation(me.x, me.y, me.z, 0xe75,1);
	EquipItem(me, newbackpack);
	if (!randomint(100) )
		me.color := 1109;
	endif
endif
