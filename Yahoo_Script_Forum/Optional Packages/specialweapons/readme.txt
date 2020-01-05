I see a lot of questions on how to make a sword or other item do an animation whenever it hits so I made this very simple package to illustrate the concept.

All I did was take the longsword weapon and copy it into the itemdesc.cfg of this package and set a graphic, change the paths to equip, uequip, control and destroy scripts and  to it and add two lines:
    CProp           type sexplosion
and
    HitScript       specialHit

The HitScript line tells POL to use the specialHit.src in this package and the type CProp tells the specialHit script what kind of weapon it is. Right now there are only two "types" of weapons--explosion and lightning. But I think it's enough to give you an idea of how it's done.

To install this package just copy the pkg folder into your POL root directory and it should make a folder called specialweapons in /pkg/opt with everything you need to get started. To add one of the items in the game just type .create lighting_hammer or .create explosion_sword and that's it.

If you have any questions or comments let me know at tekproxy@yahoo.com. If enough people are interested and give me input I could make a few other special weapons.