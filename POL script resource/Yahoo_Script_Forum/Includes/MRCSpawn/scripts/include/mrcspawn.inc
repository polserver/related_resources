//////////////////////////////////////////////////////////
//
//   MRCSpawn Include v1.01 (2000/10/25)
//
//     based on MRCSpawn Include
//       Author: ???
//
//     Author: Shinigami
//     eMail : Shinigami@gmx.net
//
//   Modifications:
//     2000/10/25 Shinigami: Complete ReWrite
//                           SellLists added
//     2000/12/09 Shinigami: HP/Armor w'modify Price
//     2001/01/07 Shinigami: Minor Bug fixed
//                           MultiLanguage ErrorMessages
//
//////////////////////////////////////////////////////////
//
// ToDo: use stackability to create single items or add to stacks.
//       stacks are always added to, currently.
//       calling CreateItemInContainer 'count' times would do this
//       automatically, actually
//
// this would be nice, and fast, but this doesn't handle multiple stacks.
// in particular, it doesn't handle multiple single nonstackable items.
//   Local itemref:=FindObjtypeInContainer(inventory, objtype);
//   If (itemref)
//     count:=count-itemref.amount;
//   EndIf

////////////
// Library
////////////

Use cfgfile;

/////////////
// Includes
/////////////

Include "include/errormsg";

///////////////////
// Error-Messages
///////////////////

Const ERRORMSGS_GERMAN:=
  "{}MRCSpawn: Das Item %% konnte nicht erzeugt werden!"+
  "{}MRCSpawn: Items in der Sells-Gruppe '%%' sind fehlerhaft definiert!"+
  "{}MRCSpawn: Kann keine Eintraege des MerchantTypes '%%' finden!"+
  "{}MRCSpawn: Kann die Datei 'mrcspawn.cfg' nicht oeffnen !"+
  "{}MRCSpawn: Items in der Gruppe '%%' sind fehlerhaft definiert!";
Const ERRORMSGS_ENGLISH:=
  "{}MRCSpawn: Unable to create Item %% !"+
  "{}MRCSpawn: Items in Sells-Group '%%' are definied in a wrong way!"+
  "{}MRCSpawn: Unable to find MerchantType '%%'!"+
  "{}MRCSpawn: Unable to open 'mrcspawn.cfg'!"+
  "{}MRCSpawn: Items in Group '%%' are definied in a wrong way!";

//////////////
// Constants
//////////////

Const HP_ARMOR:=1;    // 1=Analyze HP/Armor for Calculating Price

//////////////////////////////////////////////////
// RestockInventory - Restock Vendor's Inventory
//////////////////////////////////////////////////

Function RestockInventory(merchanttype, inventory)
  Local mrcspawnfile:=ReadConfigFile("mrcspawn");
  If (mrcspawnfile)
    Local productgroups:=FindConfigElem(mrcspawnfile, merchanttype);
    If (productgroups)
      Local sellitem;
      Local objtype;
      Local count;
      Local i;

      ForEach productgroup in GetConfigStringArray(productgroups, "Sells")
        ForEach itemstr in GetConfigStringArray(FindConfigElem(mrcspawnfile, productgroup), "Item")
          SleepMS(100);

          sellitem:=SplitWords(itemstr);
          objtype:=sellitem[1];
          If (CInt(objtype))
            objtype:=CInt(objtype);
          Else
            objtype:=GetObjtypeByName(objtype);
          EndIf

          If (objtype)
            count:=CInt(sellitem[2]);
            ForEach item in EnumerateItemsInContainer(inventory)
              If (item.objtype=objtype)
                count:=count-item.amount;
              EndIf
            EndForEach

            If (count>0)
              For (i:=1; i<=count; i:=i+1)
                If (!CreateItemInInventory(inventory, objtype, 1))
                  PrintErrorMessage(1, {Hex(objtype)});
                EndIf
              EndFor
            EndIf
          Else
            PrintErrorMessage(2, {productgroup});
          EndIf
        EndForEach
      EndForEach
    Else
      PrintErrorMessage(3, {merchanttype});
    EndIf

    UnloadConfigFile("mrcspawn");
  Else
    PrintErrorMessage(4);
  EndIf
EndFunction

///////////////////////////////////////////////////////////////
// ModifyPCSellList - Mark sellable Items in Players Backpack
///////////////////////////////////////////////////////////////

Function ModifyPCSellList(merchanttype, backpack)
  Local backpackitems:=EnumerateItemsInContainer(backpack);

  Local mrcspawnfile:=ReadConfigFile("mrcspawn");
  If (mrcspawnfile)
    Local productgroups:=FindConfigElem(mrcspawnfile, merchanttype);
    If (productgroups)
      Local buys:=GetConfigStringArray(productgroups, "Buys");
      Local nobuys:=GetConfigStringArray(productgroups, "NoBuys");

      Local iteminit:=0; // Buys everything
      Local itemmark;
      Local productgroups:={ };

      If (buys.size()>=1) // Buys nothing, but defined Items
        iteminit:=-1;itemmark:=0;
        productgroups:=buys;
      ElseIf (nobuys.size()>=1) // Buys everything, but not defined Items
        iteminit:=0;itemmark:=-1;
        productgroups:=nobuys;
      EndIf

      ForEach item in backpackitems
        item.buyprice:=iteminit;
      EndForEach

      Local buynobuyable:={ };
      Local objtype;

      If (productgroups.size())
        ForEach productgroup in productgroups
          ForEach itemstr in GetConfigStringArray(FindConfigElem(mrcspawnfile, productgroup), "Item")
            objtype:=itemstr;
            If (CInt(objtype))
              objtype:=CInt(objtype);
            Else
              objtype:=GetObjtypeByName(objtype);
            EndIf

            If (objtype)
              buynobuyable.append(objtype);
            Else
              PrintErrorMessage(5, {productgroup});
            EndIf
          EndForEach
        EndForEach

        If (buynobuyable.size())
          ForEach item in backpackitems
            If (item.objtype in buynobuyable)
              item.buyprice:=itemmark;
            EndIf
          EndForEach
        EndIf
      EndIf

      If (HP_ARMOR)
        Local itemdesc:=ReadConfigFile(":combat:itemdesc");
        Local iteminfo;
        ForEach item in backpackitems
          If (!item.buyprice)
            If (item.isa(POLCLASS_WEAPON))
              iteminfo:=itemdesc[item.objtype];
              item.buyprice:=CInt(iteminfo.vendorbuysfor*item.hp/iteminfo.maxhp);
            ElseIf (item.isa(POLCLASS_ARMOR))
              iteminfo:=itemdesc[item.objtype];
              item.buyprice:=CInt(iteminfo.vendorbuysfor*item.ar/iteminfo.ar);
            EndIf
          EndIf
        EndForEach
      EndIf
    Else // Buys nothing
      ForEach item in backpackitems
        item.buyprice:=-1;
      EndForEach

      PrintErrorMessage(3, {merchanttype});
    EndIf

    UnloadConfigFile("mrcspawn");
  Else // Buys nothing
    ForEach item in backpackitems
      item.buyprice:=-1;
    EndForEach

    PrintErrorMessage(4);
  EndIf
EndFunction
