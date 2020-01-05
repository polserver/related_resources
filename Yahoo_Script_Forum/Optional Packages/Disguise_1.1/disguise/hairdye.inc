function hairdye(who)
	var layout :=
	{
		"nodispose",
		"noclose",
		"page 0",
		"resizepic 0 0 3600 400 450",
		"resizepic 15 15 5054 120 420",
		"resizepic 145 15 5054 200 380",
		"button 145 405 2076 2075 1 0 -1",
		"button 200 405 2121 2120 1 0 -2",
	};
	var data :=
	{
	
	};
	
	var config := readconfigfile(":barber:hairshades");
	
	var pagenum := 2;
	var y := 25;
	
	foreach hairtype in GetConfigStringKeys(config);
		layout.append("button 30 " + (y+3) + " 5224 5224 0 " + pagenum);
		
		layout.append("page " + pagenum);
		var count := 1;
		var buttonx := 150;
		var buttony := 20;
		
		foreach color in getconfigstringarray(config[hairtype], "color")
			color := cint(color);
			data.append(hairtype);
			layout.append("text " + (buttonx+20) + " " + buttony + " " + color + " " + (len(data)-1));
			layout.append("radio " + buttonx + " " + buttony + " 210 211 0 " + color);
			if (count == 1)
				buttonx := buttonx + 100;
				count := 2;
			else
				buttonx := 150;
				buttony := buttony+20;
				count := 1;
			endif
		endforeach
		
		pagenum := pagenum+1;
		data.append(hairtype);
		layout.append("page 0");
		layout.append("text 60 " + y + " " + config[hairtype].titlecolor + " " + (len(data)-1));
		y:=y+25;
	endforeach
	
	var input := senddialoggump(who, layout, data);
	
	if (input[0] == -2)
		SendSysMessage(who, "Cancelled");
		return -1;
	endif
	
	foreach key in (input.keys)
		if (key >= 0)
			input := key;
		endif
	endforeach
	
	return input;
endfunction