use uo;
use npc;
use util;
use cfgfile;

include "include/string";
include "include/sith";

Const ONE_DAY  := 60 * 60 * 24;
Const ONE_WEEK := 60 * 60 * 24 * 7;

Const IM_NEUTRAL := 0;
Const MY_FRIEND  := 1;
Const MY_ENEMY   := 2;

///////////////////////////////////////////////////////
//Basic Usage:
///////////////////////////////////////////////////////
//When an NPC hears a speech event, run it through
//the "sHear" function, ie.
//
//  sHear( ev.source, ev.text );
///////////////////////////////////////////////////////
//If you want to know if someone is a friend or an
//enemy, then run them through this function:
//
//  var status := sGetRelations(who);
//
//Will return:
//  IM_NEUTRAL = 0
//  MY_FRIEND  = 1
//  MY_ENEMY   = 2
///////////////////////////////////////////////////////
//Want to change relations? Maybe if someone attacked
//your npc... Use this function:
//
//  sModRelations( who, byAmount );
//
//If there are no relations. Mod up = friendlier,
//Mod down = enemier. Say you specify -2, then it will
//like this player a bit less.
///////////////////////////////////////////////////////
//Instant relation changes
//
//sInstantEnemy( who, threshold := 10 )
//sInstantFriend( who, threshold := 10 )
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//Global Variables
///////////////////////////////////////////////////////
var sConversations := dictionary;
var sFriends := dictionary;
var sSpeechConfig := ReadConfigFile( ":sithspeak:" + (ReadConfigFile("::npcdesc")[me.npctemplate]).speachConfig );
if( !sSpeechConfig )
  sSpeechConfig := ReadConfigFile( ":sithspeak:default" );
endif
var sDefault := sGetElementData(FindConfigElem( sSpeechConfig, "default" ));
var sOptions := FindConfigElem( sSpeechConfig, "settings" );

sFriends["nextDegrade"] := ReadGameClock() + sOptions.degradeDelay;

///////////////////////////////////////////////////////
//Main Function
///////////////////////////////////////////////////////
function sHear( source, byref text )
  if( source.cmdlevel )
    if( lower(text)["reload config"] )
      UnloadConfigFile( ":sithspeak:" + (ReadConfigFile("::npcdesc")[me.npctemplate]).speachConfig );
      sSpeechConfig := ReadConfigFile( ":sithspeak:" + (ReadConfigFile("::npcdesc")[me.npctemplate]).speachConfig );
      if( !sSpeechConfig )
        UnloadConfigFile( ":sithspeak:default" );
        sSpeechConfig := ReadConfigFile( ":sithspeak:default" );
      endif

      sConversations := dictionary;
      sDefault := sGetElementData(FindConfigElem( sSpeechConfig, "default" ));
      sOptions := FindConfigElem( sSpeechConfig, "settings" );
    
      Say( "Config Reloaded." );
      return;
    elseif( lower(text)["no friends"] )
      sFriends := dictionary;
      sFriends["nextDegrade"] := ReadGameClock() + sOptions.degradeDelay;
      Say( "I dont have any friends now." );
      return;
    elseif( lower(text)["me friend"] )
      sInstantFriend( source );
      Say( "Hello friend." );
      return;
    elseif( lower(text)["me enemy"] )
      sInstantEnemy( source );
      Say( "Hello enemy." );
      return;
    elseif( lower(text)["my status"] )
      Say( "Your status is " + sGetFriendStatus(source) );
      return;
    endif
  endif
  
  text := " " + text + " ";
  
  if( !sOptions.caseSensitive )
    text := lower(text);
  endif
  
  if( !sFriends[source.serial] )
    sFriends[source.serial] := struct;
    sFriends[source.serial].+status := 0;
    sFriends[source.serial].+timeout := ReadGameClock() + ONE_WEEK;
  endif
  
  if( sConversations[source.serial] )
    sConversations[source.serial].timeout := ReadGameClock() + 45;
  else
    sConversations[source.serial] := struct;
    sConversations[source.serial].+source      := source;
    sConversations[source.serial].+timeout     := ReadGameClock() + 45;
    sConversations[source.serial].+element     := sDefault;
    sConversations[source.serial].+lasttag     := "";
    sConversations[source.serial].+postLastTag := "";
  endif
  
  sCleanConversations();
  
  return sHandleString( sConversations[source.serial], text );
