set_critical(0);
global me := self();
drop_anchor();
var npccfg := readconfigfile("npcdesc");
var speechelem := npccfg[me.npctemplate];
var speech := getconfigstring(speechelem, "speech") ;
var saywords := speechelem.saywords;
var flee_point := speechelem.flee_point;
if (!flee_point)
        flee_point := 10;
endif

if (!me.backpack)
	local newbackpack := CreateItemAtLocation(me.x, me.y, me.z, 0xe75,1);
	EquipItem(me, newbackpack);
	if( me.name["<random>"] )
		me.gender := RandomInt(2);
		me.graphic := 400 + me.gender;
		local tname := randomname(me);
		me.name := tname + " the town crier";
		if (npccfg[me.npctemplate].equip)
    			EquipFromTemplate(me, npccfg[me.npctemplate].equip);
		endif
	endif
	local myhome := { };
	myhome[1] := me.x;
	myhome[2] := me.y;
	myhome[3] := me.z;
	SetObjProperty(me,"myhome",myhome);
endif
