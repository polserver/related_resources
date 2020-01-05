

function Recruit()

local targ := Target(who, TGTOPT_CHECK_LOS+TGTOPT_NEUTRAL);
if(!targ.acctname)
	SendSysMessage(who, "You can only target players");

	return;
endif

if(GetObjProperty(targ, "town_id"))
	SendSysMessage(who, "You may only have people join if they are not under ruling already");
	return;
endif

if(len(town_struct[9]) >= MAX_TOWN_RECRUIT_QUEUE)
	SendSysMessage(who, "Too many Town members");
	return;
endif
local i;
for(i:=1;i<=len(town_struct[9]);i:=i+1)
	if(town_struct[9][i][1] = targ.serial) //recruited
		SendSysMessage(who, "That Person is already of this town");
		return;
	endif
endfor

set_critical(1);
var temp := town_struct[9];
temp.append( {targ.serial,GetTrueName(targ.name)} );
town_struct[9] := temp;
Savetown();
set_critical(0);
SendSysMessage(who, targ.name + " Is now under this ruling");
SendSysMessage(targ, "You are now under the ruling of " + town_struct[2]);
endfunction


/*This one change the fealty setting and if no ruler is set do the math*/
function SetFealty()

local member := BuildDynaGumpWithChoose(2,1,1);
if(!member)
	return;
endif

set_critical(1);
LoadDefaulttown();
LoadDefaultPlayer();
town_struct[6][player_id][4] := member;

if(town_struct[1][1] =0) //needs a new ruler
	local i,result:={};
	for(i:=1;i<=len(town_struct[6]);i:=i+1)
		if(!result[town_struct[6][i][4]])
			result[town_struct[6][i][4]] :=1;
		else
			result[town_struct[6][i][4]] := result[town_struct[6][i][4]]+1;
		endif
	endfor

	local winner:=0,votes:=0,tie:=0;
	for(i:=1;i<=result.size();i:=i+1)
		if(result[i] > votes)
			votes := result[i];
			winner :=i;
			tie :=0;
		elseif(result[i] = votes)
			tie :=1;
		endif
	endfor

	if(tie)
		town_struct[1][1] :=0;
		town_struct[1][2] := "None";
	else
		town_struct[1][1] := town_struct[6][winner][1];
		town_struct[1][2] := town_struct[6][winner][2];
		var update := GetObjProperty(item,"update");
		if(!update)
			update := {};
		endif
		update.append(town_struct[6][winner][1]);
		SetObjProperty(item,"update",update);
	endif
endif

Savetown();
set_critical(0);

endfunction


/* this adds and removes town abrev and title from ppl names */
//0: toggle
//1: refresh
//2: remove
//3: add

function Toggle_Showing(me,me_id,type)
syslog("entra no toggle");


if(!len(town_struct[3]))
	SendSysMessage(me,"No abbreviation defined");
	return;
endif

