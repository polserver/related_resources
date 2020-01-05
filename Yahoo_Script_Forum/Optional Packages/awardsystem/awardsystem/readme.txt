Name awardsystem
Version 0.1
Requires gumps 2.1
Requires raceclasssys 0.1
Maintainer M.o.E
Email m.o.e@moe99.cjb.net

These sripts are published without any warranty, they are not completely tested so there could (will)
be some bugs in them. If you find a bug, fix it and send the fix to me, please. If you can't fix the
bug send it to me (m.o.e@moe99.cjb.net) with exact desciptions of the bug and how to reproduce it
(with example code). If my time permits, I'll then try to fix it.

Intro:
The awardsystem is a simple system to give the character some goodies if he/she fulfills some
conditions. The goodies will be deleted from the awardbook if the char not fulfills the conditions
anymore because of stat los or anything else.
Basically there is a gump (awardbook) which have to be melted with a specific character
and only works for that character. Simply it lists the chars awards and the char can use these from
the book (starts a specified script).

Files in the package:
1.Basic System:
pkg.cfg (pkg/opt/raceclasssys): Package config file.

ctrl_reg.src (pkg/opt/raceclasssys): Script to register this package with the control package.

awardbook.src (pkg/opt/awardsystem): The script for the awardbook gump.

awardcaninsert.src (pkg/opt/awardsystem): Simply not permits anything to insert into the book.

awardoninsert.src (pkg/opt/awardsystem): Simply not permits anything to insert into the book.

awardcheck.src (pkg/opt/awardsystem): Controlscript which checks constantly if the char fulfills
the conditions for new awards and starts the autostart scripts.
Here you can modify the delay (WAITDELAY) between the checks.

itemdesc.cfg (pkg/opt/awardsystem): The definition of the awardbook.

awardsystem.cfg (pkg/opt/awardsystem): The definitions of the awards with its conditions.
Here a description of the possibilities:
You can use all or only one of the conditions, but you have to define a script.

Award <award>
{
  Name        <Awardname>               // Name of the award
  Script      <Awardscript>             // Script of the Award
  SkillOr     <SkillId> <min skill>     // Necessary skill and min skill amount (check with OR)
  SkillOr     <SkillId> <min skill>     // Necessary skill and min skill amount (check with OR)
  .
  .
  .
  SkillAnd    <SkillId> <min skill>     // Necessary skill and min skill amount (check with AND)
  SkillAnd    <SkillId> <min skill>     // Necessary skill and min skill amount (check with AND)
  .
  .
  .
  Stat        strength <value>          // Strength needed      (check all stats with AND)
  Stat        dexterity <value>         // Dexterity needed     (check all stats with AND)
  Stat        intelligence <value>      // Intelligence needed  (check all stats with AND)
  Class       <Classname>               // Class permitted (none -> all permitted)
  Class       <Classname>
  .
  .
  .
  Race        <Racename>                // Race permitted (none -> all permitted)
  Race        <Racename>
  .
  .
  .
  Graphic     <graphic value>           // restricted to graphic value e.g. 0x000c
  .
  .
  .
  Autorun     1                         // script runs automatic every control script cycle
}

The script you call don't have to be in the awardsystem pkg, it can be called anywhere, but it must
have the character as the first and only parameter.
The autorun scripts must have an array as parameter with param[1] := character and param[2] := 0 or 1.
The second param is the clean flag to notify the script that the award was deleted form the chars
awardbook and so, if necessary do some cleaning (erase some cprops from char or something else).

Thats all in general, but there are some scripts ready to use and as examples for both simple and
autorun scripts.

2.Example scripts:
autores.src (pkg/opt/awardsystem): An autorun script which gives the char auto resurrection.

berserk.src (pkg/opt/awardsystem): Berserker possibility for warriors.

firebreath.src (pkg/opt/awardsystem): Fire breath e.g. for dragons (used from my shapechanching pkg).

hpregeneration.src (pkg/opt/awardsystem): Faster regeneration of the chars hit points, depending on
strength stat. (autorun)

manaregeneration.src (pkg/opt/awardsystem): Faster regeneration of the chars mana points, depending
on intelligence stat. (autorun)

stamregeneration.src (pkg/opt/awardsystem): Faster regeneration of the chars stamina points,
depending on dexterity stat. (autorun)

nightsight.src (pkg/opt/awardsystem): Gives nightsight. (autorun)

mirroring.src (pkg/opt/awardsystem): Creates a mirror npc of the char. (my pcmirror ai scripts
necessary)

Comments:
I use these scripts with my Race/Class-System but it will be easy to eleminate this dependency or
modify them for your favorite Race/Class-System. (You only have to change awardcheck.src).

Feedback:

If you have questions or bugfixes, please send them to m.o.e@moe99.cjb.net
Also positiv feedback are welcome.

