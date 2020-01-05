<html><head><title>Mytharrian Vendors</title></head><body bgcolor="#000000" text="#FFFFFF" link="#FF0000" vlink="#FF3300" alink="#0000CC">

Mytharrian Vendors
<p>&nbsp;</p>
<p>The following is a list of the vendors currently working in the employ of
Mytharrian craftspeople. We would encourage you to patronize these merchants to
improve our local economy. You can click on the vendor's name to get a current
inventory.</p>
<p align="center">&nbsp;</p>
<div align="left">
  <table border="1">
    <tr>
      <td>
        <p align="center">Name</td>
      <td>
        <p align="center">Master</td>
      <td>
        <p align="center">Contact</td>
      <td>
        <p align="center">Location (x,y,z)</td>
    </tr>
    
<%

use uo;
use http;
writehtml("<span STYLE=\"position:absolute; top:520; left:0\">");    
var venstruct := struct;
venstruct.+name;
venstruct.+x;
venstruct.+y;

var vens := {};


var venlist := getglobalproperty("pcvendors");

if (!venlist)
        writehtml("<tr><td>Sorry! No vendors are registered yet!</td></tr>");
        return;
endif

var ven;

foreach ven in venlist        
	
        var vn := systemfindobjectbyserial(cint(ven));
        
        var tn := vn.name;
        tn[",",1000] := "";
        var venname := "<a href=vendor.ecl?vs=" + ven + ">" +tn + "</a>";
        venstruct.name := venname;
        venstruct.x := ( vn.x / 8.125);
        venstruct.x := ( vn.y / 8.008);
        vens.append(venstruct);
        var mastername := getobjproperty(vn, "mn");
        
        var contact := getobjproperty(vn, "cont");
        if (!contact)
        	contact := "unlisted";
        endif
        
        var loc := "(" + vn.x + " , " + vn.y + " , " + vn.z + ")";
        if (vn)
        	writehtml("<tr><td>" + venname + " </td><td>" + mastername + " </td><td>" + contact + " </td><td>" + loc + " </td></tr>");
        endif
endforeach

/*
var q;
writehtml("</span>");
foreach q in vens
	writehtml("<P STYLE=\"position:absolute; top:" + q.y + "; left:" + q.X + "\">" + q.name + "</P>");
endforeach
writehtml("<IMG SRC=\"mythmap.gif\" STYLE=\"position:absolute; top:0; left:0; z-index:-1\">");
*/
%>    

  </table>
</div>
</BODY></HTML>

