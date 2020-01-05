S!tH's Enchanted Weapons/Armour/Monster Hitscript for POL. 
+--------------+
BETA!  UNTESTED!
+--------------+
Thanks go out to:
Scull : For all his coding assistance & looking at the script for me.
Myr : For helping me get the Ownage & GotOwned lists out of the .cfg and into an array!
GM Zulu : For telling me _ALL_ the errors i had in me script stopping it from compiling :P

Make sure you changed the senchantedhit.dep file to suit your POL location!

to get this really cranking for all armours and monsters, every single weapon (including monsters weapons) should have the hitscript enable... regardless of wether its enchanted or not. this is simply so when you hit something with the weapon, it will check wether the monster or the armour requires the damage to be modified. Once the weapons have the hitscript enable on them, you add the enchantments using CProps (explained later)... you can have as many enchantments as you want... it is limited by your imagination only, and of course, your patience of typing :)

for now, ill explain enchantments with the earth enchantment:

//Earth enchantment
SEnchantment_Earth 4
(
	Name SEnchantment_Earth  <-- the CProp you set. "SEnchantment_Earth 1"
	Owns 1                   <-- the numbers (in the CFG) of the enchantments it is higher than. seperate with a space only: "1 7 12 76"
	GetsOwned 3              <-- the numbers (in the CFG) of the enchantments it is lower than. seperate with a space only: "3 9 10 104"
	OwnsAmount 1		 <-- the amount of enchantments it owns. in this case only 1
	GetsOwnedAmount 1 	 <-- the amount of enchantments that own it. in this case only 1
	OwnageMulti 1.4          <-- the damage multiplier for when the weapon is using this enchantment hits an enchantment in the "Owns" list.
	OwnageAdd 2              <-- the damage addition for when the weapon is using this enchantment hits an enchantment in the "Owns" list.
	GotOwnedDiv 1.4          <-- the damage divider for when the weapon is using this enchantment hits an enchantment in the "GetsOwned" list.
	GotOwnedSub 2            <-- the damage subtraction for when the weapon is using this enchantment hits an enchantment in the "GetsOwned" list.
	NormalAdd 2              <-- the damage addition, no matter what you hit with the weapon. if the armour/defender has this enchantment, this becomes subtraction.
	NormalSub 0              <-- the damage subtraction, no matter what you hit with the weapon. if the armour/defender has this enchantment, this becomes addition.
	NormalMulti 1            <-- the damage multi, no matter what you hit with the weapon. if the armour/defender has this enchantment, this becomes the divider.
	NormalDivis 1            <-- the damage divider, no matter what you hit with the weapon. if the armour/defender has this enchantment, this becomes the multiplier.
)

now you can mess with the damage quite a lot with this, but theres no spell-casting or anything at the moment (possibly later, if its requested.)

the .src is _FULLY_ documented... codes pretty messy tho sorry :/

!VITAL!
+-------------------+
to set an enchantment
+-------------------+
set the CProp "SENCHANTED 1" on the Weapon, Armour or NPC, so the script knows to check for enchantments.

set the CProps for all the enchantments you want on it, like:

SEnchantment_Earth 1
SEnchantment_Wind 1
My_Custom_Enchantment 1 
My_Second_Enchantment 1

------------------------------------------------------------+
Included txtcmd\gm\getcprop-setcprop.                       |
not sure if these work too well :)			    |
but i couldnt find the default ones for it anywhere,        |
so heres a way for GMs to set the enchantments in-game :)   |
------------------------------------------------------------+

Cheers

S!tH