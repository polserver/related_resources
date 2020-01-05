QuestTools v0.1
Release: 04-Dec-1999
By: Sigismund

======================================================================
Installation Instructions:

- Unzip this package into a nice package directory, lile /pkg/tools
- Move the contents of the /tools/textcommand directory somewhere into
  the  /scripts/textcmd directory, depending on what level of staff
  you want playing with the tools.   For example, to let seers or
  higher use these commands, put them in /scripts/textcmd/seer
- Ecompile the /pkg/tools directory, as well as the new commands in
  the textcmd directory
======================================================================
Contents, by Version:

*** v0.1 ***

     Spawnpoint:
          spawn control - creates a TUS-style single spawnpoint.  To
          use, just double click the spawnpoint.   The .hidespawn and
          .showspawn commands will conceal and reveal the spawnpoints.

     WordOfPowerGate:
          "word of power" operated gate.  It will remain shut until a
          player speaks the correct words of power.  The words of
          power are CASE SENSITIVE.  The .setwordofpower command will
          let you adjust the words for each gate.  You can change the
          appearance of the gate to something appropriate to it's
          surroundings by using the .setprop graphic <newpic> and
          .setprop <color> commands.

    Censor
          censors are items that punish players for speaking dirty
          words.   Note, this doesn't have to be profanity, you can
          specify any words that fit your campaigns.  Just change,
          delete, or add anything you want to the "var profanity"
          declaration in the censor.src, then recompile.   Currently,
          the punishment is rather harsh.


======================================================================
Questions?  Comments?  Vapid hostilities?   Contact me at:

        e-mail: prostheticdelirium@worldnet.att.net
        ICQ: 10520050

Sigismund
