//
// Copyright (C) 2002 Jouni Airaksinen, Mintus@Codefield.com
//
// This include contains some functions to perform string manipulation
//
// TODO : fast version of CPadStr
//

// functions //

//
// function StringOfChar()
//
// Returns string of some char.
// Does not do check on Char - this for effiency.
//
function StringOfChar(Length, Char)
  var R := Char;
  if (Length > 1)
    var I;
    for (I := 1; I < Length; I + 1)
      R := R + Char;
    endfor
  endif
  return R;
endfunction

//
// function CPadStr()
//
// Pads string with given char (defaults to "0").
//
function CPadStr(Value, Length, PadChar := "0")
  Value := CStr(Value);
  if (len(Value) < Length)
    Value := StringOfChar(Length - len(Value), PadChar) + Value;
  endif
  return Value;
endfunction

//
// function CleanUp()
//
// Trims leading commas and spaces and ending spaces from a string.
// Useful eg. with title_prefix, title_suffix properties.
//
function CleanUp(Text)
  if (Text = error)
    Text := "";
  endif
  var I;
  var S := 1;
  // trim leading "," and " "
  for (I := 1; I <= len(Text); I := I + 1) 
    if (!(Text[I] in {",", " "}))
      break;
    endif
    S := S + 1;
  endfor
  Text := Text[S, len(Text)];
  
  // trim ending " "
  var E := len(Text);
  for (I := E; I > 0; I := I - 1)
    if (Text[I] != " ")
      E := I;
      break;
    endif
  endfor
  return Text[1, E];
endfunction