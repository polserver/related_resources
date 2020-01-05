/////////////////////////////////////////////////////////////////////////
//
//   SpellBook Include v1.01 (2001/03/14)
//
//     Author: Shinigami
//     eMail : Shinigami@gmx.net
//
//   Modifications:
//     2001/03/06 Shinigami: Spellbook... Los gehts
//     2001/03/14 Shinigami: Soweit abgeschlossen
//     2001/03/15 Shinigami: Spellpanel... Los gehts
//     2001/04/01 Shinigami: Anpassung an SeBB's System
//     2001/12/09 Shinigami: Zerlegen in Include
//     2001/12/27 Shinigami: Script auskommentiert
//     2001/12/28 Shinigami: SpellPanel weiterentwickelt
//     2002/01/02 Shinigami: "Echtes" Casten aktiviert
//     2002/01/20 Shinigami: Trennung der Items rausgenommen
//     2002/02/09 Shinigami: Spells im Index werden nicht mehr sortiert
//     2002/02/10 Shinigami: Buch hat nun einen Fingerabdruck
//     2002/02/17 Shinigami: Umstellung SpellContainer -> SpellsMask
//     2002/07/23 Shinigami: SpellPanel ziemlich weit vorangetrieben
//     2002/07/30 Shinigami: SpellPanel vorerst abgeschlossen
//
/////////////////////////////////////////////////////////////////////////
//
// Zauberbuch
//   UseSpellBook              - Doppelklick auf das Spellbook
//   ShowSpellBook             - Zeigt das Spellbook an
//
// SpellPanel
//   TestDemoSpellPanel        - Erzeugt und Testet ein Panel zur Demonstration
//   ShowSpellPanels           - Zeigt alle Spellpanels an
//   ShowSpellPanel            - Zeigt ein Spellpanel an
//   ChangeSpellPanelSize      - Groesse des SpellPanels und damit der Matrix aendern
//
// Initialisierung
//   InitSpellBook             - Initialisiert das Spellbook
//   InitMagierKlasse          - Magierklasse initialisieren
//   GetWholeSpellConfig       - Ermittelt die statischen Daten aller Spells
//   CheckSpellID              - Ueberprueft die tatsaechliche SpellID
//
// Sonstiges
//   CreateSpellBookInBackpack - Erzeugt das Zauberbuch im Backpack inkl. Fingerabdruck
//   PersonalizeSpellBook      - Zauberbuch mit Fingerabdruck versehen
//   CreateSpellInBook         - Erzeugt den Spruch im Zauberbuch
//   GetSpellIDfromObjType     - Ermittelt die SpellID zum Item
//   SearchSpellBookInBackpack - Zauberbuch im Backpack suchen
//   GetSpellsMask             - Holt die SpellsMask des Buches
//   ConvertSpellsInBook       - Konvertiert die Sprueche zur Spellsmask
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Benutzte CProp's - SpellBook
//   CInt(#Open)       - Ist das Buch geoeffnet?
//   CInt(#ErrorClock) - Wann wird "#Open" nach Fehlversuch entfernt?
//   CInt(Besitzer)    - Fingerabdruck (Serial des Besitzers)
//   Array(SpellsMask) - Spellmaske (Welcher Spell ist im Buch?)
//
// Benutzte CProp's - SpellPanel
//   Array(Data) - {X-Position, Y-Position, Sichtbar?, SpellMatrix}
//                   SpellMatrix = Zeilen{ Spalten{ SpellID }}
//
/////////////////////////////////////////////////////////////////////////////
//
// Ermittelte Datenmenge (2001/03/14)
//   Layout = 1578..19879 / Data = 373..1966

// ToDo: Sounds fuer Buch oeffnen/schliessen raussuchen
//       Rotes Band (verweist auf letzten benutzten Spell)
//       Flag, welches sagt, ob das Buch offen ist (ok, gibs schon), damit das
//         Buch nach dem Wiedereinloggen automatisch angezeigt wird (minimiert...)

// Shinigami: CastSpell - Cast the Spell (this is NOT the original Pergon function)

/////////////////
// Bibliotheken
/////////////////

Use uo;
Use os;
Use cfgfile;

/////////////
// Includes
/////////////

Include "spelldefs";
Include "inscription";
Include "include/gumputil";

///////////////
// Konstanten
///////////////

Const SPELLID_KORREKTUR:=0;//400;        // (Temporaer) Korrekturwert fuer gemeinsame SpellID

Const GUMP_HIDDENBTN_LEFT:= 2184;    // 8 Buttons fuer Wechsel vom Indexeintrag zur Spellseite (links)
Const GUMP_HIDDENBTN_RIGHT:=2192;    // 8 Buttons fuer Wechsel vom Indexeintrag zur Spellseite (rechts)
Const GUMP_MAGE_SPELL:=     2240;    // Spellsymbole gemaess Magier-Klasse (klein)
Const GUMP_CLERIC_SPELL:=   2240;
Const GUMP_NECRO_SPELL:=    2240;
Const GUMP_EMPTY_EDIT:=     2152;    // Symbol fuer einen Leerplatz beim Editieren des Panels

Const DEFAULT_PANEL_X:=        30;   // Initialwerte eines neuen Panels
Const DEFAULT_PANEL_Y:=        30;
Const DEFAULT_PANEL_SPALTEN:=   6;
Const DEFAULT_PANEL_ZEILEN:=    2;
Const PANEL_GUMP_WIDTH:=       44;   // Ausmass eines Spellsymbols auf dem Panel
Const PANEL_GUMP_HEIGHT:=      44;

Const BTTN_GROSSES_BUCH:= 1;         // (Rueckgabewert) Wechsel aufs grosse Buch
Const BTTN_KLEINES_BUCH:= 2;         // (Rueckgabewert) Wechsel aufs kleine Buch
Const BTTN_EDIT:=         3;         // (Rueckgabewert) SpellPanel editieren
Const BTTN_X_POS:=        4;         // (Rueckgabewert) SpellPanel (Edit) X-Position
Const BTTN_Y_POS:=        5;         // (Rueckgabewert) SpellPanel (Edit) Y-Position
Const BTTN_ZEILEN:=       6;         // (Rueckgabewert) SpellPanel (Edit) Zeilen
Const BTTN_SPALTEN:=      7;         // (Rueckgabewert) SpellPanel (Edit) Spalten
Const BTTN_SPELLS:=      10;         // (Rueckgabewert) Spellaufruf

Const BASE_X:=117;                   // Position des Buches
Const BASE_Y:=116;

///////////////
// Gump-Daten
///////////////
//
// 2220      - Zauberbuch (gross, aufgeklappt)
// 2225-2232 - Index-Shortcuts (die Ziffern im Kreis)
// 2234      - Zauberbuch (klein)
// 2235      - Seitenwechsel zurueck
// 2236      - Seitenwechsel vor
// 2240-2303 - Spellsymbole (klein)
// 2183      - Button zum Schliessen des grossen Buches                (neu)
// 2184-2199 - Button fuer den Wechsel vom Indexeintrag zur Spellseite (neu)
//
//   Spheremaker -> Copy_Gump_2220 dann Photoshop -> Paste dann MulView import
//       0, 99 -  28,120 -> 0x878 (2183)
//      61, 54 - 185, 67 -> 0x888 (2184)
//      61, 69 - 185, 82 -> 0x889 (2185)
//      61, 84 - 185, 97 -> 0x88a (2186)
//      61, 99 - 185,112 -> 0x88b (2187)
//      61,114 - 185,127 -> 0x88c (2188)
//      61,129 - 185,142 -> 0x88d (2189)
//      61,144 - 185,157 -> 0x88e (2190)
//      61,159 - 185,172 -> 0x88f (2191)
//     224, 54 - 348, 67 -> 0x890 (2192)
//     224, 69 - 348, 82 -> 0x891 (2193)
//     224, 84 - 348, 97 -> 0x892 (2194)
//     224, 99 - 348,112 -> 0x893 (2195)
//     224,114 - 348,127 -> 0x894 (2196)
//     224,129 - 348,142 -> 0x895 (2197)
//     224,144 - 348,157 -> 0x896 (2198)
//     224,159 - 348,172 -> 0x897 (2199)

