OK, here's the deal. The pol core allows us to attach 1 hitscript per weapon. That's not enough, since people will want to be able to poison silvered weapons. So Siggy and I came up with a plan: We'll have one main hitscript for all weapons, and have it loop through an array of hitscript cprops. Sure, it eats more RAM, but RAM is cheap. We want those poisoned, silver weapons!

This is still in testing, but here are the basic files:

hitscriptinc: goes in /include
mainhitscript: goes in /pkg/std/combat
makehitscript: goes in /scripts/control

After that, all you have to do is add "controlscript makehitscript" to each of your weapon definitions!