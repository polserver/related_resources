///////////////////////////////
//S!tH Blacksmithy for pol092//
//////////////////////////////////
Contact Info:			//
             sith@wn.com.au	//
                   38288137	//
///////////////////////////////////////////
Base: Pol091 Standard Blacksmithy Package//
///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Changes:																	//
		-Four qualities:														//
				-Exceptional													//
				-Above Average													//
				-Regular													//
				-Below Average													//
		-Coloured Ingots:														//
				-Definitions for coloured ingot smithy runs through "ingots.cfg"						//
				-Can define:													//
					-Minimum craft skill required										//
					-Skill to add to craft difficulty									//
					-Colour of item crafted from ingot									//
					-Bonus points (skill gain)										//
					-Bonus HP on item											//
					-Prefix on item ( ie. "Copper" )									//
					-Suffix on item												//
					-Enchantments: Adds each entry to an "Enchantments" array CProp on item.				//
					-Damage Modifier (dmg_mod)										//
					-Armour Modifier (ar_mod)										//
					-"reqProp". Will only allow this ingot to be crafted with a smithy tool that has this CProp set to true.//
					-"reqEnch". Same as above, but checks the Enchantments CProp for an enchantment instead.		//
		-Other stuff:															//
				-Sets a CProp on the item "cashMod":										//
					1.0 to 2.0, depending on the difficulty to craft...							//
						1.0 = 50 skill or less										//
						2.0 = 100 skill required									//
					This could be used for coloured armour buying/selling on vendors for more?				//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
To Modify:							//
		-Qualities:					//
			See function "modifyQuality"		//
		-Enable Autoloop:				//
			Read thru a bit. See big commented-out	//
			section.				//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
Notes:								//
	Read through it a bit...				//
	And change the ingots.cfg to suit your shard.		//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
///////////////////Thanks to Myrathi and Xandro///////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////