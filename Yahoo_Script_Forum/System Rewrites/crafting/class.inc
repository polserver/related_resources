

function modify_points(who, skillid, points)
local skillname := "sk" + cstr(skillid);
local skillval := getobjproperty(who, skillname);

if (!skillval)
	return points;
endif

case (skillval)
	"1": local bonus := getglobalproperty("primary_bonus");
	     return cint(points*bonus);
	"S": local bonus := getglobalproperty("class_bonus");
	     return cint(points*bonus);
	"P": local pen := getglobalproperty("penalty_skill");
	     return cint(points*pen);
	"D": return 0;
endcase	
endfunction

function can_use(character, skill)
local skillname := "sk" + cstr(skillid);
local skillval := getobjproeprty(who, skillname);

if (skillval = "D")
	return 0;
else
	return 1;
endif
endfunction	       	     	     