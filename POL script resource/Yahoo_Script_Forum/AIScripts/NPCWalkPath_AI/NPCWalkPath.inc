use npc;
use util;
use os;
use uo;
use basic;

Function NPCWalkPath ( Who )

// Error checking

var rulenum := GetProperty( "NpcPathRule" );

if (!rulenum)
	SetProperty( "NpcPathRule", 1 );
	rulenum := 1;
endif

var pathname := GetProperty( "NPCPath" );

if (!pathname)
	return;
endif

var NPCPathList := GetGlobalProperty ( pathname );

if (!npcpathlist)
	return;
endif

// Get Rule elements - NPCListRule { NPCListRule[1], NPCListRule[2], NPCListRule[3] }
//                                      NX                NY               Z

var NPCListRule := NPCPathList[ rulenum ];

//print( "NPCListRule=" + npclistrule );

var nx := NPCListRule[1];
var ny := NPCListRule[2];
var z := NPCListRule[3];

//print( "nx=" + nx + " ny=" + ny + " z=" + z );

var failures := 0;

var t := 0;
var i := 0;
var speed := 0;


// MAKE! sure if it is not a movement statement that t := 1!!!
Case (nx)
	"action":

		for( i := 0; i < z; i := i + 1 )
			PerformAction( who, ny );
			sleep(1);
		endfor
		t := 1;

	"color":

		who.color := ny;
		t := 1;

	"facing":

		who.facing := ny;
		t := 1;

	"graphic":

		who.graphic := ny;
		t := 1;

	"pause":

		sleep(ny);
		t := 1;

	"rename":

		who.name := ny;
		t := 1;

	"run":

		speed := 1;

	"say":
		say ( ny );
		t := 1;

	"sfx":

		for( i := 0; i < z; i := i + 1 )
			PlaySoundEffect( who, ny );
			sleep(1);
		endfor

		t := 1;

	"walk":

		speed := 0;

endcase

// Default is walk (t = 0)
if (t = 0)

	while (who.x != ny or who.y != z)
		var olddistance := DistanceToLocation( who , ny, z );

		if (speed = 0)
			WalkTowardLocation( ny,z );
		else
			RunTowardLocation( ny,z );
		endif

		sleepms(10);

		var newdistance := DistanceToLocation( who , ny, z );

		var diff := newdistance - olddistance;

		If (diff = 0)
			failures := failures + 1;
			if (failures >= 10)
				failures := 0;
				say( "Time to move along..." );
				break;
			endif
		else
			failures := 0;
		endif

//Print ( "Who.x= " + who.x + " who.y= " + who.y + "Failes: " + failures );
//Print ( "ny=" + ny + " z=" + z );

	endwhile
endif

// Increment Path Rule # (rulenum)
rulenum := rulenum +1;
if (rulenum > NPCPathList.size())
	rulenum := 1;
endif
SetProperty( "NpcPathRule", rulenum );

endfunction


// This function check the distance from a mobile to an (X , y) Formated location

function DistanceToLocation ( who, locx, locy )

	var npcx := who.x;
	var npcy := who.y;

	Var xdiff := abs(who.x - locx);
	var ydiff := abs(who.y - locy);

	if (xdiff > ydiff)
		return xdiff;
	else
		return ydiff;
	endif

endfunction

// This function returns the variable as a possitive

function abs(x)
	if (x>=0)
		return x;
	else
		return -x;
	endif
endfunction
