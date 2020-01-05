/* webProfile.inc
 * Last Modified: 06/28/04
 *
 * All of the funtions and variables needed for webview to work.
 * If you're going to modify the webview package, this would be
 * a good place to start.
 *
 * TODO:
 *
*/

include ":webview:core";


// Define default webprop just in case it's needed
var default_webprop  := { Polcore().systime, Polcore().systime, 0, 0, 0, 0, 0, 0 };


// *** Get Functions ***
function GetProfile(who)

  var parray := array;

  // Get the profile CProp
  parray := GetObjProperty(who, "profileArray");
    
  // Oops, no profile.
  if (!parray)
    parray := { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
    SetObjProperty(who, PROFILE_PROPNAME, parray);
    return "No profile available.";
  endif     

  return parray;

endfunction


function GetWebArray(who)

  var parray := array;
  parray := GetObjProperty(who, PROP_NAME);

  if (DEBUG)
    print("DEBUG: GetWebArray - parray: " + parray);
  endif

  // If the character has no webprofile, setup the default
  if (!parray)
    SetObjProperty(who, PROP_NAME, default_webprop);
    parray := GetObjProperty(who, PROP_NAME);
  endif

  return parray;

endfunction


function GetWebProp(who, index)

  var parray := array;

  parray := GetWebArray(who);

  if (DEBUG)
    print("DEBUG: GetWebProp - parray[" + index + "]: " + parray[index]);
  endif

  return parray[index];

endfunction



function SetDateCreated(who)

  var parray := array;

  parray := GetWebArray(who);
  parray[DATE_CREATED] := Polcore().systime;
  SetObjProperty(who, PROP_NAME, parray);

endfunction


function SetLastLogin(who)

  var parray := array;

  parray := GetWebArray(who);
  parray[LAST_LOGIN] := Polcore().systime;
  SetObjProperty(who, PROP_NAME, parray);

endfunction


function SetLongestOnline(who)

  var parray := array;
  var sessiontime := ReadGameClock() - GetObjProperty(who,"logontime");

  parray := GetWebArray(who);

  if (parray[LONGEST_ONLINE] < sessiontime)
    parray[LONGEST_ONLINE] := sessiontime;
  endif

  SetObjProperty(who, PROP_NAME, parray);

endfunction


function SetLastLogoff(who)

  var parray := array;

  parray := GetWebArray(who);
  parray[LAST_LOGOFF] := Polcore().systime;
  SetObjProperty(who, PROP_NAME, parray);

endfunction



function IncreaseNPCKills(who)

  var parray := array;

  parray := GetWebArray(who);
  parray[NPCS_KILLED] := parray[NPCS_KILLED] + 1;
  SetObjProperty(who, PROP_NAME, parray);

endfunction


function IncreaseTotalOnline(who)

  var parray := array;
  var sessiontime := ReadGameClock() - GetObjProperty(who,"logontime");

  if (DEBUG)
    print ("DEBUG: IncreaseTotalOnline - sessiontime: " + parray[TOTAL_ONLINE] + sessiontime);
  endif

  parray := GetWebArray(who);
  parray[TOTAL_ONLINE] := parray[TOTAL_ONLINE] + sessiontime;
  SetObjProperty(who, PROP_NAME, parray);

endfunction


function IncreaseDeaths(who)

  var parray := array;

  parray := GetWebArray(who);
  parray[DEATHS] := parray[DEATHS] + 1;
  SetObjProperty(who, PROP_NAME, parray);

endfunction


function ViewWebProfile(who_serial)

  var who := SystemFindObjectBySerial(CInt(who_serial), SYSFIND_SEARCH_OFFLINE_MOBILES);

  if (who == error)
    WriteHtml("That character does not exist.<br>");
    return;
  endif

  var sessionTime := ReadGameClock() - GetObjProperty(who,"logontime");
  var p := "";

  if (GetObjProperty(who, "LoggedIn"))
    p := p + "<tr><td>Currently Online:</td><td><font color=\"red\"><b>Yes</b></font></td></tr>\n";
  else
    p := p + "<tr><td>Currently Online:</td><td><b>No</b></td></tr>\n";
  endif

  p := p + "<tr><td>Date Created:</td><td>" + CDateTimeStr(GetWebProp(who, DATE_CREATED)) + "</td></tr>\n";
  p := p + "<tr><td>Last Login:</td><td>" + CDateTimeStr(GetWebProp(who, LAST_LOGIN)) + "</td></tr>\n";

  if (GetObjProperty(who, "LoggedIn"))
    p := p + "<tr><td>Online Time:</td><td>" + CSecToTime(sessionTime, 1) + "</td></tr>\n";
  endif

  p := p + "<tr><td>Longest Online Time:</td><td>" + CSecToTime(GetWebProp(who, LONGEST_ONLINE), 1) + "</td></tr>\n";
  p := p + "<tr><td>Total Online Time:</td><td>" + CSecToTime(GetWebProp(who, TOTAL_ONLINE), 1) + "</td></tr>\n";
  p := p + "<tr><td>NPCs Killed:</td><td>" + GetWebProp(who, NPCS_KILLED) + "</td></tr>\n";
  p := p + "<tr><td>Deaths:</td><td>" + GetWebProp(who, DEATHS) + "</td></tr>\n";

  if (who.guild)
    p := p + "<tr><td>Guild:</td><td><a href=\"" + GUILD_PROF_URL + who.guildid + "\">" +
      who.guild.GetProp("guildname") + "</a></td></tr>\n";
  endif

  p := p + "<tr><td>Profile:</td><td>" + PlayerProfile(who) + "</td></tr>\n";

  var view_loc;

  if (SHOW_PLAYER_LOC)
    view_loc := " | <a href=\"" + LOC_SCR + "\?players=1\" target=\"_blank\">Player Locations</a>";
  endif

  WriteHtml("<font size=\"+1\"><b>Player profile: " + who.name + "</b></font><br>" +
    "<blockquote>" +
    "<table border=\"1\" cellspacing=\"0\" cellpadding=\"10\" bordercolor=\"#9c3010\" width=\"400\">" +
    p + 
    "</table>\n" +
    "</blockquote>\n" +
    "<br><br>\n\n<a href=\"" + CHAR_SCR + "\">Show All Characters</a>" + view_loc);

endfunction


function PlayerProfile(who)

  var prof := "";

  foreach line in GetProfile(who)
    if (line)
      prof := prof + CStr(line) + "<br>\n";
    endif
  endforeach

  if (prof)
    return prof;
  else
    return "This character has no profile.";
  endif

endfunction


function OutputPages(slist, max_page)

  var i, p := 1;
 
  WriteHtml("Page: ");

  if (CInt(opt[PAGE]) == p)
    WriteHtml("<a href=\"" + REQ + get[VIEW] + get[START] +
      get[SORT] + get[REVERSE] + get[QUERY] + "&page=" + p + "\"><b>" + p + "</b></a>");
  else  
    WriteHtml("<a href=\"" + REQ + get[VIEW] + get[START] +
      get[SORT] + get[REVERSE] + get[QUERY] + "&page=" + p + "\">" + p + "</a>");
  endif

  for (i := (len(slist) - max_page); i >= 0; i := i - max_page)
    p := p + 1;

    if (CInt(opt[PAGE]) == p)
      WriteHtml(", <a href=\"" + REQ + get[VIEW] + get[START] + 
        get[SORT] + get[REVERSE] + get[QUERY] + "&page=" + p + "\"><b>" + p + "</b></a>");
    else
      WriteHtml(", <a href=\"" + REQ + get[VIEW] + get[START] +
        get[SORT] + get[REVERSE] + get[QUERY] + "&page=" + p + "\">" + p + "</a>");
    endif

    sleepms(10);
  endfor

  WriteHtml("<br><br>\n\n");

endfunction


function GetParams(guild_view := 0)

  var params := array;

  if (!guild_view)
    if (QueryParam("view") == "all" || !QueryParam("view"))
      params[VIEW] := "all";
    elseif (QueryParam("view") == "online")
      params[VIEW] := "online";
    endif
  endif

  // can enter invalid start
  if (QueryParam("start"))
    params[START] := QueryParam("start");
  else
    params[START] := "";
  endif

  // can enter invalid sort
  if (QueryParam("sort"))
    params[SORT] := QueryParam("sort");
  else
    params[SORT] := "name";
  endif

  if (QueryParam("query"))
    params[QUERY] := QueryParam("query");
  else
    params[QUERY] := "";
  endif

  // can enter invalid page
  if (QueryParam("page"))
    params[PAGE] := QueryParam("page");
  else
    params[PAGE] := "1";
  endif

  if (QueryParam("reverse"))
    params[REVERSE] := 1;
  else
    params[REVERSE] := "";
  endif

  return params;

endfunction


function OutputOpts(guild_view := 0)

  WriteHtmlRaw("<font size=\"-1\">");

  if (!guild_view)
    if (opt[VIEW])
      WriteHtmlRaw("view:" + opt[VIEW] + " ");
    endif
  endif

  if (opt[SORT])
    WriteHtmlRaw("sort:" + opt[SORT] + " ");
  endif

  if (opt[START])
    WriteHtmlRaw("start:" + opt[START] + " ");
  endif

  if (opt[QUERY])
    WriteHtmlRaw("query:" + opt[QUERY] + " ");
  endif

  if (opt[PAGE])
    WriteHtmlRaw("page:" + opt[PAGE] + " ");
  endif

  if (opt[REVERSE])
    WriteHtmlRaw("reverse:" + opt[REVERSE] + " ");
  endif

  WriteHtml("</font>\n<br><br>\n\n");

endfunction





// *** DEVELOPER FUNCTIONS ***
// WARNING: These are usually useless and dangerous! Use at your own risk!

/* AddWebProp(add_val := 0)
 * Call this function if you ever add something to the WebProfile array like
 * an index to record the number of vomits.
 *
 * Note: Only works if you ADD something or if the WebProfile prop is deleted
 *       and you want to recreate it.
 *
 * Example: NUM_VOMITS		:= 10;	// Global index of the vomit count
 *          AddWebProp(0);		// Append 0 to each character's webprofile
 *
*/
function AddWebProp(add_val := 0)
  var accts := ListAccounts();
  var acct, chr, i, c;
  var parray := array;

  if (DEBUG)
    print("DEBUG: AddWebProp - Appending prop value " + add_val + " to webprop");
  endif

  foreach nme in accts
    acct := FindAccount(nme);
    if (acct)  
      for (i := 1; i <= 5; i := i + 1)
        chr := acct.getcharacter(i);
        if (chr)
          parray := GetWebArray(chr);
          if (DEBUG)
            print("DEBUG: AddWebProp - parray was: " + parray);
          endif
	  for (c := len(parray); c < len(default_webprop); c := c + 1)
            parray.append(add_val);
          endfor
          SetObjProperty(chr, PROP_NAME, parray);
          if (DEBUG)
            print("parray is: " + parray);
          endif
        endif
      endfor
    endif
  endforeach

endfunction


/* ResetWebPropVal(index, val := "")
 * Change the value of the webprofile array in index as val.
 *
 * Note: This is useful if you change how something is counted and you need
 *       a fresh start.
 *
 * Example: ResetWebPropVal(DEATHS, 0);	// Reset all deaths in every character
 *
*/
function ResetWebPropVal(index, val := "")

  var accts := ListAccounts();
  var acct, chr, i, c;
  var parray := array;

  if (DEBUG)
    print("DEBUG: ResetWebPropVal - Resetting WebProp at index " + index + " to " + val);
  endif

  foreach nme in accts
    acct := FindAccount(nme);
    if (acct)  
      for (i := 1; i <= 5; i := i + 1)
        chr := acct.getcharacter(i);
        if (chr)
          parray := GetWebArray(chr);
          parray[index] := val;
          SetObjProperty(chr, PROP_NAME, parray);
        endif
      endfor
    endif
  endforeach

endfunction


function ResetWebProp()

  var accts := ListAccounts();
  var acct, chr, i, c;

  if (DEBUG)
    print("DEBUG: ResetWebProp - Resetting WebProp to default");
  endif

  foreach nme in accts
    acct := FindAccount(nme);
    if (acct)  
      for (i := 1; i <= 5; i := i + 1)
        chr := acct.getcharacter(i);
        if (chr)
          EraseObjProperty(chr, PROP_NAME);
          SetObjProperty(chr, PROP_NAME, default_webprop);
        endif
      endfor
    endif
  endforeach

endfunction


function RenameWebProp(new_name)

  var accts := ListAccounts();
  var acct, chr, i, c;
  var parray := array;

  if (DEBUG)
    print("DEBUG: RenameWebProp - Renaming WebProp to " + new_name);
  endif

  foreach nme in accts
    acct := FindAccount(nme);
    if (acct)  
      for (i := 1; i <= 5; i := i + 1)
        chr := acct.getcharacter(i);
        if (chr)
	      EraseObjProperty(chr, PROP_NAME);
          SetObjProperty(chr, new_name, default_webprop);
        endif
      endfor
    endif
  endforeach

endfunction



function ResetShit()
  var accts := ListAccounts();
  var acct, chr, i, c;
  var parray := array;

  foreach nme in accts
    acct := FindAccount(nme);
    if (acct)  
      for (i := 1; i <= 5; i := i + 1)
        chr := acct.getcharacter(i);
        if (chr)
          parray := GetWebArray(chr);
          parray[LONGEST_ONLINE] := 0;
          parray[TOTAL_ONLINE] := 0;
          SetObjProperty(chr, PROP_NAME, parray);
        endif
      endfor
    endif
  endforeach

endfunction