//
// Copyright (C) 2002 Jouni Airaksinen, Mintus@Codefield.com
//
// This include contains some functions to perform date and time conversions
//
// TODO : Date formatting
//

// uses and includes //

include "DateConsts";
include "StringUtils";

// constants //

// polcore().systime is based to, January 1th 1970 (00:00 Greenwich Time ?)
const DateDelta := 719163; // days since 1/1/0001 till 1/1/1970

const SECONDS_IN_MINUTE := 60;
const HOURS_IN_DAY := 24;
const MINUTES_IN_HOUR := 60;

const SECONDS_IN_HOUR := SECONDS_IN_MINUTE * MINUTES_IN_HOUR;
const SECONDS_IN_DAY := SECONDS_IN_HOUR * HOURS_IN_DAY;

const AVERAGE_MONTH_LENGTH := 30.4375; // 4 year period
const AVERAGE_YEAR_LENGTH := 365.25;   // 4 year period

// arrays //

// The MonthDays array can be used to quickly find the number of
//  days in a month:  MonthDays[IsLeapYear(Y) + 1][M]

var MonthDays := array ( 
  array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31),
  array(31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31));

// Lookup arrays for month and day names (short and long versions available).
// To localize these edit DateConsts.inc.

var ShortMonthNames := array(
  SShortMonthNameJan,  SShortMonthNameFeb,  SShortMonthNameMar,  SShortMonthNameApr,
  SShortMonthNameMay,  SShortMonthNameJun,  SShortMonthNameJul,  SShortMonthNameAug,
  SShortMonthNameSep,  SShortMonthNameOct,  SShortMonthNameNov,  SShortMonthNameDec);
  
var LongMonthNames := array(
  SLongMonthNameJan,  SLongMonthNameFeb,  SLongMonthNameMar,  SLongMonthNameApr,
  SLongMonthNameMay,  SLongMonthNameJun,  SLongMonthNameJul,  SLongMonthNameAug,
  SLongMonthNameSep,  SLongMonthNameOct,  SLongMonthNameNov,  SLongMonthNameDec);

var ShortDayNames := array(
    SShortDayNameSun, SShortDayNameMon, SShortDayNameTue, SShortDayNameWed,
    SShortDayNameThu, SShortDayNameFri, SShortDayNameSat);

var LongDayNames := array(
    SLongDayNameSun, SLongDayNameMon, SLongDayNameTue, SLongDayNameWed,
    SLongDayNameThu, SLongDayNameFri, SLongDayNameSat);


// functions //

//
// function IsLeapYear()
//
// Returns 1 if given year is a leap year, otherwise 0 (that is True/False)
//
function IsLeapYear(Year)
  return ((Year % 4) = 0) and (((Year % 100) <> 0) or ((Year % 400) = 0));
endfunction

//
// function DaysInYear()
//
// Returns number of days in given year.
//
function DaysInYear(Year)
  return (365 + IsLeapYear(Year));
endfunction

//
// function DaysOfWeek()
//
// Returns index to day of weeks array of the given time.
//
// eg. LongDayNames[DayOfWeek(polcore().systime)]
// would return the current day of week as a string.
//
function DayOfWeek(Time)
  return ((CInt(Time / SECONDS_IN_DAY) + DateDelta) % 7) + 1;
endfunction

//
// function CTimeStr()
//
// Returns current date part of the polcore().systime
//
function CDateStr(Time)
  var Year, Month, Day;
  DecodeDate(Time, Year, Month, Day);  
  return CStr(Year) + DateSeparator + CPadStr(Month, 2) + DateSeparator + CPadStr(Day, 2);
endfunction

//
// function CTimeStr()
//
// Returns current time part of the polcore().systime
//
function CTimeStr(Time)
  var Hour, Minute, Second;
  DecodeTime(Time, Hour, Minute, Second);
  return CPadStr(Hour, 2) + TimeSeparator + CPadStr(Minute, 2) + TimeSeparator + CPadStr(Second, 2);
endfunction

