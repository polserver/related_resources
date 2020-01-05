/////////////////////////////////////////////////////////////////////////////////
//
//   Inscription Include - Inscription Skill for all Books
//
//   Modifications:
//     1999/04/15 ENS:       Reformatted
//     2000/10/11 Fraggulus: Anpassung von ObjTypes an das Nekromantenscript
//     2002/01/20 Bihinos:   Komplettueberarbeitung und Anpassung an neue Magie
//     2002/01/20 Shinigami: ReWrite
//     2002/02/17 Shinigami: Umstellung SpellContainer -> SpellsMask
//     2002/05/07 Shinigami: Mehrfachnutzung verhindern
//     2002/05/08 Shinigami: Include umgestrickt und Tinte&Feder eingebaut
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// CheckAndUseItemsAndInscribe - Vorbereitung und Durchfuehrung der Inscription
/////////////////////////////////////////////////////////////////////////////////

Function CheckAndUseItemsAndInscribe(who, bookobjtype, bookname)
  If (!GetObjProperty(who, "#inscription")) // Mehrfachnutzung verhindern
    SetObjProperty(who, "#inscription", 1);

    SendSysMessage(who, "Was wollt Ihr benutzen?");

    Local item:=Target(who); // get item, skill is used with
    If (item)
      If (Accessible(who, item))
        If (item.objtype=UOBJ_BLANK_SCROLL) // if item is blank scroll, skill is used to inscript spell scroll
          Local book:=SearchSpellBookInBackpack(who, bookobjtype); // get Book
          If (book) // check if who has Book
            If (Accessible(who, book))
              Local penink:=Search_Object(who, 0xfc0);
              If (penink)
                Inscription(who, book, item); // call inscription routine from include
              Else
                SendSysmessage(who, "Ihr braucht Tinte und Feder in eurem Rucksack, um schreiben zu koennen!");
              EndIf
            Else
              SendSysMessage(who, "Ihr kommt da nicht ran!");
            EndIf
          Else
            SendSysMessage(who, "Ihr habt "+bookname+", aus dem Ihr abschreiben koenntet!");
          EndIf
       // ElseIf (...)    Add future uses for skill
        Else
          SendSysMessage(who, "Das koennt ihr nicht benutzen!");
        EndIf
      Else
        SendSysMessage(who, "Ihr kommt da nicht ran!");
      EndIf
    Else
      SendSysMessage(who, "Abbruch");
    EndIf

    EraseObjProperty(who, "#inscription");
  Else
    SendSysMessage(who, "Ihr beschreibt bereits Rollen!");
  EndIf
EndFunction

//////////////////////////////////////////////////////////////
// Inscription - Spruchrolle mit Spruch aus Buch beschreiben
//////////////////////////////////////////////////////////////

