Arena v2.0b
By: Sigismund

*** Introduction ***

Arena is a fully automated player combat system, designed with places
like the Jhelom Arena in mind.   It allows players to "sign up" and
fight monsters, or other players, in a controlled setting.



*** Operation ***

The arena object consists of two separate scripts, the registry, and
the actual arena control script.  When a player double-clicks the 
arena registry stone, that player is added to a queue.  A maximum
of 7 players are allowed in the queue at one time, and a player may
not have more than one spot.  For player vs. player battles, it is
only necessary for one player to sign up.

The arena control script does all the rest of the work.  It will
perform a check every 30 seconds to see if there are any fighters
waiting in the queue.  If so, it will grab the first one, start the
fight routine, wait for the finish of the fight, and perform some 
maintenance.   If there are no fighters in the queue, it goes 
straight to the maintenance, then starts the loop again.



*** Installation ***

- Unzip this package in a directory off of /pol/pkg, and make sure
it is enabled.

- Double check the arena object (default 0xA200) to make sure it is 
not in use by other shard objects.

- Set the arenaregistry.cfg file up to your specifications.  The
file should be set as follows:


arenavendor arena		// This is the name of the arena,
				// set in the CProp "VendorID"
{
	TopX	1385		// These 6 lines set the bounds
	TopY	3729		// of the arena.   The default  
	TopZ	-21		// values are the dimensions of 
	BottX	1414		// the Jhelom arena.
	BottY	3758		
	Bottz	-21		
	DestX	1407		// These entries determine 
	DestY	3733		// possible starting locations
	DestZ	-21		// for arena fighters.   When they
	DestX	1390		// start the battle, they are
	DestY	3751		// transported to a random location
	DestZ	-21		// from this list.
	DestX	1388
	DestY	3731
	DestZ	-21
	Monster orc2		// These are monster definitions, 
	Level	2		// based on entries in npcdesc.cfg.
	Type	1		// "Level" is the difficulty level,
	Monster	liche		// as chosen in the fight script,
	Level	5		// and "type" is the # of the 
	Type	1		// battle as chosen in the fight
	Monster	lizardman1	// script.  (1 = humanoid, 2=
	Level	2		// bestial, etc. etc.)
	Type	1
}

- MAKE SURE THE ARENA OBJECT IS *NOT* LOCATED IN THE ARENA!

- Have fun :)



*** To Do ***

- Update the fight scripts with a neater version, including the
Grand Melee and Battle Royale.

- Add scoring system and fight tree for tournaments/bragging rights.

- Add gambling system.

- Set monster file to use a separate npcdesc.cfg file.

- Streamline the code.



** Questions, Comments, Vapid Hostilities? ***

Send mail to: prostheticdelirium@worldnet.att.net
Or an ICQ to: Prosthetic Delirium [10520050]


Sigismund