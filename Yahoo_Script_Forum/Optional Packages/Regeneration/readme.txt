*****************************************************************
*								*
*      		        Regeneration system			*
*			   by Porthios				*
*		       inferno_13_86@yahoo.ca			*
*				ver: 1.0			*
*								*
*****************************************************************

Well, its quite simple. You got your normal regeneration rate which is in data files. They restore 1 stat every 5 seconds. What this does is call the object properties for regen rate. The value of the regen rate is what will be added on every 5 seconds. If the objprop is not found, its considered 0, which would be 1 every 5 seconds. If the value of the prop is one, its like 2 every 5 secs and so on. Here are the props:

h_regen  =  health regenartion
m_regen  =  mana regenartion
s_regen  =  stamina regenartion


NOTE:    
	any *_regen_rate that you may have in your scripts is not took underhand in this package. 	For this package to work like it should, all *_regen_rate 's should be deleted.

TODO:   make items that increase regeneration rate

BUGS:   None so far :-)