///////////////////////////////////////////////////////////
// CreateNpc.inc
//
// Custom function to create NPCs from a package.
//
// Creator: Mercy
// Contact: mkow@sympatico.ca
//
// Created: 12-Sept-2000
// Updated: 12-Sept-2000
//
///////////////////////////////////////////////////////////

use uo;
use cfgfile;
use basic;

///////////////////////////////////////////////////////////
// Purpose: Custom function to create NPCs from a package
//			or otherwise.
// Params:  Same as CreateNpcFromTemplate() core function.
// Returns: npc			Ref to mobile object.
///////////////////////////////////////////////////////////
function CreateNpc(template, x, y, z, props := 0)
	template := CreateTemplateName(template);
	local npc := CreateNpcFromTemplate(template, x, y, z, props);
    return npc;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Find the package that the NPC is in.
// Params: 	template		Template name of npc.
// Returns:	template		Template name containing package.
///////////////////////////////////////////////////////////
function CreateTemplateName(template)
	var cfg;
	foreach pkgname in (polcore().packages)
		cfg := ReadConfigFile(":" + pkgname + ":npcdesc");
		if (cfg)
			if (FindConfigElem(cfg, template))
				return ":" + pkgname + ":" + template;
			endif
		endif
	endforeach

	// Not in a package, try config/npcdesc.cfg.
	return template;
endfunction

///////////////////////////////////////////////////////////
// Purpose: Returns the template name without package prefix.
// Params:  pkgtemplate		Npc template name.
// Returns: template		Bare template name.
///////////////////////////////////////////////////////////
function TemplateName(pkgtemplate)
	var start := find(pkgtemplate, ":", 2) + 1;
	if (!start)
		return pkgtemplate;
	endif

	return pkgtemplate[start, len(pkgtemplate)];
endfunction

///////////////////////////////////////////////////////////
// Purpose: Returns the name of the package the NPC is in.
// Params: npctempl		Npc Template name.
// Returns: package		Package the NPC is in.
///////////////////////////////////////////////////////////
/*function PackageName(npctempl)
	var end := find(npctempl, ":", 2) - 1;
	if (!end)
		return "";
	endif

	return npctempl[2, end];
endfunction
*/
