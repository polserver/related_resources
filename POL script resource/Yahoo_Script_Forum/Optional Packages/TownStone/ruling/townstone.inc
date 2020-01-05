const MAX_TOWN_NAME_SIZE := 30;
const MAX_LINE_LEN := 42;
const MAX_GM_TITLE_SIZE := 30;
const MAX_TOWN_ABREV_SIZE := 4;
const TOWN_MENU_SIZE := 10;
const MAX_TOWN_RECRUIT_QUEUE := 20;
const MAX_TOWN_TITLE_SIZE := 20;
const UOBJ_TOWNSTONE := 0x390; //don't know :-(
const UOBJ_TOWNSTONE_GRAPHIC := 0x0ED4;
const UOBJ_PACKED_TOIDSTONE_GRAPHIC := 0xE73; //nether

/*
TOWN_list
[1]town_serial
[2]town_name //
[3]town_abrev //these are for fast-find 


town'townserial'
[1] town_master
[2] name
[3] abrev
[4] type
[5] charter
[6] member_list
[7] war_list
[8] aliance_list
[9] recruit_list

[1][1] gm_serial
[1][2] gm_name
[1][3] gm_title

[6][i][1] member_serial
[6][i][2] member_name
[6][i][3] member_title
[6][i][4] member_fealty_id

[7][i][1] enemy_serial
[7][i][2] us_declared
[7][i][3] they_declared
[7][i][4] status

[8][i][1] alied_serial
[8][i][2] us_asked
[8][i][3] they_asked
[8][i][4] status

[9][i][1] recruit_serial
[9][i][2] recruit_name

*/


global town_list := {};
global town_struct := {};
global player_struct := {};
global player_id;
global town_id;


function Loadtowns()
town_list := GetGlobalProperty("town_list");
if(!town_list)
	town_list := {};
endif

//town_list.append({"oo","oo","oo"});
endfunction

function SavetownList()
return SetGlobalProperty("town_list", town_list);
endfunction

function LoadtownByID(id)
return GetGlobalProperty("town"+town_list[id][1]);
endfunction


function LoadtownBySerial(serial)
return GetGlobalProperty("town"+serial);
endfunction

function Savetown()
SetGlobalProperty("town"+item.serial,town_struct);
endfunction

function LoadDefaulttown()
town_struct :=GetGlobalProperty("town"+item.serial);
if(!town_struct)
	town_struct := {};
endif
endfunction

function LoadDefaultPlayer()
player_struct := town_struct[6][player_id];
if(!player_struct)
	player_struct :={};
endif
endfunction

function FindtownID(serial)
local i;
for(i:=1;i<=len(town_list[1]);i:=i+1);
	if(town_list[i][1] = serial)
		return i;
	endif
endfor
return 0;
endfunction

function FindMemberID(serial)
local i;
for(i:=1;i<=len(town_struct[6]);i:=i+1);
	if(town_struct[6][i][1] = serial)
		return i;
	endif
endfor
return 0;
endfunction


function BuildDynaGumpWithChoose(type,listype,button)
basedata := ldata;
baselayout := llayout;
if(button)
 	baselayout.append("button 400 405 5200 5201 1 0 1000");
endif

case(type)
	1: basedata[2] := "Set Fealty";
	2: basedata[2] := town_struct[2] + "  Roster";
	3: basedata[2] := town_struct[2] + "  Recruit List";
	4: basedata[2] := "Declare war";
	5: basedata[2] := "Call peace";
	6: basedata[2] := "Accept Candidate";
	7: basedata[2] := "Dismiss a member";
	8: basedata[2] := "Grant title to a member";
	9: basedata[2] := "Refuse Candidate";
	10:basedata[2] := "Cities that we have declared war";
	11:basedata[2] := "Cities that have declared war on us";
endcase



local maxpos;
case(listype)
	1:maxpos := len(town_struct[6]); //members
	2:maxpos := len(town_struct[9]); //recruits
	3:maxpos := len(town_list); //towns
	4:maxpos := len(town_struct[7]); //warlist
endcase

local i;

local poscount :=1;
local pagecount :=1;
local lastpage := maxpos/TOWN_MENU_SIZE;
if( (lastpage*TOWN_MENU_SIZE) < maxpos )
	lastpage :=  lastpage+1;
