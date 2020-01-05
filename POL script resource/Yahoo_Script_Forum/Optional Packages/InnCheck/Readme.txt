Inn Check 2.0
by Michael Branin

Files:

incheck.inc      -  Goes in     /pol/scripts/include/
logofftest.src   -  Goes in     /pol/scripts/misc/
bedroll.src      -  Goes in     /pol/pkg/std/camping/
innlocation.cfg  -  Goes in     /pol/config

What it does:

Allows a player to logout instantly in any Inn.  Also Allows a player to logout instantly when the a bedroll is used near a camp fire.

Instructions:

Move all files to locations stated above and compile logofftest.src and bedroll.src
restart server and happy logging.

Note:

Locations for insta log are in innlocation.cfg and are the standard locations for OSI shards.  If you are using a custom map you will need to edit the locations in that file and recompule logofftest.src.

Locations can be added or removed from innlocation.cfg following the template given in there.  For inn that have multiple rectangles follow this template

You define a region by getting the x and y coordinates from two 
opposing corners of a rectangle as if placed on the map. You need the 
NW corner(up on your monitor) coordinate and the SE corner coordinate
(down).

region Northside Inn 1         // name of first region(rectangle) of  northside in
{
rect 1455 1511 1473 1529       // rectangle coordinates X1,Y1   X2,Y2
}

region Northside Inn 2
{
rect 1473 1511 1481 1521
}

