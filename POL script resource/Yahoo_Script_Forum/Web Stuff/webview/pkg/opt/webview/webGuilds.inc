/* webGuilds.inc
 * Last Modified: 06/28/04
 *
 * Shared functions for guilds.
 *
 * TODO:
 *
*/

include ":webview:core";


function ViewGuildProfile(guildid)

  var guild := FindGuild(guildid);

  if (guild == error)
    WriteHtml("That guild does not exist.<br>");
    return;
  endif

  var datecreated := RemoveError(CDateTimeStr(guild.GetProp("timecreated")));
  var webpage     := RemoveError(guild.GetProp("webpage"));
  var abbrv       := RemoveError(guild.GetProp("guildabv"));
  var charter     := RemoveError(BuildCharter(guild));
  var type       := RemoveError(guild.GetProp("type"));

  if (webpage)
    webpage := "<a href=\"" + webpage + "\" target=\"_blank\">" + webpage + "</a>";
  else
    webpage := "N/A";
  endif

  var p := "";

  p := p + "<tr><td>Abbreviation:</td><td>" + abbrv + "</td></tr>\n";
  p := p + "<tr><td>Created:</td><td>" + datecreated + "</td></tr>\n";
  p := p + "<tr><td>Website:</td><td>" + webpage + "</td></tr>\n";
  p := p + "<tr><td>Type:</td><td>" + type + "</td></tr>\n";
  p := p + "<tr><td>Charter:</td><td>" + charter + "</td></tr>\n";
  p := p + "<tr><td>Allies:</td><td>" + GetAllies(guild) + "</td></tr>\n";
  p := p + "<tr><td>Enemies:</td><td>" + GetEnemies(guild) + "</td></tr>\n";
  p := p + "<tr><td>Members:</td><td>" + GetMembers(guild) + "</td></tr>\n";

  var view_guild;

  if (SHOW_GUILD_LOC)
    view_guild := " | <a href=\"" + LOC_SCR + "\?guilds=1\" target=\"_blank\">Guild Locations</a>";
  endif

  WriteHtml("<font size=\"+1\"><b>" + guild.GetProp("guildname") + "</b></font><br>" +
    "<blockquote>" +
    "<table border=\"1\" cellspacing=\"0\" cellpadding=\"10\" bordercolor=\"#9c3010\" width=\"400\">" +
    p + 
    "</table>" +
    "</blockquote>" +
    "<br><br>\n\n<a href=\"" + GUILD_SCR + "\">Show All Guilds</a>" + view_guild);

endfunction


function BuildCharter(guild)

  var charter_array := guild.GetProp("gc");
  var line, ret := "";

  foreach line in charter_array
    ret := ret + line + "<br>\n";
  endforeach

  return ret;

endfunction


function SetLocation(stone)

  var guildid := GetObjProperty(stone, "guild_id");
  var guild := FindGuild(guildid);

  if (DEBUG)
    print("Setting guildstone location: " + stone.x + ", " + stone.y + ", " + stone.z);
  endif

  // Set X Y and Z of guildstone
  guild.SetProp("x", stone.x);
  guild.SetProp("y", stone.y);
  guild.SetProp("z", stone.z);

endfunction


function SetCreationTime(stone)

  var guildid := GetObjProperty(stone, "guild_id");
  var guild := FindGuild(guildid);
  var timecreated := Polcore().systime;

  if (DEBUG)
    print ("Setting guild creation time on " + stone + " to " + timecreated);
  endif

  guild.SetProp("timecreated", timecreated);

  return 1;

endfunction


function GetMembers(guild, pre := "", pos := "")

  var members := array;
  var p := "";
  var member;

  members := guild.members;

  foreach member in members
    p := p + "<a href=\"" + PLAYER_PROF_URL + member.serial + "\">" + member.name + "</a><br>\n";
    sleepms(10);
  endforeach

  // This should never happen... but just in case
  if (!p)
    return "This guild has no members.<br>\n";
  else
    return p;
  endif

endfunction


function GetAllies(guild, pre := "", pos := "")

  var allies := array;
  var p := "";
  var ally;

  allies := guild.allies;

  foreach ally in allies
    p := p + ally.GetProp("guildname") + "<br>\n";
    sleepms(10);
  endforeach

  if (!p)
    return "This guild has no allies.<br>\n";
  else
    return p;
  endif

endfunction


function GetEnemies(guild, pre := "", pos := "")

  var enemies := array;
  var p := "";
  var enemy;

  enemies := guild.allies;

  foreach enemy in enemies
    p := p + enemy.GetProp("guildname") + "<br>\n";
    sleepms(10);
  endforeach

  if (!p)
    return "This guild has no enemies.<br>\n";
  else
    return p;
  endif

endfunction


function RemoveError(str)

  if (str == error)
    return "";
  else
    return str;
  endif

endfunction


// DEV FUNCTIONS
function RebuildLocs()

  // Use this if you already have a lot of guilds and you
  // want to set their locations. You can run this function
  // using the .webguilds command.

  var i := 0, t := 0, x := 0;
  var numguilds := len(ListGuilds());

  // These values may need to be changed depending on your map size.
  foreach obj in ListObjectsInBox(0, 0, -127, 100000, 100000, 127)

    if (obj.graphic == 0x0ed4)
      x := x + 1;

      if (DEBUG)
        i := i + 1;
        t := t + 1;

        print("Found guild: " + GetObjProperty(obj, "guild_id"));

        if (i >= 500)
          print("Searching for guildstones: " + t + " items searched. Sysload: " + Polcore().sysload);
          i := 0;
        endif
      endif

      SetLocation(obj);
      SetCreationTime(obj);

      // Only search until we find all the guilds!
      if (x >= numguilds)
        return;
      endif

    endif

    sleepms(10);
  endforeach

endfunction