m_thorns enchantment
sysver 1.05+ [from readme]
------------------------------------
Creator		S!tH
Email		sithilius@hotmail.com
NormalMods	No.
Bias		Armour, Else.
Level		4
Shard		Freelance (no shard)
WasHitScript	thorned.src [included, copy to combat\enchScripts]
DidHitScript	none
Description	Percentage of damage recieved also hurts the attacker. Percentage is "t_r_amt" CProp. Default is 1-40
------------------------------------
[Senchantedhit.cfg element]

Enchantment m_thorns
{
	Name m_thorns
	Suffix thorns

	WasHitScript enchScripts\thorned
	AddRanProp t_r_amt 40
	noNormalMods 1
	idstring $t_r_amt#% of damage also effects attacker.
	level 4
}
------------------------------------
[Enchantment def, level 4]

	Enchantment m_thorns arm else