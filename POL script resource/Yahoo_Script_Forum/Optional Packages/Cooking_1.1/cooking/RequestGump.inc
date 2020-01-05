//
// 1.1
// 
// RequestGump.inc
//
// By Austin Heilman
// Aheilman@home.com
//
// A simple input gump with yes/no button options.
//
// Created 6/18/2001 9:56AM
// Modified 6/18/2001 9:56AM
//


function requestgump(byref mobile, byref question, byref option := "", preval := "", cancelbutton := 0)
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
		"resizepic 10 140 3600 320 160",
	
		"text 35 165 500 0",
		"text 35 185 500 1",
		"gumppic 35 215 1141",
		"textentry 45 217 250 25 500 2 2",
	};
	var data :=
	{
		question, option, preval,
	};
	if (cancelbutton)
		layout.append("button 85 250 2076 2075 1 0 100");
		layout.append("button 200 250 2121 2120 1 0 200");
	else
		layout.append("button 150 250 2076 2075 1 0 100");
	endif
		
	var GumpInput :=  SendDialogGump(mobile, layout, data);
	
	var TextArea := GumpInput[2];
	TextArea := TextArea[4, len(TextArea)];
	
	if (GumpInput[200])
		return 0;
	elseif (!TextArea || TextArea == error)
		return 0;
	else
		return TextArea;
	endif
endfunction