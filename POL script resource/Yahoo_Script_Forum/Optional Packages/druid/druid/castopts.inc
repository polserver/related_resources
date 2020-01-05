use uo;

include "include/attributes";

function usemana(caster, circle)
var umana;
var mana := GetMana(caster);

	case(circle)
		4: umana := 30;
		5: umana := 40;
		6: umana := 50;
		7: umana := 60;
		8: umana := 70;
	endcase
    SetMana(caster, Cint(mana - umana));
endfunction