Function Inscription(who, book, emptyscrolls)
  Local spell_cfg:=ReadConfigFile("::spells");
  If (spell_cfg)
    Local itemdesc:=ReadConfigFile("::itemdesc");
    If (itemdesc)
      // Zu schreibende Cast-Scroll auswaehlen (ItemID)
      Local castscrollid:=ProcessMenu(who, book);
      If (castscrollid)
        // Ueber die ItemID zur SpellID
        Local castscrolldef:=itemdesc[castscrollid];
        If (castscrolldef)
          Local spellid:=castscrolldef.spellid;
          If (spellid)
            // Ueber die SpellID zum benoetigten Inscription Skill
            Local spelldef:=spell_cfg[spellid];
            If (spelldef)
              Local skill:=spelldef.skill;
              If (skill)
                Local skillid; // Den zu pruefenden Skill zuordnen
                Case (book.objtype)
                  UOBJ_SPELLBOOK_MAGE:   skillid:=SKILLID_MAGISCHEGEGENST;
                  UOBJ_SPELLBOOK_CLERIC: skillid:=SKILLID_GESEGNETEGEGENST;
                  UOBJ_SPELLBOOK_NECRO:  skillid:=SKILLID_VERFLUCHTEGEGENST;
                EndCase

                Local akt_x:=who.x; // Akt. Koordinaten sichern
                Local akt_y:=who.y;

                Local number:=CInt(SendTextEntryGump(who, "Wieviele Rollen wollt Ihr beschreiben? (Max 10)", 5));
                If ((1<=number) And (number<=10))
                  While (number And (emptyscrolls.amount)) // Noch was schreiben und noch was zum Schreiben da?
                    If ((akt_x=who.x) And (akt_y=who.y))   // Hab ich mich wegbewegt?
                      SubtractAmount(emptyscrolls, 1); // Eine Rolle verbraucht
                      number:=number-1;                // Einen Versuch "verbraucht"

                      // SkillCheck durchfuehren und bei Erfolg Cast-Scroll im Rucksack erzeugen
                      If (CheckSkillPergon(who, skillid, skill, 2*skill))
                        Local scroll:=CreateItemInBackpackPergon(who, castscrollid, 1);
                        If (scroll)
                          PlaySoundEffect(who, SFX_24A);
                          PlayObjectCenteredEffect(scroll, FX_MARK_EFFECT, 10, 10);
                          SendSysMessage(who, "Ihr beschreibt eine Rolle und legt sie in Euren Rucksack.");
                        Else
                          SendSysMessage(who, "Euer Rucksack ist voll!");
                        EndIf

                        Sleep(6); // Etwas warten
                      Else
                        PlaySoundEffect(who, SFX_50);
                        SendSysMessage(who, "Ihr verschreibt Euch und muesst daraufhin die Rolle wegwerfen.");

                        Sleep(4); // Etwas warten
                      EndIf
                    Else
                      SendSysMessage(who, "Ihr verliert Eure Konzentration!");
                      Break;
                    EndIf
                  EndWhile
                Else
                  SendSysMessage(who, "Abbruch");
                EndIf

                Return;
              Else
                SysLog("FEHLER: Spell "+spellid+" besitzt keinen Skill-Parameter!");
              EndIf
            Else
              SysLog("FEHLER: Spell "+spellid+" konnte nicht gefunden werden!");
            EndIf
          Else
            SysLog("FEHLER: Cast-Scroll "+castscrollid+" besitzt keinen SpellID-Parameter!");
          EndIf
        Else
          SysLog("FEHLER: Cast-Scroll "+castscrollid+" konnte nicht gefunden werden!");
        EndIf
      EndIf
    Else
      SysLog("FEHLER: Konnte die ItemDesc nicht oeffnen!");
    EndIf
  Else
    SysLog("FEHLER: Spells-ConfigFile nicht gefunden!");
  EndIf

  SendSysMessage(who, "Abbruch");
EndFunction

////////////////////////////////////////////////////
// ProcessMenu - Zu schreibenden Spruch auswaehlen
////////////////////////////////////////////////////

