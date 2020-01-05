///////////////////////////////////////////////////////////
// Speech.inc
//
// Main Speech Processing.  DO NOT CUSTOMIZE HERE!!
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use cfgfile;
use npc;
use basic;

include "../../../../scripts/include/findcity";

///////////////////////////////////////////////////////////
// CONSTS
///////////////////////////////////////////////////////////
const SPEECHDIR		:= ":ai:/npcspeech/";

const SAYINVITE		:= "grpinvite";
const SAYACCEPT		:= "grpaccept";
const SAYATTACK		:= "grpattack";
const SAYHELP		:= "grphelp";
const SAYAID		:= "grpaid";
const SAYCOMBAT		:= "incombat";
const SAYFLEE		:= "fleecombat";
const SAYLOOT		:= "itemloot";
const SAYENGAGED	:= "engagedme";

///////////////////////////////////////////////////////////
// GLOBAL VARIABLES
///////////////////////////////////////////////////////////
var speechcfg 	:= 0;
var myspeech 	:= 0;
var nosaystuff 	:= 0;

///////////////////////////////////////////////////////////
// GLOBAL CODE
///////////////////////////////////////////////////////////
if (mydesc.speech)
	speechcfg := ReadConfigFile(SPEECHDIR + mydesc.speech);
	if (!speechcfg)
		syslog("Could not read: " + SPEECHDIR + mydesc.speech + ".cfg");
	endif
	myspeech := FindConfigElem(speechcfg, mydesc.speech);
	if (!myspeech)
		syslog("Could not find element " + mydesc.speech + " in " + SPEECHDIR + mydesc.speech + ".cfg");
	endif
endif

///////////////////////////////////////////////////////////
// Purpose: This is the main speech processing function.
// Params:  ev			Event object.
//			incombat	Am I fighting right now?
// Returns: N/A
///////////////////////////////////////////////////////////
function ProcessSpeech(byref ev, incombat := 0)
	// No speech to process.
	if (!myspeech)
		return 0;
	endif

	var text := lower(ev.text);

	// Custom hook.
	if (!SpeechTest(ev))
		return 0;
	endif

	// Check if name must be spoken.
	if (ai.NameRespond and !NameSpoken(text))
		return 0;
	endif

	// Don't turn towards source if engaged in combat!
	if (!incombat)
		TurnToward(ev.source);
	endif

	// Run user defined speech function.
	if (!Speech(ev))
		return 0;
	endif

	// If in combat, give standard in combat response.
	if (incombat)
		text := SAYCOMBAT;
	endif

	var response := GetResponseTo(text);
	if (!response)
		return 0;
	endif

	// Substitiute the special tags.
	response := InsertSpeechTags(response, ev.source);

	Say(response);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Returns the response to speech.
// Params:  text		Heard words.
// Returns: response	The text response
///////////////////////////////////////////////////////////
function GetResponseTo(byref text)
	// Check each word spoken.
	var response;
	foreach word in SplitWords(text)
		response := GetConfigString(myspeech, word);
		if (response)
			break;
		endif
	endforeach

	if (!response)
		response := GetConfigString(myspeech, "default");
		if (!response)
			response := "";
		endif
	endif

	return response;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Processes the supported speech tags in the response.
// Params:  text		Text response.
//			source		The speaker of the text.
// Returns: response	Response with substituted tags.
///////////////////////////////////////////////////////////
function InsertSpeechTags(byref text, byref source)
	var response := "";
	foreach word in SplitWords(text)
		case(word)
			"<myname>":	word := me.name;
			"<name>":	word := source.name;
			"<town>":	word := FindCity(me);
			"<race>":
				word := GetObjProperty(source, "Race");
				if (!word)
					word := "Race";
				endif
		endcase

		response := response + " " + word;
	endforeach

	return response;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Say special tag words.
// Params:  none
// Returns: N/A
///////////////////////////////////////////////////////////
function SaySpeechStuff(what)
	// If poisoned, the don't scream about it every second!

	if (GetObjProperty(me, "poison_level"))
		if (nosaystuff)
			return 0;
		endif
		nosaystuff := 1;
	else
		if (nosaystuff)
			nosaystuff := 0;
		endif
	endif

	var evn := struct;
	evn.+source := me;
	evn.+text := me.name + " " + what;
	ProcessSpeech(evn);
endfunction

///////////////////////////////////////////////////////////
// Purpose: Checks if name was spoken in the sentence.
//			Only looks at the 1st word in the name, second
//			if first is 'a'.
// Params:  text		Text spoken.
// Returns: 1	Name was spoken.
//			0	Name was not spoken.
///////////////////////////////////////////////////////////
function NameSpoken(text)
	var name;
	text := lower(text);
	var lname := SplitWords(lower(me.name));

	name := lname[1];

	if (name = "a")  // Ignore the 'a' in name.
		name := lname[2];
	endif

	if (text[name])
		return 1;
	endif

	return 0;
endfunction