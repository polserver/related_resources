use uo;
use cfgfile;

function GetTime()

    local cfg := ReadConfigFile( "::days" );
    local elem := FindConfigElem( cfg , "WholeDay" );
    local length := GetConfigInt( elem , "Length" );
    local day_length := (60 * length);

//Print("DayLength: " + day_length);

    local x := readgameclock();

//Print("Read Game Clock: " + x);

    local bigpart := x / day_length;

//Print("Bigpart: " + bigpart);

    local smallpart := bigpart * day_length;
    x := (x - smallpart);

//Print("Time of Day: " + x);
//Print("The Day is " + day_length/60 + " minutes long.");

return ( x );

endfunction

function GetTransition()

    local cfg := ReadConfigFile( "::days" );
    local elem := FindConfigElem( cfg , "Transition" );
    local length := GetConfigInt( elem , "Length" );

    return length;
endfunction

function GetDayLength()

    local cfg := ReadConfigFile( "::days" );
    local elem := FindConfigElem( cfg , "WholeDay" );
    local length := GetConfigInt( elem , "Length" );

    return length;
endfunction

// Returns time in the format "hour:minutes", where hour = 00-23
function GetTimeofDay()

    local time_sec := GetTime();
    local length := (GetDayLength() * 60) * 1.0 ;

    local temp := length / time_sec;
    local raw_time := 24.0 / temp;

    local hours := cint(raw_time);
    local remainder := raw_time - hours;
    local minutes := cint( remainder * 60 );

    if( len(cstr(minutes)) = 1 )
	minutes := "0" + cstr(minutes);
    endif

    if( len(cstr(hours)) = 1 )
	hours := "0" + cstr(hours);
    endif

    return (hours+":"+minutes);

endfunction

// Returns a number of the hour of the day (1-24);
function GetHourOfDay()
    var time := GetTimeOfDay();
    var colon := find(time, ":", 1);

	return CInt(time[1, colon]);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Returns true if the hour is within
//			the specified range (inclusive).
// Params:  hr			Hour to check for.
//			hrstart		Start hr.
//			hrend		Ending hr.
// Returns: 1		Hour is within range.
//			0		Hour is outside range
///////////////////////////////////////////////////////////
function HourWithinRange(hr, hrstart, hrend)
	hr := CInt(hr) + 24;
	hrstart := CInt(hrstart) + 24;
	hrend := CInt(hrend) + 24;

	if (hrstart > hrend)
		if (hr >= hrstart or hr < hrend)
			return 1;
		endif
	else
		if (hr >= hrstart and hr <= hrend)
			return 1;
		endif
	endif

	return 0;
endfunction