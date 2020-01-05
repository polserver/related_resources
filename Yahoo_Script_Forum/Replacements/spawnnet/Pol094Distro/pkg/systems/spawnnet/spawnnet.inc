///////////////////////////////////////////
//
//   SpawnNet Include v0.95b (2000/10/22)
//
//     based on SpawnNet v0.95b
//       Author: Louds
//       eMail : louds.geo@yahoo.com
//
//     Author: Shinigami
//     eMail : Shinigami@gmx.net
//
//   Modifications:
//     2000/10/19 Shinigami: ReWrite
//
///////////////////////////////////////////

//////////////
// Constants
//////////////

Const CLEAR_RANGE:=100;

//////////////////////////////////////////////////////////
// SpawnNet_Clear - Entferne das Object aus dem SpawnNet
//////////////////////////////////////////////////////////

Function SpawnNet_Clear(obj)
  Local result:=0;

  If (GetObjProperty(obj, "spawnnet"))
    AddDeath(CInt(GetObjProperty(obj, "spawnnet")));
    EraseObjProperty(obj, "spawnnet");

    result:=1;
  EndIf

  Return (result);
EndFunction

////////////////////////////////////////////////////////
// AddCreated - SpawnRune im naechsten Zyklus erzeugen
////////////////////////////////////////////////////////

Function AddCreated(rune)
  Local result:=0;

  Local oldcrit:=Set_Critical(1);

  Local pool:=GetGlobalProperty("createpool");
  If (!pool)
    pool:={ };
  EndIf

  If (!(rune in pool))
    pool.append(rune);
    SetGlobalProperty("createpool", pool);
    result:=1;
  EndIf

  Set_Critical(oldcrit);

  Return (result);
EndFunction

/////////////////////////////////////////////////////////
// AddCreated - SpawnRune im naechsten Zyklus refreshen
/////////////////////////////////////////////////////////

Function AddRefresh(rune)
  Local oldcrit:=Set_Critical(1);

  Local pool:=GetGlobalProperty("refreshpool");
  If (!pool)
    pool:={ };
  EndIf

  If (!(rune in pool))
    pool.append(rune);
    SetGlobalProperty("refreshpool", pool);
  EndIf

  Set_Critical(oldcrit);

  Return (1);
EndFunction

////////////////////////////////////////////////////
// AddCreated - SpawnRune aus dem Zyklus entfernen
////////////////////////////////////////////////////

Function AddDeleted(rune)
  Local oldcrit:=Set_Critical(1);

  Local pool:=GetGlobalProperty("deletedpool");
  If (!pool)
    pool:={ };
  EndIf

  pool.append(rune);
  SetGlobalProperty("deletedpool", pool);

  Set_Critical(oldcrit);

  Return (1);
EndFunction

////////////////////////////////////////////////////
// AddDeath - Entferne das Object aus dem SpawnNet
////////////////////////////////////////////////////

Function AddDeath(rune)
  Local oldcrit:=Set_Critical(1);

  Local pool:=GetGlobalProperty("deathpool");
  If (!pool)
    pool:={ };
  EndIf

  pool.append(rune);
  SetGlobalProperty("deathpool", pool);

  Set_Critical(oldcrit);

  Return (1);
EndFunction

//////////////////////////////////////////////////////
// ResetSpawn - Resettet oder Loescht eine SpawnRune
//////////////////////////////////////////////////////
//
// 0 - Nur Resetten
// 1 - Rune komplett loeschen

Function ResetSpawn(runeobj, flag)
  Local spawnnet:=CInt(GetObjProperty(runeobj, "spawnnet"));
  If (!spawnnet)
    Return (0);
  EndIf

  If (flag=1)
    AddDeleted(spawnnet);
  EndIf

  // Flags der Rune ermitteln
  /////////////////////////////

  Local runeflags:=CInt(GetObjProperty(runeobj, "flags"));
  If (runeflags<0x1000) // Scheint 'n Hex aus 4 Stellen zu sein
    runeflags:=0x1000;
  EndIf
  runeflags:=CStr(Hex(runeflags));

  Local type:=CInt("0x"+runeflags[3,1]);
  Local flags:=GetFlags(CInt("0x"+runeflags[4,1])); // Wandelt 4 Bits in ein Array um

  Local dist:=CInt(GetObjProperty(runeobj, "range"))+CLEAR_RANGE;

  Case (type)
    1: ForEach npc in ListMobilesNearLocation(runeobj.x, runeobj.y, runeobj.z, dist)
         If (CInt(GetObjProperty(npc, "spawnnet"))=spawnnet)
           If (flag=1)
             EraseObjProperty(npc, "spawnnet");
           EndIf

           RevokePrivilege(npc, "invul");
           SetObjProperty(npc, "guardkill", 1);
           ApplyRawDamage(npc, GetMaxHP(npc)+3);
         EndIf
       EndForEach

    2: Local list;
       If (flags[2]=1) // Ist Bit 1 gesetzt? -> InContainerSpawn
         Local cnt:=runeobj.container;
         While ((cnt.container).serial)
           cnt:=cnt.container;
         EndWhile

         If (!cnt)
           SysLog("SpawnNet: Die Rune ("+runeobj.x+", "+runeobj.y+") befindet sich nicht in einem Container!");
           Return (0);
         EndIf

         If (CInt(GetObjProperty(cnt, "spawnnet"))=spawnnet)
           EraseObjProperty(cnt, "spawnnet");
         EndIf

         list:=EnumerateItemsInContainer(cnt);
       Else
         list:=ListObjectsInBox(runeobj.x-dist, runeobj.y-dist, -127, runeobj.x+dist, runeobj.y+dist, 127);
       EndIf

       ForEach item in list
         If (item.amount)
           If ((CInt(GetObjProperty(item, "spawnnet"))=SpawnNet) And (item.objtype<>0xa300))
             DestroyItem(item);
           EndIf
         EndIf
       EndForEach

    3: Local cnt:=CInt(GetObjProperty(runeobj, "aux"));
       If (cnt)
         cnt:=SystemFindObjectBySerial(cnt);
         If (cnt)
           DestroyItem(cnt);
         EndIf
       EndIf
  EndCase
EndFunction

//////////////////////////////////////////////
// GetFlags - Wandelt 4 Bits in ein Array um
//////////////////////////////////////////////

Function GetFlags(x)
  Local result:={0, 0, 0, 0};

  x:=CInt(x);
  If (x>7)
    x:=x-8;
    Result[4]:=1;
  EndIf
  If (x>3)
    x:=x-4;
    Result[3]:=1;
  EndIf
  If (x>1)
    x:=x-2;
    Result[2]:=1;
  EndIf
  If (x>0)
    x:=x-1;
    Result[1]:=1;
  EndIf

  Return (result);
EndFunction

///////////////////////////////////////
// Exp2 - Potenzieren mit der Basis 2
///////////////////////////////////////

Function Exp2(power)
  Local result:=1;

  Local i;
  For (i:=1; i<=power; i:=i+1)
    result:=result*2;
  EndFor

  Return (result);
EndFunction
