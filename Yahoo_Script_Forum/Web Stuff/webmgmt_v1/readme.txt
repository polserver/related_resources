Version 1 of tcb's secure web interface

This uses what I believe to be a secure hash, as well as a totally random config file for every shard.

Text commands included are:
player: .setpassword - which sets both the game and web passwords the same, and players can feel free to use their current passwords. The hashed value of the password is stored as an account prop.
admin: .makehashcfg - which is a run once command needed to use this package. It sets up the shards custom hash table. Once the config file is created it will error out instead of overwriting the original.

The index.html in the root of the zip needs to be placed into the /scripts/www folder, overwriting the original (back it up if you have customized it)

The scripts use an IP prop from the account, which can be disabled by editing the /webmgmt/www/login.src and the web account creater files.

The package includes my web account creater which is the only page accessible without logging in. More below about the creater.

The style1.css needs to be uploaded to a website (many free sites allow these files if you create a dummy index.html for them also). This is the color and layout scheme for all pages. After you upload it you need to put the path into most of the scripts and recompile. You can use UltraEdit and do a replace in files command and replace "TYPE THE PATH TO YOUR STYLESHEET HERE" with your path. Editing this file will make site wide changes immediately, no need to recompile.

Now, the account creater. It has support to deny anonymous emails via config file, which needs to be updated if you plan on using it. The same config file contains a check for propper domain suffix's, so more of those need to be added as well. ICQ numbers are required, but can be disabled by removing the check for them in the webacct.asp script. Account names are limited between 5 and 15 characters, and passwords between 6 and 16. Name and password cannot be the same. Password and password verification must be the same. No values can contain spaces. ICQ numbers must be between 5 and 11 digits. IP of the person creating the account is also added at time of creation. I added a couple of lines to my logon script so that every time a player logs into the game their IP will be updated, that way dialup users can access the website as well. A full check of password hash, IP, ICQ and email is done against the existing account to make sure someone isn't trying to make a second account (core handles duplicate account names).

I will be releasing plugins for this interface periodically. I already have a few pages, but have a full plugin in mind for them, so I will wait.

Index.ecl files need to be created in both the /www/gm and /www/player folders to let characters actually see anything when they log in. =-)
These will be part of my first plugin, but I wanted to get this portion of it out there for you guys to look at and pick apart.

Any questions, comments, or suggestions can be conducted through ICQ @ 13294961, and will be greatly appreciated.

Note on the hash. It is not in any means meant to be an irreversable, hack proof system on the web side. I do however believe it is totally immpossible to retrieve the original password value to allow someone to log into the game with. The vulnerabilities of the web side are what prompted me to include an IP check. That being said, I welcome anyone trying to prove me wrong and trying to retrieve passwords on their own shards and to let me know about it so I can update it.

thanks for your support and help (pretty much everyone, but especially Myr, MadMan, and for the hashing idea, Jason)

imtcb