Questing Commands

This was created in an attempt to make things easier in training new staff and also for old staff who happen to forget the commands sometimes :)

The commands included in here are most likely duplicates or replacements of existing functions on your shard...however, some of these also have the added feature of being gump driven (if parameters are not entered) The nice thing is that all the functions are accessible through either the .quest command or individually through their own . commands

The .quest command has the commands broken down into various categories (somewhat organized...hah!) and named according to whatever the script is named that it will be calling. The functions that have parameters to pass have a gump (typically text entry) that will show up listing the parameters that the script wants. Note that not all parameters are neccessary on all the scripts (i.e. you *can* pass a certain parameter to the script, but it is not truly necessary since it has a default value). The gump listing the parameters also has them listed in proper order so that if you wished to use the command directly, you pass the parameters in the same order.

For installation:
	I personally use a separate named folder in the textcmds called 'building', then I simply add a 'DIR' line to the cmds.cfg in the lowest cmdlevel that I want to have access to these commands (i.e. I want Seer and up to access it, so I add 
DIR ../scripts/textcmd/building
under the seer listing.
	However you do your install though, be sure to change the build command at the start_script call so that it points to wherever you put the scripts.

modules.inc - This is just my way of making sure I have the modules in the script :) ok, ok...so I'm lazy heh...no I didnt include a copy since it is easy to create one ;)

gumps.inc - Thanks to Myr for this...without it, I prolly wouldn't have done all this hehe... 

Have fun and Enjoy


Any questions, comments, suggestions, flames, or recommendations for additional functionality can be directed to:
Angreal
saangreal@excite.com