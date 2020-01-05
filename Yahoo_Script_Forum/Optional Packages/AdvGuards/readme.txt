*************************************
*	Advanced Guards System			*
*	by HellRaider <zion@uo.com.br>	*
*	Version: 1.0 - 9/14/2000		*
*************************************

I'm open to feedback and questions. Just email me.

INTRODUCTION:

First of all, only continue reading this file if you are prepared to spend a lot of time settings this system out.
For the large shards out there, it will be arduous to setup this system as it is designed to work (sure, you may write your way outs), since it's way different from louds' standard guard system.

This system works with permanent guards, invulnerable fellows that are all dispersed by the Shard, and will be called to help out eventually. In other words the system uses the guards you have in your Shard intead of creating them at the time a crime is being committed.

I may be wrong as I've not persistently tested it, but from my point of view it reduces a lot core processing, using some more memory. I've created it not only for performance issues but also because I find it cool anyhow ;). It remembers me OSI somehow.

Ok. It's totally POL90+ dependent. You wont be able to run it on pre-POL90 shards because it's totally based on process.SendEvent().

It should not be hard for the experienced POL lovers to set it up. Although I believe the new timers will not be able to configure it... so if it's your case, please try to learn more about POL before installing this package in your Shard.

It's NOT a read to use package, I'm sorry but you'll have to tweak some scripts in order for it to fit in your Shard. Guess it wont be a problem ;)

NOTE 1: This system doesn't use guard nodes. It's designed to work with special backpacks that all PCs must have (I'll explain later in this file), that will "hear" guard calls. It'll work pretty good with guardcalling NPCs as well (NOT thought the same way [backpacks] of course), without any additional load to your NPC's AI.

NOTE 2: You must have a good amount of guards running with the AI I'm making available with this package. If you have only 10 guards in your shard, as soon as people call guards at 10 or more criminals in a short time you will run out of guards and the calls wont be handled. Read the guardsnerve.src script for more info.

SCRIPTS DESCRIPTION:

- guards.src - It's a guard AI. It hat a lot of features that were totally depended of other scripts I wrote for my shard, so I've "cutted" that lines and tried to comment everything I found important.

- guardsnerve.src - It's a dedicated script that must be running all the time at your Shard (shouldn't eat processing until someone call guards ;). It will keep a list of all guards you have in your Shard, and send them (distribute) guard calls as they are received. This script checks if the caller is in a guarded area.

INSTALL GUIDE:

You will have to reserve some constants at pol/scripts/include/eventid.inc to work with advguard in order for you to compile all scripts. Here are a list of contants you must have, and pre-selected values that may be changed:

const EVID_GUARD_CALL := 0x0911;
const EVID_GUARD_REGISTER := 0x0912;
const EVID_GUARD_AVAILABLE := 0x0913;

You may just paste that into your pol/scripts/include/eventid.inc file.

Ok, now you have to create a package for the dedicated script. Create a directory into your pol/pkg/opt/ directory called advguards, and copy the files guardsnerve.src, pkg.cfg and start.src there.
You can compile the start.src script.

Open the guardsnerve.src script... have a look at it. You will have to adjust the latest function in this file to fit in your shard. Place the guarded areas coordinates there... once you have tweaked everything, compile this script.

Let's move to the guard AI. Yeah I know I've cutted out TONS of code. Unfortunately I'd have to distribute hundred of includes and other scripts in order for this AI to work in your shard like it does in mine, so I preferred to leave some part of the code for you guys to write. Note: Some important features like speech have been cutted out as well!

Ok. The next step is to place into your NPC's AI a code to make 'em able to call guards. It's optional of course.
In my Shard, all "hostile" AIs start with "hostile" at their name. So I found it's the best way to check if a NPC should be
guard whacked. You may change this to check npctemplate.guardignore if you wish...
------CODE------
	var event := struct;
	event.+type := EVID_GUARD_CALL;
	event.+criminal;
	foreach mobile in ListMobilesNearLocation(me.x, me.y, me.z, 12)
		if (mobile.script["hostile"] or mobile.criminal)
			event.criminal := mobile;
			GuardsNerve.SendEvent(event);
		endif
	endforeach
	if (event.criminal)//If we found any criminal, cry for help
		Say("Cry for help");
	endif
--END_OF_CODE--

This is the latest part, that you might find the most problematic part. It works great in my shard and maybe it will work on yours. The problem is that you must replace ALL PC's backpacks with a new backpack that handles SPEECH_EVENTS. This is how we "hear" them calling guards.

If you want to implement this, follow the instructions:

Add this following item to your itemdesc.cfg:
---------
Container 0x6300
{
	Name			PlayerBP
	Graphic			0x0E75
	ControlScript	playerbp
	Gump			0x003C
	MinX			44
	MaxX			143
	MinY			65
	MaxY			140
	Weight			0
}
---------

Copy the script playerbp.src to your pol/scripts/control/ directory, open it, read it, adjust it as necessary and compile it.

Now, you must make some changes to your pol/scripts/misc/oncreate.src script.
Basically, the first thing that must be done to every new character is replace his backpack with item 0x6300.
Then you can run your shard-oncreate-standard-functions.
Here's an example:
---------
use uo;

include "include/starteqp";
include "include/client";

var backpack;//This var is used by my other item generation functions that are not included.

program OnCreate (who, skillids)
	DestroyItem(GetEquipmentByLayer(who, LAYER_PACK));
	backpack := CreateItemAtLocation(who.x, who.y, who.z, 0x6300, 1);
	EquipItem(who, backpack);
    foreach skillid in skillids
		if (GetSkill(who, skillid))//Only give out items for skills>0
			CreateFromGroup(who, skillid);
		endif
	endforeach
	CreateFromGroup(who, "all");
endprogram
---------

Hmmmm am I forgetting anything? I hope not.
Please if you find any bugs let me know.

Feedback is always welcome.

Sorry if I couldn't document this package well enough. My english is not perfect and I could only spend 3 hours building it up. ;)

Hope you like it,
-HellRaider