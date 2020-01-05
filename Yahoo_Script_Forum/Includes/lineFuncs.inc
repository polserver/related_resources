//////////////////////////////////////////////////////////////
//
//  Line Functions
//  by Madman Across the Water
//
//  Version 0.4
//
//  This contains, so far, three functions.
//  dist_to_line - pass it the x,y of a point, and the x,y or a start and end point
//                 for a line segment, and it will return the shortest distance 
//                 between the point and the line. If that shortest line intersects
//                 the line outside the line segment, the function returns "null".
//
//  truedist     - pass it two points and it returns the distance between them.
//
//  ListMobilesInLine  - pass it start and end points for a line segment and the
//                       width of the line, and it will return an array of all 
//                       creatures on that line. Mostly for use for stationary
//                       beam effects.
//
//////////////////////////////////////////////////////////////


use math;

function dist_to_line(pointx, pointy, line1x, line1y, line2x, line2y)
    if (line1x = line2x)     // it's a vertical line, infinite slope
       if (((pointy > line1y) and (pointy > line2y)) or ((pointy < line1y) and (pointy < line2y)))
         return("null");
       endif
       return(abs(pointx - line1x));
    elseif (line1y = line2y) // horizontal line- normal slope is infinite
       if (((pointx > line1x) and (pointx > line2x)) or ((pointx < line1x) and (pointx < line2x)))
         return("null");
       endif
       return(abs(pointy - line1y));
    endif
    var slope := ((line1y-line2y)*1.0)/(line1x-line2x);
    var b := line1y - slope*line1x;
    var normal := -1.0*(1/slope);
    var normalb := pointy - normal*pointx;
    var interx := (normalb-b)/(slope-normal);
    var intery := slope*interx+b;
    if ((((interx < line1x) and (interx < line2x)) or ((interx > line1x) and (interx > line2x))) and ((intery < line1y) and (intery < line2y)) or ((intery > line1y) and (intery > line2y)))
      return("null");
    endif
    return(truedist(pointx, pointy, interx, intery));    
endfunction

function truedist(point1x, point1y, point2x, point2y)
    return(CInt(Sqrt(Pow((point1y-point2y),2) + Pow((point1x-point2x),2))));
endfunction

function ListMobilesInLine(x1,y1,x2,y2,z0,width := 1)
    var centerx := CInt(ceil((x1+x2)/2.0));
    var centery := CInt(ceil((y1+y2)/2.0));
    syslog("x:" + centerx + " y:" + centery);
    var nearbymobs := ListMobilesNearLocationEx(centerx, centery, z0, truedist(x1,y1,centerx,centery), LISTEX_FLAG_NORMAL+LISTEX_FLAG_HIDDEN);
    syslog(nearbymobs);
    var closemobs := array;
    foreach mob in nearbymobs
      var mobdistance := dist_to_line(mob.x, mob.y, x1, y1, x2, y2);
      syslog(mobdistance);
      if ((mobdistance <= (width/2.0)) and (mobdistance != "null"))
        closemobs.append(mob);
      endif
    endforeach
    return(closemobs);
endfunction