case(type)
	0:if(GetObjProperty(me,"abv")) //disabling
		if(me.name["The Murder"]) //murderer
			me.name := "The Murderer "+town_struct[6][me_id][2];
		else
			me.name := town_struct[6][me_id][2];
		endif
		EraseObjProperty(me,"abv");
	  else //enabling
		me.name:=me.name+" ["+town_struct[3]+"]";
		if(len(town_struct[6][me_id][3]))
			me.name:=me.name+", "+town_struct[6][me_id][3];
		endif
		case(town_struct[4])
			0: break;//common town
			1: //lawful
				me.name:= me.name+" [Lawful]";
			2://dreaded
				me.name:= me.name+" [Dreaded]";
		endcase
		
		SetObjProperty(me,"abv",1);
	  endif

	1:if(GetObjProperty(me,"abv"))
		if(me.name["The Murderer"]) //murderer
			me.name := "The Murderer "+town_struct[6][me_id][2];
		else
			me.name := town_struct[6][me_id][2];
		endif
		me.name:=me.name+" ["+town_struct[3]+"]";
		if(len(town_struct[6][me_id][3]))
			me.name:=me.name+", "+town_struct[6][me_id][3];
		endif
		case(town_struct[4])
			0: break;//common town
			1: //lawful
				me.name:= me.name+" [Lawful]";
			2://dreaded
				me.name:= me.name+" [Dreaded]";
		endcase
	   endif

	2:if(me.name["The Murderer"]) //murderer
			me.name := "The Murderer "+town_struct[6][me_id][2];
	  else
			me.name := town_struct[6][me_id][2];
	  endif
	  EraseObjProperty(me,"abv");

	3:if(me.name["The Murderer"]) //murderer
		me.name := "The Murderer "+town_struct[6][me_id][2];
	  else
		me.name := town_struct[6][me_id][2];
	  endif
	  me.name:=me.name+" ["+town_struct[3]+"]";
	  if(len(town_struct[6][me_id][3]))
		me.name:=me.name+", "+town_struct[6][me_id][3];
	  endif
	  case(town_struct[4])
		0: break;//common town
		1: //lawful
			me.name:= me.name+" [Lawful]";
		2://dreaded
			me.name:= me.name+" [Dreaded]";
	  endcase
	  SetObjProperty(me,"abv",1);
endcase
endfunction


/*remove a player from the Town and do all upkeep stuff needed...*/
function Resing()

local YesNoData := {
	"Do you really wish to be free?",
	"No, I am faithful.",
	"Freedom is what I shall seek",
};

local query := SendDialogGump(who,ChooseLayout,YesNoData);

case(query[0])
	0:
	1:return; //canseled or closed the menu
endcase

set_critical(1);

LoadDefaulttown();
player_id := FindMemberID(who.serial);
if(!player_id)
	SendSysMessage(who, "Shit Happening");
	set_critical(0);
	return;
endif
LoadDefaultPlayer();

Toggle_Showing(who,player_id,2);

LoadDefaultPlayer();
EraseObjProperty(who,"town_id");
if(len(town_struct[6]) =1)
	Destroytown();
	set_critical(0);
	return;
endif

if(who.serial = town_struct[1][1]) //is the ruler
	local i,result:={};
	for(i:=1;i<=len(town_struct[6]);i:=i+1)
		if(town_struct[6][i][4] = player_id) //fealty to the out ruler
			town_struct[6][i][4] := i; //back to default
		endif

		if(!result[town_struct[6][i][4]])
			result[town_struct[6][i][4]] :=1;
		else
			result[town_struct[6][i][4]] := result[town_struct[6][i][4]]+1;
		endif
	endfor

	local winner:=0,votes:=0,tie:=0;
	for(i:=1;i<=result.size();i:=i+1)
		if(result[i] > votes)
			votes := result[i];
			winner :=i;
			tie :=0;
		elseif(result[i] = votes)
			tie :=1;
		endif
	endfor

	if(tie)
		town_struct[1][1] :=0;
		town_struct[1][2] := "None";
	else
		town_struct[1][1] := town_struct[6][winner][1];
		town_struct[1][2] := town_struct[6][winner][2];
		var update := GetObjProperty(item,"update");
		if(!update)
			update := {};
		endif
		update.append(town_struct[6][winner][1]);
		SetObjProperty(item,"update",update);
	endif
	town_struct[1][3] := "Ruler";
endif

var temp := town_struct[6];
temp.erase(player_id);
town_struct[6]:= temp;
Savetown();
SorttownID(player_id);
set_critical(0);

endfunction




//////gm menu functions

/*this one is intented to change the RULER name, the hard part is the validity check*/

function SettownName()

//check timeframe
local changetime := GetObjProperty(item,"namechangetime");
if(!changetime)
	changetime := ReadGameClock()+(7*24*3600);
	SetObjProperty(item,"namechangetime",changetime);
	SendSysMessage(who, "You can only change the Ruling Stone name once a week");
	return;
endif

if(ReadGameClock() < changetime)
	SendSysMessage(who, "You can only change the Ruling Stone name once a week");
	return;
