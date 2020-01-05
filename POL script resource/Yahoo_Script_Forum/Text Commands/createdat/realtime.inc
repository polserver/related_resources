use uo;

//	Ekaterinburg time, that is +2 to MSK, or +5 to GMT
const TIMEZONE := 21600;

// Winter time
//const TIMEZONE := 18000;

//	MSK time
//const TIMEZONE := 14400;

/////////////////////////
function DateTime(secs)
/////////////////////////

        var u, t;
        secs := secs + TIMEZONE;

        // seconds
        t := secs % 60;
        secs := (secs-t) / 60;
        if( t >= 10 )
                u := ":" + t;
        else
                u := ":0" + t;
        endif

        // minutes
        t := secs % 60;
        secs := (secs-t) / 60;
        if( t >= 10 )
                u := ":" + t + u;
        else
                u := ":0" + t + u;
        endif

        // hours
        t := secs % 24;
        secs := (secs-t) / 24;
        if( t >= 10 )
                u := " " + t + u;
        else
                u := " 0" + t + u;
        endif

        var year ;

        var YEAR_2000 := 10957;
        var YEAR_FOUR := 1461;
        var YEAR_LEAP := 366;
        var YEAR_NORMAL := 365;
        var MONTHS := { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        secs := secs + 1;
        t := 1;

        if( secs > YEAR_2000 ) // isLeapYear
                year := 2000;
                secs := secs - YEAR_2000;
        else
                year := 1970;
        endif
        while( secs > YEAR_FOUR )
                secs := secs - YEAR_FOUR;
                year := year + 4;
        endwhile
        if( secs > YEAR_LEAP )
                secs := secs - YEAR_LEAP;
                year := year + 1;
        endif
        while( secs > YEAR_NORMAL )
                secs := secs - YEAR_NORMAL;
                year := year + 1;
        endwhile
        if( (year % 4 = 0) )
                MONTHS[2]:=29;
        endif
        while( secs > MONTHS[t] )
                secs := secs - MONTHS[t];
                t := t + 1;
        endwhile

        if( secs >= 10 )
                u := "-" + secs + u;
        else
                u := "-0" + secs + u;
        endif

        if( t >= 10 )
                u := "-" + t + u;
        else
                u := "-0" + t + u;
        endif

        u := year + u;       

        return u;

endfunction

////////////////////////////
function dayhourtime (secs)
////////////////////////////

   var h:= CInt( secs/3600);
   var d := CInt(h/24);
   h:= h - (d * 24);
   var u, v;
   if  ( d != 1 ) u := "s "; else u := " "; endif
   if  ( h != 1 ) v := "s "; else v := " "; endif
   var text := d + " day" + u + h + " hour" + v ;
   return text;
endfunction

/////////////////////////////
function DateTimeShort (secs)
/////////////////////////////

        var u, t;
	t := "";
	u := "";
        secs := secs + TIMEZONE;

        // seconds
        t := secs % 60;
        secs := (secs-t) / 60;
//        if( t >= 10 )
//                u := ":" + t;
//        else
//                u := ":0" + t;
//        endif

        // minutes
        t := secs % 60;
        secs := (secs-t) / 60;
        if( t >= 10 )
                u := ":" + t + u;
        else
                u := ":0" + t + u;
        endif

        // hours
        t := secs % 24;
        secs := (secs-t) / 24;
        if( t >= 10 )
                u := "/" + t + u;
        else
                u := "/0" + t + u;
        endif


        var year ;

        var YEAR_2000 := 10957;
        var YEAR_FOUR := 1461;
        var YEAR_LEAP := 366;
        var YEAR_NORMAL := 365;
        var MONTHS := { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        secs := secs + 1;
        t := 1;

        if( secs > YEAR_2000 ) // isLeapYear
                year := 2000;
                secs := secs - YEAR_2000;
        else
                year := 1970;
        endif
        while( secs > YEAR_FOUR )
                secs := secs - YEAR_FOUR;
                year := year + 4;
        endwhile
        if( secs > YEAR_LEAP )
                secs := secs - YEAR_LEAP;
                year := year + 1;
        endif
        while( secs > YEAR_NORMAL )
                secs := secs - YEAR_NORMAL;
                year := year + 1;
        endwhile
        if( (year % 4 = 0) )
                MONTHS[2]:=29;
        endif
        while( secs > MONTHS[t] )
                secs := secs - MONTHS[t];
                t := t + 1;
        endwhile

        // # of the month
        if( t >= 10 )
                u := "." + t + u;
        else
                u := ".0" + t + u;
        endif

	// day of the month
        if( secs >= 10 )
                u := secs + u;
        else
                u := "0" + secs + u;
        endif

//        u := year + u;       

        return u;

endfunction


/////////////////////////////
function DateTimer (secs)
/////////////////////////////

        var u, t;
	t := "";
	u := "";
//        secs := secs + TIMEZONE;

        // seconds
        t := secs % 60;
        secs := (secs-t) / 60;
        if( t >= 10 )
                u := ":" + t;
        else
                u := ":0" + t;
        endif

        // minutes
        t := secs % 60;
        secs := (secs-t) / 60;
        if( t >= 10 )
                u := ":" + t + u;
        else
                u := ":0" + t + u;
        endif

        // hours
/*
        t := secs % 24;
        secs := (secs-t) / 24;
        if( t >= 10 )
                u := "/" + t + u;
        else
                u := "/0" + t + u;
        endif

        u := secs+" "+u;
*/
		  u := "" + secs + u;
        
        return u;

endfunction
