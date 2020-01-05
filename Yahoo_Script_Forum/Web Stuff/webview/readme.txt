[ABSTRACT]
This package is a character and guild profile system. You can make in-game gumps to use the information that it collects, but right now for this version, you can view it from the web using the POL webserver. It also can let you see the online location on a map of all players, guild locations and spawn regions.


[INSTALLATION]
First, copy the pkg folder to your POL root directory. This will put the webview package in /pkg/opt/webview.

Next add these lines to the following files:

In /pkg/items/guildstone/guildDeed.src:
// Add this at the top
include ":webview:webGuilds";

  ...

      DestroyItem(deed);
      SetObjProperty(item, "houseserial", house.serial);

      // ADDED THIS LINE
      SetLocation(item);

    endif
  endif
endprogram



In /pkg/items/guildstone/guildMove.src:
// Add this at the top
include ":webview:webGuilds";

  ...

    // ADDED THIS LINE
    SetLocation(stone);

  endif
endprogram



In /scripts/misc/chrdeath.src:
  include ":webview:webProfile"; //ADD THIS AT THE TOP

  ...

  IncreaseDeaths(ghost); 	//ADD THIS LINE HERE

  var fame := CInt(GetObjProperty(ghost, "Fame"));

  ...



In /scripts/misc/death.src:
  include ":webview:webProfile"; //ADD THIS AT THE TOP

  // CHANGE/ADD these things (I think it's a bug to not increase noto when logged off)
  if ((killer != error) && (!GetObjProperty(corpse, "guardkill")))
    var kwho := SystemFindObjectBySerial(killer[2], SYSFIND_SEARCH_OFFLINE_MOBILES);
    AdjustNoto(kwho, corpse);

    // Increase NPC kills if this is an account
    if (kwho.acctname)
      IncreaseNPCKills(kwho);
    endif

  endif

  ...



You'll also want to configure the URLs if you use PHP to include the .ecl files, and maybe a few other settings. So open constants.inc and take a look there. 

const CHAR_SRC		:= "view_chars.ecl";
const GUILD_SCR		:= "view_guilds.ecl";
const LOC_SCR		:= "view_locations.ecl";
const IMG_URL		:= "http://www.yourhost.com/map.jpg";


If something doesn't work, it's likely because I forgot to tell you to change a const variable in constants.inc. If so, I'm sorry. Just let me know and I'll fix it. If I were you I'd just have a quick look-through the scripts and look for any variables you'd want to change. Finally, you want to recompile and you should be set.


[NOTES]
The actual profile text for players comes from the profile system from newclientsupport. It's pretty good but if you don't want to use it, it shouldn't be that hard to use whatever you want. In later versions I'll add a native profile command. I took (too?) many steps to make sure these scripts would be flexible and easy to modify without digging around in the code. I've also included two versions of PHP you can use to include these files. One uses cgi and the other doesn't. They're in the php directory and there is a readme in there that can help you out. I hopped to have a way to view a list of guilds and have links to their charters, but it was giving me hell so I'll have to release it in the next version. I used UOAutoMap to create map.jpg. All I did was run it and it created some MAP-0.bmp in it's program directory and I converted it to .jpg using photoshop at the highest quality setting. You could use your own custom map image by repeating the process.

There are also two commands that come with this package .webguilds and .webview. You shouldn't have to use them all the time, they're more for developing. If you add this system and you already have a lot of guilds you'll have to type this:
.webguilds rebuldlocs

Which will rebuild the profile information for all the guilds.


[KNOWN BUGS]
There seems to be a problem with the wrestling script where LastHit is not being added. Because of this if you kill a NPC it doesn't increase the total NPC kills. If you know anything about this (like if I'm just doing something wrong) contact me. I'd fix it myself but it's not like I can include the fix in this package too.


[UPDATES]
Thanks again to drummond for testing and feature requests!

Too many updates to list them all!


[CONTACT]
There is a very real chance you'll find a bug. If so, and you want to get some karma points, tell me and I'll try to fix it, or if you have comments, lemme know.

E-mail: tekproxy@mantis.sytes.net or tekproxy@yahoo.com
Aim: tekproxy