endfunction

function sHandleString( byref sConverse, byref text )
  var x, hearingData := sConverse.element["hear"];
  
  for( x := 1; x <= len(hearingData); x := x + 1 )
    if( sCheckHearing( sConverse, hearingData[x], text ) )
      if( !sOptions.checkAll )
        return sHandleReply( sConverse, x );
      else
        sHandleReply( sConverse, x );
      endif
    endif
  endfor
  
  if( sOptions.noDefaultCheck )
    return sError("Not a recognized string in this element.");
  endif
  
  var oldElem := sConverse.element;
  sConverse.element := sDefault;
  
  hearingData := sConverse.element["hear"];
  for( x := 1; x <= len(hearingData); x := x + 1 )
    if( sCheckHearing( sConverse, hearingData[x], text ) )
      if( !sOptions.checkAll )
        return sHandleReply( sConverse, x );
      else
        sHandleReply( sConverse, x );
      endif
    endif
  endfor
  
  sConverse.element := oldElem;
  return sError("Not a recognized string or this element or default.");
endfunction

function sCheckHearing( byref conversationData, byref hearingData, byref text )
  var gotVital := 0;
  
  foreach vital in hearingData
    gotVital := 0;
    foreach semivital in vital
      sFixSpeechVars( conversationData, semivital );
      if( lower(semivital) == "[isfriend]" && sGetRelations(conversationData.source) == MY_FRIEND )
        gotVital := 1;
        break;
      elseif( lower(semivital) == "[isenemy]" && sGetRelations(conversationData.source) == MY_ENEMY )
        gotVital := 1;
        break;
      elseif( sStrPosInStr( semivital, text ) )
        conversationData.lasttag := sWordFromPos( text, sStrPosInStr(semivital,text) );
        gotVital := 1;
        break;
      endif
    endforeach
    if( !gotVital )
      return 0;
    endif
    sleepms(2);
  endforeach
  
  var startPos := sStrPosInStr( conversationData.lasttag, text );
  startPos := sStrPosInStr( " ", text, startPos );
  for( startPos := startPos; startPos <= len(text); startPos := startPos + 1 )
    if( text[startPos,1] != " " )
      conversationData.postLastTag := cStr(text[startPos,len(text)]);
      break;
    endif
  endfor
  
  return 1;
endfunction

function sWordFromPos( byref text, byref pos )
  var x, y;
  for( x := pos; x >= 1; x := x - 1 )
    if( text[x,1] == " " )
      x := x + 1;
      break;
    endif
  endfor
  for( y := pos; y <= len(text); y := y + 1 )
    if( text[y,1] == " " && y != pos )
      break;
    endif
  endfor
  return text[x,y-x];
endfunction

function sHandleReply( byref sConverse, x )
  var frenMod := sConverse.element["fren"][x];
  if( frenMod )
    sModRelations( sConverse.source, frenMod );
  endif

  var replyData := sConverse.element["resp"][x];
  var theReply := replyData[RandomInt(len(replyData))+1];
  
  if( !theReply )
    return sError("No reply? Replydata: " + replyData );;
  endif
  
  if( cStr(theReply[1,4]) == "[RE]" )
    var replyElemKey := cStr(theReply[5,len(theReply)]);
    var replyElem := FindConfigElem( sSpeechConfig, replyElemKey );
    if( sGetFriendStatus(sConverse.source) > sOptions.friend )
      if( FindConfigElem(sSpeechConfig,replyElemKey+"Friend") )
        replyElem := FindConfigElem(sSpeechConfig,replyElemKey+"Friend");
      endif
    elseif( sGetFriendStatus(sConverse.source) < sOptions.enemy )
      if( FindConfigElem(sSpeechConfig,replyElemKey+"Enemy") )
        replyElem := FindConfigElem(sSpeechConfig,replyElemKey+"Enemy");
      endif
    endif
    if( replyElem )
      var replyStrings := GetConfigStringArray( replyElem, "ReplyString" );
      if( len(replyStrings) )
        sHandleReplyString( sConverse, replyStrings[RandomInt(len(replyStrings))+1] );
        if( GetConfigString(replyElem,"goto") )
          sConverse.element := sGetElementData( FindConfigElem( sSpeechConfig, GetConfigString(replyElem,"goto") ) );
        elseif( sConverse.element["goto"][x] )
          sConverse.element := sGetElementData( FindConfigElem( sSpeechConfig, sConverse.element["goto"][x] ) );
        endif
        var overRideFren := GetConfigString(replyElem,"fren");
        if( overRideFren )
          sModRelations( sConverse.source, overRideFren );
        endif
        return 1;
      else
      	return sError("No reply strings in reply element.");
      endif
    endif
  else
    sHandleReplyString( sConverse, theReply );
    if( sConverse.element["goto"][x] )
      sConverse.element := sGetElementData( FindConfigElem( sSpeechConfig, sConverse.element["goto"][x] ) );
    endif
    return 1;
  endif
