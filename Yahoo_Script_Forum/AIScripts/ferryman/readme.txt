Ferryman NPC script
By Brian Docherty
Last Modified; 20th Feb 2001

This script was brought about by the awful bridge between the mainland and Skara Brae.  I've destroyed the mid part of the bridge and put a ferryman at each side (Just like an origin shard) and added a couple of boats for decoration.
You can configure the ferryman to take you to any X,Y,Z co-ordinate, set a price and a destination name.

Instructions;
1. Copy the template below into npcdesc.cfg in \pol\config
2. Put ferryman.src into your \pol\scripts\ai folder and compile

In game, a person with command level greater than 2 can configure the ferryman.
3. Do a .createnpc ferryman to position your ferryman on the docks (or wherever)
4. Use the following commands to set him up;
      setx <Return> - To set the target X co-ord
      sety <Return> - To set the target y co-ord
      setz <Return> - To set the target z co-ord
      setprice <Return> - To set how many gps for the voyage
      setdestname <Return> - To set the destination name (eg. Skara Brae, or the mainland, etc)
      settings <Return> - To get the ferryman to show you the destination co-ords (for checking)

Thats it.

Player commands are;
      hail or hello - The ferryman will report on where he will take you and for what price.
      cross - The ferryman will take the required gold and transport you to the destination co-ords.

I know it's only very basic and bits have been ripped from other scripts, but it's still very useful.
In my shard I will set up ferries to Buccs Den from Trinsic, and Buccs Den to Magincia.

Regards, Brian


NpcTemplate ferryman
{
    Name                <random> the Ferryman
    script              ferryman
    
    ObjType             0x190
    Color               33784
    TrueColor           33784
    Gender              0
    STR                 200
    INT                 200
    DEX                 200
    HITS                200
    MANA                200
    STAM                200
    Inscription         90
    Magery              70
    Cartography         60
    Wrestling           50
    Tactics             50
    CProp       Equipt       smerchant
    Privs               invul
    Settings            invul
    guardignore         1
    alignment           good
    speech              26
    Wrestling           100
    AttackSkillId       Wrestling
    AttackSpeed         80
    AttackDamage        5d100
    dstart              2
    psub                50
}
