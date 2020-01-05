Shrine of the Moon Advanced-Teleporting-TextCommand [v1.2]

This is a Rewrite of the Distro tele.src and mtele.src Scripts.

It features flame-teleporting (if visible) and multi-teleporting in one script.
If you want to teleport once, just click on the target-area.
If you want to Multi-Teleport, first click on yourself and enjoy the Multi-Teleport-Feature.
If you want to leave Multi-Teleporting just click on yourself again or push ESC!

Just copy the tele.src in your scripts\textcmd\coun and replace your old tele.src (create a BackUp).
Afterwards create the Flame-Item in your Itemdesc.cfg! We created the flame as Item because otherwise it would
have the wrong facing!

Editet by

SoM-Scripting-Team o|0|o


Feedback:

If you have questions or bugfixes, please post them to the POL-Scripting Forum.

If you would prefer a German-Version mail to:

St.Gero@gmx.de

We hope you're enjoying our ReWrite!

----------------------------------------

Append these Items to your Itemdesc.cfg:

----------------------------------------

Item 0xFF05
{
     Name            flame
     Graphic         0x3709
     Desc            flame
     Facing          1
     SaveOnExit      0
     Movable         0
}

Feel free to edit the script and the flame, but don't forget to recompile!