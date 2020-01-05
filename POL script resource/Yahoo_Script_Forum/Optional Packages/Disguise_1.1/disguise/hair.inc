function hairgump(who)
	var layout :=
	{
		"nodispose",
		"page 0",
		"noclose",
		"resizepic 10 10 3600 235 460",
		"text 55 30 500 0",
		"gumppic 35 50 96",
		"button 35 430 2076 2075 1 0 1",
		"button 160 430 2121 2120 1 0 0",
		"page 1",
		"radio 35 65 2151 2154 0 8251",
		"text 70 70 500 1",
		"radio 35 95 2151 2154 0 8252",
		"text 70 100 500 2",
		"radio 35 125 2151 2154 0 8253",
		"text 70 130 500 3",		
		"radio 35 155 2151 2154 0 8260",
		"text 70 160 500 4",
		"radio 35 185 2151 2154 0 8261",
		"text 70 190 500 5",
		"radio 35 215 2151 2154 0 8262",
		"text 70 220 500 6",
		"radio 35 245 2151 2154 0 8263",
		"text 70 250 500 7",
		"radio 35 275 2151 2154 0 8264",
		"text 70 280 500 8",
		"radio 35 305 2151 2154 0 8265",
		"text 70 310 500 9",
		"radio 35 335 2151 2154 0 8266",
		"text 70 340 500 10",
		"radio 35 365 2151 2154 1 1000",
		"text 70 370 500 11",
	};
	var data :=
	{
		"Select a hair style",
		"Short Hair", "Long Hair", "Pony Tail", "Mohawk", "Pageboy", "Buns", "Afro", "Receeding", "Braids", "Top Knot", "Bald",
	};
	var hairstyle := senddialoggump(who, layout, data);


	if (hairstyle[1] == 1)
		foreach key in (hairstyle.keys)
			if (key >= 1000)
				hairstyle := cint(key);
				break;
			endif
		endforeach
		
		return hairstyle;
	endif
endfunction

function beardgump(who)
	var layout :=
	{
		"nodispose",
		"page 0",
		"noclose",
		"resizepic 10 10 3600 235 460",
		"text 35 30 500 0",
		"gumppic 35 50 96",
		"button 35 430 2076 2075 1 0 1",
		"button 160 430 2121 2120 1 0 0",
		"page 1",
		"radio 35 65 2151 2154 0 8254",
		"text 70 70 500 1",
		"radio 35 95 2151 2154 0 8255",
		"text 70 100 500 2",
		"radio 35 125 2151 2154 0 8256",
		"text 70 130 500 3",		
		"radio 35 155 2151 2154 0 8257",
		"text 70 160 500 4",
		"radio 35 185 2151 2154 0 8267",
		"text 70 190 500 5",
		"radio 35 215 2151 2154 0 8268",
		"text 70 220 500 6",
		"radio 35 245 2151 2154 0 8269",
		"text 70 250 500 7",
		"radio 35 275 2151 2154 1 1000",
		"text 70 280 500 8",
	};
	var data :=
	{
		"Select a facial hair style",
		"Long Beard", "Short Beard", "Goatee", "Mustache", "Short Beard & Must.", "Long Beard & Must.", "Vandyke", "Bald",
	};
	var hairstyle := senddialoggump(who, layout, data);

	if (hairstyle[1] == 1)
		foreach key in (hairstyle.keys)
			if (key >= 1000)
				hairstyle := cint(key);
				break;
			endif
		endforeach
		
		return hairstyle;
	endif
endfunction
