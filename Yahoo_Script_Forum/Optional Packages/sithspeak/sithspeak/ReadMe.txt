SithSpeak
By S1tH


**********************************
Descriptionz0r
**********************************
One day I had an idea for an include file that would make it really easy for NPCs to hold semi-decent conversations. This is what became of that idea, the NPCs can hold multi-pathed conversations, and can have conversations with different people at the same time. They can remember people as friends, enemies or neutral - and each thing the person says can have an affect on that status. The status of a persons relationship with the NPC can retrieved/modified with two easy functions. The friendship data is not remembered over a shutdown or a script restart, though it could be easily modified to do so.


**********************************
Installationz0r
**********************************
1) Put 'sSpeech.inc' into your scripts\include


2) When an NPC hears a speech event, use:

  sHear( ev.source, ev.text );


3) To make a new speech group, simply make a new config like the ones defined, and add the following line to the npcdesc.cfg entry:

  speachConfig mySpeechGroup


**********************************
Helpz0r
**********************************
If you need help, you can contact me via ICQ #38288137 or by email, sithilius@hotmail.com