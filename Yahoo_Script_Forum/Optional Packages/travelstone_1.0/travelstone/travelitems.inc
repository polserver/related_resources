include "include/client";

const UOBJ_GOLD_COIN := 0xeed;

// If you want to CHARGE for this, set it to however much you want
// Otherwise enter 0 for NO FEE TO TRAVEL
const travelfee := 50;

function displaymenu(who,itemstone)

GFInitGump( 0, 0 );
GFResizePic(0,0,0x2422,600,500);
GFGumpPic( 50,50,0x1598);
GFGumpPic( 0,0,0x157C);
var yew := GFButtonID( 90, 140, 0x4B9, 0x4BA, 1);
GFTextLine( 100, 140, 1975, "Yew");
var britain := GFButtonID( 160, 200, 0x4B9, 0x4BA, 1);
GFTextLine( 170, 200, 1975, "Britain");
var minoc := GFButtonID( 240, 100, 0x4B9, 0x4BA, 1);
GFTextLine( 250, 100, 1975, "Minoc");
var vesper := GFButtonID( 270, 130, 0x4B9, 0x4BA, 1);
GFTextLine( 280, 130, 1975, "Vesper");

//RIGHTSIDE - DUNGEONS
GFTextLine(430, 75, 100, "DUNGEONS");
var dung_cove := GFButtonID(435, 95, 0x4B9,0x4B9,1);
GFTextLine(450, 95, 1975, "Covetous");
var Choice := GFSendGump(who);
if(!Choice)
  SendSysMessage(who,"Cancelled!");
endif
if(Choice[0] == yew.keyid)
  var cont := GetPayment(who,travelfee);
  if(!cont)
    return;
  endif
  SendSysMessage(who,"Yew Bound!");
  CountDown(who);
  PlayStationaryEffect( who.x, who.y, who.z, FX_SMOKE, speed:=0xa, loop:=0xa );
  MoveCharacterToLocation(who, 547, 993, 0);
  PlayStationaryEffect( 547, 993, 0, FX_SMOKE, speed:=0xa, loop:=0xa );
  PlaySoundEffect( who, SFX_SPELL_TELEPORT );
elseif(Choice[0] == britain.keyid)
  var cont := GetPayment(who,travelfee);
  if(!cont)
    return;
  endif
  SendSysMessage(who,"Britain Bound!");
  CountDown(who);
  PlayStationaryEffect( who.x, who.y, who.z, FX_SMOKE, speed:=0xa, loop:=0xa );
  MoveCharacterToLocation(who, 1429, 1697, 0);
  PlayStationaryEffect( 1429, 1697, 0, FX_SMOKE, speed:=0xa, loop:=0xa );
  PlaySoundEffect( who, SFX_SPELL_TELEPORT );
elseif(Choice[0] == minoc.keyid)
  var cont := GetPayment(who,travelfee);
  if(!cont)
    return;
  endif
  SendSysMessage(who,"Minoc Bound!");
  CountDown(who);
  PlayStationaryEffect( who.x, who.y, who.z, FX_SMOKE, speed:=0xa, loop:=0xa );
  MoveCharacterToLocation(who, 2503, 563, 0);
  PlayStationaryEffect( 2503, 563, 0, FX_SMOKE, speed:=0xa, loop:=0xa );
  PlaySoundEffect( who, SFX_SPELL_TELEPORT );
elseif(Choice[0] == vesper.keyid)
  var cont := GetPayment(who,travelfee);
  if(!cont)
    return;
  endif
  SendSysMessage(who,"Vesper Bound!");
  CountDown(who);
  PlayStationaryEffect( who.x, who.y, who.z, FX_SMOKE, speed:=0xa, loop:=0xa );
  MoveCharacterToLocation(who, 2895, 687, 0);
  PlayStationaryEffect( 2895, 687, 0, FX_SMOKE, speed:=0xa, loop:=0xa );
  PlaySoundEffect( who, SFX_SPELL_TELEPORT );
elseif(Choice[0] == dung_cove.keyid)
  var cont := GetPayment(who,travelfee);
  if(!cont)
    return;
  endif
  SendSysMessage(who,"Covetous Dungeon Bound!");
  CountDown(who);
  PlayStationaryEffect( who.x, who.y, who.z, FX_SMOKE, speed:=0xa, loop:=0xa );
  MoveCharacterToLocation(who, 2503, 924, 0);
  PlayStationaryEffect( 2503, 924, 0, FX_SMOKE, speed:=0xa, loop:=0xa );
  PlaySoundEffect( who, SFX_SPELL_TELEPORT );
endif
endfunction

function CountDown(who)
var i := 5;
while(i > 0)
  PrintTextAbove(who,CStr(i));
  sleep(1);
i := i - 1;
endwhile
endfunction

function GetPayment(player, price)
  var backpack := EnumerateItemsInContainer(player.backpack);
  var a := 0;
  foreach item in backpack
    if ((item.objtype == 0xeed) && (item.amount >= price) )
      if(SubtractAmount(item, price))
        a := 1;
        break;
      endif
    endif
  endforeach
  if(a == 1)
    return 1;
  else
    SendSysMessage(player,"You dont have " + price + " gold coins!");
    return 0;
  endif
endfunction