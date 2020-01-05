Meditation Version 1.0

News On Version 1.0
===================
  - Added Restrition for Armors
  - Fixed some Advancment Bugs

News on Version 0.3
===================

  - Code Cleanup(Thanks Louds)
  - Added restriction to combat mode and things on hands(weapon, shield, etc) and hidden

Instructions
============

Just create a new dir in /pkg/opt and put the files in it. Don't forget to edit /config/skill.cfg
and delete the meditation from there.

Don't Forget to compile all files

How Does it Work?
=================

  Actually the players doens't check a skill. He must start meditate(no skill check needed)
and DO NEED to stay still to it work. The default recovery rate is from 0 to Char Meditation
Skill/10 + 1. For each mana point the player regenerate, he gets some raw points.

How much Armor Takes?
=====================

  For each piece of armor equiped player will loose points of the ones he would gain(Just Plate and Chain take points). Each piece of plate take 2 points(BreadsPlate take 3 and Gorget 1) and each piece of Chain takes 1 Point(Tunic takes 2).
  For example: if a player has equiped a plate helm(2 points) a chain tunic(2 points) and a gorget (1 point) equiped, the points he would loos would be 5(2+2+1), as he has 70.0 on Meditation he can regenerate each 5 seconds, 0-3 of mana, MaxRegen= (Skill/10)+1-Loss.
  Ps.: There is no negative raise.
  

ToDo
====

  Improve the system, anyone got ideas?



Charles Haustron