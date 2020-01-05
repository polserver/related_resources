Const MOVING_EFFECT_PURPLE_POTION  := 0x0F0D; 
Const SOUND_EFFECT_EXPLOSION	:= 0x208; 
Const EFFECT_EXPLOSION := 0x36b0;

function GonnaBlow( potion )
	local bomb_flag := cint( GetObjProperty( potion, "#explode" ));
	
	if ( bomb_flag )	// forcing it to be true or false, mebe not nessesary
		return(1);
	else
		return(0);
	endif 
endfunction

function SetBlowFlag( potion, val )
	local bomb_flag := val;
	
	SetObjProperty( potion, "#explode", bomb_flag );
endfunction

function ToggleBlowFlag( potion )
	local bomb_flag := cint( GetObjProperty( potion, "#explode" ) );
	
	if ( !bomb_flag )	// bogus check
		bomb_flag := 0;
	endif
	
	if ( bomb_flag ) 	// invert bomb_flag
		SetObjProperty( potion, "#explode", (!bomb_flag) );
		return(0);
	else
		eraseObjProperty( potion, "#explode" );
		return(1);
	endif
endfunction

function can_throw_there( character, cast_on, potion )
	
	if ( !potion )
		return(0);
	endif
	
	if (!CheckLosAt( character, cast_on.x, cast_on.y, cast_on.z ) )
                //print("returning 0"); 	//debug
                return(0);	//force false
        else
       		//print("returning 1");	//debug
       		return(1);	//force true
	endif
endfunction   

function throw_explosive( character, potion, tgt )
	
	if ( !potion )
		return(0);
	endif
	
	PlayMovingEffectxyz( character.x, character.y, character.z+15, tgt.x, tgt.y, tgt.z, MOVING_EFFECT_PURPLE_POTION, 8, 0, 0 ); 
	//print("playing effect");	//debug
	MoveItemToLocation( potion, tgt.x, tgt.y, tgt.z, MOVEITEM_NORMAL );
	return(1);
endfunction

/*		
 mebbe use

PlayStationaryEffect( x, y, z, effect, speed, loop := 0, explode := 0 );
ListMobilesNearLocationEx( x,y,z, range, flags );
MoveItemToLocation( item, x, y, z, flags );
PrintTextAbove( above_object, text ); 
ApplyDamage( mobile, damage );
ApplyRawDamage( character, hits ); // raw damage (ignores armor etc)
CheckLineOfSight( object1, object2 );
DestroyItem( item );
GetObjProperty( object, property_name );
GetObjType( object );
ListMobilesNearLocation( x, y, z, range );
PlayMovingEffect( source, target, effect, speed, loop := 0, explode := 0 );
PlayObjectCenteredEffect( center, effect, speed, loop := 0 );
PlaySoundEffect( character, effect );
SetObjProperty( object, property_name, property_value_string_only );
TargetCoordinates( by_character ); // returns struct(x,y,z) 
const TGTOPT_CHECK_LOS   := 0x0001;
const TGTOPT_NOCHECK_LOS := 0x0000; // in case you want to be explicit

const TGTOPT_HARMFUL     := 0x0002;
const TGTOPT_NEUTRAL     := 0x0000;
const TGTOPT_HELPFUL     := 0x0004;

Target( by_character, options := TGTOPT_CHECK_LOS+TGTOPT_NEUTRAL);

const MOVECHAR_FORCELOCATION := 0x40000000;
const MOVEITEM_NORMAL        := 0;
const MOVEITEM_FORCELOCATION := 0x40000000;
*/