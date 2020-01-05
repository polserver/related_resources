// I've modified this ripped parts of code onle when necessary to make it work

var layout3 := {
"page 0",
"nodispose",
"nomove",
"resizepic  20 20 2620 517 260", // background

"text     30  0  910 0 ",
"text    410  0  910 1 ",

"button  508 0 4011 4013 1 0 1", //modify notes button

"textentry 30 30 500 20 910 2 2",
"textentry 30 50 500 20 910 3 3",
"textentry 30 70 500 20 910 4 4",
"textentry 30 90 500 20 910 5 5",
"textentry 30 110 500 20 910 6 6",
"textentry 30 130 500 20 910 7 7",
"textentry 30 150 500 20 910 8 8",
"textentry 30 170 500 20 910 9 9",
"textentry 30 190 500 20 910 10 10",
"textentry 30 210 500 20 910 11 11",
"textentry 30 230 500 20 910 12 12",
"textentry 30 250 500 20 910 13 13"
};
var testdata := {
    NOTES_ON_ACC,
    SAVE_IT,
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};


//////////////////////////////////////////////////////////////////////////////////////////////////
function SetNotes(note)
  var split:=SplitWords(note);
  var width:=0;
  var lines:=0;
  var index:=1;
  while ((index<=len(split)) && (lines<=12))
    if (width==0)
      var testword:=split[index];
      lines:=lines+1;
      testdata[2+lines]:=testword;
      width:=GumpTextWidthFast(testword);
      index:=index+1;
    else
      var testword:=" "+split[index];
      var testwidth:=GumpTextWidthFast(testword);
      if (width+testwidth<CInt(500/1.5))
        testdata[2+lines]:=testdata[2+lines]+testword;
        width:=width+testwidth;
        index:=index+1;
      else
        width:=0;
      endif
    endif
  endwhile
  if (lines>12)
    testdata[1+lines]:=testdata[1+lines]+"...";
  else
    while(lines<12)
      lines:=lines+1;
      testdata[2+lines]:="";
    endwhile
  endif
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function ShowTheCmdLev()
  GFTextLine( 500, 65, COLOR_RED, CMDLEV );
  var levelname;
  var me;
  me := acc.GetCharacter(1);
   case( me.cmdlevel )
      0: levelname := "Player";
      1: levelname := "Counselor";
      2: levelname := "Seer";
      3: levelname := "GM";
      4: levelname := "Admin";
      5: levelname := "Devel.";
      default: levelname := "-";
   endcase
   GFTextLine( 500, 90, COLOR_BLACK, levelname );
   me := acc.GetCharacter(2);
   case( me.cmdlevel )
      0: levelname := "Player";
      1: levelname := "Counselor";
      2: levelname := "Seer";
      3: levelname := "GM";
      4: levelname := "Admin";
      5: levelname := "Devel.";
      default: levelname := "-";
   endcase
   GFTextLine( 500, 110, COLOR_BLACK, levelname );
   me := acc.GetCharacter(3);
   case( me.cmdlevel )
      0: levelname := "Player";
      1: levelname := "Counselor";
      2: levelname := "Seer";
      3: levelname := "GM";
      4: levelname := "Admin";
      5: levelname := "Devel.";
      default: levelname := "-";
   endcase
   GFTextLine( 500, 130, COLOR_BLACK, levelname );
   me := acc.GetCharacter(4);
   case( me.cmdlevel )
      0: levelname := "Player";
      1: levelname := "Counselor";
      2: levelname := "Seer";
      3: levelname := "GM";
      4: levelname := "Admin";
      5: levelname := "Devel.";
      default: levelname := "-";
   endcase
   GFTextLine( 500, 150, COLOR_BLACK, levelname );
   me := acc.GetCharacter(5);
   case( me.cmdlevel )
      0: levelname := "Player";
      1: levelname := "Counselor";
      2: levelname := "Seer";
      3: levelname := "GM";
      4: levelname := "Admin";
      5: levelname := "Devel.";
      default: levelname := "-";
   endcase
   GFTextLine( 500, 170, COLOR_BLACK, levelname );

endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function ShowWhenLastLogged()
  var lstlog := cint( acc.getprop( "LastLogin" ) );
  var secago := cint( ReadGameClock() - lstlog );
  var minago := cint( secago  / 60 );
  var hoursago := cint( minago / 60 );
  var daysago := cint( hoursago / 24 );
   if( secago >= 60 )
    if( ((secago/60) < 10) and (secago > 0) ) // to avoid the RunaAway script error
     for( secago; secago >= 60; secago:= secago -60)
     endfor
    else
     secago := 0;
    endif
   endif
    if( minago >= 60 )
     if( ((minago/60) < 10) and (minago > 0) )
      for( minago; minago >= 60; minago:= minago -60)
      endfor
     else
      minago := 0;
     endif
   endif
   if( hoursago >= 24 )
    if( ((hoursago/24) < 10) and (hoursago > 0) )
     for( hoursago; hoursago >= 24; hoursago:= hoursago -24)
     endfor
    else
     hoursago := 0;
    endif
   endif
  GFTextLine( 20, 200, COLOR_RED, LAST_LOGGED_IN + daysago + DAYS_AGO + hoursago + HOURS_AGO + minago + MIN_AGO + secago + SEC_AGO );

