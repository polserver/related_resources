use uo;
use os;
use math;
use basic;
use cfgfile;

var config := "hashcfg";
var element := "hash";

function hashing( newpassword )
 var password := lower( newpassword );
 var product := 1;
 if( find( password, "a", 1 ))
  var lookup := "a";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "b", 1 ))
  var lookup := "b";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "c", 1 ))
  var lookup := "c";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "d", 1 ))
  var lookup := "d";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "e", 1 ))
  var lookup := "e";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "f", 1 ))
  var lookup := "f";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "g", 1 ))
  var lookup := "g";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "h", 1 ))
  var lookup := "h";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "i", 1 ))
  var lookup := "i";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "j", 1 ))
  var lookup := "j";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "k", 1 ))
  var lookup := "k";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "l", 1 ))
  var lookup := "l";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "m", 1 ))
  var lookup := "m";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "n", 1 ))
  var lookup := "n";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "o", 1 ))
  var lookup := "o";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "p", 1 ))
  var lookup := "p";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "q", 1 ))
  var lookup := "q";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "r", 1 ))
  var lookup := "r";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "s", 1 ))
  var lookup := "s";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "t", 1 ))
  var lookup := "t";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "u", 1 ))
  var lookup := "u";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "v", 1 ))
  var lookup := "v";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "w", 1 ))
  var lookup := "w";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "x", 1 ))
  var lookup := "x";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "y", 1 ))
  var lookup := "y";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "z", 1 ))
  var lookup := "z";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "0", 1 ))
  var lookup := "0";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "1", 1 ))
  var lookup := "1";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "2", 1 ))
  var lookup := "2";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "3", 1 ))
  var lookup := "3";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "4", 1 ))
  var lookup := "4";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "5", 1 ))
  var lookup := "5";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "6", 1 ))
  var lookup := "6";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "7", 1 ))
  var lookup := "7";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "8", 1 ))
  var lookup := "8";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 if( find( password, "9", 1 ))
  var lookup := "9";
  var hashnum := gethashnum( lookup );
  product := product + hashnum;
 endif
 var hashpass := finishhash( product );
 return hashpass;
endfunction

function gethashnum( lookup )
 UnloadConfigFile( config );
 var hashfile := ReadConfigFile( config );
 var hashelem := FindConfigElem( hashfile, lookup );
 var hashnum := hashelem.value;
 return hashnum;
endfunction

function finishhash( product )
 var prodstr := CStr( product );
 var count := len( prodstr );
 var hashpass := count;
 var numbr := prodstr[count-1];
 numbr := CInt( numbr );
 hashpass := Pow( hashpass, numbr);
 numbr := prodstr[count-3];
 numbr := CInt( numbr );
 hashpass := Pow( hashpass, numbr);
 numbr := prodstr[count-4];
 numbr := CInt( numbr );
 hashpass := Pow( hashpass, numbr);
 return hashpass;
endfunction

function passcheck( pass, name )
 var acct := FindAccount( name );
 var acctpass := acct.getprop( "password" );
 var passhash := hashing( pass );
 if( passhash == acctpass )
  return 1;
 endif
endfunction