endif
local ypos;

for(i:=1;i<=maxpos;i:=i+1)
	if(poscount =1) //needs page header
		baselayout.append("page "+pagecount);
		if(pagecount >1) //needs upper button
			baselayout.append("button 490 60 5208 5210 0 "+(pagecount-1));
		endif
		if(pagecount <lastpage) //needs lower button
			baselayout.append("button 490 410 5209 5210 0 "+(pagecount+1));
		endif
		pagecount := pagecount+1;
	endif

	//time to add the text entry, the data and, if asked, the button
	//first the text
	ypos := (poscount*20) + 70;
	if(type != 5) //everything
		baselayout.append("text 165 " + ypos + " 0 " + (i+1)); //access i+1 data field
		if(button) //needs a radio button
			baselayout.append("radio 140 "+ypos+" 5002 5003 0 "+i);
		endif
		case(listype)
			1:if(len(town_struct[6][i][3]));
				basedata.append(town_struct[6][i][2] +", " + town_struct[6][i][3]);
			  else
				basedata.append(town_struct[6][i][2]);
			  endif
			2:basedata.append(town_struct[9][i][2]);
			3:if(type = 4)//war list
				if(town_struct[7][i][2]) //allready declared
					if(poscount > 1)
						poscount := poscount-1;
					endif
					basedata.append("");
				else
					basedata.append(town_list[i][2]);
				endif
			  else
				basedata.append(town_list[i][2]);
			  endif
			4:case(type)
				5: //fall intencionally, since the lists are the same
				10:if(town_struct[7][i][2]) //us declared
					basedata.append(town_list[FindtownID(town_struct[7][i][1])][2]);
				   else
					if(poscount > 1)
						poscount := poscount-1;
					endif
					basedata.append("");
				   endif
				11:if(town_struct[7][i][3]) //theys declared
					basedata.append(town_list[FindtownID(town_struct[7][i][1])][2]);
				   else
					if(poscount > 1)
						poscount := poscount-1;
					endif
					basedata.append("");
				   endif
			  endcase

		endcase
	else //peace menu
		if(town_struct[7][i][2]) //can't ask 4 peace if it's off...
			baselayout.append("text 165 " + ypos + " 0 " + (i+1)); //access i+1 data field
			if(button) //needs a radio button
				baselayout.append("radio 140 "+ypos+" 5002 5003 0 "+i);
			endif	
		else
			if(poscount > 1)
				poscount := poscount-1;
			endif
		endif
		basedata.append(town_list[FindtownID(town_struct[7][i][1])][2]);
	endif

	if(poscount >= TOWN_MENU_SIZE)
		poscount := 1;
	else
		poscount := poscount +1;
	endif
endfor


local box3 := SendDialogGump(who, baselayout, basedata);

if(box3[0] =2000) //done button
	foreach k in (box3.keys)
		if(k>0 and k<1000)
			return k;
		endif
	endforeach
endif

return 0;
endfunction



function SorttownID(id)
local i;
set_critical(1);
LoadDefaulttown();
for(i:=1;i<=len(town_struct[6]);i:=i+1)
	if(town_struct[6][i][4] > id)
		town_struct[6][i][4] := town_struct[6][i][4]-1;
	elseif(town_struct[6][i][4] =id)
		town_struct[6][i][4] :=i;
	endif
endfor
Savetown();
set_critical(0);
endfunction



function ChecktownList(str,index)
Loadtowns();

local i;
for(i:=1;i<=town_list.size();i:=i+1)
	if(lower(town_list[i][index]) = lower(str))
		return 1;
	endif
endfor
return 0;

endfunction

function NameValidation(theString)
local validstr := {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e",
		   "f","g","h","i","j","k","l","m","n","o","p","k","r","s","t","u","v","w","x","y","z"," ",};
theString := lower(theString);
local i;
for( i :=1; i<=len(theString);i:=i+1)
	if(!(theString[i] in validstr))
		return 0;
	endif
endfor
return 1;

endfunction


function GetTrueName(name)


if(name["The Murderer"])
	local ret := name[14,(len(name)-13)];
	return ret;
endif

return name;

endfunction