endfunction

//////////////////////////////////////////////////////////////////////////////////////////////////
function ChangeCmdLev(who, c)
 var char := acc.GetCharacter(c);
 var cmd_layout:={
  "page0",
  "nodispose",
  "resizepic 0 0 3600 300 360",
  "croppedtext 60 20 220 20 93 0",
  "text 60 40 66 1",
  "text 80 73 98 2",
  "text 80 113 98 3",
  "text 80 153 98 4",
  "text 80 193 98 5",
  "text 80 233 98 6",
  "text 80 273 98 7",
  "button 220 300 2122 2123 1 0 49" };

 var cmd_data:={
  char.name,
  "",
  "Player",
  "Coun",
  "Seer",
  "Gm",
  "Admin",
  "Test" };

 cmd_data[2]:="Set Command Level";
 cmd_layout.append("button 220 300 2122 2123 1 0 49");

 var i;
 for (i:=0;i<=5;i:=i+1)
   if ( (who=char) or (  who.cmdlevel>3  ) )
     cmd_layout.append("radio 40 "+(70+(i*40))+" 2152 2154 "+(char.cmdlevel=i)+" "+(50+i));
   else
     cmd_layout.append("gumppic 40 "+(70+(i*40))+" "+(2152+2*(char.cmdlevel=i)));
   endif
 endfor

 var retval:=SendDialogGump(who,cmd_layout,cmd_data);
 if (retval[49])
   var setlevel;
   for (i:=0;i<=5;i:=i+1)
     if (retval[50+i])
       setlevel:=i;
     endif
   endfor
   if ((char=who) and (setlevel<who.cmdlevel))
     sendsysmessage(who,"! Warning ! Are you sure you wish to lower your command level to "+cmd_data[setlevel+3]+" ?");
     if (!YesNo(who,"Lower CmdLevel?"))
       return;
     endif
   else
     char.cmdlevel:=setlevel;
     if (char!=who)
       sendsysmessage(who,char.name+" is now "+cmd_data[setlevel+3]);
     endif
     sendsysmessage(char,"You are now "+cmd_data[setlevel+3]);
   endif
 endif
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function ChangeSex( who, i )
 var char := acc.GetCharacter(i);
 var sex_layout:={
  "page0",
  "nodispose",
  "resizepic 0 0 "+BKGND_DARK_STONE+" 300 260",
  "croppedtext 60 20 220 20 93 0",
  "text 60 40 66 1",
  "text 80 73 98 2",
  "text 80 113 98 3",
  "text 80 153 98 4",
  "button 220 220 2122 2123 1 0 49" };

 var sex_data:={
  char.name,
  "",
  IS_HIM,
  IS_HER,
  IS_NEITHER,
 };

  sex_data[2] := CHANGE_SEX;
  sex_layout.append("button 220 220 2122 2123 1 0 49");
  sex_layout.append("radio 40 "+70+" 2152 2154 0 "+50);
  sex_layout.append("radio 40 "+110+" 2152 2154 0 "+51);
  sex_layout.append("radio 40 "+150+" 2152 2154 0 "+52);

 var retval:=SendDialogGump(who,sex_layout,sex_data);
 if( retval[50] )
       char.gender := 0;
       char.graphic := 400;
 elseif( retval[51] )
       char.gender := 1;
       char.graphic := 401;
 elseif( retval[52] )
       char.gender := 2;
 endif
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////

