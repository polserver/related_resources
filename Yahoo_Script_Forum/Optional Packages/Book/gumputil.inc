/////////////////////////////////////////////
//
//  Shinigami's GumpUtil v1.02 (2000/04/29)
//    (some nice Functions for Gumps)
//
//  Author:    Shinigami
//  eMail:     Shinigami@gmx.net
//  Languages: English/German
//
/////////////////////////////////////////////

/////////////////
// Installation
/////////////////
//
// Move it to /pol/scripts/include and use it in your script:
//   Include "include/gumputil";

//////////////
// Functions
//////////////
//
// GumpTextWidth(gumptext)           // Returns the Width of GumpText
// GumpTextWidthFast(gumptext)       // Returns the Width of GumpText
// GumpTextLeft(gumptext, x, width)  // Returns the X-Value (Left-Alignment)
// GumpTextRight(gumptext, x, width) // Returns the X-Value (Right-Alignment)
// GumpTextMid(gumptext, x, width)   // Returns the X-Value (Mid-Alignment)
//
//   Parameters:
//     gumptext - a String
//     x        - X-Value from the Textbox
//     width    - Width from the Textbox
//
// Create_ScrollBar(x, y, height, pages, page, layout) // Shows a Scrollbar
//
//   Parameters:
//     x,y    - X-/Y-Value of the left-top Corner
//     height - Height
//     pages  - Number of Pages
//     page   - Actual Page Number
//     layout - Contains the actual Gump Layout
//   Returns:
//     Updated "layout"

//////////////////////
// Original Location
//////////////////////
//
// www.egroups.com
//
//   www.egroups.com/files/pol-scriptforum/Includes/gumputil.zip

///////////////////////////////////////////////////////////////////////////////

//////////////
// Constants
//////////////

Global c34:=CChr(34);

Global length:={ };
       length.+chars:={
         "",                   // Dummy (for Speed...)
         "|",                  //  2
         "`',.;:",             //  3
         c34+"!",              //  4
         "il1[]",              //  5
         "bcejotîˆ(){}=",      //  6
         "adfpqrszIÑ‰~",       //  7
         "ghnuvyÅ¸ <>-",       //  8
         "xJ578$?ﬂ+",          //  9
         "kCE2369^/*",         // 10
         "mwABDFOPéƒô÷40%",    // 11
         "GLNQSZ#",            // 12
         "HRT&_",              // 13
         "Kö‹UY",              // 14
         "X",                  // 15
         "V",                  // 16
         "M",                  // 18
         "W",                  // 21
       };
       length.+charsf:=        // Space as Filler is not allowed
         "|||||||||||||||"+    //  2
         "`',.;::::::::::"+    //  3
         c34+"!!!!!!!!!!!!!!"+ //  4
         "il1[]]]]]]]]]]]"+    //  5
         "bcejotîˆ(){}==="+    //  6
         "adfpqrszIÑ‰~~~~"+    //  7
         "ghnuvyÅ¸ <>----"+    //  8
         "xJ578$?ﬂ+++++++"+    //  9
         "kCE2369^/******"+    // 10
         "mwABDFOPéƒô÷40%"+    // 11
         "GLNQSZ#########"+    // 12
         "HRT&___________"+    // 13
         "Kö‹UYYYYYYYYYYY"+    // 14
         "XXXXXXXXXXXXXXX"+    // 15
         "VVVVVVVVVVVVVVV"+    // 16
         "MMMMMMMMMMMMMMM"+    // 18
         "WWWWWWWWWWWWWWW";    // 21
       length.+width:={
          2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
          12, 13, 14, 15, 16, 18, 21
       };

//////////////
// Functions
//////////////

// Returns the Width of GumpText

Function GumpTextWidth(gumptext)
  Local start_i:=len(length.chars);
  Local points:=0;
  Local j;

  For (j:=len(gumptext); j>0; j:=j-1)
    Local i:=start_i;
    While ((i>0) And (!length.chars[i][CStr(gumptext[j])]))
      i:=i-1;
    EndWhile;
    If (i>0) // siehe Speed-Dummy
      points:=points+length.width[i-1];
    Else
      SysLog("GumpTextWidth: Unknown Character = '"+gumptext[j]+"'");
    EndIf
  EndFor

  Return (points);
EndFunction

// Returns the Width of GumpText

Function GumpTextWidthFast(gumptext)
  Local points:=0;
  Local j;

  For (j:=len(gumptext); j>0; j:=j-1)
    Local i:=Find(length.charsf, gumptext[j], 1)-1;
    If (i>=0)
      points:=points+length.width[CInt(i/15)+1];
    Else
      SysLog("GumpTextWidthFast: Unknown Character = '"+gumptext[j]+"'");
    EndIf
  EndFor

  Return (points);
EndFunction

// Returns the X-Value (Left-Alignment)

Function GumpTextLeft(gumptext, x, width)
  Return (x);
EndFunction

// Returns the X-Value (Right-Alignment)

Function GumpTextRight(gumptext, x, width)
  Return (x+(width-GumpTextWidthFast(gumptext)));
EndFunction

// Returns the X-Value (Mid-Alignment)

Function GumpTextMid(gumptext, x, width)
  Return (x+CInt((width-GumpTextWidthFast(gumptext))/2));
EndFunction

//////////////////////////////////////////////////
// Create_ScrollBar - Erzeugt einen Scrollbalken
//////////////////////////////////////////////////

Function Create_ScrollBar(x, y, height, pages, page, layout)
  If (pages>1)
    Local x_str:=CStr(x)+" ";
    Local button_x_str:="button "+x_str;
    Local gumppic_x_str:="gumppic "+x_str;
    Local page_before:=" 0 "+CStr(page-1);
    Local page_next:=" 0 "+CStr(page+1);

    Local y_mark;
    If (pages=page)
      y_mark:=y+height-46;
      layout.append(gumppic_x_str+CStr(y_mark-7)+" 256");
    Else
      y_mark:=y+CInt((height-67)/(pages-1))*(page-1)+21;
      layout.append(gumppic_x_str+CStr(y_mark)+" 256");
    EndIf
    layout.append("gumppic "+CStr(x+1)+" "+CStr(y_mark)+" 254");

    Local y_bkg;
    Local y_bkg_end;
    If (page>1)
      y_bkg_end:=y+21;
      For (y_bkg:=y_mark-32; y_bkg>y_bkg_end; y_bkg:=y_bkg-32)
        layout.append(button_x_str+CStr(y_bkg)+" 256 256"+page_before);
      EndFor;
      layout.append(button_x_str+CStr(y_bkg_end)+" 256 256"+page_before);
      layout.append(button_x_str+CStr(y)+" 250 251"+page_before);
    Else
      layout.append(gumppic_x_str+CStr(y)+" 250");
    EndIf
    If (page<pages)
      y_bkg_end:=y+height-21-32;
      For (y_bkg:=y_mark+25; y_bkg<y_bkg_end; y_bkg:=y_bkg+32)
        layout.append(button_x_str+CStr(y_bkg)+" 256 256"+page_next);
      EndFor;
      layout.append(button_x_str+CStr(y_bkg_end)+" 256 256"+page_next);
      layout.append(button_x_str+CStr(y+height-21)+" 252 253"+page_next);
    Else
      layout.append(gumppic_x_str+CStr(y+height-21)+" 252");
    EndIf
  EndIf

  Return (layout);
EndFunction
