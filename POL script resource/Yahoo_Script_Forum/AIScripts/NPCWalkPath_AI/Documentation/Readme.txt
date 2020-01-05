Name: AI Script - NPCWalkPath

Created by Cassandra White (casswhite@home.com)
    With assistance from Syzygy, Myrathi

Last updated: 04/02/00
Last updated: 04/28/00
Last updated: 04/30/00

Document Information:

This readme.txt was written using notepad, in full screen with wordwrap on.
Please refur to the changes.txt for summer updates. All details are still added to documentation dirrectly.

Introduction:

Unfortunately there is no real way to suggest a demo of this NPC package. However, I hope that will not detour you from this use of this well designed set of scripts. Documentation of this package grows as the package does, and is only as extensive as it's latest release. For further details, or questions, please look to the end or beginning of this readme.txt for my email address, where you can address any issues dirrectly.

I want to append to the above statement weeks after it was written, with the new commands added, I have a greater chance of giving you an idea of how a series of commands will make for an intersting quest, or other related ideas. Look to the bottom of this document for a demo list of input commands.

FAQ (Frequently Asked Questions):

Okay, so I am sure question one is, "What does it do?".

Well in short, it allows anyone granted the command level of the text commands supplied, to set up global properties in the form of paths. These paths may also include performing actions, adding sound effects and even pausing to take a breather, amongst many other options.

"Why use global props? Why not a config file?"

The answer to that is simple. When using a config file, you are limited as to how to deal with the file through eScript. For example I can delete entire Global Properties while never shutting down. To do the same with a .cfg is impossible at this time. 

"But wouldn't the ease of .cfg file manipulation make things easier for GMs?"

No, it is my intention to design a webpage that will allow GMs to edit online Global Path Properties in the near future. This will allow detailed manipulation, much like a cfg, but without the down time to reload the cfg.

"What happens to a Global Property when the server shuts down? Isn't it a variable? Won't it be errased?"

When a server shuts down, all Global Properties are saved to /pol/data/pol.txt. Global Properties are more then just variables, they are like hard variables, that are put on pause until the server is reinitiated.

"What happens when a path location is blocked?"

I have spend some time on the NPC to location error checking. NPCs after 10 attempts will move on to the next .addpath in the list (pause, action whatever), emitting a "Time to move along..." as well. In the process I have added a function to the NPCWalkPath.inc that allows you to check the number of steps it would take a mobile (npc or char) to go from the current location to any point/location 'as the crow flies', in other words, if it's a straight line only. This is not an issue for this AI. And you can see why in the NPCWalkPath.inc.

"What happens to the NPC when the server is shut down?"

A Cprop is assigned to the NPC so the AI is able to determine at what point in the 'NPCPathList' the NPC is presently. If the server is shut down, this CProp is saved. Exaclty like a Global Propery. When the server loads once again, and the NPC's AI is reactivated, the AI looks for the CProp so it knows what locations the NPC was walking towards last, and continues on that journey.

"Why is there a NPCWalkPath.src and an NPCWalkPath.inc?"

The reason for this is, a basic NPCWalkPath.src AI has been set up so you can create simple automated NPCs. For example a lumberjack goes off to chop would. You may not want any further AI features, so this will work with the NPCTemplate listed below. All you have to do is dress the NPC (.dress [dressclass]) and name it (.rename [name]). Threason the main AI was posted to an include (.inc) file was to these routines may be called from other NPC AI's. So a merchant may be able to wander in a specified path while still selling his/her goods.

Note: The above is based in Distro 88s AI/NPCs.


File locations, if you don't want to use the package setup.
Files:
NPCWalkPath.inc		/include
NPCWalkPath.src		/scripts/ai
addpath.src		/scripts/textcmd/? (your choice)
setnpcpath.src		/scripts/textcmd/? (your choice)
undolastadd.src		/scripts/textcmd/? (your choice)

Note: *.src will need to be compiled.

Optional Files:

