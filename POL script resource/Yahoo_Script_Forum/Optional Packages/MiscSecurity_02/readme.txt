/////////////////////////////////////////////
//
// Misc security checks/banned ip checks
//
/////////////////////////////////////////////
//
// Updated      : 26 February 2003
// Author       : MuadDib
// Core Required: 94
// ExtraRequired: Login.src and Reconnect.src
//
//
/////////////////////////////////////////////
//
//   - Config files required for /config
//   - logon and reconnect script addons
//
/////////////////////////////////////////////
// Thanks
// ======
//
//  - To those who annoyed me in order to cause
//	these being created
//
/////////////////////////////////////////////
//
// Installation (POL 94)
// ============================
//
// 1. Backup all your existing /data
// 2. Add `include "include/security"` to logon
//      and reconnect scripts.
// 3. Use the functions within the inc at the top
//      of your logon/reconnect to be sure they
//      run before rest of the script.
// 3. Extract the 4 .cfg files to your /config
//	directory
///////////////////////////////////////////
//
//  Email me with any issues, bugs, problems
//  and I can help you fix them or add them
//  to this pkg and update it on the forum
//  "webmaster@rcsi-usa.com"
//
/////////////////////////////////////////////
//
// Additional Notes.....
// ============================
// 1. Added IP vs Acct checking for cmdlevel
// 2. Future textcmds to add to the staffips
//	file from ingame and reloading of it.
// 3. Ditto for manual adding of banned,
//	allowany, and allowedips and reload
//
/////////////////////////////////////////////


*********************************************
