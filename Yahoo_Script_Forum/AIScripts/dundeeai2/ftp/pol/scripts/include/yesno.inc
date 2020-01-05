use uo;

function YesNo(me, Prompt)

	var layout := array(
                        "page 0",
                        "gumppic 0 0 2070",
                        "button 30 75 2130 2129 1 0 1",
                        "button 90 75 2119 2120 1 0 0",
                        "text 40 30 1355 0",
                        
	);

	var data := array(  Prompt  );
           
	var res := SendDialogGump( me, layout, data );

	if (res)
		return 1;
	else
		return 0;
	endif
	
endfunction