Added Documentation:
Actions.txt	- A full list of mobile actions
ReadMe.txt	- The file you are currently reading
Sndlist.txt	- A complete list of sndfx in UO
   Note: This list is not well documented.
         The use of Inside UO is greatly suggested.
UOXColors.txt	- A partialy documented list of colors


Command Structure:

.addpath [command] [pathname] [param1] [param2] [param3]

Note: [ and ] are only used here to show the seperation of paramaters and should not actualy be used when entering commands. Also note, not all params are used with every command, please recognize the exceptions.


If any of the paramaters after [command] are missing, example:

.addpath [command]
or...
.addpath testpath

then a search will be done to see if the path name [command] / testpath in this case, exists. If it does not exist, [Command] will be used as the [pathname] for initiation sake only, and only in this instance.

If this occures by mistake, simply remove the path using the .erasepath command listed below.

List of Props used:
CProp NPCPath     - stored the NPCs pathname
CProp NPCPathRule - stores what rule the NPC is currently at

List of Commands:

.addpath [pathname]
Example, .addpath testpath
This will initiate a new path.

.addpath action [pathname] [actionhex] [repatitions]
Example, .addpath ocllolumberjack 0x013 1
This will add an action to the NPCs list of duties, in the location last added to the list. In this case the lumberjack will preform a tree chop action once.

.addpath color [pathname] [colorhex]
Example, .addpath minocwerewolf 0x0841
This will change the colour of the mobile to that specified. This works well in conjuction with the graphic command.

.addpath facing [pathname] [decimal]
Example, .addpath facing ocllodrunkard 2
This will turn the NPC in a specific dirrection, based on the facings listed below.
Note: that this action is preformed very quickly and without an .addpath pause statement, may actualy be unnoticable.
7 8 1
6   2
5 4 3

.addpath graphic [pathname] [graphichex]
Example, .addpath graphic minocwerewolf 0x00e1
This will change the current mobiles graphic to that of the new graphichex setting, which works well in conjunction with the color graphic. So in this case you could change from a human, to a wolf, and back to a human again as needed.

.addpath pause [pathname] [seconds]
Example, .addpath pause oclloguard 5
This will have the NPC idle in place for [seconds] number of seconds.

.addpath rename [pathname] [phrase]
Example, addpath rename ocellovampire a vampire bat
This will rename the mobile as needed, works well with the [graphic] command. Don't forget to change the name back if needed.

.addpath run [pathname] <target>
Example, .addpath run messenger <target>
This function springs to life a target curser that will ask you to where you wish your NPC to run. You may click yourself, an item placed on the ground or the ground itself. If an item is used, the coordinates of the item at when selected, are used, not the current items location. This also goes for clicking yourself.

.addpath say [pathname] [phrase]
Example, .addpath say jhelomdrunkard Jusht one more pweeze! I promish I won't gesh drunk!
This will have the mobile repeat the phrase above it's head as any player would do. The duration of the words staying visible is based on the client side setup.

.addpath sfx [pathname] [soundhex] [repatitions]
Example, .addpath sfx ocllolumberjack 0x13f 1
This will play a sound effect located at the NPC origan for [repatition] number of times.

.addpath walk [pathname] <target>
Example, .addpath walk ocllocrier <target>
This function works exactly the same as run with the exception that the NPC walks, rather then runs.

.erasepath [pathname]
Example, .erasepath testpath
This will remove the path with the name [pathname] / testpath, from the path pool.

.setnpcpath [pathname] <target>
Example, .setnpcpath oclloguard <target>
This will set the NPC targeted to the path you have entered. If a path CProp already exists on the NPC, it will be updated to the new path.

.undolastadd [pathname]
Example, .undolast ocelloguard1
This is like an undo command, it has no set number of uses, it will just remove the last added command. So be careful.


NPC Example:

