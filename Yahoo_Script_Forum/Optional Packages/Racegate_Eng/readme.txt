Shrine of the Moons Racegate-Script [V1.5]

This is a Rewrite of Dream Weavers Racegate-Script.

It features several basics:
like Stat-Mods (Str,Int,Dex), Visual-Mods (Graphics,Skin-Color,Gender-Depending Hairstyle).
And also allows you to set a Racename(Gender-Depending).

And you may be also able to change the Race afterwards to 
Half-Elves/Drow/Dwarfs/...(count as Elves/Drow/Dwarfs/...) 
by just changing the TitleRace-Property.

Just copy the racegate.src and the racegate.ecl into your scripts\items directory and append
the Example-Racegates to your Itemdesc.cfg.

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

Item 0x9000
{
     Graphic         0x0F6C
     Name            Gate of the Elves
     WalkOnScript    racegate
     SaveOnExit      1
     Movable         0
     Facing          1
     Color           1310
     cprop color     i1310
     cprop strmod    i-5
     cprop dexmod    i10
     cprop intmod    i10
     cprop racename  sElf
}

Item 0x9001
{
     Graphic         0x0F6C
     Name            Gate of the Dwarfs
     WalkOnScript    racegate
     SaveOnExit      1
     Movable         0
     Facing          1
     Color           743
     cprop color     i743
     cprop strmod    i15
     cprop dexmod    i5
     cprop intmod    i0
     cprop racename  sDwarf
}

----------------------------------------

Feel free to edit these or create new races,
but don't forget to change the Racegate.src 
and to recompile the script.