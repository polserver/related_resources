/* core.inc
 * Last Modified: 06/28/04
 *
 * Core constants and functions required for almost everything
 * to work. If you're going to change settings, this is the place
 * to do it.
 *
 * TODO:
 * Add variable for map size to dynamicly calculate stuff.
 *
 *
*/


function CSecToTime(sec, small := 0)

  var seconds := sec;
  var years   := (seconds - (seconds % (52 * 7 * 24 * 60 * 60))) / (52 * 7 * 24 * 60 * 60);
  seconds     := seconds - (years * 52 * 7 * 24 * 60 * 60);
  var weeks   := (seconds - (seconds % (7 * 24 * 60 * 60))) / (7 * 24 * 60 * 60);
  seconds     := seconds - (weeks * 7 * 24 * 60 * 60);
  var days    := (seconds - (seconds % (24 * 60 * 60))) / (24 * 60 * 60);
  seconds     := seconds - (days * 24 * 60 * 60);
  var hours   := (seconds - (seconds % (60 * 60))) / (60 * 60);
  seconds     := seconds - (hours * 60 * 60);
  var minutes := (seconds - (seconds % 60)) / (60);
  seconds     := seconds - (minutes * 60);

  if (small)
    var retstr;
    if (years)
      retstr := CStr(years + "y " + weeks + "w " + days + "d " + hours + "h " + minutes + "m " + seconds + "s");
    elseif (weeks)
      retstr := CStr(weeks + "w " + days + "d " + hours + "h " + minutes + "m " + seconds + "s");
    elseif (days)
      retstr := CStr(days + "d " + hours + "h " + minutes + "m " + seconds + "s");
    elseif (hours)
      retstr := CStr(hours + "h " + minutes + "m " + seconds + "s");
    elseif (minutes)
      retstr := CStr(minutes + "m " + seconds + "s");
    else
      retstr := CStr(seconds + "s");
    endif
    return retstr;
  endif

  return years + "y " + weeks + "w " + days + "d " + hours + "h " + minutes + "m " + seconds + "s";

endfunction


// Misc Constants
const DEBUG		:= 0;			// 1 = show debug messages on console


// URL constants (Change these if you are going to use PHP.)
const CHAR_SCR		:= "view_chars.php";	// Name of PHP/ecl script that calls view_chars
const GUILD_SCR		:= "view_guilds.php";	// Name of PHP/ecl script that calls view_guilds
const LOC_SCR		:= "view_locations.php";// Name of PHP/ecl script that calls view_locations


// Map View Constants
const IMG_URL		:= "http://tribulation.sytes.net/res/map.jpg"; // CHANGE THIS

const SHOW_PLAYER_LOC	:= 1;			// 1 = have link to view player locations
const SHOW_PLAYER_PROF	:= 1;			// Should player names link to profiles?
const SHOW_PLAYER_XY	:= 1;			// Show (x, y) cordinates next to name?

const SHOW_GUILD_LOC	:= 1;			// 1 = have link to view guild locations
const SHOW_GUILD_PROF	:= 1;			// 1 = have link to guild profiles
const SHOW_GUILD_XY	:= 1;			// 1 = show guildstone x y cords

const DOT_COLOR		:= "white";		// HTML color of the dot
const TEXT_COLOR	:= "white";		// HTML color of the text
const BORDER_COLOR	:= "white";		// HTML color of the borders
const VLINK		:= "white";		// HTML color of visited links
const ALINK		:= "white";		// HTML color of active links

const PLAYER_PROF_URL	:= CHAR_SCR + "?serial=";
const GUILD_PROF_URL	:= GUILD_SCR + "?guildid=";
const SREGIONS_URL	:= LOC_SCR + "?spawnregions=1";


// Web Profile Constants (Shouldn't have to change any of these.)
const PROP_NAME		:= "WebProfile";	// Property name for webprofile array
const PROFILE_PROPNAME  := "profileArray";	// Property name for character profile array

const MAX_PAGE_P	:= 25;			// Number of players to show per page
const MAX_PAGE_G	:= 25;			// Number of guilds to show per page


// Player Listing
const MAX_CMD_LVL	:= 6;   // Show only those up to this cmdlevel (0 = player, 5 = test)


// WebProp array indexes
const DATE_CREATED	:= 1;			// UNIX time()
const LAST_LOGIN	:= 2;			// UNIX time()
const LONGEST_ONLINE	:= 3;			// int
const NPCS_KILLED	:= 4;			// int
const DEATHS		:= 5;			// int
const VOMITS		:= 6;			// int
const LAST_LOGOFF	:= 7;			// UNIX time()
const TOTAL_ONLINE	:= 8;			// int