NpcTemplate npcwalkpath
{
    Name        <random> the pathwalker
    script      :npcwalkpath:npcwalkpath

    ObjType     0x190
    Color       33784
    TrueColor   33784

    Gender      0

    speech 	30

    STR         200
    INT         200
    DEX         200

    HITS        200
    MANA        200
    STAM        200

    guardignore 1
    alignment   good

    Privs       invul
    Settings    invul

    Wrestling 	100

    AttackSkillId Wrestling
    AttackSpeed 80
    AttackDamage 5d100

    dstart 10
}

You may create NPCs templates with preset paths using an added entry in the NPC template as follows:

CProp NPCPath s[pathname]

An example...

NpcTemplate npcwalkpath
{
    Name        <random> the pathwalker
    script      npcwalkpath

    ObjType     0x190
    Color       33784
    TrueColor   33784

    Gender      0

    speech 	30

    STR         200
    INT         200
    DEX         200

    HITS        200
    MANA        200
    STAM        200

    CProp    NPCPath    soclloguard

    guardignore 1
    alignment   good

    Privs       invul
    Settings    invul

    Wrestling 	100

    AttackSkillId Wrestling
    AttackSpeed 80
    AttackDamage 5d100

    dstart 10
}

Note: When using the NPCWalkPath.src remember to use the ...
Script :NpcWalkPath:NpcWalkPath
for the NPCTemplate AI Script.


Sample code to Add to AIs:

Note: Change the ...

    Local ev;
    ev := os::wait_for_event( 30 );

      to ...

    Local ev;
    ev := os::wait_for_event( 1 );

      when using Distro AIs.

// Wander or WalkPath

	var havenpcpath := GetProperty( "NPCPath" );
	if (!havenpcpath)
	        if (ReadGameClock() >= next_wander)
	                wander();
	                next_wander := ReadGameClock() + 10;
	        endif
	else
		NPCWalkPath(me);
		sleepms(10);
	endif

List of Demo Commands for input:
.addpath test1                     (will create a test path called 'test1' as a global prop)
.addpath graphic test1 0x00e1      (will change the mobiles graphic to that of a wolf)
.addpath color test1 0x0841        (will change the mobile to an off brown colour)
.addpath say test1 Hoooowwwwwwwl!! (will have the mobile say "Hoooowwwwwwwl!!")
.addpath sfx test1 0x00b8          (will produce the wolf growling sound)
.addpath pause test1 7             (will pause long enough for the say above to time out)
.addpath graphic test1 0x0190      (will change the mobile back to it's default graphic)
.addpath color test1 37784         (will set the mobile back to it's default color)
.addpath action test1 0x0005 2     (will perform the look around action twice)
.addpath walk test1                (oops, that was a mistake)
.undolastadd test1                 (removes that unsightly mistake)
.addpath say test1 What was that?! (will say "What was that?!")
.addpath pause test1 15            (will pause for 15 seconds)

.createnpc npcwalkpath             (creates an NPC with the NPCWalkPath base AI script)
*Note: this step can be ignored if you use the add code and not the NPC Template*

.setnpcpath test1                  (sets the NPCPathWalker's path to 'test1')

Essentaily what this simulates is that an unsuspection male, transforms into a wolf, howls, then transforms back into a man, wondering what just happened. This is just a single idea, one that spawned into a larger idea for a Lycanthropy quest on my shard. Where a vampire creeps into town one night and kidnaps a town mayor. Now the players are called to arms, and offered a reward if the mayor is found and brought back. When this quest was tested, a player actualy saw the vampirebat (mongbat) fly into town, transform into a humaniod (vampire), grab the mayor, and leave town.

Conclussion:

I know alot of you guru scripters are cringing out there, saying "there really is an easier way to do that". And I fully agree. I just don't know of it at this time. So all suggestions and upgrades are greatly apprieciated. Any bug reports are welcome also.

I want to officialy thank Syzygy and Myrathi for coding assistance, and I want to thank Dundee for inspiration.

Cassandra White 'Admin ZeuZ' of Nirvana Shard
ICQ: 27148383
Email: casswhite@home.com

addpath [spell effects]