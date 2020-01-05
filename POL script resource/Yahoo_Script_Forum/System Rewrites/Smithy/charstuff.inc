////////////////////////////////////
//
//charstuff.inc
//
//S!tH, 1/2/2001 (1st february)
//
//Functions:
//
//faceobject( who, object )
//
////////////////////////////////////

///////////////////////
//What we are gonna use
///////////////////////
use uo;
use os;

///////////////////////////
//faceobject( who, object )
//
//*should* make the player
//face the object.
//
//TODO:
//Does char need refreshing?
//Make code better :)
///////////////////////////
function faceobject( who, object )

Const North := 0;
Const South := 4;
Const East := 2;
Const West := 6;
Const NorEast := 1;
Const NorWest := 7;
Const SouEast := 3;
Const SouWest := 5;

Var newFacing := 0;

Var whoPos := {0,0};
whoPos[1] := who.x;
whoPos[2] := who.y;

Var objPos := {0,0};
objPos[1] := object.x;
objPos[2] := object.y;

Var distn := 0;
Var distw := 0;
Var dists := 0;
Var diste := 0;

//Do X
if( objPos[1] > whoPos[1] ) //Object is eastern.
	diste := objPos[1] - whoPos[1];
elseif( objPos[1] < whoPos[1] ) //Object is western.
	distw := whoPos[1] - objPos[1];
endif

//Do Y
if( objPos[2] > whoPos[2] ) //Object is southern.
	dists := objPos[2] - whoPos[2];
elseif( objPos[2] < whoPos[2] ) //Object is northen.
	distn := whoPos[2] - objPos[2];
endif

if( !distn && !distw && !dists && !diste )
	print( "returning! didnt get any values!");
	return; //the object is on top of the player!!
endif

if( distn && !distw && !dists && !diste )
	newFacing := North;
	who.facing := newFacing;
	return;
endif

if( dists && !distw && !distn && !diste )
	newFacing := South;
	who.facing := newFacing;
	return;
endif

if( diste && !distw && !dists && !distn )
	newFacing := East;
	who.facing := newFacing;
	return;
endif

if( distw && !distn && !dists && !diste )
	newFacing := West;
	who.facing := newFacing;
	return;
endif

if( distw && distn ) //therefore we cannot have s/e
	if ( ( distw / 2 ) >= distn ) //we should still face west.
		newFacing := West;
		who.facing := newFacing;
		return;
	elseif ( ( distn / 2 ) >= distw ) //we should still face north.
		newFacing := North;
		who.facing := newFacing;
		return;
	else
		newFacing := NorWest;
		who.facing := newFacing;
		return;
	endif
endif

if( diste && distn ) //therefore we cannot have s/w
	if ( ( diste / 2 ) >= distn ) //we should still face east.
		newFacing := East;
		who.facing := newFacing;
		return;
	elseif ( ( distn / 2 ) >= diste ) //we should still face north.
		newFacing := North;
		who.facing := newFacing;
		return;
	else
		newFacing := NorEast;
		who.facing := newFacing;
		return;
	endif
endif

if( distw && dists ) //therefore we cannot have n/e
	if ( ( distw / 2 ) >= dists ) //we should still face west.
		newFacing := West;
		who.facing := newFacing;
		return;
	elseif ( ( dists / 2 ) >= distw ) //we should still face south.
		newFacing := South;
		who.facing := newFacing;
		return;
	else
		newFacing := SouWest;
		who.facing := newFacing;
		return;
	endif
endif

if( diste && dists ) //therefore we cannot have n/w
	if ( ( diste / 2 ) >= dists ) //we should still face East.
		newFacing := East;
		who.facing := newFacing;
		return;
	elseif ( ( dists / 2 ) >= diste ) //we should still face south.
		newFacing := South;
		who.facing := newFacing;
		return;
	else
		newFacing := SouEast;
		who.facing := newFacing;
		return;
	endif
endif

print( "Hit end of faceobject. Shouldnt have." );
return; //Just in case

endfunction