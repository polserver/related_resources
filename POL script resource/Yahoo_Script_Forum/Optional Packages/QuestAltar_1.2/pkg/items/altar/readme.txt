Quest Altar 1.2
(c) 2003-2004 Keelhaul
Keelhaul@t-online.de

Written using the 0.95 POL core.

Description
-----------
The quest altar scans its surface for assigned items. If a correct item has been
placed, it is consumed by flames, otherwise nothing happens. Once all correct items
have been consumed, it either destroys assigned obstacle items (no multis), unlocks
assigned doors/containers or kills assigned mobiles.

Instructions
------------
- create an altar tile (item id: "altartile")
- select the desired mode (aftereffect): destroying an item or unlocking a door/container
- select aftereffect targets, press ESC to continue once all targets have been assigned
- select items, press ESC to continue once all items have been assigned
- after the items have been targeted, the altar is active
- players must place all selected items onto its surface to complete the sequence
- the altar will then perform the selected aftereffect

Notes
-----
- "items" are items to be placed on the altar, "targets" are items or mobiles to be
  handled by the altar once all items have been placed
- once the sequence has been completed, the altar no longer scans its surface for items,
  but the script will continue to run until the tile is destroyed
- items are identified by their objtype, so it is recommended to use items with unique
  objtypes (e.g. custom items)
- you must select at leat 1 target, or the setup procedure will abort
- you must select at least 1 item, or the setup procedure will abort
- items may not have the same objtype, an item of the same type will be only assigned once
- tile surface is blue while active (scanning), otherwise grey
- if a Seer or above double clicks the tile while it is active, it will can be reset and
  the staff member will be prompted to set it up
- if the default objtype of the altar tile is already taken on your shard, assign a new one
- you may change the altar graphic, but make sure it's not too hard to place items onto it

Version history
---------------
1.2
Changes:
- an infinite amount of items can now be assigned (as opposed to max 3 items in previous
  versions), read the instructions
- an infinite amount of targets can now be assigned (as oppoest to max 1 target in
  previous versions), read the instructions
- added new aftereffect: killing a targeted mobile
- all online staff will now be notified when a correct item has been placed on the altar
  (including its number) and once the sequence has been completed

1.1
Fixes:
- the staff member who set up the altar will no longer have to stay online until the
  altar sequence has been completed; before, the script would stop
- other staff members also will be able to control the same instance of the altar script,
  as the altar now works independently
- players will now only be prompted to place items on the altar if it's active (blue)
- the flame strike effect will now only play once after an item has been accepted
Changes:
- some fixes required a change to the whole script structure, the script file was split
  up into a control script and an interface script
- staff will now be prompted whether the altar should be reconfigured upon double click
- mode selection now uses gump with buttons instead of prompting for a number
- added 'Version History' and 'Credits' sections to this file

1.0
- initial release

Credits
-------
Bishop Ebonhand, Folko and MuadDib for EScript assistance.