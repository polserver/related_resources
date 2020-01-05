set_critical(0);
global speech;
global master;
global spells := {};
global me := self();

global cast_pct;
global num_casts;
global count_casts ;
global saywords := 1;
global summons := 3;

global will_cast;
global flee_point;

var npccfg := readconfigfile("npcdesc");
var speechelem := npccfg[me.npctemplate];
speech := getconfigstring(speechelem, "speech") ;
spells := GetConfigStringArray( speechelem, "spell" );
cast_pct := speechelem.cast_pct;
num_casts  := speechelem.num_casts;
count_casts  := speechelem.count_casts;
saywords := speechelem.saywords;
if (!cast_pct)
        cast_pct := 10;
endif
flee_point := speechelem.flee_point;
if (!flee_point)
        flee_point := 10;
endif

if (!me.backpack)
	local newbackpack := CreateItemAtLocation(me.x, me.y, me.z, 0xe75,1);
	EquipItem(me, newbackpack);
	if (npccfg[me.npctemplate].colorrange)
		var parms := splitwords(npccfg[me.npctemplate].colorrange);
		me.color := randomint(cint(parms[2]) - cint(parms[1]))+cint(parms[1]);
		setobjproperty(me,"color",me.color);
	endif
	if (npccfg[me.npctemplate].dress)
		var parms := {};
		parms[1]:= me;
		parms[2]:= npccfg[me.npctemplate].dress;
		start_script("::/misc/dressme", parms);
	elseif (npccfg[me.npctemplate].equip)
    		EquipFromTemplate(me, npccfg[me.npctemplate].equip);
	endif

	if( me.name["<random>"] )
		if ((me.graphic = 400) or (me.graphic = 401))
			me.gender := RandomInt(2);
			me.graphic := 400 + me.gender;
		endif
		SetName ( me , RandomName( me ) );
	endif

	if ( npccfg[me.npctemplate].mount )
		local mymount := CreateItemAtLocation(5288,1176,0,0xF021,1);
		local mountparms := splitwords(npccfg[me.npctemplate].mount);
		mymount.graphic := cint(mountparms[1]);
		mymount.color := cint(mountparms[2]);
		EquipItem(me, mymount);
	endif

endif
