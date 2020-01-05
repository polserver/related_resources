heavenly enchantment
sysver 1.13+ [from readme]
------------------------------------
Creator		Naksu
Email		Naksu@naksu.net
NormalMods	Yes.
Bias		Weapons
Level		5
Shard		The Fallen Realm (http://fallenrealm.cjb.net) & The Dragons Land (http://dragons.hellfish.org)
WasHitScript	none
DidHitScript	heavenhit.src [included, copy to combat\enchScripts]
Description	+150% damage to undead, colour 1953 (Thues pkg), +6 to damage, mana regeneration
------------------------------------
[Senchantedhit.cfg element]

Enchantment heavenly
{
	Name heavenly
	Strengths 
	Weaknesses 
	StrengthMulti 1
	StrengthAdd   0
	WeaknessDiv   1
	WeaknessSub   0
	NormAdd	      6
	NormSub	      0
	NormMulti     1
	NormDivis     1
	Prefix heavenly
	Suffix 

	DidHitScript enchScripts\heavenhit
	noNormalMods 0
	toColour 1953
	level 4
	AddRanProp d2mAmt 80
	idstring 250% damage to undead.
        idstring +6 to damage.
	idstring $d2mAmt#% of damage regenerates mana.
        conflicts silver
}

------------------------------------
[Enchantment def, level 5]

	Enchantment heavenly wep