// Schreibsysmbol - 0xfc1

Global layout_small:={
  "nodispose",                                    // Grundeinstellung
  "nomove",
  "page 0",                                       // Basisseite
  "button 16 16 2234 2234 1 0 "+BTTN_GROSSES_BUCH //  Verweis auf grosses Buch
};

////////////////////
//                //
//   Zauberbuch   //
//                //
////////////////////

/////////////////////////////////////////////////
// UseSpellBook - Doppelklick auf das Spellbook
/////////////////////////////////////////////////

Function UseSpellBook(who, spellbook)
  Local bookdesc; // Beschreibungen des Buches ermitteln
  Case (spellbook.objtype)
    UOBJ_SPELLBOOK_MAGE:   bookdesc:={"Das Grimoire", "Dieses Grimoire"};
    UOBJ_SPELLBOOK_CLERIC: bookdesc:={"Der Liber Castus", "Dieser Liber Castus"};
    UOBJ_SPELLBOOK_NECRO:  bookdesc:={"Das paq mu'qaDmey", "Dieses paq mu'qaDmey"};
  EndCase

  Local basiscontainer:=spellbook.container; // Buch muss sich im Backpack befinden
  While (basiscontainer.container)
    basiscontainer:=basiscontainer.container;
  EndWhile

  If (basiscontainer.serial=who.serial) // Befindet sich das Buch im Backpack?
    Local fingerabdruck:=GetObjProperty(spellbook, "Besitzer");
    If (fingerabdruck)
      If ((fingerabdruck=who.serial) Or (who.cmdlevel))
        // Ist das SpellBook bereits geoeffnet?
        Local open:=GetObjProperty(spellbook, "#Open");
        If (open) // Ja. Falls doch nicht, wird das Flag nach 5 Sekunden entfernt
          Local errorclock:=GetObjProperty(spellbook, "#ErrorClock");
          If (errorclock)
            If (errorclock>ReadGameClock())
              EraseObjProperty(spellbook, "#Open");
              open:=0; // Buch ist wohl doch nicht geoeffnet...
            EndIf
          EndIf
        EndIf

        // Ist das Buch nun geoeffnet?
        If (open) // Ja
          SendSysMessage(who, bookdesc[1]+" ist bereits geoeffnet!");
          SendSysMessage(who, "Falls doch nicht, versucht es erneut...");

          SetObjProperty(spellbook, "#ErrorClock", ReadGameClock()+5);
        Else // Nein. Oeffnen...
          EraseObjProperty(spellbook, "#ErrorClock");
          SetObjProperty(spellbook, "#Open", 1);

          SendSysMessage(who, bookdesc[1]+" wird geoeffnet.");

          Set_Script_Option(SCRIPTOPT_NO_RUNAWAY, 1);
          ShowSpellBook(who, spellbook);

          // Test
          TestDemoSpellPanel(who, spellbook);

          EraseObjProperty(spellbook, "#Open");
        EndIf
      Else
        Local besitzer:=SystemFindObjectBySerial(fingerabdruck, SYSFIND_SEARCH_OFFLINE_MOBILES);
        If (besitzer)
          SendSysMessage(who, bookdesc[2]+" gehoert "+besitzer.name+" und nicht Euch!");
          SysLog("WARNUNG: "+who.name+" wollte das Zauberbuch von "+besitzer.name+" ("+
            Lower(Hex(spellbook.serial))+") benutzen!");
        Else
          SendSysMessage(who, bookdesc[2]+" hat keinen Besitzer mehr. Vernichtet es!");
          SysLog("WARNUNG: "+who.name+" wollte das Zauberbuch "+Lower(Hex(spellbook.serial))+" benutzen!");
        EndIf
      EndIf
    Else
      SendSysMessage(who, bookdesc[2]+" wurde fehlerhaft initialisiert. Vernichtet es!");
    EndIf
  Else
    SendSysMessage(who, bookdesc[1]+" muss sich im Backpack befinden!");
  EndIf
EndFunction

///////////////////////////////////////////
// ShowSpellBook - Zeigt das Spellbook an
///////////////////////////////////////////