Function ProcessMenu(who, spellbook)
  // Konstanten gemaess Magierklasse verteilen
  Local magierklasse:=0; // Identifikator der globalen Variablen
  Local min_spell_item;  // Minimale ItemID der Spezial-Spells
  Local symbol_circle;   // Positionsangabe der Circle-Symbol-Items
  Local symbol_spell;    // Positionsangabe des Spell-Symbol-Items
  Case (spellbook.objtype)
    UOBJ_SPELLBOOK_MAGE:   magierklasse:=MAGE_DESC;
                           min_spell_item:=MIN_MAGE_SPELL_ITEM;
                           symbol_circle:=SYMBOL_MAGE_CIRCLE-1;
                           symbol_spell:=SYMBOL_MAGE_SPELL-1;
    UOBJ_SPELLBOOK_CLERIC: magierklasse:=CLERIC_DESC;
                           min_spell_item:=MIN_CLERIC_SPELL_ITEM;
                           symbol_circle:=SYMBOL_CLERIC_CIRCLE-1;
                           symbol_spell:=SYMBOL_CLERIC_SPELL-1;
    UOBJ_SPELLBOOK_NECRO:  magierklasse:=NECRO_DESC;
                           min_spell_item:=MIN_NECRO_SPELL_ITEM;
                           symbol_circle:=SYMBOL_NECRO_CIRCLE-1;
                           symbol_spell:=SYMBOL_NECRO_SPELL-1;
  EndCase

  // Auswahlmenue zusammenbauen
  If (magierklasse)
    Local spellsmask:=GetSpellsMask(spellbook, magierklasse);       // Spellmaske (Welcher Spell ist im Buch?)
    Local spellsindex:=GetGlobalProperty("SpIndex"+magierklasse);   // Spelldaten sortiert nach Circle und Spellname
    Local spellscircle:=GetGlobalProperty("SpCircle"+magierklasse); // Anfang des Circles im Index

    Local circles:={}; // Gibt es in dem Circle einen Spell?
    Local spelldata;   // Daten zum aktuellen Spell
    Local anyspell;    // Gibt es in irgendein Circle einen Spell?
    Local spellid;     // Aktueller Spell [eines Circles] (Schleifenzaehler)
    Local circle;      // Aktueller Circle (Schleifenzaehler)

    // Fuer welche Circle existieren Spells?
    For (circle:=1; circle<spellscircle.size(); circle:=circle+1)
      For (spellid:=spellscircle[circle][1]; spellid<spellscircle[circle+1][1]; spellid:=spellid+1)
        If (spellsmask[spellid]) // Ist der Spell im Buch enthalten?
          circles[circle]:=1; // Dieser Circle enthaelt einen Spell
          anyspell:=1;        // Irgendein Circle enthaelt einen Spell
        EndIf
      EndFor
    EndFor

    // Circle-Auswahlmenue erzeugen
    If (anyspell)
      Local menu:=CreateMenu("Waehlt einen Zirkel!");

      For (circle:=1; circle<spellscircle.size(); circle:=circle+1)
        If (circles[circle])
          AddMenuItem(menu, circle+symbol_circle, MakeRoman(circle)+". Zirkel");
        EndIf
      EndFor

      // Circle auswaehlen
      circle:=SelectMenuItem2(who, menu);
      If (circle)
        circle:=CInt(circle.objtype-symbol_circle);

        // Spell-Auswahlmenue erzeugen
        menu:=CreateMenu("Waehlt einen Spruch!");

        // Spells fuer einzelnen Circle einfuegen
        For (spellid:=spellscircle[circle][1]; spellid<spellscircle[circle+1][1]; spellid:=spellid+1)
          If (spellsmask[spellid]) // Ist der Spell im Buch enthalten?
            spelldata:=spellsindex[spellid]; // Daten zum Spell holen
            AddMenuItem(menu, spelldata[2]+symbol_spell, spelldata[1]);
          EndIf
        EndFor

        // Spell auswaehlen
        spellid:=SelectMenuItem2(who, menu);
        If (spellid)
          Return (CInt(spellid.objtype-symbol_spell)+min_spell_item-1);
        EndIf
      EndIf
    Else
      SendSysMessage(who, "Euer Buch ist leer!");
    EndIf
  Else
    SysLog("Spells: Dieses Script ist faelschlicherweise mit dem Item "+Lower(Hex(spellbook.objtype))+" verknuepft!");
  EndIf
EndFunction

////////////////////////////////////////////////
// MakeRoman - Roemische Zirkelnummern liefern
////////////////////////////////////////////////

Function MakeRoman(str)
  Case (str)
    1: Return("I");
    2: Return("II");
    3: Return("III");
    4: Return("IV");
    5: Return("V");
    6: Return("VI");
    7: Return("VII");
    8: Return("VIII");
  EndCase
EndFunction

////////////////////////////////////////////////////////////
// Search_Object - Searches for an Object in your Backpack
////////////////////////////////////////////////////////////

Function Search_Object(who, objtype)
  ForEach item In EnumerateItemsInContainer(who.backpack)
    If (item.objtype=objtype)
      Return (item);
    EndIf
  EndForEach
EndFunction