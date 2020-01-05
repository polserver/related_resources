//////////////////////////////////////////////////
//
//   Shinigami's Book-Package v1.01 (2000/02/26)
//
//   Usage: DoubleClick a Book
//
//   Author: Shinigami
//   eMail : Shinigami@gmx.net
//
//   Dependencies: gumputil.inc
//
//////////////////////////////////////////////////

Installation:
  Disable the Item 0xff0 in /pol/config/itemdesc.cfg
  Copy my Package to /pol/pkg/opt/book/*
  Move gumputil.inc to /pol/scripts/inlcude (u can find new versions
    at OneList/pol-scriptforum/Includes/gumputil.zip)
  Restart your server (only necessary after changing itemdesc.cfg)

Book-Creation:
  ".create 0xff0" or "0xfef", "0xff1", "0xff2", "0xff3", "0xff4"

Usage:
  After DoubleClick you can read and write your Book and... just, check it out
  (it's easy to use :)

Problems and next Implementations:
  Look at my ToDo-List (in book.src :)

Shini

////////////
// History
////////////

2000/02/24 v1.0  - First official Release
2000/02/26 v1.01 - gumputil.inc patched, German Umlauts are usable
                   new Book-Items (0xfef..0xff4 thanks bzagh :)
                   problem with 0xfef and pkg/std/tailoring
                     (Recalac, the scripter, is informed)

//////////////////////
// Original Location
//////////////////////

www.egroups.com

  www.egroups.com/files/pol-scriptforum/OptionalPackages/book.zip
  www.egroups.com/files/pol-scriptforum/Includes/gumputil.zip
