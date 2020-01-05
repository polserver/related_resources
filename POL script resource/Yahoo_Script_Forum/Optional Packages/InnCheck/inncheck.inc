use uo;
use os;
use cfgfile;
use util;

function Inncheck(character)

  local element, rect;
  local cfgfile := ReadConfigFile("::innlocation");
  local entries := GetConfigStringKeys(cfgfile);
  foreach listing in entries
    element :=  cfgfile[listing];
    rect := element.rect;
    rect := SplitWords(rect);
    if((character.x >= Cint(rect[1])) and (character.x <= Cint(rect[3])) and (character.y >= Cint(rect[2])) and (character.y <= Cint(rect[4])))
      return 1;
      break;
    endif
  endforeach
  return 0;

endfunction  