
To set up:
The only file you strictly need to modify is spelllist.cfg. This
file contains the names of the spells as they will appear in your
spellbook, and what SpellID number that spell is assigned in 
spells.cfg. 
The cantrips call on SKILLID_THAUMATURGY. You may want to replace
all instances of that with SKILLID_MAGERY if you are using this as
part of your magery package, or with whatever magic type you are
using it with.

You'll probably also need to delete the scrolls from itemdesc.cfg-
I reused the original scrolls' item numbers. On the bright side, 
this means you won't have to change transcribe.src where it checks
to see if you have selected a valid scroll unless your valid scrolls
are not those numbers.

Once all this is done such that it compiles and is happy, you'll need
the admin to run the command ".fillwop". As written, this function starts
at spellID #101 and goes up until it hits a number that doesn't have 
a spell. Since the spellbook is mostly designed for people who have
screwed around with the spelllist, it may be easiest of anyone who
uses it renumber their spells appropriately (I have no idea if this
breaks the AIs- I made my spells 101- so the AIs could keep using 1-64
until I rewrote them :). If you don't want to do this, you'll have to 
rewrite the loop to take that into account- easiest way would be to
repeat the loop twice, once starting at 1 and once at 101.

Anyway, fillwop will need to be run anytime spells.cfg is changed by
adding or subtracting spells, or by changing words of power.

Fillwop creates the list of legal spells that can be cast with the .cast
player command, which is used by typing ".cast <WoP>", for instance:
".cast In Son" would cast Melody. (SON, by the way, is the Gargish word
for "sound"- it is revealed in Ultima VI that Gargoyles speak the 
language of magic, so I pilfered the word from there. If you prefer,
you could use Quas and declare the sound to be illusionary.)

Any spells that get cast through this spellbook need to include the
spellinc file, and call CleanUp(caster) at each return point. CleanUp
removes the cprop that tells the casting script that you are already
casting a spell and thus neither the spellbook nor .cast should allow
you to cast another one until that property is removed.

The seer command .fillspellbook does just what it says.

Please report any bugs or feature requests to burra@alum.rpi.edu.