Function ShowSpellBook(who, spellbook)
  // Konstanten gemaess Magierklasse verteilen
  Local magierklasse:=0; // Identifikator der globalen Variablen
  Local skillid;         // Skill zum Casten
  Local min_spell;       // Basis-SpellID zum Casten
  Local symbol_spell;    // Positionsangabe des Spell-Gumps
  Case (spellbook.objtype)
    UOBJ_SPELLBOOK_MAGE:   magierklasse:=MAGE_DESC;
                           skillid:=MAGE_SKILL;
                           min_spell:=MIN_MAGE_SPELL;
                           symbol_spell:=GUMP_MAGE_SPELL;
    UOBJ_SPELLBOOK_CLERIC: magierklasse:=CLERIC_DESC;
                           skillid:=CLERIC_SKILL;
                           min_spell:=MIN_CLERIC_SPELL;
                           symbol_spell:=GUMP_CLERIC_SPELL;
    UOBJ_SPELLBOOK_NECRO:  magierklasse:=NECRO_DESC;
                           skillid:=NECRO_SKILL;
                           min_spell:=MIN_NECRO_SPELL;
                           symbol_spell:=GUMP_NECRO_SPELL;
  EndCase

  // Spellbook zusammenbauen
  If (magierklasse)
    Local spellsindex:=GetGlobalProperty("SpIndex"+magierklasse);     // Spelldaten sortiert nach Circle und Spellname
    Local spellsreindex:=GetGlobalProperty("SpReIndex"+magierklasse); // Umkehrliste (Zuordnung SpellID zu Pos. in Spelldaten)
    Local spellscircle:=GetGlobalProperty("SpCircle"+magierklasse);   // Anfang des Circles im Index

    // Endlosschleife, fuer Wechsel zwischen kleinem und grossem Buch
    Local bttn:=BTTN_GROSSES_BUCH;
    While (bttn=BTTN_GROSSES_BUCH)
      Local spellsmask:=GetSpellsMask(spellbook, magierklasse); // Spellmaske (Welcher Spell ist im Buch?)
      Local layout:=GetGlobalProperty("SpLayout"+magierklasse); // Vorgefertigtes Layout
      Local data:=GetGlobalProperty("SpData"+magierklasse);     // Vorgefertigte Daten

      Local spellspage:=spellscircle[spellscircle.size()][2]; // Erste Seite der Spells im Buch
      Local datadescpos:=data.size(); // Startposition der Spellnamen in den Gump-Daten
      Local lastpageshown:=0; // Letzte erzeugte Gump-Seite
      Local pageshown; // Ist die Gump-Seite bereits gewechselt, also "sichtbar"?
      Local leftpage;  // Links oder rechts auf der Seite?
      Local pages:=0;  // Anzahl [und Position im Buch] der Spells
      Local bttnpic;   // Hilfsvariable fuer Gump-Button-Definitionen
      Local spellnr;   // Aktueller Spell auf der aktuellen Index-Seite
      Local spellid;   // Aktueller Spell [eines Circles] (Schleifenzaehler)
      Local circle;    // Aktueller Circle (Schleifenzaehler)
      Local page;      // Aktuelle Gump-Seite

      // Buch-Index mit Eintraegen fuellen
      For (circle:=1; circle<spellscircle.size(); circle:=circle+1)
        page:=spellscircle[circle][2];     // Index-Seite fuer Circle ermitteln
        leftpage:=spellscircle[circle][3]; // Links oder rechts auf der Index-Seite?
        pageshown:=0;                      // Seitenwechsel am Anfang eines neuen Circles erzwingen
        spellnr:=0;                        // Neues Seite, also noch nichts eingetragen

        // Buch-Index fuer einzelnen Circle fuellen
        For (spellid:=spellscircle[circle][1]; spellid<spellscircle[circle+1][1]; spellid:=spellid+1)
          If (spellsmask[spellid]) // Ist der Spell im Buch enthalten?
            If (!pageshown) // Seitenwechsel einfuegen?
              pageshown:=1;

              If (lastpageshown<>page) // Echter Seitenwechsel noetig?
                lastpageshown:=page;
                layout.append("page "+page);
              EndIf
            EndIf

            // Indexeintrag des Spells einfuegen
            pages:=pages+1;
            If (leftpage) // Links oder rechts?
              bttnpic:=" "+(GUMP_HIDDENBTN_LEFT+spellnr);
              layout.append("button "+(BASE_X+61)+" "+(BASE_Y+54+spellnr*15)+bttnpic+bttnpic+
                " 0 "+(spellspage+CInt((pages-1)/2)+1));
              layout.append("croppedtext "+(BASE_X+61)+" "+(BASE_Y+50+spellnr*15)+" 123 15 0 "+data.size());
            Else
              bttnpic:=" "+(GUMP_HIDDENBTN_RIGHT+spellnr);
              layout.append("button "+(BASE_X+224)+" "+(BASE_Y+54+spellnr*15)+bttnpic+bttnpic+
                " 0 "+(spellspage+CInt((pages-1)/2)+1));
              layout.append("croppedtext "+(BASE_X+224)+" "+(BASE_Y+50+spellnr*15)+" 123 15 0 "+data.size());
            EndIf
            data.append(spellsindex[spellid][1]);

            // Zahl der Sprueche im Index und damit Seiten weiterzaehlen
            spellnr:=spellnr+1;
            If (spellnr>7) // Seite vollgeschrieben?
              spellnr:=0;

              leftpage:=1-leftpage;
              If (leftpage) // Echter Seitenwechsel noetig?
                page:=page+1;
                pageshown:=0;
              EndIf
            EndIf
          EndIf
        EndFor
      EndFor

      // Spell-Beschreibungen (echte Spell-Seiten) erzeugen
      If (pages)
        pages:=spellspage+CInt((pages-1)/2)+1; // Gesamtzahl der Gump-Seiten ermitteln
        page:=spellspage;                      // Startseite holen

        If (!pageshown) // Seitenwechsel einfuegen?
          If (lastpageshown<>page) // Echter Seitenwechsel noetig?
            layout.append("page "+page);
          EndIf
        EndIf
        layout.append("button "+(BASE_X+321)+" "+(BASE_Y+8)+" 2236 2236 0 "+(page+1));

        Local spelldata; // Daten zum aktuellen Spell
        Local reagnr;    // Aktuelle Reagenzie (Schleifenzaehler)
        leftpage:=1;     // Neue Gump-Seite, also links gehts los

        // Ausformulierte Seiten der Spells einfuegen
        For (circle:=1; circle<spellscircle.size(); circle:=circle+1)
          bttnpic:=" "+(2224+circle); // Button fuer den Circle

          // Spells fuer einzelnen Circle einfuegen
          For (spellid:=spellscircle[circle][1]; spellid<spellscircle[circle+1][1]; spellid:=spellid+1)
            If (spellsmask[spellid]) // Ist der Spell im Buch enthalten?
              spelldata:=spellsindex[spellid]; // Daten zum Spell holen

              // Gump des Spells ermitteln
              bttnpic:=" "+(symbol_spell+spelldata[2]-1);

              // Spellseite zusammenbasteln
              If (leftpage) // Links oder rechts?
                // Seitengrundgeruest anlegen
                page:=page+1;
                layout.append("page "+page); // Seitenwechsel erzeugen
                layout.append("button "+(BASE_X+50)+" "+(BASE_Y+8)+" 2235 2235 0 "+(page-1));

                // Spellname, Spellsymbol und PowerWords erzeugen
                layout.append("htmlgump "+(BASE_X+85)+" "+(BASE_Y+12)+" 99 35 "+datadescpos+" 0 0");
                layout.append("button "+(BASE_X+61)+" "+(BASE_Y+54)+" "+bttnpic+bttnpic+" 1 0 "+
                  (BTTN_SPELLS+spelldata[2]));
                layout.append("htmlgump "+(BASE_X+109)+" "+(BASE_Y+58)+" 76 35 "+data.size()+" 0 0");
                data.append(spelldata[3]);

                // Reagenzien erzeugen
                For (reagnr:=1; reagnr<=spelldata[5].size(); reagnr:=reagnr+1)
                  layout.append("text "+(BASE_X+61)+" "+(BASE_Y+95+reagnr*15)+" 0 "+spelldata[5][reagnr]);
                EndFor

                // Verknuepfung zum Index (Circle-Basis-Seite) erzeugen
                bttnpic:=" "+(2224+circle);
                layout.append("button "+(BASE_X+58)+" "+(BASE_Y+175)+bttnpic+bttnpic+" 0 "+
                  spellscircle[circle][2]);
              Else
                // Seitengrundgeruest vervollstaendigen
                If (page<pages) // Gibt es eine nachfolgende Seite?
                  layout.append("button "+(BASE_X+321)+" "+(BASE_Y+8)+" 2236 2236 0 "+(page+1));
                EndIf

                // Spellname, Spellsymbol und PowerWords erzeugen
                layout.append("htmlgump "+(BASE_X+224)+" "+(BASE_Y+12)+" 99 35 "+datadescpos+" 0 0");
                layout.append("button "+(BASE_X+224)+" "+(BASE_Y+54)+" "+bttnpic+bttnpic+" 1 0 "+
                  (BTTN_SPELLS+spelldata[2]));
                layout.append("htmlgump "+(BASE_X+272)+" "+(BASE_Y+58)+" 76 35 "+data.size()+" 0 0");
                data.append(spelldata[3]);

                // Reagenzien erzeugen
                For (reagnr:=1; reagnr<=spelldata[5].size(); reagnr:=reagnr+1)
                  layout.append("text "+(BASE_X+224)+" "+(BASE_Y+95+reagnr*15)+" 0 "+spelldata[5][reagnr]);
                EndFor

                // Verknuepfung zum Index (Circle-Basis-Seite) erzeugen
                bttnpic:=" "+(2224+circle);
                layout.append("button "+(BASE_X+332)+" "+(BASE_Y+175)+bttnpic+bttnpic+" 0 "+
                  spellscircle[circle][2]);
              EndIf

              datadescpos:=datadescpos+1; // Position des naechsten Spellnamen in den Gump-Daten ermitteln
              leftpage:=1-leftpage;       // Neuer Spell, neue Seite
            EndIf
          EndFor
        EndFor
      EndIf

      // Spellbook aufrufen und Ergebnisse bearbeiten
      bttn:=CInt(SendDialogGump(who, layout, data)[0]);
      If (bttn>BTTN_SPELLS) // Spell casten
        Local spellid:=spellsindex[spellsreindex[bttn-BTTN_SPELLS]][2]; // Daten zum Spell

        If (spellid<=MAX_MAIN_SPELL)
          CastSpell(who, spellid+SPELLID_KORREKTUR, skillid);
        Else
          CastSpell(who, spellid+min_spell-COUNT_MAIN_SPELLS-1, skillid);
        EndIf

        bttn:=CInt(SendDialogGump(who, layout_small, {})[0]); // Buch minimieren
      ElseIf (bttn=BTTN_KLEINES_BUCH)
        bttn:=CInt(SendDialogGump(who, layout_small, {})[0]); // Buch minimieren
      EndIf
    EndWhile
  Else
    SysLog("Spells: Dieses Script ist faelschlicherweise mit dem Item "+Lower(Hex(spellbook.objtype))+" verknuepft!");
  EndIf
EndFunction

