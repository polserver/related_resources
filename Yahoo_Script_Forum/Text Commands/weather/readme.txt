Weather commands
by Angreal


ok....just a few comments on these things....

now I know there is a setweather command, in fact I based all of these off of that one :)
but I wanted to make some 'quicker' and easier weather commands....

for now they are all set up as .<weathertype> <region> for the input where weathertype is
the command name (snow, rain, thunderstorm...yada yada) and region is the *weather* region
in which you want the weather to occur....

the only one I have really spent any time at all on is the thunderstorm (putting in the sound fx
and cycling), so you *may* wanna do some 'fixing up' on the others....

also if you run a single region, i.e. "Background", you can simplify the commands further by doing
the following:
1) in the broadcast line change the output text to say whatever you want, i.e. "a thunderstorm sweeps
across the whatzit lands" and remove the '+ params' bit
2) in the SetRegionWeatherLevel command, change 'params' to your region name, i.e. "Background" if you
haven't modified your regions at all
3) in the program line, remove the ', params' so that you will only have something like: 
   program thunderstorm( who )
once you have done this you will be set to have your command be just .<weathertype>   :)


things that need to be fixed still:
1) when you have multiple weather/light regions and have a storm sweep the whole lands, it will not
return to the daynight cycle properly....this is a minor bug that can be avoided by making sure your
weather regions and light regions align, but I don't like this right now...


any comments/questions/suggestions send em to saangreal@excite.com

enjoy all