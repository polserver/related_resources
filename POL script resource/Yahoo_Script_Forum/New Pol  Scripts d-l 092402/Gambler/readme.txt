Gambler version 1.0
by Zulu (zulu@zuluhotel.com)   November 12, 2000

==================================================

1. Installing the auction system
   copy gambler.src to directory \pol\pkg\scripts\ai\

2. Copy the follow to \pol\config\npcdesc.cfg

3. To create a gambler type .createnpc gambler or put in a spawn

NpcTemplate gambler
{
    Name        <random>
    script      gambler

    ObjType     0x190
    Color       33784
    TrueColor   33784
    Gender      0
    STR         200
    INT         200
    DEX         200
    HITS        200
    MANA        200
    STAM        200

    Tactics       100
    MaceFighting  140
    
    AttackSpeed         55
    AttackDamage        2d100
    AttackSkillId       MaceFighting
    AR                  32
    Privs               invul
    Settings            invul

    guardignore     1
    dstart          10
}
