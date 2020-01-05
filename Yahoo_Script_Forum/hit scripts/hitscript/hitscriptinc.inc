// HitScript Include

use uo;
use util;

// DealDamage(defender, attacker, rawdamage)
// Modifies damage for anatomy, then applies it to the target.

function DealDamage(defender, attacker, rawdamage)

	rawdamage := rawdamage + ( CInt(GetObjProperty(attacker, 1) ) / 10);
	ApplyRawDamage(defender, rawdamage);

endfunction

// AdjustNoto(attacker)
// If we need to make any adjustments here, we can do it.

function AdjustNoto(attacker)

	return;

endfunction


// AlterHitScripts(defender, weapon, armor, rawdamage)
// If any of our effects call for altering the hit scripts (such as a
// one-shot weapon, like a Glass Sword, or a magic arrow), we can 
// remove them here.   We can also use this to add things like 
// communicable disesase, where we add a "diseased" prop to victim.

// function AlterHitScripts(defender, weapon, armor, rawdamage)
