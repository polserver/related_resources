function OpenCharWindow( who, i )
  var me := acc.GetCharacter(i);
  var j := 0;
  while( 1 )
    if( me.ip )
        j := 1;
    endif
    GFInitGump( 20, 20 );
    GFResizePic( 0, 0, BKGND_DARK_STONE, 400, 500 );
    GFTextLine( 20, 15, 50, acc.name + " / " + me.name );
    var bu1 := GFButtonID( 370, 20, 0x19, 0x1a, 1 );
/////////////////////////////////////////////////
    GFTextLine( 40, 50, COLOR_BLUE, CHAR_STR + GetBaseStrength( me ) + " (+" + GetStrengthMod( me ) + ")" );
    var bu2 := GFButtonID( 20, 55, 0x4ba, 0x4b9, 1 );
    GFTextLine( 40, 70, COLOR_BLUE, CHAR_DEX + GetBaseDexterity( me ) + " (+" + GetDexterityMod( me ) + ")" );
    var bu3 := GFButtonID( 20, 75, 0x4ba, 0x4b9, 1 );
    GFTextLine( 40, 90, COLOR_BLUE, CHAR_INT + GetBaseIntelligence( me ) + " (+" + GetIntelligenceMod( me ) +")" );
    var bu4 := GFButtonID( 20, 95, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
    GFTextLine( 40, 180, COLOR_BLUE, EDIT_SKILLS );
    var bu5 := GFButtonID( 20, 185, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
    GFTextLine( 40, 430, COLOR_BLUE, DEL_CHAR );
    var bu6 := GFButtonID( 20, 435, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
    GFTextLine( 40, 200, COLOR_BLUE, EDIT_CPROPS );
    var bu7 := GFButtonID( 20, 205, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
   ShowCharacterDetails( me );
/////////////////////////////////////////////////
   GFTextLine( 40, 225, COLOR_BLUE, KICK_IT );
   var bu8 := GFButtonID( 20, 230, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
   var gen;
   case( me.gender )
     0: gen := IS_HIM;
     1: gen := IS_HER;
     default: gen := IS_NEITHER;
   endcase
   GFTextLine( 40, 375, COLOR_BLUE, CHR_GENDER + gen );
   var bu9 := GFButtonID( 20, 380, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
   var levelname;
   case( me.cmdlevel )
      0: levelname := "Player";
      1: levelname := "Counselor";
      2: levelname := "Seer";
      3: levelname := "GM";
      4: levelname := "Admin";
      5: levelname := "Devel.";
      default: levelname := "-";
   endcase
   GFTextLine( 40, 400, COLOR_BLUE, CMDLEV + levelname );
   var bu10 := GFButtonID( 20, 405, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
   if( me.dead )
      GFTextLine( 40, 245, COLOR_BLUE, RES_IT );
   else
      GFTextLine( 40, 245, COLOR_BLUE, KILL_IT );
   endif
   var bu11 := GFButtonID( 20, 250, 0x4ba, 0x4b9, j );
/////////////////////////////////////////////////
   GFTextLine( 40, 270, COLOR_BLUE, OPEN_BACKPACK );
   var bu12 := GFButtonID( 20, 275, 0x4ba, 0x4b9, 1 );
   GFTextLine( 40, 290, COLOR_BLUE, OPEN_BANK );
   var bu13 := GFButtonID( 20, 295, 0x4ba, 0x4b9, 1 );
   GFTextLine( 40, 310, COLOR_BLUE, WIPE_BACKPACK );
   var bu14 := GFButtonID( 20, 315, 0x4ba, 0x4b9, 1 );
   GFTextLine( 40, 330, COLOR_BLUE, WIPE_BANK );
   var bu15 := GFButtonID( 20, 335, 0x4ba, 0x4b9, 1 );
   GFTextLine( 40, 350, COLOR_BLUE, SHOW_PPR_DOLL );
   var bu16 := GFButtonID( 20, 355, 0x4ba, 0x4b9, 1 );
/////////////////////////////////////////////////
   GFTextLine( 40, 110, COLOR_RED, HP + GetHP(me) + "/" + GetMaxHP(me) );
   var bu17 := GFButtonID( 20, 115, 0x4ba, 0x4b9, 0 );
   GFTextLine( 40, 130, COLOR_RED, ST + GetStamina(me) + "/" + GetMaxStamina(me) );
   var bu18 := GFButtonID( 20, 135, 0x4ba, 0x4b9, 0 );
   GFTextLine( 40, 150, COLOR_RED, MP + GetMana(me) + "/" + GetMaxMana(me) );
   var bu19 := GFButtonID( 20, 155, 0x4ba, 0x4b9, 0 );
/////////////////////////////////////////////////
   GFTextLine( 220, 230, COLOR_BLUE, GOTO_CHAR );
   var bu20 := GFButtonID( 200, 235, 0x4ba, 0x4b9, 1 );
   GFTextLine( 220, 250, COLOR_BLUE, SUMMON_CHAR );
   var bu21 := GFButtonID( 200, 255, 0x4ba, 0x4b9, j );
   GFTextLine( 220, 270, COLOR_BLUE, SEND_CHAR );
   var bu22 := GFButtonID( 200, 275, 0x4ba, 0x4b9, j );
/////////////////////////////////////////////////
   var bu23 := GFButtonID( 200, 300, 0x4ba, 0x4b9, j );
   if( me.ip )
     GFTextLine( 220, 295, COLOR_BLUE, WHAT_IS_HE_TRAINING );
   else
     GFTextLine( 220, 295, COLOR_BLUE, WHAT_IS_HE_TRAINING );
   endif
/////////////////////////////////////////////////
   var bu24 := GFButtonID( 200, 325, 0x4ba, 0x4b9, j );
   if( me.frozen )
      GFTextLine( 220, 320, COLOR_BLUE, UNFREEZE );
   else
      GFTextLine( 220, 320, COLOR_BLUE, FREEZE );
   endif
   var bu25 := GFButtonID( 200, 345, 0x4ba, 0x4b9, j );
   if( me.squelched )
      GFTextLine( 220, 340, COLOR_BLUE, UNSQUELCH );
   else
      GFTextLine( 220, 340, COLOR_BLUE, SQUELCH );
   endif
   var bu26 := GFButtonID( 200, 365, 0x4ba, 0x4b9, j );
   if( acc.getprop("Release") )
     GFTextLine( 220, 360, COLOR_BLUE, UNJAIL );
   else
     GFTextLine( 220, 360, COLOR_BLUE, JAIL );
   endif
/////////////////////////////////////////////////
    var keys := GFSendGump( who );
    if( keys == error )
        SendSysMessage( who, "Error!" );
    	return;
    elseif( keys[0] == bu1.keyid )
        return;
    elseif( keys[0] == bu2.keyid )
        var res := cint(RequestInput( who, who.backpack, REQUEST_NEW_VALUE ));
          SetBaseStrength( me, res );
          me.maxhp := res;
          me.hp := res;
          SendSysMessage( who, CHANGED );
    elseif( keys[0] == bu3.keyid )
        var res := cint(RequestInput( who, who.backpack, REQUEST_NEW_VALUE ));
          SetBaseDexterity( me, res );
          me.maxstamina := res;
          me.stamina := res;
          SendSysMessage( who, CHANGED );
    elseif( keys[0] == bu4.keyid )
        var res := cint(RequestInput( who, who.backpack, REQUEST_NEW_VALUE ));
          SetBaseIntelligence( me, res );
          me.maxmana := res;
          me.mana := res;
          SendSysMessage( who, CHANGED );
    elseif( keys[0] == bu5.keyid )
        EditSkills( who, i );
    elseif( keys[0] == bu6.keyid )
        var res := YesNo( who, DEL_CHAR_Q );
        if( res )
           SendSysMessage( who, DELETED_CHAR + me.name );
           WipeBankBox(acc.GetCharacter(1));
	   for z:=1 to 25
	     var x := GetEquipmentByLayer(me, z);
	     MoveItemToContainer(x, me.backpack);
	   endfor
           DestroyItem(me.backpack);
           acc.DeleteCharacter(i);
           return;
        else
           SendSysMessage( who, CANCELED );
        endif
    elseif( keys[0] == bu7.keyid )
        Prop_Editor( who, i );
    elseif( keys[0] == bu8.keyid )
        DisconnectClient( me );
    elseif( keys[0] == bu9.keyid )
        ChangeSex( who, i );
    elseif( keys[0] == bu10.keyid )
        ChangeCmdLev( who, i );
    elseif( keys[0] == bu11.keyid )
        if( me.ip ) // is connected
          if( me.dead )  // then we'll do it olf fashion way
             Resurrect( me );
          else
             Damage( me, me.maxhp );
          endif
        endif
    elseif( keys[0] == bu12.keyid )
        SendOpenSpecialContainer( who, me.backpack );
    elseif( keys[0] == bu13.keyid )
        var bnkbox := FindBankBox( me );
        SendOpenSpecialContainer( who, bnkbox );
    elseif( keys[0] == bu14.keyid )
        var res := yesNo( who, ASK_IF_SURE );
        if( res )
           WipeBackPack( me );
        endif
    elseif( keys[0] == bu15.keyid )
        var res := yesNo( who, ASK_IF_SURE );
        if( res )
           WipeBankBox( me );
        endif
    elseif( keys[0] == bu16.keyid )
        OpenPaperdoll( who, me );
    elseif( keys[0] == bu17.keyid )
        EditHP( who, me );
    elseif( keys[0] == bu18.keyid )
        EditST( who, me );
    elseif( keys[0] == bu19.keyid )
        EditMP( who, me );
    elseif( keys[0] == bu20.keyid )
        GoToChar( who, me );
    elseif( keys[0] == bu21.keyid )
        if( me.ip )
           MoveCharacterToLocation( me, who.x, who.y, who.z, MOVECHAR_FORCELOCATION );
        endif
    elseif( keys[0] == bu22.keyid )
        SendCharTo( who, me );
    elseif( keys[0] == bu23.keyid )
        CoMakruje( who, me );
    elseif( keys[0] == bu24.keyid )
        if( me.frozen )
           me.frozen := 0;
        else
           me.frozen := 1;
        endif
    elseif( keys[0] == bu25.keyid )
        if( me.squelched )
            me.squelched := 0;
        else
            var duration := cint(SendTextEntryGump( who, ON_HOW_LONG ));
            me.squelch( duration );
        endif
    elseif( keys[0] == bu26.keyid )
        if( acc.getprop( "Release" ) )
           LetHimFree( me );
        else
           JailHim( who, me );
        endif
    endif
  endwhile
endfunction

//////////////////////////////////////////////////////////////////////////////////////////////////
function EditSkills( who, num )
   var me := acc.GetCharacter(num);

   GFInitGump( 30, 60 );
   GFResizePic( 0, 0, BKGND_DARK_STONE, 300, 400 );
   
   var z := 0;
   var pagecnt := 1;
   GFPage( 1 );
   GFButtonPage( 180, 350, 5540, 5541, 2 );
   GFTextLine( 60, 20, 50, CHAR_SKILLS );
   var butt;
   for i:=0 to len( GetSkillIds() )-1
       z := z + 1;
       if( z > 13 )
         z := 1;
         pagecnt := pagecnt + 1;
         GFPage( pagecnt );
         GFTextLine( 60, 20, 50, CHAR_SKILLS );
         GFButtonPage( 180, 350, 5540, 5541, (pagecnt+1) );
         GFButtonPage( 120, 350, 5537, 5538, (pagecnt-1) );
       endif
       GFTextLine( 40, ((z*20)+60), COLOR_BLUE, GetAttributeIdBySkillId( i ) );
       GFTextLine( 200, ((z*20)+60), COLOR_RED, GetBaseSkill( me, i ) );
       GFButtonID( 20, ((z*20)+65), 0x4ba, 0x4b9, 1, i+1 );
   endfor
   GFPage( (pagecnt+1) );
   GFButtonPage( 120, 350, 5537, 5538, pagecnt );
   var keys := GFSendGump( who );
   if( (keys == error) or !keys[0] )
      return;
   endif
   var inpu := cint(RequestInput( who, who.backpack, CHANGE_TO_WHAT + GetAttributeIdBySkillId( keys[0]-1 ) ));
   if( !inpu )
      SendSysMessage( who, CANCELED );
      return;
   endif
   SetBaseSkill( me, keys[0]-1, inpu );
   SendSysMessage( who, CHANGED );
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////

function ShowCharacterDetails( me )
   // paperdoll-like window here
   
   // WEIGHT
   GFTextLine( 200, 205, COLOR_RED, WEIGHT_INF + me.weight );
   // AR
   GFTextLine( 200, 180, COLOR_RED, "AR " + me.ar +" (+" + me.ar_mod + ")" );
   // ONLINE STATUS
    if( me.ip )
      GFTextLine( 130, 450, COLOR_GREEN, IS_ONLINE );
      GFTextLine( 150, 470, COLOR_BLACK, me.ip );
    else
      GFTextLine( 130, 470, COLOR_RED, IS_OFFLINE );
    endif
   // CREATED TIME
   GFTextLine( 200, 50, COLOR_RED, CREATED_AGO );
   var lstlog := cint( me.getprop( "OnCreate" ) );
   var oncreate := lstlog;
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
   GFTextLine( 200, 70, COLOR_RED, daysago + DAYS_AGO + hoursago + HOURS_AGO );
   GFTextLine( 200, 90, COLOR_RED,  minago + MIN_AGO + secago + SEC_AGO );
   
   // ONLINE TIME ( smth is screwed here )
   lstlog := cint( GetObjProperty( me, "onlinetimer" ) );
   secago := cint( ReadGameClock() - lstlog );
   minago := cint( secago  / 60 );
   hoursago := cint( minago / 60 );
   daysago := cint( hoursago / 24 );
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
   GFTextLine( 200, 115, COLOR_RED, IS_ALRDY_PLAYING );
   GFTextLine( 200, 135, COLOR_RED, daysago + DAYS_AGO + hoursago + HOURS_AGO );
   GFTextLine( 200, 155, COLOR_RED, minago + MIN_AGO + secago + SEC_AGO2 );
   
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function EditHP( who, me )
   GFInitGump( 100, 50 );
   GFResizePic( 0, 0, BKGND_DARK_STONE, 150, 200 );
   
   var keys := GFSendGump( who );
   if( keys == error )
      return;
   endif
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function EditST( who, me )
   GFInitGump( 100, 50 );
   GFResizePic( 0, 0, BKGND_DARK_STONE, 150, 200 );

   var keys := GFSendGump( who );
   if( keys == error )
      return;
   endif
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function EditMP( who, me )
   GFInitGump( 100, 50 );
   GFResizePic( 0, 0, BKGND_DARK_STONE, 150, 200 );

   var keys := GFSendGump( who );
   if( keys == error )
      return;
   endif
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function GoToChar( who, me )
   MoveCharacterToLocation( who, me.x, me.y, me.z, MOVECHAR_FORCELOCATION );
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function SendCharTo( who, me )
    var locs    := readconfigfile("::golocs");
    var MaxLocs := GetConfigMaxIntKey(locs);
    var z := 0;
    var pgnum := 1;
    var currloc := locs[1];
    SendSysMessage( who, currloc.Name );
    GFInitGump( 20, 20 );
    GFResizePic( 0, 0, BKGND_DARK_STONE, 250, 400 );
    GFPage(1);
    GFTextLine( 20, 20, 50, SEND_CHAR + " " + me.name );

    if( MaxLocs > 15 )
       GFButtonPage( 150, 370, 5540, 5541, pgnum+1 );
    endif
    for i:=1 to MaxLocs
        currloc := locs[i];
        z:=z+1;
        if( z > 15 )
           z := 1;
           pgnum := pgnum + 1;
           GFPage(pgnum);
           GFTextLine( 20, 20, 50, SEND_CHAR + " " + me.name );
           GFButtonPage( 50, 370, 5537, 5538, pgnum-1 );
           GFButtonPage( 150, 370, 5540, 5541, pgnum+1 );
        endif
        GFTextLine( 40, (z*20)+35, COLOR_BLUE, currloc.Name );
        GFButtonID( 20, (z*20)+40, 0x4ba, 0x4b9, 1, i );
    endfor
    GFPage( pgnum+1 );
    GFButtonPage( 50, 370, 5537, 5538, pgnum );
    
    var keys := GFSendGump( who );
    if( keys == error ) return; endif
    currloc := locs[ keys[0] ];
    MoveCharacterToLocation( me, currloc.x, currloc.y,  GetMapInfo(currloc.x, currloc.y).z, MOVECHAR_FORCELOCATION );
    
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function WipeBackPack( me )
   foreach item in EnumerateItemsInContainer( me.backpack )
       DestroyItem( item );
       sleep(1);  // to avoid the run-away script error
   endforeach
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
function LetHimFree( me )
  acc.setprop( "Release", 0 );
  MoveCharacterToLocation( me, 790, 3976, 0, MOVECHAR_FORCELOCATION );

endfunction

//////////////////////////////////////////////////////////////////////////////////////////////////
function JailHim( who, me )
    var val := cint( SendTextEntryGump( who, ON_HOW_LONG ) );
    var time := 0;
    case( val )
       1: time := 86400;
       2: time := 172800;
       3: time := 259200;
       4: time := 345600;
       5: time := 432000;
       6: time := 518400;
       7: time := 604800;
       8: time := 691200;
       9: time := 777600;
      10: time := 864000;
      11: time := 950400;
      12: time := 1036800;
      13: time := 1123200;
      14: time := 1209600;
    endcase
    if( (time==0) or (time>1209600) )
      SendSysMessage( who, CANCELED );
      return;
    endif
    acc.setprop( "Release", (ReadGameClock() + time) );
    var ran := RandomInt( 13 );
    case( ran )  // diffrent cells
        0:
        1:  MoveCharacterToLocation( me, 5876, 3, 0, MOVECHAR_FORCELOCATION );
        2:  MoveCharacterToLocation( me, 5871, 3, 0, MOVECHAR_FORCELOCATION );
        3:  MoveCharacterToLocation( me, 5866, 3, 0, MOVECHAR_FORCELOCATION );
        4:  MoveCharacterToLocation( me, 5861, 3, 0, MOVECHAR_FORCELOCATION );
        5:  MoveCharacterToLocation( me, 5856, 3, 0, MOVECHAR_FORCELOCATION );
        6:  MoveCharacterToLocation( me, 5852, 3, 0, MOVECHAR_FORCELOCATION );
        7:  MoveCharacterToLocation( me, 5876, 9, 0, MOVECHAR_FORCELOCATION );
        8:  MoveCharacterToLocation( me, 5871, 9, 0, MOVECHAR_FORCELOCATION );
        9:  MoveCharacterToLocation( me, 5866, 9, 0, MOVECHAR_FORCELOCATION );
        10:  MoveCharacterToLocation( me, 5861, 9, 0, MOVECHAR_FORCELOCATION );
        11:  MoveCharacterToLocation( me, 5856, 9, 0, MOVECHAR_FORCELOCATION );
        12:  MoveCharacterToLocation( me, 5852, 9, 0, MOVECHAR_FORCELOCATION );
    endcase
endfunction
//////////////////////////////////////////////////////////////////////////////////////////////////
