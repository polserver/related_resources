include "include/vetement";
global me := self();

var npccfg := readconfigfile("npcdesc");
var speechgroup := npccfg[me.npctemplate].speech;
var flee_point := npccfg[me.npctemplate].flee_point;
if (!flee_point)
        flee_point := 10;
endif

if (!me.backpack)
	local newbackpack := CreateItemAtLocation(5288,1176,0, 0xe75,1);
    EquipItem(me, newbackpack);
	if (npccfg[me.npctemplate].colorrange)
		var parms := splitwords(npccfg[me.npctemplate].colorrange);
		me.color := randomint(cint(parms[2]) - cint(parms[1]))+cint(parms[1]);
	endif
	if (npccfg[me.npctemplate].dress)
		var parms := {};
		parms[1]:= me;
		parms[2]:= npccfg[me.npctemplate].dress;
		start_script("::/misc/dressme", parms);
	elseif (npccfg[me.npctemplate].equip)
    		set_priority(50);
       		Habille( me , npccfg[me.npctemplate].equip );
       		set_priority(1);
	endif

	if( me.name["<random>"] )
		if ((me.graphic = 400) or (me.graphic = 401))
			me.graphic := 400 + RandomInt(2);
		endif
		if (npccfg[me.npctemplate].title)
			local title := randomint(20);
			local ttitle := "";
			case (title) 
        	  	0: ttitle := "";
          		1: ttitle := " o cidadao";
	          	2: ttitle := " o fazendeiro";
        	  	3: ttitle := " o marinheiro";
	          	4: ttitle := " o bebado";
	          	5: ttitle := " o andarilho";
	          	6: ttitle := " o campones";
	          	7: ttitle := " o cigano";
	          	8: ttitle := " o vagabundo";
	          	9: ttitle := " o peao";
        		default: ttitle := "";
			endcase
			local tname := randomname(me);
			setname(me, tname + ttitle);
		else
			SetName ( me , RandomName( me ) );
		endif
	endif

	if ( npccfg[me.npctemplate].mount )
		local mymount := CreateItemAtLocation(5288,1176,0,0xF021,1);
		local mountparms := splitwords(npccfg[me.npctemplate].mount);
		mymount.graphic := cint(mountparms[1]);
		mymount.color := cint(mountparms[2]);
        mymount.truecolor := mymount.color;
		EquipItem(me, mymount);
	endif

    if (me.npctemplate = "zulu")
        DressZulu();
    endif
endif
me.truecolor := me.color;


function DressZulu();
    local gender := me.gender;
    var item;
    CreateAndEquip(me, 0x1C08, 0);
    case (RandomInt(2))         // cabelos
        0: item := 0x2044;
        1: item := 0x204A;
    endcase
    CreateAndEquip(me, item, 0x464);
    if ((RandomInt(10)=1)and(gender))   // Mascaras
        case (RandomInt(2))         // cabelos
            0: item := 0x1549;
            1: item := 0x154B;
        endcase
        CreateAndEquip(me, item, 0);
    endif

    if (RandomInt(5)=1)
        // arqueiro
        CreateAndEquip(me, 0x13B2, 0); // Arco
        CreateItemInBackPack(me, 0xF3F, 30);  // Flechas
        me.script := "archerkillpcs";
        RestartScript(me);
    else
        CreateAndEquip(me, 0xF63, 0);  // Lança
    endif

    local montaria;
    case (RandomInt(20))
	    0: montaria := 0x3ea2;
    	1: montaria := 0x3e9f;
	    2: montaria := 0x3ea0;
    	3: montaria := 0x3ea1;
	    4: montaria := 0x3ea6;
        default: montaria := 0;
    endcase
    if (montaria)
        local animal := CreateItemAtLocation(me.x, me.y, me.z, 0xF021, 1);
        animal.graphic := montaria;
        EquipItem(me, animal);
    endif
endfunction

function CreateAndEquip(me,item,color)
	if (item)
		local theitem := CreateItemAtLocation(me.x,me.y,me.z,item,1);
		if (theitem)
			if (EquipItem(me,theitem))
				theitem.color := color;
			else
				DestroyItem(theitem);
			endif
		endif
	endif
endfunction