endfunction

function sHandleReplyString( byref sConverse, byref replyString )
  replyString := sSplitSpeechString( replyString, "#n" );
  foreach reply in replyString
    sFixSpeechVars( sConverse, reply );
    Say( reply );
  endforeach
endfunction

function sGetFriendStatus( who )
  return sFriends[who.serial].status;
endfunction

function sGetRelations( who );
  var friendStatus := sFriends[who.serial].status;
  if( friendStatus >= sOptions.friend )
    return MY_FRIEND;
  elseif( friendStatus <= sOptions.enemy )
    return MY_ENEMY;
  else
    return IM_NEUTRAL;
  endif
endfunction

function sModRelations( who, byAmount )
  if( !cInt(byAmount) && len(byAmount) > 1 )
    var posNeg := byAmount[1,1];
    var amtNum := byAmount[2,len(byAmount)];
    if( cInt(amtNum) )
      amtNum := cInt(amtNum);
    else
      amtNum := RandomDiceRoll(amtNum);
    endif
    if( posNeg == "-" )
      byAmount := 0 - amtNum;
    else
      byAmount := amtNum;
    endif
  else
    byAmount := cInt(byAmount);
  endif
  if( sFriends[who.serial] )
    sFriends[who.serial].status := sFriends[who.serial].status + byAmount;
    if( sFriends[who.serial].timeout < ReadGameClock() + (ONE_DAY*3) )
      sFriends[who.serial].timeout := ReadGameClock() + (ONE_DAY*3);
    endif
    return 1;
  else
    sFriends[who.serial] := struct;
    sFriends[who.serial].+status  := byAmount;
    sFriends[who.serial].+timeout := ReadGameClock() + ONE_WEEK;
    return 1;
  endif
endfunction

function sInstantEnemy( who, threshold := 10 )
  sModRelations(who,0);
  sFriends[who.serial].status := sOptions.enemy - threshold;
endfunction

function sInstantFriend( who, threshold := 10 )
  sModRelations(who,0);
  sFriends[who.serial].status := sOptions.friend + threshold;
endfunction

function sFixSpeechVars( byref sConverse, byref text )
  while( text["$LPT$"] )
    text["$LPT$"] := sConverse.lasttag;
  endwhile
  sleepms(2);
  
  while( text["$PLPT$"] )
    text["$PLPT$"] := sConverse.postLastTag;
  endwhile
  sleepms(2);
  
  while( text["$CN$"] )
    text["$CN$"] := (sConverse.source).name;
  endwhile
  sleepms(2);
  
  while( text["$CFN$"] )
    text["$CFN$"] := SplitWords((sConverse.source).name)[1];
  endwhile
  sleepms(2);
  
  while( text["$MN$"] )
    text["$MN$"] := Self().name;
  endwhile
  sleepms(2);
  
  while( text["$MFN$"] )
    text["$MFN$"] := Self().name[1];
  endwhile
  sleepms(2);
  
  while( text["$A$"] )
    var articlePos := sStrPosInStr( "$A$", text );
    var preString := text[1,articlePos-1];
    var postString := AddArticle( text[articlePos+3,len(text)] );
    text := cStr( preString + postString );
  endwhile
  sleepms(2);
  
  while( text["$C$"] )
    var articlePos := sStrPosInStr( "$C$", text );
    var x;
    for( x := articlePos + 3; x <= len(text); x := x + 1 )
      if( text[x,1] != " " )
        text[x,1] := Upper(text[x,1]);
        break;
      endif
    endfor
    text[articlePos,3] := "";
  endwhile
  
  return text;
