///////////////////////////////////////////////////////
// enchant.inc
///////////////////////////////////////////////////////
//
// - shamelessly adapted from include/startEqp.inc to
//   allow easy scripting of enchanted items in a
//   distro compatible manner.....
// - thanks & credit to the original author(s)
//
///////////////////////////////////////////////////////
// FUNCTIONS
//
//External functions:
//  MagicAllowedandType(item,itemdesc:=0)  // itemdesc is composite <cfgref>
//  EnchantWand(item,type,charges)
//  EnchantCloth(item,type,charges)
//  EnchantArmor(item,type,charges,hpmod:=0,armod:=0)
//  EnchantWeapon(item,dmgmod,accymod:=0,hpmod:=0)
//  ClearEnchantments(item)
//
//Internal functions:
//  ApplyDmgMod(item,numb)
//  ApplyAccyMod(item,numb)
//  ApplyHPMod(item,numb)
//  ApplyARMod(item,numb)
//  SilverMod(item)
//  AddName(item)
//
///////////////////////////////////////////////////////
// NOTES
//
//- Enchantment types & sub-types .....
//
//  1.Weapons
//    type: automatic, dependant upon damage mod.....
//    silverhit: always added to an enchanted weapon.....           
//
//  2.Armors
//    1: protection
//    2: strength
//    3: blessing
//    4: reflect
//
//  3.Cloths
//    1: nightsight
//    2: protection
//    3: strength
//    4: invisibility
//    5: blessing
//    6: reflect
//
//  4.Wands
//    1: clumsiness
//    2: feeblemindedness
//    3: healing
//    4: weakness
//    5: harming
//    6: fireballs
//    7: greater healing
//    8: lightning
//    9: mana draining
//   10: identification
//
///////////////////////////////////////////////////////

include "include/string"; // necessary for AddArticle(itemname)
                          // in ClearEnchantements(item)

const MAX_HPMOD:=100;
const MAX_ACCY:=100;
const MAX_DMGMOD:=100;
const MAX_ARMOD:=100;

///////////////////////////////////////////////////////
// External Functions

// If an item can be made magical this function returns
// it's main enchantement type (otherwise 0)
//
function MagicAllowedandType(item,itemdesc:=0)
  if (!itemdesc)
    itemdesc:=ReadConfigFile(":*:itemdesc");
  endif
  var objname:=lower(itemdesc[item.graphic].name);
  var magicweapcfg := ReadConfigFile(":combat:magicweaps");
  var magicarmorcfg := ReadConfigFile(":combat:magicarmor");
  var magicclothcfg := ReadConfigFile(":combat:magiccloth");
  var elem1 := FindConfigElem(magicweapcfg, "1");
  var data1 := GetConfigInt(elem1, objname);
  if(data1)
    return 1;		// 1. enchantable weapon
  endif
  var elem2 := FindConfigElem(magicarmorcfg, "1");
  var data2 := GetConfigInt(elem2, objname);
  if(data2)
    return 2;		// 2. enchantable armour
  endif
  var elem3 := FindConfigElem(magicclothcfg, "1");
  var data3 := GetConfigInt(elem3, objname);
  if(data3)
    return 3;           // 3. enchantable clothes
  endif
  if (item.graphic in array( 0xdf2, 0xdf3, 0xdf4, 0xdf5, 0x13f9 ))
    return 4;           // 4. enchantable wand
  endif
  return 0;             // 0. can't enchant this item
endfunction

