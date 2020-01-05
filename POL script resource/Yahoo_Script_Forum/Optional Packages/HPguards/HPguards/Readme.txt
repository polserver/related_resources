HPguards v1.0
=============
Written by: Hugo P.L., hugo_pl@bol.com.br

CORE 093-094 INSTALLATION
=========================
Just unzip in any PKG folder, like others PKGs...

CORE 092 INSTALLATION
=====================
Unzip in any PKG folder, like others PKGs...
This PKG was tested with CORE 094... but it will work with CORE093... for CORE092 do it:
in line 68 of instakillguard.src, replace:

ApplyRawDamage( targ, (GetVitalMaximumValue(targ, "Life")/100) + 3);

for:

ApplyRawDamage( targ, targ.maxhp + 3);

compile the script and it will work with CORE92, i think. =P




COMMANDS
========

.guardssetup

Choose which cities will be protected by guards.

.guardinvul

Set guards invulnerability for a NPC or staff member.