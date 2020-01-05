function requestgump(byref mobile, byref question, byref option := "", preval := "")
	//Mobile = Character input gump is sent to.
	//Question = Question to ask.
	//Option = Optional text to put under the question.
	//Preval = What you want them to see in the text area when it comes up.

	if (!preval || preval == error)
		preval := "";
	endif
	var  layout :=
	{
		"page 0",
		"noclose",
		"resizepic 10 140 3600 320 200",
	
		"text 35 170 500 0",
		"text 35 185 500 1",
		"gumppic 35 215 1141",
		"textentry 45 217 250 25 500 2 2",
		"button 150 290 2076 2075 1 0 1",
	};
	var data :=
	{
		question,option, preval,
	};
	var gumpinput :=  SendDialogGump(mobile, layout, data);
	gumpinput := gumpinput[2];
	gumpinput := gumpinput[4, len(gumpinput)];
	
	if (!gumpinput || gumpinput == error)
		return 0;
	else
		return gumpinput;
	endif
endfunction