endif

//query for the new name
local tname := SendTextEntryGump(who,"What's the new Ruling Stone name",0,1,MAX_TOWN_NAME_SIZE,"Write the name");

if(!tname)
	return;
endif

//double check the len
if(len(tname) > MAX_TOWN_NAME_SIZE)
	SendSysMessage(who,"Ruling Stone name can't have more than "
			+MAX_TOWN_NAME_SIZE+" characters");
	return;
endif

//check if is unique
if(ChecktownList(tname,2)) //have clone
	SendSysMessage(who, "Please select another name");
	return;
endif

if(!NameValidation(tname))
	SendSysMessage(who, "You are using invalid characters");
	return;
endif

//set everything
set_critical(1);
Loadtowns();
LoadDefaulttown();
town_id := FindtownID(item.serial);
town_list[town_id][2] := tname;
town_struct[2] :=  tname;
SavetownList();
Savetown();
changetime := ReadGameClock() +(7*24*3600);
SetObjProperty(item,"namechangetime",changetime);
set_critical(0);
item.name := "Ruling Stone for " + tname;

endfunction


/*Change the town Abreviation*/
function SetAbrevName()

//check timeframe
local changetime := GetObjProperty(item,"abrevchangetime");
if(!changetime)
	changetime := 1;
endif

if(ReadGameClock() < changetime)
	SendSysMessage(who, "You can only change the Ruling Stone abbreviation once a week");
	return;
endif

//query for the new name
local tname := SendTextEntryGump(who,"What's the new Ruler's abbreviation",0,1,MAX_TOWN_ABREV_SIZE,"Write the abrev");
if(!tname)
	return;
endif

//double check the len
if(len(tname) > MAX_TOWN_ABREV_SIZE)
	SendSysMessage(who,"Abbreviation can't have more than "
			+MAX_TOWN_ABREV_SIZE+" caracters");
	return;
endif

//check if is unique
if(ChecktownList(tname,3)) //have clone
	SendSysMessage(who, "This abbreviation is already in use");
	return;
endif

if(!NameValidation(tname))
	SendSysMessage(who, "You are using invalid characters");
	return;
endif

//set everything
set_critical(1);
Loadtowns();
LoadDefaulttown();
town_id := FindtownID(item.serial);
town_list[town_id][3] := tname;
town_struct[3] :=  tname;
SavetownList();
Savetown();
changetime := ReadGameClock() +(7*24*3600);
SetObjProperty(item,"abrevchangetime",changetime);
set_critical(0);

local update:= {},tmp;
tmp := town_struct[6];
foreach dd in tmp
	update.append(dd[1]);
endforeach
SetObjProperty(item,"update", update);

endfunction



/*This one is intented to remove a Town member, due core lack of support the member must be  online, sort the fealties after*/
function Dismiss()
	
local dude := BuildDynaGumpWithChoose(7,1,1);
if(!dude)
	return;
endif

if(dude = player_id)//no need for look-up only the ruler can do it :-)
	SendSysMessage(who,"You cannot dismiss yourself");
	return;
endif

local kicked := SystemFindObjectBySerial(town_struct[6][dude][1]);
if(!kicked)
	SendSysMessage(who, "The dismissed member must be online\nOffline Dissmis coming soon");
	return;
endif

local YesNoData := {
	"Do you want to dismiss ",
	"No, the member stays!",//1
	"Yes, Remove thy self",//2
};

data[1] := data[1]+ town_struct[6][dude][2]+"?";
local query := SendDialogGump(who,ChooseLayout,YesNoData);

case(query[0])
	2: break; //accepted
	1: //canseled
	0: return; //canseled
endcase


if(GetObjProperty(kicked,"abv")) //have title on...
	kicked.name := town_struct[6][dude][2];
	EraseObjProperty(kicked,"abv");
endif

set_critical(1);
LoadDefaulttown();

