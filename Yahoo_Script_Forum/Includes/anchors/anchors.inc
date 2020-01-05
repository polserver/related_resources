////////////////////////////////////
//
//   Anchor Wandering Include v1.0
//
//     Author: Shinigami
//     eMail : Shinigami@gmx.net
//
////////////////////////////////////
//
// Drop_Anchor - Sets the Anchor for an NPC
//   Uses: NPCDesc Template.dstart - AnchorRange  (0   - disable Anchor)
//         NPCDesc Template.psub   - BorderChance (100 - ignore Border)
//                                                (0   - accept Border)
//         NPC Object.Anchor - Array(Anchor.x, Anchor.y, dstart, psub)
//
// WanderAnchor      - don't walk through Doors
// WanderDoorsAnchor - walk through Doors

////////////////
// Drop_Anchor 
////////////////
//
// overwrite = 0 -> Will remember Anchor after ServerRestart.
//             1 -> Sets a new Anchor.

Function Drop_Anchor(overwrite:=0)
  If ((!GetObjProperty(me, "Anchor")) Or overwrite)
    Local cfg:=ReadConfigFile("npcdesc");
    If (cfg)
      Local dstart:=cfg[me.npctemplate].dstart;
      If (dstart)
        Local psub:=cfg[me.npctemplate].psub;
        If (!psub)
          psub:=100;
        EndIf

        SetObjProperty(me, "Anchor", {me.x, me.y, dstart, psub});

       // SetAnchor(me.x, me.y, dstart, psub);
      Else
        EraseObjProperty(me, "Anchor");
      EndIf
    Else
      SysLog("Anchor: Kann die Datei 'npcdesc.cfg' nicht oeffnen !");
    EndIf
  EndIf
EndFunction

////////////////////////////////////////////
// WanderAnchor - don't walk through Doors
////////////////////////////////////////////

Function WanderAnchor()
  Local me:=Self();

  ForEach item in ListItemsNearLocation(me.x, me.y, me.z, 2)
    If (item.isa(POLCLASS_DOOR))
      WalkAwayFrom(item);
      Return;
    EndIf
  EndForEach

  Local walking:=1;
  Local anchor:=GetObjProperty(me, "Anchor");
  If (anchor.size()=4)
    Local diffx:=me.x-anchor[1];
    Local diffy:=me.y-anchor[2];

    If (CInt(Sqrt(diffx*diffx+diffy*diffy))>anchor[3])
      If (RandomInt(100)<anchor[4])
        WalkTowardLocation(anchor[1], anchor[2]);
        walking:=0;
      EndIf
    EndIf
  EndIf

  If (walking)
    Case (RandomInt(8))
      0: 1: 2: 3: 4: 5: Move(me.facing);
      6:                Move(me.facing-1);
      7:                Move(me.facing+1);
    EndCase
  EndIf
EndFunction

///////////////////////////////////////////
// WanderDoorsAnchor - walk through Doors
///////////////////////////////////////////

Function WanderDoorsAnchor()
  Local me:=Self();

  Local walking:=1;
  Local anchor:=GetObjProperty(me, "Anchor");
  If (anchor.size()=4)
    Local diffx:=me.x-anchor[1];
    Local diffy:=me.y-anchor[2];

    If (CInt(Sqrt(diffx*diffx+diffy*diffy))>anchor[3])
      If (RandomInt(100)<anchor[4])
        WalkTowardLocation(anchor[1], anchor[2]);
        walking:=0;
      EndIf
    EndIf
  EndIf

  If (walking)
    Case (RandomInt(8))
      0: 1: 2: 3: 4: 5: Move(me.facing);
      6:                Move(me.facing-1);
      7:                Move(me.facing+1);
    EndCase
  EndIf
EndFunction