////////////////////
//                //
//   SpellPanel   //
//                //
////////////////////

////////////////////////////////////////////////////////////////////////
// TestDemoSpellPanel - Erzeugt und Testet ein Panel zur Demonstration
////////////////////////////////////////////////////////////////////////

Function TestDemoSpellPanel(who, spellbook)
  Local spellpanelanzahl:=0;

  ForEach spellpanel in EnumerateItemsInContainer(spellbook)
    If (spellpanel.objtype=UOBJ_SPELLPANEL) // Ist es ein SpellPanel?
      spellpanelanzahl:=spellpanelanzahl+1;
    EndIf
  EndForEach

  // Wenn es noch kein Panel gibt, dann ein neues anlegen
  If (!spellpanelanzahl)
    Local matrix:={}; // Matrix der Spells auf dem Panel (Zeile x Spalte)

    // Matrix zur Demonstration fuellen
    For zeile:=1 To DEFAULT_PANEL_ZEILEN
      Local spellzeile:={}; // Eine komplette SpellZeile

      // SpellZeile fuellen
      For spalte:=1 To DEFAULT_PANEL_SPALTEN
        spellzeile.append(0);
      EndFor

      matrix.append(spellzeile);
    EndFor

    // Panel anlegen
    Local spellpanel:=CreateItemInContainer(spellbook, UOBJ_SPELLPANEL);
    If (spellpanel)
      SetObjProperty(spellpanel, "Data", {DEFAULT_PANEL_X, DEFAULT_PANEL_Y, 1, matrix});
    EndIf
  EndIf

  // Alle Spellpanels anzeigen
  ShowSpellPanels(who, spellbook);
EndFunction

////////////////////////////////////////////////
// ShowSpellPanels - Zeigt alle Spellpanels an
////////////////////////////////////////////////

Function ShowSpellPanels(who, spellbook)
  ForEach spellpanel in EnumerateItemsInContainer(spellbook)
    If (spellpanel.objtype=UOBJ_SPELLPANEL) // Ist es ein SpellPanel?
      Local data:=GetObjProperty(spellpanel, "Data");
      If (data) // Sind die Einstellungen vorhanden?
        If (data[3]) // Soll das Panel angezeigt werden?
          // ToDo: 'n extra Script draus machen... so nimmt er immer nur das erste, was er findet
          ShowSpellPanel(who, spellpanel);
        EndIf
      Else
        SysLog("FEHLER: SpellPanel "+Lower(Hex(spellpanel.serial))+" wurde nicht richtig konfiguriert!");
      EndIf
    EndIf
  EndForEach
EndFunction

/////////////////////////////////////////////
// ShowSpellPanel - Zeigt ein Spellpanel an
/////////////////////////////////////////////