var temp := town_struct[6];
temp.erase(dude);
town_struct[6] := temp;
Savetown();
SorttownID(dude);
set_critical(0);

endfunction


/*Handles basic warfare, there's not utility right now*/
function Declarewar()
town_id := FindtownID(item.serial);
local oposing_town := BuildDynaGumpWithChoose(4,3,1);
if(!oposing_town)
	return;
endif

if(oposing_town = town_id)
	SendSysMessage(who, "You cannot declare war against your City");
	return;
endif
local i, listpoz :=0,enemypoz :=0;
local enemy_town := {};
local opgs := town_list[oposing_town][1];
set_critical(1);

LoadDefaulttown();
enemy_town:= LoadtownBySerial(opgs);

//find if thes towns have some tread between'em
for(i:=1;i<=len(town_struct[7]);i:=i+1)
	if(town_struct[7][i][1] = opgs)
		listpoz := i;
		break;
	endif
endfor
var temp;
if(!listpoz) //new declare
	temp := town_struct[7];
	temp.append({opgs,1,0,0});
	town_struct[7] := temp;
	temp := enemy_town[7];
	temp.append({item.serial,0,1,0});
	enemy_town[7] := temp;

else //already declared by one side
	for(i:=1;i<=len(enemy_town[7]);i:=i+1)
		if(enemy_town[7][i][1] = item.serial)
			enemypoz := i;
			break;
		endif
	endfor

	if(town_struct[7][listpoz][2])
		SendSysMessage(who,"War already declared");
		return;
	endif

	if(town_struct[7][listpoz][3]) //they have declared
		town_struct[7][listpoz][4] :=1;
		enemy_town[7][enemypoz][4] :=1;
		SendSysMessage(who,"War now is declared");
	else
		SendSysMessage(who,"We shall shine in victory");
	endif

	town_struct[7][listpoz][2] :=1;
	enemy_town[7][enemypoz][3] :=1;

endif

Savetown();
SetGlobalProperty("town"+opgs,enemy_town);

set_critical(0);

endfunction


/* Intented to call peace uppon conflicts*/
function DeclarePeace()
var temp;
local oposing_town := BuildDynaGumpWithChoose(5,4,1);
if(!oposing_town)
	return;
endif

local i, listpoz :=0,enemypoz :=0;
local enemy_town:= {};
local opgs := town_list[oposing_town][1];

set_critical(1);
LoadDefaulttown();
enemy_town:= LoadtownBySerial(opgs);

//find if thes towns have some tread between'em
for(i:=1;i<=len(town_struct[7]);i:=i+1)
	if(town_struct[7][i][1] = opgs)
		listpoz := i;
		break;
	endif
endfor


if(!listpoz) //bug
	SendSysMessage(who, "Unknown City");
	set_critical(0);
	return;
endif

//find enemypoz
for(i:=1;i<=len(enemy_town[7]);i:=i+1)
	if(enemy_town[7][i][1] = item.serial)
		enemypoz := i;
		break;
	endif
endfor

if(!enemypoz)//bug check
	SendSysMessage(who,"Stone problem, canceling war");
	temp := town_struct[7];
	temp.erase(listpoz);
	town_struct[7] := temp;
	Savetown();
	set_critical(0);
	return;
endif

//do peace stuff
if(town_struct[7][listpoz][4])//war goin on
	if(!town_struct[7][listpoz][3]) //they made peace too, soo wipe list
		temp := town_struct[7];
		temp.erase(listpoz);
		town_struct[7] := temp;

		temp :=enemy_town[7];
		temp.erase(enemypoz);
		enemy_town[7] := temp;
		SendSysMessage(who,"Peace made, war off");
	else
		town_struct[7][listpoz][2] :=0;
		enemy_town[7][enemypoz][3] :=0;
	endif

else//war off soo other side have not declared, since right now current town have declared
	temp := town_struct[7];
	temp.erase(listpoz);
	town_struct[7] := temp;
	temp := enemy_town[7];
	temp.erase(enemypoz);
	enemy_town[7] := temp;
