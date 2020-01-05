
You'll need to modify all the spells in the spells package slightly to make use of this. 
They all need to include spellinc.inc (which should be put in the include directory), and
they must all contain the following code, either at the beginning or after any targetting:


	if (parms[1] != "#MOB")   // NPCs have already handled spellcasting in npccast.inc
	  if (!DoCast(caster, THISSPELL))
		CleanUp(caster);
		return;
	  endif
	endif

CleanUp(caster) needs to be placed at all exit points to all spell scripts, ie before any return
and before the endprogram. If you don't, your poor mages will be flagged as "already casting" until
the server restarts. :> Actually, it should be put at any point after which you want your mage to be
able to start casting again, so for spells like firefield you'll want to put it at the detach() call 
rather than the exit.

An explanation of the files:
Seer textcommand: .fillmyspellbook : fills a spellbook of this type.
Player textcommand: .cast : use ".cast <words of power>" to cast a spell. Alternative to using the
   spellbook gump.
spellbook.src : contains the spellbook gump. Reads data in from spelllist.cfg for how to display
   the spellnames. (This gives you the option to find better ways to shorten long spellnames than
   just truncating them.)
spelllist.cfg : contains the spellnames and their spellids. By default, describes OSI's spelllist.
itemdesc.cfg : contains the definition for the new spellbook.
start.src : Creates the global dictionary of words of power that .cast checks against.
castspell.src : called by both the spellbook gump and castspell, it checks to see that you have the
   spell in your spellbook, and that you have enough mana and regs. It does not consume the mana 
   and regs- that is left to the DoCast function. Castspell applies a CProp to the caster with the
   caster's current hit points. This is compared against in BrokeCon to make sure the caster did not
   have his spell interrupted.(DoCast and BrokeCon are, you'll recall, the functions you must add to
   all your spell scripts.) It also checks that there isn't already a casterhp CProp, which implies you're
   still in the middle of a spell.
checkspell.inc : Contains the function that checks if you have the spell in your spellbook.
spellinc.inc : Contains the following included functions:
   BrokeCon : makes sure the caster has at least as many hit points as he started with.
   DoCast : makes the skill check and consumes the regs and mana. Returns false if any of these fail.
   CleanUp : removes the CProp containing the starting hit points.
   hasReagents : used in castspell.src to check if the caster has the reagents necessary without 
      consuming them.
transcribe.src : Adds the spell to the spellbook.
callDestroyItem.src : destroys the scroll after the transcription.