function EnchantWand(item,type,charges)
  var amt;
  case(type)
    1: SetObjProperty(item, "SpellId",  1);   SetObjProperty(item, "damagemod", "of clumsiness");
    2: SetObjProperty(item, "SpellId",  3);   SetObjProperty(item, "damagemod", "of feeblemindedness");
    3: SetObjProperty(item, "SpellId",  4);   SetObjProperty(item, "damagemod", "of healing");
    4: SetObjProperty(item, "SpellId",  8);   SetObjProperty(item, "damagemod", "of weakness");
    5: SetObjProperty(item, "SpellId", 12);   SetObjProperty(item, "damagemod", "of harming");
    6: SetObjProperty(item, "SpellId", 18);   SetObjProperty(item, "damagemod", "of fireballs");
    7: SetObjProperty(item, "SpellId", 29);   SetObjProperty(item, "damagemod", "of greater healing");
    8: SetObjProperty(item, "SpellId", 30);   SetObjProperty(item, "damagemod", "of lightning");
    9: SetObjProperty(item, "SpellId", 31);   SetObjProperty(item, "damagemod", "of mana draining");
   10: SetObjProperty(item, "SpellId", 65);   SetObjProperty(item, "damagemod", "of identification");
  endcase
  SetObjProperty(item, "charges", charges);
  item.usescript := ":wands:magicWands";
  var dsc;
  if(item.objtype == 0x13f9)
    dsc := "gnarled staff";
  else
    dsc := "wand";
  endif
  SetName(item, "a magic " + dsc);
endfunction

function EnchantCloth(item,type,charges)
 case (type)
   1:
    SetObjProperty(item, "type", "sight");
    SetObjProperty(item, "damagemod", " of nightsight");
   2:
    SetObjProperty(item, "type", "protection");
    SetObjProperty(item, "damagemod", " of protection");
   3:
    SetObjProperty(item, "type", "strength");
    SetObjProperty(item, "damagemod", " of strength");
   4:
    SetObjProperty(item, "type", "invisibility");
    SetObjProperty(item, "damagemod", " of invisibility");
   5:
    SetObjProperty(item, "type", "blessing");
    SetObjProperty(item, "damagemod", " of blessing");
   6:
    SetObjProperty(item, "type", "reflect");
    SetObjProperty(item, "damagemod", " of magic reflection");
  endcase
  SetObjProperty(item, "charges", charges);
  AddName(item);
endfunction

function EnchantArmor(item,type,charges,hpmod:=0,armod:=0)
  if (hpmod)
    ApplyHPMod(item,hpmod);
  endif
  if (armod)
    ApplyARMod(item,armod);  
  endif
  case (type) 
      1: SetObjProperty(item, "charges", charges);
         SetObjProperty(item, "type", "protection");
         var dmgmod := GetObjProperty(item, "damagemod");
         if(dmgmod)
           dmgmod := dmgmod + " and protection";
           SetObjProperty(item, "damagemod", dmgmod);
         else
           dmgmod := " of protection";
           SetObjProperty(item, "damagemod", dmgmod);
         endif
      2: SetObjProperty(item, "charges", charges);
         SetObjProperty(item, "type", "strength");
         var dmgmod := GetObjProperty(item, "damagemod");
         if(dmgmod)
           dmgmod := dmgmod + " and strength";
           SetObjProperty(item, "damagemod", dmgmod);
         else
           dmgmod := " of strength";
           SetObjProperty(item, "damagemod", dmgmod);
         endif
      3: SetObjProperty(item, "charges", charges);
         SetObjProperty(item, "type", "blessing");
         var dmgmod := GetObjProperty(item, "damagemod");
         if(dmgmod)
           dmgmod := dmgmod + " and blessing";
           SetObjProperty(item, "damagemod", dmgmod);
         else
           dmgmod := " of blessing";
           SetObjProperty(item, "damagemod", dmgmod);
         endif
      4: SetObjProperty(item, "charges", charges);
         SetObjProperty(item, "type", "reflect");
         var dmgmod := GetObjProperty(item, "damagemod");
         if(dmgmod)
           dmgmod := dmgmod + " and magic reflection";
           SetObjProperty(item, "damagemod", dmgmod);
         else
           dmgmod := " of magic reflection";
           SetObjProperty(item, "damagemod", dmgmod);
         endif
  endcase
  AddName(item);
endfunction

function EnchantWeapon(item,dmgmod,accymod:=0,hpmod:=0)
  var types:={ };
  if (accymod)
    ApplyAccyMod(item,accymod);
  endif
  if (hpmod)
    ApplyHPMod(item,hpmod);
  endif
  ApplyDmgMod(item,dmgmod);
  AddName(item);
endfunction

