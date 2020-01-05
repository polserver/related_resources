//Utilitys for merc

// ** Requires Shinigami's Book-Package v1.01 to be installed **
const CREATE_HELPBOOK := 0;

function EquiptMerc(merc)

	local meNewPrice := 0;

	if (!merc.backpack)
		local newbackpack := CreateItemAtLocation(5288 , 1176 , 0, 0xe75,1);
		if (!EquipItem(merc, newbackpack)) DestroyItem(newbackpack); endif
	endif

	if (merc.strength < 40)
		meNewPrice := meNewPrice + 200;	
	elseif (merc.strength < 50)
		meNewPrice := meNewPrice + 500;	
	elseif (merc.strength < 60)
		meNewPrice := meNewPrice + 1000;	
	elseif (merc.strength < 70)
		meNewPrice := meNewPrice + 2000;	
	elseif (merc.strength < 80)
		meNewPrice := meNewPrice + 4000;	
	endif

	if (CREATE_HELPBOOK)
		local helpbook := CreateItemInBackpack( merc, 0x0ff0 ,1);
		SetObjProperty(helpbook, "writeable", 0);

		var booktext := {};
		booktext[1] := {"Mercenary Guide", "", "Merc LeaderShip", "by" , merc.name, ""};
		booktext[2] := "
		Command Note: most of these commands require the mercenarys name infrom of them. ie BOB attack.
		 * Action: follow, attack, kill, guard, camp, loot, carve, help
		 * Freindlist: friend, enemy, remove, removeall
		 * Passive: quote, battlecry, ride/mount, autoloot
		 * Helpfull: release, skill, report, version, wash
		 * Equip: rearm, wear, undress
		 *** NOTES: To open a mercs backpack, stand next to it and double click on him. Mercs can use potions. Mercs can train on Dummys. Mercs like bandages.";

		SetObjProperty(helpbook, "bookcontent", booktext);
	endif


	CreateItemInBackpack( merc, 0x0e21 , 10 + randomInt(30)); //Bandages
	create_rand_food(merc);
	start_script("::/misc/mercdress", merc);
	SetRawSkill(me,Getweapon(),BaseSkillToRawSkill(RandomInt(200)+300));

	if(GetEquipmentByLayer( merc, 25 ))
		MountTemplate := "horse";
		meNewPrice := meNewPrice + 350;
	endif
	
	return meNewPrice;

endfunction

function GetMyPrice()

	local myprice := HIRE_GP;
	if (me.strength > 50)
		myprice := myprice + (me.strength-50)*125;
	endif
	if (me.intelligence > 50)
		myprice := myprice + (me.intelligence-50)*25;
	endif
	if (me.dexterity > 55)
		myprice := myprice + (me.dexterity-55)*75;
	endif
	return myprice;

endfunction


function RunToIt(item)

	local numsteps;
	for (numsteps := 0; numsteps < 8; numsteps := numsteps +1)
		if ( distance(me, item) < 2 )
			return;
		else
			runtoward(item);
		endif
	endfor

endfunction

function FindObjinBackpack(obj)
	foreach item in EnumerateItemsInContainerOfObjType(me.backpack, obj )
		return item;
	endforeach
	return 0;
endfunction

function RunLikeHell(opponent := 0)

	cleareventque();
	
	SetWarMode( 0 );

	if (opponent)
		flee(opponent,25,15); //runnn
		return;
	endif

	local mex:= me.x, myy := me.y, tries := 0;
	while ((DistanceToLocation(me, mex, myy) < 10) and (tries < 25))
		tries := tries + 1;
		RunAwayFromLocation(me.x, me.y);
	endwhile

	cleareventque();

endfunction

function DistanceToLocation ( who, locx, locy )

	var npcx := who.x;
	var npcy := who.y;

	Var xdiff := abs(who.x - locx);
	var ydiff := abs(who.y - locy);

	if (xdiff > ydiff)
		return xdiff;
	else
		return ydiff;
	endif

endfunction

function create_rand_food(who)

	local food, i;	

	for (i:=0; i < 3; i:=i+1)
		case (RandomInt(8))
		1:	food := 0x09ea;
		2:	food := 0x1040;
		3:	food := 0x09b7;
		4: 	food := 0x1608;
		5: 	food := 0x09e9;
		6: 	food := 0x1044;
		7: 	food := 0x0c77;
		default: food := 0xc920;
		endcase
		CreateIteminBackpack(who, food, RandomInt(3));
	endfor

endfunction


