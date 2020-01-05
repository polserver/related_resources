//////////////////////////////////////////////////////////////////
//
//   SpellDefs Include
//
//     Author: Shinigami
//     eMail : Shinigami@gmx.net
//
//   Modifications:
//     2001/12/27 Shinigami: SpellBook-Konstanten -> ObjType.inc
//
//////////////////////////////////////////////////////////////////

////////////
// Objekte
////////////

Const UOBJ_SPELLBOOK_MAGE  :=0x6820; // Grimoire
Const UOBJ_SPELLBOOK_CLERIC:=0x6821; // Liber Castus
Const UOBJ_SPELLBOOK_NECRO :=0x6822; // paq mu'qaDmey

Const UOBJ_SPELLPANEL      :=0x682f; // SpellPanel

///////////////
// Konstanten
///////////////

Const MAGE_DESC:=  "Mage";           // Magierklassen-[Kurz]Bezeichnung
Const CLERIC_DESC:="Cleric";
Const NECRO_DESC:= "Necro";

Const MAGE_SKILL:=  25;//SKILLID_MAGIE;
Const CLERIC_SKILL:=25;//SKILLID_SEGNEN;
Const NECRO_SKILL:= 25;//SKILLID_FLUCHEN;

Const MIN_MAGE_SPELL_ITEM:=  0x1f2d;//0x6700; // Inscription-Scrolls gemaess Magier-Klasse (ItemID)
Const MAX_MAGE_SPELL_ITEM:=  0x1f6c;//0x673f;
Const MIN_CLERIC_SPELL_ITEM:=0x1f2d;//0x6760;
Const MAX_CLERIC_SPELL_ITEM:=0x1f6c;//0x679f;
Const MIN_NECRO_SPELL_ITEM:= 0x1f2d;//0x67c0;
Const MAX_NECRO_SPELL_ITEM:= 0x1f6c;//0x67ff;

//Const MIN_MAGE_CAST_ITEM:=   0x6900; // Cast-Scrolls gemaess Magier-Klasse        (ItemID)
//Const MAX_MAGE_CAST_ITEM:=   0x693f;
//Const MIN_CLERIC_CAST_ITEM:= 0x6960;
//Const MAX_CLERIC_CAST_ITEM:= 0x699f;
//Const MIN_NECRO_CAST_ITEM:=  0x69c0;
//Const MAX_NECRO_CAST_ITEM:=  0x69ff;

Const MIN_SPELL_ITEM:=MIN_MAGE_SPELL_ITEM;  // Inscription-/Cast-Scrolls unabhaengig von Magier-Klasse (ItemID)
Const MAX_SPELL_ITEM:=MAX_NECRO_SPELL_ITEM;
//Const MIN_CAST_ITEM:= MIN_MAGE_CAST_ITEM;
//Const MAX_CAST_ITEM:= MAX_NECRO_CAST_ITEM;

Const SYMBOL_MAGE_CIRCLE:=   0x20c0; // Circle-Symbole gemaess Magier-Klasse     (ItemID)
Const SYMBOL_CLERIC_CIRCLE:= 0x20c0;
Const SYMBOL_NECRO_CIRCLE:=  0x20c0;

Const SYMBOL_MAGE_SPELL:=    0x2080; // Spell-Symbole gemaess Magier-Klasse      (ItemID)
Const SYMBOL_CLERIC_SPELL:=  0x2080;
Const SYMBOL_NECRO_SPELL:=   0x2080;

Const MIN_MAIN_SPELL:=            1; // Spellnummern gemaess Magier-Klasse       (SpellID)
Const MAX_MAIN_SPELL:=           32;
Const MIN_MAGE_SPELL:=           33; //101;
Const MAX_MAGE_SPELL:=           64; //132;
Const MIN_CLERIC_SPELL:=         33; //201;
Const MAX_CLERIC_SPELL:=         64; //232;
Const MIN_NECRO_SPELL:=          33; //301;
Const MAX_NECRO_SPELL:=          64; //332;

Const DISTRO_KORREKTUR:=        100; // Distro hat alle Spells doppelt, mit und ohne Reagenzien

Const COUNT_MAIN_SPELLS:=MAX_MAIN_SPELL-MIN_MAIN_SPELL+1;