function ClearEnchantments(item)
  var checkhitscript,onhit:=array;
  var on_hit:=GetObjProperty(item,"OnHit");
  if (on_hit)
    foreach checkhitscript in (GetObjProperty(item,"OnHit"))
      if (!checkhitscript["silverHit"])
        onhit.append(checkhitscript);
      endif
    endforeach
    SetObjProperty(item,"OnHit",onhit);
  endif
  EraseObjProperty(item,"silvermod");
  EraseObjProperty(item,"IDed");
  EraseObjProperty(item,"spellid");
  EraseObjProperty(item,"damagemod");  
  EraseObjProperty(item,"type");
  EraseObjProperty(item,"charges");
  EraseObjProperty(item,"accuracy");
  EraseObjProperty(item,"durability");
  var itemname:=itemcfg[item.objtype].desc;
  if (!itemname)
    itemname:=itemcfg[item.objtype].name;
  endif
  item.name:=AddArticle(itemname);
endfunction


///////////////////////////////////////////////////////
// Internal Functions

function ApplyDmgMod(item,numb)
  if(numb<=3)
    SetObjProperty(item, "damagemod", "of ruin");
  elseif(numb<=5)
    SetObjProperty(item, "damagemod", "of might");
  elseif(numb <= 7)
    SetObjProperty(item, "damagemod", "of force");
  elseif(numb <=9)
    SetObjProperty(item, "damagemod", "of power");
  elseif(numb <=20)
    SetObjProperty(item, "damagemod", "of vanquishing");
  else
    if (numb>MAX_DMGMOD)
      numb:=MAX_DMGMOD;
    endif
    SetObjProperty(item, "damagemod", "of annihalation");
  endif
  item.dmg_mod:=numb;
  SilverMod(item);
endfunction

function ApplyAccyMod(item,numb)
  if(numb < 10 )
    SetObjProperty(item, "accuracy", "accurate");
  elseif(numb <15 )
    SetObjProperty(item, "accuracy", "surpassingly accurate");
  elseif(numb < 20)
    SetObjProperty(item, "accuracy", "eminently accurate");
  elseif(numb < 25)
    SetObjProperty(item, "accuracy", "exceedingly accurate");
  elseif(numb< 30)
    SetObjProperty(item, "accuracy", "supremely accurate");    
  else
    if (numb>MAX_ACCY)
      numb:=MAX_ACCY;
    endif
    SetObjProperty(item, "accuracy", "heartseeking");
  endif
  SetObjProperty(item, "type", "accuracy");
  SetObjProperty(item, "gain", numb );
endfunction

function ApplyHPMod(item,numb)
  if(numb<10)
    SetObjProperty(item, "durability", "durable");
  elseif(numb <15)
    SetObjProperty(item, "durability", "substantial");
  elseif(numb < 20)
    SetObjProperty(item, "durability", "massive");
  elseif(numb < 25)
    SetObjProperty(item, "durability", "fortified");
  else
    SetObjProperty(item, "durability", "indestructable");
    if (numb>MAX_HPMOD)
      numb:=MAX_HPMOD;
    endif
  endif
  item.maxhp_mod := numb;
  item.hp := item.maxhp;
endfunction

function ApplyARMod(item,numb)
  if(numb < 10)
    SetObjProperty(item, "damagemod", "of defense");
  elseif(numb < 15)
    SetObjProperty(item, "damagemod", "of guarding");
  elseif(numb < 20)
    SetObjProperty(item, "damagemod", "of hardening");
  elseif(numb < 25)
    SetObjProperty(item, "damagemod", "of fortification");
  else
    SetObjProperty(item, "damagemod", "of invulnerability");
    if (numb>MAX_ARMOD)
      numb:=MAX_ARMOD;
    endif
  endif
 item.ar_mod := numb;
endfunction

function SilverMod(item)
  var hits := GetObjProperty(item, "OnHit");
  if(!hits)
    hits := {};
  endif
  hits.append(":combat:silverHit");
  SetObjProperty(item, "OnHit", hits);
  SetObjProperty(item, "silvermod", 1);
endfunction

function AddName(item)
  var currdesc := item.desc;
  if(currdesc[1] == "a")
    var space := find(item.desc, " ", 1);
    currdesc := currdesc[space+1,len(currdesc)];
  endif
  SetName(item, "magic " + currdesc);
endfunction