endif

Savetown();
SetGlobalProperty("town"+opgs,enemy_town);
set_critical(0);

endfunction


/*Self explanable, first checks for validity, them append stuff to town_struct*/

function  AcceptCandidate()

local num := BuildDynaGumpWithChoose(6,2,1);
if(!num)
	return;
endif
local pesent := SystemFindObjectBySerial(town_struct[9][num][1]);

if(!Pesent)
	SendSysMessage(who, "The player must be online to be accepted");
	return;
endif


set_critical(1);
LoadDefaulttown();
var temp;
if(GetObjProperty(Pesent," town_id"))
	SendSysMessage(who, "Member already with a City");
	temp :=	town_struct[9];
	temp.erase(num);
	town_struct[9] := temp;
	Savetown();
	set_critical(0);
	return;
endif

local pesent_id := len(town_struct[6])+1;
temp := town_struct[6];
temp.append({pesent.serial, GetTrueName(pesent.name),"",pesent_id});
town_struct[6] := temp;
temp :=town_struct[9];
temp.erase(num);
town_struct[9] := temp;


SetObjProperty(pesent,"town_id", item.serial);
Savetown();
set_critical(0);

endfunction


/*
this function throw out of someone from the candidate list
*/
function RefuseCandidate()

local num := BuildDynaGumpWithChoose(9,2,1);
if(!num)
	return;
endif

set_critical(1);
LoadDefaulttown();
var temp := town_struct[9];
temp.erase(num);
town_struct[9] := temp;
Savetown();
set_critical(0);

endfunction


/*GM have special title*/
function SetGMTitle()

local tname := SendTextEntryGump(who,"What's the new Rulers title name",0,1,MAX_GM_TITLE_SIZE,"Write the name");
if(!tname)
	return;
endif

if(len(tname) > MAX_GM_TITLE_SIZE)
	SendSysMessage(who, "Your title can't have more than "+MAX_GM_TITLE_SIZE+" characters");
	return;
endif
if(!NameValidation(tname))
	SendSysMessage(who, "You are using invalid characters");
	return;
endif

set_critical(1);
LoadDefaulttown();

town_struct[6][player_id][3] := tname;
town_struct[1][3] := tname;
Savetown();
LoadDefaultPlayer();
set_critical(0);
Toggle_Showing(who,player_id,1);

endfunction


/*Grant a title to another member, again both must be online*/
function GrantTitle()

local dude := BuildDynaGumpWithChoose(8,1,1);
if(!dude)
	return;
endif

if(dude = player_id) //ruler can't have title
	SendSysMessage(who, "You cannot give the leader a title");
	return;
endif

local tname := SendTextEntryGump(who,"What's the new member title?",0,1,MAX_TOWN_TITLE_SIZE,"Write the title");
if(!tname)
	return;
endif

if(!NameValidation(tname))
	SendSysMessage(who, "You are using invalid characters");
	return;
endif

set_critical(1);
LoadDefaulttown();
town_struct[6][dude][3] := tname;
Savetown();
set_critical(0);

local granted := SystemFindObjectBySerial(town_struct[6][dude][1]);
if(granted)
	Toggle_Showing(granted,dude,1);
else
	var update := GetObjProperty(item,"update");
	if(!update)
		update := {};
	endif
	update.append(town_struct[6][dude][1]);
	SetObjProperty(item,"update",update);
endif

endfunction




function Teleport()

local changetime := GetObjProperty(item,"telechangetime");
if(ReadGameClock() < changetime)
	changetime := ReadGameClock()+(7*24*3600);
	SetObjProperty(item,"telechangetime", changetime);
else
	SendSysMessage(who, "You can only teleport the stone once a week");
	return;
endif

//item.movable :=0;
//item.newbie :=1;
//MoveItemToContainer(item, who.backpack);
//item.graphic := UOBJ_PACKED_TOIDSTONE_GRAPHIC;
//item.movable :=0;
//item.usescript :="packedstone";

endfunction