Function ShowSpellPanel(who, spellpanel)
  Local spellbook:=spellpanel.container; // Zugehoeriges Spellbook
  If (spellbook) // Befindet sich das Panel "im" Spellbook?
    // Konstanten gemaess Magierklasse verteilen
    Local magierklasse:=0; // Identifikator der globalen Variablen
    Local skillid;         // Skill zum Casten
    Local min_spell;       // Basis-SpellID zum Casten
    Local symbol_spell;    // Positionsangabe des Spell-Gumps
    Case (spellbook.objtype)
      UOBJ_SPELLBOOK_MAGE:   magierklasse:=MAGE_DESC;
                             skillid:=MAGE_SKILL;
                             min_spell:=MIN_MAGE_SPELL;
                             symbol_spell:=GUMP_MAGE_SPELL;
      UOBJ_SPELLBOOK_CLERIC: magierklasse:=CLERIC_DESC;
                             skillid:=CLERIC_SKILL;
                             min_spell:=MIN_CLERIC_SPELL;
                             symbol_spell:=GUMP_CLERIC_SPELL;
      UOBJ_SPELLBOOK_NECRO:  magierklasse:=NECRO_DESC;
                             skillid:=NECRO_SKILL;
                             min_spell:=MIN_NECRO_SPELL;
                             symbol_spell:=GUMP_NECRO_SPELL;
    EndCase

    // Spellpanel zusammenbauen
    If (magierklasse)
      Local spellsindex:=GetGlobalProperty("SpIndex"+magierklasse);     // Spelldaten sortiert nach Circle und Spellname
      Local spellsreindex:=GetGlobalProperty("SpReIndex"+magierklasse); // Umkehrliste (Zuordnung SpellID zu Pos. in Spelldaten)

      // Endlosschleife
      Local edit:=0; // Produktives Panel, oder Panel editieren?
      Local bttn:=BTTN_EDIT;
      While ((bttn=BTTN_EDIT) Or edit)
        // Daten des Panels holen
        Local paneldata:=GetObjProperty(spellpanel, "Data");
        Local x_pos:=paneldata[1];       // X-Position der linken, oberen Ecke
        Local y_pos:=paneldata[2];       // Y-Position der linken, oberen Ecke
        Local matrix:=paneldata[4];      // SpellMatrix
        Local zeilen:=matrix.size();     // Anzahl der SpellZeilen
        Local spalten:=matrix[1].size(); // Anzahl der SpellSpalten

        Local spellsmask:=GetSpellsMask(spellbook, magierklasse); // Spellmaske (Welcher Spell ist im Buch?)
        Local spelldata; // Daten zum aktuellen Spell
        Local bttnpic;   // Hilfsvariable fuer Gump-Button-Definitionen
        Local spellid;   // Aktueller Spell [eines Circles] (Schleifenzaehler)

        // Layout und Data aufbauen
        Local layout:={"nodispose", "nomove", "page 0", "resizepic "+x_pos+" "+y_pos+" 5054 "+
          (spalten*PANEL_GUMP_WIDTH+8)+" "+(zeilen*PANEL_GUMP_HEIGHT+8)};
        Local data:={};

        If (!edit) // Produktives Panel, oder Panel editieren?
          // Clickflaeche des Edit-Buttons
          layout.append("button "+(x_pos+spalten*PANEL_GUMP_WIDTH-19)+" "+
            (y_pos+zeilen*PANEL_GUMP_HEIGHT-19)+" 2703 2703 1 0 "+BTTN_EDIT);

          // Spellpanel zusammenbasteln
          For zeile:=1 To zeilen
            For spalte:=1 To spalten
              spellid:=matrix[zeile][spalte];
              If (spellid)
                If (spellsmask[spellid]) // Ist der Spell im Buch enthalten?
                  spelldata:=spellsindex[spellid][2]; // Daten zum Spell holen

                  // Gump des Spells ermitteln
                  bttnpic:=" "+(symbol_spell+spelldata-1);

                  // Spellsymbol erzeugen
                  layout.append("button "+(x_pos+(spalte-1)*PANEL_GUMP_WIDTH+4)+" "+(y_pos+
                    (zeile-1)*PANEL_GUMP_HEIGHT+4)+" "+bttnpic+bttnpic+" 1 0 "+(BTTN_SPELLS+spelldata));
                EndIf
              EndIf
            EndFor
          EndFor

          // Optische Flaeche des Edit-Buttons
          layout.append("button "+(x_pos+spalten*PANEL_GUMP_WIDTH-19)+" "+
            (y_pos+zeilen*PANEL_GUMP_HEIGHT-19)+" 2703 2703 1 0 "+BTTN_EDIT);

          // Endlosschleife
          bttn:=BTTN_SPELLS+1;
          While (bttn>BTTN_SPELLS)
            // Spellpanel aufrufen und Ergebnisse bearbeiten
            bttn:=CInt(SendDialogGump(who, layout, data)[0]);
            If (bttn>BTTN_SPELLS) // Spell casten
              Local spellid:=spellsindex[spellsreindex[bttn-BTTN_SPELLS]][2]; // Daten zum Spell
              If (spellid<=MAX_MAIN_SPELL)
                CastSpell(who, spellid+SPELLID_KORREKTUR, skillid);
              Else
                CastSpell(who, spellid+min_spell-COUNT_MAIN_SPELLS-1, skillid);
              EndIf
            ElseIf (bttn=BTTN_EDIT)
              edit:=1; // Edit-Modus betreten
            EndIf
          EndWhile
        Else
          // Position des Parameterfeldes bestimmen
          Local basis_x;
          If (x_pos<220)
            basis_x:=x_pos+(spalten*PANEL_GUMP_WIDTH+8)+10;
          Else
            basis_x:=30;
          EndIf

          // Parameterfeld zusammenbasteln
          layout.append("resizepic "+basis_x+" 30 2620 180 107");
          layout.append("text "+(basis_x+10)+" 43 40 0");
          layout.append("text "+(basis_x+100)+" 43 5 1");
          layout.append("button "+(basis_x+145)+" 40 2640 2641 1 0 "+BTTN_X_POS);
          layout.append("text "+(basis_x+10)+" 63 40 2");
          layout.append("text "+(basis_x+100)+" 63 5 3");
          layout.append("button "+(basis_x+145)+" 60 2640 2641 1 0 "+BTTN_Y_POS);
          layout.append("text "+(basis_x+10)+" 83 40 4");
          layout.append("text "+(basis_x+100)+" 83 5 5");
          layout.append("button "+(basis_x+145)+" 80 2640 2641 1 0 "+BTTN_ZEILEN);
          layout.append("text "+(basis_x+10)+" 103 40 6");
          layout.append("text "+(basis_x+100)+" 103 5 7");
          layout.append("button "+(basis_x+145)+" 100 2640 2641 1 0 "+BTTN_SPALTEN);
          data:={"X-Position", CStr(x_pos), "Y-Position", CStr(y_pos), "Zeilen", CStr(zeilen), "Spalten", CStr(spalten)};

          // Spellpanel zusammenbasteln
          For zeile:=1 To zeilen
            For spalte:=1 To spalten
              spellid:=matrix[zeile][spalte];
              If (spellid)
                If (spellsmask[spellid]) // Ist der Spell im Buch enthalten?
                  spelldata:=spellsindex[spellid][2]; // Daten zum Spell holen

                  // Gump des Spells ermitteln
                  bttnpic:=" "+(symbol_spell+spelldata-1);

                  // Spellsymbol erzeugen
                  layout.append("button "+(x_pos+(spalte-1)*PANEL_GUMP_WIDTH+4)+" "+(y_pos+
                    (zeile-1)*PANEL_GUMP_HEIGHT+4)+bttnpic+bttnpic+" 1 0 "+(BTTN_SPELLS+spalte+(zeile-1)*spalten));
                EndIf
              Else
                // Spellsymbol erzeugen
                layout.append("button "+(x_pos+(spalte-1)*PANEL_GUMP_WIDTH+12)+" "+(y_pos+
                  (zeile-1)*PANEL_GUMP_HEIGHT+12)+" "+GUMP_EMPTY_EDIT+" "+GUMP_EMPTY_EDIT+" 1 0 "+
                  (BTTN_SPELLS+spalte+(zeile-1)*spalten));
              EndIf
            EndFor
          EndFor

          // Spellpanel aufrufen und Ergebnisse bearbeiten
          bttn:=CInt(SendDialogGump(who, layout, data)[0]);
          If (bttn>BTTN_SPELLS) // Spell casten
            Local zeile:=(bttn-BTTN_SPELLS+spalten-1)/spalten;
            Local spalte:=(bttn-BTTN_SPELLS)-(zeile-1)*spalten;

            // Neuen Spruch fuer das Panel auswaehlen (ItemID)
            Local panelscrollid:=ProcessMenu(who, spellbook);
            If (panelscrollid) // Neue Matrix schreiben
              matrix[zeile][spalte]:=GetSpellIDfromObjType(spellbook, panelscrollid);
            Else
              matrix[zeile][spalte]:=0;
            EndIf
            SetObjProperty(spellpanel, "Data", {x_pos, y_pos, 1, matrix});
          ElseIf (bttn) // Parameter aendern
            Local description;
            Local maxval;

            Case (bttn)
              BTTN_X_POS:   description:="X-Position";maxval:=2048;
              BTTN_Y_POS:   description:="Y-Position";maxval:=2048;
              BTTN_ZEILEN:  description:="Zeilen";    maxval:=10;
              BTTN_SPALTEN: description:="Spalten";   maxval:=10;
            EndCase

            Local val:=CInt(SendTextEntryGump(who, "Bitte den neuen Wert fuer '"+
              description+"' eingeben!", TE_CANCEL_ENABLE, TE_STYLE_NUMERICAL, maxval));
            If (val)
              Case (bttn)
                BTTN_X_POS:   SetObjProperty(spellpanel, "Data", {val, y_pos, 1, matrix});
                BTTN_Y_POS:   SetObjProperty(spellpanel, "Data", {x_pos, val, 1, matrix});
                BTTN_ZEILEN:  ChangeSpellPanelSize(spellpanel, x_pos, y_pos, val, spalten, matrix);
                BTTN_SPALTEN: ChangeSpellPanelSize(spellpanel, x_pos, y_pos, zeilen, val, matrix);
              EndCase
            Else
              SendSysMessage(who, "Abbruch.");
            EndIf
          Else
            edit:=0; // Edit-Modus verlassen
            bttn:=BTTN_EDIT;
          EndIf
        EndIf
      EndWhile
    Else
      SysLog("Spells: Dieses Script ist faelschlicherweise mit dem Item "+Lower(Hex(spellbook.objtype))+" verknuepft!");
    EndIf
  Else
    SysLog("Spells: Das Panel "+Lower(Hex(spellpanel.serial))+" befindet sich nicht 'in' einem Spellbook!");
  EndIf
EndFunction

////////////////////////////////////////////////////////////////////////////////
// ChangeSpellPanelSize - Groesse des SpellPanels und damit der Matrix aendern
////////////////////////////////////////////////////////////////////////////////

Function ChangeSpellPanelSize(spellpanel, x_pos, y_pos, zeilen_new, spalten_new, matrix_old)
  Local matrix:={};
  Local spellid;

  // Neue Matrix initialisieren
  For zeile:=1 To zeilen_new
    Local spellzeile:={}; // Eine komplette SpellZeile

    // SpellZeile fuellen
    For spalte:=1 To spalten_new
      spellid:=matrix_old[zeile][spalte];
      If (spellid)
        spellzeile.append(spellid); // Wert aus der alten Matrix uebernehmen
      Else
        spellzeile.append(0);
      EndIf
    EndFor

    matrix.append(spellzeile);
  EndFor

  SetObjProperty(spellpanel, "Data", {x_pos, y_pos, 1, matrix});
EndFunction

/////////////////////////
//                     //
//   Initialisierung   //
//                     //
/////////////////////////

////////////////////////////////////////////////
// InitSpellBook - Initialisiert das Spellbook
////////////////////////////////////////////////

Function InitSpellBook()
  BroadCast("Magic-Pergon Spellbook wird initialisiert...");
  SysLog("Magic-Pergon Spellbook wird initialisiert...");

  // Magierklassen initialisieren
  If (InitMagierKlasse(MAGE_DESC) And InitMagierKlasse(CLERIC_DESC) And
     InitMagierKlasse(NECRO_DESC))
    BroadCast("Magic-Pergon Spellbook wurde initialisiert.");
    SysLog("Magic-Pergon Spellbook wurde initialisiert.");
  Else
    BroadCast("Magic-Pergon Spellbook konnte nicht initialisiert werden!");
    SysLog("Magic-Pergon Spellbook konnte nicht initialisiert werden!");
  EndIf
EndFunction

///////////////////////////////////////////////////
// InitMagierKlasse - Magierklasse initialisieren
///////////////////////////////////////////////////

