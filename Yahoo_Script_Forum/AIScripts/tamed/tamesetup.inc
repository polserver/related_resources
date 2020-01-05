set_priority(10);

const HALT_THRESHOLD := 10;
const EVID_ALL_ATTACK_CMD := 0x12;
const EVID_ALL_FOLLOW_CMD := 0x11;
const EVID_MASTER_DEAD := 0x50;
const EVID_BODY_TOUCHED := 0x60;
const ENABLE_TRESHOLD := 20;

global master:=0;
global masterserial := GetObjProperty( me , "master");
if(masterserial)
else
	Release();
endif
masterserial := cint(masterserial);

global happyness := GetProperty("happyness");
if(!happyness) happyness := 6; endif


global friends :=  GetProperty("friends");
if(!friends)
	friends := { };
endif

global friends_name := GetProperty("friends_name");
if(!friends_name )
	friends_name  := { };
endif

global opponent :=0;
global followed :=0;
global fightqueue := {};


SetAnchor( me.x, me.y, 5, 0 );

if (getobjproperty(me, "frozen"))
	me.frozen := 1;
endif

global melem := readconfigfile("::npcdesc")[me.npctemplate];
global icfg :=ReadConfigFile("::itemdesc");
global tameskill :=cint(melem.tameskill);
global hungryrate := 370000000/ (tameskill*(tameskill+11)*(100-tameskill) );
if(!hungryrate) //it's not tamable!
	hungryrate := 3000;
endif
global nexthungry := ReadGameClock()+hungryrate;


global caster:=0;
global spells;
global count_casts;
global num_casts;
global cast_pct;
global saywords := 0;
global summons :=0;

if (melem.script = "spellkillpcs")
	caster := 1;
	spells := GetConfigStringArray( melem, "spell" );
	cast_pct := melem.cast_pct;
	num_casts  := melem.num_casts;
	count_casts  := melem.count_casts;
	if (!cast_pct)
		cast_pct := 10;
	endif
endif

if (!me.backpack)
	local newbackpack := CreateItemAtLocation(me.x, me.y, me.z, 0xe75,1);
	EquipItem(me, newbackpack);
endif


CheckMaster();
me.setmaster( master );