endfunction

function sGetElementData( byref cfgElem )
  if( !cfgElem )
    return sDefault;
  endif

  var elemData := dictionary;
  elemData["hear"] := GetConfigStringArray( cfgElem, "hear" );
  elemData["resp"] := GetConfigStringArray( cfgElem, "resp" );
  elemData["goto"] := GetConfigStringArray( cfgElem, "goto" );
  elemData["fren"] := GetConfigStringarray( cfgElem, "fren" );
  
  foreach keyString in (elemData["hear"])
    keyString := sSplitSpeechString( keyString, "&&" );
    foreach stringPiece in keyString
      stringPiece := sSplitSpeechString( stringPiece, "||" );
      foreach semiVital in stringPiece
        semiVital := sTrimSpaces( semiVital );
        semiVital := sCheckOuterFlags( semiVital );
      endforeach
    endforeach
    sleepms(2);
  endforeach
  
  foreach response in (elemData["resp"])
    response := sSplitSpeechString( response, "||" );
  endforeach
  
  return elemData;
endfunction

function sCheckOuterFlags( byref text )
  if( text[1,1] == "*" )
    text := cStr(text[2,len(text)]);
  else
    text := " " + text;
  endif
  if( text[len(text),1] == "*" )
    text := cStr(text[1,len(text)-1]);
  else
    text := text + " ";
  endif
  return text;
endfunction

function sTrimSpaces( byref text )
  while( text[1,1] == " " )
    text := cStr(text[2,len(text)]);
  endwhile
  while( text[len(text),1] == " " )
    text := cStr(text[1,len(text)-1]);
  endwhile
  return text;
endfunction

function sSplitSpeechString( byref text, splitter := "#n" )
  var sLen := len(splitter);
  var newText := {};
  var x, y := 1;
  
  for( x := 1; x <= len(text); x := x + 1 )
    if( text[x,sLen] == splitter )
      newText.append( cStr(text[y,x-y]) );
      y := x + sLen;
      x := x + sLen;
    endif
  endfor
  
  if( x - y > 0 )
    newText.append( cStr(text[y,x]) );
  endif
  
  foreach nText in newText
    sTrimSpaces(nText);
  endforeach
  
  return newText;
endfunction

function sStrPosInStr( byref strToFind, byref strToSearch, startPos := 1 )
  var x, strLen := len(strToFind);
  
  for( x := startPos; x <= len(strToSearch); x := x + 1 )
    if( strToSearch[x,strLen] == strToFind )
      return x;
    endif
  endfor
  
  return error;
endfunction

function sCleanConversations()
  var nConversations := dictionary;
  foreach sConverse in (sConversations.Keys())
    if( sConversations[sConverse].timeout > ReadGameClock() )
      nConversations[sConverse] := sConversations[sConverse];
    endif
  endforeach
  sConversations := nConversations;
  
  var nFriends := dictionary;
  foreach sFriend in (sFriends.Keys())
    if( sFriends[sFriend].timeout )
      if( sFriends[sFriend].timeout > ReadGameClock() )
        nFriends[sFriend] := sFriends[sFriend];
      endif
    endif
  endforeach
  sFriends := nFriends;
  
  if( sFriends["nextDegrade"] <= ReadGameClock() )
    var multiplier := (ReadGameClock()-(sFriends["nextDegrade"]-sOptions.degradeDelay)) / sOptions.degradeDelay;
    if( multiplier < 1 )
      multiplier := 1;
    endif
    foreach sFriend in (sFriends.Keys())
      if( sFriends[sFriend].status < sOptions.enemy )
        sFriends[sFriend].status := sFriends[sFriend].status + ( sOptions.enemyDegrade * multiplier );
        if( sFriends[sFriend].status > sOptions.enemy )
          sFriends[sFriend].status := sOptions.enemy;
        endif
      elseif( sFriends[sFriend].status > sOptions.friend )
        sFriends[sFriend].status := sFriends[sFriend].status - ( sOptions.friendDegrade * multiplier );
        if( sFriends[sFriend].status < sOptions.friend )
          sFriends[sFriend].status := sOptions.friend;
        endif
      endif
    endforeach
    sFriends["nextDegrade"] := ReadGameClock() + sOptions.degradeDelay;
  endif  
endfunction