Function InitMagierKlasse(magierklasse)
  Local spells:=GetWholeSpellConfig(magierklasse); // Statische Daten aller Spells holen
  If (spells)
    // Gump-Layout definieren
    Local layout:={"nodispose",
      "page 0",
      "gumppic "+BASE_X+" "+BASE_Y+" 2220",
      "button "+BASE_X+" "+(BASE_Y+99)+" 2183 2183 1 0 "+BTTN_KLEINES_BUCH};

    Local spellsdata; // Spelldaten der Spells, getrennt nach Circle
    Local min_spell;  // SpellID-Korrekturwert
    Local data;       // Gump-Data

    // Anzahl der Circle, Circle-Beschreibungen und SpellID-Korrekturwert festlegen
    Case (magierklasse)
      MAGE_DESC:   spellsdata:={{}, {}, {}, {}, {}, {}, {}, {}}; // Nur 8 Circle
                   data:={
                     "INDEX",          // Index-Seite 1..8
                     "Erster Zirkel",
                     "Zweiter Zirkel",
                     "Dritter Zirkel",
                     "Vierter Zirkel",
                     "Fuenfter Zirkel",
                     "Sechster Zirkel",
                     "Siebter Zirkel",
                     "Achter Zirkel"};
                   min_spell:=MIN_MAGE_SPELL;
      CLERIC_DESC: spellsdata:={{}, {}, {}, {}, {}, {}, {}, {}}; // Nur 8 Circle
                   data:={
                     "INDEX",          // Index-Seite 1..8
                     "Erster Zirkel",
                     "Zweiter Zirkel",
                     "Dritter Zirkel",
                     "Vierter Zirkel",
                     "Fuenfter Zirkel",
                     "Sechster Zirkel",
                     "Siebter Zirkel",
                     "Achter Zirkel"};
                   min_spell:=MIN_CLERIC_SPELL;
      NECRO_DESC:  spellsdata:={{}, {}, {}, {}, {}, {}, {}, {}}; // Nur 8 Circle
                   data:={
                     "INDEX",          // Index-Seite 1..8
                     "Erster Zirkel",
                     "Zweiter Zirkel",
                     "Dritter Zirkel",
                     "Vierter Zirkel",
                     "Fuenfter Zirkel",
                     "Sechster Zirkel",
                     "Siebter Zirkel",
                     "Achter Zirkel"};
                   min_spell:=MIN_NECRO_SPELL;
    EndCase

    Local datareagpos:=data.size()-1; // Startposition der Reagenzien in den Gump-Daten
    Local spellsreagents:={}; // Liste der Reagenzien, synchron zu den Gump-Daten
    Local spellsmask:={}; // Spellmaske (Welcher Spell ist im Buch?) im Voraus generieren
    Local circle; // Circle des Spells
    Local class;  // Zuordnung des Spells ("All", "Mage", "Cleric" oder "Necro")
    Local desc;   // Beschreibung des Spells

    // Spelldaten ermitteln und getrennt nach Circle einordnen
    ForEach spell in spells
      // SpellID ermitteln
      Local spellid:=spell.spellid;
      If (spellid>=SPELLID_KORREKTUR)
        spellid:=spellid-SPELLID_KORREKTUR;
      EndIf

      // Spell gemaess Spellnummer den allgemeinen oder speziellen Spells zuordnen
      If (spellid<=MAX_MAIN_SPELL)
        class:="All";
      Else
        class:=magierklasse;
      EndIf

     // // Passt der Class-Eintrag zur SpellID?
     // If (spell.class=class)
        // Gehoert der Spell einem gueltigen Circle an?
        circle:=CInt(spell.circle);
        If ((1<=circle) And (circle<=spellsdata.size()))
         // // Ist die Spell-Beschreibung gueltig?
         // desc:=CStr(spell.desc);
         // If ((desc[1, 8]="Spruch "+CChr(34)) And (desc[Len(desc), 1]=CChr(34)))
            // Verweisliste der Reagenzien erstellen
            Local reagents:={};
            ForEach reagent in GetConfigStringArray(spell, "Reagent") //"PergonReag")
              If (reagent in spellsreagents)
                // Position der Reagenzie raussuchen
                Local index:=1;
                While (spellsreagents[index]<>reagent)
                  index:=index+1;
                EndWhile

                reagents.append(index+datareagpos); // Index der Verweisliste hinzufuegen
              Else
                data.append(reagent); // Reagenzie in die Gump-Daten aufnehmen
                spellsreagents.append(reagent);

                reagents.append(spellsreagents.size()+datareagpos); // Index der Verweisliste hinzufuegen
              EndIf
            EndForEach

            // Luecke zwischen speziellem und allgemeinem Spell schliessen
            If (spellid>=min_spell)
              spellid:=spellid-min_spell+COUNT_MAIN_SPELLS+1;
            EndIf

            // Spelldaten, nach Circle sortiert, eintragen
            //   Beschreibung, SpellID, PowerWords, Script, Reagenzienverweis
           // spellsdata[circle].append({desc[9, Len(desc)-9], spellid,
           //   GetConfigString(spell, "Power"+magierklasse), spell.script, reagents});
            spellsdata[circle].append({spell.name, spellid-DISTRO_KORREKTUR, spell.powerwords, spell.script, reagents});
         // Else
         //   SysLog("Spells: Fehlerhafte 'Desc' in Spell "+spell.spellid+"!");
         // EndIf
        Else
          SysLog("Spells: Fehlerhafter 'Circle' in Spell "+spell.spellid+"!");
        EndIf
     // Else
     //   SysLog("Spells: Fehlerhafte 'Class' in Spell "+spell.spellid+"!");
     // EndIf

      spellsmask.append(0); // Spellmaske erweitern
    EndForEach

    Local spellscirclebase:={}; // Bei welchem Eintrag faengt welcher Circle an?
    Local spellsindex:={}; // Spelldaten sortiert nach Circle und Spellname
    Local base:=1; // Bei welchem Eintrag fing der aktuelle Circle an?

    // Spelldaten innerhalb der Circle [nicht] sortieren und Gesamtliste bilden
    For (circle:=1; circle<=spellsdata.size(); circle:=circle+1)
      // Spelldaten innerhalb des Circle [nicht] sortieren
      ForEach spell in (spellsdata[circle]) // SortMultiArrayByIndexNotCase(spellsdata[circle], 1)
        spellsindex.append(spell);
      EndForEach

      spellscirclebase.append(base); // Position des ersten Spells des Circles speichern
      base:=base+spellsdata[circle].size();
    EndFor
    spellscirclebase.append(base); // Position hinter der des letzten Spells speichern

    // Umkehrtliste zur Gesamtliste bilden
    Local spellsreindex:={}; // Umkehrliste (Zuordnung SpellID zu Pos. in Spelldaten)
    Local spellid; // Aktuelle SpellNummer (Schleifenzaehler)
    For (spellid:=1; spellid<=spellsindex.size(); spellid:=spellid+1)
      spellsreindex[spellsindex[spellid][2]]:=spellid;
    EndFor

    Local spellcirclepages:={}; // Anzahl der Index-Seiten je Circle
    Local spellscircle:={}; // Anfang des Circles im Index
    Local leftpage:=1; // Links oder rechts auf der Seite?
    Local circlepage;  // Aktuelle Seite des Circles (Schleifenzaehler)
    Local page:=0;     // Aktuelle Index-Seite im Gump

    // Verteilung der Circle im Buch-Index ermitteln
    For (circle:=1; circle<spellscirclebase.size(); circle:=circle+1)
      // Anzahl der Index-Seiten je Circle ermitteln
      spellcirclepages.append(CInt((spellscirclebase[circle+1]-spellscirclebase[circle]-1)/8)+1);

      // Anfang des Circles im Index speichern
      //   Position des ersten Spells des Circles, Gump-Startseite, links oder rechts
      If (leftpage) // Links oder rechts?
        spellscircle.append({spellscirclebase[circle], page+1, 1});
      Else
        spellscircle.append({spellscirclebase[circle], page, 0});
      EndIf

      // Index-Seiten "durchzaehlen"
      For (circlepage:=1; circlepage<=spellcirclepages[circle]; circlepage:=circlepage+1)
        If (leftpage) // Echter Seitenwechsel noetig?
          page:=page+1;
        EndIf

        leftpage:=1-leftpage;
      EndFor
    EndFor
    // Position hinter der des letzten Spells und Seite hinter der letzten Index-Seite speichern
    spellscircle.append({spellscirclebase[spellscirclebase.size()], page});

    leftpage:=1; // Links oder rechts auf der Seite?   (Wert initialisieren)
    page:=0;     // Aktuelle Index-Seite im Gump       (Wert initialisieren)

    // Alle Index-Seiten zusammenbauen
    For (circle:=1; circle<spellscirclebase.size(); circle:=circle+1)
      For (circlepage:=1; circlepage<=spellcirclepages[circle]; circlepage:=circlepage+1)
        If (leftpage) // Links oder rechts?
          // Seitengrundgeruest anlegen
          page:=page+1;
          layout.append("page "+page);

          // Circle-"ShortButtons" an der Buchunterseite im Index erzeugen
          layout.append("button "+(BASE_X+58)+" "+(BASE_Y+175)+" 2225 2225 0 "+spellscircle[1][2]);
          layout.append("button "+(BASE_X+93)+" "+(BASE_Y+175)+" 2226 2226 0 "+spellscircle[2][2]);
          layout.append("button "+(BASE_X+130)+" "+(BASE_Y+175)+" 2227 2227 0 "+spellscircle[3][2]);
          layout.append("button "+(BASE_X+164)+" "+(BASE_Y+175)+" 2228 2228 0 "+spellscircle[4][2]);
          layout.append("button "+(BASE_X+227)+" "+(BASE_Y+175)+" 2229 2229 0 "+spellscircle[5][2]);
          layout.append("button "+(BASE_X+260)+" "+(BASE_Y+175)+" 2230 2230 0 "+spellscircle[6][2]);
          layout.append("button "+(BASE_X+297)+" "+(BASE_Y+175)+" 2231 2231 0 "+spellscircle[7][2]);
          layout.append("button "+(BASE_X+332)+" "+(BASE_Y+175)+" 2232 2232 0 "+spellscircle[8][2]);

          // Button zum Wechsel auf die Vorseite erzeugen
          If (!((circle=1) And (circlepage=1)) )
            layout.append("button "+(BASE_X+50)+" "+(BASE_Y+8)+" 2235 2235 0 "+(page-1));
          EndIf

          // Seitentitel und Circle-Beschreibungen erzeugen
          layout.append("text "+GumpTextMid(data[1], BASE_X+50, 151)+" "+(BASE_Y+12)+" 1111 0");
          layout.append("text "+(BASE_X+61)+" "+(BASE_Y+31)+" 2100 "+circle);
        Else
          // Button zum Wechsel auf die Folgeseite erzeugen
          If (!((circle=spellscirclebase.size()-1) And (circlepage=spellcirclepages[circle])))
            layout.append("button "+(BASE_X+321)+" "+(BASE_Y+8)+" 2236 2236 0 "+(page+1));
          EndIf

          // Seitentitel und Circle-Beschreibungen erzeugen
          layout.append("text "+GumpTextMid(data[1], BASE_X+204, 152)+" "+(BASE_Y+12)+" 1111 0");
          layout.append("text "+(BASE_X+224)+" "+(BASE_Y+31)+" 2100 "+circle);
        EndIf

        leftpage:=1-leftpage;
      EndFor
    EndFor

    // Alle voraus"berechneten" Daten speichern
    SetGlobalProperty("SpIndex"+magierklasse, spellsindex);     // Spelldaten sortiert nach Circle und Spellname
    SetGlobalProperty("SpReIndex"+magierklasse, spellsreindex); // Umkehrliste (Zuordnung SpellID zu Pos. in Spelldaten)
    SetGlobalProperty("SpCircle"+magierklasse, spellscircle);   // Anfang des Circles im Index
    SetGlobalProperty("SpMask"+magierklasse, spellsmask);       // Spellmaske (Welcher Spell ist im Buch?)
    SetGlobalProperty("SpLayout"+magierklasse, layout);         // Vorgefertigtes Gump-Layout
    SetGlobalProperty("SpData"+magierklasse, data);             // Vorgefertigte Gump-Daten

    Return (1);
  Else
    SysLog("  Klasse '"+magierklasse+"' konnte nicht initialisiert werden!");
  EndIf