//
// function CDateTimeStr()
//
// Does same as two functions above, but returns both.
//
// Notes: Does not use above functions by design.
//
function CDateTimeStr(Time)
  var Year, Month, Day;
  var Hour, Minute, Second;
  DecodeDate(Time, Year, Month, Day);  
  DecodeTime(Time, Hour, Minute, Second);
  return CStr(Year) + DateSeparator + CPadStr(Month, 2) + DateSeparator + CPadStr(Day, 2) + "  " + 
    CPadStr(Hour, 2) + TimeSeparator + CPadStr(Minute, 2) + TimeSeparator + CPadStr(Second, 2);
endfunction

//
// function CDateTimeCounterStr()
//
// Converts Time (seconds) to counter string.
// eg. with 100 seconds function would return string "1 mins, 40 secs".
//
// TODO : Custom formatting string
//
function CDateTimeCounterStr(Time, ShowDays := 1, ShowHours := 1, ShowMinutes := 1, ShowSeconds := 1)
  var Days := CInt(Time / SECONDS_IN_DAY);
  Time := CInt(Time % SECONDS_IN_DAY);
  var Hour := CInt(Time / SECONDS_IN_HOUR);
  var Second := CInt(Time % SECONDS_IN_HOUR);
  var Minute := CInt(Second / SECONDS_IN_MINUTE);
  Second := CInt(Second % SECONDS_IN_MINUTE);
  var R := "";
  if (ShowDays) 
    R := CStr(Days) + " days";
  endif
  if (ShowHours) 
    R := R + ", " + CStr(Hour) + " hours";
  endif
  if (ShowMinutes) 
    R := R + ", " + CStr(Minute) + " mins";
  endif
  if (ShowSeconds) 
    R := R + ", " + CStr(Second) + " secs";
  endif
  return R;
endfunction

//
// function DivMod()
//
// Does division and returns result and reminder.
// Used internally. Should be moved to separate Maths.inc
//
function DivMod(Dividend, Divisor, byref Result, byref Remainder)
  Result := 0;
  Remainder := 0;
  if (Divisor)
    Result := CInt(Dividend / Divisor);
    Remainder := CInt(Dividend % Divisor);
  endif
endfunction

//
// function DecodeTime()
//
// Used internally to decode Time to Hours, Minutes and Seconds.
//
function DecodeTime(Time, byref Hour, byref Minute, byref Second)
  Time := CInt(Time % SECONDS_IN_DAY); // ingore beyond one day
  Hour := CInt(Time / SECONDS_IN_HOUR);
  Second := CInt(Time % SECONDS_IN_HOUR);
  Minute := CInt(Second / SECONDS_IN_MINUTE);
  Second := CInt(Second % SECONDS_IN_MINUTE);  
endfunction

//
// function DecodeDate()
//
// Used internally to decode Time to Years, Months and Days.
//
const D1 := 365;
const D4 := D1 * 4 + 1;
const D100 := D4 * 25 - 1;
const D400 := D100 * 4 + 1;

//function DecodeDate(Time, byref Year, byref Month, byref Day, byref DOW, byref Reminder)
function DecodeDate(Time, byref Year, byref Month, byref Day)
//  Reminder := CInt(Time % SECONDS_IN_DAY);
  
  var T := CInt(Time / SECONDS_IN_DAY) + DateDelta;
  if (T <= 0)
    Year := 0;
    Month := 0;
    Day := 0;
//    DOW := 0;
  else
//    DOW := T % 7;
    T := T - 1;
    // Calculate years. Meaning of D??? is to take care of leapyears.
    var Y := 1;
    while (T >= D400)
      T := T - D400;
      Y := Y + 400;
    endwhile
    var I, D;
    DivMod(T, D100, I, D);
    if (I = 4)
      I := I - 1;
      D := D + D100;
    endif    
    Y := Y + (I * 100);
    DivMod(D, D4, I, D);
    Y := Y + (I * 4);
    DivMod(D, D1, I, D);
    if (I = 4)
      I := I - 1;
      D := D + D1;
    endif
    Y := Y + I;    
    // Reminder has months and days.
    var IsLeap := IsLeapYear(Y) + 1;
    var M := 1;
    while (1)
      I := MonthDays[IsLeap][M];
      if (D < I) break; endif
      D := D - I;
      M := M + 1;
    endwhile
    Year := Y;
    Month := M;
    Day := D + 1;
  endif
endfunction