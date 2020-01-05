/* webLocation.inc
 * Last Modified: 06/28/04
 *
 * Constants and functions related to the map-viewing.
 *
 * TODO:
 * Add functions to show regions (not spawn regions)
 * Add option to use dot graphic instead of <div> tags
 *
 * NOTE:
 * The actual image of the map is 1.98 megs and you need a
 * browser that doesn't suck at caching images.
 *         
*/


use datafile;


include ":webview:core";


const PLAYER_DOT	:= 1;
const GUILD_DOT		:= 2;


function ViewPlayerLocations()

  // Show the location of all the players on the map.

  var accts := ListAccounts();
  var acct, chr, holder, i;

  WriteHtml("<body vlink=\"white\" alink=\"white\">");
  WriteHtml("<div style=\"position:absolute; width:1000px; height:100px; left:0px; top:0px;\">" +
    "<img src=\"" + IMG_URL + "\"></div>");


  // Main loop to find all loggedin characters and show them
  foreach nme in accts
    acct := FindAccount(nme);

    if (acct)  
      for (i := 1; i <= 5; i := i + 1)
        chr := acct.getcharacter(i);

        if (chr && GetObjProperty(chr, "LoggedIn"))
          // Draw the location using <div> tags.
          DrawDot(chr, PLAYER_DOT);
        endif
      endfor
    endif

    sleepms(10);
  endforeach

endfunction


function ViewGuildLocations()

  var guilds := array;
  var guild;

  guilds := ListGuilds();


  WriteHtml("<body vlink=\"" + VLINK + "\" alink=\"" + ALINK +"\">");
  WriteHtml("<div style=\"position:absolute; width:1000px; height:100px; left:0px; top:0px;\">" +
    "<img src=\"" + IMG_URL + "\"></div>");


  // Main loop to find all 
  foreach guild in guilds
    DrawDot(guild, GUILD_DOT);
    WriteHtml(guild.GetProp("x") + ", " + guild.getprop("y") + ", " + guild.getprop("z") + "<br><br>");
    sleepms(10);
  endforeach

endfunction


function DrawDot(obj, type)

  // You could change this to use a small graphic.

  var x;
  var y;

  // Get x and y values
  if (type == PLAYER_DOT)
    x := obj.x;
    y := obj.y;
  elseif (type == GUILD_DOT)
    x := obj.GetProp("x");
    y := obj.GetProp("y");
  endif


  // Calculate cordinates based on image size
  x := CInt(x / 2) - 1;
  y := CInt(y / 2) - 1;


  if (DEBUG)
    print ("DEBUG: DrawDot - Drawing dot at (" + x + ", " + y + ")");
  endif

  WriteHtml("<div style=\"position:absolute; background-color:" + DOT_COLOR + "; " +
    "width:3px; height:3px; left:" + x + "px; top:" + y + ";\"></div>");
  WriteHtmlRaw("<div style=\"position:absolute; left:" + (x + 6) + "px; top:" + (y - 5) + "; " +
    "color:" + TEXT_COLOR + "; width:auto; font-size:12px;\">");

  // Determine how the output should look (profile? cordinates?)
  if (type == PLAYER_DOT)

    if (SHOW_PLAYER_PROF)
      WriteHtmlRaw("<b><a style=\"text-decoration:none\" href=\"" +
        PLAYER_PROF_URL + obj.serial +"\" alt=\"" + obj.name + "\">" + obj.name + "</a>");
    else
      WriteHtmlRaw("<b>" + obj.name + "</b>");
    endif

    // Show the cordinates next to the name?
    if (SHOW_PLAYER_XY)
      WriteHtmlRaw(" (" + obj.x + ", " + obj.y + ")");
    endif

  elseif (type == GUILD_DOT)

    if (SHOW_GUILD_PROF)
      WriteHtmlRaw("<b><a style=\"text-decoration:none\" href=\"" +
        GUILD_PROF_URL + obj.guildid +"\" alt=\"" + obj.GetProp("guildname") + "\">" +
        obj.GetProp("guildname") + "</a>");
    else
      WriteHtmlRaw("<b>" + obj.GetProp("guildname") + "</b>");
    endif

    // Show the cordinates next to the name?
    if (SHOW_GUILD_XY)
      WriteHtmlRaw(" (" + obj.GetProp("x") + ", " + obj.GetProp("y") + ")");
    endif

  endif

  WriteHtml("</b></div>");

endfunction


function ViewSpawnRegionLocations()

  // This will show the location of all the spawn regions on the map.

  WriteHtml("<body vlink=\"white\" alink=\"white\">");
  WriteHtml("<div style=\"position:absolute; width:auto; height:auto; left:0px; top:0px;\">" +
    "<img src=\"" + IMG_URL + "\"></div>");

  foreach region in ReadSpawnRegionXY()
    DrawSpawnRegion(region[1], region[2], region[3], region[4], region[5]);
  endforeach

endfunction


function DrawSpawnRegion(name, x1, y1, x2, y2)

  // The image file included is half the size of the actual map so
  // we divide the player cords by 2 and subtract 1.

  x1 := CInt(x1 / 2) - 1;
  y1 := CInt(y1 / 2) - 1;
  x2 := CInt(x2 / 2) - 1;
  y2 := CInt(y2 / 2) - 1;

  var w := CInt(x2 - x1);
  var h := CInt(y2 - y1);
  var c := {
    CInt(w / 2) - (len(name) * 2) + x1,
    CInt(h / 2) + y1
  };

  // Draw top horizontal line
  WriteHtml("<div style=\"position:absolute; background-color:white; " +
    "width:" + w + "px; height:3px; left:" + x1 + "px; top:" + y1 + ";\"></div>");

  // Draw bottom horizontal line
  WriteHtml("<div style=\"position:absolute; background-color:white; " +
    "width:" + w + "px; height:3px; left:" + x1 + "px; top:" + y2 + ";\"></div>");

  // Draw left vertical line
  WriteHtml("<div style=\"position:absolute; background-color:" + BORDER_COLOR + "; " +
    "width:3px; height:" + h + "px; left:" + x1 + "px; top:" + y1 + ";\"></div>");

  // Draw right vertical line
  WriteHtml("<div style=\"position:absolute; background-color:white; " +
    "width:3px; height:" + h + "px; left:" + x2 + "px; top:" + y1 + ";\"></div>");

  // Place the region name
  WriteHtml("<div style=\"position:absolute;" +
    "left:" + c[1] + "px; top:" + c[2] + "; width:" +  ((len(name) * 6) + 8) + "px; " +
    "color:" + TEXT_COLOR + "; font-size:12px;\"><b>" + name + "</a></b></div>");

endfunction


function ReadSpawnRegionXY()

  // Read the region info from the datafile.
  // Returns: { region name, x1, y1, x2, y2 }

  var regionscfg := OpenDataFile(":spawnregion:SpawnRegions");
  var retarray := array;
  var tmp := array;

  if (DEBUG)
    print("DEBUG: ReadSpawnRegionXY - " + regionscfg);
  endif

  foreach regname in(regionscfg.Keys())
    var regelem := regionscfg.FindElement(regname);

    if(!regelem)
      continue;
    endif

    tmp := SplitWords(regelem.GetProp("rect"));
    retarray.append( { regname, CInt(tmp[1]), CInt(tmp[2]), CInt(tmp[3]), CInt(tmp[4]) } );
  endforeach

  return retarray;

endfunction