EndFunction

//////////////////////////////////////////////////////////////////////
// GetWholeSpellConfig - Ermittelt die statischen Daten aller Spells
//////////////////////////////////////////////////////////////////////

Function GetWholeSpellConfig(magierklasse)
  // Spell-Konfigurationen einlesen
  Local spellsfile:=ReadConfigFile("::spells");
  If (spellsfile)
    Local spells:={}; // Statische Daten der Spells
    Local spellid; // Aktueller Spell (Schleifenzaehler)

    // Statische Daten der allgemeinen Spells zusammenstellen
    For (spellid:=MIN_MAIN_SPELL+DISTRO_KORREKTUR; spellid<=MAX_MAIN_SPELL+DISTRO_KORREKTUR; spellid:=spellid+1)
      spells.append(CheckSpellID(spellsfile[spellid+SPELLID_KORREKTUR], spellid+SPELLID_KORREKTUR));
    EndFor

    // Statische Daten der speziellen Spells zusammenstellen
    Case (magierklasse)
      MAGE_DESC:   For (spellid:=MIN_MAGE_SPELL+DISTRO_KORREKTUR; spellid<=MAX_MAGE_SPELL+DISTRO_KORREKTUR; spellid:=spellid+1)
                     spells.append(CheckSpellID(spellsfile[spellid], spellid));
                   EndFor
      CLERIC_DESC: For (spellid:=MIN_CLERIC_SPELL+DISTRO_KORREKTUR; spellid<=MAX_CLERIC_SPELL+DISTRO_KORREKTUR; spellid:=spellid+1)
                     spells.append(CheckSpellID(spellsfile[spellid], spellid));
                   EndFor
      NECRO_DESC:  For (spellid:=MIN_NECRO_SPELL+DISTRO_KORREKTUR; spellid<=MAX_NECRO_SPELL+DISTRO_KORREKTUR; spellid:=spellid+1)
                     spells.append(CheckSpellID(spellsfile[spellid], spellid));
                   EndFor
    EndCase

    Return (spells);
  Else
    SysLog("Spells: Kann die Datei 'spells.cfg' nicht oeffnen !");
  EndIf
EndFunction

/////////////////////////////////////////////////////////
// CheckSpellID - Ueberprueft die tatsaechliche SpellID
/////////////////////////////////////////////////////////

Function CheckSpellID(spellconfig, spellid)
  If (CInt(spellconfig.spellid)<>spellid)
    SysLog("Spells: Fehlerhafter 'SpellID' in Spell "+spellid+"!");
  EndIf

  Return (spellconfig);
EndFunction

///////////////////
//               //
//   Sonstiges   //
//               //
///////////////////

///////////////////////////////////////////////////////////////////////////////////////
// CreateSpellBookInBackpack - Erzeugt das Zauberbuch im Backpack inkl. Fingerabdruck
///////////////////////////////////////////////////////////////////////////////////////

Function CreateSpellBookInBackpack(who, bookobjtype)
  Local book:=CreateItemInBackpack(who, bookobjtype, 1);
  If (book)
    PersonalizeSpellBook(who, book); // Zauberbuch mit Fingerabdruck versehen

    Return (book);
  EndIf
EndFunction

/////////////////////////////////////////////////////////////////
// PersonalizeSpellBook - Zauberbuch mit Fingerabdruck versehen
/////////////////////////////////////////////////////////////////