function DestroyAccount( who );
  var acctname := acc.name;
  var banverify := YesNo( who, ASK_IF_SURE );
  if( banverify )
     var characters := EnumerateOnlineCharacters();
       foreach char in characters
         if(char.acctname == acctname)
           SendSysMessage(char, "You were kicked by " + who.name + ".");
           SetObjProperty(char,"justbanned", 1);
           DisconnectClient(char);
           break;
         endif
       endforeach
       foreach chr in characters
         if(chr.cmdlevel > 1)
           SendSysMessage(chr, "account " + acctname + " has been destroyed.");
         endif
       endforeach
       Detach();
       sleep(10);
       acc.ban();
	   var x, i;
       WipeBankBox(acc.GetCharacter(1));
	   for(i := 1; i <= 25; i := i + 1)
	     x := GetEquipmentByLayer(acc.GetCharacter(1), i);
	     MoveItemToContainer(x, acc.GetCharacter(1).backpack);
	   endfor
       DestroyItem(acc.GetCharacter(1).backpack);
       acc.DeleteCharacter(1);
       i := 0;
       WipeBankBox(acc.GetCharacter(2));
	   for(i := 1; i <= 25; i := i + 1)
	     x := GetEquipmentByLayer(acc.GetCharacter(2), i);
	     MoveItemToContainer(x, acc.GetCharacter(2).backpack);
	   endfor
       DestroyItem(acc.GetCharacter(2).backpack);
       acc.DeleteCharacter(2);
       i := 0;
       WipeBankBox(acc.GetCharacter(3));
	   for(i := 1; i <= 25; i := i + 1)
	     x := GetEquipmentByLayer(acc.GetCharacter(3), i);
	     MoveItemToContainer(x, acc.GetCharacter(3).backpack);
	   endfor
       DestroyItem(acc.GetCharacter(3).backpack);
       acc.DeleteCharacter(3);
       i := 0;
       WipeBankBox(acc.GetCharacter(4));
	   for(i := 1; i <= 25; i := i + 1)
	     x := GetEquipmentByLayer(acc.GetCharacter(4), i);
	     MoveItemToContainer(x, acc.GetCharacter(4).backpack);
	   endfor
       DestroyItem(acc.GetCharacter(4).backpack);
       acc.DeleteCharacter(4);
       i := 0;
       WipeBankBox(acc.GetCharacter(5));
	   for(i := 1; i <= 24; i := i + 1)
	     x := GetEquipmentByLayer(acc.GetCharacter(5), i);
	     MoveItemToContainer(x, acc.GetCharacter(5).backpack);
	   endfor
       DestroyItem(acc.GetCharacter(5).backpack);
       acc.DeleteCharacter(5);
  endif
endfunction

function CoMakruje( who, chr )  // thnx J4RR3
  var makra_x:= {};
  var i:=0;
  var e:=0;
  var czas := cint(SendTextEntryGump( who, WHAT_DELAY ));

  if(!czas)
     return;
  endif

  if (CInt(czas)>440)
     SendSysMessage(who, DELAY_NOT_BIGGER_THAN + 440 );
     return;
  endif

  if (CInt(czas)<3)
     SendSysMessage(who, DELAY_NOT_SMALLER_THAN + 3);
     return;
  endif

  SendSysMessage(who, ACTIVATING);
  for (i:=0;i<=49;i:=i+1)
      makra_x[i]:= GetEffectiveSkill( chr, i);
  endfor
//  SendSysMessage(who, "Czekanie "+CInt(czas)+" sekund");
  sleep(CInt(czas));
  SendSysMessage(who, CHECKING);
  i:=0;
  GFInitGump( 100 , 0 );
  //GFGumpPic( 0 , 0 , 0x27 );
  GFResizePic( 0, 0,  BKGND_DARK_STONE , 400, 400 );
  GFTextLine( 20, 10, 50, WHAT_IS_HE_TRAINING );
  foreach makro in makra_x
      i:= i + 1;
      if (makra_x[i]<GetEffectiveSkill( chr, i))
               e:= e + 1;
               GFTextLine( 200 , (e*15)+20 , COLOR_BLUE , chr.acctname+" / "+chr.name + IS_TRAINING + i);
      endif
  endforeach
  GFSendGump( who );
endfunction

function Makrowniki( who )
   var osoby_x:= {};
   var osoby_y:= {};
   var i:=0;
   var d:=0;
   var e:=0;
   var czas := cint(SendTextEntryGump( who, WHAT_DELAY ));
   
   if(!czas)
      return;
   endif

  if (CInt(czas)>440)
     SendSysMessage(who, DELAY_NOT_BIGGER_THAN + 440 );
     return;
  endif

  if (CInt(czas)<3)
     SendSysMessage(who, DELAY_NOT_SMALLER_THAN + 3);
     return;
  endif


  SendSysMessage(who, ACTIVATING);
  foreach chr in EnumerateOnlineCharacters()
      i := i + 1 ;
      osoby_x[i]:=chr.x;
      osoby_y[i]:=chr.y;
  endforeach
  // SendSysMessage(who, "Czekanie "+CInt(czas)+" sekund");
  sleep(CInt(czas));
  SendSysMessage(who, CHECKING);
  i:=0;
  GFInitGump( 100 , 0 );
  //GFGumpPic( 0 , 0 , 0x27 );
  GFResizePic( 0, 0,  BKGND_DARK_STONE , 400, 400 );
  GFTextLine( 20, 10, 50, SEARCH_FOR_PASSIVE_TRN );
  foreach osobnik in EnumerateOnlineCharacters()
      i:= i + 1;
      if (osoby_x[i]==osobnik.x)
           if (osoby_y[i]==osobnik.y)
                if ((d*15)+20>310)
                   e:= e + 1;
                   GFTextLine( 200 , (e*15)+20 , COLOR_BLUE , osobnik.acctname+" / "+osobnik.name );
                else
                   d:= d + 1;
                   GFTextLine( 30 , (d*15)+20 , COLOR_BLUE , osobnik.acctname+" / "+osobnik.name );
                endif
           endif
      endif
  endforeach
  GFSendGump( who );
