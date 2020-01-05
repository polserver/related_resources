// Created November 1, 2000
// last update December 17, 2000
// zulu (zulu@zuluhotel.com)
//
// Includes guilddeed updates from Marquis and Bishop
// Includes changes to guildmove.src by Zulu, used Marquis and Bishop's code
// Includes guildstone updates from Magic

********
Features
********
- Declare War and Declare Ally, have to be requested from both guild 
before became valid. (so for broken war and ally).

When a guild want to make an alliance, a request are made... when the 
other guild accept the request, then the two guild became ally.
(so for war declaration)

When a guild want to broke an alliance, a request are made.. when the 
other guild accept the request, then the two guild are not more ally.
(so for war declaration)


**********
Installing
**********
Load the pcs.txt file and remove the following lines:
  GuildId #
  in players name remove [guild abv]
  CProp guild_id i#
  CProp abv i1
  TitleGuild " [w00t], Guildmaster"
  remove anything else that has to do with guilds.

delete the old /pkg/opt/guildstone/
 
unzip guildstone.zip to  /pkg/opt/guildstone/

move c.src to /textcmd/player/

************
IMPORTANT!!!
************
On the Zulu package there's a BUG! The guild have to use an ID > 1.
so when you download the package, you have to modify the guild.txt 
file on the data dir.

the first entry for guild ID, MUST IS 2.
So the guild.txt have to be:

#
#  GUILDS.TXT: Guild Data
#

General
{
NextGuildId 2
}

If you don't do this... the guild that have an ID 0 or 1, cannot have 
ally or declaration of war. (the error is on the mode that is used to 
retrive the selected guild from the gump.....)