Function PersonalizeSpellBook(who, book)
  SetObjProperty(book, "Besitzer", who.serial); // Fingerabdruck

  Case (book.objtype) // Spellmaske (Welcher Spell ist im Buch?)
    UOBJ_SPELLBOOK_MAGE:   SetObjProperty(book, "SpellsMask", GetGlobalProperty("SpMask"+MAGE_DESC));
    UOBJ_SPELLBOOK_CLERIC: SetObjProperty(book, "SpellsMask", GetGlobalProperty("SpMask"+CLERIC_DESC));
    UOBJ_SPELLBOOK_NECRO:  SetObjProperty(book, "SpellsMask", GetGlobalProperty("SpMask"+NECRO_DESC));
  EndCase
EndFunction

/////////////////////////////////////////////////////////
// CreateSpellInBook - Erzeugt den Spruch im Zauberbuch
/////////////////////////////////////////////////////////

Function CreateSpellInBook(spellbook, scrollobjtype)
  Local magierklasse:=0; // Identifikator der globalen Variablen
  Local min_spell_item;  // Minimale ItemID der Spezial-Spells
  Local max_spell_item;  // Maximale ItemID der Spezial-Spells
  Case (spellbook.objtype)
    UOBJ_SPELLBOOK_MAGE:   magierklasse:=MAGE_DESC;
                           min_spell_item:=MIN_MAGE_SPELL_ITEM;
                           max_spell_item:=MAX_MAGE_SPELL_ITEM;
    UOBJ_SPELLBOOK_CLERIC: magierklasse:=CLERIC_DESC;
                           min_spell_item:=MIN_CLERIC_SPELL_ITEM;
                           max_spell_item:=MAX_CLERIC_SPELL_ITEM;
    UOBJ_SPELLBOOK_NECRO:  magierklasse:=NECRO_DESC;
                           min_spell_item:=MIN_NECRO_SPELL_ITEM;
                           max_spell_item:=MAX_NECRO_SPELL_ITEM;
  EndCase

  // Spruch eintragen
  If (magierklasse)
    Local spellsreindex:=GetGlobalProperty("SpReIndex"+magierklasse); // Umkehrliste (Zuordnung SpellID zu Pos. in Spelldaten)

    Local spellsmask:=GetObjProperty(spellbook, "SpellsMask"); // Spellmaske (Welcher Spell ist im Buch?)
    If (!spellsmask)
      spellsmask:=GetGlobalProperty("SpMask"+magierklasse);

      SysLog("FEHLER: Zauberbuch "+Lower(Hex(spellbook.serial))+" hat keine gueltige SpellsMask!");
    EndIf

    // Spruch in Spellmaske eintragen
    If ((min_spell_item<=scrollobjtype) And (scrollobjtype<=max_spell_item))
      spellsmask[spellsreindex[scrollobjtype-min_spell_item+1]]:=1;
    EndIf

    SetObjProperty(spellbook, "SpellsMask", spellsmask);
  Else
    SysLog("Spells: Dieses Script ist faelschlicherweise mit dem Item "+Lower(Hex(spellbook.objtype))+" verknuepft!");
  EndIf
EndFunction

///////////////////////////////////////////////////////////
// GetSpellIDfromObjType - Ermittelt die SpellID zum Item
///////////////////////////////////////////////////////////

Function GetSpellIDfromObjType(spellbook, scrollobjtype)
  Local magierklasse:=0; // Identifikator der globalen Variablen
  Local min_spell_item;  // Minimale ItemID der Spezial-Spells
  Local max_spell_item;  // Maximale ItemID der Spezial-Spells
  Case (spellbook.objtype)
    UOBJ_SPELLBOOK_MAGE:   magierklasse:=MAGE_DESC;
                           min_spell_item:=MIN_MAGE_SPELL_ITEM;
                           max_spell_item:=MAX_MAGE_SPELL_ITEM;
    UOBJ_SPELLBOOK_CLERIC: magierklasse:=CLERIC_DESC;
                           min_spell_item:=MIN_CLERIC_SPELL_ITEM;
                           max_spell_item:=MAX_CLERIC_SPELL_ITEM;
    UOBJ_SPELLBOOK_NECRO:  magierklasse:=NECRO_DESC;
                           min_spell_item:=MIN_NECRO_SPELL_ITEM;
                           max_spell_item:=MAX_NECRO_SPELL_ITEM;
  EndCase

  // SpruchID ermitteln
  If (magierklasse)
    Local spellsreindex:=GetGlobalProperty("SpReIndex"+magierklasse); // Umkehrliste (Zuordnung SpellID zu Pos. in Spelldaten)

    // SpruchID ermitteln
    If ((min_spell_item<=scrollobjtype) And (scrollobjtype<=max_spell_item))
      Return (spellsreindex[scrollobjtype-min_spell_item+1]);
    EndIf
  Else
    SysLog("Spells: Dieses Script ist faelschlicherweise mit dem Item "+Lower(Hex(spellbook.objtype))+" verknuepft!");
  EndIf
EndFunction

//////////////////////////////////////////////////////////////
// SearchSpellBookInBackpack - Zauberbuch im Backpack suchen
//////////////////////////////////////////////////////////////

Function SearchSpellBookInBackpack(who, bookobjtype)
  ForEach item in EnumerateItemsInContainer(who.backpack)
    If (item.objtype=bookobjtype)
      Local fingerabdruck:=GetObjProperty(item, "Besitzer"); // Darf ich das Buch benutzen?
      If (fingerabdruck)
        If ((fingerabdruck=who.serial) Or (who.cmdlevel))
          Return (item); // Ein benutzbares Buch gefunden...
        EndIf
      EndIf
    EndIf
  EndForEach
EndFunction

///////////////////////////////////////////////////
// GetSpellsMask - Holt die SpellsMask des Buches
///////////////////////////////////////////////////

Function GetSpellsMask(spellbook, magierklasse)
  Local spellsmask:=GetObjProperty(spellbook, "SpellsMask"); // Spellmaske (Welcher Spell ist im Buch?)
  If (!spellsmask)
    spellsmask:=GetGlobalProperty("SpMask"+magierklasse);
    SetObjProperty(spellbook, "SpellsMask", spellsmask);

    If (ConvertSpellsInBook(spellbook)) // Altes Buch konvertieren?
      spellsmask:=GetObjProperty(spellbook, "SpellsMask");
    Else
      SysLog("FEHLER: Zauberbuch "+Lower(Hex(spellbook.serial))+" hat keine gueltige SpellsMask!");
    EndIf
  EndIf

  Return (spellsmask);
EndFunction

//////////////////////////////////////////////////////////////////
// ConvertSpellsInBook - Konvertiert die Sprueche zur Spellsmask
//////////////////////////////////////////////////////////////////

Function ConvertSpellsInBook(spellbook)
  Local spellitems:=EnumerateItemsInContainer(spellbook);
  If (spellitems)
    Local result:=0;

    ForEach spellitem in spellitems
      If (spellitem.objtype<>UOBJ_SPELLPANEL) // Alles was kein Panel ist umwandeln
        CreateSpellInBook(spellbook, spellitem.objtype);
        DestroyItem(spellitem);
        result:=1; // Es wurde konvertiert, also kein Fehler...
      EndIf
    EndForEach

    Return (result);
  EndIf
EndFunction

//////////////////////////////////////////////////////////////////////////
// CastSpell - Cast the Spell (this is NOT the original Pergon function)
//////////////////////////////////////////////////////////////////////////
// Shinigami: I'm not sure about the right Distro way to handle this

Function CastSpell(who, spellid, skill)
  Local spells:=ReadConfigFile("::spells");                      // load spells.cfg
  Local spell:=FindConfigElem(spells, spellid+DISTRO_KORREKTUR); // look up spell
  Local script:=GetConfigString(spell, "Script");                // read controlscript for spell

  Detach();
  Start_Script(":spells:"+script, who); // calling spelleffect

  Return (1);
EndFunction