endfunction

global searchOnlineLayout := {
"page 0",
"nodispose",
"resizepic  50   0 "+BKGND_DARK_STONE+" 540 405", // background
"resizepic 210 360 5100 200  25", // buttons

"text 175 30 "+COLOR_BLUE+" 0", // title
"text  95 60 "+COLOR_BLUE+" 1", // account
"text 203 60 "+COLOR_BLUE+" 2", // name
"text 335 60 "+COLOR_BLUE+" 3", // ip
"text 465 60 "+COLOR_BLUE+" 4"  // location
};

global searchOnlineData := {
"",
"Account",
"Name",
"IP Address",
"Location",
"", // 5
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
};


function SearchForOnlinePlayers( who )

    // Variables designed to Store The full array of players, the number of players, and the current player
    local players := EnumerateOnlineCharacters();
    local numplayer := len(players);

    searchOnlinedata[1] := "Admin Control Panel - " + numplayer + " players online.";

    local player;

    // Counter.
    local i := 0, locationscount := 35, rowcount :=80, pagecount :=2, playercount :=0;

    searchOnlinelayout.append("page 1");

    // Cycle through all the players in the game and add them to the goto list.
    for (i := 1; i <= numplayer; i := i + 1)
      player := players[i];

      playercount := playercount +1;

      if (playercount>13)
      playercount :=1;
      rowcount :=80;
      // add forward button
        searchOnlinelayout.append("button 350 361 5540 5541 0 " + pagecount);
      // add backward button
	if (pagecount>2)
		searchOnlinelayout.append("button 260 361 5537 5538 0 " + (pagecount-2));
	endif
      searchOnlinelayout.append("page " + pagecount);
      pagecount := pagecount +1;
      endif

      searchOnlinelayout.append("button 75 " + (rowcount+3) + " 2117 2118 1 0 " + i);

      searchOnlinelayout.append("text 95 " + rowcount + " "+COLOR_BLUE+" " + locationscount);
      searchOnlinedata.append(player.acctname);
      locationscount := locationscount + 1;

      searchOnlinelayout.append("text 203 " + rowcount + " "+COLOR_BLUE+" " + locationscount);

      fixname(player);

      if( player.cmdlevel=0 )
        searchOnlinedata.append(searchOnlinedata[6]);
      elseif( player.cmdlevel>=4 )
        searchOnlinedata.append("+" + searchOnlinedata[6]);
      else
      	searchOnlinedata.append("*" + searchOnlinedata[6]);
      endif

      locationscount := locationscount + 1;
      searchOnlinelayout.append("text 335 " + rowcount + " "+COLOR_BLUE+" " + locationscount);
      searchOnlinedata.append(player.ip);

      locationscount := locationscount + 1;
      searchOnlinelayout.append("text 465 " + rowcount + " "+COLOR_BLUE+" " + locationscount);
      searchOnlinedata.append(player.x +","+player.y+","+player.z);

      locationscount := locationscount + 1;
      searchOnlinedata.append(player.name);
      locationscount := locationscount + 1;
      rowcount := rowcount +20;
    endfor

  if (pagecount>2)
  searchOnlinelayout.append("button 260 361 5537 5538 0 " + (pagecount-2));
  endif

  var res := SendDialogGump( who, searchOnlineLayout, searchOnlineData );
  if( res[0] == 0 ) return; endif
  
  local client, playername := (searchOnlinedata[35+ (5*res[0]) ]);
  foreach onlinechr in EnumerateOnlineCharacters()
    if (onlinechr.name = playername)
      client :=onlinechr;
      break;
    endif
  endforeach
  acc := client.acct;

endfunction

function fixname(player)

	local oldname :=player.name;
	local split := SplitWords( oldname ), i, newname :="";

	for (i := 1; i <= 2; i := i + 1)

	if (split[i])
	  newname := newname + split[i] + " ";
        endif

	endfor

	if (GetObjProperty(player,"guardtype")=2)
		searchOnlinedata[6] := "CVG " + split[1];
	elseif (GetObjProperty(player,"guardtype")=1)
		searchOnlinedata[6] := "OVG " + split[1];
	else
	searchOnlinedata[6] := newname;
	endif

endfunction

