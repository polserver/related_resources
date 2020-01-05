use uo;
use math;

const MM:=2147483647; // a Mersenne prime
const AA:=48271; // does well in spectral test
const QQ:=44488; // M/A
const RR:=3399; // M%A


// calculates next number in the sequence
// always in (0 -> 0x7FFFFFFF)
function BaseRandom()

	var X := CInt( GetGlobalProperty("randomeroseed") );
	X := AA * (X%QQ) - RR * (X/QQ);
	if(X<0)
		X:=X+MM;
	endif
	SetGlobalProperty("randomeroseed", X);
	return X;

endfunction


// return a number in the range [0 -> modulo-1]
// modulo can't be too high, don't use modulo > 2^28
function Random( modulo )

	return ( BaseRandom() % modulo );

endfunction


// throws "dices" dices with "faces" faces plus a "bonus" bonus
// as in AD&D's dicesDfaces+bonus (ie RandomDice(2,10,3)=>"2d10+3")
function RandomDice(dices, faces, bonus)

	var r := bonus;
	for i := 1 to dices
		r := r + Random(faces) + 1;
	endfor
	return r;

endfunction


// makes a random diceroll, string-based, dicesDfaces+bonus (ex. 3D6+4)
function RandomDiceStr( dice_str )

	var space	:= Find( dice_str , "d" , 1 );
	var space2a	:= Find( dice_str , "+" , space+1 );
	var space2b	:= Find( dice_str , "-" , space+1 );
	var dice_a	:= Cint( dice_str[1, space-1] );
	var bonus	:= 0;
	var dice_t;

	if( (!space2a) & (space2b) )
		space2a := space2b;
	endif

	if( !space )
		return Cint(dice_str);
	endif

	if( !space2a )
		dice_t := Cint( dice_str[space+1, len(dice_str)-space] );
	else
		dice_t := Cint( dice_str[space+1, (space2a-space-1)] );
		bonus  := Cint( dice_str[space2a+1, len(dice_str)-space2a]) ;
	endif

	if( space2b )
		bonus := 0 - bonus;
	endif

	//inlined return(RandomDice(dice_a, dice_t, bonus));
	var r := bonus;
	for i:=1 to dice_a
		r := r + Random(dice_t) + 1;
	endfor
	return r;

endfunction


// uniform distribution (0.0 -> 1.0)
function RandomFloat()

	return CDbl( BaseRandom() / 0x7FFFFFFF );

endfunction


// normal distribution with mean 0.0 and variance 1.0:
//   (-.25 -> +.25) with  19.741265%
//   (-.50 -> +.50) with  38.292492%
//   (-.75 -> +.75) with  54.674530%
//   (-1.0 -> +1.0) with  68.268949%
//   (-1.5 -> +1.5) with  86.638560%
//   (-2.0 -> +2.0) with  95.449974%
//   (-3.0 -> +3.0) with  99.730020%
//   (-4.0 -> +4.0) with  99.993666%
//   (-inf -> +inf) with 100.000000%
// note: it generates TWO values at a time, the second one is saved for later
var normal_value := "n";
function RandomStandardNormal()

	if( normal_value != "n" )
		var t := normal_value;
		normal_value := "n";
		return t;
	endif

	var u, v, s;
	repeat
		u := RandomFloat() * 2 - 1;
		v := RandomFloat() * 2 - 1;
		s := u * u + v * v;
	until( s < 1.0 );

	if( s = 0.0 )
		normal_value := 0.0;
		return( 0.0 );
	else
		s := Sqrt( -2 * LogE(s) / s );
		normal_value := v * s;
		return ( u * s );
	endif

endfunction


// (avg-.25*dev -> avg+.25*dev) with  19.741265%
// (avg-.50*dev -> avg+.50*dev) with  38.292492%
// (avg-.75*dev -> avg+.75*dev) with  54.674530%
// (avg-1.0*dev -> avg+1.0*dev) with 	68.268949%
// (avg-1.5*dev -> avg+1.5*dev) with 	86.638560%
// (avg-2.0*dev -> avg+2.0*dev) with 	95.449974%
// (avg-3.0*dev -> avg+3.0*dev) with 	99.730020%
// (avg-4.0*dev -> avg+4.0*dev) with 	99.993666%
// (   -inf*dev ->    +inf    ) with 100.000000%
function RandomNormal(avg, dev)

	return ( avg + RandomStandardNormal() * dev );

endfunction